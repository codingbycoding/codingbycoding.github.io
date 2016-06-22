#
"this is setup for core build"


from distutils.core import setup, Extension

#Extension('pyext', source=['pyext.c'])

MOD='pyext'

setup(name=MOD, ext_modules=[Extension(MOD, sources=['pyext.c'])])
