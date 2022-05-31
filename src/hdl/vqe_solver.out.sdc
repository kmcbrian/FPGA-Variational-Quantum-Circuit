## Generated SDC file "vqe_solver.sdc"

## Copyright (C) 2020  Intel Corporation. All rights reserved.
## Your use of Intel Corporation's design tools, logic functions 
## and other software and tools, and any partner logic 
## functions, and any output files from any of the foregoing 
## (including device programming or simulation files), and any 
## associated documentation or information are expressly subject 
## to the terms and conditions of the Intel Program License 
## Subscription Agreement, the Intel Quartus Prime License Agreement,
## the Intel FPGA IP License Agreement, or other applicable license
## agreement, including, without limitation, that your use is for
## the sole purpose of programming logic devices manufactured by
## Intel and sold by Intel or its authorized distributors.  Please
## refer to the applicable agreement for further details, at
## https://fpgasoftware.intel.com/eula.


## VENDOR  "Altera"
## PROGRAM "Quartus Prime"
## VERSION "Version 20.1.0 Build 711 06/05/2020 SJ Lite Edition"

## DATE    "Sun Oct  3 15:40:14 2021"

##
## DEVICE  "5CSEBA6U23I7"
##


#**************************************************************
# Time Information
#**************************************************************

set_time_format -unit ns -decimal_places 3



#**************************************************************
# Create Clock
#**************************************************************

create_clock -name {fpga_clock} -period 20.000 -waveform { 0.000 0.500 } [get_ports {fpga_clock}]
create_clock -name {clock_divider:clk|count[22]} -period 20.000 -waveform { 0.000 0.500 } [get_registers {clock_divider:clk|count[22]}]
create_clock -name {listener_flag} -period 20.000 -waveform { 0.000 0.500 } [get_ports {listener_flag}]


#**************************************************************
# Create Generated Clock
#**************************************************************



#**************************************************************
# Set Clock Latency
#**************************************************************



#**************************************************************
# Set Clock Uncertainty
#**************************************************************

set_clock_uncertainty -rise_from [get_clocks {listener_flag}] -rise_to [get_clocks {listener_flag}] -setup 0.170  
set_clock_uncertainty -rise_from [get_clocks {listener_flag}] -rise_to [get_clocks {listener_flag}] -hold 0.060  
set_clock_uncertainty -rise_from [get_clocks {listener_flag}] -fall_to [get_clocks {listener_flag}] -setup 0.170  
set_clock_uncertainty -rise_from [get_clocks {listener_flag}] -fall_to [get_clocks {listener_flag}] -hold 0.060  
set_clock_uncertainty -fall_from [get_clocks {listener_flag}] -rise_to [get_clocks {listener_flag}] -setup 0.170  
set_clock_uncertainty -fall_from [get_clocks {listener_flag}] -rise_to [get_clocks {listener_flag}] -hold 0.060  
set_clock_uncertainty -fall_from [get_clocks {listener_flag}] -fall_to [get_clocks {listener_flag}] -setup 0.170  
set_clock_uncertainty -fall_from [get_clocks {listener_flag}] -fall_to [get_clocks {listener_flag}] -hold 0.060  
set_clock_uncertainty -rise_from [get_clocks {clock_divider:clk|count[22]}] -rise_to [get_clocks {listener_flag}] -setup 0.280  
set_clock_uncertainty -rise_from [get_clocks {clock_divider:clk|count[22]}] -rise_to [get_clocks {listener_flag}] -hold 0.270  
set_clock_uncertainty -rise_from [get_clocks {clock_divider:clk|count[22]}] -fall_to [get_clocks {listener_flag}] -setup 0.280  
set_clock_uncertainty -rise_from [get_clocks {clock_divider:clk|count[22]}] -fall_to [get_clocks {listener_flag}] -hold 0.270  
set_clock_uncertainty -rise_from [get_clocks {clock_divider:clk|count[22]}] -rise_to [get_clocks {clock_divider:clk|count[22]}]  0.380  
set_clock_uncertainty -rise_from [get_clocks {clock_divider:clk|count[22]}] -fall_to [get_clocks {clock_divider:clk|count[22]}]  0.380  
set_clock_uncertainty -rise_from [get_clocks {clock_divider:clk|count[22]}] -rise_to [get_clocks {fpga_clock}]  0.350  
set_clock_uncertainty -rise_from [get_clocks {clock_divider:clk|count[22]}] -fall_to [get_clocks {fpga_clock}]  0.350  
set_clock_uncertainty -fall_from [get_clocks {clock_divider:clk|count[22]}] -rise_to [get_clocks {listener_flag}] -setup 0.280  
set_clock_uncertainty -fall_from [get_clocks {clock_divider:clk|count[22]}] -rise_to [get_clocks {listener_flag}] -hold 0.270  
set_clock_uncertainty -fall_from [get_clocks {clock_divider:clk|count[22]}] -fall_to [get_clocks {listener_flag}] -setup 0.280  
set_clock_uncertainty -fall_from [get_clocks {clock_divider:clk|count[22]}] -fall_to [get_clocks {listener_flag}] -hold 0.270  
set_clock_uncertainty -fall_from [get_clocks {clock_divider:clk|count[22]}] -rise_to [get_clocks {clock_divider:clk|count[22]}]  0.380  
set_clock_uncertainty -fall_from [get_clocks {clock_divider:clk|count[22]}] -fall_to [get_clocks {clock_divider:clk|count[22]}]  0.380  
set_clock_uncertainty -fall_from [get_clocks {clock_divider:clk|count[22]}] -rise_to [get_clocks {fpga_clock}]  0.350  
set_clock_uncertainty -fall_from [get_clocks {clock_divider:clk|count[22]}] -fall_to [get_clocks {fpga_clock}]  0.350  
set_clock_uncertainty -rise_from [get_clocks {fpga_clock}] -rise_to [get_clocks {clock_divider:clk|count[22]}]  0.350  
set_clock_uncertainty -rise_from [get_clocks {fpga_clock}] -fall_to [get_clocks {clock_divider:clk|count[22]}]  0.350  
set_clock_uncertainty -rise_from [get_clocks {fpga_clock}] -rise_to [get_clocks {fpga_clock}] -setup 0.310  
set_clock_uncertainty -rise_from [get_clocks {fpga_clock}] -rise_to [get_clocks {fpga_clock}] -hold 0.270  
set_clock_uncertainty -rise_from [get_clocks {fpga_clock}] -fall_to [get_clocks {fpga_clock}] -setup 0.310  
set_clock_uncertainty -rise_from [get_clocks {fpga_clock}] -fall_to [get_clocks {fpga_clock}] -hold 0.270  
set_clock_uncertainty -fall_from [get_clocks {fpga_clock}] -rise_to [get_clocks {clock_divider:clk|count[22]}]  0.350  
set_clock_uncertainty -fall_from [get_clocks {fpga_clock}] -fall_to [get_clocks {clock_divider:clk|count[22]}]  0.350  
set_clock_uncertainty -fall_from [get_clocks {fpga_clock}] -rise_to [get_clocks {fpga_clock}] -setup 0.310  
set_clock_uncertainty -fall_from [get_clocks {fpga_clock}] -rise_to [get_clocks {fpga_clock}] -hold 0.270  
set_clock_uncertainty -fall_from [get_clocks {fpga_clock}] -fall_to [get_clocks {fpga_clock}] -setup 0.310  
set_clock_uncertainty -fall_from [get_clocks {fpga_clock}] -fall_to [get_clocks {fpga_clock}] -hold 0.270  


#**************************************************************
# Set Input Delay
#**************************************************************



#**************************************************************
# Set Output Delay
#**************************************************************



#**************************************************************
# Set Clock Groups
#**************************************************************



#**************************************************************
# Set False Path
#**************************************************************



#**************************************************************
# Set Multicycle Path
#**************************************************************



#**************************************************************
# Set Maximum Delay
#**************************************************************



#**************************************************************
# Set Minimum Delay
#**************************************************************



#**************************************************************
# Set Input Transition
#**************************************************************

