## Generates SystemVerilog to solve variational quantum circuits on an FPGA

Running the code will generate SystemVerilog which can be compiled to run on an FPGA. The variational circuit HDL code will allow for multiple quantum circuits to be simulated on an FPGA for each compilation. Besides the HDL, the program also generates all quantum gates and rotation matrices used in the circuit that serve as input into the FPGA design.  The final state-vector of the simulated quantum circuit is output via a parallel communication protocol I wrote to communicate between the FPGA and an Arduino Uno.  I have only tested compilation of the HDL using Quartus for an Altera Cyclone V FPGA on-board a DE-10Nano development board.  

Here is a link to my accepted thesis, containing a full-write up of the methods: [Thesis Link](<https://csu-sdsu.primo.exlibrisgroup.com/permalink/01CALS_SDL/r45sar/alma991023771232502917>)

Research is done in collaboration with Dr. Calvin Johnson and the late Dr. Raymond Moberly at SDSU. There are some unused functions within variational_circuit.cpp that I hope to get running and documented soon.  

An example of the fully generated SystemVerilog code is in the 'example_hdl' folder.
