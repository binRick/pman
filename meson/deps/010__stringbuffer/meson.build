stringbuffer_lib = library('str_replace', '../../../submodules/c_string_buffer/src/stringbuffer.c', install: false, 
  dependencies: [occurrences_dep], 
  include_directories: [
    '../../../submodules/c_fsio/include',
    '../../../submodules/c_string_buffer/include',
  ]
)
stringbuffer_dep = declare_dependency(include_directories: 
  [
    '../../../submodules/c_string_buffer/include',
    '../../../submodules/c_fsio/include',
    ], 
  link_with: stringbuffer_lib)
deps += stringbuffer_dep
