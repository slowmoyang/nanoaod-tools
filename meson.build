project(
  'nanoaod_tools',
  'cpp',
  license: 'MIT',
  version: '1.0.0',
)

# root
root_config = find_program('root-config', required: true)
root_compile_args = run_command(root_config, '--cflags', check: true).stdout().strip().split(' ')
root_link_args = run_command(root_config, '--ldflags', '--libs', check: true).stdout().strip().split(' ')
root_incdir = run_command(root_config, '--incdir', check: true).stdout().strip().split(' ')
root_dep = declare_dependency(
    compile_args: root_compile_args,
    link_args: root_link_args,
    include_directories: root_incdir
)

# correctionlib
correction = find_program('correction', required: true)
correctionlib_compile_args = run_command(correction, 'config', '--cflags', check: true).stdout().strip().split(' ')
correctionlib_link_args = run_command(correction, 'config', '--ldflags', '--rpath', check: true).stdout().strip().split(' ')
correctionlib_incdir = run_command(correction, 'config', '--incdir', check: true).stdout().strip().split(' ')
correctionlib_dep = declare_dependency(
  compile_args: correctionlib_compile_args,
  link_args: correctionlib_link_args,
  include_directories: correctionlib_incdir
)

sources = [
  'src/btagging.cc',
  'src/correction_tools.cc',
  'src/jet_energy_scale.cc',
  'src/jet_energy_resolution.cc',
  'src/lumi_mask.cc',
  'src/mc_truth_helper.cc',
  'src/logical_file_name.cc',
]

nanoaod_tools_dep = declare_dependency(
  include_directories: include_directories('include'),
  sources: sources,
  dependencies: [
    root_dep,
    correctionlib_dep,
  ]
)

meson.override_dependency(meson.project_name(), nanoaod_tools_dep)
