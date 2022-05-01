simpleconf_lib = library('simpleconf', '../../../submodules/simpleconf/simpleconf.c', install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/simpleconf',
  ]
)
simpleconf_dep = declare_dependency(include_directories: ['../../../submodules/simpleconf'], link_with: simpleconf_lib)
deps += simpleconf_dep
