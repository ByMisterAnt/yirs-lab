#ifndef SOLVESYSTEM_H
#define SOLVESYSTEM_H

#include <iostream>
#include <math.h>
#include <vector>
#include <array>
#include <algorithm>

#include "control.h"

class solveSystem
{
public:

    solveSystem();

    void calculate(int systemType, double K, double T2, double omega);

    //output signal and time values
    std::vector<double> y_values;
    std::vector<double> time_values;
    std::vector<double> u_values;

    // PID
    PID pid;

private:

    double sim_time = 40;

    //aperiodic tf
    aperiodic W1;
    aperiodic W2;
    aperiodic W7;


    //integrator
    integral W3;
    integral W4;

    //coleb
    coleb W5;

    // diff
    diff W6;

    //--------------------tf's coefficients---------------------------
    double k1 = 25;
    double k2 = 1;

    double y01 = 0;
    double y02 = 0;
    double y03 = 0, y04 = 0;

    double T1 = 0.45;

    double dt = 0.001;

    double Kc = 0.3307, ksi = 0.3844, Ta2 = 0.9720*0.9720, Ta = 0.9720;
    //----------------------------------------------------------------

    //sine init value
    double u = 0;

    //error initialization
    double error = 0;

    //white noize
    double noize = 0;

    //-------------------- filters & its values -----------------------------

    // F1, medium filter
    std::array<double, 8> F1;

    //init value of centering
    double centering = 0;

    //----------------------------------------------------------------

    void centering_loop(int N);
    void first_system(double K, double omega);
    void second_system(double K, double omega);


};

#endif // SOLVESYSTEM_H
