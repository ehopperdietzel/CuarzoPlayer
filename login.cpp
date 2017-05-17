#include "login.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QHttpMultiPart>
#include <QNetworkRequest>

Login::Login()
{
    code->hide();
    QRect screen = QApplication::desktop()->screenGeometry();
    setStyleSheet("Login{background:#FFF}");
    setMinimumSize(500,600);
    logo->setPixmap(QPixmap(":res/img/icon.png"));
    QWidget *logoFrame = new QWidget();
    QBoxLayout *logoLayout = new QBoxLayout(QBoxLayout::LeftToRight,logoFrame);
    logoLayout->setAlignment(Qt::AlignCenter);
    logoLayout->addWidget(logo);
    logoLayout->setMargin(20);
    logo->setFixedSize(150,150);
    logo->setScaledContents(true);
    title->resize(500,100);
    title->setAlignment(Qt::AlignCenter);
    subtitle->setAlignment(Qt::AlignCenter);
    code->hide();
    backBtn->hide();
    readyBtn->hide();
    layout->addWidget(new QWidget(),4);
    layout->setMargin(25);
    layout->setSpacing(25);
    layout->addWidget(title);
    layout->addWidget(subtitle);
    layout->addWidget(logoFrame);
    layout->addWidget(loginBtn,1);
    layout->addWidget(code);
    layout->addWidget(readyBtn);
    layout->addWidget(backBtn);
    layout->addWidget(skipBtn);
    layout->addWidget(new QWidget(),5);
    resize(800,800);
    move(screen.width()/2-400,screen.height()/2-400);
    connect(loginBtn,SIGNAL(released()),this,SLOT(getCode()));
    connect(readyBtn,SIGNAL(released()),this,SLOT(getToken()));
}
void Login::cancel(){


}

void Login::getCode(){

        title->changeText("Authorize Cuarzo Player");
        subtitle->changeText("Paste the code and click Continue");
        loginBtn->hide();
        readyBtn->show();
        code->show();
        backBtn->show();
        skipBtn->hide();


        QString scope = "https://www.googleapis.com/auth/drive";
        QString apiKey = "AIzaSyCQXTMwalQiq-twGJrBrnXmDFNJeGwWs0g";
        QString redirect = "urn:ietf:wg:oauth:2.0:oob";
        QString clientID = "677866894523-ejp2cte1mn0mnb7v7m62kiuteng6mo8v.apps.googleusercontent.com";
        QString clientSecret = "QW5thR07Nwo4dfUy4oozRofU";
        QString url = "https://accounts.google.com/o/oauth2/v2/auth?scope="+scope+"&key="+apiKey+"&redirect_uri="+redirect+"&client_id="+clientID+"&response_type=code";
        QDesktopServices::openUrl(QUrl(url));

       /*Add folder

        QNetworkAccessManager *network = new QNetworkAccessManager(this);
        connect(network,SIGNAL(finished(QNetworkReply*)),this,SLOT(response(QNetworkReply*)));


        json js;

        js["name"] = "PeitoFolder";
        js["mimeType"] = "application/vnd.google-apps.folder";

        QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v3/files"));
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json;charset=UTF-8");
        request.setRawHeader("Authorization",QString("Bearer "+token).toUtf8());
        network->post(request,QString::fromStdString(js.dump()).toUtf8());
     */
}
void Login::getToken(){

    cod = code->text();

    QString scope = "https://www.googleapis.com/auth/drive";
    QString apiKey = "AIzaSyCQXTMwalQiq-twGJrBrnXmDFNJeGwWs0g";
    QString redirect = "urn:ietf:wg:oauth:2.0:oob";
    QString clientID = "677866894523-ejp2cte1mn0mnb7v7m62kiuteng6mo8v.apps.googleusercontent.com";
    QString clientSecret = "QW5thR07Nwo4dfUy4oozRofU";
    QString url = "https://accounts.google.com/o/oauth2/v2/auth?scope="+scope+"&key="+apiKey+"&redirect_uri="+redirect+"&client_id="+clientID+"&response_type=code";
    QString token;
    QString refTok;

    QNetworkAccessManager *network = new QNetworkAccessManager(this);
    connect(network,SIGNAL(finished(QNetworkReply*)),this,SLOT(response(QNetworkReply*)));
    QUrlQuery postData;
    postData.addQueryItem("code", cod);
    postData.addQueryItem("client_id", clientID);
    postData.addQueryItem("client_secret", clientSecret);
    postData.addQueryItem("redirect_uri", "urn:ietf:wg:oauth:2.0:oob");
    postData.addQueryItem("grant_type", "authorization_code");

    QNetworkRequest request(QUrl("https://accounts.google.com/o/oauth2/token"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    network->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

}
void Login::response(QNetworkReply*res){

    json jres = json::parse(res->readAll().toStdString());

    if(!jres["access_token"].is_null() && !jres["refresh_token"].is_null()){
        loggedIn(QString::fromStdString(jres["access_token"]),QString::fromStdString(jres["refresh_token"]));
    }

    qDebug() << QString::fromStdString(jres.dump());
}