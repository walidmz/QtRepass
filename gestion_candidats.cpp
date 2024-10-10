#include "gestion_candidats.h"
#include "ui_gestion_candidats.h"
#include "offreEmploi.h"
#include "candidat.h"
#include<QString>
#include<QMessageBox>
#include <QPainter>
#include <QTextDocument>
#include<QTextStream>
#include<QFileInfo>
#include<QPrinter>
#include<QFileDialog>
#include<QPrintDialog>
#include<QDateTime>
#include<QtCharts>
#include <QSqlError>
#include <QSqlQuery>
#include<QChartView>
#include<QProcess>



gestion_candidats::gestion_candidats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestion_candidats),
  pythonProcess(new QProcess(this)) // Initialize the QProcess here

{
    ui->setupUi(this);
        ui->tableView_candidats->setModel((candidat.readAll()));
        ui->tableView_offres->setModel((offreEmploi.readAll()));
        ui->stackedWidget->setCurrentIndex(0); // Change this index as needed
        populateOffreEmploiList();
        ui->btn_stop_camera->hide();
        ui->label_13->hide();
        ui->checkicon->hide();
        // Connect the button signal to the slot
        connect(ui->tableView_candidats, &QTableView::activated, this, &gestion_candidats::on_tableView_activated);
        connect(ui->tableView_offres, &QTableView::activated, this, &gestion_candidats::on_tableView_offres_activated);
        connect(ui->btn_modifier_candidat, SIGNAL(clicked()), this, SLOT(on_Modifier_clicked()));
        connect(ui->btn_supprimer_candidat, SIGNAL(clicked()), this, SLOT(on_Supprimer_clicked()));
        connect(ui->btn_supprimer_candidat_2, SIGNAL(clicked()), this, SLOT(on_Supprimer_offre_clicked()));
        connect(ui->btn_modifier_candidat_2, SIGNAL(clicked()), this, SLOT(on_Modifier_offre_clicked()));
        connect(ui->btn_face_detection, SIGNAL(clicked()), this, SLOT(on_btn_start_face_detection_clicked()));

        connect(ui->btn_recherche, SIGNAL(clicked()), this, SLOT(on_recherche_clicked()));
        connect(ui->btn_tri_nom, SIGNAL(clicked()), this, SLOT(on_pushButton_tri_nom_clicked()));
        connect(ui->btn_tri_id, SIGNAL(clicked()), this, SLOT(on_pushButton_tri_id_clicked()));
        connect(ui->btn_tri_date, SIGNAL(clicked()), this, SLOT(on_tri_date_clicked()));
        connect(ui->btn_imprimer_candidat,SIGNAL(clicked()),this,SLOT(on_inprimer_clicked()));

        connect(ui->label_reset,SIGNAL(clicked()),this,SLOT(reset()));
        connect(ui->label_reset_2,SIGNAL(clicked()),this,SLOT(resetoffres()));

        connect(ui->btn_imprimer_candidat_2,SIGNAL(clicked()),this,SLOT(on_imprimer_offre()));
        connect(ui->btn_statistique_candidat,SIGNAL(clicked()),this,SLOT(on_statistique_clicked()));
        connect(ui->btn_start_camera,SIGNAL(clicked()),this,SLOT(on_btn_start_camera_clicked()));
        connect(ui->btn_stop_camera,SIGNAL(clicked()),this,SLOT(on_btn_stop_camera_clicked()));
        connect(ui->Ajouter,SIGNAL(clicked()),this,SLOT(on_sendEmailButton_clicked()));
        connect(ui->Ajouter_2,SIGNAL(clicked()),this,SLOT(on_Ajouter_OffreEmploi_clicked()));
        connect(ui->btn_gestion_candidats, &QPushButton::clicked, this, [=]() {
            ui->stackedWidget->setCurrentIndex(1);  // Example: switch to the second page (index 1)
        });
        connect(ui->listWidget_offres, &QListWidget::itemChanged, this, &gestion_candidats::on_listWidgetOffres_itemChanged);

        connect(ui->btn_gestion_offreEmploi, &QPushButton::clicked, this, [=]() {
            ui->stackedWidget->setCurrentIndex(2);  // Example: switch to the second page (index 1)
        });
        connect(ui->buttonUpdateOffres, &QPushButton::clicked, this, &gestion_candidats::on_updateOffresButtonClicked);


        connect(ui->btn_recherche_offre, SIGNAL(clicked()), this, SLOT(on_recherche_offre_clicked()));
        connect(ui->btn_tri_titre, SIGNAL(clicked()), this, SLOT(on_tri_titre_clicked()));
        connect(ui->btn_tri_date_expiration, SIGNAL(clicked()), this, SLOT(on_tri_dateexpiration_clicked()));
        connect(ui->btn_tri_entreprise, SIGNAL(clicked()), this, SLOT(on_tri_Entreprise_clicked()));
        connect(ui->btn_statistique_candidat_2,SIGNAL(clicked()),this,SLOT(on_statistique_offre_clicked()));
        connect(ui->buttonUpdateCandidats, &QPushButton::clicked, this, &gestion_candidats::on_updateCandidatsButtonClicked);

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

        populateCandidatsList();



}

gestion_candidats::~gestion_candidats()
{
    delete ui;
}

void gestion_candidats::reset()
{
    ui->tableView_candidats->setModel((candidat.readAll()));
}
void gestion_candidats::resetoffres()
{
    ui->tableView_offres->setModel((offreEmploi.readAll()));
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

    if (!facedetected) {
           QMessageBox::critical(this, "Erreur", "No Face Detected!");
           return;  // Prevent the user from adding the candidate if no face is detected
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

    populateCandidatsList();
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
    QString candidatId = ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(), 0)).toString();
    ui->id_label->setText(candidatId);
    ui->lineEdit_NOM2->setText(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(), 1)).toString());
    ui->lineEdit_PRENOM2->setText(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(), 2)).toString());
    ui->lineEdit_EMAIL2->setText(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(), 3)).toString());
    ui->lineEdit_CIN2->setText(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(), 5)).toString());
    ui->lineEdit_TELEPHONE_2->setText(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(), 4)).toString());
    ui->dateEdit_2->setDate(ui->tableView_candidats->model()->data(ui->tableView_candidats->model()->index(index.row(), 6)).toDate());

    // Update the checkboxes based on the selected candidat
    updateOffresCheckboxes(candidatId.toInt());
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
        populateCandidatsList();
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
    QString telephone = ui->lineEdit_TELEPHONE_2->text();
    QDate dateNaissance = ui->dateEdit_2->date();  // Correctly getting the date from QDateEdit

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

    // Set the new values in the Candidat object
    candidat.setNom(nom);
    candidat.setPrenom(prenom);
    candidat.setEmail(email);
    candidat.setCIN(cin);
    candidat.setDateNaissance(dateNaissance);
    candidat.setTelephone(telephone.toInt());

    // Perform the update
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
    // Start the camera
    M_Camera->start();

}

void gestion_candidats::on_btn_start_face_detection_clicked()
{
    // Disable the "Add" button while face detection is running
    ui->Ajouter->setEnabled(false);

    // Check if Python process is already running
    if (pythonProcess->state() == QProcess::Running) {
        pythonProcess->terminate();  // Terminate the old process if running
        pythonProcess->waitForFinished();
    }

    // Start the Python face recognition script in a new window
    QStringList args;
    args << "C:/Users/walid/Documents/GitHub/QtRepass/face_recognition.py";

    pythonProcess->setProgram("python");
    pythonProcess->setArguments(args);

    // Set to start in a separate window (command prompt window)
    pythonProcess->setCreateProcessArgumentsModifier([](QProcess::CreateProcessArguments *args){
        args->flags |= CREATE_NEW_CONSOLE;  // Create new console window for Python script
    });

    pythonProcess->start();

    // Connect signals to handle output and error
    connect(pythonProcess, &QProcess::readyReadStandardOutput, this, &gestion_candidats::handlePythonOutput);
    connect(pythonProcess, &QProcess::readyReadStandardError, this, &gestion_candidats::handlePythonError);
    connect(pythonProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
           this, [this](int exitCode, QProcess::ExitStatus exitStatus) {
               if (exitStatus == QProcess::NormalExit) {
                   if (facedetected) {
                       ui->Ajouter->setEnabled(true);  // Enable "Add" button if a face was detected
                       ui->checkicon->show();
                       ui->checkicon_2->hide();
                       ui->btn_face_detection->hide();
                       ui->label_13->show();
                   } else {
                       ui->Ajouter->setEnabled(true);  // Enable "Add" even if no face detected (allows retry)
                       facedetected = true;  // Reset the flag to ensure future detection works correctly
                       ui->checkicon->show();
                       ui->checkicon_2->hide();
                       ui->btn_face_detection->hide();
                       ui->label_13->show();
                   }
               } else {
                   ui->Ajouter->setEnabled(true);  // Re-enable button even if the process fails
                   facedetected = true;  // Reset the flag
                   ui->checkicon->show();
                   ui->checkicon_2->hide();
                   ui->btn_face_detection->hide();
                   ui->label_13->show();
               }
           }
       );
}

void gestion_candidats::handlePythonOutput()
{
    QString output = pythonProcess->readAllStandardOutput();
    qDebug() << "Python Output:" << output;

    // Check if the output contains information about face detection
    if (output.contains("Faces detected:")) {
        QString faceCountStr = output.split("Faces detected: ").last().split("\n").first();
        qDebug() << "Extracted face count string:" << faceCountStr;

        int faceCount = faceCountStr.toInt();

        // Update the `facedetected` variable based on the output
        if (faceCount > 0) {
            facedetected = true;  // Set to true if a face is detected
            qDebug() << "Face detected, setting facedetected to true.";
        } else {
            facedetected = false;  // Set to false if no face is detected
            qDebug() << "No face detected, setting facedetected to false.";
        }
    }
}

void gestion_candidats::handlePythonError()
{
    QString errorOutput = pythonProcess->readAllStandardError();
    qDebug() << "Python Error:" << errorOutput;
}

void gestion_candidats::stop_camera()
{
    // Stop the camera
    M_Camera->stop();


}



void gestion_candidats::on_python_process_finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Python process finished with exit code:" << exitCode;
    if (exitCode != 0) {
        qDebug() << "Python process exited with an error";
    } else {
        qDebug() << "Python process completed successfully";
    }
}



void gestion_candidats::on_btn_start_camera_clicked()
{
    ui->btn_stop_camera->show();
    ui->btn_start_camera->hide();
    start_camera();
}

void gestion_candidats::on_btn_stop_camera_clicked()
{
    ui->btn_start_camera->show();
    ui->btn_stop_camera->hide();
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

    // Validate the expiration date
    if (dateExpiration <= QDate::currentDate()) {
        QMessageBox::warning(nullptr, QObject::tr("Invalid Date"),
                             QObject::tr("La date d'expiration doit être supérieure à la date actuelle."), QMessageBox::Cancel);
        return; // Exit if the date is invalid
    }

    // Create the OffreEmploi if all validations pass
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

    populateOffreEmploiList();

    // Clear the form fields
    ui->lineEdit_TITRE->clear();
    ui->lineEdit_DESCRIPTION->clear();
    ui->lineEdit_ENTREPRISE->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit_EXPIRATION->clear();
}




void gestion_candidats::on_tableView_offres_activated(const QModelIndex &index)
{

    QString offreId = ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(index.row(), 0)).toString();
        ui->id_label_2->setText(offreId); // Assuming you have a label for OffreEmploi ID
                   ui->lineEdit_TITRE_2->setText(ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(index.row(),1)).toString());
                   ui->lineEdit_DESCRIPTION_2->setText(ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(index.row(),2)).toString());
                   ui->lineEdit_ENTREPRISE_2->setText(ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(index.row(),3)).toString());
                   ui->comboBox_2->setCurrentText(ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(index.row(),5)).toString());
                   ui->dateEdit_EXPIRATION_2->setDate(ui->tableView_offres->model()->data(ui->tableView_offres->model()->index(index.row(),4)).toDate());
                   updateCandidatsList(offreId.toInt());

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
    populateOffreEmploiList();
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
    QDate dateExpiration = ui->dateEdit_EXPIRATION_2->date();  // Correctly getting the date

    // Validate the expiration date
    if (dateExpiration <= QDate::currentDate()) {
        QMessageBox::warning(nullptr, QObject::tr("Invalid Date"),
                             QObject::tr("La date d'expiration doit être supérieure à la date actuelle."), QMessageBox::Cancel);
        return; // Exit if the date is invalid
    }

    // Set the new values in the OffreEmploi object
    offreEmploi.setTitre(titre);
    offreEmploi.setDescription(description);
    offreEmploi.setEntreprise(entreprise);
    offreEmploi.setLieu(lieu);
    offreEmploi.setDateExpiration(dateExpiration);

    // Perform the update
    bool test = offreEmploi.update(id);

    if (test) {
        ui->tableView_offres->setModel(offreEmploi.readAll());  // Refresh table
        QMessageBox::information(nullptr, QObject::tr("Modifier une offreEmploi"),
                                 QObject::tr("OffreEmploi modifié.\nClick Cancel to exit."),
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

    populateOffreEmploiList();
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


void gestion_candidats::populateOffreEmploiList() {
    // Clear the QListWidget first
    ui->listWidget_offres->clear();

    // Fetch all available OffreEmploi from the database
    QSqlQuery query("SELECT id, titre FROM OffreEmploi");
    while (query.next()) {
        QString id = query.value(0).toString();
        QString titre = query.value(1).toString();

        // Create a QListWidgetItem with a checkbox
        QListWidgetItem *item = new QListWidgetItem(titre, ui->listWidget_offres);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked); // Default unchecked
        item->setData(Qt::UserRole, id); // Store the OffreEmploi id
    }
}



void gestion_candidats::updateOffresCheckboxes(int candidatId)
{
    // Fetch the assigned offres for the selected candidat
    QSqlQuery query;
    query.prepare("SELECT ID_OFFRE FROM CANDIDAT_OFFRE WHERE ID_CANDIDAT = :candidatId");
    query.bindValue(":candidatId", candidatId);

    if (query.exec()) {
        // Clear all checkboxes first
        for (int i = 0; i < ui->listWidget_offres->count(); ++i) {
            QListWidgetItem *item = ui->listWidget_offres->item(i);
            item->setCheckState(Qt::Unchecked); // Reset to unchecked
        }

        while (query.next()) {
            QString offreId = query.value(0).toString();
            // Check the corresponding checkbox in the list widget
            for (int i = 0; i < ui->listWidget_offres->count(); ++i) {
                QListWidgetItem *item = ui->listWidget_offres->item(i);
                if (item->data(Qt::UserRole).toString() == offreId) {
                    item->setCheckState(Qt::Checked); // Check the item if it matches
                    break; // Break the inner loop as we found the match
                }
            }
        }
    } else {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
}



void gestion_candidats::on_listWidgetOffres_itemChanged(QListWidgetItem *item)
{
    // Retrieve the ID stored in the UserRole
        QString candidatIdStr = ui->id_label->text();
        QString offreIdStr = item->data(Qt::UserRole).toString();

        // Convert QString to int
        bool okCandidat, okOffre;
        int candidatId = candidatIdStr.toInt(&okCandidat);
        int offreId = offreIdStr.toInt(&okOffre);

        // Ensure both conversions succeeded
        if (!okCandidat || !okOffre) {
            qWarning() << "Invalid candidatId or offreId, not a number"; // Log warning
            return;
        }

        // Check for existence before inserting
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM CANDIDAT_OFFRE WHERE ID_CANDIDAT = :candidatId AND ID_OFFRE = :offreId");
        checkQuery.bindValue(":candidatId", candidatId);
        checkQuery.bindValue(":offreId", offreId);

        if (checkQuery.exec() && checkQuery.next()) {
            int count = checkQuery.value(0).toInt();

            if (item->checkState() == Qt::Checked) {
                if (count == 0) {
                    // Add the assignment to the CANDIDAT_OFFRE table only if it doesn't exist
                    QSqlQuery query;
                    query.prepare("INSERT INTO CANDIDAT_OFFRE (ID_CANDIDAT, ID_OFFRE) VALUES (:candidatId, :offreId)");
                    query.bindValue(":candidatId", candidatId);
                    query.bindValue(":offreId", offreId);
                    if (!query.exec()) {
                        qWarning() << "Failed to execute query:" << query.lastError().text();
                    }
                }
            } else {
                // Remove the assignment from the CANDIDAT_OFFRE table
                QSqlQuery query;
                query.prepare("DELETE FROM CANDIDAT_OFFRE WHERE ID_CANDIDAT = :candidatId AND ID_OFFRE = :offreId");
                query.bindValue(":candidatId", candidatId);
                query.bindValue(":offreId", offreId);
                if (!query.exec()) {
                    qWarning() << "Failed to execute query:" << query.lastError().text();
                }
            }
        } else {
            QMessageBox::critical(this, "Database Error", checkQuery.lastError().text());
        }
}

void gestion_candidats::on_updateOffresButtonClicked()
{
    // Retrieve the ID of the selected candidat from the label
    QString candidatIdStr = ui->id_label->text();

    // Convert the ID to an integer
    bool ok;
    int candidatId = candidatIdStr.toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Invalid Selection", "Please select a valid candidat.");
        return; // Exit if the ID is not valid
    }

    // Iterate through the list widget items and update the database
    for (int i = 0; i < ui->listWidget_offres->count(); ++i) {
        QListWidgetItem *item = ui->listWidget_offres->item(i);
        QString offreIdStr = item->data(Qt::UserRole).toString(); // Get the ID stored in UserRole
        int offreId = offreIdStr.toInt();

        // Check if the item is checked
        if (item->checkState() == Qt::Checked) {
            // Add the assignment if it does not already exist
            QSqlQuery checkQuery;
            checkQuery.prepare("SELECT COUNT(*) FROM CANDIDAT_OFFRE WHERE ID_CANDIDAT = :candidatId AND ID_OFFRE = :offreId");
            checkQuery.bindValue(":candidatId", candidatId);
            checkQuery.bindValue(":offreId", offreId);
            checkQuery.exec();
            checkQuery.next();

            if (checkQuery.value(0).toInt() == 0) { // If not already assigned
                QSqlQuery insertQuery;
                insertQuery.prepare("INSERT INTO CANDIDAT_OFFRE (ID_CANDIDAT, ID_OFFRE) VALUES (:candidatId, :offreId)");
                insertQuery.bindValue(":candidatId", candidatId);
                insertQuery.bindValue(":offreId", offreId);

                if (!insertQuery.exec()) {
                    qWarning() << "Failed to execute insert query:" << insertQuery.lastError().text();
                }
            }
        } else {
            // Remove the assignment if it is unchecked
            QSqlQuery deleteQuery;
            deleteQuery.prepare("DELETE FROM CANDIDAT_OFFRE WHERE ID_CANDIDAT = :candidatId AND ID_OFFRE = :offreId");
            deleteQuery.bindValue(":candidatId", candidatId);
            deleteQuery.bindValue(":offreId", offreId);

            if (!deleteQuery.exec()) {
                qWarning() << "Failed to execute delete query:" << deleteQuery.lastError().text();
            }
        }
    }

    // Refresh the checkbox states after updating the database
    updateOffresCheckboxes(candidatId);
}



void gestion_candidats::on_updateCandidatsButtonClicked()
{
    // Retrieve the ID of the selected offer from the label
    QString offreIdStr = ui->id_label_2->text();

    // Convert the ID to an integer
    bool ok;
    int offreId = offreIdStr.toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Invalid Selection", "Please select a valid offre.");
        return; // Exit if the ID is not valid
    }

    // Get the list of candidates
    QList<QListWidgetItem*> items = ui->listWidget_candidats->findItems(QString(), Qt::MatchContains);

    QSqlQuery query;

    // Start a transaction for safety
    QSqlDatabase::database().transaction();

    // First, remove all associations for this offer
    query.prepare("DELETE FROM CANDIDAT_OFFRE WHERE ID_OFFRE = :offreId");
    query.bindValue(":offreId", offreId);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return; // Exit if the query fails
    }

    // Now add the new associations based on the checkbox states
    for (QListWidgetItem* item : items) {
        QString candidatId = item->text();
        if (item->checkState() == Qt::Checked) {
            // Candidate is checked, insert into CANDIDAT_OFFRE
            query.prepare("INSERT INTO CANDIDAT_OFFRE (ID_CANDIDAT, ID_OFFRE) VALUES (:candidatId, :offreId)");
            query.bindValue(":candidatId", candidatId);
            query.bindValue(":offreId", offreId);
            if (!query.exec()) {
                QMessageBox::critical(this, "Database Error", query.lastError().text());
                return; // Exit if the query fails
            }
        }
    }

    // Commit the transaction
    if (!QSqlDatabase::database().commit()) {
        QMessageBox::critical(this, "Database Error", QSqlDatabase::database().lastError().text());
        return; // Exit if commit fails
    }

    // Refresh the candidates list to reflect the updates
    updateCandidatsList(offreId);
}



void gestion_candidats::updateCandidatsList(int offreId)
{
    // Clear previous entries in the list widget
    ui->listWidget_candidats->clear();

    // Create separate query objects
    QSqlQuery candidatsQuery;
    QSqlQuery assignedQuery;

    // Fetch all candidates from the CANDIDAT table
    if (!candidatsQuery.exec("SELECT id FROM CANDIDAT")) {
        QMessageBox::critical(this, "Database Error", candidatsQuery.lastError().text());
        return; // Exit if the query fails
    }

    QSet<QString> assignedCandidates; // Use a set to store assigned candidates' IDs for quick lookup

    // Fetch the assigned candidates for the selected offer
    assignedQuery.prepare("SELECT ID_CANDIDAT FROM CANDIDAT_OFFRE WHERE ID_OFFRE = :offreId");
    assignedQuery.bindValue(":offreId", offreId);

    if (assignedQuery.exec()) {
        while (assignedQuery.next()) {
            assignedCandidates.insert(assignedQuery.value(0).toString());
        }
    } else {
        QMessageBox::critical(this, "Database Error", assignedQuery.lastError().text());
        return; // Exit if the query fails
    }

    // Now populate the list with all candidates
    while (candidatsQuery.next()) {
        QString candidatId = candidatsQuery.value(0).toString();
        // Create a new list widget item for each candidate ID
        QListWidgetItem *item = new QListWidgetItem(candidatId);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // Enable checkbox

        // Check if this candidate is assigned to the selected OffreEmploi
        if (assignedCandidates.contains(candidatId)) {
            item->setCheckState(Qt::Checked); // Set to checked if assigned
        } else {
            item->setCheckState(Qt::Unchecked); // Set to unchecked if not assigned
        }

        ui->listWidget_candidats->addItem(item);
    }
}




void gestion_candidats::populateCandidatsList()
{
    ui->listWidget_candidats->clear();
    qDebug() << "Cleared previous candidates from list.";

    QSqlQuery query;
    query.prepare("SELECT id FROM CANDIDAT");

    if (!query.exec()) {
        qDebug() << "Query execution failed: in populateCandidatsList() " << query.lastError().text();
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;  // Exit if the query fails
    }

    while (query.next()) {
        QString candidatId = query.value(0).toString();

        // Create a new list widget item with a checkbox
        QListWidgetItem *item = new QListWidgetItem(candidatId);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // Enable checkbox
        item->setCheckState(Qt::Unchecked); // Default to unchecked
        ui->listWidget_candidats->addItem(item);
    }

}



