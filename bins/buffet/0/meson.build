
bin_name = 'buffet0'

bin = {
 'name': bin_name,
 'executable': executable(
     bin_name,
     [
       './' + bin_name + '.c',
     ],
     dependencies: [
        deps,
        buffet_dep,
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

