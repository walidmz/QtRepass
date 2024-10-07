#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H
#include<QString>
#include<QSqlQueryModel>

class enseignant
{
public :
  void setNOME(QString n);
  void setPRENOME(QString n);
  void setCINE(int n);
  void setMODULE(QString n);
  void setID(QString n);
  void setSALAIRE(int n);
  QString get_NOME(){return NOME;}
  QString get_PRENOME(){return PRENOME;}
  int get_CINE(){return CINE;}
  QString get_MODULE(){return MODULE;}
  QString get_ID(){return ID;}
  int get_SALAIRE(){return SALAIRE;}
  enseignant();
  enseignant(int,QString,QString,QString,QString,int);
  bool ajouter();
  QSqlQueryModel * afficher();
  bool supprimer(int);
  bool modifier(int,QString,QString,QString,QString,int);
  QSqlQueryModel * rechercherM(QString);

  QSqlQueryModel * triC();
  QSqlQueryModel * triN();
  QSqlQueryModel * triA();






private:
      QString NOME,PRENOME,MODULE,ID;
      int CINE,SALAIRE;
};



#endif // ENSEIGNANT_H
