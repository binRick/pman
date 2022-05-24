models_inc = include_directories(
  '../../../submodules/colorin/include',
  '../../../submodules/colorin/util/models/include',
  '../../../submodules/colorin/util/args/include',
)

models_lib = library('models',                                                                                   
  '../../../submodules/colorin/util/models/src/models.c',
  install: false,
  dependencies: [m_dep],
  include_directories: [models_inc, inc]
) 

models_dep = declare_dependency(
  include_directories: [models_inc], 
  link_with: [models_lib],
)

#executable('colorin', 
#  '../../../submodules/colorin/src/colorin.c',
#  install: false, 
#  dependencies: [models_dep], 
#  include_directories: [models_inc],
#)
