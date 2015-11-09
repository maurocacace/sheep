[Mesh]
  file = ic.e
[]

[Variables]
  [./temperature]
    order = FIRST
    family = LAGRANGE
	initial_from_file_var = temperature
    initial_from_file_timestep = 2
  [../]
[]

#[GlobalParams]
#  temperature = temperature
#[]

[Functions]
  [./top_bc]
	type = SheepFunctionBC
	data_file = top.dat
	format = file
	nx = 121
	ny = 110
	neumann = false
	interpol = true
  [../]
[]

[BCs]
  [./temp_top]
    type = FunctionPresetBC
    variable = temperature
    boundary = 1
	function = top_bc
  [../]
  [./temp_bottom]
    type = PresetBC
    variable = temperature
    boundary = 2
	value = 1300
  [../]  
[]

[Kernels]
  [./temp_time_deriv]
    type = GMSEnergyTimeDerivative
    variable = temperature
  [../]
  [./temp_conduction]
    type = GMSEnergyResidual
    variable = temperature
  [../]
[]

[UserObjects]
  [./prop]
    type = PropertyReadFile
    prop_file_name = prop.dat
	nprop = 4
	nx = 121
	ny = 110
	nz = 12
  [../]
[]

[Materials]
  [./EocenePres]
    type = GMSMaterial
    block = 0
	scale_factor = 2.3e+07
    density = 2350
    thermal_conductivity = 0.563
    heat_capacity = 1368
	heat_production = 0.0
	read_prop_user_object = prop
#	outputs = out
  [../]  
  [./CretPalc]
    type = GMSMaterial
    block = 1
	scale_factor = 2.3e+07
    density = 2350
    thermal_conductivity = 0.563
    heat_capacity = 1368
	heat_production = 0.0
	read_prop_user_object = prop
#	outputs = out
  [../]  
  [./JurCret]
    type = GMSMaterial
    block = 2
	scale_factor = 2.3e+07
    density = 2350
    thermal_conductivity = 0.563
    heat_capacity = 1368
	heat_production = 0.0
	read_prop_user_object = prop
#	outputs = out
  [../]  
  [./PerJur]
    type = GMSMaterial
    block = 3
	scale_factor = 2.3e+07
    density = 2350
    thermal_conductivity = 0.563
    heat_capacity = 1368
	heat_production = 0.0
	read_prop_user_object = prop
#	outputs = out
  [../]  
  [./PrePer]
    type = GMSMaterial
    block = 4
	scale_factor = 2.3e+07
    density = 2350
    thermal_conductivity = 0.563
    heat_capacity = 1368
	heat_production = 0.0
	read_prop_user_object = prop
#	outputs = out
  [../]  
  [./ContUC]
    type = GMSMaterial
    block = 5
	scale_factor = 2.3e+07
    density = 2350
    thermal_conductivity = 0.563
    heat_capacity = 1368
	heat_production = 0.0
	read_prop_user_object = prop
#	outputs = out
  [../]
  [./ContLC]
    type = GMSMaterial
    block = 6
	scale_factor = 2.3e+07
    density = 2350
    thermal_conductivity = 0.563
    heat_capacity = 1368
	heat_production = 0.0
	read_prop_user_object = prop
#	outputs = out
  [../]  
  [./ContHDB]
    type = GMSMaterial
    block = 7
	scale_factor = 2.3e+07
    density = 2350
    thermal_conductivity = 0.563
    heat_capacity = 1368
	heat_production = 0.0
	read_prop_user_object = prop
#	outputs = out
  [../] 
  [./ContGreenLandCrust]
    type = GMSMaterial
    block = 8
	scale_factor = 2.3e+07
    density = 2350
    thermal_conductivity = 0.563
    heat_capacity = 1368
	heat_production = 0.0
	read_prop_user_object = prop
#	outputs = out
  [../]
  [./OceanicCrust]
    type = GMSMaterial
    block = 9
	scale_factor = 2.3e+07
    density = 2350
    thermal_conductivity = 0.563
    heat_capacity = 1368
	heat_production = 0.0
	read_prop_user_object = prop
#	outputs = out
  [../]
  [./OceanicHDB]
    type = GMSMaterial
    block = 10
	scale_factor = 2.3e+07
    density = 2350
    thermal_conductivity = 0.563
    heat_capacity = 1368
	heat_production = 0.0
	read_prop_user_object = prop
#	outputs = out
  [../]  
  [./LithMant]
    type = GMSMaterial
    block = 11
	scale_factor = 2.3e+07
    density = 2350
    thermal_conductivity = 0.563
    heat_capacity = 1368
	heat_production = 0.0
	read_prop_user_object = prop
#	outputs = out
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
  [./SMP]
	type = SMP
    off_diag_column = 'temperature'
  [../]
[]

[Executioner]
  type = Transient
  scheme = 'crank-nicolson'
  start_time = 0.0
  end_time = 110.0
  num_steps = 2000000
  solve_type = Newton
  line_search = basic
  nl_rel_tol = 1.0e-10
  nl_abs_tol = 1.0e+00
  [./TimeStepper]
    type = ConstantDT
    dt = 0.1
 [../]
[]

[Outputs]
	file_base = thermal_transient
  print_linear_residuals = false
  print_perf_log = true
  [./out]
    type = Exodus
  [../]
[]