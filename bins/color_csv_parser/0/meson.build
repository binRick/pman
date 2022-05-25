
bin_name = 'color_csv_parser0'

bin = {
 'name': bin_name,
 'executable': executable(
     bin_name,
     [
       './' + bin_name + '.c',
       './module/def.h',
       './module/module.h',
       './module/require.h',
     ],
     dependencies: [
        deps,
        rhash_md5_dep,
        djbhash_dep,
        list_dep,
        bestline_dep,
        case_dep,
        rgba_dep,
        commander_dep,
        trim_dep,
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

