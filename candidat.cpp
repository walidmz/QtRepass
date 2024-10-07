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
    QSqlQuery query("SELECT * FROM Candidat");
    query.exec();
    model->setQuery(query);
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

// Delete Candidat by ID
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
QSqlQueryModel* Candidat::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM CANDIDAT ORDER BY NOM");
               return model;
}












