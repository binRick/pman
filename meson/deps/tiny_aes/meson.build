tiny_aes_lib = library('tiny_aes', '../../../submodules/tiny-AES-c/aes.c', install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/tiny-AES-c',
  ]
)
tiny_aes_dep = declare_dependency(include_directories: ['../../../submodules/tiny-AES-c'], link_with: tiny_aes_lib)
deps += tiny_aes_dep
