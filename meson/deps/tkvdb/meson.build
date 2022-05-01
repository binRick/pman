tkvdb_lib = library('tkvdb', '../../../submodules/tkvdb/tkvdb.c', install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/tkvdb',
  ]
)
tkvdb_dep = declare_dependency(include_directories: ['../../../submodules/tkvdb'], link_with: tkvdb_lib)
deps += tkvdb_dep
