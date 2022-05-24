tempdir_lib = library('tempdir', 
  '../../../deps/tempdir/tempdir.c', 
  install: false, dependencies: [], 
  include_directories: [
    '../../../deps',
    '../../../deps/tempdir',
  ]
)

tempdir_dep = declare_dependency(include_directories: [
    '../../../deps',
    '../../../deps/tempdir',
], link_with: tempdir_lib)

#deps += tempdir_dep
