#ifndef TIMESLICE_H
#define TIMESLICE_H

#include "gate.h"

class Timeslice
{
    private:
        int num_qubits;
        Gate **qubit_gates; // pointer to array of pointers to Gate object
        Timeslice* next_timeslice;

    public:
        Timeslice(){};
        Timeslice(int);
        ~Timeslice();

        Gate* get_gate(int);
        void set_gate(int, Gate*);

        Timeslice* get_next_timeslice();
        void set_next_timeslice(Timeslice*);
};

#endif

