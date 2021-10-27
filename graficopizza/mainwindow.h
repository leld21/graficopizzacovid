#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <iostream>
#include <string>
#include <QLabel>
#include <QApplication>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    string a [5];
};


class Sintomas
{
protected:
string sintomas[30000];
public:
void separar (int *n);

void setsintomas (string s,int *n);

};

//as variaveis estão publicas pois dificultaria muito deixá-las privadas
class Dados: public Sintomas{

public:
int ateonde;
string sintunic[50];
int quant[50];

void pegaunicos (int *n);

void buscaquant (int *n);

void ordena ();
};


#endif // MAINWINDOW_H
