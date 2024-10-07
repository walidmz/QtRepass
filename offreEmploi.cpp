#include"offreEmploi.h"
#include <QDebug>
#include<QSqlQueryModel>
#include <QSqlQuery>
#include<QString>
#include<QMessageBox>
#include <QSqlError>


OffreEmploi::OffreEmploi()    {}
OffreEmploi::OffreEmploi(QString titre, QString description, QString entreprise, QDate dateExpiration, QString lieu ):
    titre(titre), description(description), entreprise(entreprise), dateExpiration(dateExpiration), lieu(lieu){}



// Create a new OffreEmploi
bool OffreEmploi::create() {
    QSqlQuery query;
    query.prepare("INSERT INTO OFFREEMPLOI (titre, description, entreprise, dateExpiration, lieu) VALUES (:titre, :description, :entreprise, :cin, :dateExpiration, :lieu)");
    query.bindValue(":titre", titre);
    query.bindValue(":description", description);
    query.bindValue(":entreprise", entreprise);
    query.bindValue(":dateExpiration", dateExpiration);
    query.bindValue(":lieu", lieu);

    if (!query.exec()) {
        qDebug() << "Error inserting Candidat:" << query.lastError().text();
        return false;
    }
    return true;
}


// Read all OFFREEMPLOIs
QSqlQueryModel* OffreEmploi::readAll() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("SELECT * FROM OFFREEMPLOI");
    query.exec();
    model->setQuery(query);
    return model;
}

// Update OFFREEMPLOI by ID
bool OffreEmploi::update(int id) {
    QSqlQuery query;
    query.prepare("UPDATE OFFREEMPLOI SET titre = :titre, description = :description, entreprise = :entreprise, dateExpiration = :dateExpiration, lieu = :lieu,  WHERE id = :id");
    query.bindValue(":titre", titre);
    query.bindValue(":description", description);
    query.bindValue(":entreprise", entreprise);
    query.bindValue(":dateExpiration", dateExpiration);
    query.bindValue(":lieu", lieu);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error updating Candidat:" << query.lastError().text();
        return false;
    }
    return true;
}

// Delete OffreEmploi by ID
bool OffreEmploi::remove(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM OFFREEMPLOI WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting OffreEmploi:" << query.lastError().text();
        return false;
    }
    return true;
}

/*
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
*/











