#ifndef ETHEREUMUTILS_H
#define ETHEREUMUTILS_H
#include <QByteArray>
#include <QString>

inline QString removeHexMark(QString hexString)
{
    if(hexString.startsWith("0x"))
        hexString.remove(0, 2);
    return hexString;
}

inline bool isHexValid(const QString& hexString, int size = -1)
{
    if(!hexString.startsWith("0x"))
        return false;
    if(size > -1)
    {
        if(hexString.size() != 2 * size + 2)
            return false;
    }
    for(int i = 2; i < hexString.size(); i++)
    {
        char c = hexString[i].toLatin1();
        if(!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
            return false;
    }
    return true;
}

inline QByteArray formatHex(const QByteArray& hexString, int size = -1)
{
    QByteArray data = hexString;
    if(size > -1)
    {
        int totalSize = size * 2;
        if(data.size() != totalSize)
        {
            if(data.size() < totalSize)
            {
                for(int i = data.size(); i < totalSize; i++)
                {
                    data.prepend('0');
                }
            }
            else
            {
                int diff = data.size() - totalSize;
                data.remove(data.size() -1 -diff, diff);
            }
        }
    }
    return "0x" + data;
}

inline QByteArray int2hex(const int64_t& rawData)
{
    QByteArray binaryData = QByteArray::number(rawData, 16);
    return formatHex(binaryData);
}

inline bool hex2int(const QString& rawData, int64_t& value)
{
    bool ok = true;
    value = rawData.toLongLong(&ok, 16);
    return ok;
}

inline int64_t hex2int(const QString& rawData)
{
    return rawData.toLongLong(0, 16);
}

inline QByteArray binary2hex(const QByteArray& rawData)
{
    QByteArray binaryData = rawData.toHex();
    return formatHex(binaryData);
}

inline QByteArray hex2binary(const QString& rawData)
{
    QString hexData = removeHexMark(rawData);
    QByteArray binaryData = QByteArray::fromHex(hexData.toUtf8());
    return binaryData;
}

#endif // ETHEREUMUTILS_H
