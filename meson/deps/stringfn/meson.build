
stringfn_lib = library('stringfn', '../../../submodules/c_stringfn/src/stringfn.c', install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/c_stringfn/include',
  ]
)
stringfn_dep = declare_dependency(include_directories: [], link_with: stringfn_lib)
deps += stringfn_dep
