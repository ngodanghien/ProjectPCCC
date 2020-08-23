#include "network.h"

#include <QJsonDocument>
#include <QJsonObject>


Network::Network()
{
    manager = new QNetworkAccessManager(this);
    if (settings->getToken() != ""){
        request.setRawHeader("Authorization", settings->getToken().toUtf8());
    }
}

void Network::login(QString username, QString password)
{
    QVariantMap mapData;
    mapData["email"] = username;
    mapData["password"] = password;
    QByteArray jsonData = QJsonDocument(
                QJsonObject::fromVariantMap(
                        mapData
                )
        ).toJson();

    request.setUrl(QUrl::fromUserInput(settings->getServerUrl() + loginPath));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    reply = manager->post(request, jsonData);
}

void Network::uploadDeviceParameter(QByteArray jsonData)
{
    request.setUrl(QUrl::fromUserInput(settings->getServerUrl() + dataPath));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    reply = manager->post(request, jsonData);
}

void Network::syncData()
{
    request.setUrl(QUrl::fromUserInput(settings->getServerUrl() + dataPath));
    reply = manager->get(request);
}