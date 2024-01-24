# Configure Intel MKL & FFTW (for Apple M-series)
if (${IS_AARCH64})
    if (APPLE)
        message(WARNING "Apple Silicon is not yet supported")
    else ()
        message(WARNING "ARM based systems is not yet supported")
    endif ()
    set(FFTW_INCLUDE_DIR "${CMAKE_BINARY_DIR}/vendor/include/fftw")
    file(MAKE_DIRECTORY ${FFTW_INCLUDE_DIR})
    message(STATUS "Creating dummy fftw3.h")
    file(TOUCH ${FFTW_INCLUDE_DIR}/fftw3.h)
    include_directories(SYSTEM ${FFTW_INCLUDE_DIR})
else ()
    # MKL
    if (EXISTS ${CMAKE_BINARY_DIR}/venv/lib/cmake/mkl/MKLConfig.cmake)
        include(${CMAKE_BINARY_DIR}/venv/lib/cmake/mkl/MKLConfig.cmake)
    endif ()
    set(MKL_LINK "static")
    set(MKL_ILP64 ON)
    find_package(MKL CONFIG REQUIRED PATHS $ENV${MKLROOT})
    include_directories(SYSTEM ${MKL_ROOT}/include/fftw)
    link_directories(${MKL_ROOT}/lib)
endif ()
