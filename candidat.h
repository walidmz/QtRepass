#ifndef CANDIDAT_H
#define CANDIDAT_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QVariant>


class Candidat
{
public:
    // Constructor
    Candidat(int id, QString nom, QString prenom, QString email, QString cin, QDate dateNaissance, int telephone);
    Candidat( QString nom,  QString prenom,  QString email,  QString cin,  QDate dateNaissance,  int telephone);
    Candidat();
        bool create(); // Create a new Candidat
        QSqlQueryModel* readAll(); // Read all Candidats
        bool update(int id ); // Update Candidat by ID
        bool remove(int id); // Delete Candidat by ID
        QSqlQueryModel* rechercher(QString NOM);
        QSqlQueryModel* triNom();
        QSqlQueryModel* triID();
        QSqlQueryModel* triDate();




    // Getters and setters
    int getId() const;
    void setId(int id);

    QString getNom() const;
    void setNom(const QString &nom);

    QString getPrenom() const;
    void setPrenom(const QString &prenom);

    QString getEmail() const;
    void setEmail(const QString &email);

    QDate getDateNaissance() const;
    void setDateNaissance(const QDate &date);

    int getTelephone() const;
    void setTelephone(const int &telephone);

    QString getCIN() const;
    void setCIN(const QString &cin);

private:
    int id;
    QString nom;
    QString prenom;
    QString email;
    QDate dateNaissance;
    int telephone;
    QString cin;

};

#endif // CANDIDAT_H
