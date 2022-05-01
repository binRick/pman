project('pman',          ['c'],         version : '0.0.1',         default_options : ['warning_level=0','c_std=gnu99'])
add_project_arguments('-D_GNU_SOURCE', language : 'c')
deps = []
#//***********************************************************/
pwd = run_command('pwd', check: true).stdout().strip()
find_deps_cmd = 'find meson/deps -type f -name meson.build|xargs dirname'
find_deps = run_command('env', 'bash', '-c', find_deps_cmd, check: true).stdout().strip().split('\n')
foreach m : find_deps
  subdir(m)
endforeach
#//***********************************************************/
cmake = import('cmake')
filesystem = import('fs')
pkg = import('pkgconfig')
#//***********************************************************/
opts = cmake.subproject_options()
opts.add_cmake_defines({'BUILD_SHARED_LIBS': false,'OLM_TESTS': false})
#//opts.add_cmake_defines({'CMAKE_C_FLAGS':  '-O3 -std=gnu99 -Wall -fPIC -fno-plt -lm -lshmc'})
#//add_global_arguments('-lm',language : 'c',)
#//***********************************************************/
thread_dep = dependency('threads')
vterm_dep = dependency('vterm')
opts.set_override_option('werror', 'false')
opts.set_override_option('warning_level', '0')
host_system = host_machine.system()
z_dep = dependency('zlib', required : true)
cc = meson.get_compiler('c')
#//***********************************************************/
sh = find_program('sh', required : true)
passh = find_program('passh', required : true)
#//***********************************************************/
#//***********************************************************/
test_deps = []
#//***********************************************************/
#c = run_command('./scripts/submodule-cmds.sh', check: true)
#xxxxxxxxx = c.stdout().strip().split('\n')
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

#//////////////////////////////////////////////
srcs = []
csv = ['submodules/csv_parser/csv.c','submodules/csv_parser/split.c','submodules/csv_parser/fread_csv_line.c']
vterm = ['submodules/libvterm/src/vterm.c','submodules/libvterm/src/pen.c','submodules/libvterm/src/unicode.c',
'submodules/libvterm/src/parser.c', 'submodules/libvterm/src/screen.c', 'submodules/libvterm/src/state.c']
#/////////////////////////////////
template = ['src/template/template.c','src/template/hashmap.c','src/template/vector.c','src/template/mpc.c','include/template/template.h','include/template/hashmap.h','include/template/vector.h','include/template/mpc.h']
#/////////////////////////////////
srcs += csv
srcs += template
#//***********************************************************/
pman = executable('pman',['bins/pman.c', files(srcs)], dependencies: [deps], include_directories: [incdir])
#//***********************************************************/
test_env = environment()
test_env.set('__MESON_TEST_MODE__', '1')
test_env.set('__SH', sh.full_path())
test_env.set('TEMPLATE_PATH', pwd + '/etc/tpl/color-names')
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())
#//***********************************************************/
template0 = executable('template0',
     ['bins/template0.c', files(template),  ], 
     dependencies: [deps],
     include_directories: [incdir])
assert0 = executable('assert0',['bins/assert0.c', files(srcs),
     ], dependencies: [deps],
     include_directories: [incdir])
#////////////////////////////////////////////////////
vterm0 = executable('vterm0',['bins/vterm0.c', files(srcs), files(vterm),
     ], dependencies: [deps, vterm_dep],
     include_directories: [incdir])
#////////////////////////////////////////////////////
fort0 = executable('fort0',['bins/fort0.c', files(srcs),
     ], dependencies: [deps],
     include_directories: [incdir])
#////////////////////////////////////////////////////
tmt0 = executable('tmt0',['bins/tmt0.c', files(srcs), ], dependencies: [deps], include_directories: [incdir])
#////////////////////////////////////////////////////
commander0 = executable('commander0',['bins/commander0.c', 
      files(srcs),
     ], dependencies: [deps], include_directories: [incdir])
spin0 = executable('spin0',['bins/spin0.c', files(srcs)], dependencies: [deps],include_directories: [incdir])
#//***********************************************************/
#_tests = [
#  ['pman', pman],
#]
#__tests = [
#  ['fort0', fort0, 'fort0.log'],
#  ['assert0', assert0, 'assert0.log'],
#  ['spin0', spin0, 'spin0.log'],
#  ['tmt0', tmt0, 'tmt0.log'],
#  ['commander0', commander0, 'commander0.log'],
#  #  ['template0', template0],
#  ['vterm0', vterm0],
#]
#//***********************************************************/


#////////////////////////////////////////////////////
pman_test_env = environment()
pman_test_env.set('__MESON_TEST_MODE__', '1')
test_env.set('TEMPLATE_PATH', pwd + '/etc/tpl/color-names')
#[
#  '-i', 'etc/colornames.csv', '-t', 'etc/tpl/color-names/color-names.tpl', '-o', '/tmp/out0', 
#  '--test-mode', 
#  '--mode',  'read_test',
#  ],env: test_env)
#endforeach
#//***********************************************************/
field_range_parser = executable('field-range-parser',
     ['bins/field-range-parser.c', files(srcs),  ], 
     dependencies: [deps],
     include_directories: [incdir])
#//***********************************************************/
bin_tests = [
  ['field-range-parser', field_range_parser],
]
#//***********************************************************/
foreach i : bin_tests
  test(i[0], i[1], args: ['--test'], env: test_env)
endforeach
#//***********************************************************/
pman_tests = [
  ['Spinner #0', spin0,  test_env, []],
  ['Parse Colors', pman,  pman_test_env, ['-i', pwd + '/etc/colornames.csv', '-t', pwd + '/etc/tpl/color-names/color-names.tpl', '-c']],
    #  ['Parse 10 Colors', pman,  pman_test_env, ['-i', pwd + '/etc/colornames-10.csv', '-t', pwd + '/etc/tpl/color-names/color-names.tpl', '-c', '-v'],
    #],
    #['Parse Color Names', pman,  pman_test_env,
    # ['-v', '-c', '-t'], #'-i', pwd + '/etc/colornames.csv', '-t', pwd + '/etc/tpl/color-names/color-names.tpl', '-r', '--parse-color-names'],
    #],
]
#//***********************************************************/
foreach t : pman_tests
  test(t[0], t[1], args: t[3], env: t[2])
endforeach
#//***********************************************************/

