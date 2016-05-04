#ifndef ETHLOCALCLIENT_H
#define ETHLOCALCLIENT_H

#include <QObject>
#include <QLocalSocket>
#include "iethclient.h"

class EthLocalClient : public QObject, public IEthClient
{
    Q_OBJECT
public:
    explicit EthLocalClient(QString serverPath = QString(), QObject *parent = 0);
    ~EthLocalClient();

    QVariantMap &clientParameters() override;
    bool connectToServer() override;
    bool disconnectToServer() override;
    bool requestingResponse(const QByteArray& request, QByteArray& response) override;
    int64_t errorNumber() override;
    QString errorString() override;

    static QString defaultServerPath();

signals:

public slots:
    void onSocketError(QLocalSocket::LocalSocketError err);
    void onSocketReadyRead();
    void connectedToServer();
    void disconnectedFromServer();

    void connectionTimeout();

private:
    QLocalSocket m_socket;
    QVariantMap m_parameters;
    int m_code;
    QString m_error;
};

#endif // ETHLOCALCLIENT_H

