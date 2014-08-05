import _pyisaac


__all__ = ('rand',)


def rand(*dimensions):
    """
    rand(d0, d1, ..., dn)

    Random values in a given shape.

    Create a numpy array of the given shape and propagate it with
    random samples from a uniform distribution over ``[0, 1)``.

    Parameters
    ----------
    d0, d1, ..., dn : int, optional
        The dimensions of the returned array, should all be positive.
        If no argument is given a single Python float is returned.

    Returns
    -------
    out : ndarray, shape ``(d0, d1, ..., dn)``
        Random values.

    Examples
    --------
    >>> pyisaac.np.rand(3, 2)
    array([[ 0.14022471,  0.96360618],
           [ 0.37601032,  0.25528411],
           [ 0.49313049,  0.94909878]])
    """
    if len(dimensions) == 0:
        return _pyisaac.random()
    else:
        if any(dim < 0 for dim in dimensions):
            raise ValueError('negative dimensions are not allowed')

        return _pyisaac.np_rand(dimensions)
