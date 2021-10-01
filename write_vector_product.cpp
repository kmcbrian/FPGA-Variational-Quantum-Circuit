#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// Writes the verilog module to take the tensor product of two vectors
// Vectors can be of same or different dimension
// Output of vector product module is a vector of dimensionality
// equal to the product of the input vectors
// e.g. vector in 2 qb space and vector in 3 qb space make a vector in 6 qb space

// A new module must be generated for different num_qb1, num_qb2, or N

void write_vector_product(int num_qb1, int num_qb2, int N){
// int num_qb1: number of qubits of 1st vector
// int num_qb2: number of qubits of 2nd vector
// int N:       bit lenght of the numbers being multiplied


    const int D1 = pow(2,num_qb1);
	const int D2 = pow(2,num_qb2);
    string filename = "vectorproduct_" + to_string(num_qb1) + to_string(num_qb2) + "qb.sv";

	// check if file already exists
	ifstream f(filename);
	// if you can open an ifstream to the file
	// it exists already
	if (f.good()){
		cout << "Vector_product already exists" << endl;
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
