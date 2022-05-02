rhash_md5_lib = library('rhash_md5', '../../../deps/rhash_md5/md5.c', install: false, dependencies: [], 
  include_directories: [
    '../../../deps/rhash_md5',
  ]
)
rhash_md5_dep = declare_dependency(include_directories: ['../../../deps/rhash_md5'], link_with: rhash_md5_lib)
deps += rhash_md5_dep
