#include "gestion_candidats.h"
#include "ui_gestion_candidats.h"
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
        ui->tableView->setModel((candidat.readAll()));
        // Connect the button signal to the slot
        connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

}

gestion_candidats::~gestion_candidats()
{
    delete ui;
}


void gestion_candidats::on_Ajouter_clicked()
{
   QString cin=ui->lineEdit_CIN->text();
   QString nom=ui->lineEdit_NOM->text();
   QString prenom=ui->lineEdit_PRENOM->text();
   QString email=ui->lineEdit_EMAIL->text();
   QDate date= ui-> dateEdit->date();
   QString telephone=ui->lineEdit_TELEPHONE->text();
   Candidat candidat( nom,prenom, email,cin,date, telephone );
   bool test=candidat.create();
   if(test)
       {
           ui->tableView->setModel((candidat.readAll()));
          QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("Ajout effectué\n"
                                               "Click Cancel to exit."),QMessageBox::Cancel);
       }
          else
              QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                       QObject::tr("Ajout non effectué\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);

         ui->lineEdit_CIN->clear();
         ui->lineEdit_NOM->clear();
         ui->lineEdit_PRENOM->clear();
         ui->lineEdit_EMAIL->clear();
         ui->dateEdit->clear();
         ui->lineEdit_TELEPHONE->clear();
}
void gestion_candidats::on_tableView_activated(const QModelIndex &index)
{

                   ui->lineEdit_CIN_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
                   ui->lineEdit_NOM_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
                   ui->lineEdit_PRENOM_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString());
                   ui->lineEdit_ADRESSE_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toString());
                   ui->lineEdit_MARCHANDISE_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),4)).toString());

}

void gestion_candidats::on_Supprimer_clicked()
{/*
    int cin=ui->lineEdit_CIN_2->text().toInt();
    bool test=f.supprimer(cin);
    if(test)
        {
            ui->tableView->setModel(f.afficher());
            QMessageBox::information(nullptr,QObject::tr("Not OK"),
                                     QObject::tr("Suppression effectuée\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                     QObject::tr("Suppression non effectué\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);
      ui->lineEdit_CIN_2->clear();
      ui->lineEdit_NOM_2->clear();
      ui->lineEdit_PRENOM_2->clear();
      ui->lineEdit_ADRESSE_2->clear();
      ui->lineEdit_MARCHANDISE_2->clear();
*/
}


void gestion_candidats::on_Modifier_clicked()
{
   /* int cin=ui->lineEdit_cin_2->text().toInt();
   QString NOMF=ui->lineEdit_NOM_2->text();
   QString PRENOMF=ui->lineEdit_PRENOM_2->text();
   QString CLASSE=ui->lineEdit_ADRESSE_2->text();
   QString ID=ui->lineEdit_MARCHANDISE_2->text();
   fournisseur f( cin,  NOMF, PRENOMF, CLASSE, ID );
   bool test=f.modifier(cin,  NOMF, PRENOMF, CLASSE, ID );
   if(test)
                   {
                       ui->tableView->setModel(f.afficher());
                       QMessageBox::information(nullptr, QObject::tr("modifier un etudiant"),
                                         QObject::tr("fournisseur  modifié.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
                    }

                         else
                             QMessageBox::critical(nullptr, QObject::tr("Modifier etudiant"),
                                         QObject::tr("Erreur !.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
   ui->lineEdit_cin_2->clear();
    ui->lineEdit_NOM_2->clear();
  ui->lineEdit_PRENOM_2->clear();
  ui->lineEdit_ADRESSE_2->clear();
  ui->lineEdit_MARCHANDISE_2->clear();
*/

}

void gestion_candidats::on_Gestion_Fournisseur_tabBarClicked(int index)
{
    /*
    index=1;
    ui->tableView->setModel(f.afficher());
*/
}

void gestion_candidats::on_recherche_clicked()
{
    /*
    QString rech=ui->lineEdit_rech->text();

             ui->tableView->setModel(f.rechercherM(rech));
             ui->lineEdit_rech->clear();
*/

}

void gestion_candidats::on_triC_clicked()
{
    /*
    fournisseur f;
    ui->tableView->setModel(f.triC());
    */
}

void gestion_candidats::on_pushButton_triN_clicked()
{
    /*fournisseur f;
    ui->tableView->setModel(f.triN());*/
}

void gestion_candidats::on_pushButton_triA_clicked()
{/*

    fournisseur f;
    ui->tableView->setModel(f.triA());*/
}

void gestion_candidats::on_inprimer_clicked()
{/* QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();
    QString TT = QDateTime::currentDateTime().toString();
    out <<"<html>\n"
          "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << "<title>ERP - COMmANDE LIST<title>\n "
        << "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<h1 style=\"text-align: center;\"><strong> ******LISTE DES  licence commerciale ******"+TT+" </strong></h1>"
           +"<img src=C://Users//WALID//OneDrive//Bureau//logo//logo />"
        "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
          "</br> </br>";
    // headers
    out << "<thead><tr bgcolor=#d6e5ff>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data =ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
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

    delete document;*/
}

void gestion_candidats::on_statistique_clicked()
{/*
    QSqlQueryModel * model= new QSqlQueryModel();
                                model->setQuery("select * from FOURNISSEUR where PRIX_UNITAIRE < 400 ");
                                float nbr1=model->rowCount();
                                model->setQuery("select * from FOURNISSEUR where PRIX_UNITAIRE  between 400 and 700 ");
                                float nbr2=model->rowCount();
                                model->setQuery("select * from FOURNISSEUR where PRIX_UNITAIRE >700 ");
                                float nbr3=model->rowCount();
                                float total=nbr1+nbr2+nbr3;
                                QString a=QString(" PRIX_UNITAIRE< 400"+  QString::number((nbr1*100)/total,'f',2)+"%" );
                                QString b=QString(" PRIX_UNITAIRE between 400 and 700"+  QString::number((nbr2*100)/total,'f',2)+"%" );
                                QString c=QString(" PRIX_UNITAIRE >700"+ QString::number((nbr3*100)/total,'f',2)+"%" );
                                QPieSeries *series = new QPieSeries();
                                series->append(a,nbr1);
                                series->append(b,nbr2);
                                series->append(c,nbr3);
                        if (nbr1!=0)
                        {QPieSlice *slice = series->slices().at(0);
                         slice->setLabelVisible();
                         slice->setPen(QPen());}
                        if ( nbr2!=0)
                        {
                                 // Add label, explode and define brush for 2nd slice
                                 QPieSlice *slice1 = series->slices().at(1);
                                 //slice1->setExploded();
                                 slice1->setLabelVisible();
                        }
                        if(nbr3!=0)
                        {
                                 // Add labels to rest of slices
                                 QPieSlice *slice2 = series->slices().at(2);
                                 //slice1->setExploded();
                                 slice2->setLabelVisible();
                        }
                                // Create the chart widget
                                QChart *chart = new QChart();
                                // Add data to chart with title and hide legend
                                chart->addSeries(series);
                                chart->setTitle("Statistique des prix untaires par marchandises ");
                                chart->legend()->hide();
                                // Used to display the chart
                                QChartView *chartView = new QChartView(chart);
                                chartView->setRenderHint(QPainter::Antialiasing);
                                chartView->resize(1000,500);
                                chartView->show();*/
}

void gestion_candidats::on_pushButton_clicked()
{
        //gestionTeacherDialog->show();
}

