kat_lib = library('kat', 
    '../../../submodules/kat/highlight.c',
    '../../../submodules/kat/hashtable.c',
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/kat',
        '../../../submodules/kat/include',
    ]
)

kat_dep = declare_dependency(include_directories: [
        '../../../submodules/kat',
        '../../../submodules/kat/include',
    ], link_with: kat_lib
)

#deps += kat_dep
