[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 10
  ny = 10
  nz = 10
  xmin = 0
  xmax = 100
  ymin = 0
  ymax = 100
  zmin = 0
  zmax = 100
[]

[Variables]
  [./load]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[GlobalParams]
  load = load
[]

[BCs]
  [./load_top]
    type = PresetBC
    variable = load
    boundary = front
    value = 0
  [../]
[]

[Kernels]
  [./static_load]
    type = StaticLoad
    variable = load
  [../]
[]

[Materials]
  [./sheep]
    type = SheepMaterial
    block = 0
    bulk_density = 2350
  [../]
[]

[Preconditioning]
  [./precond]
    type = SMP
    full = true
    petsc_options = '-snes_ksp_ew'
    petsc_options_iname = '-ksp_type -pc_type -snes_atol -snes_rtol -snes_max_it -ksp_max_it -sub_pc_type -sub_pc_factor_shift_type'
    petsc_options_value = 'gmres asm 1E-10 1E-10 200 500 lu NONZERO'
  [../]
[]

[Executioner]
  type = Steady
  solve_type = Newton
[]

[Outputs]
  output_initial = true
  print_linear_residuals = true
  print_perf_log = true
  [./out]
    type = Exodus
  [../]
[]