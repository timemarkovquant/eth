#ifndef IETHCLIENT_H
#define IETHCLIENT_H
#include <QByteArray>
#include <QVariantMap>
class IEthClient
{
public:
    virtual QVariantMap& clientParameters() = 0;
    virtual bool connectToServer() = 0;
    virtual bool disconnectToServer() = 0;
    virtual bool requestingResponse(const QByteArray& request, QByteArray& response) = 0;
    virtual int64_t errorNumber() = 0;
    virtual QString errorString() = 0;
    virtual ~IEthClient(){}
};

#endif // IETHEREUMCLIENT_H
