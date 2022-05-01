scriptexec_lib = library('scriptexec', '../../../submodules/scriptexec/src/scriptexec.c', install: false, dependencies: [fsio_dep, stringbuffer_dep], 
  include_directories: [
    '../../../submodules/scriptexec/include',
  ]
)
scriptexec_dep = declare_dependency(include_directories: ['../../../submodules/scriptexec/include'], link_with: scriptexec_lib)
deps += scriptexec_dep
