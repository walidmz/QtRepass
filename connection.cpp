#include"connection.h"
#include <QDebug>

connection::connection()
{

}
bool connection::createconnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projetQT");//inserer le nom de la source de données ODBC
db.setUserName("SYSTEM");//inserer nom de l'utilisateur
db.setPassword("1234");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void connection::closeconnection() {db.close();}
