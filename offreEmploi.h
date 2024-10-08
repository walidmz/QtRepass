#ifndef OFFREEMPLOI_H
#define OFFREEMPLOI_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QVariant>

class OffreEmploi
{
public:
    // Constructor
    OffreEmploi(int id, QString titre, QString description, QString entreprise, QDate dateExpiration, QString lieu);
    OffreEmploi(QString titre, QString description, QString entreprise, QDate dateExpiration, QString lieu);
    OffreEmploi();

    bool create(); // Create a new OffreEmploi
    QSqlQueryModel* readAll(); // Read all OffreEmplois
    bool update(int id); // Update OffreEmploi by ID
    bool remove(int id); // Delete OffreEmplois by ID
    QSqlQueryModel* rechercher(QString NOM);
    QSqlQueryModel* triNom();
    QSqlQueryModel* triEntreprise();
    QSqlQueryModel* triDate();

    // Getters and setters
    int getId() const;
    void setId(int id);

    QString getTitre() const;
    void setTitre(const QString &titre);

    QString getDescription() const;
    void setDescription(const QString &description);

    QString getEntreprise() const;
    void setEntreprise(const QString &entreprise);

    QDate getDateExpiration() const;
    void setDateExpiration(const QDate &date);

    QString getLieu() const;
    void setLieu(const QString &lieu);


private:
    int id;
    QString titre;
    QString description;
    QString entreprise;
    QDate dateExpiration;
    QString lieu;
};

#endif // OFFREEMPLOI_H
