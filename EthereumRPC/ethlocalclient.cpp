#include "ethlocalclient.h"

namespace EthLocalClient_NS
{
    const int MSECS = 2000;
}
using namespace EthLocalClient_NS;

EthLocalClient::EthLocalClient(QString serverPath, QObject *parent) : QObject(parent)
{
    m_parameters["serverPath"] = serverPath.isEmpty() ? defaultServerPath() : serverPath;

    connect(&m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)),
            this, SLOT(onSocketError(QLocalSocket::LocalSocketError)));
    connect(&m_socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
    connect(&m_socket, SIGNAL(connected()), this, SLOT(connectedToServer()));
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(disconnectedFromServer()));
}

EthLocalClient::~EthLocalClient()
{
    disconnectToServer();
}

QVariantMap &EthLocalClient::clientParameters()
{
    return m_parameters;
}

bool EthLocalClient::connectToServer()
{
    disconnectToServer();

    m_socket.connectToServer(m_parameters["serverPath"].toString());
    return m_socket.waitForConnected(MSECS);
}

bool EthLocalClient::disconnectToServer()
{
    m_socket.disconnectFromServer();
    return m_socket.waitForDisconnected(MSECS);
}

bool EthLocalClient::requestingResponse(const QByteArray &request, QByteArray &response)
{
    bool ret = false;
    if(m_socket.isWritable())
    {

    }
    return ret;
}

int64_t EthLocalClient::errorNumber()
{
    return m_socket.error();
}

QString EthLocalClient::errorString()
{
    return m_socket.errorString();
}

QString EthLocalClient::defaultServerPath()
{
    return "";
}

void EthLocalClient::onSocketError(QLocalSocket::LocalSocketError err)
{
    m_error = m_socket.errorString();
    m_code = err;
}

void EthLocalClient::onSocketReadyRead()
{

}

void EthLocalClient::connectedToServer()
{

}

void EthLocalClient::disconnectedFromServer()
{

}

void EthLocalClient::connectionTimeout()
{

}
