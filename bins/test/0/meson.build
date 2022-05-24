
bin_name = 'test0'

bin = {
 'name': bin_name,
 'executable': executable(
     bin_name,
     [
       './' + bin_name + '.c',
     ],
     dependencies: [
        deps,
        case_dep,
     ],
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

