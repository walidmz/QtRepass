#include"etudiant.h"
#include <QDebug>
#include<QSqlQueryModel>
#include <QSqlQuery>
#include<QString>
#include<QMessageBox>

etudiant::etudiant()
{
    CINE=0;
    NOME="";
    PRENOME="";
    CLASSE="";
    ID="";

}
etudiant::etudiant(int CINE, QString NOME,QString PRENOME,QString CLASSE,QString ID )
{
    this->CINE=CINE;
    this->NOME=NOME;
    this->PRENOME=PRENOME;
    this->CLASSE=CLASSE;
    this->ID=ID;
}


bool etudiant::ajouter()
{
    QSqlQuery query;
       QString res= QString::number(CINE);
        query.prepare("INSERT INTO student ( CINE,NOME, PRENOME,CLASSE,ID) "
                            "VALUES (:CINE,:NOME, :PRENOME,:CLASSE,:ID)");
        query.bindValue(":CINE", res);
        query.bindValue(":NOME", NOME);
        query.bindValue(":PRENOME", PRENOME);
        query.bindValue(":CLASSE", CLASSE);
        query.bindValue(":ID", ID);

        return    query.exec();
}



QSqlQueryModel * etudiant::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from student");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CINE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOME"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CLASSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID"));
        return model;
}


bool etudiant::supprimer(int CINE)
{
    QSqlQuery query;
    QString res= QString::number(CINE);
    query.prepare("Delete from student where CINE = :CINE ");
    query.bindValue(":CINE", res);


    return    query.exec();
}

bool etudiant::modifier(int CINE, QString NOME,QString PRENOME,QString CLASSE,QString ID )

{
    QSqlQuery query;
       query.prepare("UPDATE student SET NOME=:NOME,PRENOME=:PRENOME,CLASSE=:CLASSE,ID=:ID WHERE CINE=:CINE");
       query.bindValue(":CINE", CINE);
       query.bindValue(":NOME", NOME);
       query.bindValue(":PRENOME", PRENOME);
       query.bindValue(":CLASSE", CLASSE);
       query.bindValue(":ID", ID);

       return    query.exec();
}
QSqlQueryModel* etudiant::  rechercherM(QString CLASSE)
{
    QSqlQueryModel * model= new QSqlQueryModel();
            QString recher="select * from student where CLASSE like '%"+CLASSE+"%' ";
            model->setQuery(recher);
            return model;
}
QSqlQueryModel* etudiant::triC()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM student ORDER BY CINE");
               return model;
}

QSqlQueryModel* etudiant::triN()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM student ORDER BY NOME");
               return model;
}

QSqlQueryModel* etudiant::triA()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM student ORDER BY CLASSE");
               return model;
}
