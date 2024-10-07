#include"fournisseur.h"
#include <QDebug>
#include<QSqlQueryModel>
#include <QSqlQuery>
#include<QString>
#include<QMessageBox>

fournisseur::fournisseur()
{
    CINF=0;
    NOMF="";
    PRENOMF="";
    CLASSE="";
    ID="";


}
fournisseur::fournisseur(int CINF, QString NOMF,QString PRENOMF,QString CLASSE,QString ID )
{
    this->CINF=CINF;
    this->NOMF=NOMF;
    this->PRENOMF=PRENOMF;
    this->CLASSE=CLASSE;
    this->ID=ID;
}


bool fournisseur::ajouter()
{
    QSqlQuery query;
       QString res= QString::number(CINF);
        query.prepare("INSERT INTO STUDENT ( CINF,NOMF, PRENOMF,CLASSE,ID) "
                            "VALUES (:CINF,:NOMF, :PRENOMF,:CLASSE,:ID)");
        query.bindValue(":CINF", res);
        query.bindValue(":NOMF", NOMF);
        query.bindValue(":PRENOMF", PRENOMF);
        query.bindValue(":CLASSE", CLASSE);
        query.bindValue(":ID", ID);

        return    query.exec();
}



QSqlQueryModel * fournisseur::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from STUDENT");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CINF"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMF"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOMF "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CLASSE "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID "));

        return model;
}


bool fournisseur::supprimer(int CINF)
{
    QSqlQuery query;
    QString res= QString::number(CINF);
    query.prepare("Delete from STUDENT where CINF = :CINF ");
    query.bindValue(":CINF", res);


    return    query.exec();
}

bool fournisseur::modifier(int CINF, QString NOMF,QString PRENOMF,QString CLASSE,QString ID )

{
    QSqlQuery query;
       query.prepare("UPDATE STUDENT SET NOMF=:NOMF,PRENOMF=:PRENOMF,CLASSE=:CLASSE,ID=:ID WHERE CINF=:CINF");
       query.bindValue(":CINF", CINF);
       query.bindValue(":NOMF", NOMF);
       query.bindValue(":PRENOMF", PRENOMF);
       query.bindValue(":CLASSE", CLASSE);
       query.bindValue(":ID", ID);

       return    query.exec();
}
QSqlQueryModel* fournisseur::rechercherM(QString NOMF)
{
    QSqlQueryModel * model= new QSqlQueryModel();
            QString recher="select * from STUDENT where NOMF like '%"+NOMF+"%' ";
            model->setQuery(recher);
            return model;
}
QSqlQueryModel* fournisseur::triC()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM STUDENT ORDER BY CLASSE");
               return model;
}

QSqlQueryModel* fournisseur::triN()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM STUDENT ORDER BY NOMF");
               return model;
}

QSqlQueryModel* fournisseur::triA()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM STUDENT ORDER BY CINF");
               return model;
}









