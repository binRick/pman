expandbraces_lib = library('expandbraces', 
    '../../../submodules/expand-braces/expand-braces.c',
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/expand-braces',
    ]
)

expandbraces_dep = declare_dependency(include_directories: [
        '../../../submodules/expand-braces',
    ], link_with: expandbraces_lib
)

#deps += expandbraces_dep
