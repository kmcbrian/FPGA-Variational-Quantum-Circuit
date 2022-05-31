#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// Writes the verilog module to take the tensor product of 2 matrices
// The matrices can be of same or different dimension
// Output of tensor product module is a matrix of dimensionality
// equal to the product of the input matrices
// e.g. 2 qb gate and 3 qb gate make a 6 qb gate

// A new module must be generated for differend num_qb1, num_qb2, or N

void write_tensor_product(int num_qb1, int num_qb2, int N){
// int num_qb1: number of qubits of 1st matrix
// int num_qb2: number of qubits of 2nd matrix
// int N:       bit length of the numbers being multiplied

        const int D1 = pow(2,num_qb1);
	const int D2 = pow(2,num_qb2);
    string filename = "tensorproduct_" + to_string(num_qb1) + to_string(num_qb2) + "qb.sv";
    // check if file already exists
    ifstream f(filename);
    // if you can open an ifstream to the file
    // it exists already
    if (f.good()){
        cout << "Tensorproduct already exists" << endl;
        return;
    }

    // add filename to file for easy deletion
    ofstream generate_file;
    generate_file.open("generated_files.txt", ofstream::app);
    generate_file << filename << endl;
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
