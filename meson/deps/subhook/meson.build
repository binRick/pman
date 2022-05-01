subhook_lib = library('subhook', '../../../submodules/subhook/subhook.c', install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/subhook',
  ]
)
subhook_dep = declare_dependency(include_directories: ['../../../submodules/subhook'], link_with: subhook_lib)
deps += subhook_dep
