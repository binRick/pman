strsplit_lib = library('strsplit', '../../../deps/strsplit/strsplit.c', install: false, dependencies: [], 
  include_directories: [
    '../../../deps',
    ]
  )
strsplit_dep = declare_dependency(include_directories: [], link_with: strsplit_lib)
deps += strsplit_dep
