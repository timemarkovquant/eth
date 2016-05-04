#include "jsoncoder.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QVariant"
#include "QVariantMap"

bool decodeJsonRPC(const QByteArray &response, int64_t id, QVariant &result)
{
    QJsonDocument document = QJsonDocument::fromJson(response);
    if(!document.isObject()) return false;
    QJsonObject jsonObject = document.object();
    QVariantMap variantMap = jsonObject.toVariantMap();
    if(!variantMap.contains("id") || !variantMap.contains("jsonrpc") || !variantMap.contains("result"))
        return false;

    int64_t j_id = variantMap["id"].toLongLong();
    QString j_jsonrpc = variantMap["jsonrpc"].toString();
    QVariant j_result = variantMap["result"];

    if(j_id != id) return false;
    if(j_jsonrpc != "2.0") return false;

    result = j_result;
    return true;
}

QByteArray encodeJsonRPC(const QString &method, const QVariant &params, int64_t &id)
{
    static int64_t methodId = 0;

    QVariantMap variantMap;
    variantMap["jsonrpc"] = "2.0";
    variantMap["method"] = method;
    variantMap["params"] = params;
    id = ++methodId;
    variantMap["id"] = id;
    QJsonObject jsonObject = QJsonObject::fromVariantMap(variantMap);
    QJsonDocument document(jsonObject);

    return document.toJson();
}
