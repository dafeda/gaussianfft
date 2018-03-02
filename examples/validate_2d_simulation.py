import numpy as np
import matplotlib.pyplot as plt
import nrlib


VTYPES = [
    'spherical',
    'exponential',
    'general_exponential',
    'matern32',
    # 'matern52',
    'matern72',
    'gaussian',
]


def example_cube():
    nrlib.seed(123)
    n = 200
    p = 400
    d = 0.5
    variogram = nrlib.variogram('gaussian', main_range=100, perp_range=100)
    field = nrlib.advanced.simulate(variogram, n, d, n, d, padx=p, pady=p)
    field2d = np.array(field).reshape((n, n), order='F')
    plot_surface(field2d, 'Gaussian variogram, insufficient simulation padding')
    plt.show()


def example_cubes():
    n = 100
    d = 1.0
    for i, p in enumerate([100, 200, 300, 400]):
        nrlib.seed(123)
        variogram = nrlib.variogram('gaussian', main_range=100, perp_range=100)
        field = nrlib.advanced.simulate(variogram, n, d, n, d, padx=p, pady=p)
        field2d = np.array(field).reshape((n, n), order='F')
        plt.subplot(411 + i)
        plot_surface(field2d, 'Gaussian variogram, padding={} x range'.format(int(p/100)))
    plt.show()


def example_box():
    nrlib.seed(123)
    variogram = nrlib.variogram('exponential', main_range=1000.0, perp_range=1000.0,)
    nx, ny = 50, 100
    dx, dy = 10, 10
    field = nrlib.simulate(variogram, nx, dx, ny, dy)
    field2d = np.array(field).reshape((nx, ny), order='F')
    plot_surface(field2d, 'Exponential variogram')
    plt.show()


def example_variogram():
    nx, ny = 100, 100
    dx, dy = 10.0, 10.0
    fig, axes = plt.subplots(2, 3)
    for vt, ax in zip(VTYPES, axes.flatten()):
        v = nrlib.variogram(vt, 1000.0, 250.0)
        f = nrlib.simulate(v, nx, dx, ny, dy).reshape((nx, ny), order='F')
        ax.imshow(f, interpolation='None')
        ax.set_title(vt)
    plt.suptitle('Variogram comparisons')
    plt.show()


def example_variogram2():
    nx, ny = 100, 100
    dx, dy = 10.0, 10.0
    px, py = nx * 7, ny * 7
    fig, axes = plt.subplots(2, 3)
    for vt, ax in zip(VTYPES, axes.flatten()):
        nrlib.seed(5545)
        v = nrlib.variogram(vt, 1000.0, 250.0)
        f = nrlib.advanced.simulate(v, nx, dx, ny, dy, padx=px, pady=py).reshape((nx, ny), order='F')
        ax.imshow(f, interpolation='None')
        ax.set_title(vt)
    plt.suptitle('Variogram comparisons (equal padding)')
    plt.show()


def plot_surface(field, title):
    plt.imshow(field, interpolation='None')
    plt.title(title)


if __name__ == '__main__':
    import sys
    examples = {
        'box': example_box,
        'cube': example_cube,
        'cubes': example_cubes,
        'vario': example_variogram,
        'vario2': example_variogram2,
    }
    if len(sys.argv) != 2 or sys.argv[1] not in examples:
        print("Run as")
        print("  [python] {} <example>".format("validate_2d_simulation"))
        print("")
        print("  <example> being one of:")
        for f in examples.keys():
            print("    " + f)
    else:
        examples[sys.argv[1]]()
