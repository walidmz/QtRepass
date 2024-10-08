#include "gestion_candidats.h"
#include "ui_gestion_candidats.h"
#include "offreEmploi.h"
#include "candidat.h"
#include<QString>
#include<QMessageBox>
#include<QSqlQuery>
#include <QPainter>
#include <QTextDocument>
#include<QTextStream>
#include<QFileInfo>
#include<QPrinter>
#include<QFileDialog>
#include<QPrintDialog>
#include<QDateTime>
#include<QtCharts>
#include<QChartView>



gestion_candidats::gestion_candidats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestion_candidats)
{
    ui->setupUi(this);
        ui->tableView_candidats->setModel((candidat.readAll()));
        ui->tableView_offres->setModel((offreEmploi.readAll()));
        // Connect the button signal to the slot
        connect(ui->tableView_candidats, &QTableView::activated, this, &gestion_candidats::on_tableView_activated);
        connect(ui->tableView_offres, &QTableView::activated, this, &gestion_candidats::on_tableView_offres_activated);
        connect(ui->btn_modifier_candidat, SIGNAL(clicked()), this, SLOT(on_Modifier_clicked()));
        connect(ui->btn_supprimer_candidat, SIGNAL(clicked()), this, SLOT(on_Supprimer_clicked()));
        connect(ui->btn_supprimer_candidat_2, SIGNAL(clicked()), this, SLOT(on_Supprimer_offre_clicked()));
        connect(ui->btn_modifier_candidat_2, SIGNAL(clicked()), this, SLOT(on_Modifier_offre_clicked()));
        connect(ui->btn_recherche, SIGNAL(clicked()), this, SLOT(on_recherche_clicked()));
        connect(ui->btn_tri_nom, SIGNAL(clicked()), this, SLOT(on_pushButton_tri_nom_clicked()));
        connect(ui->btn_tri_id, SIGNAL(clicked()), this, SLOT(on_pushButton_tri_id_clicked()));
        connect(ui->btn_tri_date, SIGNAL(clicked()), this, SLOT(on_tri_date_clicked()));
        connect(ui->btn_imprimer_candidat,SIGNAL(clicked()),this,SLOT(on_inprimer_clicked()));
        connect(ui->btn_imprimer_candidat_2,SIGNAL(clicked()),this,SLOT(on_imprimer_offre()));
        connect(ui->btn_statistique_candidat,SIGNAL(clicked()),this,SLOT(on_statistique_clicked()));
        connect(ui->btn_start_camera,SIGNAL(clicked()),this,SLOT(on_btn_start_camera_clicked()));
        connect(ui->btn_stop_camera,SIGNAL(clicked()),this,SLOT(on_btn_stop_camera_clicked()));
        connect(ui->Ajouter,SIGNAL(clicked()),this,SLOT(on_sendEmailButton_clicked()));
        connect(ui->Ajouter_2,SIGNAL(clicked()),this,SLOT(on_Ajouter_OffreEmploi_clicked()));
        connect(ui->btn_gestion_candidats, &QPushButton::clicked, this, [=]() {
            ui->stackedWidget->setCurrentIndex(0);  // Example: switch to the second page (index 1)
        });
        connect(ui->btn_gestion_offreEmploi, &QPushButton::clicked, this, [=]() {
            ui->stackedWidget->setCurrentIndex(1);  // Example: switch to the second page (index 1)
        });

        connect(ui->btn_recherche_offre, SIGNAL(clicked()), this, SLOT(on_recherche_offre_clicked()));
        connect(ui->btn_tri_titre, SIGNAL(clicked()), this, SLOT(on_tri_titre_clicked()));
        connect(ui->btn_tri_date_expiration, SIGNAL(clicked()), this, SLOT(on_tri_dateexpiration_clicked()));
        connect(ui->btn_tri_entreprise, SIGNAL(clicked()), this, SLOT(on_tri_Entreprise_clicked()));
        connect(ui->btn_statistique_candidat_2,SIGNAL(clicked()),this,SLOT(on_statistique_offre_clicked()));






           gouvernorates << "Ariana" << "Béja" << "Ben Arous" << "Bizerte"
                         << "Gabès" << "Gafsa" << "Jendouba" << "Kairouan"
                         << "Kasserine" << "Kebili" << "La Manouba" << "Le Kef"
                         << "Mahdia" << "Manouba" << "Medenine" << "Monastir"
                         << "Nabeul" << "Sfax" << "Sidi Bouzid" << "Siliana"
                         << "Souk Ahras" << "Tataouine" << "Tozeur" << "Tunis";

           // Populate the QComboBox with the governorates
           ui->comboBox->addItems(gouvernorates); // Replace comboBox_LIEU with your QComboBox object name
           ui->comboBox_2->addItems(gouvernorates);

        for(const QCameraInfo &infor : QCameraInfo::availableCameras())
        {
            qDebug() << infor.description();
        }

        M_Camera.reset(new QCamera(QCameraInfo::defaultCamera()));
        M_Camera->setViewfinder(ui->camera_view);




}

gestion_candidats::~gestion_candidats()
{
    delete ui;
}


void gestion_candidats::on_Ajouter_clicked()
{
    QString cin = ui->lineEdit_CIN->text();
    QString nom = ui->lineEdit_NOM->text();
    QString prenom = ui->lineEdit_PRENOM->text();
    QString email = ui->lineEdit_EMAIL->text();
    QDate dateNaissance = ui->dateEdit->date();
    QString telephone = ui->lineEdit_TELEPHONE->text();

    // Initialize an empty string for error messages
    QString errorMsg = "";

    // Validate CIN: 8 digits only
    QRegExp cinRegex("\\d{8}");
    if (!cinRegex.exactMatch(cin)) {
        errorMsg += "Le CIN doit contenir exactement 8 chiffres.\n";
    }

    // Validate Telephone: 8 digits only
    QRegExp telRegex("\\d{8}");
    if (!telRegex.exactMatch(telephone)) {
        errorMsg += "Le numéro de téléphone doit contenir exactement 8 chiffres.\n";
    }

    // Validate Nom: Letters only
    QRegExp nameRegex("^[A-Za-zÀ-ÿ]+$");
    if (!nameRegex.exactMatch(nom)) {
        errorMsg += "Le nom doit contenir uniquement des lettres.\n";
    }

    // Validate Prenom: Letters only
    if (!nameRegex.exactMatch(prenom)) {
        errorMsg += "Le prénom doit contenir uniquement des lettres.\n";
    }

    // Validate Email: Basic email format
    QRegExp emailRegex("^[\\w\\.-]+@[\\w\\.-]+\\.[a-z]{2,}$");
    if (!emailRegex.exactMatch(email)) {
        errorMsg += "Veuillez entrer une adresse e-mail valide.\n";
    }

    // Validate Age: Between 18 and 30
    int currentYear = QDate::currentDate().year();
    int birthYear = dateNaissance.year();
    int age = currentYear - birthYear;

    // Adjust for the exact day of birth not yet occurring in the current year
    if (QDate::currentDate() < dateNaissance.addYears(age)) {
        age--;
    }

    if (age < 18) {
        errorMsg += "Le candidat est âgé(e) de moins de 18 ans.\n";
    } else if (age > 30) {
        errorMsg += "Le candidat est âgé(e) de plus de 30 ans.\n";
    }

    // If there are errors, show them in a message box and return
    if (!errorMsg.isEmpty()) {
        QMessageBox::critical(this, "Erreur", errorMsg);
        return;
    }

    // Create the Candidat if all validations pass
    Candidat candidat(nom, prenom, email, cin, dateNaissance, telephone.toInt());
    bool test = candidat.create();
    if (test) {
        ui->tableView_candidats->setModel(candidat.readAll());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    // Clear the form fields
    ui->lineEdit_EMAIL->clear();
    ui->lineEdit_NOM->clear();
    ui->lineEdit_PRENOM->clear();
    ui->lineEdit_EMAIL->clear();
    ui->dateEdit->clear();
    ui->lineEdit_TELEPHONE->clear();
}



void gestion_candidats::on_tableView_activated(const QModelIndex &index)
{
                   ui->id_label->setText(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(),0)).toString());
                   ui->lineEdit_NOM2->setText(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(),1)).toString());
                   ui->lineEdit_PRENOM2->setText(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(),2)).toString());
                   ui->lineEdit_EMAIL2->setText(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(),3)).toString());
                   ui->lineEdit_CIN2->setText(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(),5)).toString());
                   ui->lineEdit_TELEPHONE_2->setText(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(),4)).toString());
                   ui->dateEdit_2->setDate(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(),6)).toDate());

}

void gestion_candidats::on_Supprimer_clicked()
{
    int id=ui->id_label->text().toInt();
    bool test=candidat.remove(id);
    if(test)
        {
            ui->tableView_candidats->setModel(candidat.readAll());
            QMessageBox::information(nullptr,QObject::tr("Not OK"),
                                     QObject::tr("Suppression effectuée\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                     QObject::tr("Suppression non effectué\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);
      ui->lineEdit_CIN2->clear();
      ui->lineEdit_NOM2->clear();
      ui->lineEdit_PRENOM2->clear();
      ui->lineEdit_EMAIL2->clear();
      ui->lineEdit_TELEPHONE_2->clear();
      ui->dateEdit_2->clear();


}

void gestion_candidats::on_Modifier_clicked()
{
    int id = ui->id_label->text().toInt();
    QString cin = ui->lineEdit_CIN2->text();
    QString nom = ui->lineEdit_NOM2->text();
    QString prenom = ui->lineEdit_PRENOM2->text();
    QString email = ui->lineEdit_EMAIL2->text();
    int telephone = ui->lineEdit_TELEPHONE_2->text().toInt();
    QDate datenaissance = ui->dateEdit_2->date();  // Make sure to correctly get the date from QDateEdit

    candidat.setNom(nom);
    candidat.setPrenom(prenom);
    candidat.setEmail(email);
    candidat.setCIN(cin);
    candidat.setDateNaissance(datenaissance);
    candidat.setTelephone(telephone);

    bool test = candidat.update(id);

    if (test) {
        ui->tableView_candidats->setModel(candidat.readAll());  // Refresh table
        QMessageBox::information(nullptr, QObject::tr("modifier un candidat"),
                                 QObject::tr("candidat modifié.\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Modifier candidat"),
                              QObject::tr("Erreur !.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }

    // Clear the fields after modification
    ui->lineEdit_CIN2->clear();
    ui->lineEdit_NOM2->clear();
    ui->lineEdit_PRENOM2->clear();
    ui->lineEdit_EMAIL2->clear();
    ui->lineEdit_TELEPHONE_2->clear();
    ui->dateEdit_2->setDate(QDate::currentDate()); // Set default date after clearing
}


void gestion_candidats::on_Gestion_CANDIDAT_tabBarClicked(int index)
{
    index = 1;

    // Check if the database connection is open
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    // Bind the data model to the table view
    ui->tableView_candidats->setModel(candidat.readAll());
}



void gestion_candidats::on_recherche_clicked()
{

    QString rech=ui->lineEdit_rech->text();

             ui->tableView_candidats->setModel(candidat.rechercher(rech));
             ui->lineEdit_rech->clear();


}

void gestion_candidats::on_tri_date_clicked()
{

    Candidat candidat;
    ui->tableView_candidats->setModel(candidat.triDate());
}

void gestion_candidats::on_pushButton_tri_id_clicked()
{

    Candidat candidat;
    ui->tableView_candidats->setModel(candidat.triID());
}

void gestion_candidats::on_pushButton_tri_nom_clicked()
{

    Candidat candidat;
    ui->tableView_candidats->setModel(candidat.triNom());
}

void gestion_candidats::on_inprimer_clicked()
{ QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_candidats->model()->rowCount();
    const int columnCount = ui->tableView_candidats->model()->columnCount();
    QString TT = QDateTime::currentDateTime().toString();
    out <<"<html>\n"
          "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << "<title>ERP - COMmANDE LIST<title>\n "
        << "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<h1 style=\"text-align: center;\"><strong> ******LISTE DES CANDIDATS******\n"+TT+" </strong></h1>"
           +"<img src=C://Users//WALID//OneDrive//Bureau//logo//logo />"
        "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
          "</br> </br>";
    // headers
    out << "<thead><tr bgcolor=#d6e5ff>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_candidats->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_candidats->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_candidats->isColumnHidden(column)) {
                QString data =ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

void gestion_candidats::on_statistique_clicked()
{
    // Get the current date
    QDate currentDate = QDate::currentDate();

    // Calculate the birthdate ranges based on the current date
    QDate date22 = currentDate.addYears(-18);  // 18 years old (youngest)
    QDate date18 = currentDate.addYears(-22);  // 22 years old
    QDate date26 = currentDate.addYears(-23);  // 23 years old
    QDate date30 = currentDate.addYears(-26);  // 26 years old
    QDate dateOver26 = currentDate.addYears(-30); // Older than 30

    QSqlQueryModel * model = new QSqlQueryModel();

    // Query for candidates between 18 and 22 years old
    QString query1 = QString("SELECT * FROM Candidat WHERE datenaissance BETWEEN TO_DATE('%1', 'YYYY-MM-DD') AND TO_DATE('%2', 'YYYY-MM-DD')")
                        .arg(date18.toString("yyyy-MM-dd")).arg(date22.toString("yyyy-MM-dd"));
    model->setQuery(query1);
    float nbr1 = model->rowCount();

    // Query for candidates between 23 and 26 years old
    QString query2 = QString("SELECT * FROM Candidat WHERE datenaissance BETWEEN TO_DATE('%1', 'YYYY-MM-DD') AND TO_DATE('%2', 'YYYY-MM-DD')")
                        .arg(date26.toString("yyyy-MM-dd")).arg(date18.toString("yyyy-MM-dd"));
    model->setQuery(query2);
    float nbr2 = model->rowCount();

    // Query for candidates older than 26
    QString query3 = QString("SELECT * FROM Candidat WHERE datenaissance < TO_DATE('%1', 'YYYY-MM-DD')")
                        .arg(date30.toString("yyyy-MM-dd"));
    model->setQuery(query3);
    float nbr3 = model->rowCount();

    // Total number of candidates
    float total = nbr1 + nbr2 + nbr3;

    // Prepare the labels for the pie chart
    QString a = QString("Candidats entre 18-22 ans: %1%").arg(QString::number((nbr1 * 100) / total, 'f', 2));
    QString b = QString("Candidats entre 23-26 ans: %1%").arg(QString::number((nbr2 * 100) / total, 'f', 2));
    QString c = QString("Candidats plus que 26 ans: %1%").arg(QString::number((nbr3 * 100) / total, 'f', 2));

    // Create the pie chart series
    QPieSeries *series = new QPieSeries();
    series->append(a, nbr1);
    series->append(b, nbr2);
    series->append(c, nbr3);

    // Show labels for non-zero slices
    if (nbr1 != 0) {
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }

    if (nbr2 != 0) {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
    }

    if (nbr3 != 0) {
        QPieSlice *slice2 = series->slices().at(2);
        slice2->setLabelVisible();
    }

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique des âges des candidats");
    chart->legend()->hide();

    // Display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 500);
    chartView->show();
}


void gestion_candidats::start_camera()
{
    M_Camera->start();
}

void gestion_candidats::stop_camera()
{
    M_Camera->stop();
}


void gestion_candidats::on_btn_start_camera_clicked()
{
    start_camera();
}

void gestion_candidats::on_btn_stop_camera_clicked()
{
    stop_camera();

}

void gestion_candidats::on_sendEmailButton_clicked() {}


void gestion_candidats::sendConfirmationEmail(const QString &email) {}



void gestion_candidats::on_Ajouter_OffreEmploi_clicked()
{
    QString titre = ui->lineEdit_TITRE->text();
    QString description = ui->lineEdit_DESCRIPTION->text();
    QString entreprise = ui->lineEdit_ENTREPRISE->text();
    QString lieu = ui->comboBox->currentText();
    QDate dateExpiration = ui->dateEdit_EXPIRATION->date();

    // Initialize an empty string for error messages
    QString errorMsg = "";


    // Create the Candidat if all validations pass
    OffreEmploi offreEmploi(titre, description, entreprise, dateExpiration, lieu);
    bool test = offreEmploi.create();
    if (test) {
        ui->tableView_offres->setModel(offreEmploi.readAll());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    // Clear the form fields
    ui->lineEdit_TITRE->clear();
    ui->lineEdit_DESCRIPTION->clear();
    ui->lineEdit_ENTREPRISE->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit_EXPIRATION->clear();
}



void gestion_candidats::on_tableView_offres_activated(const QModelIndex &index)
{
                   ui->id_label_2->setText(ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(index.row(),0)).toString());
                   ui->lineEdit_TITRE_2->setText(ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(index.row(),1)).toString());
                   ui->lineEdit_DESCRIPTION_2->setText(ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(index.row(),2)).toString());
                   ui->lineEdit_ENTREPRISE_2->setText(ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(index.row(),3)).toString());
                   ui->comboBox_2->setCurrentText(ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(index.row(),5)).toString());
                   ui->dateEdit_EXPIRATION_2->setDate(ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(index.row(),4)).toDate());

}



void gestion_candidats::on_Gestion_Offres_tabBarClicked(int index)
{
    if (index == 1) {  // Only load if it's the job offers tab
            if (!QSqlDatabase::database().isOpen()) {
                qDebug() << "Database is not open!";
                return;
            }

            ui->tableView_offres->setModel(offreEmploi.readAll());
    }
}


void gestion_candidats::on_Supprimer_offre_clicked()
{
    int id=ui->id_label_2->text().toInt();
    bool test=offreEmploi.remove(id);
    if(test)
        {
            ui->tableView_offres->setModel(offreEmploi.readAll());
            QMessageBox::information(nullptr,QObject::tr("Not OK"),
                                     QObject::tr("Suppression effectuée\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                     QObject::tr("Suppression non effectué\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);
      ui->lineEdit_TITRE_2->clear();
      ui->lineEdit_DESCRIPTION_2->clear();
      ui->lineEdit_ENTREPRISE_2->clear();
      ui->comboBox_2->setCurrentIndex(0);
      ui->dateEdit_EXPIRATION_2->clear();


}

void gestion_candidats::on_Modifier_offre_clicked()
{
    int id = ui->id_label_2->text().toInt();
    QString titre = ui->lineEdit_TITRE_2->text();
    QString description = ui->lineEdit_DESCRIPTION_2->text();
    QString entreprise = ui->lineEdit_ENTREPRISE_2->text();
    QString lieu = ui->comboBox_2->currentText();
    QDate dateExpiration = ui->dateEdit_EXPIRATION_2->date();  // Make sure to correctly get the date from QDateEdit

    offreEmploi.setTitre(titre);
    offreEmploi.setDescription(description);
    offreEmploi.setEntreprise(entreprise);
    offreEmploi.setLieu(lieu);
    offreEmploi.setDateExpiration(dateExpiration);




    bool test = offreEmploi.update(id);

    if (test) {
        ui->tableView_offres->setModel(offreEmploi.readAll());  // Refresh table
        QMessageBox::information(nullptr, QObject::tr("modifier un offreEmploi"),
                                 QObject::tr("offreEmploi modifié.\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Modifier offreEmploi"),
                              QObject::tr("Erreur !.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }

    // Clear the fields after modification
    ui->lineEdit_TITRE_2->clear();
    ui->lineEdit_DESCRIPTION_2->clear();
    ui->lineEdit_ENTREPRISE_2->clear();
    ui->comboBox_2->setCurrentText(lieu);
    ui->dateEdit_EXPIRATION_2->clear();
}

void gestion_candidats::showEvent(QShowEvent *event) {
    // Ensure the base class showEvent is called
    QWidget::showEvent(event);

    // Load the job offers into the tableView_offres
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    ui->tableView_offres->setModel(offreEmploi.readAll());
}



void gestion_candidats::on_recherche_offre_clicked()
{
    QString rech=ui->lineEdit_rech_offre->text();

             ui->tableView_offres->setModel(offreEmploi.rechercher(rech));
             ui->lineEdit_rech_offre->clear();
}

void gestion_candidats::on_tri_dateexpiration_clicked()
{

    OffreEmploi offreEmploi;
    ui->tableView_offres->setModel(offreEmploi.triDate());
}

void gestion_candidats::on_tri_titre_clicked()
{

    OffreEmploi offreEmploi;
    ui->tableView_offres->setModel(offreEmploi.triNom());
}

void gestion_candidats::on_tri_Entreprise_clicked()
{

    OffreEmploi offreEmploi;
    ui->tableView_offres->setModel(offreEmploi.triEntreprise());
}

void gestion_candidats::on_statistique_offre_clicked()
{
    // List of governorates (assuming this is already available in the class)
    QStringList gouvernorates;
    gouvernorates << "Ariana" << "Béja" << "Ben Arous" << "Bizerte"
                  << "Gabès" << "Gafsa" << "Jendouba" << "Kairouan"
                  << "Kasserine" << "Kebili" << "La Manouba" << "Le Kef"
                  << "Mahdia" << "Manouba" << "Medenine" << "Monastir"
                  << "Nabeul" << "Sfax" << "Sidi Bouzid" << "Siliana"
                  << "Souk Ahras" << "Tataouine" << "Tozeur" << "Tunis";

    QSqlQueryModel *model = new QSqlQueryModel();

    // Step 1: Calculate the total number of offers across all governorates
    float total = 0;
    for (const QString &governorate : gouvernorates) {
        QString query = QString("SELECT * FROM OffreEmploi WHERE lieu = '%1'").arg(governorate);
        model->setQuery(query);
        total += model->rowCount();
    }

    // Prepare a pie chart series to hold the data
    QPieSeries *series = new QPieSeries();

    // Step 2: Add each governorate's data to the chart and calculate its percentage based on the total
    for (const QString &governorate : gouvernorates) {
        QString query = QString("SELECT * FROM OffreEmploi WHERE lieu = '%1'").arg(governorate);
        model->setQuery(query);
        float count = model->rowCount();

        // Only add non-zero results to the chart
        if (count > 0 && total > 0) {
            // Calculate percentage based on the total number of offers
            float percentage = (count * 100) / total;
            QString label = QString("%1: %2%").arg(governorate).arg(QString::number(percentage, 'f', 2));
            series->append(label, count);
        }
    }

    // Show labels for non-zero slices
    for (int i = 0; i < series->slices().size(); ++i) {
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
    }

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des offres d'emploi par gouvernorat");
    chart->legend()->hide();

    // Display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 500);
    chartView->show();
}



void gestion_candidats::on_imprimer_offre()
{ QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_offres->model()->rowCount();
    const int columnCount = ui->tableView_offres->model()->columnCount();
    QString TT = QDateTime::currentDateTime().toString();
    out <<"<html>\n"
          "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << "<title>ERP - Liste des Offres d'emploi<title>\n "
        << "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<h1 style=\"text-align: center;\"><strong> ******Liste des Offres d'emploi******\n"+TT+" </strong></h1>"
           +"<img src=C://Users//WALID//OneDrive//Bureau//logo//logo />"
        "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
          "</br> </br>";
    // headers
    out << "<thead><tr bgcolor=#d6e5ff>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_offres->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_offres->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_offres->isColumnHidden(column)) {
                QString data =ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

