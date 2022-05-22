stricks_lib = library('stricks', 
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/stricks/src',
    ]
)

stricks_dep = declare_dependency(include_directories: [
        '../../../submodules/stricks/src',
    ], link_with: stricks_lib
)

deps += stricks_dep
