libdotenv_lib = library('libdotenv', '../../../submodules/libdotenv/dot_env.h', install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/libdotenv',
  ]
)
libdotenv_dep = declare_dependency(include_directories: ['../../../submodules/libdotenv'], link_with: libdotenv_lib)
deps += libdotenv_dep
