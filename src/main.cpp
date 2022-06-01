#include <iostream>
#include <string>
#include <cmath>

#include "gate.h"
#include "timeslice.h"
#include "variational_circuit.h"
#define PI 3.141592653589793

using namespace std;


int main()
{

    /// Filling angle array -----------------------------------
    double angle_min = 0.0;
    double angle_max = 2*PI;
    int num_angles = 12;

    double step = (angle_max - angle_min) / (num_angles-1);
    double theta[num_angles];
    for(int i=0;i<num_angles;i++)
        theta[i] = angle_min + i*step;

    /// Filling variational_angles ----------------------------
    vector<vector<double>> variational_angles;

    vector<double> angles_0(pow(num_angles,2));
    vector<double> angles_1(pow(num_angles,2));

    for(int i=0;i<num_angles;i++)
    {
        for(int j=0;j<num_angles;j++)
        {
            angles_0[i*num_angles +j] = (theta[i] + theta[j])/2.;
            angles_1[i*num_angles +j] = (theta[i] - theta[j])/2.;
        }
    }

	variational_angles.push_back(angles_0);
	variational_angles.push_back(angles_1);


	/// Variational Circuit Example ---------------------------
	Variational_Circuit* vc;

	vc = new Variational_Circuit(2);
	
	// puts angle vectors in scope of circuit member func.
	vc->set_variational_angles(variational_angles);

	vc->H(0);
	vc->variational(1,"Ry",0); // 0 -> angles_0
	vc->control(0,1,"X");
	vc->variational(1,"Ry",1); // 1 -> angles_1
	vc->control(0,1,"X");
	vc->H(0);

	vc->write_verilog();

	delete vc;
	return 0;
}

