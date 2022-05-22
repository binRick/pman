bytes_lib = library('bytes', '../../../deps/bytes/bytes.c', install: false, dependencies: [], 
  include_directories: [
    '../../../deps/bytes',
  ]
)
bytes_dep = declare_dependency(include_directories: ['../../../deps/bytes'], link_with: bytes_lib)
deps += bytes_dep
