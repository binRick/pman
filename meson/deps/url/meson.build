url_lib = library('url', 
  '../../../deps/url/url.c',
  install: false, 
  dependencies: [], 
  include_directories: [
    '../../../deps/url',
  ]
)

url_dep = declare_dependency(include_directories: [
        '../../../deps/url',
    ], 
    link_with: url_lib
)

deps += url_dep
