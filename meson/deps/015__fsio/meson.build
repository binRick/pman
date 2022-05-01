fsio_lib = library('fsio', 
  '../../../submodules/fsio/src/fsio.c', 
  install: false, dependencies: [stringbuffer_dep], 
  include_directories: [
  '../../../submodules/fsio/include',
  '../../../submodules/c_string_buffer/include',
  ]
)
fsio_dep = declare_dependency(include_directories: [
], link_with: fsio_lib)
deps += fsio_dep
