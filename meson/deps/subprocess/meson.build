subprocess_lib = library('subprocess', '../../../submodules/subprocess.h/subprocess.h', install: false, dependencies: [], 
  include_directories: [
    '../../../deps',
  ]
)
subprocess_dep = declare_dependency(include_directories: [], link_with: subprocess_lib)
deps += subprocess_dep
