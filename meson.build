project('pman',          ['c'],         version : '0.0.1',         default_options : ['warning_level=0','c_std=gnu99'])
add_project_arguments('-D_GNU_SOURCE', language : 'c')
#//***********************************************************/
deps = []
test_deps = []
srcs = []
pman_test_env = environment()
test_env = environment()
cc = meson.get_compiler('c')
#//***********************************************************/
find_deps_cmd = 'find meson/deps -type f -name meson.build|xargs dirname|sort -u'
csv = ['submodules/csv_parser/csv.c','submodules/csv_parser/split.c','submodules/csv_parser/fread_csv_line.c']
vterm = ['submodules/libvterm/src/vterm.c','submodules/libvterm/src/pen.c','submodules/libvterm/src/unicode.c',
'submodules/libvterm/src/parser.c', 'submodules/libvterm/src/screen.c', 'submodules/libvterm/src/state.c']
template = ['src/template/template.c','src/template/hashmap.c','src/template/vector.c','src/template/mpc.c','include/template/template.h','include/template/hashmap.h','include/template/vector.h','include/template/mpc.h']
#//***********************************************************/
sh = find_program('sh', required : true)
pwd_bin = find_program('pwd', required : true)
passh = find_program('passh', required : true)
#//***********************************************************/
find_deps = run_command(sh, '-c', find_deps_cmd, check: true).stdout().strip().split('\n')
pwd = run_command(pwd_bin, check: true).stdout().strip()
#//***********************************************************/
foreach m : find_deps
  subdir(m)
endforeach
#//***********************************************************/
host_system = host_machine.system()
#//***********************************************************/
cmake = import('cmake')
filesystem = import('fs')
pkg = import('pkgconfig')
#//***********************************************************/
opts = cmake.subproject_options()
opts.add_cmake_defines({'BUILD_SHARED_LIBS': false,'OLM_TESTS': false})
#//***********************************************************/
deps += dependency('threads', required : true)
vterm_dep = dependency('vterm', required : true)
#//***********************************************************/
opts.set_override_option('werror', 'false')
opts.set_override_option('warning_level', '1')
#//***********************************************************/
incdir = include_directories(
  '.',
  './include', 
  './deps', 
  './src', 
  './include/template', 
  './submodules/libvterm',
  './submodules/libvterm/include',
  './submodules/libvterm/src',
  './submodules/c_string_buffer/include',
  './submodules/c_stringfn/include',
  './submodules/c_stringfn/src',
)
install_headers([])
#/////////////////////////////////
srcs += csv
srcs += template
#//***********************************************************/
pman = executable('pman',['bins/pman.c', files(srcs)], dependencies: [deps], include_directories: [incdir])
#//***********************************************************/
test_env.set('__MESON_TEST_MODE__', '1')
test_env.set('__SH', sh.full_path())
test_env.set('TEMPLATE_PATH', pwd + '/etc/tpl/color-names')
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())
test_env.set('TEMPLATE_PATH', pwd + '/etc/tpl/color-names')
#//***********************************************************/
pman_test_env.set('__MESON_TEST_MODE__', '1')
#//***********************************************************/
bin_tests = [
  ['vterm0', executable('vterm0',['bins/vterm0.c', files(srcs), files(vterm) ], 
        dependencies: [deps, vterm_dep],
        include_directories: [incdir]
  )],
  ['field-range-parser', executable('field-range-parser',['bins/field-range-parser.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['assert0', executable('assert0',['bins/assert0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['tmt0', executable('tmt0',['bins/tmt0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['fort0', executable('fort0',['bins/fort0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['spin0', executable('spin0',['bins/spin0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['commander0', executable('commander0',['bins/commander0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['subprocess0', executable('subprocess0',['bins/subprocess0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['json0', executable('json0',['bins/json0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['terminput0', executable('terminput0',['bins/terminput0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['bestline0', executable('bestline0',['bins/bestline0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['tkvdb0', executable('tkvdb0',['bins/tkvdb0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['tkvdb1', executable('tkvdb1',['bins/tkvdb1.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['scriptexec0', executable('scriptexec0',['bins/scriptexec0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['dotenv0', executable('dotenv0',['bins/dotenv0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['regex0', executable('regex0',['bins/regex0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['conf0', executable('conf0',['bins/conf0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['wildcardcmp0', executable('wildcardcmp0',['bins/wildcardcmp0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['uptime0', executable('uptime0',['bins/uptime0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['libansilove0', executable('libansilove0',['bins/libansilove0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
  ['bat0', executable('bat0',['bins/bat0.c', files(srcs),  ], 
        dependencies: [deps],
        include_directories: [incdir]
  )],
]  
#//***********************************************************/
pman_tests = [
  ['Parse Colors', pman,  pman_test_env, ['-i', pwd + '/etc/colornames.csv', '-t', pwd + '/etc/tpl/color-names/color-names.tpl', '-c']],
]
#//***********************************************************/
foreach i : bin_tests
  test(i[0], i[1], args: ['--test'], env: test_env)
endforeach
#//***********************************************************/
foreach t : pman_tests
  test(t[0], t[1], args: t[3], env: t[2])
endforeach
#//***********************************************************/

