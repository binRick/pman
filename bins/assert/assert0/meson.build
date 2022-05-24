assert0_bin = {
 'name': 'assert0',
 'executable': executable('assert0',
     [
       './assert0.c',
     ],
     dependencies: [deps],
     include_directories: [
       '../../../',
     ],
   )
}


test(assert0_bin['name'], 
  assert0_bin['executable'], 
  args: ['--test'], 
  env: test_env,
)

