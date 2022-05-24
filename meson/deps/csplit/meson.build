csplit_lib = library('csplit', 
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/csplit'
    ]
)

csplit_dep = declare_dependency(include_directories: [
        '../../../submodules/csplit',
    ], link_with: csplit_lib
)

#deps += csplit_dep
