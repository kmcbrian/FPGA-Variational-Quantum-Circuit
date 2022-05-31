#include <iostream>
#include <string>
#include <cmath>

#include "gate.h"
#include "timeslice.h"
#include "vqe.h"
#define PI 3.141592653589793

using namespace std;

void run_test();

bool overlap_circuit   = false;
bool jz_diag_circuit   = true;
bool jpjm_diag_circuit = false;
bool jpjm_offdiag_circuit = false;
bool jpjm_vqe = false;

bool test_circuit = false;


int main()
{
    VQE* test_vqe;

    /// Filling angle array ----------------------
    double angle_min = 0.0;
    double angle_max = 2*PI;
    int num_angles = 12;

    double step = (angle_max - angle_min) / (num_angles-1);
    double theta[num_angles];
    for(int i=0;i<num_angles;i++)
    {
        theta[i] = angle_min + i*step;
    }

    /// Filling variational_angles ----------------
    vector<vector<double>> variational_angles;

    vector<double> matrix_0(pow(num_angles,2));
    vector<double> matrix_1(pow(num_angles,2));
    vector<double> pm_0(3);
    vector<double> pm_1(3);
    vector<double> diag_0(num_angles); // used in both diagonal circuits
    vector<double> zeros(num_angles);


    for(int i=0;i<num_angles;i++)
    {
        diag_0[i] = theta[i];
        zeros[i] = 0.;

        for(int j=0;j<num_angles;j++)
        {
            matrix_0[i*num_angles +j] = (theta[i] + theta[j])/2.;
            matrix_1[i*num_angles +j] = (theta[i] - theta[j])/2.;
        }
    }

    for(int i=0;i<3;i++)
    {
        pm_0[i] = matrix_0[0*num_angles + i];
        pm_1[i] = matrix_1[0*num_angles + i];
    }


    /// Overlap circuit --------------------------------------------------------
    if(overlap_circuit)
    {
        // angles used for full GCM
        //variational_angles.push_back(matrix_0);
        //variational_angles.push_back(matrix_1);

        // angles used for VQE
        variational_angles.push_back(diag_0);
        variational_angles.push_back(zeros);


        test_vqe = new VQE(2);
        test_vqe->set_variational_angles(variational_angles);
        //test_vqe->print_variational_angles();
        test_vqe->H(0);
        test_vqe->variational(1,"Ry",0);
        test_vqe->control(0,1,"X");
        test_vqe->variational(1,"Ry",1);
        test_vqe->control(0,1,"X");
        test_vqe->H(0);


        cout << "0 num gates: " << test_vqe->get_head_ptr()->get_next_timeslice()->get_gate(1)->get_num_gates() << endl;
        cout << "1 num gates: " << test_vqe->get_head_ptr()->get_next_timeslice()->get_next_timeslice()->get_next_timeslice()->get_gate(1)->get_num_gates() << endl;


    }

        /// Jz diag circuit --------------------------------------------------------
    if(jz_diag_circuit)
    {
        variational_angles.push_back(diag_0);

        test_vqe = new VQE(1);
        test_vqe->set_variational_angles(variational_angles);
        test_vqe->variational(0,"Ry",0);
    }

    /// Jz off-diag circuit is the same as the overlap circuit
    /// only difference is that the eigenvalues are different

    /// JpJm Diagonal Circuit ------------------------------------------------------
    if(jpjm_diag_circuit)
    {
        variational_angles.push_back(diag_0);

        test_vqe = new VQE(2);
        test_vqe->set_variational_angles(variational_angles);

        test_vqe->variational(0,"Ry",0);
        test_vqe->variational(1,"Ry",0);
        test_vqe->control(0,1,"X");
        test_vqe->H(0);
    }

    if(jpjm_offdiag_circuit)
    {
        //variational_angles.push_back(pm_0);
        //variational_angles.push_back(pm_1);

        test_vqe = new VQE(3);
        //test_vqe->set_variational_angles(variational_angles);

        test_vqe->H(0);
        //test_vqe->variational(1,"Ry",0);
        //test_vqe->variational(2,"Ry",0);
        test_vqe->Ry(1,matrix_0[22]);
        test_vqe->Ry(2,matrix_0[22]);
        test_vqe->control(0,1,"X");
        test_vqe->control(0,2,"X");
        //test_vqe->variational(1,"Ry",1);
        //test_vqe->variational(2,"Ry",1);
        test_vqe->Ry(1,matrix_1[22]);
        test_vqe->Ry(2,matrix_1[22]);
        test_vqe->control(0,1,"X");
        test_vqe->control(0,2,"X");
        test_vqe->control(1,2,"X");
        test_vqe->H(0);
        test_vqe->H(1);
    }
    if(jpjm_vqe)
    {
        variational_angles.push_back(diag_0);

        test_vqe = new VQE(2);
        test_vqe->set_variational_angles(variational_angles);

        //test_vqe->H(0);
        test_vqe->variational(0,"Ry",0);
        test_vqe->variational(1,"Ry",0);
        test_vqe->control(0,1,"X");
        test_vqe->H(0);
        //test_vqe->H(1);
    }
    if(test_circuit)
    {
        test_vqe = new VQE(2);

        //Bell state : 1/sqrt(2) ( |01> + |10> )
        //test_vqe->X(0);
        test_vqe->X(1);
        test_vqe->H(0);
        test_vqe->control(0,1,"X");
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
