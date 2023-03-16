#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QErrorMessage>
#include <qcustomplot.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_run_calc_btn_clicked();

    void on_savePlot_btn_clicked();

    void on_pushButton_2_clicked();

private:

    Ui::MainWindow *ui;

    QCustomPlot *sysPlot;

    void setup_plot(std::vector<double> &x_values, std::vector<double> &y1_values, std::vector<double> &y2_values);

};
#endif // MAINWINDOW_H
