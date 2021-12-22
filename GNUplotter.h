#ifndef GNUPLOTTER_H
#define GNUPLOTTER_H

class GPlotter
{

public:

  void show();

  void write(const std::vector<double>& line1, const std::vector<double>& line2, const std::vector<double>& line3);

  virtual ~GPlotter()
  {
    remove( "test.dat" );
  }

};


void GPlotter::show()
{
    FILE *gp = _popen("gnuplot -persist","w");

    if (gp == NULL)
    {

    printf("Error opening pipe to GNU plot.\n");
    exit(0);

    }

    fprintf(gp, "set title ' '\nset nokey\nset grid\nset xlabel 'Time, sec'\nset ylabel 'Output signal'\n");
    fprintf(gp, "set multiplot\nplot 'test.dat' using 1:2 with lines lt rgb 'red' lw 1, 'test.dat' using 1:3 with lines lt rgb 'blue' lw 1\n");

    _pclose(gp);


}

void GPlotter::write(const std::vector<double> &line1, const std::vector<double> &line2, const std::vector<double> &line3)
{

    FILE *fp;

    fopen_s(&fp, "test.dat", "w");

    for (int i = 0; i < line1.size(); i++)
    {
        fprintf(fp,"%f\t%f\t%f\t%f\n", line1[i], line2[i], line3[i]);
    }

    fclose(fp);

}

#endif GNUPLOTTER_H