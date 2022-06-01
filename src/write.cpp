#ifndef WRITE_CPP
#define WRITE_CPP

#include "binary.h"
#include "write.h"
#include "gate.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void write_matmul(int num_qubits, int N){
// int num_qubits: used for determining dimensionality
// int N:          bit length of the numbers being multiplied

	const int D = pow(2,num_qubits); // matrix: DxD; vector: Dx1
	string filename = "hdl/matmul_" + to_string(num_qubits) + "qb.sv";

	// check if file already exists
        ifstream f(filename);
        // if you can open an ifstream to the file
        // it exists already
        if (f.good()){
            cout << "Matmul already exists" << endl;
            return;
        }

    string local_file = "matmul_" + to_string(num_qubits) + "qb.sv";
    // add filename to file for easy deletion
    ofstream generate_file;
    generate_file.open("hdl/generated_files.txt", ofstream::app);
    generate_file << local_file << endl;
    generate_file.close();

	ofstream verilog;
	verilog.open(filename);
	verilog << "// matmul module generated using c++" << endl;
	verilog << "// multiplies a matrix and a vector to" << endl;
	verilog << "// output a  vector" << endl;

	// module heading
	verilog << "module matmul_" << num_qubits << "qb #(" << endl;
	verilog << "parameter N = " << N << ","  << endl;
	verilog << "parameter D = " << D << "\n)\n("  << endl;

	// module input/outputs
	verilog << "input [N-1:0] matrix [0:D**2 *2 -1],"  << endl;
	verilog << "input [N-1:0] i_vector [0:D*2 -1],"  << endl;
	verilog << "output [N-1:0] o_vector [0:D*2 -1]\n);"  << endl;

	// variable initialization
	verilog << "wire [N-1:0] re_toadd[0:D**2-1];" << endl;
	verilog << "wire [N-1:0] im_toadd[0:D**2-1];" << endl;
	verilog << "wire ovr[0:D**2-1];"  << endl;

	if(D != 2)
	{
		verilog << "wire [N-1:0] re_sums[0:D**2-D];"  << endl;
		verilog << "wire [N-1:0] im_sums[0:D**2-D];"  << endl;
	}
	verilog << "\n// Multiply corresponding complex numbers" << endl;
	// complex multiplication
	for(int i=0;i<pow(D,2); i++)
	{
		verilog << "\ncomplex_mult #(N) ele_" << i << "(\n";
		verilog <<  ".a(matrix[" <<  i*2 <<  "]),\n";
		verilog <<  ".b(matrix[" <<  (i*2)+1 << "]),\n";
		verilog << ".c(i_vector[" << (i*2)%(D*2) << "]),\n";
		//verilog << ".d(i_vector[" << ((i*2)+1)%static_cast<int>(pow(D,2)) << "]),\n";
		verilog << ".d(i_vector[" << ((i*2)+1)%(D*2) << "]),\n";
		verilog <<  ".re(re_toadd[" << i << "]),\n";
		verilog <<  ".im(im_toadd[" << i << "]),\n";
		verilog <<  ".ovr(ovr[" << i << "])\n";
		verilog <<  ");\n";
	}

	verilog << "\n// Add complex products to find output vector" << endl;
	if(D == 2)
	{
		for(int j=0;j<2;j++)
		{
			verilog << "qadd #(N-1,N) re_sum_v" << j << " ("  << endl;
			verilog <<  ".a(re_toadd[" << 2*j    << "]),\n";
                	verilog <<  ".b(re_toadd[" << 2*j +1 << "]),\n";
			verilog <<  ".c(o_vector[" << 2*j    << "])\n";
			verilog <<  ");\n";

			verilog << "qadd #(N-1,N) im_sum_v" << j << " ("  << endl;
                        verilog <<  ".a(im_toadd[" << 2*j    << "]),\n";
                        verilog <<  ".b(im_toadd[" << 2*j +1 << "]),\n";
                        verilog <<  ".c(o_vector[" << 2*j +1 << "])\n";
                        verilog <<  ");\n";
		}
	}
	else {  // separated the D=2 case since you do not need to temporarily store
		// the current sum,  you only add 2 numbers so you can output directly
		// to the output vector

		for(int i_row=0; i_row<D; i_row++)
		{ // loop over every vector element (ele)
			verilog << "qadd #(N-1,N) re_sum_newrow_" << i_row  << " ("  << endl;
                        verilog <<  ".a(re_toadd[" << D*i_row     << "]),\n";
                        verilog <<  ".b(re_toadd[" << D*i_row + 1 << "]),\n";
                        verilog <<  ".c(re_sums["  << (D-1)*i_row << "])\n";
                        verilog <<  ");\n";

			verilog << "qadd #(N-1,N) im_sum_newrow_" << i_row  << " ("  << endl;
                        verilog <<  ".a(im_toadd[" << D*i_row     << "]),\n";
                        verilog <<  ".b(im_toadd[" << D*i_row + 1 << "]),\n";
                        verilog <<  ".c(im_sums["  << (D-1)*i_row << "])\n";
                        verilog <<  ");\n";

			for(int i_sum=0; i_sum<D-2; i_sum++)
			{ // loop for every addition between D elements

				verilog << "qadd #(N-1,N) re_sum_" << i_row << i_sum << " ("  << endl;
                        	verilog <<  ".a(re_toadd[" <<  D*i_row    + i_sum + 2 << "]),\n";
                        	verilog <<  ".b(re_sums["  << (D-1)*i_row + i_sum     << "]),\n";
                        	verilog <<  ".c(re_sums["  << (D-1)*i_row + i_sum + 1 << "])\n";
                        	verilog <<  ");\n";

				verilog << "qadd #(N-1,N) im_sum_" << i_row << i_sum << " ("  << endl;
                                verilog <<  ".a(im_toadd[" << D*i_row + i_sum + 2 << "]),\n";
                                verilog <<  ".b(im_sums["  << (D-1)*i_row + i_sum     << "]),\n";
                                verilog <<  ".c(im_sums["  << (D-1)*i_row + i_sum + 1 << "])\n";
                                verilog <<  ");\n";
			}
		}
		verilog << "\n// assign sums to output" << endl;
		for(int i=0; i<D; i++) // D always even
		{
			verilog << "assign o_vector[" << 2*i   << "] = re_sums[" << (D-1)*(i+1) -1 << "];"  << endl;
			verilog << "assign o_vector[" << 2*i+1 << "] = im_sums[" << (D-1)*(i+1) -1 << "];"  << endl;
		}
	}


	verilog << "\nendmodule";

}



void write_tensor_product(int num_qb1, int num_qb2, int N){
// int num_qb1: number of qubits of 1st matrix
// int num_qb2: number of qubits of 2nd matrix
// int N:       bit length of the numbers being multiplied

        const int D1 = pow(2,num_qb1);
	const int D2 = pow(2,num_qb2);
    string filename = "hdl/tensorproduct_" + to_string(num_qb1) + to_string(num_qb2) + "qb.sv";
    // check if file already exists
    ifstream f(filename);
    // if you can open an ifstream to the file
    // it exists already
    if (f.good()){
        cout << "Tensorproduct already exists" << endl;
        return;
    }

    string local_file = "tensorproduct_" + to_string(num_qb1) + to_string(num_qb2) + "qb.sv";
    // add filename to file for easy deletion
    ofstream generate_file;
    generate_file.open("hdl/generated_files.txt", ofstream::app);
    generate_file << local_file << endl;
    generate_file.close();

    ofstream verilog;
    verilog.open(filename);
    verilog << "// tensor product module generated using c++" << endl;
    verilog << "// takes kronecker product of 2 matrices of arbitrary size to" << endl;
    verilog << "// output a  matrix" << endl;

    // module heading
    verilog << "module tensorproduct_" << num_qb1 << num_qb2 << "qb #(" << endl;
    verilog << "parameter N = " << N << ","  << endl;
	verilog << "parameter D1 = " << D1 << ","  << endl;
    verilog << "parameter D2 = " << D2 << "\n)\n(\n"  << endl;

    // module input/outputs
    verilog << "input [N-1:0] mat_1 [0:D1**2 *2 -1],"  << endl;
    verilog << "input [N-1:0] mat_2 [0:D2**2 *2 -1],"  << endl;
    verilog << "output [N-1:0] o_mat [0:2*(D1**2)*(D2**2) -1]"  << endl;
	verilog << ");\n\n";

	verilog << "wire ovr[0:(D1**2 * D2**2) -1];\n" << endl;


	// tensor product
	verilog << "// complex multiplication indexed as mat1_row, mat1_col, mat2_row, mat2_col" << endl;
	for(int a_row=0; a_row<D1; a_row++) //loop over rows of 1st matrix
	{
		for(int b_row=0; b_row<D2; b_row++) // loop over rows of 2nd matrix
		{
			for(int a_col=0; a_col<D1; a_col++) // loop over columns of 1st matrix
			{
				for(int b_col=0; b_col<D2; b_col++) // loop over columns of 2nd matrix
				{
					verilog << "\ncomplex_mult #(N) ele_" << a_row << a_col << b_row << b_col << "(\n";
               				verilog <<  ".a(mat_1[" << 2*(D1*a_row + a_col)    << "]),\n";
                			verilog <<  ".b(mat_1[" << 2*(D1*a_row + a_col) +1 << "]),\n";
                			verilog <<  ".c(mat_2[" << 2*(D2*b_row + b_col)    << "]),\n";
                			verilog <<  ".d(mat_2[" << 2*(D2*b_row + b_col) +1 << "]),\n";
                			verilog <<  ".re(o_mat["<< 2*(D2*(a_row*D2*D1 + b_row*D1 + a_col)+b_col)    << "]),\n";
                			verilog <<  ".im(o_mat["<< 2*(D2*(a_row*D2*D1 + b_row*D1 + a_col)+b_col) +1 << "]),\n";
                			verilog <<  ".ovr(ovr[" <<    D2*(a_row*D2*D1 + b_row*D1 + a_col)+b_col << "])\n";
                			verilog <<  ");\n";
				}
			}
		}
	}
	verilog << "\nendmodule";
}


void write_vector_product(int num_qb1, int num_qb2, int N){
// int num_qb1: number of qubits of 1st vector
// int num_qb2: number of qubits of 2nd vector
// int N:       bit lenght of the numbers being multiplied


    const int D1 = pow(2,num_qb1);
	const int D2 = pow(2,num_qb2);
    string filename = "hdl/vectorproduct_" + to_string(num_qb1) + to_string(num_qb2) + "qb.sv";

	// check if file already exists
	ifstream f(filename);
	// if you can open an ifstream to the file
	// it exists already
	if (f.good()){
		cout << "Vector_product already exists" << endl;
		return;
	}

    string local_file = "vectorproduct_" + to_string(num_qb1) + to_string(num_qb2) + "qb.sv";
    // add filename to file for easy deletion
    ofstream generate_file;
    generate_file.open("hdl/generated_files.txt", ofstream::app);
    generate_file << local_file << endl;
    generate_file.close();

    ofstream verilog;
    verilog.open(filename);
    verilog << "// tensor product module generated using c++" << endl;
    verilog << "// takes tensor product of 2 vectors of arbitrary size to" << endl;
    verilog << "// output a vector of size D1*D2" << endl;

    // module heading
    verilog << "module vectorproduct_" << num_qb1 << num_qb2 << "qb #(" << endl;
    verilog << "parameter N = " << N << ","  << endl;
    verilog << "parameter D1 = " << D1 << ","  << endl;
    verilog << "parameter D2 = " << D2 << "\n)\n(\n"  << endl;

    // module input/outputs
    verilog << "input [N-1:0] vec_1 [0:D1*2 -1],"  << endl;
    verilog << "input [N-1:0] vec_2 [0:D2*2 -1],"  << endl;
    verilog << "output [N-1:0] o_vec [0:2*D1*D2 -1]"  << endl;
    verilog << ");\n\n";

    verilog << "wire ovr[0:(D1**2 * D2**2) -1];\n" << endl;


	// tensor product
	verilog << "// complex multiplication indexed as mat1_row, mat1_col, mat2_row, mat2_col" << endl;
	for(int i_1=0; i_1<D1; i_1++)
	{
		for(int i_2=0; i_2<D2; i_2++)
		{
			verilog << "\ncomplex_mult #(N) ele_" << i_1 << i_2 << "(\n";
               		verilog <<  ".a(vec_1[" << 2*i_1    << "]),\n";
                	verilog <<  ".b(vec_1[" << 2*i_1 +1 << "]),\n";
                	verilog <<  ".c(vec_2[" << 2*i_2    << "]),\n";
                	verilog <<  ".d(vec_2[" << 2*i_2 +1 << "]),\n";
                	verilog <<  ".re(o_vec["<< 2*(D2*i_1 + i_2)    << "]),\n";
                	verilog <<  ".im(o_vec["<< 2*(D2*i_1 + i_2) +1 << "]),\n";
                	verilog <<  ".ovr(ovr[" <<    D2*i_1 + i_2     << "])\n";
                	verilog <<  ");\n";
		}
	}
	verilog << "\nendmodule";
}


void write_output(int psi_f_length, int N, int n_qb){
// int n_qb:   number of qubits in circuit
// int N:      bit length of numbers. Multiple of 8 required

	//const int NUM_VAL = 2 * pow(2, n_qb); //number of real numbers
	const int NUM_BYTES = static_cast<int>(N/8);
    const int NUM_OUT = psi_f_length * NUM_BYTES; //number of output cycles
	string filename = "hdl/output_" + to_string(n_qb) + "qb.sv";

	// check if file already exists
    ifstream f(filename);
    // if you can open an ifstream to the file
    // it exists already
    if (f.good()){
        cout << filename << " file already exists" << endl;
        return;
    }

    // add filename to file for easy deletion
    string local_file = "output_" + to_string(n_qb) + "qb.sv";
    ofstream generate_file;
    generate_file.open("hdl/generated_files.txt", ofstream::app);
    generate_file << local_file << endl;
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

#endif
