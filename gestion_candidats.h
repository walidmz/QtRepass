#ifndef GESTION_CANDIDATS_H
#define GESTION_CANDIDATS_H
#include"candidat.h"
#include <QDialog>

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

    void on_Gestion_Fournisseur_tabBarClicked(int index);

    void on_recherche_clicked();

    void on_triC_clicked();

    void on_pushButton_triN_clicked();

    void on_pushButton_triA_clicked();

    void on_inprimer_clicked();

    void on_statistique_clicked();

    void on_pushButton_clicked();


private:
    Ui::gestion_candidats *ui;
    Candidat candidat;

};

#endif // GESTION_CANDIDATS_H
