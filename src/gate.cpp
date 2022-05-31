#ifndef GATE_CPP
#define GATE_CPP

#include <string>
#include "gate.h"

using namespace std;

Gate::Gate(int n_qb, int index)
{
	num_qubits = n_qb;
	matrix_index = index;
	is_variational = false;
	angle = 0.0;
}

void Gate::set_num_qubits(int qb)
{ this->num_qubits = qb;}

int Gate::get_num_qubits()
{ return num_qubits;}


void Gate::set_matrix_index(int index)
{this->matrix_index = index;}

int Gate::get_matrix_index()
{ return this->matrix_index;}


void Gate::set_name(string _name)
{
    size_t len = _name.copy(this->name,15,0);
    this->name[len] = '\0';
}
char* Gate::get_name()
{return this->name;}


void Gate::set_is_variational(bool vari_bool)
{this->is_variational = vari_bool;}

bool Gate::get_is_variational()
{return this->is_variational;}


void Gate::set_variational_gate(Gate* new_gate)
{
    this->variational_gates.push_back(new_gate);
}

Gate* Gate::get_variational_gate(int index)
{
    return this->variational_gates[index];
}

int Gate::get_num_gates()
{
    return this->variational_gates.size();
}


void Gate::set_angle(double _angle)
{this->angle = _angle;}

double Gate::get_angle()
{return this->angle;}

#endif
