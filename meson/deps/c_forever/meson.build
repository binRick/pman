c_forever_lib = library('c_forever', 
    '../../../submodules/c_forever/src/forever.c',
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/c_forever/include',
    ]
)

c_forever_dep = declare_dependency(include_directories: [
        '../../../submodules/c_forever/include',
    ], link_with: c_forever_lib
)

deps += c_forever_dep
