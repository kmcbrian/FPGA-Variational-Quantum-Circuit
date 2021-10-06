#ifndef VQE_CPP
#define VQE_CPP

#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <math.h>
#include "vqe.h"
#include "binary.h"

#define PI 3.141592653589793

using namespace std;

/** Constructor
        - only constructor to be used
    input:
        const int - number of qubits in circuit
*/
VQE::VQE(const int n_qb)
{
	num_qubits = n_qb;
	head_ts_ptr = new Timeslice(n_qb);
	curr_ts_ptr = head_ts_ptr;
	//N = 32; // size of data


    multiplied_qbs = new int*[n_qb];
	for(int i=0;i<n_qb;i++)
	{
	    multiplied_qbs[i] = new int[n_qb];
		for(int j=0;j<n_qb;j++) //initialize to false
			{multiplied_qbs[i][j] = 0.;}
		multiplied_qbs[i][i] = 1.; // qubits in 1 qb space
	}

	// initialize gates
    matrix_vect.push_back({{1.0/sqrt(2), 0.0}, // Hadamard - 0
                    {1.0/sqrt(2), 0.0},
                    {1.0/sqrt(2), 0.0},
                    {-1.0/sqrt(2), 0.0}});
    matrix_vect.push_back({{0.0, 0.0},         // X - 1
                  		{1.0, 0.0},
                  		{1.0, 0.0},
                  		{0.0, 0.0}});
    matrix_vect.push_back({{0.0, 0.0},         // Y - 2
                        	{0.0,-1.0},
                        	{0.0, 1.0},
                        	{0.0, 0.0}});
    matrix_vect.push_back({{1.0, 0.0},         // Z - 3
                        	{0.0, 0.0},
                        	{0.0, 0.0},
                        	{-1.0, 0.0}});
    matrix_vect.push_back({{1.0, 0.0},         // I - 4
                         	{0.0, 0.0},
                         	{0.0, 0.0},
                         	{1.0, 0.0}});


    identity = new Gate;
    string i_name = "identity";
    identity->set_num_qubits(1);
    identity->set_matrix_index(4); // index pulled from above ^^
    identity->set_name(i_name);
    identity->set_is_variational(false);

    pauli_X = new Gate;
    string x_name = "pauli_X";
    pauli_X->set_num_qubits(1);
    pauli_X->set_matrix_index(1);
    pauli_X->set_name(x_name);
    pauli_X->set_is_variational(false);

    pauli_Y = new Gate;
    string y_name = "pauli_Y";
    pauli_Y->set_num_qubits(1);
    pauli_Y->set_matrix_index(2);
    pauli_Y->set_name(y_name);
    pauli_Y->set_is_variational(false);

    pauli_Z = new Gate;
    string z_name = "pauli_Z";
    pauli_Z->set_num_qubits(1);
    pauli_Z->set_matrix_index(3);
    pauli_Z->set_name(z_name);
    pauli_Z->set_is_variational(false);

    hadamard = new Gate;
    string h_name = "hadamard";
    hadamard->set_num_qubits(1);
    hadamard->set_matrix_index(0);
    hadamard->set_name(h_name);
    hadamard->set_is_variational(false);

    target = new Gate;
    string t_name = "target";
    target->set_num_qubits(0);
    target->set_name(t_name);
    target->set_is_variational(false);

    // create file for storing generated files
    // allows for easy deletion, especially when
    // changing the data size
    ifstream f("generated_files.txt");
    if (!f.good()){
        ofstream make_file;
        make_file.open("generated_files.txt");
        make_file.close();
    }
}

/** Destructor **/
VQE::~VQE()
{
	// delete last object and all ptrs of the class
	Timeslice* temp;

	while(head_ts_ptr->get_next_timeslice() != nullptr)
    {
        temp = head_ts_ptr;
        curr_ts_ptr = head_ts_ptr;
        while(curr_ts_ptr->get_next_timeslice() != nullptr)
        {
            temp = curr_ts_ptr;
            curr_ts_ptr = curr_ts_ptr->get_next_timeslice();
        }
        delete curr_ts_ptr;
        temp->set_next_timeslice(nullptr);
    }
    delete head_ts_ptr;

    delete identity;
    delete pauli_X;
    delete pauli_Y;
    delete pauli_Z;
    delete hadamard;
    delete target;

	for(int i=0;i<num_qubits;i++)
	{
	    delete [] multiplied_qbs[i];
	}
    delete [] multiplied_qbs;

    for(int i=0;i<static_cast<int>(gate_vect.size());i++)
    {
        delete gate_vect[i];
    }
}


/** new_timeslice(void)
        - new object in the linked-list structure
          holding information about circuit
*/
void VQE::new_timeslice()
{
    // initialize new timeslice
    Timeslice *next_timeslice;
    next_timeslice = new Timeslice(num_qubits);

    // link previous timeslice to the new timeslice
    curr_ts_ptr->set_next_timeslice(next_timeslice);

    // change to new timeslice
    curr_ts_ptr = next_timeslice;
}


/** Timeslice attribute getter functions
**/
Timeslice* VQE::get_head_ptr()
{   return this->head_ts_ptr;}

Timeslice* VQE::get_curr_ptr()
{   return this->curr_ts_ptr;}



/*** void Initial state to file()
        - writes the |0> vector in binary to a file
*/
void VQE::init_state_to_file(int N){
    string filename = "vector_qb.dat";

    ifstream f(filename);
        if (f.good()){
                cout <<  filename << " already exists" << endl;
                return;
        }

    ofstream generate_file;
    generate_file.open("generated_files.txt", ofstream::app);
    generate_file << filename << endl;
    generate_file.close();

    ofstream vector_file;
    vector_file.open(filename);

    int num_reals = static_cast<int>(pow(2,this->num_qubits));
    int binary[num_reals][N];
    // initialize binary array to 0
    binary[0][0] = 0;
    for(int j=1;j<N;j++)
        binary[0][j] = 1;
    for(int i=1; i<num_reals; i++)
    {
        for(int j=0;j<N;j++)
            binary[i][j] = 0;
    }

    for(int i=0;i<num_reals;i++)
    {
        for(int bit=0;bit<N;bit++)
            vector_file << binary[i][bit];
        vector_file << "\n";
    }
    vector_file.close();
}


/** int get qubit dimensionality
        - returns the number of qubits in the same
          vector space as the specified qubit
**/
int VQE::get_qb_dim(int qb)
{
        int dim = 0;
        for(int i=0; i<num_qubits; i++)
        {
                if(multiplied_qbs[qb][i])
                {dim++;}
        }
        return dim;
}


/** Constant Single Qubit gates
        -I, X, Y, Z, H
*/
void VQE::I(int qubit)
{
    curr_ts_ptr->set_gate(qubit, identity);
    this->new_timeslice();
}

void VQE::X(int qubit)
{
    curr_ts_ptr->set_gate(qubit, pauli_X);
    this->new_timeslice();
}
void VQE::Y(int qubit)
{
    curr_ts_ptr->set_gate(qubit, pauli_Y);
    this->new_timeslice();
}
void VQE::Z(int qubit)
{
    curr_ts_ptr->set_gate(qubit, pauli_Z);
    this->new_timeslice();
}
void VQE::H(int qubit)
{
    curr_ts_ptr->set_gate(qubit, hadamard);
    this->new_timeslice();
}


/** Variable Single Qubit gates
        -Rz, Rx, Ry, Phase
*/
void VQE::Rz(int qubit, double angle, bool set_gate)
{
    if(angle < 0.0)
        angle = 6.2831853 + angle; // 2*pi + angle
    else if(angle == 0.0)
        angle = fabs(angle);

    string Rz_name = "rz_" + to_string(angle).substr(0,1) + "_" + to_string(angle).substr(2,6);
    int gv_index = gate_vect.size();
    int gate_loc = gv_index; // init to invalid index
    for(int i=0;i<gv_index;i++)
    { // search for matching gate: rz then angle of rotation
        if(Rz_name.compare(0,10,gate_vect[i]->get_name(),0,10) == 0 && angle == gate_vect[i]->get_angle())
            gate_loc = i;
    }

    if(gate_loc != gv_index)
    {
        if(set_gate)
        {
            curr_ts_ptr->set_gate(qubit, gate_vect[gate_loc]);
            this->new_timeslice();
        }
    }
    else
    {
        gate_vect.push_back(new Gate);
        gate_vect[gv_index]->set_num_qubits(1);
        gate_vect[gv_index]->set_matrix_index(matrix_vect.size());
        gate_vect[gv_index]->set_name(Rz_name);
        gate_vect[gv_index]->set_angle(angle);
        gate_vect[gv_index]->set_is_variational(false);

        if(set_gate)
        {
            curr_ts_ptr->set_gate(qubit, gate_vect[gv_index]);
            this->new_timeslice();
        }
        //  Initialize gate matrix: temp
        vector<vector<double>> temp;
        int N = 4;
        temp.resize(N, vector<double>(2));
        for(int j=0;j<N;j++){temp[j][0]=0; temp[j][1]=0;}

        temp[0][0] = cos(angle);
        temp[0][1] = -sin(angle);
        temp[N-1][0] = cos(angle);
        temp[N-1][1] = sin(angle);

        matrix_vect.push_back(temp);
    }

}

void VQE::Rx(int qubit, double angle, bool set_gate)
{
    if(angle < 0.0)
        angle = 6.2831853 + angle; // 2*pi + angle
    else if(angle == 0.0)
        angle = fabs(angle);

    string Rx_name = "rx_"+ to_string(angle).substr(0,1) + "_" + to_string(angle).substr(2,6);
    int gv_index = gate_vect.size();
    int gate_loc = gv_index; // init to invalid index
    for(int i=0;i<gv_index;i++)
    { // search for matching gate: rz then angle of rotation
        if(Rx_name.compare(0,10,gate_vect[i]->get_name(),0,10) == 0 && angle == gate_vect[i]->get_angle())
            gate_loc = i;
    }

    if(gate_loc != gv_index)
    {
        if(set_gate)
        {
            curr_ts_ptr->set_gate(qubit, gate_vect[gate_loc]);
            this->new_timeslice();
        }
    }
    else
    {
        gate_vect.push_back(new Gate);
        gate_vect[gv_index]->set_num_qubits(1);
        gate_vect[gv_index]->set_matrix_index(matrix_vect.size());
        gate_vect[gv_index]->set_name(Rx_name);
        gate_vect[gv_index]->set_angle(angle);
        gate_vect[gv_index]->set_is_variational(false);

        if(set_gate)
        {
            curr_ts_ptr->set_gate(qubit, gate_vect[gv_index]);
            this->new_timeslice();
        }
        //  Initialize gate matrix: temp
        vector<vector<double>> temp;
        int N = 4;
        temp.resize(N, vector<double>(2));
        for(int j=0;j<N;j++){temp[j][0]=0; temp[j][1]=0;}

        temp[0][0] = cos(angle);
        temp[1][1] = -sin(angle);
        temp[2][1] = -sin(angle);
        temp[3][0] = cos(angle);
        matrix_vect.push_back(temp);
    }

}


void VQE::Ry(int qubit, double angle, bool set_gate)
{
    if(angle < 0.0)
        angle = 6.2831853 + angle; // 2*pi + angle
    else if(angle == 0.0)
        angle = fabs(angle);

    string Ry_name = "ry_"+ to_string(angle).substr(0,1) + "_" + to_string(angle).substr(2,6);
    int gv_index = gate_vect.size();

    int gate_loc = gv_index; // init to invalid index
    for(int i=0;i<gv_index;i++)
    { // search for matching gate: rz then angle of rotation
        if(Ry_name.compare(0,10,gate_vect[i]->get_name(),0,10) == 0 && angle == gate_vect[i]->get_angle())
            gate_loc = i;
    }

    if(gate_loc != gv_index)
    {
        if(set_gate)
        {
            curr_ts_ptr->set_gate(qubit, gate_vect[gate_loc]);
            this->new_timeslice();
        }
    }
    else
    {
        cout << " " << Ry_name << " " ;
        gate_vect.push_back(new Gate);
        gate_vect[gv_index]->set_num_qubits(1);
        gate_vect[gv_index]->set_matrix_index(matrix_vect.size());
        gate_vect[gv_index]->set_name(Ry_name);
        gate_vect[gv_index]->set_angle(angle);
        gate_vect[gv_index]->set_is_variational(false);

        if(set_gate)
        {
            curr_ts_ptr->set_gate(qubit, gate_vect[gv_index]);
            this->new_timeslice();
        }
        //  Initialize gate matrix: temp
        vector<vector<double>> temp;
        int N = 4;
        temp.resize(N, vector<double>(2));
        for(int j=0;j<N;j++){temp[j][0]=0; temp[j][1]=0;}

        temp[0][0] = cos(angle);
        temp[1][0] = -sin(angle);
        temp[2][0] = sin(angle);
        temp[3][0] = cos(angle);
        matrix_vect.push_back(temp);
    }

}


void VQE::phase(int qubit, double angle, bool set_gate)
{
    string P_name = "p_" + to_string(angle).substr(0,1) + "_" + to_string(angle).substr(2,6);
    int gv_index = gate_vect.size();
    int gate_loc = gv_index; // init to invalid index
    for(int i=0;i<gv_index;i++)
    { // search for matching gate: rz then angle of rotation
        if(P_name.compare(0,10,gate_vect[i]->get_name(),0,10) == 0 && angle == gate_vect[i]->get_angle())
            gate_loc = i;
    }

    if(gate_loc != gv_index)
    {
        if(set_gate)
        {
            curr_ts_ptr->set_gate(qubit, gate_vect[gate_loc]);
            this->new_timeslice();
        }
    }
    else
    {
        gate_vect.push_back(new Gate);
        gate_vect[gv_index]->set_num_qubits(1);
        gate_vect[gv_index]->set_matrix_index(matrix_vect.size());
        gate_vect[gv_index]->set_name(P_name);
        gate_vect[gv_index]->set_angle(angle);
        gate_vect[gv_index]->set_is_variational(false);

        if(set_gate)
        {
            curr_ts_ptr->set_gate(qubit, gate_vect[gv_index]);
            this->new_timeslice();
        }

        //  Initialize gate matrix: temp
        vector<vector<double>> temp;
        int N = 4;
        temp.resize(N, vector<double>(2));
        for(int j=0;j<N;j++){temp[j][0]=0; temp[j][1]=0;}

        temp[0][0] = 1;
        temp[N-1][0] = cos(angle);
        temp[N-1][1] = sin(angle);

        matrix_vect.push_back(temp);
    }

}


/** Variational Gate
*/
void VQE::variational(int qubit, const char gate[], double start, double stop, int num_angles)
{
    /// string cleansing
    string temp_name(gate);
    for(unsigned int i=0;i<temp_name.length();i++)
        temp_name[i] = tolower(temp_name[i]);

    /// check if valid gate for varying
    if(temp_name.compare("rx") && temp_name.compare("ry") && temp_name.compare("rz"))
        throw invalid_argument("Invalid Argument: Gate does not exist for as a Variational gate.\nValid options include Rx, Ry, Rz.");
    if(abs(start) >= 2*PI || abs(stop) >= 2*PI) /// ~ 2pi
        throw invalid_argument("Start or Stop exceeds the allowable ranges. Acceptable values in range [-2pi,2pi] radians ");

    if(start == 0.0)
        start = fabs(start);
    else if(start < 0.0)
        start = fabs(6.2831853 + start); // 2*pi + angle
    if(stop == 0.0)
        stop = fabs(stop);
    else if(stop < 0.0)
        stop = fabs(6.2831853 + stop); // 2*pi + angle

    /// check if variational gate exists already
    string gate_name = temp_name + "V_"+ to_string(start).substr(0,1) + to_string(start).substr(2,2) + "_" + to_string(stop).substr(0,1) + to_string(stop).substr(2,2) + "_" + to_string(num_angles);
    int gv_index = this->gate_vect.size();
    int gate_loc = gv_index;
    for(int i=0;i<gv_index;i++)
    { // search for matching gate: rz then angle of rotation
        if(gate_name.compare(0,12,this->gate_vect[i]->get_name(),0,12) == 0)
            gate_loc = i;
    }

    /// if variational gate exists, just point to that
    if(gate_loc != gv_index)
    {
        this->curr_ts_ptr->set_gate(qubit, gate_vect[gate_loc]);
        this->new_timeslice();
    }
    else
    {
        /// make all rotation gates/matrices
        double angles[num_angles];
        double lower = min(start,stop);
        double higher= max(start,stop);
        double step_size = (higher - lower)/static_cast<double>(num_angles);
        for(int i=0;i<num_angles;i++)
        {
            angles[i] = lower + i*step_size;
            cout << angles[i] << "  ";
        }
        if(!temp_name.compare("rx"))
        {
            for(int i=0;i<num_angles;i++)
                this->Rx(qubit, angles[i], false);
        }
        else if(!temp_name.compare("ry"))
        {
            for(int i=0;i<num_angles;i++)
                this->Ry(qubit, angles[i], false);
        }
        else
        {
            for(int i=0;i<num_angles;i++)
                this->Rz(qubit, angles[i], false);
        }
        cout << "\ngate vector size:" << this->gate_vect.size() << endl;


        /// create variational gate in gate_vect
        gv_index = this->gate_vect.size();
        gate_loc = gv_index;

        gate_vect.push_back(new Gate);
        gate_vect[gv_index]->set_num_qubits(1);
        gate_vect[gv_index]->set_name(gate_name);
        gate_vect[gv_index]->set_is_variational(true);

        cout << endl;
        /// find all corrsponding rotation gates created above
        string loop_name;
        for(int i_angles=0;i_angles<num_angles;i_angles++)
        {
            loop_name.assign(temp_name + "_" + to_string(angles[i_angles]).substr(0,1) + "_" + to_string(angles[i_angles]).substr(2,6));
            for(int i=0;i<gv_index;i++)
            { // search for matching gate: rz then angle of rotation
                if(loop_name.compare(0,10,this->gate_vect[i]->get_name(),0,10) == 0 && angles[i_angles] == this->gate_vect[i]->get_angle())
                {
                        this->gate_vect[gv_index]->set_variational_gate(this->gate_vect[i]);
                        cout << i << "  "<< angles[i_angles] << "  " << this->gate_vect[i]->get_angle() << "\n";
                }
            }
            //cout << "  " << this->gate_vect[gv_index]->get_variational_gate(i_angles)->get_name();
        }
        cout << endl;

        /// assign timeslice pointer to variational gate
        this->curr_ts_ptr->set_gate(qubit, gate_vect[gv_index]);
        this->new_timeslice();
    }
}



/**  Two qubit gates
        -control, swap
*/
void VQE::control(int cont, int targ, const char gate[])
{
    int matrix_index=0;
    double angle = 0.;
    string gate_name(gate);
    for(unsigned int i=0;i<gate_name.length();i++)
        gate_name[i] = tolower(gate_name[i]);

    // get location of matrix being "controlled"
    if(!gate_name.compare("h"))
        matrix_index = hadamard->get_matrix_index();
    else if(!gate_name.compare("x"))
        matrix_index = pauli_X->get_matrix_index();
    else if(!gate_name.compare("y"))
        matrix_index = pauli_Y->get_matrix_index();
    else if(!gate_name.compare("z"))
        matrix_index = pauli_Z->get_matrix_index();
    else
        throw invalid_argument("Invalid Argument: Gate does not exist for Control");

    string name;
    name.append("c");
    name.append(gate_name);
    name.append(to_string(cont) + to_string(targ));

    int gv_index = gate_vect.size();
    int gate_loc = gv_index; // init to invalid index
    for(int i=0;i<gv_index;i++)
    { // search for matching gate: rz then angle of rotation
        if(name.compare(0,5,gate_vect[i]->get_name(),0,5) == 0 && angle == gate_vect[i]->get_angle())
            gate_loc = i;
    }
    if(gate_loc != gv_index)
    {
        curr_ts_ptr->set_gate(cont, gate_vect[gate_loc]);
        curr_ts_ptr->set_gate(targ, target);
        this->new_timeslice();
    }
    else
    {
        gate_vect.push_back(new Gate);
        gate_vect[gv_index]->set_num_qubits(2);
        gate_vect[gv_index]->set_matrix_index(matrix_vect.size());
        gate_vect[gv_index]->set_name(name);
        gate_vect[gv_index]->set_angle(angle);
        gate_vect[gv_index]->set_is_variational(false);

        curr_ts_ptr->set_gate(cont, gate_vect[gv_index]);
        curr_ts_ptr->set_gate(targ, target);
        this->new_timeslice();


        vector<vector<double>> temp;
        int N = static_cast<int>(pow(2, 2 * abs(cont - targ) + 2));
        temp.resize(N, vector<double>(2));
        for(int j=0;j<N;j++){temp[j][0]=0; temp[j][1]=0;}

        int D = static_cast<int>(pow(2,  abs(cont - targ) + 1));
        int num_bits = (targ > cont) ? targ + 1 : cont + 1;
        int bin[num_bits], bin_flip[num_bits], x;

        for(int i=0; i<D; i++) // loop through every row
        {
            for(int j=0;j<num_bits;j++){bin[j]=0; bin_flip[j]=0;}
            // convert i to binary to see if control bit is true
            inttoBinary(i, bin, num_bits);

            if(bin[cont] == 1)
            {   // diagonal element
                temp[D*i+i][0] = matrix_vect[matrix_index][2*bin[targ] + bin[targ]][0];
                temp[D*i+i][1] = matrix_vect[matrix_index][2*bin[targ] + bin[targ]][1];
                // copy binary to flip bit
                for(int j=0;j<num_bits;j++){bin_flip[j]=bin[j];}
                // bit-flip: 0->1, 1->0
                bin_flip[targ] = -1*bin_flip[targ] + 1;
                // record decimal represented by bit flipped binary
                x = binarytoInt(bin_flip,num_bits);
                // off-diagonal element
                temp[D*i+x][0] = matrix_vect[matrix_index][2*bin[targ] + bin_flip[targ]][0];
                temp[D*i+x][1] = matrix_vect[matrix_index][2*bin[targ] + bin_flip[targ]][1];

            }
            else
            { 	// when control bit is false, 1 along diagonal
                temp[D*i+i][0] = 1.0;
            }

        }

        matrix_vect.push_back(temp);
        //print_mat(gate_vect[gv_index]);
    }
}



void VQE::temp_control(int cont, int targ, const char gate[], double angle)
{
    int matrix_index=0;
    string gate_name(gate);
    for(int i=0;i<gate_name.length();i++)
        gate_name[i] = tolower(gate_name[i]);

    // get location of matrix being "controlled"
    if(!gate_name.compare("h"))
        matrix_index = hadamard->get_matrix_index();
    else if(!gate_name.compare("x"))
        matrix_index = pauli_X->get_matrix_index();
    else if(!gate_name.compare("y"))
        matrix_index = pauli_Y->get_matrix_index();
    else if(!gate_name.compare("z"))
        matrix_index = pauli_Z->get_matrix_index();
    else if(!gate_name.compare("rz")){
        int gv_index = gate_vect.size();
        int gate_loc = gv_index; // init to invalid index
        for(int i=0;i<gv_index;i++)
        { // search for matching gate
            if(!gate_name.compare(0,10,gate_vect[i]->get_name(),0,10) == 0 && angle == gate_vect[i]->get_angle())
                gate_loc = i;
        }
        if(gate_loc != gv_index){
            matrix_index = gate_vect[gate_loc]->get_matrix_index();
        }
        else{
            Rz(0,angle,false);
            matrix_index = gate_vect[gv_index]->get_matrix_index();
        }
    }
    else if(!gate_name.compare("rx")){
        int gv_index = gate_vect.size();
        int gate_loc = gv_index; // init to invalid index
        for(int i=0;i<gv_index;i++)
        { // search for matching gate
            if(!gate_name.compare(0,10,gate_vect[i]->get_name(),0,10) == 0 && angle == gate_vect[i]->get_angle())
                gate_loc = i;
        }
        if(gate_loc != gv_index){
            matrix_index = gate_vect[gate_loc]->get_matrix_index();
        }
        else{
            Rx(0,angle,false);
            matrix_index = gate_vect[gv_index]->get_matrix_index();
        }
    }
    else if(!gate_name.compare("ry")){
        int gv_index = gate_vect.size();
        int gate_loc = gv_index; // init to invalid index
        for(int i=0;i<gv_index;i++)
        { // search for matching gate
            if(!gate_name.compare(0,10,gate_vect[i]->get_name(),0,10) == 0 && angle == gate_vect[i]->get_angle())
                gate_loc = i;
        }
        if(gate_loc != gv_index){
            matrix_index = gate_vect[gate_loc]->get_matrix_index();
        }
        else{
            Ry(0,angle,false);
            matrix_index = gate_vect[gv_index]->get_matrix_index();
        }
    }
    else if(!gate_name.compare("phase")){
        // gate is same when control & target qbs are switched
        int low = min(cont,targ);
        int high = max(cont,targ);
        cont = low;
        targ = high;

        int gv_index = gate_vect.size();
        int gate_loc = gv_index; // init to invalid index
        for(int i=0;i<gv_index;i++)
        { // search for matching gate
            if(!gate_name.compare(0,10,gate_vect[i]->get_name(),0,10) == 0 && angle == gate_vect[i]->get_angle())
                gate_loc = i;
        }
        if(gate_loc != gv_index){
            matrix_index = gate_vect[gate_loc]->get_matrix_index();
        }
        else{
            phase(0,angle,false);
            matrix_index = gate_vect[gv_index]->get_matrix_index();
        }
    }
    else
        throw invalid_argument("Invalid Argument: Gate does not exist for Control\nValid gates include x,y,z,rx,ry,rz,phase");

    string name;
    name.append("c");
    name.append(gate_name);
    name.append(to_string(cont) + to_string(targ));
    if(angle != 0.)
        name.append("_" + to_string(angle).substr(0,1) + "_" + to_string(angle).substr(2,6));


    int gv_index = gate_vect.size();
    int gate_loc = gv_index; // init to invalid index
    for(int i=0;i<gv_index;i++)
    { // search for matching gate: rz then angle of rotation
        if(name.compare(0,5,gate_vect[i]->get_name(),0,5) == 0 && angle == gate_vect[i]->get_angle())
            gate_loc = i;
    }
    if(gate_loc != gv_index)
    {
        curr_ts_ptr->set_gate(cont, gate_vect[gate_loc]);
        curr_ts_ptr->set_gate(targ, target);
    }
    else
    {
        gate_vect.push_back(new Gate);
        gate_vect[gv_index]->set_num_qubits(2);
        gate_vect[gv_index]->set_matrix_index(matrix_vect.size());
        gate_vect[gv_index]->set_name(name);
        gate_vect[gv_index]->set_angle(angle);

        curr_ts_ptr->set_gate(cont, gate_vect[gv_index]);
        curr_ts_ptr->set_gate(targ, target);


        vector<vector<double>> temp;
        int N = static_cast<int>(pow(2, 2 * abs(cont - targ) + 2));
        temp.resize(N, vector<double>(2));
        for(int j=0;j<N;j++){temp[j][0]=0; temp[j][1]=0;}

        int D = static_cast<int>(pow(2,  abs(cont - targ) + 1));
        int num_bits = (targ > cont) ? targ + 1 : cont + 1;
        int bin[num_bits], bin_flip[num_bits], x;

    for(int i=0; i<D; i++) // loop through every row
        {
            for(int j=0;j<num_bits;j++){bin[j]=0; bin_flip[j]=0;}
            // convert i to binary to see if control bit is true
            inttoBinary(i, bin, num_bits);

            if(bin[cont] == 1)
            {   // diagonal element
                temp[D*i+i][0] = matrix_vect[matrix_index][2*bin[targ] + bin[targ]][0];
                temp[D*i+i][1] = matrix_vect[matrix_index][2*bin[targ] + bin[targ]][1];
                // copy binary to flip bit
                for(int j=0;j<num_bits;j++){bin_flip[j]=bin[j];}
                // bit-flip: 0->1, 1->0
                bin_flip[targ] = -1*bin_flip[targ] + 1;
                // record decimal represented by bit flipped binary
                x = binarytoInt(bin_flip,num_bits);
                // off-diagonal element
                temp[D*i+x][0] = matrix_vect[matrix_index][2*bin[targ] + bin_flip[targ]][0];
                temp[D*i+x][1] = matrix_vect[matrix_index][2*bin[targ] + bin_flip[targ]][1];

            }
            else
            {   // when control bit is false, 1 along diagonal
                temp[D*i+i][0] = 1.0;
            }

        }

        matrix_vect.push_back(temp);
        //print_mat(gate_vect[gv_index]);
    }
}




void VQE::swap_gate(int qb1, int qb2)
{
    double angle = 0.;
    int low_qb, high_qb;

    string name;
    name.append("swap");
    if(qb1<qb2){
        low_qb = qb1;
        high_qb = qb2;
    }
    else{
        low_qb = qb2;
        high_qb=qb1;
    }
    name.append(to_string(low_qb) + to_string(high_qb));

    int gv_index = gate_vect.size();
    int gate_loc = gv_index; // init to invalid index
    for(int i=0;i<gv_index;i++)
    { // search for matching gate: rz then angle of rotation
        if(name.compare(0,6,gate_vect[i]->get_name(),0,6) == 0 && angle == gate_vect[i]->get_angle())
            gate_loc = i;
    }
    if(gate_loc != gv_index)
    {
        curr_ts_ptr->set_gate(qb1, gate_vect[gate_loc]);
        curr_ts_ptr->set_gate(qb2, target);
        this->new_timeslice();
    }
    else
    {
        gate_vect.push_back(new Gate);
        gate_vect[gv_index]->set_num_qubits(2);
        gate_vect[gv_index]->set_matrix_index(matrix_vect.size());
        gate_vect[gv_index]->set_name(name);
        gate_vect[gv_index]->set_angle(angle);
        gate_vect[gv_index]->set_is_variational(false);

        curr_ts_ptr->set_gate(qb1, gate_vect[gv_index]);
        curr_ts_ptr->set_gate(qb2, target);
        this->new_timeslice();


        vector<vector<double>> temp;
        int N = static_cast<int>(pow(2, 2 * abs(high_qb - low_qb) + 2));
        temp.resize(N, vector<double>(2));
        for(int j=0;j<N;j++){temp[j][0]=0; temp[j][1]=0;}

        int D = static_cast<int>(pow(2,  abs(high_qb - low_qb) + 1));
        int num_bits = high_qb + 1;
        int bin[num_bits], bin_flip[num_bits], x;

        for(int i=0; i<D; i++) // loop through every row
        {
            for(int j=0;j<num_bits;j++){bin[j]=0; bin_flip[j]=0;}
            // convert i to binary to see if control bit is true
            inttoBinary(i, bin, num_bits);

            if(bin[low_qb] != bin[high_qb])
            {
                // copy binary to flip bit
                for(int j=0;j<num_bits;j++){bin_flip[j]=bin[j];}
                // bit-flip: 0->1, 1->0
                bin_flip[qb1] = -1*bin_flip[qb1] + 1;
                bin_flip[qb2] = -1*bin_flip[qb2] + 1;
                // record decimal represented by bit flipped binary
                x = binarytoInt(bin_flip,num_bits);
                // off-diagonal element
                temp[D*i+x][0] = 1.0;

            }
            else
            { 	// when bits are the same, 1 along diagonal
                temp[D*i+i][0] = 1.0;
            }
        }
        matrix_vect.push_back(temp);
    }
}


void VQE::matrix_to_file(Gate* curr_gate, int N){
    // convert the matrix to sign-magnitude binary and print to file to be read by HDL
    const char extension[] = ".dat";
    char* filename = new char[strlen(curr_gate->get_name()) + strlen(extension)+1];
    strcpy(filename, curr_gate->get_name());
    strcat(filename, extension);
    // check if file already exists for matrix
    ifstream f(filename);
        if (f.good()){
                cout <<  filename << " already exists" << endl;
                delete[] filename;
                return;
        }

    ofstream generate_file;
    generate_file.open("generated_files.txt", ofstream::app);
    generate_file << filename << endl;
    generate_file.close();

    ofstream vector_file;
    vector_file.open(filename);

    int mat_size = matrix_vect[curr_gate->get_matrix_index()].size();
    int binary[2*mat_size][N];
    // initialize binary array to 0
    for(int i=0; i<mat_size*2; i++)
    {
        for(int j=0;j<N;j++)
            binary[i][j] = 0;
    }

    for(int m=0; m<mat_size;m++)
    {   //iterate over real and imaginary parts for each element
        for(int n=0;n<2; n++)
        {   // writes binary numbers to binary array
            // binary is passed by reference
            dbltoBinary(matrix_vect[curr_gate->get_matrix_index()][m][n], binary[m*2 + n], N);
        }
    }

    for(int i=0;i<mat_size*2;i++)
    {
        for(int bit=0;bit<N;bit++)
        {
            vector_file << binary[i][bit];
        }
        vector_file << "\n";
    }

    vector_file.close();
    delete[] filename;
}

void VQE::write_verilog()
{
    int n_var = write_vqe_solver();
    write_circuit(n_var);
}

void VQE::write_circuit(int n_var)
{
    string filename = "variational_circuit" + to_string(n_var) +".sv";
    // check if file already exists
    ifstream f(filename);
    // if you can open an ifstream to the file
    // it exists already
    if (f.good()){
        cout << filename << " already exists" << endl;
        return;
    }

    ofstream circuit;
    circuit.open(filename);
    //const int N = 16; // data size in Verilog

    // add filename to file for easy deletion
    ofstream generate_file;
    generate_file.open("generated_files.txt", ofstream::app);
    generate_file << filename << endl;
    generate_file.close();

    curr_ts_ptr = head_ts_ptr;
    Gate *curr_gate = nullptr;
    Gate *temp_gate = nullptr;

    // Code Generating Variables
    int psi_index = num_qubits; // used to increment wavefunctions
    int i_module = 0; // increment module name
    int last_index[num_qubits]; // holds last wf index for each qubit
    int i_temp, j_temp;
    int gate_qb; // number of qubits for current gate
    int gate_space[num_qubits];  // qubit spaces gate acts on
    int diff_space[num_qubits];  // difference between curr_space and gate_space
    int target_qb;  // holds index of target qubit for control gate
    int min_qb, max_qb; // for iterating through mult_qb
    int curr_qb_space, next_qb_space;
    char curr_matrix_name[16];
    int  curr_matrix_dim;
    vector<Gate*> gates_used;
    int i_var_gate = 0;

    // MODULE HEADER
    circuit << "`timescale 1ns/1ps" << endl;
    circuit << "module variational_circuit" << n_var << "#(" << endl;
    circuit << "    parameter N=" << N << ","<< endl;
    circuit << "    parameter n_qb= "<< num_qubits << "\n)\n(" << endl;
    for(int i=0;i<n_var;i++)
        circuit << "    input wire [N-1:0] v_matrix" << i << " [0:7]," << endl; // only single qb variational gates
    circuit << "    output wire [N-1:0] psi_f [0:" << static_cast<int>(pow(2,num_qubits+1)-1) << "]\n);" << endl;

    // Initialize qubits
    for(int i=0;i<num_qubits;i++)
    {
        circuit << "reg [N-1:0] psi_" << i << " [0:3];" << endl;
        last_index[i] = i; // initialize array
        gate_space[i] = 0;
    }
    circuit << "\n // generating vector_products, tensor_products, and matmul\n" << endl;
    while(curr_ts_ptr != nullptr)
    {
        for(int i_qb=0;i_qb < this->num_qubits;i_qb++)
		{
			curr_gate = curr_ts_ptr->get_gate(i_qb);
			if(curr_gate != nullptr)
			{
                cout <<  "Gate: " << curr_gate->get_name() << " - " << i_qb << endl;
                gate_qb = curr_gate->get_num_qubits();
                //strcpy(curr_matrix_name, curr_gate->get_name()); //keep current matrix name to multiply

                for(int reset=0;reset<num_qubits;reset++){
                    gate_space[reset] = 0;
                }

                // determine vector space gate acts on
                if(gate_qb == 1){
                    gate_space[i_qb] =1;
                    min_qb = i_qb;
                    max_qb = i_qb+1;
                }
                else if(gate_qb == 2){
                    target_qb = -1;
                    for(int ii_qb=0; ii_qb<num_qubits; ii_qb++){ // find target to control gate
                        if(curr_ts_ptr->get_gate(ii_qb) != nullptr && strcmp(curr_ts_ptr->get_gate(ii_qb)->get_name(),"target") == 0){
                            target_qb = ii_qb;
                        }
                    }
                    if(target_qb != -1){ // if target gate was found
                        for(int jj=min(i_qb,target_qb);jj<max(i_qb,target_qb)+1;jj++){
                            gate_space[jj] =1;
                        }
                    }
                    else{
                        cout << "\nTarget gate not found" << endl;
                    }
                    min_qb = min(i_qb, target_qb);
                    max_qb = max(i_qb, target_qb)+1;
                }
                else{ // if target gate
                    break;
                }
                curr_matrix_dim = max_qb - min_qb;

                if(curr_gate->get_is_variational())
                {
                    sprintf(curr_matrix_name, "v_matrix%d", i_var_gate);
                    i_var_gate++;
                }
                else
                {
                    strcpy(curr_matrix_name, curr_gate->get_name()); //keep current matrix name to multiply

                    if(find(gates_used.begin(),gates_used.end(),curr_gate) == gates_used.end())
                    {
                        gates_used.push_back(curr_gate); // add gates after target have been removed
                        circuit << "reg [N-1:0] " << curr_matrix_name << " [0:" << pow(2, 2*(curr_matrix_dim)+1 )-1 << "];" << endl;
                    }

                }
                // Determine if Tensor_product or Vector product is necessary
                for(int i=min_qb;i<max_qb;i++){
                    for(int j=0;j<num_qubits;j++){
                        diff_space[j] = multiplied_qbs[i][j] - gate_space[j];

                        if(diff_space[j] == 1){ // if qubit space bigger than gate space
                            // output tensor product module
                            if(find(gates_used.begin(),gates_used.end(),identity) == gates_used.end()){
                                gates_used.push_back(identity);
                                circuit << "reg [N-1:0] identity [0:7];" << endl;
                            }
                            if(i_qb<j){ //expand to qubit space below gate
                                write_tensor_product(curr_matrix_dim, 1, N);
                                circuit << "wire [N-1:0] o_mat" << psi_index << " [0:" << pow(2, 2*(curr_matrix_dim+1)+1 )-1 << "];" << endl;
                                circuit << "tensorproduct_" << curr_matrix_dim << "1qb tp" << i_module << "(" << endl;
                                circuit << "    .mat_1(" << curr_matrix_name << ")," << endl;
                                circuit << "    .mat_2(" << identity->get_name() << ")," << endl;
                                circuit << "    .o_mat(o_mat" <<psi_index << ")\n);\n" << endl;

                                sprintf(curr_matrix_name, "o_mat%d", psi_index);
                                curr_matrix_dim++;
                                psi_index++;
                                i_module++;
                                gate_space[j] = 1; // gate space grows in tensor products
                                //break;
                            }
                            else if(i_qb>j){ // expand to qubit space above gate
                                write_tensor_product(1, curr_matrix_dim, N);
                                circuit << "wire [N-1:0] o_mat" << psi_index << " [0:" << pow(2, 2*(curr_matrix_dim+1)+1 )-1 << "];" << endl;
                                circuit << "tensorproduct_1" << curr_matrix_dim << "qb tp" << i_module << "(" << endl;
                                circuit << "    .mat_1(" << identity->get_name() << ")," << endl;
                                circuit << "    .mat_2(" << curr_matrix_name << ")," << endl;
                                circuit << "    .o_mat(o_mat" <<psi_index << ")\n);\n" << endl;

                                sprintf(curr_matrix_name, "o_mat%d", psi_index);
                                curr_matrix_dim++;
                                psi_index++;
                                i_module++;
                                gate_space[j] = 1; // gate space grows in tensor products

                                //break;
                            }
                            else{
                                cout << "\n\nsomething is not quite right in write_circuit\n\n";
                            }
                        }
                        else if(diff_space[j] == -1){
                            curr_qb_space = get_qb_dim(i_qb);
                            next_qb_space = get_qb_dim(j);
                            if(i_qb<j){ //expand to qubit space below gate
                                write_vector_product(curr_qb_space, next_qb_space, N);
                                circuit << "wire [N-1:0] psi_" << psi_index << " [0:" << pow(2, curr_qb_space+next_qb_space+1 )-1 << "];" << endl;
                                circuit << "vectorproduct_" << curr_qb_space << next_qb_space << "qb vp" << i_module << "(" << endl;
                                circuit << "    .vec_1(psi_" << last_index[i_qb] << ")," << endl;
                                circuit << "    .vec_2(psi_" << last_index[j] << ")," << endl;
                                circuit << "    .o_vec(psi_" << psi_index << ")\n);\n" << endl;

                                // update last_index
                                i_temp = last_index[i_qb];
                                j_temp = last_index[j];
                                for(int i_l=0;i_l<num_qubits;i_l++){
                                    //cout << last_index[i_l];
                                    if(last_index[i_l] == i_temp || last_index[i_l] == j_temp){
                                        last_index[i_l] = psi_index;
                                    }
                                }
                                cout << "\n";
                                //update multiplied_qbs from last_index
                                for(int i_mq=0;i_mq<num_qubits;i_mq++){
                                    for(int j_mq=0;j_mq<num_qubits;j_mq++){
                                        if(last_index[i_mq]==last_index[j_mq]){
                                            multiplied_qbs[i_mq][j_mq] = 1;
                                        }
                                        //cout << multiplied_qbs[i_mq][j_mq];
                                    }
                                }
                                //cout << "\n";
                                psi_index++;
                                i_module++;
                                //break;
                            }
                            else if(i_qb>j){ //expand to qubit space below gate
                                write_vector_product(next_qb_space, curr_qb_space, N);
                                circuit << "wire [N-1:0] psi_" << psi_index << " [0:" << pow(2, curr_qb_space+next_qb_space+1 )-1 << "];" << endl;
                                circuit << "vectorproduct_" << next_qb_space << curr_qb_space << "qb vp" << i_module << "(" << endl;
                                circuit << "    .vec_1(psi_" << last_index[j] << ")," << endl;
                                circuit << "    .vec_2(psi_" << last_index[i_qb] << ")," << endl;
                                circuit << "    .o_vec(psi_" << psi_index << ")\n);\n" << endl;

                                // update last_index
                                i_temp = last_index[i_qb];
                                j_temp = last_index[j];
                                for(int i_l=0;i_l<num_qubits;i_l++){
                                    if(last_index[i_l] == i_temp || last_index[i_l] == j_temp){
                                        last_index[i_l] = psi_index;
                                    }
                                }

                                //update multiplied_qbs from last_index
                                for(int i_mq=0;i_mq<num_qubits;i_mq++){
                                    for(int j_mq=0;j_mq<num_qubits;j_mq++){
                                        if(last_index[i_mq]==last_index[j_mq]){
                                            multiplied_qbs[i_mq][j_mq] = 1;
                                        }
                                    }
                                }
                                psi_index++;
                                i_module++;
                            }
                        }
                    }
                }
                // print matmul module
                curr_qb_space = get_qb_dim(i_qb);
                write_matmul(curr_qb_space, N);
                // make place for result to be stored

                circuit << "wire [N-1:0] psi_" << psi_index << " [0:" << static_cast<int>(pow(2,curr_qb_space +1) -1) << "];" << endl;
                // print matmul module in ofstream
                circuit << "matmul_" << curr_qb_space << "qb mm" <<  i_module << " (" << endl;
                circuit << "    .matrix(" << curr_matrix_name << ")," << endl;
                circuit << "    .i_vector(psi_" << last_index[i_qb] << ")," << endl;
                circuit << "    .o_vector(psi_" << psi_index << ")\n);\n" << endl;

                // update last_index
                //cout << "i_qb: " << i_qb << " last_index: ";
                i_temp = last_index[i_qb];
                for(int i_l=0;i_l<num_qubits;i_l++){
                    //cout << last_index[i_l];
                    if(last_index[i_l] == i_temp){
                        last_index[i_l] = psi_index;
                    }
                }
                cout << endl;
                i_module++;
                psi_index++;
			}
		}
        curr_ts_ptr = curr_ts_ptr->get_next_timeslice();
    }
    circuit << "\ninitial begin" << endl;
    init_state_to_file(N);
    for(int i=0;i<num_qubits;i++){
        circuit << "   $readmemb(\"vector_qb.dat\", psi_" << i << ");" << endl;
    }


    for(int i=0;i<gates_used.size();i++){
        circuit << "   $readmemb(\"" << gates_used[i]->get_name() << ".dat\", " << gates_used[i]->get_name() << ");" << endl;
        matrix_to_file(gates_used[i],N);
    }
    circuit << "end" << endl << endl;

    circuit << "assign psi_f[0:" <<  static_cast<int>(pow(2,num_qubits+1)-1) << "] = psi_" << psi_index-1 << "[0:" <<  static_cast<int>(pow(2,num_qubits+1)-1) << "];" << endl;

    circuit << "\nendmodule";
}


//returns number of variational gates
int VQE::write_vqe_solver()
{
    ofstream solver;
    string filename = "vqe_solver.sv";

    // add filename to file for easy deletion
    ofstream generate_file;
    generate_file.open("generated_files.txt", ofstream::app);
    generate_file << filename << endl;
    generate_file.close();

    solver.open(filename);

    curr_ts_ptr = head_ts_ptr;
    Gate *curr_gate = nullptr;
    Gate *temp_gate = nullptr;

    // Code Generating Variables
    int psi_f_length = 1;
    int n_wavefunctions = 1; // multiplicative so need to start at 1
    vector<Gate*> gates_used;
    vector<Gate*> variational_gates;

    // MODULE HEADER
    solver << "`timescale 1ns/1ps" << endl;
    solver << "module vqe_solver(" << endl;
    solver << "    input wire listener_flag,"<< endl;
    solver << "    input wire fpga_clock," << endl;
    solver << "    output wire shared_clock," << endl; // only single qb variational gates
    solver << "    output wire LEDR," << endl;
    solver << "    output wire[7:0] out," << endl;
    solver << "    output wire source_flag," << endl;
    solver << "    output wire parity \n);\n" << endl;

    solver << "parameter N = "<< N << ";" << endl;
    solver << "parameter n_qb = " << num_qubits << ";" << endl;

    solver << "reg source_flag_reg;" << endl;
    solver << "assign source_flag = source_flag_reg;" << endl;
    solver << "assign LEDR = source_flag_reg;\n" << endl;

    // Initializing all registers for variational gates
    while(curr_ts_ptr != nullptr)
    {
        for(int i_qb=0;i_qb < this->num_qubits;i_qb++)
		{
			curr_gate = curr_ts_ptr->get_gate(i_qb);
			if(curr_gate != nullptr)
			{
                if(curr_gate->get_is_variational())
                {
                    variational_gates.push_back(curr_gate);
                    for(int i_gate=0;i_gate<curr_gate->get_num_gates();i_gate++)
                    {
                        temp_gate = curr_gate->get_variational_gate(i_gate);
                        if(find(gates_used.begin(),gates_used.end(),temp_gate) == gates_used.end())
                        {
                            gates_used.push_back(temp_gate); // add gates after target have been removed
                            solver << "reg [N-1:0] " << temp_gate->get_name() << " [0:7];" << endl;
                        }
                    }
                }
            }
		}
		curr_ts_ptr = curr_ts_ptr->get_next_timeslice();
    }
    solver << "\ninitial begin" << endl;
    solver << "   source_flag_reg <= 1'b0;" << endl;
    for(int i=0;i<gates_used.size();i++){
        solver << "   $readmemb(\"" << gates_used[i]->get_name() << ".dat\", " << gates_used[i]->get_name() << ");" << endl;
        matrix_to_file(gates_used[i],N);
    }
    solver << "end\n" << endl;

    for(int i=0;i<variational_gates.size();i++)
    {
        solver << "reg [N-1:0] " << variational_gates[i]->get_name()[1] << i << " [0:7];" << endl;
        n_wavefunctions *= variational_gates[i]->get_num_gates();
    }
    psi_f_length *= static_cast<int>(pow(2,num_qubits+1)) * n_wavefunctions;

    solver << "reg [N-1:0] psi_f_temp [0:" << static_cast<int>(pow(2,num_qubits+1)-1) << "];" << endl;
    solver << "reg [N-1:0] psi_f_reg [0:" << psi_f_length-1 << "];" << endl;
    solver << "wire [N-1:0] psi_f_array [0:" << psi_f_length-1 << "];" << endl;
    solver << "assign psi_f_array[0:" << psi_f_length-1 << "] = psi_f_reg[0:" << psi_f_length-1 << "];" << endl;

    solver << endl << "variational_circuit" << variational_gates.size() << " circuit(" << endl;
    for(int i=0;i<variational_gates.size();i++)
    {
        solver << "    .v_matrix" << i << "(" << variational_gates[i]->get_name()[1] << i << ")," << endl;
    }
    solver << "    .psi_f(psi_f_temp) \n);\n" << endl;

    solver << "clock_divider clk(" << endl;
    solver << "    .fast_clock(fpga_clock)," << endl;
    solver << "    .slow_clock(shared_clock)" << endl;
    solver << ");" << endl << endl;

    // output module
    write_output(psi_f_length, N, num_qubits);
    solver << "output_" << num_qubits << "qb op" << "(" << endl;
    solver << "    .psi_f(psi_f_array)," << endl;
    solver << "    .i_clock(shared_clock)," << endl;
    solver << "    .listener_flag(listener_flag)," << endl;
    solver << "    .out(out)," << endl;
    solver << "    .parity(parity)" << endl << ");\n" << endl;

    solver << "integer i_ang = 0;" << endl;
    solver << "always @ (posedge shared_clock)" << endl;
    solver << "begin" << endl;
    solver << "    case(i_ang)" << endl;

    /// recursion ---------------------------
    int index[variational_gates.size()];
    int last_index[variational_gates.size()];
    int case_index[variational_gates.size()]; // used to index case statement
    // holds number of gates per cycle of corresponding gate
    for(int i_v=0;i_v<variational_gates.size();i_v++)
    {
        index[i_v] = 0;
        last_index[i_v] = 10; // ensure last_index[i] != index[i]
        case_index[i_v] = 1;
    }
    //cout << "case index\n";
    for(int i=0; i<variational_gates.size();i++)
    {
        for(int j=i+1;j<variational_gates.size();j++)
            case_index[i] *= variational_gates[j]->get_num_gates();
        //cout << case_index[i] << endl;
    }

    int i_var = 0;
    recursive_vqe_writer(i_var, variational_gates.size(), variational_gates, index, last_index, case_index, solver);

    solver << "    endcase" << endl;
    solver << "    i_ang = i_ang + 1;" << endl;
    solver << "end\n" << endl;
    solver << "endmodule";
    solver.close();

    return variational_gates.size();
}


void VQE::recursive_vqe_writer(int i_var, int n_var, vector<Gate*> variational_gates, int index[], int last_index[], int case_index[],ofstream& solver)
{
    int case_number;
    int vector_size = static_cast<int>(pow(2,num_qubits+1));
    if(i_var < n_var)
    {
        for(int i=0;i<variational_gates[i_var]->get_num_gates();i++)
        {
            index[i_var] = i;
            recursive_vqe_writer(i_var+1,n_var,variational_gates,index,last_index,case_index,solver);

            /// Only print on inner-most nested loop
            if(i_var == n_var-1)
            {
                case_number = get_case_number(n_var,index,case_index);
                solver << "        " << case_number*2 << ": begin" << endl;
                for(int j=0;j<n_var;j++)
                {
                    if(index[j] != last_index[j])
                    {
                        solver << "            " << variational_gates[j]->get_name()[1] << j << "[0:7] <= ";
                        solver << variational_gates[j]->get_variational_gate(index[j])->get_name() << "[0:7];" << endl;
                        last_index[j] = index[j];
                    }
                }
                solver << "        end" << endl;
                solver << "        " << case_number*2 +1 << ": begin" << endl;
                solver << "            psi_f_reg[" << case_number*vector_size << ":" << (case_number+1)*vector_size - 1  ;
                solver << "] <= psi_f_temp[0:" << vector_size-1 << "];" << endl;
                solver << "        end" << endl << endl;
            }
        }
        // needs to be innermost nested loop b/c arrays were passed by ref.
        if(index[0] == case_index[0]-1 && i_var == n_var-1)
        {
            solver << "        " << case_number*2 +2 << ": begin" << endl;
            solver << "            source_flag_reg <= 1'b1;" << endl;
            solver << "        end" << endl << endl;
        }
    }
    else return;
}

int VQE::get_case_number(int N, int index[], int num_gates[])
{
    int sum=0;
    for(int i=0;i<N;i++)
        sum += index[i] * num_gates[i];
    return sum;
}

#endif // VQE_CPP
