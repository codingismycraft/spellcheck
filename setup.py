
from distutils.core import setup, Extension

extra_compile_args = ["-std=c++11", "-Wall", "-Wextra", "-DNDEBUG", "-O3"]

setup(
    name = 'wdistModule', 
    version = '0.0.1',
    ext_modules = [
        Extension
        (
            'wdistModule',
            [
                './spellcheck/src/wdist.cpp', 
                './spellcheck/src/matcher.cpp', 
                'wdistmodule.c'
                ],
            include_dirs=["./spellcheck/include"],
            extra_compile_args=extra_compile_args
        )
    ]
)
