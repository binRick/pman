uptime_lib = library('uptime', '../../../submodules/uptime/src/uptime.c', install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/uptime/include',
  ]
)
uptime_dep = declare_dependency(include_directories: ['../../../submodules/uptime'], link_with: uptime_lib)
deps += uptime_dep
