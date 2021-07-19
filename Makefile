NAME = nrlib
VERSION = $(shell ./bin/find-version-of-docker-image.sh)
DOCKER_REGISTRY_SERVER = git.equinor.com:4567
DOCKER_REGISTRY = $(DOCKER_REGISTRY_SERVER)/sdp/nrlib
IMAGE_NAME = $(DOCKER_REGISTRY)/$(NAME):$(VERSION)

EMPTY :=

# Use packages provided by a distribution, e.g. RMS
USE_SITE_PACKAGES ?= yes
USE_USER_INSTALL ?= no
USE_SKIP_LOCKING ?= no

SITE_PACAGES_OPTION := $(EMPTY)
KEEP_OUTDATED := $(EMPTY)
USER_INSTALL := $(EMPTY)
SKIP_LOCKING := $(EMPTY)

ifeq ($(USE_SITE_PACKAGES),yes)
SITE_PACAGES_OPTION := --site-packages
KEEP_OUTDATED := --keep-outdated
USER_INSTALL := --user
else
# Override user installation
ifeq ($(USE_USER_INSTALL),yes)
USER_INSTALL := --user
endif
endif

ifeq ($(USE_SKIP_LOCKING),yes)
SKIP_LOCKING := --skip-lock
endif


CODE_DIR ?= $(shell pwd)
SETUP.PY := $(CODE_DIR)/setup.py

BOOST_VERSION ?= 1.76.0
BOOST_DIR := $(CODE_DIR)/sources/boost/$(BOOST_VERSION)
BOOST_ARCHIVE := $(BOOST_DIR).tar.gz

DOCKERFILE := $(CODE_DIR)/Dockerfile

PIPENV_TO_BE_INSTALLED := pipenv

PYTHON ?= $(shell which python)
PIP ?= $(PYTHON) -m pip --proxy "$(HTTPS_PROXY)"
PIPENV ?= $(PYTHON) -m pipenv
RUN ?= $(PIPENV) run
PY.TEST ?= $(RUN) python -m pytest
VIRTUAL_PYTHON ?= $(shell $(PIPENV) --venv)/bin/python
MINIMUM_NUMPY_VERSION := 1.10.4

DISTRIBUTION_DIR ?= $(CODE_DIR)/dist

NRLIB_LINKING ?= static

PYPI_SERVER ?= http://pypi.aps.equinor.com:8080
PYPI_NAME := statoil

define PYPIRC
[distutils]
index-servers =
    $(PYPI_NAME)

[$(PYPI_NAME)]
repository: $(PYPI_SERVER)
username: $(PYPI_USER)
password: $(PYPI_PASSWORD)
endef
export PYPIRC

.PHONY: all tests clean build

docker-image:
	docker build --pull --rm --tag $(IMAGE_NAME) --file $(DOCKERFILE) $(CODE_DIR)

docker-push-image: docker-image
	docker push $(IMAGE_NAME)

docker-login:
	docker login $(DOCKER_REGISTRY_SERVER)

check-requirements: install-requirements
	$(PIPENV) check

install-wheel:
	$(PIPENV) install $(SKIP_LOCKING) $(DISTRIBUTION_DIR)/$(shell ls $(DISTRIBUTION_DIR)) || $(PIP) install -U $(DISTRIBUTION_DIR)/$(shell ls $(DISTRIBUTION_DIR))

install: install-requirements build-boost-python
	NRLIB_LINKING=$(NRLIB_LINKING) \
	CXXFLAGS="-fPIC" \
	$(PYTHON) $(SETUP.PY) build_ext --inplace build install

install-requirements: setup-virtual-environment
	$(PIPENV) install --dev $(KEEP_OUTDATED) $(SKIP_LOCKING)

setup-virtual-environment: install-pipenv create-virtual-env

create-virtual-env:
	$(PIPENV) --venv || $(PIPENV) --python=$(PYTHON) $(SITE_PACAGES_OPTION)

install-pipenv:
	$(PIPENV) 2>&1 >/dev/null && echo "Pipenv already installed" || $(PIP) install $(USER_INSTALL) $(PIPENV_TO_BE_INSTALLED)

tests: install-requirements
	$(PY.TEST) $(CODE_DIR)/tests

upload: pypirc
	$(PYTHON) $(SETUP.PY) register -r $(PYPI_NAME) upload -r $(PYPI_NAME)

pypirc:
	echo "$$PYPIRC" > $(CODE_DIR)/.pypirc

build-wheel: build
	$(VIRTUAL_PYTHON) $(SETUP.PY) bdist_wheel --dist-dir $(DISTRIBUTION_DIR)

build: build-boost-python
	NRLIB_LINKING=$(NRLIB_LINKING) \
	CXXFLAGS="-fPIC -fpermissive" \
	$(VIRTUAL_PYTHON) $(SETUP.PY) build_ext --inplace build

build-boost-python: setup-virtual-environment boost install-numpy
	CODE_DIR=$(CODE_DIR) \
	  $(CODE_DIR)/bootstrap.sh \
	                   --prefix=$(shell pwd)/build \
	                   --with-python=$(VIRTUAL_PYTHON) \
	                   --with-icu && \
	CPLUS_INCLUDE_PATH=$(shell $(VIRTUAL_PYTHON) -c "from sysconfig import get_paths; print(get_paths()['include'])") \
	  $(CODE_DIR)/b2   --with-python \
	                   --with-filesystem \
	                   --with-system \
	                   -q \
	                   cxxflags=-fPIC \
	                   cflags=-fPIC \
	                   python-debugging=off \
	                   threading=multi \
	                   variant=release \
	                   link=$(NRLIB_LINKING) \
	                   runtime-link=$(NRLIB_LINKING) \
	                   stage

boost: $(BOOST_ARCHIVE) $(BOOST_DIR)

$(BOOST_ARCHIVE):
	mkdir -p $(CODE_DIR)/sources/boost
	curl -L --output $(BOOST_DIR).tar.gz \
	https://boostorg.jfrog.io/artifactory/main/release/$(BOOST_VERSION)/source/boost_$(shell echo $(BOOST_VERSION) | tr '.' '_').tar.gz

$(BOOST_DIR):
	mkdir -p $(BOOST_DIR)
	tar -xvf $(BOOST_ARCHIVE) -C $(BOOST_DIR) --strip-components=1

	# Remove unnecessary files, some of these are binary, and others are encoded in an encoding incompatible with UTF-8
	rm -rf $(shell find $(BOOST_DIR) -name 'doc' -type d)
	rm -rf $(shell find $(BOOST_DIR) -name 'test' -type d)
	rm -f  $(shell find $(BOOST_DIR) -name '*.html' -type f)

	cp -r $(BOOST_DIR)/boost $(CODE_DIR)

	# Copy necessary 'libs' files
	mkdir -p $(CODE_DIR)/libs
	for item in config filesystem headers python system Jamfile.v2 ; do \
		cp -r $(BOOST_DIR)/libs/$$item $(CODE_DIR)/libs ; \
	done

	# Copy necessary bootstrapping files
	for item in tools boost-build.jam boostcpp.jam bootstrap.sh Jamroot ; do \
		cp -r $(BOOST_DIR)/$$item $(CODE_DIR) ; \
	done

clean-boost:
	rm -rf $(CODE_DIR)/boost \
	       $(CODE_DIR)/tools \
	       $(CODE_DIR)/libs \
	       $(CODE_DIR)/boost-build.jam \
	       $(CODE_DIR)/boostcpp.jam \
	       $(CODE_DIR)/bootstrap.sh \
	       $(CODE_DIR)/Jamroot \
	       $(CODE_DIR)/project-config.jam* \
	       $(CODE_DIR)/boost_source_files.txt

install-numpy:
	$(VIRTUAL_PYTHON) -c 'import numpy' || $(PIPENV) install 'numpy==$(MINIMUM_NUMPY_VERSION)' $(SKIP_LOCKING)

clean:
	cd $(CODE_DIR) && \
	rm -rf build \
	       nrlib.egg-info \
	       dist \
	       bin.v2 \
	       .pytest_cache \
	       project-config.jam* \
	       b2 \
	       bjam \
	       bootstrap.log \
	       .pypirc \
	       *.so
