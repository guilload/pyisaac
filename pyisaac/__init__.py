"""
A Python wrapper of the C implementation of ISAAC, a cryptographically secure
 pseudo random number generator (CSPRNG) designed and implemented in 1996 by Bob
 Jenkins.

http://burtleburtle.net/bob/rand/isaac.html
"""
import os
import time
import warnings

import _pyisaac


def seed(sd=None):
    """
    Seed the CSPRNG.

    >>> pyisaac.seed('pyisaac')
    >>> pyisaac.random()
    0.9284197092056274
    """
    if sd is None:
        try:
            sd = os.urandom(_pyisaac.RANDSIZB)
        except NotImplementedError:
            sd = str(time.time())
            warnings.warn('Algorithm seeded from system time, not suitable '
                          'for cryptographic use!')

    _pyisaac.seed(sd)

seed()

random = _pyisaac.random
randuint32 = _pyisaac.randuint32
