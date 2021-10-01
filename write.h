#ifndef WRITE_H
#define WRITE_H

void write_matmul(int num_qubits, int N);

void write_output(int psi_f_length, int N, int n_qb);

void write_tensor_product(int num_qb1, int num_qb2, int N);

void write_vector_product(int num_qb1, int num_qb2, int N);

#endif
