from distutils.core import setup, Extension


pyisaac = Extension('pyisaac', sources=['pyisaac/pyisaac.c', 'pyisaac/rand.c'])

setup(name = 'pyisaac',
      version = '0.1',
      description = 'ISAAC: a fast cryptographically secure pseudo random number generator',
      author='Adrien Guillo',
      author_email='adrien@guilload.com',
      url='https://github.com/guilload/pyisaac',
      platforms=['Linux', 'OS X'],
      license='MIT',
      ext_modules = [pyisaac])