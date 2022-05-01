str_replace_lib = library('str_replace', '../../../submodules/c_string_buffer/src/stringbuffer.c', install: false, 
  dependencies: [occurrences_dep], 
  include_directories: [
    '../../../submodules/c_string_buffer/include',
  ]
)
str_replace_dep = declare_dependency(include_directories: [], link_with: str_replace_lib)
deps += str_replace_dep
