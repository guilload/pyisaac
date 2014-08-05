from codecs import open
from os import path

import numpy

from setuptools import find_packages, setup, Extension


here = path.abspath(path.dirname(__file__))

with open(path.join(here, 'README.rst'), encoding='utf-8') as f:
    long_description = f.read()


pyisaac = Extension('_pyisaac',
                    include_dirs=[numpy.get_include()],
                    sources=['pyisaac/_pyisaac.c', 'pyisaac/rand.c'])

setup(name='pyisaac',
      version='0.1',
      description='ISAAC: a fast cryptographically secure pseudo random number generator',
      long_description=long_description,
      url='https://github.com/guilload/pyisaac',
      author='Adrien Guillo',
      author_email='adrien@guilload.com',
      license='MIT',
      classifiers=[
                   'Development Status :: 3 - Beta',
                   'Intended Audience :: Developers',
                   'License :: OSI Approved :: MIT License',
                   'Programming Language :: Python :: 2.6',
                   'Programming Language :: Python :: 2.7',
                   ],
      keywords='ISAAC, CSPRNG, PRNG, cryptography',
      platforms=['Cross-platform'],
      ext_modules=[pyisaac],
      install_requires=['numpy'],
      packages=find_packages(exclude=['tests']),
      )
