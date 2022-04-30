#//***********************************************************/
project('pman',          ['c'],         version : '0.0.1',         default_options : ['warning_level=0','c_std=gnu99'])
#//***********************************************************/
#if(NOT EXISTS "target/cmake-modules/src/utils.cmake")
#  execute_process(COMMAND git clone https://github.com/sagiegurari/cmake-modules.git)
#endif()
#list(APPEND CMAKE_MODULE_PATH "./submodules/cmake-modules/src")
#include(utils)
#//***********************************************************/
add_project_arguments('-D_GNU_SOURCE', language : 'c')
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
deps = [thread_dep]
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

install_headers([
])

#//////////////////////////////////////////////
srcs = []
fort = ['src/fort.c']
tmt = ['src/tmt.c']
flag = ['deps/flag/flag.c']
commander = ['deps/commander/commander.c']
rgba = ['deps/rgba/rgba.c']
int = ['src/int.c']
str = ['deps/str-replace/str-replace.c',
  'submodules/c_string_buffer/src/stringbuffer.c',
  'deps/strsplit/strsplit.c', 'deps/is_number/is_number.c', 'submodules/c_stringfn/src/stringfn.c',
  #//  'src/utils.c',
]
fs = ['deps/fs/fs.c']
case = ['deps/case/case.c']
trim = ['deps/trim/trim.c']
timestamp = ['deps/timestamp/timestamp.c', 'src/datetime.c']
csv = ['submodules/csv_parser/csv.c','submodules/csv_parser/split.c','submodules/csv_parser/fread_csv_line.c']
occurrences = ['deps/occurrences/occurrences.c']
b64 = ['deps/b64/buffer.c','deps/b64/decode.c','deps/b64/encode.c']
vterm = ['submodules/libvterm/src/vterm.c','submodules/libvterm/src/pen.c','submodules/libvterm/src/unicode.c',
'submodules/libvterm/src/parser.c', 'submodules/libvterm/src/screen.c', 'submodules/libvterm/src/state.c']
#/////////////////////////////////
template = ['src/template/template.c','src/template/hashmap.c','src/template/vector.c','src/template/mpc.c','include/template/template.h',
'include/template/hashmap.h','include/template/vector.h','include/template/mpc.h']
#/////////////////////////////////
srcs += flag
srcs += fort
srcs += commander
srcs += fs
srcs += str
srcs += b64
srcs += occurrences
srcs += csv
srcs += trim
srcs += case
srcs += rgba
srcs += template
srcs += timestamp
srcs += int
#//***********************************************************/
pman = executable('pman',['bins/pman.c', files(srcs)], dependencies: [deps], include_directories: [incdir])
#//***********************************************************/
test_env = environment()
test_env.set('__MESON_TEST_MODE__', '1')
test_env.set('__SH', sh.full_path())
test_env.set('TEMPLATE_PATH', '../etc/tpl')
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())
#////////////////////////////////////////////////////
embedded_tests = [
  ['Parse Colors', pman],
]
foreach i : embedded_tests
test(i[0], i[1], args: [
  '-i', '/tmp/in0', '-o', '/tmp/out0', 
  '--verbose',  '--test-mode', 
  '--mode',  'read_test',
  ],env: test_env)
endforeach
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
tmt0 = executable('tmt0',['bins/tmt0.c', files(srcs), files(tmt), ], dependencies: [deps], include_directories: [incdir])
#////////////////////////////////////////////////////
commander0 = executable('commander0',['bins/commander0.c', 
      files(srcs),
     ], dependencies: [deps], include_directories: [incdir])
spin0 = executable('spin0',['bins/spin0.c', files(srcs)], dependencies: [deps],include_directories: [incdir])
_tests = [
  ['pman', pman],
]
tests = [
  ['fort0', fort0, 'fort0.log'],
  ['assert0', assert0, 'assert0.log'],
  ['spin0', spin0, 'spin0.log'],
  ['tmt0', tmt0, 'tmt0.log'],
  ['commander0', commander0, 'commander0.log'],
  ['template0', template0],
  ['vterm0', vterm0],
]
#//***********************************************************/

#//***********************************************************/
foreach i : tests
test(i[0], i[1], args: ['--test'], env: test_env)
endforeach
#//***********************************************************/


