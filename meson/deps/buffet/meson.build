buffet_lib = library('buffet', 
    '../../../submodules/buffet/src/buffet.c',
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/buffet/src',
    ]
)

buffet_dep = declare_dependency(include_directories: [
        '../../../submodules/buffet/src',
    ], link_with: buffet_lib
)

#deps += buffet_dep
