[Mesh]
  file = peter.e
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
    boundary = 1
    value = 0
  [../]
[]

[Kernels]
  [./static_load]
    type = GMSMassResidual
    variable = load
  [../]
[]
[UserObjects]
  [./prop]
    type = PropertyReadFile
    prop_file_name = prop.dat
	nprop = 4
	nx = 121
	ny = 110
	nz = 13
  [../]
[]

[Materials]

  [./water]
    type = GMSMaterial
    block = 0
    density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]
  
  [./EocenePres]
    type = GMSMaterial
    block = 1
	density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]
  
  [./CretPalc]
    type = GMSMaterial
    block = 2
	density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]
  
  [./JurCret]
    type = GMSMaterial
    block = 3
	density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]
  
  [./PerJur]
    type = GMSMaterial
    block = 4
	density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]
  
  [./PrePer]
    type = GMSMaterial
    block = 5
	density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]
  
  [./ContUC]
    type = GMSMaterial
    block = 6
	density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]

  [./ContLC]
    type = GMSMaterial
    block = 7
	density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]
  
  [./ContHDB]
    type = GMSMaterial
    block = 8
	density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]  

  [./ContGreenLandCrust]
    type = GMSMaterial
    block = 9
	density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]

  [./OceanicCrust]
    type = GMSMaterial
    block = 10
	density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]

  [./OceanicHDB]
    type = GMSMaterial
    block = 11
	density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]
  
  [./LithMant]
    type = GMSMaterial
    block = 12
	density = 2350
	read_prop_user_object = prop
	outputs = out
  [../]  
  
[]

[Preconditioning]
  active = 'hypre'
  [./hypre]
    type = SMP
    full = true
    petsc_options = '-snes_ksp_ew'
    petsc_options_iname = '-pc_type -pc_hypre_type -snes_linesearch_type -ksp_gmres_restart'
    petsc_options_value = 'hypre boomeramg cp 201'
  [../]
  [./asm_ilu]
    type = SMP
    full = true
    petsc_options = '-snes_ksp_ew'
    petsc_options_iname = '-ksp_type -pc_type -snes_atol -snes_rtol -snes_max_it -ksp_max_it -sub_pc_type'
    petsc_options_value = 'gmres asm 1E-06 1E-08 100 200 ilu'
  [../]
  [./bjacobi_ilu]
    type = SMP
    full = true
    petsc_options = '-snes_ksp_ew'
    petsc_options_iname = '-ksp_type -pc_type -snes_atol -snes_rtol -snes_max_it -ksp_max_it -sub_pc_type -ksp_gmres_restart'
    petsc_options_value = 'gmres bjacobi 1E+00 1E-08 200 400 ilu 201'
  [../]
  [./asm_lu]
    type = SMP
    full = true
    petsc_options = '-snes_ksp_ew'
    petsc_options_iname = '-ksp_type -pc_type -snes_atol -snes_rtol -snes_max_it -ksp_max_it -sub_pc_type -sub_pc_factor_shift_type'
    petsc_options_value = 'gmres asm 1E-08 1E-12 50 100 lu NONZERO'
  [../]
[]

[Executioner]
  type = Steady
  solve_type = Newton
[]

[Outputs]
  file_base = static_load
  print_linear_residuals = true
  print_perf_log = true
  [./out]
    type = Exodus
  [../]
[]