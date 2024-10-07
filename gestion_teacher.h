#ifndef GESTION_TEACHER_H
#define GESTION_TEACHER_H
#include "teacher.h"
#include <QDialog>
#include <QWidget>
namespace Ui {
class gestion_teacher;
}

class gestion_teacher : public QDialog
{
    Q_OBJECT

public:
    explicit gestion_teacher(QWidget *parent = nullptr);
    ~gestion_teacher();

private slots:
    void on_triC_2_clicked();

    void on_pushButton_triN_2_clicked();

    void on_pushButton_triA_2_clicked();

    void on_recherche_2_clicked();

    void on_Modifier_2_clicked();

    void on_inprimer_2_clicked();

    void on_Supprimer_2_clicked();

    void on_statistique_2_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_tableView_3_activated(const QModelIndex &index);

    void on_Ajouter_2_clicked();

private:
    Ui::gestion_teacher *ui;
    teacher f;
};

#endif // GESTION_TEACHER_H

