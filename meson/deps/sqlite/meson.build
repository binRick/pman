sqlite_lib = library('sqlite', 
    '../../../deps/sqlite/sqlite3.c',
    install: false, dependencies: [], 
    include_directories: [
        '../../../deps/sqlite',
    ]
)

sqlite_dep = declare_dependency(include_directories: [
        '../../../deps/sqlite',
    ], link_with: sqlite_lib
)

#deps += sqlite_dep
