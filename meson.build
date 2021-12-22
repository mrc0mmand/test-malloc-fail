project('test-malloc-fail', 'c',
  version : '0.1',
  default_options : ['c_std=gnu99', 'warning_level=2'])

shared_library('test_malloc_fail',
               'test_malloc_fail.c',
               c_args: ['-g', '-O0', '-Wall', '-D_GNU_SOURCE'],
               version: '0.0.1',
               soversion: '0')

