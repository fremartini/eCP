from distutils.core import setup, Extension

name = 'eCP_wrapper'
module = Extension(f'_{name}', 
                   sources=['eCP_wrap.cxx', 'combined.cpp'],
                   extra_compile_args=["-O3"])

setup (name = name,
       version = '0.3',
       author      = "frem nime mskk",
       description = """Wrapper for the eCP algorithm""",
       ext_modules = [module],
       py_modules = [name],
       )