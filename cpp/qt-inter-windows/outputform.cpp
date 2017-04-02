#include "outputform.h"
#include "ui_outputform.h"

OutputForm::OutputForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputForm)
{
    ui->setupUi(this);
}

OutputForm::~OutputForm()
{
    delete ui;
}
