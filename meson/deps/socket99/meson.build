socket99_lib = library('socket99', 
    '../../../submodules/socket99/socket99.c',
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/socket99',
    ]
)

socket99_dep = declare_dependency(include_directories: [
        '../../../submodules/socket99',
    ], link_with: socket99_lib
)

deps += socket99_dep
