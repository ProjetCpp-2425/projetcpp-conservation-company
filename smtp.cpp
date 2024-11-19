#include "smtp.h"

smtp::smtp( const QString &user, const QString &pass, const QString &host, int port, int timeout )
{
    //QSslSocket, qui est un socket sécurisé pour la communication via SSL/TLS.
    socket = new QSslSocket(this);

    //Cette connexion permet au programme de réagir immédiatement dès qu'il y a des données entrantes.
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    //Notifier ou initialiser des processus après l'établissement de la connexion avec le serveur SMTP.
    connect(socket, SIGNAL(connected()), this, SLOT(connected() ) );
    //Permet de détecter, afficher ou enregistrer les erreurs réseau,
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this,SLOT(errorReceived(QAbstractSocket::SocketError)));

    //Fournir un mécanisme pour observer et réagir aux changements d'état de la connexion.
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));

    //Gérer les nettoyages nécessaires ou notifier que la connexion est terminée.
    connect(socket, SIGNAL(disconnected()), this,SLOT(disconnected()));


    this->user = user;
    this->pass = pass;

    this->host = host;
    this->port = port;
    this->timeout = timeout;
}



void smtp::sendMail(const QString &from, const QString &to, const QString &subject, const QString &body, QStringList files)
{

    // Prépare le message avec les champs standard du protocole SMTP.
    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");

    //MIME protocole standard qui permet d'envoyer des e-mails contenant des fichiers, des images
    message.append("MIME-Version: 1.0\n");
    message.append("Content-Type: multipart/mixed; boundary=frontier\n\n");
    message.append( "--frontier\n" );

    //message.append( "Content-Type: text/html\n\n" );  //Uncomment this for HTML formating, coment the line below
    message.append( "Content-Type: text/plain\n\n" );

    //Ajoute le contenu principal du message
    message.append(body);
    message.append("\n\n");

    // Vérifie s'il y a des fichiers en pièce jointe.
    if(!files.isEmpty())
    {
        qDebug() << "Files to be sent: " << files.size();
        foreach(QString filePath, files) // Parcourt chaque fichier à envoyer en pièce jointe.

        {
            QFile file(filePath);// Crée un objet QFile pour manipuler le fichier.

            // Vérifie si le fichier existe.
            if(file.exists())
            {
                if (!file.open(QIODevice::ReadOnly))
                {
                    qDebug("Couldn't open the file");
                    QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Couldn't open the file\n\n" )  );
                        return ;
                }

                // Lit le contenu du fichier et le convertit en Base64.
                QByteArray bytes = file.readAll();
                message.append( "--frontier\n" );
                message.append( "Content-Type: application/octet-stream\nContent-Disposition: attachment; filename="+ QFileInfo(file.fileName()).fileName() +";\nContent-Transfer-Encoding: base64\n\n" );
                message.append(bytes.toBase64());
                message.append("\n");
            }
        }
    }
    else
        qDebug() << "No attachments found";


    message.append( "--frontier--\n" );

    message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n" ) );

    // SI UNE ligne contient seulement (.) le SMTP pense qu'il est terminé.
    message.replace( QString::fromLatin1( "\r\n.\r\n" ),QString::fromLatin1( "\r\n..\r\n" ) );


    this->from = from;
    rcpt = to;
    state = Init;

    //Le socket se connecte de manière sécurisée à host sur le port spécifié.
    socket->connectToHostEncrypted(host, port); //"smtp.gmail.com" and 465 for gmail TLS
    if (!socket->waitForConnected(timeout)) {
         qDebug() << socket->errorString();
     }

    t = new QTextStream( socket );



}

smtp::~smtp()
{
    delete t;
    delete socket;
}
void smtp::stateChanged(QAbstractSocket::SocketState socketState)
{

    qDebug() <<"stateChanged " << socketState;
}

void smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << "error " <<socketError;
}

void smtp::disconnected()
{

    qDebug() <<"disconneted";
    qDebug() << "error "  << socket->errorString();
}

void smtp::connected()
{
    qDebug() << "Connected ";
}

void smtp::readyRead()
{

     qDebug() <<"readyRead";
    // SMTP is line-oriented

     // Variable pour stocker temporairement chaque ligne de la réponse.
    QString responseLine;

    //La fonction lit ligne par ligne la réponse envoyée par le serveur.
//Elle vérifie si la réponse est complète (généralement, une ligne se termine par un espace
    do
    {
        responseLine = socket->readLine();
        response += responseLine;
    }
    while ( socket->canReadLine() && responseLine[3] != ' ' );


    responseLine.truncate( 3 );
    qDebug() << "Server response code:" <<  responseLine;
    qDebug() << "Server response: " << response;

    //Le serveur est prêt à recevoir des commandes
    if ( state == Init && responseLine == "220" )
    {
        // banner was okay, let's go on
        *t << "EHLO localhost" <<"\r\n";
        t->flush();

        state = HandShake;
    }
    //La commande a été exécutée avec succès.

    else if (state == HandShake && responseLine == "250")
    {
        socket->startClientEncryption();
        if(!socket->waitForEncrypted(timeout))
        {
            qDebug() << socket->errorString();
            state = Close;
        }


        //Send EHLO once again but now encrypted

        *t << "EHLO localhost" << "\r\n";
        t->flush();
        state = Auth;
    }
    else if (state == Auth && responseLine == "250")
    {
        // Trying AUTH
        qDebug() << "Auth";
        *t << "AUTH LOGIN" << "\r\n";
        t->flush();
        state = User;
    }
    //Le serveur demande des informations supplémentaires (authentification).

    else if (state == User && responseLine == "334")
    {
        //Trying User
        qDebug() << "Username";
        //GMAIL is using XOAUTH2 protocol, which basically means that password and username has to be sent in base64 coding
        //https://developers.google.com/gmail/xoauth2_protocol
        *t << QByteArray(user.toUtf8()).toBase64() << "\r\n";
        t->flush();

        state = Pass;
    }
    else if (state == Pass && responseLine == "334")
    {
        //Trying pass
        qDebug() << "Pass";
        *t << QByteArray(pass.toUtf8()).toBase64() << "\r\n";
        t->flush();

        state = Mail;
    }
    else if ( state == Mail && responseLine == "235" )
    {
        // HELO response was okay (well, it has to be)

        //Apperantly for Google it is mandatory to have MAIL FROM and RCPT email formated the following way -> <email@gmail.com>
        qDebug() << "MAIL FROM:<" << from << ">";
        *t << "MAIL FROM:<" << from << ">\r\n";
        t->flush();
        state = Rcpt;
    }
    else if ( state == Rcpt && responseLine == "250" )
    {
        //Apperantly for Google it is mandatory to have MAIL FROM and RCPT email formated the following way -> <email@gmail.com>
        *t << "RCPT TO:<" << rcpt << ">\r\n"; //r
        t->flush();
        state = Data;
    }
    else if ( state == Data && responseLine == "250" )
    {

        *t << "DATA\r\n";
        t->flush();
        state = Body;
    }
    else if ( state == Body && responseLine == "354" )
    {

        *t << message << "\r\n.\r\n";
        t->flush();
        state = Quit;
    }
    else if ( state == Quit && responseLine == "250" )
    {

        *t << "QUIT\r\n";
        t->flush();
        // here, we just close.
        state = Close;
        emit status( tr( "Message sent" ) );
    }
    else if ( state == Close )
    {
        deleteLater();
        return;
    }
    else
    {
        // something broke.
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Unexpected reply from SMTP server:\n\n" ) + response );
        state = Close;
        emit status( tr( "Failed to send message" ) );
    }
    response = "";
}

