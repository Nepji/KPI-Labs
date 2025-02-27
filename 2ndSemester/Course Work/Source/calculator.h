#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <vector>
#include "numeralsystem.h"

QT_BEGIN_NAMESPACE

namespace Ui { class Calculator; }
using namespace std;

QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();


signals:


private:
    Ui::Calculator *ui;
    NumeralSystem *numeralsys;
    double Value;
    double temp;

    bool finished;
    vector<double> ValuesVec;
    vector<QString> OperationVec;
    int indicator = 0;
    int NumberOfBrace = 0;
    int OpEnd = 0;
    int OpStart = 0;
    int OpPlus = 0;
    int elementsInside = 0;
    bool error = false;




private slots:
    void number();
    void numberWithPoint();

    void operation();

    void equ_solution();
    void equ_solution_res();

    void TrigoNfunction();
    void Nfunction();

    void on_pushButton_per_clicked();
    void on_pushButton_factorial_clicked();
    void on_pushButton_root_clicked();
    void on_pushButton_pi_clicked();
    void on_pushButton_EXP_clicked();
    void on_pushButton_e_clicked();
    void on_pushButton_reset_clicked();
    void on_pushButton_pow_clicked();

    void on_pushButton_openbrace_clicked();
    void on_pushButton_closebrace_clicked();
    void on_pushButton_equ_clicked();

#endif // CALCULATOR_H


    void on_actionnumeral_system_2_triggered();
};
