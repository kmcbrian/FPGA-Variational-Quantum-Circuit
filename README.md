## Generates SystemVerilog to solve variational quantum circuits on an FPGA

Running the code will generate SystemVerilog that can be compiled to run on an FPGA. The variational circuit HDL code will allow for multiple quantum circuits to be similated on a FPGA for each compilation. Besides the HDL, the program also generates all quantum gates and rotation matrices used in the circuit that serves as input into the FPGA design.  The final state-vector of the simulated quantum circuit is output via a parallel communication protocol I wrote to communicate between the FPGA and an Arduino Uno.  I have only tested compilation of the HDL using Quartus for an Altera Cyclone V FPGA on-board a DE-10Nano development board.  

A thorough write-up of all the derivations of quantum circuits and formulas will be published in my Masters thesis upon acceptance.  Research is done in collaboration with Dr Calvin Johnson and the late Dr Raymond Moberly at SDSU.  The example circuit currently in main.cpp will be replaced with the circuits used in my research upon publication too.  There are some unused functions within variational_circuit.cpp that I hope to get running and documented soon.  

An example of the full generated SystemVerilog code is in the 'example_hdl' folder.
