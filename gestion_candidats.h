#ifndef GESTION_CANDIDATS_H
#define GESTION_CANDIDATS_H
#include"candidat.h"
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QMultimedia>
#include <QtMultimediaWidgets>
#include "offreEmploi.h"






namespace Ui {
class gestion_candidats;
}

class gestion_candidats : public QDialog
{
    Q_OBJECT

public:
    explicit gestion_candidats(QWidget *parent = nullptr);
    ~gestion_candidats();


private slots:
    void on_Ajouter_clicked();

    void on_Supprimer_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_Modifier_clicked();

    void on_Gestion_CANDIDAT_tabBarClicked(int index);

    void on_recherche_clicked();

    void on_tri_date_clicked();

    void on_pushButton_tri_nom_clicked();

    void on_pushButton_tri_id_clicked();

    void on_inprimer_clicked();

    void on_statistique_clicked();

    void on_pushButton_clicked();

    void start_camera();
    void stop_camera();
    void on_sendEmailButton_clicked() ;
    void sendConfirmationEmail(const QString &email);

    void on_btn_start_camera_clicked();

    void on_btn_stop_camera_clicked();
    void on_Ajouter_OffreEmploi_clicked();
    void on_tableView_offres_activated(const QModelIndex &index);
    void on_Gestion_Offres_tabBarClicked(int index);
    void on_Supprimer_offre_clicked();
    void on_Modifier_offre_clicked();
    void showEvent(QShowEvent *event);
    void on_recherche_offre_clicked();
    void on_statistique_offre_clicked();
    void on_tri_dateexpiration_clicked();

    void on_tri_titre_clicked();
    void on_imprimer_offre();
    void on_tri_Entreprise_clicked();
private:
    Ui::gestion_candidats *ui;
    Candidat candidat;
    OffreEmploi offreEmploi;
    QScopedPointer<QCamera> M_Camera;
    QStringList gouvernorates;


};

#endif // GESTION_CANDIDATS_H
