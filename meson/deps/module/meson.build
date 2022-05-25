module_lib = library('module', 
  '../../../deps/clibs/module/def.h',
  '../../../deps/clibs/module/module.h',
  '../../../deps/clibs/module/require.h',
  install: false, 
  dependencies: [], 
  include_directories: [
    '../../../deps/clibs/module',
  ]
)

module_dep = declare_dependency(include_directories: [
        '../../../deps/clibs/module',
    ], 
    link_with: module_lib
)

deps += module_dep
