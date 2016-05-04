#ifndef ETHOBJECT_H
#define ETHOBJECT_H

#include <QMap>
#include <QVector>
#include <QString>
#include <QVariant>
#include <QByteArray>
#include <QByteArrayList>

//The macro generate functions necessary for working with ETH Objects
#define ETH_OBJECT(Params) \
    void serialize(QVariantMap& map, bool read) override\
    {\
        bool nullCheck = false;\
        int notNull = 0;\
        if(!read)map.clear();\
        Params\
    }\
    bool isNull() {\
        QVariantMap map;\
        bool read = false;\
        bool nullCheck = true;\
        int notNull = 0;\
        Params\
        return notNull == 0; \
    }

//The macro generate code for working with ETH Parameters
#define ETH_PARAM(Param) \
    if(nullCheck)\
    {\
        if(!Param.isNull()) notNull++;\
    }\
    else if(read)\
    {\
        Param.fromRawData(map[#Param]);\
    }\
    else\
    {\
        if(!Param.isNull())\
        {\
            map[#Param] = Param.toRawData();\
        }\
    }

class EValue
{
public:
    EValue();
    virtual bool isNull() { return m_isNull; }
    virtual void fromRawData(const QVariant& rowData) = 0;
    virtual QVariant toRawData() const = 0;

protected:
    bool m_isNull;
};

class EObject : public EValue
{
public:
    EObject();

    void fromRawData(const QVariant& rowData);
    QVariant toRawData() const;
    virtual void serialize(QVariantMap& map, bool read) = 0;
};

class EBool : public EValue
{
public:
    EBool();
    EBool(bool value);
    inline operator bool() { return m_value; }
    void fromRawData(const QVariant& rowData) override;
    QVariant toRawData() const override;

private:
    bool m_value;
};

class EInt : public EValue
{
public:
    EInt();
    EInt(int64_t value);
    inline operator int64_t() { return m_value; }
    void fromRawData(const QVariant& rowData) override;
    QVariant toRawData() const override;

private:
    int64_t m_value;
};

class EByteArray : public EValue
{
public:
    EByteArray();
    EByteArray(const QByteArray& value);
    EByteArray(char* value);
    inline operator QByteArray() { return m_value; }
    void fromRawData(const QVariant& rowData) override;
    QVariant toRawData() const override;

private:
    QByteArray m_value;
};

class EString : public EValue
{
public:
    EString();
    EString(const QString& value);
    inline operator QString() { return m_value; }
    void fromRawData(const QVariant& rowData) override;
    QVariant toRawData() const override;

private:
    QString m_value;
};

class EVariant : public EValue
{
public:
    EVariant();
    EVariant(const QVariant& value);
    inline operator QVariant() { return m_value; }
    void fromRawData(const QVariant& rowData) override;
    QVariant toRawData() const override;

private:
    QVariant m_value;
};

class EByteArrayList : public EValue
{
public:
    EByteArrayList();
    EByteArrayList(const QByteArrayList& value);
    inline operator QByteArrayList() { return m_value; }
    void fromRawData(const QVariant& rowData) override;
    QVariant toRawData() const override;

private:
    QByteArrayList m_value;
};


//Object for syncing data
class ESyncing : public EObject
{
public:
    ESyncing();
    //It is true when syncing, false when not syncing
    bool isSyncing();
    //The block at which the import started (will only be reset, after the sync reached his head)
    EInt startingBlock;
    //The current block, same as eth_blockNumber
    EInt currentBlock;
    //The estimated highest block
    EInt highestBlock;

    ETH_OBJECT
    (
        ETH_PARAM(startingBlock);
        ETH_PARAM(currentBlock);
        ETH_PARAM(highestBlock);
    )
};

//Object for transaction data
class ETransaction : public EObject{
public:
    ETransaction();
    //DATA, 20 Bytes - The address the transaction is send from.
    EByteArray from;
    //DATA, 20 Bytes - The address the transaction is directed to.
    EByteArray to;
    //QUANTITY - Integer of the gas provided for the transaction execution. It will return unused gas.
    EInt gas;
    //QUANTITY - Integer of the gasPrice used for each paid gas
    EInt gasPrice;
    //QUANTITY - Integer of the value send with this transaction
    EInt value;
    //DATA - The compiled code of a contract OR the hash of the invoked method signature and encoded parameters. For details see Ethereum Contract ABI
    EByteArray data;
    //QUANTITY - Integer of a nonce. This allows to overwrite your own pending transactions that use the same nonce.
    EInt nonce;
    //DATA, 32 Bytes - hash of the transaction.
    EByteArray hash;
    //DATA, 32 Bytes - hash of the block where this transaction was in. null when its pending.
    EByteArray blockHash;
    //QUANTITY - block number where this transaction was in. null when its pending.
    EInt blockNumber;
    //QUANTITY - integer of the transactions index position in the block. null when its pending.
    EInt transactionIndex;

    ETH_OBJECT
    (
        ETH_PARAM(from);
        ETH_PARAM(to);
        ETH_PARAM(gas);
        ETH_PARAM(gasPrice);
        ETH_PARAM(value);
        ETH_PARAM(data);
        ETH_PARAM(nonce);
        ETH_PARAM(hash);
        ETH_PARAM(blockHash);
        ETH_PARAM(blockNumber);
        ETH_PARAM(transactionIndex);
    )
};

class EBlock : public EObject{
public:
    EBlock();
    //QUANTITY - the block number. null when its pending block.
    EInt number;
    //DATA, 32 Bytes - hash of the block. null when its pending block.
    EByteArray hash;
    //DATA, 32 Bytes - hash of the parent block.
    EByteArray parentHash;
    //DATA, 8 Bytes - hash of the generated proof-of-work. null when its pending block.
    EByteArray nonce;
    //DATA, 32 Bytes - SHA3 of the uncles data in the block.
    EByteArray sha3Uncles;
    //DATA, 256 Bytes - the bloom filter for the logs of the block. null when its pending block.
    EByteArray logsBloom;
    //DATA, 32 Bytes - the root of the transaction trie of the block.
    EByteArray transactionsRoot;
    //DATA, 32 Bytes - the root of the final state trie of the block.
    EByteArray stateRoot;
    //DATA, 32 Bytes - the root of the receipts trie of the block.
    EByteArray receiptsRoot;
    //DATA, 20 Bytes - the address of the beneficiary to whom the mining rewards were given.
    EByteArray miner;
    //QUANTITY - integer of the difficulty for this block.
    EInt difficulty;
    //QUANTITY - integer of the total difficulty of the chain until this block.
    EInt totalDifficulty;
    //DATA - the "extra data" field of this block.
    EByteArray extraData;
    //QUANTITY - integer the size of this block in bytes.
    EInt size;
    //QUANTITY - the maximum gas allowed in this block.
    EInt gasLimit;
    //QUANTITY - the total used gas by all transactions in this block.
    EInt gasUsed;
    //QUANTITY - the unix timestamp for when the block was collated.
    EInt timestamp;
    //Array - Array of transaction objects, or 32 Bytes transaction hashes depending on the last given parameter.
    EByteArrayList transactions;
    //Array - Array of uncle hashes.
    EByteArrayList uncles;

    ETH_OBJECT
    (
        ETH_PARAM(number);
        ETH_PARAM(hash);
        ETH_PARAM(parentHash);
        ETH_PARAM(nonce);
        ETH_PARAM(sha3Uncles);
        ETH_PARAM(logsBloom);
        ETH_PARAM(transactionsRoot);
        ETH_PARAM(stateRoot);
        ETH_PARAM(receiptsRoot);
        ETH_PARAM(miner);
        ETH_PARAM(difficulty);
        ETH_PARAM(totalDifficulty);
        ETH_PARAM(extraData);
        ETH_PARAM(size);
        ETH_PARAM(gasLimit);
        ETH_PARAM(gasUsed);
        ETH_PARAM(timestamp);
        ETH_PARAM(transactions);
        ETH_PARAM(uncles);
    )
};

class EReceipt : public EObject{
public:
    EReceipt();
    //DATA, 32 Bytes - hash of the transaction.
    EByteArray transactionHash;
    //QUANTITY - integer of the transactions index position in the block.
    EInt transactionIndex;
    //DATA, 32 Bytes - hash of the block where this transaction was in.
    EByteArray blockHash;
    //QUANTITY - block number where this transaction was in.
    EInt blockNumber;
    //QUANTITY - The total amount of gas used when this transaction was executed in the block.
    EInt cumulativeGasUsed;
    //QUANTITY - The amount of gas used by this specific transaction alone.
    EInt gasUsed;
    //DATA, 20 Bytes - The contract address created, if the transaction was a contract creation, otherwise null.
    EByteArray contractAddress;
    //Array - Array of log objects, which this transaction generated.
    EByteArrayList logs;

    ETH_OBJECT
    (
        ETH_PARAM(transactionHash);
        ETH_PARAM(transactionIndex);
        ETH_PARAM(blockHash);
        ETH_PARAM(blockNumber);
        ETH_PARAM(cumulativeGasUsed);
        ETH_PARAM(gasUsed);
        ETH_PARAM(contractAddress);
        ETH_PARAM(logs);
    )
};

class EFilter : public EObject{
public:
    EFilter();
    //QUANTITY|TAG - (optional, default: "latest") Integer block number,
    //or "latest" for the last mined block or "pending", "earliest" for not yet mined transactions.
    EVariant fromBlock;
    //QUANTITY|TAG - (optional, default: "latest") Integer block number,
    //or "latest" for the last mined block or "pending", "earliest" for not yet mined transactions.
    EVariant toBlock;
    //DATA|Array, 20 Bytes - (optional) Contract address or a list of addresses from which logs should originate.
    EVariant address;
    //Array of DATA, - (optional) Array of 32 Bytes DATA topics. Topics are order-dependent.
    //Each topic can also be an array of DATA with "or" options.
    EByteArrayList topics;

    ETH_OBJECT
    (
        ETH_PARAM(fromBlock);
        ETH_PARAM(toBlock);
        ETH_PARAM(address);
        ETH_PARAM(topics);
    )
};

class SWhisper : public EObject{
public:
    SWhisper();
    //DATA, 60 Bytes - The identity of the sender.
    EByteArray from;
    //DATA, 60 Bytes - The identity of the receiver.
    //When present whisper will encrypt the message so that only the receiver can decrypt it.
    EByteArray to;
    //Array of DATA - Array of DATA topics, for the receiver to identify messages.
    EByteArrayList topics;
    //DATA - The payload of the message.
    EByteArray payload;
    //QUANTITY - The integer of the priority in a rang from ... (?).
    EInt priority;
    //QUANTITY - integer of the time to live in seconds.
    EInt ttl;

    ETH_OBJECT
    (
        ETH_PARAM(from);
        ETH_PARAM(to);
        ETH_PARAM(topics);
        ETH_PARAM(payload);
        ETH_PARAM(priority);
        ETH_PARAM(ttl);
    )
};

class SFilter : public EObject{
public:
    SFilter();
    /*DATA, 60 Bytes - (optional) Identity of the receiver.
    When present it will try to decrypt any incoming message if the client holds the private key to this identity.*/
    EByteArray to;
    /*Array of DATA - Array of DATA topics which the incoming message's topics should match. You can use the following combinations:
        [A, B] = A && B
        [A, [B, C]] = A && (B || C)
        [null, A, B] = ANYTHING && A && B null works as a wildcard*/
    EByteArrayList topics;

    ETH_OBJECT
    (
        ETH_PARAM(to);
        ETH_PARAM(topics);
    )
};

class SFilterMessage : public EObject{
public:
    SFilterMessage();
    //DATA, 32 Bytes - The hash of the message.
    EByteArray hash;
    //DATA, 60 Bytes - The sender of the message, if a sender was specified.
    EByteArray from;
    //DATA, 60 Bytes - The receiver of the message, if a receiver was specified.
    EByteArray to;
    //QUANTITY - Integer of the time in seconds when this message should expire.
    EInt expiry;
    //QUANTITY - Integer of the time the message should float in the system in seconds.
    EInt ttl;
    //QUANTITY - Integer of the unix timestamp when the message was sent.
    EInt sent;
    //Array of DATA - Array of DATA topics the message contained.
    EByteArrayList topics;
    //DATA - The payload of the message.
    EByteArray payload;
    //QUANTITY - Integer of the work this message required before it was send.
    EInt workProved;

    ETH_OBJECT
    (
        ETH_PARAM(hash);
        ETH_PARAM(from);
        ETH_PARAM(to);
        ETH_PARAM(expiry);
        ETH_PARAM(ttl);
        ETH_PARAM(sent);
        ETH_PARAM(topics);
        ETH_PARAM(payload);
        ETH_PARAM(workProved);
    )
};

#endif // ETHOBJECT_H
