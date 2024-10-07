#ifndef ADDTEACHER_H
#define ADDTEACHER_H

#include <QDialog>

namespace Ui {
class AddTeacher;
}

class AddTeacher : public QDialog
{
    Q_OBJECT

public:
    explicit AddTeacher(QWidget *parent = nullptr);
    ~AddTeacher();

private:
    Ui::AddTeacher *ui;
};

#endif // ADDTEACHER_H
