#include "addteacher.h"
#include "ui_addteacher.h"

AddTeacher::AddTeacher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTeacher)
{
    ui->setupUi(this);
}

AddTeacher::~AddTeacher()
{
    delete ui;
}
