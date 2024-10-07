#include"teacher.h"
#include <QDebug>
#include<QSqlQueryModel>
#include <QSqlQuery>
#include<QString>
#include<QMessageBox>

teacher::teacher()
{
    CINT=0;
    NOMT="";
    PRENOMT="";
    MODULE="";
    ID="";
     SALAIRE=0;


}
teacher::teacher(int CINT, QString NOMT,QString PRENOMT,QString MODULE,QString ID ,int SALAIRE)
{
    this->CINT=CINT;
    this->NOMT=NOMT;
    this->PRENOMT=PRENOMT;
    this->MODULE=MODULE;
    this->ID=ID;
    this->SALAIRE=SALAIRE;
}


bool teacher::ajouter()
{
    QSqlQuery query;
       QString res= QString::number(CINT);
       QString res1= QString::number(SALAIRE);
        query.prepare("INSERT INTO teacher ( CINT,NOMT, PRENOMT,MODULE,ID,SALAIRE) "
                            "VALUES (:CINT,:NOMT, :PRENOMT,:MODULE,:ID,,:SALAIRE)");
        query.bindValue(":CINT", res);
        query.bindValue(":NOMT", NOMT);
        query.bindValue(":PRENOMT", PRENOMT);
        query.bindValue(":MODULE", MODULE);
        query.bindValue(":ID", ID);
        query.bindValue(":SALAIRE", res1);

        return    query.exec();
}



QSqlQueryModel * teacher::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from teacher");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CINT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOMT "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MODULE "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("SALAIRE"));


        return model;
}


bool teacher::supprimer(int CINT)
{
    QSqlQuery query;
    QString res= QString::number(CINT);
    query.prepare("Delete from teacher where CINT = :CINT ");
    query.bindValue(":CINT", res);


    return    query.exec();
}

bool teacher::modifier(int CINT, QString NOMT,QString PRENOMT,QString MODULE,QString ID ,int SALAIRE)

{
    QSqlQuery query;
       query.prepare("UPDATE teacher SET NOMT=:NOMT,PRENOMT=:PRENOMT,MODULE=:MODULE,ID=:ID,SALAIRE=:SALAIRE WHERE CINF=:CINF");
       query.bindValue(":CINT", CINT);
       query.bindValue(":NOMT", NOMT);
       query.bindValue(":PRENOMT", PRENOMT);
       query.bindValue(":MODULE", MODULE);
       query.bindValue(":ID", ID);
       query.bindValue(":SALAIRE", SALAIRE);

       return    query.exec();
}
QSqlQueryModel* teacher::rechercherM(QString NOMT)
{
    QSqlQueryModel * model= new QSqlQueryModel();
            QString recher="select * from teacher where NOMT like '%"+NOMT+"%' ";
            model->setQuery(recher);
            return model;
}
QSqlQueryModel* teacher::triC()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM teacher ORDER BY MODULE");
               return model;
}

QSqlQueryModel* teacher::triN()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM teacher ORDER BY NOMT");
               return model;
}

QSqlQueryModel* teacher::triA()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM teacher ORDER BY CINT");
               return model;
}









