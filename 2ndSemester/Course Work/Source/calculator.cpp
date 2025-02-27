#include "calculator.h"
#include "./ui_calculator.h"
#include <vector>
#include <math.h>
#include <QMessageBox>
#include "numeralsystem.h"

double tempValue;
using namespace std;

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    numeralsys = new NumeralSystem();
    connect(numeralsys, &NumeralSystem::defoultcalculator, this, &Calculator::show);

    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_six,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_seven,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_eight,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_nine,SIGNAL(clicked()),this,SLOT(number()));

    connect(ui->pushButton_point,SIGNAL(clicked()),this,SLOT(numberWithPoint()));

    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(operation()));
    connect(ui->pushButton_min,SIGNAL(clicked()),this,SLOT(operation()));
    connect(ui->pushButton_mult,SIGNAL(clicked()),this,SLOT(operation()));
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(operation()));

    connect(ui->pushButton_cos,SIGNAL(clicked()),this,SLOT(TrigoNfunction()));
    connect(ui->pushButton_sin,SIGNAL(clicked()),this,SLOT(TrigoNfunction()));
    connect(ui->pushButton_tan,SIGNAL(clicked()),this,SLOT(TrigoNfunction()));
    connect(ui->pushButton_csc,SIGNAL(clicked()),this,SLOT(TrigoNfunction()));
    connect(ui->pushButton_sec,SIGNAL(clicked()),this,SLOT(TrigoNfunction()));
    connect(ui->pushButton_log,SIGNAL(clicked()),this,SLOT(Nfunction()));
    connect(ui->pushButton_In,SIGNAL(clicked()),this,SLOT(Nfunction()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::number()
{
    if(finished==true)
    {
      Calculator::on_pushButton_reset_clicked();
    }

    QPushButton *button = (QPushButton* ) sender();
    Value = ((ui->shower->text()+button->text()).toDouble());

    QString update;
    update = QString::number(Value, 'g', 9);
    ui->shower->setText(update);
}

void Calculator:: numberWithPoint()
{
    if(ui->shower->text().contains('.') == false)
    {
       ui->shower->setText(ui->shower->text()+".");
    }
}

void Calculator::on_pushButton_per_clicked()
{
    if(ui->shower->text() != "")
    {
        Value = Value*0.01;
        ui->history->setText(ui->history->text()+ui->shower->text()+"%");
        ui->shower->setText("");
    }
}

int factorial(int i)
{
  if (i==0) return 1;
  else return i*factorial(i-1);
}
void Calculator::on_pushButton_factorial_clicked()
{
   if(ui->shower->text() != "")
   {
       Value = factorial((int)Value);
       ui->history->setText(ui->history->text()+ui->shower->text()+"!");
       ui->shower->setText("");
   }
}

void Calculator::Nfunction()
{
    if(finished==true)
        Calculator::on_pushButton_reset_clicked();
    if(ui->history->text().isEmpty()==false)
    {
        QString Check = ui->history->text();
        if((Check.back()!='+' && Check.back()!='-' && Check.back()!='/' && Check.back()!='*'))
        {
            ValuesVec.push_back(Value);
            OperationVec.push_back("*");
            ui->history->setText(ui->history->text()+"*");
        }
    }

    QPushButton *button = (QPushButton* ) sender();
    button->setCheckable(true);
    if(ui->shower->text() == "") return;

    if(ui->pushButton_In->isCheckable())
    {
        ui->history->setText(ui->history->text()+"ln");
        Value = log(ui->shower->text().toDouble());
    }
    else if(ui->pushButton_log->isCheckable())
    {
        if(ui->shower->text().toDouble()==0)
        {
            QMessageBox::information(this,"Error","Unable to find logarithm of 0");
            Calculator::on_pushButton_reset_clicked();
            error=true;
        }
        else
        {
            ui->history->setText(ui->history->text()+"log");
            Value = log10(ui->shower->text().toDouble());
        }
    }

    if(error!=true)
    {
        ui->history->setText(ui->history->text()+ui->shower->text());
        ui->shower->setText("");
    }
    button->setCheckable(false);

}

void Calculator::TrigoNfunction()
{
    if(ui->pushButton_pow->isCheckable() == true)
    {

    }
    if(ui->shower->text() == "") return;

    double temp = ui->shower->text().toDouble();
    if(finished==true)
        Calculator::on_pushButton_reset_clicked();

    if(ui->history->text().isEmpty()==false)
    {
        QString Check = ui->history->text();
        if((Check.back()!='+' && Check.back()!='-' && Check.back()!='/' && Check.back()!='*' && Check.back()!= '('))
        {
            ValuesVec.push_back(Value);
            OperationVec.push_back("*");
            ui->history->setText(ui->history->text()+"*");
        }
    }

    QPushButton *button = (QPushButton* ) sender();
    button->setCheckable(true);
    if(ui->radioButton_Rad->isChecked())
        temp = temp * 180/3.14;

    if(ui->pushButton_tan->isCheckable())
    {
        ui->history->setText(ui->history->text()+"tan");
        Value = tan(temp);
    }
    else if(ui->pushButton_cos->isCheckable())
    {
        ui->history->setText(ui->history->text()+"cos");
        Value = cos(temp);
    }
    else if(ui->pushButton_sin->isCheckable())
    {
        ui->history->setText(ui->history->text()+"sin");
        Value = sin(temp);
    }
    else if(ui->pushButton_sec->isCheckable())
    {
        ui->history->setText(ui->history->text()+"sec");
        Value = 1/cos(temp);
    }
    else if(ui->pushButton_csc->isCheckable())
    {
        ui->history->setText(ui->history->text()+"csc");
        Value = 1/sin(temp);
    }
    ui->history->setText(ui->history->text()+ui->shower->text());
    ui->shower->setText("");
    button->setCheckable(false);

}

void Calculator::on_pushButton_root_clicked()
{
    if(ui->shower->text() == "") return;

    ui->history->setText(ui->history->text()+"√"+ui->shower->text());
    Value = sqrt(ui->shower->text().toDouble());
    ui->shower->setText("");
}

void Calculator::on_pushButton_pow_clicked()
{
    if(ui->pushButton_pow->isCheckable() == true)
    {
        ui->history->setText(ui->history->text()+ui->shower->text());
        Value = pow(temp, Value);
        ui->shower->setText("");
        ui->pushButton_pow->setCheckable(false);
    }
    else
    {
        temp = Value;
        ui->history->setText(ui->history->text()+ui->shower->text()+"^");
        ui->shower->setText("");
        ui->pushButton_pow->setCheckable(true);
    }
}

void Calculator::on_pushButton_pi_clicked()
{
    Value = 3.1415;

    QString update;
    update = QString::number(Value);
    ui->shower->setText(update);
}

void Calculator::operation()
{
    if(ui->pushButton_pow->isCheckable() == true)
    {
        Calculator::on_pushButton_pow_clicked();
    }

    QPushButton *button = (QPushButton* ) sender();
    if(ui->history->text().isEmpty() == false &&
       ui->shower->text().isEmpty())
    {
        QString Check = ui->history->text();
        if((Check.back()=='+' || Check.back()=='-' || Check.back()=='/' || Check.back()=='*'))
        {
            OperationVec.pop_back();
            Check.replace(Check.size()-1,1,button->text());
            ui->history->setText(Check);
        }
        else
        {
            ui->history->setText(ui->history->text()+ui->shower->text()+button->text());
            ValuesVec.push_back(Value);
        }
    }
    else
    {
        ui->history->setText(ui->history->text()+ui->shower->text()+button->text());
        ValuesVec.push_back(Value);
    }
    ui->shower->setText("");
    OperationVec.push_back(button->text());
    button->setCheckable(false);
}

void Calculator::on_pushButton_EXP_clicked()
{
    if(ui->shower->text() != "")
    {
        ui->history->setText(ui->history->text()+"exp"+ui->shower->text());
        Value = exp(ui->shower->text().toDouble());
        ui->shower->setText("");
    }
}

void Calculator::on_pushButton_e_clicked()
{
    Value = 2.718;
    QString update;
    update = QString::number(Value);
    ui->shower->setText(update);
}

void Calculator::on_pushButton_openbrace_clicked()
{
    if(finished==true)
        Calculator::on_pushButton_reset_clicked();

    indicator++;
    ui->history->setText(ui->history->text()+"(");
    OperationVec.push_back("(");
    NumberOfBrace++;
}

void Calculator::on_pushButton_closebrace_clicked()
{
    if(ui->pushButton_pow->isCheckable() == true)
    {
        Calculator::on_pushButton_pow_clicked();
    }
    if(finished==true)
        Calculator::on_pushButton_reset_clicked();

    indicator--;
    ui->history->setText(ui->history->text()+ui->shower->text()+")");
    Value = ui->shower->text().toDouble();
    ui->shower->setText("");
    OperationVec.push_back(")");
    NumberOfBrace++;
}

void Calculator::on_pushButton_reset_clicked()
{
    ValuesVec.clear();
    OperationVec.clear();

    ui->history->setText("");
    ui->shower->setText("0");

    NumberOfBrace = indicator = 0;

    finished=false;
    error=false;
}

void Calculator::on_pushButton_equ_clicked()
{
    if(ui->pushButton_pow->isCheckable() == true)
    {
        Calculator::on_pushButton_pow_clicked();
    }

        QPushButton *button = (QPushButton* ) sender();
        if(ui->history->text().isEmpty()==false &&
           ui->shower->text().isEmpty())
        {
            QString Check = ui->history->text();
            if((Check.back()=='+' ||
              Check.back()=='-' ||
              Check.back()=='/' ||
              Check.back()=='*'))
            {
                OperationVec.pop_back();
                Check.replace(Check.size()-1,1,button->text());
                ui->history->setText(Check);
            }
            else
            {
                ui->history->setText(ui->history->text()+ui->shower->text());
                ValuesVec.push_back(Value);
            }
        }
        else
        {
            ui->history->setText(ui->history->text()+ui->shower->text());
            ValuesVec.push_back(Value);
        }

        ui->shower->setText("");
        Calculator::equ_solution();

        if(!error)
        {
            ui->shower->setText("="+QString::number(ValuesVec[0], 'g', 10));
            finished=true;
        }
}

void Calculator::equ_solution_res()
{
    int min=0,plus=0,mult=0,div=0;

    for(int i=OpEnd;i<=OpStart;i++)
    {
        if(OperationVec[i]=='+')
            plus++;
        else if(OperationVec[i]=='-')
            min++;
        else if(OperationVec[i]=='*')
            mult++;
        else if(OperationVec[i]=='/')
            div++;
    }

    elementsInside= plus+min+mult+div;

    if(mult !=0 )
      for(int j=OpStart;j>=OpEnd;j--)
          if(OperationVec[OpEnd+j]=='*')
          {
              j-=OpPlus;
              ValuesVec[OpEnd+j+1]=ValuesVec[OpEnd+j] * ValuesVec[OpEnd+j+1];
              ValuesVec.erase(ValuesVec.begin() + j+OpEnd);
              j+=OpPlus;
              OperationVec.erase(OperationVec.begin()+j+OpEnd);
          }

    if(div !=0 )
      for(int j=OpStart;j>=OpEnd;j--)
          if(OperationVec[OpEnd+j]=='/')
          {
              if(ValuesVec[OpEnd+j+1]==0)
              {
                  QMessageBox::information(this,"Error","Division by 0 is not possible");
                  Calculator::on_pushButton_reset_clicked();
                  error=true;
              }
              else
              {
                  j-=OpPlus;
                  ValuesVec[OpEnd+j+1]=ValuesVec[OpEnd+j] / ValuesVec[OpEnd+j+1];
                  ValuesVec.erase(ValuesVec.begin() + j+OpEnd);
                  j+=OpPlus;
                  OperationVec.erase(OperationVec.begin()+j+OpEnd);
              }
          }

    if(plus !=0 )
    {
      for(int j=OpStart;j>=OpEnd;j--)
      {
        if(OperationVec[OpEnd+j] != '+') continue;

        j -= OpPlus;
        ValuesVec[OpEnd+j+1]=ValuesVec[OpEnd+j] + ValuesVec[OpEnd+j+1];
        ValuesVec.erase(ValuesVec.begin() + j+OpEnd);
        j+=OpPlus;
        OperationVec.erase(OperationVec.begin()+j+OpEnd);
      }
    }


    if(min !=0 )
      for(int j=OpStart;j>=OpEnd;j--)
          if(OperationVec[OpEnd+j]=='-')
          {
              j-=OpPlus;
              ValuesVec[OpEnd+j+1]=ValuesVec[OpEnd+j] - ValuesVec[OpEnd+j+1];
              ValuesVec.erase(ValuesVec.begin() + j+OpEnd);
              j+=OpPlus;
              OperationVec.erase(OperationVec.begin()+j+OpEnd);
          }
}

void Calculator::equ_solution()
{
    double temp;
    if(indicator !=0)
    {
        QMessageBox::information(this,"Error","One of the brackets is missing");
        Calculator::on_pushButton_reset_clicked();
        error=true;
    }

    if(NumberOfBrace != 0)
    {
        int bracketshead=0, bracketstail=0;
        while(NumberOfBrace!=0)
        {
            int passed_started=0;
            for(int i=0;i<OperationVec.size();i++)
                if(OperationVec[i]==')')
                {
                    bracketstail=i;
                    break;
                }

            for(int i=0;i<OperationVec.size();i++)
                if(OperationVec[i]=='(' && i<bracketstail)
                {
                    bracketshead=i;
                    passed_started++;
                }


            if(OperationVec[0] != '(' && bracketshead==0)
            {
                QMessageBox::information(this,"Error","Incorrect brackets placement");
                Calculator::on_pushButton_reset_clicked();
                error=true;
                NumberOfBrace=0;
            }
            else
            {
                OpStart = bracketstail;
                OpEnd = bracketshead;
                OpPlus = passed_started;

                Calculator::equ_solution_res();
                NumberOfBrace-=2;

                OperationVec.erase(OperationVec.begin() + bracketstail-elementsInside);
                OperationVec.erase(OperationVec.begin() + bracketshead);

                bracketstail=0;
            }
        }
        OpPlus=0;
    }
    if(OperationVec.size()!=0)
    {
        OpStart = OperationVec.size()-1;
        OpEnd = 0;
        Calculator::equ_solution_res();
    }
}


void Calculator::on_actionnumeral_system_2_triggered()
{
    this->close();
    numeralsys->setWindowTitle("Calculator: NumeralSystem");
    numeralsys->show();
}
