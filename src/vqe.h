#ifndef VQE_H
#define VQE_H

#include "gate.h"
#include "timeslice.h"
#include "write.h"
#include <vector>

using namespace std;

class VQE
{
    private:
        int num_qubits;
        const int N = 16; // number of bits for each number
        Timeslice* head_ts_ptr;
        Timeslice* curr_ts_ptr;
        void new_timeslice();

        // keeps track of which qubits have been
        // multiplied into larger vector spaces.
        int **multiplied_qbs;
        void init_state_to_file(int);
	void matrix_to_file(Gate*,int);

        // returns number of qubits in current qb's space
        // for purposes of writing verilog code
        int get_qb_dim(int qb);

        // gates:
        Gate *identity;
        Gate *pauli_X;
        Gate *pauli_Y;
        Gate *pauli_Z;
        Gate *hadamard;
        Gate *target; // for collision detection w/ multi-qubit gates
        vector<Gate*> gate_vect;  // ptrs to generated gates: cnot, rotation

        vector<vector<vector<double>>> matrix_vect;

        void write_circuit(int); //input number of var. gates
        int write_vqe_solver();  //returns number of variational gates
        vector<vector<double>> variational_angles; // need setter and getter

        void vqe_case_writer(vector<Gate*>,ofstream& solver);
        void rotation(const char[], int qubit, double angle, bool set_gate=true);
        string get_rotation_gate_name(const char[], double angle);


    public:
        VQE(){};
        VQE(const int);
        ~VQE();

        Timeslice* get_head_ptr();
        Timeslice* get_curr_ptr();

        void write_verilog();
        void print_mat(Gate*);

        void I(int qubit);
        void X(int qubit);
        void Y(int qubit);
        void Z(int qubit);
        void H(int qubit);

        void Rz(int qubit, double angle, bool set_gate=true);
        void Rx(int qubit, double angle, bool set_gate=true);
        void Ry(int qubit, double angle, bool set_gate=true);
        void phase(int qubit, double angle, bool set_gate=true);

        void variational(int qubit, const char[], int angle_index);
        void set_variational_angles(vector<vector<double>>);
        void print_variational_angles();

        void control(int control, int target, const char[]);
        void temp_control(int control, int target, const char[], double angle=0);
        void swap_gate(int qb1, int qb2);

};

#endif
