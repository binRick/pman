list_lib = library('list', 
'../../../deps/list/list_iterator.c',
'../../../deps/list/list_node.c',
'../../../deps/list/list.c', 
install: false, dependencies: [], 
  include_directories: [
    '../../../deps/list',
  ]
)
list_dep = declare_dependency(include_directories: ['../../../deps/list'], link_with: list_lib)
deps += list_dep
