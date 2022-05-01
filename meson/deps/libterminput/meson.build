libterminput_lib = library('libterminput', '../../../submodules/libterminput/libterminput.c', install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/libterminput',
  ]
)
libterminput_dep = declare_dependency(include_directories: [], link_with: libterminput_lib)
deps += libterminput_dep
