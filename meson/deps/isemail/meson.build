isemail_lib = library('isemail', '../../../deps/is-email/is-email.c', install: false, dependencies: [], 
  include_directories: [
    '../../../deps/is-email',
  ]
)
isemail_dep = declare_dependency(include_directories: ['../../../deps/is-email'], link_with: isemail_lib)
deps += isemail_dep
