#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include<QString>
#include<QSqlQueryModel>

class fournisseur
{
public:

       void setNOMF(QString n);
       void setPRENOMF(QString n);
       void setCINF(int n);
       void setCLASSE(QString n);
       void setID(QString n);
       QString get_NOMF(){return NOMF;}
       QString get_PRENOMF(){return PRENOMF;}
       int get_CINF(){return CINF;}
       QString get_CLASSE(){return CLASSE;}
       QString get_ID(){return ID;}
       fournisseur();
       fournisseur(int,QString,QString,QString,QString);
       bool ajouter();
       QSqlQueryModel * afficher();
       bool supprimer(int);
       bool modifier(int,QString,QString,QString,QString);
       QSqlQueryModel * rechercherM(QString);

       QSqlQueryModel * triC();
       QSqlQueryModel * triN();
       QSqlQueryModel * triA();


   private:
           QString NOMF,PRENOMF,CLASSE,ID;
           int CINF;
};
#endif // FOURNISSEUR_H
