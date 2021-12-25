#include "solvesystem.h"

solveSystem::solveSystem()
{

}

void solveSystem::calculate (int systemType, double K, double T2, double omega)
{

    W1.set_values(1/T1, k1, dt, y01);
    W2.set_values(1/T2, k2, dt, y02);
    W3.set_values(dt, y03);


    if (systemType == 1)
    {
        first_system(K, omega);
    }

    else
    {
        centering_loop(1000);
        second_system(K, omega);
    }

}

void solveSystem::centering_loop(int N)
{
    for (int i = 0; i < N; i++)
    {

        noize = rand_noize(0);

        centering += noize;

        if (i >= 992)
        {
            F1[i - 992] = noize;
        }
    }

    centering = centering / 1000;
}

void solveSystem::first_system(double K, double omega)
{
    for (int i = 0; i < int(sim_time/dt); i++)
    {

        u = std::sin(omega * i * dt);

        W1.aperiodic_solver(K * u);

        y_values.push_back(W1.y0);

        u_values.push_back(u);

        time_values.push_back(double(i * dt));

    }
}

void solveSystem::second_system(double K, double omega)
{
    for (int i = 0; i < int(sim_time/dt); i++)
    {

        u = std::sin(omega * i * dt);

        // feedback
        error = u - W3.y0;

        W1.aperiodic_solver(K * error);

        noize = W1.y0 - centering + rand_noize(W1.y0);

        W2.y0 = primary_filter(F1, noize);

        W2.aperiodic_solver(W2.y0);

        deadzone(&W2.y0, 0.01);

        W3.integral_solver(W2.y0);


        y_values.push_back(W1.y0);

        u_values.push_back(u);

        time_values.push_back(double(i * dt));

    }

}
