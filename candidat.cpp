#include"candidat.h"
#include <QDebug>
#include<QSqlQueryModel>
#include <QSqlQuery>
#include<QString>
#include<QMessageBox>
#include <QSqlError>


Candidat::Candidat() : id(0) {}
Candidat::Candidat(QString nom, QString prenom, QString email, QString cin, QDate dateNaissance, QString telephone ):
    nom(nom), prenom(prenom), email(email), cin(cin), dateNaissance(dateNaissance), telephone(telephone) {}
// Setter for 'nom'
void Candidat::setNom(const QString &nom) {
    this->nom = nom;
}

// Setter for 'prenom'
void Candidat::setPrenom(const QString &prenom) {
    this->prenom = prenom;
}

// Setter for 'email'
void Candidat::setEmail(const QString &email) {
    this->email = email;
}

// Setter for 'dateNaissance'
void Candidat::setDateNaissance(const QDate &date) {
    this->dateNaissance = date;
}

// Setter for 'telephone'
void Candidat::setTelephone(const QString &telephone) {
    this->telephone = telephone;
}

// Setter for 'cin'
void Candidat::setCIN(const QString &cin) {
    this->cin = cin;
}



// Create a new Candidat
bool Candidat::create() {
    QSqlQuery query;
    query.prepare("INSERT INTO Candidat (nom, prenom, email, cin, datenaissance, telephone) VALUES (:nom, :prenom, :email, :cin, :datenaissance, :telephone)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":cin", cin);
    query.bindValue(":datenaissance", dateNaissance);
    query.bindValue(":telephone", telephone);

    if (!query.exec()) {
        qDebug() << "Error inserting Candidat:" << query.lastError().text();
        return false;
    }
    return true;
}


// Read all Candidats
QSqlQueryModel* Candidat::readAll() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    if (!query.exec("SELECT * FROM Candidat")) {
        qDebug() << "Error executing query:" << query.lastError().text();
    } else {
        model->setQuery(query);
    }

    return model;
}

// Update Candidat by ID
bool Candidat::update(int id) {
    QSqlQuery query;
    query.prepare("UPDATE Candidat SET nom = :nom, prenom = :prenom, email = :email, cin = :cin, datenaissance = :datenaissance, telephone = :telephone WHERE id = :id");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":cin", cin);
    query.bindValue(":datenaissance", dateNaissance);
    query.bindValue(":telephone", telephone);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error updating Candidat:" << query.lastError().text();
        return false;
    }
    return true;
}

// Delete Candidat by CIN
bool Candidat::remove(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM Candidat WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting Candidat:" << query.lastError().text();
        return false;
    }
    return true;
}


QSqlQueryModel* Candidat::rechercher(QString NOM)
{
    QSqlQueryModel * model= new QSqlQueryModel();
            QString recher="select * from CANDIDAT where nom like '%"+NOM+"%' ";
            model->setQuery(recher);
            return model;
}
QSqlQueryModel* Candidat::triNom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM CANDIDAT ORDER BY NOM");
               return model;
}

QSqlQueryModel* Candidat::triID()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM CANDIDAT ORDER BY ID");
               return model;
}

QSqlQueryModel* Candidat::triDate()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM CANDIDAT ORDER BY DATENAISSANCE");
               return model;
}












