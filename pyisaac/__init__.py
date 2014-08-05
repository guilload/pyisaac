"""
A Python wrapper of the C implementation of ISAAC, a cryptographically secure
 pseudo random number generator (CSPRNG) designed and implemented in 1996 by Bob
 Jenkins.

http://burtleburtle.net/bob/rand/isaac.html
"""

import pyisaac.np

from .core import random, randuint32, seed


seed()
