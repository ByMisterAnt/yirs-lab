#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "solvesystem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->input_K_value->setValidator(new QRegExpValidator(QRegExp("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$"), this));
    ui->input_T2_value->setValidator(new QRegExpValidator(QRegExp("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$"), this));
    ui->input_omega_value->setValidator(new QRegExpValidator(QRegExp("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$"), this));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_run_calc_btn_clicked()
{
    solveSystem f1;


    if (ui->first_system->isChecked())
    {
        f1.calculate(1, (ui->input_K_value->text()).toDouble(), (ui->input_T2_value->text()).toDouble(), (ui->input_omega_value->text()).toDouble());
    }
    if (ui->second_system->isChecked())
    {
        f1.calculate(2, (ui->input_K_value->text()).toDouble(), (ui->input_T2_value->text()).toDouble(), (ui->input_omega_value->text()).toDouble());
    }

    setup_plot(f1.time_values, f1.u_values, f1.y_values);

    f1.time_values.clear();
    f1.u_values.clear();
    f1.y_values.clear();

}


void MainWindow::on_savePlot_btn_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Выберите формат для сохранения файла"), QString(),
                                            tr("PNG(*.png);;JPG(*.jpg);;PDF(*.pdf);;BMP(*.bmp);;All Files(*)"));

    if(!fileName.isEmpty())
    {

        if(fileName.endsWith(".png", Qt::CaseInsensitive))
        {
            ui->ourPlot->savePng(fileName);
        }

        else if(fileName.endsWith(".jpg", Qt::CaseInsensitive))
        {
            ui->ourPlot->saveJpg(fileName);
        }

        else if(fileName.endsWith(".pdf", Qt::CaseInsensitive))
        {
            ui->ourPlot->savePdf(fileName);
        }

        else if(fileName.endsWith(".bmp", Qt::CaseInsensitive))
        {
            ui->ourPlot->saveBmp(fileName);
        }

        else
        {
            fileName += ".png";
            ui->ourPlot->savePng(fileName);
        }

    }
}

void MainWindow::setup_plot(std::vector<double> &x_values, std::vector<double> &y1_values, std::vector<double> &y2_values)
{
    ui->ourPlot->clearGraphs();
    ui->ourPlot->addGraph();
    ui->ourPlot->graph(0)->setData(QVector<double>::fromStdVector(x_values), QVector<double>::fromStdVector(y1_values));
    ui->ourPlot->graph(0)->setPen(QPen(Qt::red, 2));

    /*ui->ourPlot->addGraph();
    ui->ourPlot->graph(1)->setData(QVector<double>::fromStdVector(x_values), QVector<double>::fromStdVector(y2_values));
    ui->ourPlot->graph(1)->setPen(QPen("blue"));*/


    ui->ourPlot->xAxis->setLabel("Время, с");
    ui->ourPlot->yAxis->setLabel("Угол тангажа, °");

    ui->ourPlot->xAxis->setRange(ui->xmin_value_3->text().toDouble(), ui->xmax_value_3->text().toDouble());
    ui->ourPlot->yAxis->setRange(ui->ymin_value_3->text().toDouble(), ui->ymax_value_3->text().toDouble());

    ui->ourPlot->xAxis->setLabelFont(QFont(QFont().family(), 14));
    ui->ourPlot->yAxis->setLabelFont(QFont(QFont().family(), 14));

    ui->ourPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 14));
    ui->ourPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 14));

    ui->ourPlot->setInteraction(QCP::iRangeZoom, true);
    ui->ourPlot->setInteraction(QCP::iRangeDrag,true);
    ui->ourPlot->setInteraction(QCP::iSelectPlottables,true);
    ui->ourPlot->replot();
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->ourPlot->xAxis->setRange(ui->xmin_value_3->text().toDouble(), ui->xmax_value_3->text().toDouble());
    ui->ourPlot->yAxis->setRange(ui->ymin_value_3->text().toDouble(), ui->ymax_value_3->text().toDouble());
    ui->ourPlot->replot();
}

