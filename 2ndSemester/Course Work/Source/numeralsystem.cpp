#include "numeralsystem.h"
#include "ui_numeralsystem.h"
#include "calculator.h"
#include <vector>
#include <QMovie>


char NW16[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

NumeralSystem::NumeralSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NumeralSystem)
{


    ui->setupUi(this);

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

     connect(ui->pushButton_FN2,SIGNAL(clicked()),this,SLOT(FN2lock()));
     connect(ui->pushButton_FN10,SIGNAL(clicked()),this,SLOT(FN2lock()));
     connect(ui->pushButton_FN8,SIGNAL(clicked()),this,SLOT(FN2lock()));
}

NumeralSystem::~NumeralSystem()
{
    delete ui;
}

void NumeralSystem::on_defoultcalculator_swap_triggered()
{
    this->close();
    emit defoultcalculator();
}

void NumeralSystem::number()
{
    if(finished==true)
        NumeralSystem::on_pushButton_reset_clicked();

    QPushButton *button = (QPushButton* ) sender();
    Value = ((ui->input->text()+button->text()).toDouble());

    ui->input->setText(QString::number(Value, 'g', 16));
}

void NumeralSystem::on_pushButton_reset_clicked()
{
    ui->input->setText("");
    ui->output->setText("");

    finished=false;
    error=false;
}

void NumeralSystem::FN2lock()
{
    QPushButton *button = (QPushButton* ) sender();
    if(button->text() == ui->pushButton_FN2->text())
    {
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_six->setEnabled(false);
        ui->pushButton_seven->setEnabled(false);
        ui->pushButton_eight->setEnabled(false);
        ui->pushButton_nine->setEnabled(false);
    }
    else
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_six->setEnabled(true);
        ui->pushButton_seven->setEnabled(true);
        ui->pushButton_eight->setEnabled(true);
        ui->pushButton_nine->setEnabled(true);
    }


}

void NumeralSystem::FN10_Operation()
{
        if(ui->pushButton_FN10->isChecked() && ui->pushButton_TN2->isChecked())
        {
            while(Value != 0)
            {
                temp = Value % 2;
                Value /= 2;
                ui->output->setText(QString::number(temp)+ui->output->text());
            }
        }
        else if(ui->pushButton_FN10->isChecked() && ui->pushButton_TN16->isChecked())
        {
            while(Value !=0)
            {
                temp = Value%16;
                Value/=16;
                ui->output->setText(NW16[temp]+ui->output->text());
            }
        }
        else
            ui->output->setText(ui->input->text());
}

void NumeralSystem::FN2_Operation()
{
    if(ui->pushButton_FN2->isChecked() && ui->pushButton_TN10->isChecked())
        {
            QString Temp = QString::number(Value);
            temp=0;
            for(int i=0;i<Temp.size();i++)
                if(Temp[i]=='1')
                    temp+=pow(2,Temp.size()-(i+1));
            ui->output->setText(QString::number(temp));

        }
        else if(ui->pushButton_FN2->isChecked() && ui->pushButton_TN16->isChecked())
        {
            QString Temp = QString::number(Value);
            Value=0;
            for(int i=0;i<Temp.size();i++)
                if(Temp[i]=='1')
                    Value+=pow(2,Temp.size()-(i+1));
            while(Value !=0)
            {
                temp = Value%16;
                Value/=16;
                ui->output->setText(NW16[temp]+ui->output->text());
            }
        }
        else
            ui->output->setText(ui->input->text());
}

void NumeralSystem::FN8_Operation()
{
    if(ui->pushButton_FN8->isChecked() && ui->pushButton_TN2->isChecked())
        {
            temp=0;
            for(int i=0;Value != 0;i++)
            {
                temp += Value%10*pow(8,i);
                Value/=10;
            }
            while(temp != 0)
            {
                Value = temp % 2;
                temp /= 2;
                ui->output->setText(QString::number(Value)+ui->output->text());
            }

        }
        else if(ui->pushButton_FN8->isChecked() && ui->pushButton_TN10->isChecked())
        {
            temp=0;
            for(int i=0;Value != 0;i++)
            {
                temp += Value%10*pow(8,i);
                Value/=10;
            }
            ui->output->setText(QString::number(temp));
        }
        else if(ui->pushButton_FN8->isChecked() && ui->pushButton_TN16->isChecked())
        {
            temp=0;
            for(int i=0;Value != 0;i++)
            {
                temp += Value%10*pow(8,i);
                Value/=10;
            }
            while(temp !=0)
            {
                Value = temp%16;
                temp/=16;
                ui->output->setText(NW16[Value]+ui->output->text());
            }
        }
        else
            ui->output->setText(ui->input->text());
}

void NumeralSystem::on_pushButton_equ_clicked()
{

    ui->output->setText("");

    if(ui->pushButton_FN10->isChecked())
    {
        FN10_Operation();
    }
    else if(ui->pushButton_FN2->isChecked())
    {
        FN2_Operation();
    }

    else if(ui->pushButton_FN8->isChecked())
    {
        FN8_Operation();
    }
    finished=true;
}

void NumeralSystem::on_actionNew_Pic_triggered()
{
    QMovie* mov = new QMovie(":/res/img/sticker.gif");
    QMovie* UKRAINE = new QMovie(":/res/img/UKRAINE.gif");
    QMovie* FONK = new QMovie(":/res/img/3Rre.gif");
    ui->picture->setMovie(mov);
    ui->input->setMovie(UKRAINE);
    ui->output->setMovie(UKRAINE);
    ui->Fonk->setMovie(FONK);

    ui->INFO_INP->setText("Try anouther time");
    ui->INFO_OUT->setText("Try anouther time");
    mov->start();
    FONK->start();
    UKRAINE->start();

    ui->pushButton_FN10->setText("LMAO");
    ui->pushButton_FN2->setText("XIXI");
    ui->pushButton_FN8->setText("LMAO");

    ui->pushButton_TN10->setText("XOXO");
    ui->pushButton_TN2->setText("LMAO");
    ui->pushButton_TN16->setText("XAXA");

    ui->pushButton_0->setText("6");
    ui->pushButton_1->setText("2");
    ui->pushButton_2->setText("3");
    ui->pushButton_3->setText("8");
    ui->pushButton_4->setText("7");
    ui->pushButton_5->setText("1");
    ui->pushButton_six->setText("4");
    ui->pushButton_seven->setText("9");
    ui->pushButton_nine->setText("0");
    ui->pushButton_0->setText("5");

    ui->pushButton_reset->setText("0.0");
    ui->pushButton_equ->setText("TR-15");

    ui->CONVERT->setText("BYBA \\/");
}

