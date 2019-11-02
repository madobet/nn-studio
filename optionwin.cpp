#include "optionwin.h"
#include "ui_optionwin.h"

OptionWin::OptionWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionWin)
{
    ui->setupUi(this);
}

OptionWin::~OptionWin()
{
    delete ui;
}
