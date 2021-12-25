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

private:

    double sim_time = 25;

    //aperiodic tf
    aperiodic W1;
    aperiodic W2;

    //integrator
    integral W3;

    //--------------------tf's coefficients---------------------------
    double k1 = 0.75;
    double k2 = 1;

    double y01 = 0;
    double y02 = 0;
    double y03 = 0;

    double T1 = 0.45;

    double dt = 0.01;

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
