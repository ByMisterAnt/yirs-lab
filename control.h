#ifndef CONTROL_H
#define CONTROL_H

//---------------aperiodic--------------------------------
struct aperiodic
{

  double one_div_T = 0.0;
  double k = 0.0;
  double dt = 0.0;
  double y0 = 0.0;

  void set_values(double one_div_T, double k, double dt, double y0)
  {

    this->one_div_T = one_div_T;
    this->k = k;
    this->dt = dt;
    this->y0 = y0;

  }
};

void aperiodic_solver(aperiodic *W, double u)
{

    W->y0 = W->y0 + (W->dt) * (W->one_div_T) * ((W->k) * (u) - (W->y0));
  
}
//-------------------------------------------------------------------


//---------------- integral -----------------------------------------
struct integral
{

    double dt = 0.0;
    double y0 = 0.0;

    void set_values(double dt, double y0)
    {

        this->dt = dt;
        this->y0 = y0;

    }
};

void integral_solver(integral *W, double u)
{
    W->y0 = W->y0 + W->dt * u;

}
//-------------------------------------------------------------------

//randomizer
double rand_noize(double u)
{
    if (u == 0)
    {
        return (double)(rand() - RAND_MAX / 2) / (RAND_MAX / 2);
    }
    else
    {
        double v = (double)(rand() - RAND_MAX / 2) / (RAND_MAX / 2);

        return v * 0.05 * u;
    }  
}

//---------------- primary filter -----------------------------------
double primary_filter(std::array<double, 8> &f, double new_val)
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

    return sum / f2.size();
}
//-------------------------------------------------------------------

//---------------- deadzone -----------------------------------------
void deadzone(double *u, double zone)
{
    if (std::abs(*u) < zone) *u = 0;
}
//-------------------------------------------------------------------

#endif // CONTROL_H
