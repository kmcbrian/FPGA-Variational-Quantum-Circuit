#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// Writes the verilog module to multiply a matrix by a vector
// Dimension of matrix and vector equal to num_qubits**2
// Output of matrix multiplication is a vector of same dimension

// A new module must be generated for different num_qubits or N

void write_matmul(int num_qubits, int N){
// int num_qubits: used for determining dimensionality
// int N:          bit length of the numbers being multiplied

	const int D = pow(2,num_qubits); // matrix: DxD; vector: Dx1
	string filename = "matmul_" + to_string(num_qubits) + "qb.sv";

	// check if file already exists
        ifstream f(filename);
        // if you can open an ifstream to the file
        // it exists already
        if (f.good()){
            cout << "Matmul already exists" << endl;
            return;
        }

    // add filename to file for easy deletion
    ofstream generate_file;
    generate_file.open("generated_files.txt", ofstream::app);
    generate_file << filename << endl;
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

