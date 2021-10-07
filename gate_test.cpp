#include <iostream>
#include <string>

#include "gate.h"
#include "timeslice.h"
#include "vqe.h"
#define PI 3.141592653589793

using namespace std;

void run_test();

bool overlap_circuit = true;
bool jz_diag_circuit = false;

int main()
{
    VQE* test_vqe;

    vector<vector<double>> variational_angles;
    vector<double> gate0 = {0., PI/3., 2*PI/3};
    vector<double> gate1 = {0., PI/3., 2*PI/3};
    variational_angles.push_back(gate0);
    variational_angles.push_back(gate1);


    /// Overlap circuit --------------------------------------------------------
    if(overlap_circuit)
    {
        test_vqe = new VQE(2);
        test_vqe->set_variational_angles(variational_angles);
        test_vqe->print_variational_angles();
        test_vqe->H(0);
        test_vqe->variational(1,"Ry",0);
        test_vqe->control(0,1,"X");
        test_vqe->variational(1,"Ry",1);
        test_vqe->control(0,1,"X");
        test_vqe->H(0);
    }

        /// Jz diag circuit --------------------------------------------------------
    if(jz_diag_circuit)
    {
        test_vqe = new VQE(1);
        //test_vqe->variational(0,"Ry",theta_min,theta_max,3);
    }

    test_vqe->write_verilog();

    delete test_vqe;
    return 0;
}


void run_tests()
{
        // Gate-class member function testbench --------------
    Gate* test_gate;
    test_gate = new Gate();

    Gate* temp_gate;
    temp_gate = new Gate();
    string temp_name = "tempi";
    temp_gate->set_name(temp_name);

    test_gate->set_num_qubits(8);
    cout << test_gate->get_num_qubits() << endl;

    test_gate->set_matrix_index(7);
    cout << test_gate->get_matrix_index() << endl;

    string gate_name = "test_gate";
    test_gate->set_name(gate_name);
    cout << test_gate->get_name() << endl;

    bool variational = true;
    test_gate->set_is_variational(variational);
    cout << test_gate->get_is_variational() << endl;
    test_gate->set_variational_gate(temp_gate);
    cout << test_gate->get_variational_gate(0)->get_name();


    // Timeslice-class member function testbench ---------
    Timeslice* test_ts;
    test_ts = new Timeslice(3);
    test_ts->set_gate(1, test_gate);
    cout << test_ts->get_gate(1)->get_name() << endl;

    Timeslice* next_ts;
    next_ts = new Timeslice(3);
    test_ts->set_next_timeslice(next_ts);
    test_ts->get_next_timeslice()->set_gate(0, test_gate);
    cout << next_ts->get_gate(0)->get_name() << endl;

    delete test_gate;
    delete temp_gate;
    delete test_ts;
    delete next_ts;

}
