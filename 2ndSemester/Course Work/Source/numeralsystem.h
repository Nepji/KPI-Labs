#ifndef NUMERALSYSTEM_H
#define NUMERALSYSTEM_H

#include <QMainWindow>
#include <vector>

using namespace std;

namespace Ui
{
  class NumeralSystem;
}

class NumeralSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit NumeralSystem(QWidget *parent = nullptr);
    ~NumeralSystem();



signals:
    void defoultcalculator();

private slots:

    void number();
    void on_defoultcalculator_swap_triggered();
    void on_pushButton_reset_clicked();
    void on_pushButton_equ_clicked();
    void FN2lock();

    void FN10_Operation();
    void FN2_Operation();
    void FN8_Operation();

    void on_actionNew_Pic_triggered();

private:
    int FromCon;
    int ToCon;
    int Value;
    int temp;

    Ui::NumeralSystem *ui;

    bool finished;
    bool error= false;
    vector<int> TempVec;


};

#endif // NUMERALSYSTEM_H
