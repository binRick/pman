bestline_lib = library('bestline', '../../../submodules/bestline/bestline.c', install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/bestline',
  ]
)
bestline_dep = declare_dependency(include_directories: ['../../../submodules/bestline'], link_with: bestline_lib)
deps += bestline_dep
