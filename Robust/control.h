#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <math.h>
#include <vector>
#include <array>
#include <algorithm>

//---------------aperiodic--------------------------------
class aperiodic
{
public:
  double one_div_T = 0.0;
  double k = 0.0;
  double dt = 0.1;
  double y0 = 0.0;

  void set_values(double one_div_T, double k, double dt, double y0)
  {

    this->one_div_T = one_div_T;
    this->k = k;
    this->dt = dt;
    this->y0 = y0;

  }

  void aperiodic_solver(double u)
  {

      y0 = y0 + (dt) * (one_div_T) * ((k) * (u)-(y0));

  }
};
//-------------------------------------------------------------------


//---------------- integral -----------------------------------------
class integral
{
public:
    double dt = 0.1;
    double y0 = 0.0;

    void set_values(double dt, double y0)
    {

        this->dt = dt;
        this->y0 = y0;

    }

    void integral_solver(double u)
    {
        y0 = y0 + dt * u;

    }
};
//-------------------------------------------------------------------

//---------------- diff -----------------------------------------
class diff
{
public:
    double err = 0.0, D = 0.0, prevErr = 0.0, setpoint = 0.0, dt = 0.1;

    void set_values(double dt, double prevErr)
    {
        this->dt = dt;
        this->prevErr = prevErr;
    }
    void calc_diff(double u)
    {
        D = (u - prevErr) / dt;
        prevErr = u;
    }
};
//-------------------------------------------------------------------

//---------------- coleb -----------------------------------------
class coleb
{
public:
    double dt = 0.1;
    double y01 = 0.0, y02 = 0.0;
    double Tau2 = 0.0, K = 0.0, Tau = 0.0;

    void set_values(double dt, double y01, double y02, double Tau2, double K, double Tau)
    {

        this->dt = dt;
        this->y01 = y01;
        this->y02 = y02;
        this->Tau2 = Tau2;
        this->K = K;
        this->Tau = Tau;

    }

    void coleb_solver(double u)
    {
        y01 = y01 + dt * (y02);
        y02 = y02 + dt * (-Tau*y02 - y01 + K*u)/Tau2;

    }
};
//-------------------------------------------------------------------

//------------------------ randomizer -------------------------------
inline double rand_noize(double u)
{
    if (u == 0)
    {
        return (double)(rand() - RAND_MAX * 0.5) / (RAND_MAX * 0.5);
    }
    else
    {
        double v = (double)(rand() - RAND_MAX * 0.5) / (RAND_MAX * 0.5);

        return v * 0.05 * u;
    }  
}

//---------------- primary filter -----------------------------------
inline double primary_filter(std::array<double, 8> &f, double new_val)
{
    //shit code, but otherwise it is difficult
    double sum = 0;

    std::array<double, 8> f2;

    for (int i = 0; i < f.size(); i++)
    {
        f2[i] = f[i];
    }

    for (int i = f.size() - 2; i >= 0; i--)
    {
        f[i + 1] = f[i];
    }

    // add new value
    f[0] = new_val;

    //sort array
    std::sort(f2.begin(), f2.end());

    for (int i = 2; i < f2.size()-2; i++)
    {
        sum += f2[i];
    }

    return sum / (f2.size() - 4);
}
//-------------------------------------------------------------------

//---------------- deadzone -----------------------------------------
inline void deadzone(double &u, double zone)
{
    if (std::abs(u) < zone) u = 0;
}
//-------------------------------------------------------------------

//---------------- saturation -----------------------------------------
inline void saturation(double &u, double zone_min, double zone_max)
{
    if (u < zone_min) u = zone_min;
    else if (u > zone_max) u = zone_max;
}
//-------------------------------------------------------------------

//---------------- PID -----------------------------------------
class PID
{
public:
    integral integr;
    diff df;
    double Kp, Kd, Ki;
    double y0;

    void set_values(double Kp, double Ki, double Kd, double dt)
    {
        this->Kp = Kp;
        this->Ki = Ki;
        this->Kd = Kd;
        df.set_values(dt, 0.0);
        integr.set_values(dt, 0.0);
    }
    void calc_u(double u)
    {
        integr.integral_solver(u*Ki);
        df.calc_diff(u*Kd);

        y0 = integr.y0 + df.D + Kp*u;
    }
};
//-------------------------------------------------------------------

#endif // CONTROL_H
