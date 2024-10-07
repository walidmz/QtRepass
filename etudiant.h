#ifndef ETUDIANT_H
#define ETUDIANT_H
#include<QString>
#include<QSqlQueryModel>

class etudiant
{
  public :
    void setNOME(QString n);
    void setPRENOME(QString n);
    void setCINE(int n);
    void setCLASSE(QString n);
    void setID(QString n);
    QString get_NOME(){return NOME;}
    QString get_PRENOME(){return PRENOME;}
    int get_CINE(){return CINE;}
    QString get_CLASSE(){return CLASSE;}
    QString get_ID(){return ID;}
    etudiant();
    etudiant(int,QString,QString,QString,QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QString);
    QSqlQueryModel * rechercherM(QString);

    QSqlQueryModel * triC();
    QSqlQueryModel * triN();
    QSqlQueryModel * triA();






private:
        QString NOME,PRENOME,CLASSE,ID;
        int CINE;
};

#endif // ETUDIANT_H
