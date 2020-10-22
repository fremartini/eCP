from distutils.core import setup, Extension

name = 'eCP_wrapper'
module = Extension(f'_{name}', sources=['eCP_wrap.cxx', 'combined.cpp'])

setup (name = name,
       version = '0.2',
       author      = "frem nime mskk",
       description = """Wrapper for the eCP algorithm""",
       ext_modules = [module],
       py_modules = [name],
       )