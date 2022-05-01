parson_lib = library('parson', '../../../deps/parson/parson.c', install: false, dependencies: [], 
  include_directories: [
    '../../../deps/parson',
  ]
)
parson_dep = declare_dependency(include_directories: [], link_with: parson_lib)
deps += parson_dep
