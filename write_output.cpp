#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;


void write_output(int psi_f_length, int N, int n_qb){
// int n_qb:   number of qubits in circuit
// int N:      bit length of numbers. Multiple of 8 required

	//const int NUM_VAL = 2 * pow(2, n_qb); //number of real numbers
	const int NUM_BYTES = static_cast<int>(N/8);
    const int NUM_OUT = psi_f_length * NUM_BYTES; //number of output cycles
	string filename = "output_" + to_string(n_qb) + "qb.sv";

	// check if file already exists
    ifstream f(filename);
    // if you can open an ifstream to the file
    // it exists already
    if (f.good()){
        cout << filename << " file already exists" << endl;
        return;
    }

    // add filename to file for easy deletion
    ofstream generate_file;
    generate_file.open("generated_files.txt", ofstream::app);
    generate_file << filename << endl;
    generate_file.close();

	ofstream verilog;
        verilog.open(filename);
        verilog << "// Output module generated using c++" << endl;
        verilog << "// sends final state-vector to arduino" << endl;

	// module heading
        verilog << "module output_" << n_qb << "qb #(" << endl;
        verilog << "parameter N = " << N << "\n)\n("  << endl;

	// module input/outputs
	verilog << "input [N-1:0] psi_f [0:" << psi_f_length-1 << "]," << endl;
    verilog << "input wire i_clock,"    << endl;
    verilog << "input wire listener_flag," << endl;
	verilog << "output wire[7:0] out,"  << endl;
    verilog << "output wire parity\n);" << endl << endl;

	// variable initialization
	verilog << "// used for iterating through output" << endl;
    verilog << "integer n_num = " << NUM_OUT << ";" << endl;
	verilog << "integer i_num = 0;" << endl;

	verilog << "reg [7:0] out_reg; // for assigning numbers in always block" << endl;
	verilog << "assign out[7:0] = out_reg[7:0];" << endl;
	verilog << "reg parity_reg;" << endl;
	verilog << "assign parity = parity_reg;" << endl;

	// initialization block
	verilog << endl << "// intialization of values" << endl;
	verilog << "initial begin" << endl;
	//verilog << "    source_flag_reg <= 1'b0;" << endl;
	verilog << "    out_reg <= 8'b10001011;" << endl;
	verilog << "    parity_reg <= 1'b0;" << endl;
	verilog << "end" << endl;

	// first always block for sending ready signal to arduino
	/*
	verilog << "\n\n// at the end of the calculation" << endl;
	verilog << "always @ (psi_f[" << NUM_VAL-1 <<"])" << endl;
	verilog << "begin" << endl;
	verilog << "    source_flag_reg <= 1'b1;" << endl;
	verilog << "end" << endl;
*/
	// second always block, assigning pins at arduinos signal
	verilog << "\n\n// transfer data to arduino" << endl;
        verilog << "always @ (posedge listener_flag)" << endl;
        verilog << "begin" << endl;

	verilog << "    case(i_num)" << endl;
	for(int i = 0;i<psi_f_length;i++)
	{
	    for(int j = NUM_BYTES-1;j>=0;j--)
	    {
	        verilog << "    "<< (NUM_BYTES*i) - j + NUM_BYTES -1 << ": begin" << endl;
	        verilog << "         out_reg[7:0] <= psi_f[" << i << "][" << (8*j)+7 << ":" << 8*j << "];" << endl;
	        verilog << "         parity_reg <= ^psi_f["  << i << "][" << (8*j)+7 << ":" << 8*j << "];" << endl;
	        verilog << "       end" << endl;
	    }
	}
    verilog << "    default: out_reg[7:0] <= 8'b00000000;" << endl;
	verilog << "    endcase" << endl;
	verilog << "    i_num = i_num + 1;" << endl;

	verilog << "end" << endl;
	verilog << "endmodule";

}

