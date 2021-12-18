#ifndef GNUPLOTTER_H
#define GNUPLOTTER_H

class GPlotter
{

public:

  void show();

  void write(const std::vector<double> &line1, const std::vector<double> &line2);

  virtual ~GPlotter()
  {
    remove( "test.dat" );
  }

};


void GPlotter::show()
{

  #ifdef _WIN32
    FILE *gp = _popen("gnuplot -persist","w");
  #else
    FILE* gp = popen("gnuplot -persist", "w");
  #endif

  if (gp == NULL)
  {

  printf("Error opening pipe to GNU plot.\n");
  exit(0);

  }

  fprintf(gp, "set title 'Sine control plot'\nset nokey\nset grid\nset xlabel 'Time, sec'\nset ylabel 'Output signal'\n");
  fprintf(gp, "set multiplot\nplot 'test.dat' using 1:2 with lines lt rgb 'red' lw 1, \n");

  _pclose(gp);


}

void GPlotter::write(const std::vector<double> &line1, const std::vector<double> &line2)
{
    //FILE* fp = fopen("test.dat", "w");
    FILE* fp;
    fopen_s(&fp, "test.dat", "w");

  for (int i = 0; i < line1.size(); i++)
  {

    fprintf(fp,"%f\t%f\n", line1[i], line2[i]);

  }

  fclose(fp);

}

#endif GNUPLOTTER_H