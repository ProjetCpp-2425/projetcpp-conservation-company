#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QSqlError>
#include<QObject>
#include<QMessageBox>//afficher un message de succès ou d'échec d'une opération
#include<map>
#include <QSqlQueryModel>

#include <QPdfWriter>
#include <QPainter>
#include <QSqlRecord>
#include <QFileDialog>

//Ce constructeur initialise les attributs avec des valeurs par défaut.
client::client()
{
IDENTIFIANT=""; NOM=""; PRENOM=""; TELEPHONE=0; EMAIL="";
}


client::client(QString IDENTIFIANT,QString NOM,QString PRENOM,QString EMAIL, int TELEPHONE )
{this->IDENTIFIANT=IDENTIFIANT; this->NOM=NOM; this->PRENOM=PRENOM;this->TELEPHONE=TELEPHONE;this->EMAIL=EMAIL;}


//getTELEPHONE() retourne le numéro de téléphone.
int client:: getTELEPHONE(){return TELEPHONE;}
QString client:: getNOM(){return NOM;}
QString client::getPRENOM(){return PRENOM;}
QString client::getEMAIL(){return EMAIL;}
QString client::getIDENTIFIANT(){return IDENTIFIANT;}
//setTELEPHONE() modifie le numéro de téléphone.
void client::setTELEPHONE(int TELEPHONE){this->TELEPHONE=TELEPHONE;}
void client::setNOM(QString NOM){this->NOM=NOM;}
void client::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void client::setEMAIL(QString EMAIL){this->EMAIL=EMAIL;}
void client::setIDENTIFIANT(QString IDENTIFIANT){this->IDENTIFIANT=IDENTIFIANT;}


bool client::ajouter()
{
    //Création d'un objet QSqlQuery (objet) permet d'envoyer des requêtes SQL
    QSqlQuery query;

    //Prépare une requête SQL pour insérer un nouvel enregistrement
    query.prepare("INSERT INTO CLIENT (IDENTIFIANT, NOM, PRENOM, EMAIL, TELEPHONE) "
                  "VALUES (:IDENTIFIANT, :NOM, :PRENOM, :EMAIL, :TELEPHONE)");

    // permet d'ajouter dans le champs préparer
    query.bindValue(":IDENTIFIANT", IDENTIFIANT);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":EMAIL", EMAIL); // Assurez-vous que TÉLÉPHONE est un entier
    query.bindValue(":TELEPHONE", TELEPHONE);

    qDebug() << query.lastQuery(); // Afficher la requête préparée pour le débogage

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion : " << query.lastError().text();
        return false; // Échec de l'insertion
    }

    return true; // Insertion réussie
}




QSqlQueryModel* client::afficher() {

    //Crée un objet QSqlQueryModel pour contenir les données récupérées de la base de données.
    QSqlQueryModel* model = new QSqlQueryModel();

    // Définir la requête SQL pour récupérer les données de la table CLIENT
    model->setQuery("SELECT * FROM CLIENT");

    // Définir les en-têtes de colonnes pour l'affichage
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));

    return model;
}







 bool client::supprimer(QString IDENTIFIANT) {

    // Supprimer les espaces et caractères non imprimables
   IDENTIFIANT = IDENTIFIANT.trimmed();

   if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "La base de données n'est pas ouverte. Vérifiez la connexion.";
        return false;
        }

    QSqlQuery query;

     // Vérifiez si l'identifiant existe
     query.prepare("SELECT COUNT(*) FROM CLIENT WHERE IDENTIFIANT = :IDENTIFIANT");
     query.bindValue(":IDENTIFIANT", IDENTIFIANT);


     //Exécute la requête. Si l'exécution échoue, affiche un message d'erreur et retourne false.
     if (!query.exec()) {
         qDebug() << "Erreur lors de la vérification de l'existence de l'identifiant : " << query.lastError().text();
          return false;
      }

    query.next();//va récupérer le nombre de clients correspondant à l'identifiant.

    //Indique combien de lignes correspondent à l'identifiant fourni.
    int count = query.value(0).toInt();
    qDebug() << "Count for IDENTIFIANT" << IDENTIFIANT << ":" << count;

    if (count == 0) {
         qDebug() << "Identifiant non trouvé : " << IDENTIFIANT;
          return false;
        }

     // Si l'identifiant existe, procédez à la suppression
      query.prepare("DELETE FROM CLIENT WHERE IDENTIFIANT = :IDENTIFIANT");
      query.bindValue(":IDENTIFIANT", IDENTIFIANT);

      if (!query.exec()) {
         qDebug() << "Erreur lors de la suppression : " << query.lastError().text();
          return false;
            }

            return true;
        }




        bool client::Modifier(QString IDENTIFIANT, QString NOM, QString PRENOM,QString EMAIL, int TELEPHONE)
        {

            QSqlQuery query;
            //Assure que le numéro de téléphone soit sous le format approprié pour l'insertion dans la base de données.
            QString TELEPHONE_string =QString::number(TELEPHONE);
            query.prepare("UPDATE Client SET NOM=:NOM ,PRENOM=:PRENOM, EMAIL=:EMAIL, TELEPHONE=:TELEPHONE WHERE IDENTIFIANT=:IDENTIFIANT");

            query.bindValue(":IDENTIFIANT",IDENTIFIANT);
            query.bindValue(":NOM", NOM);
            query.bindValue(":PRENOM", PRENOM);
            query.bindValue(":EMAIL", EMAIL);
            query.bindValue(":TELEPHONE",TELEPHONE_string);

             return  query.exec();

     }


     //a : Un terme de recherche (type QString) pour effectuer la recherche dans la base de données.
     //g : Un pointeur vers un objet QTableView qui sera mis à jour avec les résultats de la recherche.


 void client::rechercher(const QString &a, QTableView *g)
            {

    QSqlQuery qry;

    //stocker les résultats de la requête SQL sous forme de modèle
    QSqlQueryModel *m = new QSqlQueryModel();

    qry.prepare("SELECT * FROM Client WHERE NOM LIKE :searchTerm OR PRENOM LIKE :searchTerm OR IDENTIFIANT LIKE :searchTerm OR EMAIL LIKE :searchTerm OR TELEPHONE LIKE :searchTerm");

    // Utilisation du '%' pour la recherche par début de mot
    qry.bindValue(":searchTerm", a + "%");

    if (qry.exec()) {

        //permet au modèle de stocker les résultats de la requête SQL
         m->setQuery(qry);
         g->setModel(m);  // Mise à jour du modèle de la table
         }
   else {
          qDebug() << "Erreur lors de la recherche : " << qry.lastError().text();
         }
         }



  QSqlQueryModel* client::trierclient(const QString& critere)
        {
           QSqlQueryModel *model = new QSqlQueryModel();

           // Création de la requête SQL en fonction du critère passé
          QString query;
          if (critere == "NOM") {
           query = "SELECT * FROM CLIENT ORDER BY NOM ASC";
          } else if (critere == "PRENOM") {
            query = "SELECT * FROM CLIENT ORDER BY PRENOM ASC";
            } else if (critere == "TELEPHONE") {
              query = "SELECT * FROM CLIENT ORDER BY TELEPHONE ASC";
            }

            // charge les résultats dans le modèle.
             model->setQuery(query);

             // Définir les en-têtes de colonnes pour l'affichage
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));

               return model;
              }


            bool client::exporterPDF()
            {
                // Choisir l'emplacement de sauvegarde
                QString filename = QFileDialog::getSaveFileName(nullptr, "Enregistrer en PDF", "", "*.pdf");
                if (filename.isEmpty())
                    return false;


    //vérifie si l'utilisateur a spécifié une extension pour le fichier. Si ce n'est pas le cas, elle ajoute l'extension .pdf au nom du fichier.
                if (QFileInfo(filename).suffix().isEmpty())
                    filename.append(".pdf");


                // Un objet QPdfWriter : Création du document PDF
                QPdfWriter pdfWriter(filename);
                pdfWriter.setPageSize(QPageSize(QPageSize::A4));
                pdfWriter.setResolution(300);// 300 dpi pour une qualité d'impression optimale.

                //Un QPainter est initialisé pour dessiner sur le document PDF.
                QPainter painter(&pdfWriter);
                int yPos = 50;

                // Titre du document
                painter.setFont(QFont("Helvetica", 14, QFont::Bold));  // Taille de police réduite pour le titre
                painter.drawText(2000, yPos, "Liste des Clients");
                yPos += 100;

                // Définir des largeurs pour les colonnes plus petites
                int col1Width = 500;
                int col2Width = 800;
                int col3Width = 1100;
                int col4Width = 1600;
                int col5Width = 2000;
                int tableWidth = 2500;

                // En-tête du tableau (police plus petite pour gagner de l'espace)
                painter.setFont(QFont("Helvetica", 10, QFont::Bold));
                painter.drawText(100, yPos, "IDENTIFIANT");
                painter.drawText(col2Width, yPos, "NOM");
                painter.drawText(col3Width, yPos, "PRENOM");
                painter.drawText(col4Width, yPos, "EMAIL");
                painter.drawText(col5Width, yPos, "TELEPHONE");

                // Tracer les lignes du tableau
                painter.drawLine(50, yPos + 10, tableWidth, yPos + 10); // Ligne en bas de l'en-tête
                yPos += 30;

                // Requête SQL pour récupérer tous les clients
                QSqlQuery query;
                query.prepare("SELECT IDENTIFIANT, NOM, PRENOM, EMAIL, TELEPHONE FROM Client");

                if (query.exec()) {
                    // Remplissage du tableau avec les données des clients
                    painter.setFont(QFont("Helvetica", 8));  // Taille de police réduite pour les données
                    while (query.next()) {
                        QString identifiant = query.value("IDENTIFIANT").toString();
                        QString nom = query.value("NOM").toString();
                        QString prenom = query.value("PRENOM").toString();
                        QString email = query.value("EMAIL").toString();
                        QString telephone = query.value("TELEPHONE").toString();

                        // Affichage des données dans le tableau
                        painter.drawText(100, yPos, identifiant);
                        painter.drawText(col2Width, yPos, nom);
                        painter.drawText(col3Width, yPos, prenom);
                        painter.drawText(col4Width, yPos, email);
                        painter.drawText(col5Width, yPos, telephone);

                        // Tracer les lignes de séparation entre les données
                        painter.drawLine(50, yPos + 5, tableWidth, yPos + 5);  // Ligne sous chaque ligne de données
                        yPos += 30;  // Espacement plus petit entre les lignes
                    }
                } else {
                    qWarning() << "Erreur de requête : " << query.lastError().text();
                    return false;
                }

                painter.end(); // Fin du dessin et enregistrement du PDF

                return true;
            }




                int client::calculerPoints(QString IDENTIFIANT)
                {
                    QSqlQuery qry;
                    int nbr=0;
                    bool test;

                    qry.prepare("select COUNT(*) from CLIENT,ACHETER where CLIENT.IDENTIFIANT=ACHETER.IDENTIFIANTC AND CLIENT.IDENTIFIANT=:IDENTIFIANT");

                    qry.bindValue(":IDENTIFIANT",IDENTIFIANT);
                    qry.exec();

                    while(qry.next())

        {

            nbr=qry.value("COUNT(*)").toInt();

        }

        qry.prepare("UPDATE CLIENT SET POINTSF=:nbr WHERE IDENTIFIANT=:IDENTIFIANT");
        qry.bindValue(":nbr",nbr);
        qry.bindValue(":IDENTIFIANT",IDENTIFIANT);
        test=qry.exec();

        if (test)
        {
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("points ajouter avec success.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        }

        else

        {

            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("ajout de points failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }

        return nbr;


    }



                bool client::remise(QString IDENTIFIANT) {
                    QSqlQuery qry;
                    int points = 0;
                    QString remiseAvecPourcentage;

                    // Récupérer les points fidélité du client
                    qry.prepare("SELECT POINTSF FROM CLIENT WHERE IDENTIFIANT = :IDENTIFIANT");
                    qry.bindValue(":IDENTIFIANT", IDENTIFIANT);

                    if (!qry.exec()) {
                        qDebug() << "Erreur dans la requête SELECT:" << qry.lastError().text();
                        return false;
                    }

                    if (qry.next()) {
                        points = qry.value("POINTSF").toInt();
                    } else {
                        qDebug() << "Client introuvable avec IDENTIFIANT:" << IDENTIFIANT;
                        return false;
                    }

                    // Calcul de la remise basée sur les points fidélité
                    double remise = 0.0;
                    if (points >= 5) {
                        remise = (points / 5) * 10; // Chaque palier de 5 points ajoute 10% de remise
                        if (remise > 100) remise = 100; // Plafonner la remise à 100%
                    } else {
                        qDebug() << "Pas assez de points pour une remise.";
                        return false;
                    }

                    // Ajouter le symbole % à la remise
                    remiseAvecPourcentage = QString("%1%").arg(QString::number(remise, 'f', 2));

                    // Mise à jour de la remise dans la base de données
                    qry.prepare("UPDATE CLIENT SET PROMO = :remise WHERE IDENTIFIANT = :IDENTIFIANT");
                    qry.bindValue(":remise", remiseAvecPourcentage); // Insère "10%" ou "20%"
                    qry.bindValue(":IDENTIFIANT", IDENTIFIANT);

                    if (!qry.exec()) {
                        qDebug() << "Erreur dans la requête UPDATE:" << qry.lastError().text();
                        return false;
                    }

                    return true;
                }




                /*QString client::genererStatistiquesPoints() {
                    QSqlQuery qry;
                    QString resultat;
                    QMap<int, int> pointsDistribution; // Clé : nombre de points, Valeur : nombre de clients.

                    // Récupérer tous les clients et leurs points.
                    qry.prepare("SELECT POINTSF FROM CLIENT");
                    if (!qry.exec()) {
                        return "Erreur lors de l'extraction des données.";
                    }

                    // Parcourir les résultats pour construire la distribution des points.
                    while (qry.next()) {
                        int points = qry.value(0).toInt();
                        pointsDistribution[points]++;
                    }

                    // Construire l'histogramme en texte.
                    resultat += "Statistiques des points des clients :\n";
                    for (auto it = pointsDistribution.cbegin(); it != pointsDistribution.cend(); ++it) {
                        resultat += QString("Points : %1 -> Nombre de clients : %2\n")
                                        .arg(it.key())
                                        .arg(it.value());
                    }

                    return resultat;
                }*/

