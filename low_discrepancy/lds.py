# a simple snippet to generate low-discrepancy sequences for arbitrary dimensions
# based on https://extremelearning.com.au/unreasonable-effectiveness-of-quasirandom-sequences


def low_discrepancy_sequence(num_dimensions: int):
    y = generate_increments(num_dimensions)
    x = [0] * num_dimensions
    while True:
        x = [(x[i] + y[i]) % 1.0 for i in range(0, num_dimensions)]
        yield x


def generate_increments(num_dimensions: int):
    x = 1.0 / phi(num_dimensions)
    return [x**k for k in range(1, num_dimensions+1)]


def phi(d: int):
    last_x, x = 1.0, 2.0
    while x != last_x:
        last_x = x
        x = (x + 1)**(1.0 / (d + 1))
    return x
