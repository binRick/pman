wildcardcmp_lib = library('wildcardcmp', '../../../submodules/wildcardcmp/wildcardcmp.c', install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/wildcardcmp',
  ]
)
wildcardcmp_dep = declare_dependency(include_directories: ['../../../submodules/wildcardcmp'], link_with: wildcardcmp_lib)
deps += wildcardcmp_dep
