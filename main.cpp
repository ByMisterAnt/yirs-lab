#include <iostream>
#include <math.h>
#include <vector>
#include <array>
#include <algorithm>

#include "control.h"
#include "GNUplotter.h"

#define SIM_TIME 20

int main(int argc, char const *argv[]) {

  //transfer functions
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
  double T2 = 0.1;

  double dt = 0.01;

  //----------------------------------------------------------------

  //step)
  double u = 0;

  //error initialization
  double error = 0;

  //white noize
  double noize = 0;

  //-------------------- filters & its values -----------------------------
  // F1, primary filter
  std::array<double, 8> F1;

  //init value of centering
  double centering = 0;


  //----------------------------------------------------------------
  

  //output signal and time values
  std::vector<double> y_values;
  std::vector<double> time_values;
  std::vector<double> u_values;

  //set values for 2 aperiodics and 1 integral
  W1.set_values(1/T1, k1, dt, y01);
  W2.set_values(1/T2, k2, dt, y02);
  W3.set_values(dt, y03);

  //set gain after OY
  double K = 1.5;

  //------------------- centering loop -------------------------------

  for (int i = 0; i < 1000; i++)
  {

      noize = rand_noize(0);

      centering += noize;

      if (i >= 992)
      {
          F1[i - 992] = noize;
      }
  }

  centering = centering / 1000;

  //------------------------------------------------------------------
  
  //------------------- main loop -------------------------------------
  for (int i = 0; i < int(SIM_TIME/dt); i++)
  {
      
      u = std::sin(1.2 * i * dt);
      
      // feedback
      error = u - W3.y0;
      
      aperiodic_solver(&W1, K * error);
      
      noize = W1.y0 - centering + rand_noize(W1.y0);

      W2.y0 = primary_filter(F1, noize);

      aperiodic_solver(&W2, W2.y0);

      deadzone(&W2.y0, 0.01);

      integral_solver(&W3, W2.y0);
      
     
      y_values.push_back(W1.y0);

      u_values.push_back(u);

      time_values.push_back(double(i * dt));

  }
  //----------------------------------------------------------------

  //plot

  GPlotter plot;

  plot.write(time_values, u_values, y_values);
  plot.show();

  y_values.clear();
  time_values.clear();

  return 0;
}
