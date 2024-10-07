#include "gestion_teacher.h"
#include "ui_gestion_teacher.h"
#include "teacher.h"
#include<QString>
#include<QMessageBox>
#include<QSqlQuery>
#include <QPainter>
#include <QTextDocument>
#include<QTextStream>
#include<QFileInfo>
#include<QPrinter>
#include<QFileDialog>
#include<QPrintDialog>
#include<QDateTime>
#include<QtCharts>
#include<QChartView>

gestion_teacher::gestion_teacher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestion_teacher)
{
    ui->setupUi(this);
}

gestion_teacher::~gestion_teacher()
{
    delete ui;
    ui->tableView_3->setModel((f.afficher()));
}

void gestion_teacher::on_triC_2_clicked()
{
    teacher f;
    ui->tableView_3->setModel(f.triC());

}

void gestion_teacher::on_pushButton_triN_2_clicked()
{
    teacher f;
    ui->tableView_3->setModel(f.triN());
}

void gestion_teacher::on_pushButton_triA_2_clicked()
{
    teacher f;
    ui->tableView_3->setModel(f.triA());
}

void gestion_teacher::on_recherche_2_clicked()
{
    QString rech=ui->lineEdit_rech_2->text();

             ui->tableView_3->setModel(f.rechercherM(rech));
             ui->lineEdit_rech_2->clear();
}

void gestion_teacher::on_Modifier_2_clicked()
{
    int CINT=ui->lineEdit_CIN_3->text().toInt();
   QString NOMF=ui->lineEdit_NOM_3->text();
   QString PRENOMF=ui->lineEdit_PRENOM_3->text();
   QString MODULE=ui->lineEdit_MODULE_3->text();
   QString ID=ui->lineEdit_ID_3->text();
   int SALAIRE=ui->lineEdit_SALAIRE_3->text().toInt();
   teacher f( CINT,  NOMF, PRENOMF, MODULE, ID,SALAIRE );
   bool test=f.modifier(CINT,  NOMF, PRENOMF, MODULE, ID,SALAIRE);
   if(test)
                   {
                       ui->tableView_3->setModel(f.afficher());
                       QMessageBox::information(nullptr, QObject::tr("modifier un enseignant"),
                                         QObject::tr("fournisseur  modifié.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
                    }

                         else
                             QMessageBox::critical(nullptr, QObject::tr("Modifier enseignant"),
                                         QObject::tr("Erreur !.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
   ui->lineEdit_CIN_3->clear();
    ui->lineEdit_NOM_3->clear();
     ui->lineEdit_MODULE_3->clear();
    ui->lineEdit_PRENOM_3->clear();
     ui->lineEdit_ID_3->clear();
   ui->lineEdit_SALAIRE_3->clear();

}

void gestion_teacher::on_inprimer_2_clicked()
{

}

void gestion_teacher::on_Supprimer_2_clicked()
{
    int cin=ui->lineEdit_CIN_3->text().toInt();
    bool test=f.supprimer(cin);
    if(test)
        {
            ui->tableView_3->setModel(f.afficher());
            QMessageBox::information(nullptr,QObject::tr("Not OK"),
                                     QObject::tr("Suppression effectuée\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                     QObject::tr("Suppression non effectué\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);
      ui->lineEdit_CIN_3->clear();
      ui->lineEdit_NOM_3->clear();
      ui->lineEdit_PRENOM_3->clear();
      ui->lineEdit_MODULE_3->clear();
      ui->lineEdit_ID_3->clear();
      ui->lineEdit_SALAIRE_3->clear();

}

void gestion_teacher::on_statistique_2_clicked()
{

}

void gestion_teacher::on_tabWidget_tabBarClicked(int index)
{
    index=1;
    ui->tableView_3->setModel(f.afficher());
}

void gestion_teacher::on_tableView_3_activated(const QModelIndex &index)
{
    ui->lineEdit_CIN_3->setText(ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(),0)).toString());
    ui->lineEdit_NOM_3->setText(ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(),1)).toString());
    ui->lineEdit_PRENOM_3->setText(ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(),2)).toString());
    ui->lineEdit_MODULE_3->setText(ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(),3)).toString());
    ui->lineEdit_ID_3->setText(ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(),4)).toString());
    ui->lineEdit_SALAIRE_3->setText(ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(),5)).toString());

}

void gestion_teacher::on_Ajouter_2_clicked()
{
    int CINT=ui->lineEdit_CIN_4->text().toInt();
    QString NOMT=ui->lineEdit_NOM_4->text();
    QString PRENOMT=ui->lineEdit_PRENOM_4->text();
    QString MODULE=ui->lineEdit_MODULE_4->text();
    QString ID=ui->lineEdit_ID_4->text();
    int SALAIRE=ui->lineEdit_SALAIRE_4->text().toInt();
    teacher f( CINT,  NOMT, PRENOMT, MODULE, ID ,SALAIRE);
    bool test=f.ajouter();
    if(test)
        {
            ui->tableView_3->setModel((f.afficher()));
           QMessageBox::information(nullptr,QObject::tr("OK"),
                                    QObject::tr("Ajout effectué\n"
                                                "Click Cancel to exit."),QMessageBox::Cancel);
        }
           else
               QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                        QObject::tr("Ajout non effectué\n"
                                                  "Click Cancel to exit."),QMessageBox::Cancel);

          ui->lineEdit_CIN_4->clear();
          ui->lineEdit_NOM_4->clear();
          ui->lineEdit_PRENOM_4->clear();
          ui->lineEdit_MODULE_4->clear();
          ui->lineEdit_ID_4->clear();
          ui->lineEdit_SALAIRE_4->clear();

}
