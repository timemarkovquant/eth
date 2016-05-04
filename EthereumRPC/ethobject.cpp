#include "ethobject.h"
#include "ethrpc_utils.h"

bool ESyncing::isSyncing()
{
    return !isNull();
}

EBool::EBool() :
    m_value(false)
{}

EBool::EBool(bool value) :
    m_value(value)
{
    m_isNull = false;
}

void EBool::fromRawData(const QVariant &rowData)
{
    m_isNull = rowData.isNull();
    if(!m_isNull)
    {
        m_value = rowData.toBool();
    }
}

QVariant EBool::toRawData() const
{
    QVariant rowData;
    if(!m_isNull)
    {
        rowData = m_value;
    }
    return rowData;
}

EInt::EInt():
    m_value(0)
{}

EInt::EInt(int64_t value):
    m_value(value)
{
    m_isNull = false;
}

void EInt::fromRawData(const QVariant &rowData)
{
    m_isNull = rowData.isNull();
    if(!m_isNull)
    {
        QString rowString = rowData.toString();
        m_isNull = !hex2int(rowString, m_value);
    }
}

QVariant EInt::toRawData() const
{
    QVariant rowData;
    if(!m_isNull)
    {
        rowData = int2hex(m_value);
    }
    return rowData;
}

EByteArray::EByteArray()
{}

EByteArray::EByteArray(const QByteArray &value):
    m_value(value)
{
    m_isNull = false;
}

EByteArray::EByteArray(char *value):
    m_value(value)
{
    m_isNull = false;
}

void EByteArray::fromRawData(const QVariant &rowData)
{
    m_isNull = rowData.isNull();
    if(!m_isNull)
    {
        QString rowString = rowData.toString();
        m_value = hex2binary(rowString);
    }
}

QVariant EByteArray::toRawData() const
{
    QVariant rowData;
    if(!m_isNull)
    {
        rowData = binary2hex(m_value);
    }
    return rowData;
}

EString::EString()
{}

EString::EString(const QString &value):
    m_value(value)
{
    m_isNull = false;
}

void EString::fromRawData(const QVariant &rowData)
{
    m_isNull = rowData.isNull();
    if(!m_isNull)
    {
        m_value = rowData.toString();
    }
}

QVariant EString::toRawData() const
{
    QVariant rowData;
    if(!m_isNull)
    {
        rowData = m_value;
    }
    return rowData;
}

EVariant::EVariant()
{}

EVariant::EVariant(const QVariant &value):
    m_value(value)
{
    m_isNull = false;
}

void EVariant::fromRawData(const QVariant &rowData)
{
    m_isNull = rowData.isNull();
    if(!m_isNull)
    {
        if(rowData.type() == QVariant::String)
        {
            m_value = rowData.toString();
        }
        else
        {
            QString rowString = rowData.toString();
            int64_t value = 0;
            m_isNull = !hex2int(rowString, value);
            m_value = value;
        }
    }
}

QVariant EVariant::toRawData() const
{
    QVariant rowData;
    if(!m_isNull)
    {
        if(m_value.type() == QVariant::String)
        {
            rowData = m_value;
        }
        else
        {
            rowData = int2hex(m_value.toLongLong());
        }
    }
    return rowData;
}

EByteArrayList::EByteArrayList()
{}

EByteArrayList::EByteArrayList(const QByteArrayList &value):
    m_value(value)
{
    m_isNull = false;
}

void EByteArrayList::fromRawData(const QVariant &rowData)
{
    m_isNull = rowData.isNull();
    if(!m_isNull)
    {
        QList<QVariant> rowValues = rowData.toList();
        for(int i = 0 ; i < rowValues.count(); i++)
        {
            QVariant rowValue = rowValues[i];
            QString rowString = rowValue.toString();
            m_value.append(hex2binary(rowString));
        }
    }
}

QVariant EByteArrayList::toRawData() const
{
    QList<QVariant> rowData;
    if(!m_isNull)
    {
        for(int i = 0 ; i < m_value.count(); i++)
        {
            rowData.append(binary2hex(m_value[i]));
        }
    }
    return rowData;
}

EObject::EObject()
{}

void EObject::fromRawData(const QVariant &rowData)
{
    QVariantMap in = rowData.toMap();
    serialize(in, true);
}

QVariant EObject::toRawData() const
{
    QVariantMap out;
    const_cast<EObject*>(this)->serialize(out, false);
    return out;
}

ETransaction::ETransaction()
{}

EValue::EValue() :
    m_isNull(true)
{}

ESyncing::ESyncing()
{}

EBlock::EBlock()
{}

EReceipt::EReceipt()
{}

EFilter::EFilter()
{}

SWhisper::SWhisper()
{}

SFilter::SFilter()
{}

SFilterMessage::SFilterMessage()
{}
