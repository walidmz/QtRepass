#include "enseignant.h"
#include <QDebug>
#include<QSqlQueryModel>
#include <QSqlQuery>
#include<QString>
#include<QMessageBox>

enseignant::enseignant()
{
    CINE=0;
    NOME="";
    PRENOME="";
    MODULE="";
    ID="";
    SALAIRE=0;

}
enseignant::enseignant(int CINE, QString NOME,QString PRENOME,QString MODULE,QString ID ,int SALAIRE)
{
    this->CINE=CINE;
    this->NOME=NOME;
    this->PRENOME=PRENOME;
    this->MODULE=MODULE;
    this->ID=ID;
    this->SALAIRE=SALAIRE;
}


bool enseignant::ajouter()
{
    QSqlQuery query;
       QString res= QString::number(CINE);
       QString res1= QString::number(SALAIRE);
        query.prepare("INSERT INTO teacher ( CINE,NOME, PRENOME,MODULE,ID,SALAIRE) "
                            "VALUES (:CINE,:NOME, :PRENOME,:MODULE,:ID,:SALAIRE)");
        query.bindValue(":CINE", res);
        query.bindValue(":NOME", NOME);
        query.bindValue(":PRENOME", PRENOME);
        query.bindValue(":MODULE", MODULE);
        query.bindValue(":ID", ID);
        query.bindValue(":SALAIRE", res1);

        return    query.exec();
}



QSqlQueryModel * enseignant::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from teacher");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CINE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOME"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MODULE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("SALAIRE"));
    return model;
}


bool enseignant::supprimer(int CINE)
{
    QSqlQuery query;
    QString res= QString::number(CINE);
    query.prepare("Delete from teacher where CINE = :CINE ");
    query.bindValue(":CINE", res);


    return    query.exec();
}

bool enseignant::modifier(int CINE, QString NOME,QString PRENOME,QString MODULE,QString ID,int SALAIRE )

{
    QSqlQuery query;
       query.prepare("UPDATE teacher SET NOME=:NOME,PRENOME=:PRENOME,MODULE=:MODULE,ID=:ID,SALAIRE:=SALAIRE WHERE CINE=:CINE");
       query.bindValue(":CINE", CINE);
       query.bindValue(":NOME", NOME);
       query.bindValue(":PRENOME", PRENOME);
       query.bindValue(":MODULE", MODULE);
       query.bindValue(":ID", ID);
       query.bindValue(":SALAIRE", SALAIRE);


       return    query.exec();
}
QSqlQueryModel* enseignant::  rechercherM(QString NOM)
{
    QSqlQueryModel * model= new QSqlQueryModel();
            QString recher="SELECT * from teacher where NOME like '%"+NOM+"%' ";
            model->setQuery(recher);
            return model;
}
QSqlQueryModel* enseignant::triC()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM teacher ORDER BY SALAIRE");
               return model;
}

QSqlQueryModel* enseignant::triN()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM teacher ORDER BY NOME");
               return model;
}


