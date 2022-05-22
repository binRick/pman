strendswith_lib = library('strendswith', 
    '../../../submodules/str-ends-with/src/str-ends-with.c', 
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/str-ends-with/src',
    ]
)

strendswith_dep = declare_dependency(include_directories: [
        '../../../submodules/str-ends-with/src',
    ], link_with: strendswith_lib
)

deps += strendswith_dep
