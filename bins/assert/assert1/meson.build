assert1_bin = {
 'name': 'assert1',
 'executable': executable('assert1',
     [
       './assert1.c',
     ],
     dependencies: [deps],
     include_directories: [
       '../../../',
     ],
   )
}


test(assert1_bin['name'], 
  assert1_bin['executable'], 
  args: ['--test'], 
  env: test_env,
)

