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

// Setter for 'titre'
void OffreEmploi::setTitre(const QString &titre) {
    this->titre = titre;
}

// Setter for 'description'
void OffreEmploi::setDescription(const QString &description) {
    this->description = description;
}

// Setter for 'entreprise'
void OffreEmploi::setEntreprise(const QString &entreprise) {
    this->entreprise = entreprise;
}

// Setter for 'lieu'
void OffreEmploi::setLieu(const QString &lieu) {
    this->lieu = lieu;
}

// Setter for 'lieu'
void OffreEmploi::setDateExpiration(const QDate &date) {
    this->dateExpiration = date;
}

// Create a new OffreEmploi
bool OffreEmploi::create() {
    QSqlQuery query;
    query.prepare("INSERT INTO OFFREEMPLOI (titre, description, entreprise, dateExpiration, lieu) VALUES (:titre, :description, :entreprise, :dateExpiration, :lieu)");
    query.bindValue(":titre", titre);
    query.bindValue(":description", description);
    query.bindValue(":entreprise", entreprise);
    query.bindValue(":dateExpiration", dateExpiration);
    query.bindValue(":lieu", lieu);


    if (!query.exec()) {
        qDebug() << "Error inserting OffreEmploi:" << query.lastError().text();
        return false;
    }
    return true;
}


// Read all OFFREEMPLOIs
QSqlQueryModel* OffreEmploi::readAll() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    if (!query.exec("SELECT * FROM OffreEmploi")) {
        qDebug() << "Error executing query:" << query.lastError().text();
    } else {
        model->setQuery(query);
    }

    return model;
}

// Update OFFREEMPLOI by ID
bool OffreEmploi::update(int id) {
    QSqlQuery query;
    query.prepare("UPDATE OFFREEMPLOI SET titre = :titre, description = :description, entreprise = :entreprise, dateExpiration = :dateExpiration, lieu = :lieu WHERE id = :id");
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


QSqlQueryModel* OffreEmploi::rechercher(QString titre)
{
    QSqlQueryModel * model= new QSqlQueryModel();
            QString recher="select * from OFFREEMPLOI where titre like '%"+titre+"%' ";
            model->setQuery(recher);
            return model;
}
QSqlQueryModel* OffreEmploi::triEntreprise()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM OFFREEMPLOI ORDER BY ENTREPRISE");
               return model;
}

QSqlQueryModel* OffreEmploi::triNom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM OFFREEMPLOI ORDER BY TITRE");
               return model;
}


QSqlQueryModel* OffreEmploi::triDate()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("SELECT * FROM OFFREEMPLOI ORDER BY DATEEXPIRATION");
               return model;
}











