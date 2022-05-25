gd_dep = cc.find_library('gd', required: false)
m_dep = cc.find_library('m', required: false)
libansilove_lib = library('libansilove', 
    '../../../submodules/libansilove/src/fonts.c',
    '../../../submodules/libansilove/src/init.c',
    '../../../submodules/libansilove/src/output.c',
    '../../../submodules/libansilove/src/loadfile.c',
    '../../../submodules/libansilove/src/savefile.c',
    '../../../submodules/libansilove/src/drawchar.c',
    '../../../submodules/libansilove/src/clean.c',
    '../../../submodules/libansilove/src/loaders/ansi.c',
    '../../../submodules/libansilove/compat/reallocarray.c',
    '../../../submodules/libansilove/compat/strtonum.c',
  install: false, 
  dependencies: [gd_dep, m_dep], 
  include_directories: [
    '../../../submodules/libansilove/include',
    '../../../submodules/libansilove/src',
    '../../../submodules/libansilove/compat',
  ]
)
libansilove_dep = declare_dependency(include_directories: ['../../../submodules/libansilove/include'], link_with: libansilove_lib)
#deps += libansilove_dep
