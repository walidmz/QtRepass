#ifndef TEACHER_H
#define TEACHER_H
#include<QString>
#include<QSqlQueryModel>


class teacher
{
public:
    teacher();
    void setNOMT(QString n);
    void setPRENOMT(QString n);
    void setCINT(int n);
    void setMODULE(QString n);
    void setID(QString n);
     void setSALAIRE(int n);

    QString get_NOMF(){return NOMT;}
    QString get_PRENOMF(){return PRENOMT;}
    int get_CINF(){return CINT;}
    QString get_MODULE(){return MODULE;}
    QString get_ID(){return ID;}
    int get_SALAIRE(){return SALAIRE;}

    teacher(int,QString,QString,QString,QString,int);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QString,int);
    QSqlQueryModel * rechercherM(QString);

    QSqlQueryModel * triC();
    QSqlQueryModel * triN();
    QSqlQueryModel * triA();






private:
        QString NOMT,PRENOMT,MODULE,ID;
        int CINT,SALAIRE;
};

#endif // TEACHER_H
