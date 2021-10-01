#ifndef GATE_H
#define GATE_H

#include <string>
#include <vector>
using namespace std;

class Gate
{
    private:
        int num_qubits;
        int matrix_index; //index of matrices in matrix_vect
        char name[16];

        // Variational gate is just head gate pointing to many regular rotation gates
        bool is_variational; // flag for whether gate has range of inputs
        vector<Gate*> variational_gates;  // holds pointers to all variations of gates

        double angle; // for discerning rotation matrices

    public:
        Gate(){};
        Gate(int, int);
        ~Gate(){};

        void set_num_qubits(int);
        int get_num_qubits();

        void set_matrix_index(int);
        int get_matrix_index();

        void set_name(string);
        char* get_name();

        void set_is_variational(bool);
        bool get_is_variational();

        void set_variational_gate(Gate*);
        Gate* get_variational_gate(int);
        int get_num_gates();

        void set_angle(double angle);
        double get_angle();

};

#endif

