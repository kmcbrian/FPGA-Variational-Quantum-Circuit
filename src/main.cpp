#include <iostream>
#include <string>
#include <cmath>

#include "gate.h"
#include "timeslice.h"
#include "vqe.h"
#define PI 3.141592653589793

using namespace std;

void run_test();

// Choose which circuit to run
bool overlap_circuit  = false; // also used for jz_gcm
bool jz_vqe_circuit   = false;
bool jpjm_vqe_circuit = false;
bool jpjm_gcm_circuit = true;


int main()
{
    VQE* vc;

    /// Filling angle array ----------------------
    double angle_min = 0.0;
    double angle_max = 2*PI;
    int num_angles = 12;

    double step = (angle_max - angle_min) / (num_angles-1);
    vector<double> theta(num_angles);
    for(int i=0;i<num_angles;i++)
    {
        theta[i] = angle_min + i*step;
    }

    /// Filling variational_angles ---------------
    vector<vector<double>> variational_angles;

    vector<double> gcm_angles_0(pow(num_angles,2));
    vector<double> gcm_angles_1(pow(num_angles,2));
    vector<double> zeros(num_angles);


    for(int i=0;i<num_angles;i++)
    {
        zeros[i] = 0.;
        for(int j=0;j<num_angles;j++)
        {
            gcm_angles_0[i*num_angles +j] = (theta[i] + theta[j])/2.;
            gcm_angles_1[i*num_angles +j] = (theta[i] - theta[j])/2.;
        }
    }

    /// Overlap/Jz GCM circuit ------------------------------------------------
    if(overlap_circuit)
    {	
	// put variational angles into proper format
        variational_angles.push_back(gcm_angles_0);
        variational_angles.push_back(gcm_angles_1);

        vc = new VQE(2);
	
	// put variational angles in scope of member functions
        vc->set_variational_angles(variational_angles);
        vc->H(0);
        vc->variational(1,"Ry",0); // 0 -> 1st set of angles
        vc->control(0,1,"X");
        vc->variational(1,"Ry",1); // 1 -> 2nd set of angles
        vc->control(0,1,"X");
        vc->H(0);
    }

    /// Jz VQE circuit --------------------------------------------------------
    if(jz_vqe_circuit)
    {
        variational_angles.push_back(theta);

        vc = new VQE(1);
        vc->set_variational_angles(variational_angles);
        vc->variational(0,"Ry",0);
    }

    /// J+^2 + J-^2 VQE Circuit -----------------------------------------------
    if(jpjm_vqe_circuit)
    {
        variational_angles.push_back(theta);

        vc = new VQE(2);
        vc->set_variational_angles(variational_angles);

        vc->variational(0,"Ry",0);
        vc->variational(1,"Ry",0);
        vc->control(0,1,"X");
        vc->H(0);
    }
    
    /// J+^2 + J-^2 GCM Circuit -----------------------------------------------
    if(jpjm_gcm_circuit)
    {
        variational_angles.push_back(gcm_angles_0);
        variational_angles.push_back(gcm_angles_1);

        vc = new VQE(3);
        vc->set_variational_angles(variational_angles);

        vc->H(0);
        vc->variational(1,"Ry",0);
        vc->variational(2,"Ry",0);
        vc->control(0,1,"X");
        vc->control(0,2,"X");
        vc->variational(1,"Ry",1);
        vc->variational(2,"Ry",1);
        vc->control(0,1,"X");
        vc->control(0,2,"X");
        vc->control(1,2,"X");
        vc->H(0);
        vc->H(1);
    }

    vc->write_verilog();

    delete vc;
    return 0;
}

