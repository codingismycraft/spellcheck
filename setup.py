
from distutils.core import setup, Extension

setup(
    name = 'wdistModule', 
    version = '0.0.1',
    ext_modules = [
        Extension
        (
            'wdistModule',
            ['./spellcheck/src/wdist.cpp', 'wdistmodule.c'],
            include_dirs=["./spellcheck/include"]
        )
    ]
)
