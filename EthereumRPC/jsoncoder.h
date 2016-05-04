#ifndef JSONCODER_H
#define JSONCODER_H
#include "QByteArray"
#include "ethobject.h"

QByteArray encodeJsonRPC(const QString& method, const QVariant& params, int64_t& id);

bool decodeJsonRPC(const QByteArray& response, int64_t id, QVariant& result);

#endif // JSONCODER_H
