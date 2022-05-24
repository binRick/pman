bin = {
 'name': 'json0',
 'executable': executable('json0',
     [
       './json0.c',
     ],
     dependencies: [deps],
     include_directories: [
       '../../../',
     ],
   )
}


test(bin['name'], 
  bin['executable'], 
  args: ['--test'], 
  env: test_env,
)

