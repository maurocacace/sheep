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
  [./temperature]
    order = FIRST
    family = LAGRANGE
    initial_condition = 40
  [../]
[]

[GlobalParams]
  temperature = temperature
[]

[BCs]
  [./temp_left]
    type = DirichletBC
    variable = temperature
    boundary = front
    value = 40
  [../]
  [./temp_right]
    type = DirichletBC
    variable = temperature
    boundary = back
    value = 80
  [../]
[]

[Kernels]
  [./temp_time_deriv]
    type = ThermoTimeDerivative
    variable = temperature
  [../]
  [./temp_conduction]
    type = ThermalConduction
    variable = temperature
  [../]
[]

[Materials]
  [./sheep]
    type = SheepMaterial
    block = 0
    bulk_thermal_conductivity = 2.7
    bulk_density = 2350
    bulk_heat_capacity = 1368
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
  type = Transient
  solve_type = Newton
  start_time = 0.0
  end_time = 5.0e+9
  line_search = 'none'
  [./TimeStepper]
    type = ConstantDT
    dt = 5.0e+08
  [../]
[]

[Outputs]
  output_initial = true
  print_linear_residuals = true
  print_perf_log = true
  [./out]
    type = Exodus
  [../]
[]