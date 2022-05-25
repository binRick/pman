fsio_lib = library('fsio', 
  '../../../submodules/c_fsio/src/fsio.c', 
  install: false, dependencies: [stringbuffer_dep], 
  include_directories: [
  '../../../submodules/c_fsio/include',
  '../../../submodules/c_string_buffer/include',
  ]
)
fsio_dep = declare_dependency(include_directories: [
], link_with: fsio_lib)
deps += fsio_dep
