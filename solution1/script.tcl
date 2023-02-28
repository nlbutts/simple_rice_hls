############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project simple_rice_hls
set_top compress_line
add_files simple_rice_hls/rice.cpp
add_files -tb simple_rice_hls/rice_tb.cpp
open_solution "solution1" -flow_target vivado
set_part {xc7z010iclg225-1L}
create_clock -period 10 -name default
config_export -output /home/nlbutts/projects/simple_rice_hls/output
source "./simple_rice_hls/solution1/directives.tcl"
csim_design
csynth_design
cosim_design -wave_debug -trace_level all
export_design -rtl verilog -format ip_catalog -output /home/nlbutts/projects/simple_rice_hls/output
