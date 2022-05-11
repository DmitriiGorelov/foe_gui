#include "formhelp.h"
#include "ui_formhelp.h"

FormHelp::FormHelp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormHelp)
{
    ui->setupUi(this);
}

FormHelp::~FormHelp()
{
    delete ui;
}

void FormHelp::on_btnClose_clicked()
{
    close();
}

