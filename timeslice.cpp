#ifndef TIMESLICE_CPP
#define TIMESLICE_CPP


#include "timeslice.h"
#include "gate.h"
#include <stdexcept>
#include <iostream>

using namespace std;

// constructor
Timeslice::Timeslice(int num_qb)
{
        num_qubits = num_qb;
        next_timeslice = nullptr;

        qubit_gates = new Gate*[num_qb];
        for(int i=0;i<num_qubits;i++)
            {qubit_gates[i] = nullptr;}
}

// destructor
Timeslice::~Timeslice()
{
        delete [] qubit_gates;
}

Gate* Timeslice::get_gate(int qubit)
{
        return this->qubit_gates[qubit];
}

void Timeslice::set_gate(int qubit, Gate* new_gate)
{
    if(qubit < num_qubits && qubit >= 0)
    {
        if(this->get_gate(qubit) == nullptr)
            {this->qubit_gates[qubit] = new_gate; }
        else
            { throw invalid_argument("Invalid Argument: Qubit already has gate for current timeslice"); }
    }
    else
    {
            cout << "Error: qubit " << qubit << endl;
            throw invalid_argument("Invalid argument: Gate applied to invalid qubit number.  Valid arguments between zero and num_qubits-1.");}
}

Timeslice* Timeslice::get_next_timeslice()
{
    return this->next_timeslice;
}

void Timeslice::set_next_timeslice(Timeslice* next)
{
    this->next_timeslice = next;
}


#endif
