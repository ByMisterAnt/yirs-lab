#include "solvesystem.h"

solveSystem::solveSystem()
{

}

void solveSystem::calculate (int systemType, double K, double T2, double omega)
{

    pid.set_values(K, T2, omega, dt);
    W1.set_values(1/0.03, 25, dt, 0.0);
    W3.set_values(dt, 0.0);
    W4.set_values(dt, 0.0);
    W5.set_values(dt, 0.0, 0.0, Ta2, -Kc, 2*Ta*ksi);

    W7.set_values(1/0.03, 1, dt, 0.0);

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
        u = 1;
        // feedback
        error = u - W4.y0;
        error = -error + (1.0288*W5.y01+W6.D);

        pid.calc_u(error);
        // <привод
        W1.aperiodic_solver((pid.y0 - W3.y0));
        saturation(W1.y0, -25, 25);
        W3.integral_solver(W1.y0);
        // привод>

        // <самолет
        W5.coleb_solver(W3.y0);
        W6.calc_diff(W5.y01);
        // получаем тангаж
        W4.integral_solver((1.0288*W5.y01+W6.D));

        // сохраняем данные
        u_values.push_back(W4.y0);
        time_values.push_back(double(i * dt));
    }
}

void solveSystem::second_system(double K, double omega)
{
    for (int i = 0; i < int(sim_time/dt); i++)
    {
        u = 1;
        // feedback
        error = u - W4.y0 - 0.55*rand_noize(W4.y0);
        error = -error + (1.0288*W5.y01+W6.D) - rand_noize(1.0288*W5.y01+W6.D);

        pid.calc_u(error);
        // <привод
        W1.aperiodic_solver((pid.y0 - W3.y0));
        saturation(W1.y0, -25, 25);
        W3.integral_solver(W1.y0);
        // привод>

        // <самолет
        W5.coleb_solver(W3.y0);
        W6.calc_diff(W5.y01);
        // получаем тангаж
        W4.integral_solver((1.0288*W5.y01+W6.D));

        // сохраняем данные
        u_values.push_back(W4.y0);
        //u_values.push_back(rand_noize(W4.y0));
        time_values.push_back(double(i * dt));
    }
}
