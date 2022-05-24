tiny_regex_c_lib = library('tiny_regex_c', '../../../submodules/tiny-regex-c/re.c', install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/tiny-regex-c',
  ]
)
tiny_regex_c_dep = declare_dependency(include_directories: ['../../../submodules/tiny-regex-c'], link_with: tiny_regex_c_lib)
#deps += tiny_regex_c_dep
