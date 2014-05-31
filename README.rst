=======
pyisaac
=======

.. image:: https://secure.travis-ci.org/guilload/pyisaac.png?branch=master

Overview
========
*pyisaac* is a Python wrapper of the C implementation of `ISAAC <http://burtleburtle.net/bob/rand/isaac.html>`_, a cryptographically secure pseudo random number generator (CSPRNG), designed and implemented in 1996 by Bob Jenkins.

Install
=======
The package is hosted on `PyPI <http://pypi.python.org/pypi/pyisaac>`_::

$ pip install pyisaac
$ easy_install pyisaac

Use
===

The API is simple:

>>> import pyisaac
>>> pyisaac.random()
0.3417196273803711
>>> pyisaac.seed('pyisaac')
>>> pyisaac.random()
0.9284197092056274

License
=======

The MIT License (MIT)

Copyright (c) 2014 Adrien Guillo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
