#include "ethrpc.h"
#include "iethclient.h"
#include "jsoncoder.h"

class RPC_Private{
public:
    RPC_Private():
        m_client(0)
    {}

    ~RPC_Private()
    {
        if(m_client)
            delete m_client;
    }

    bool call_rpc_method(const QString& method, const QVariantList& params, EValue& out)
    {
        bool ret = true;
        int64_t id = 0;
        QByteArray request;
        QByteArray response;
        QVariant result;
        request = encodeJsonRPC(method, params, id);
        ret = m_client->requestingResponse(request, response);
        if(!ret) return ret;
        ret &= decodeJsonRPC(response, id, result);
        out.fromRawData(result);
        return ret;
    }

    IEthClient* m_client;
};

EthRPC::EthRPC():
    m_p(0)
{
    m_p = new RPC_Private();
}

EthRPC::~EthRPC()
{
    delete m_p;
    m_p = 0;
}

bool EthRPC::connect(const EString &serverUri)
{
    Q_UNUSED(serverUri);
    return false;
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"web3_clientVersion","params":[],"id":67}'

// Result
{
  "id":67,
  "jsonrpc":"2.0",
  "result": "Mist/v0.9.3/darwin/go1.4.1"
}
*/
bool EthRPC::web3_clientVersion(EString &clientVersion)
{
    return m_p->call_rpc_method("web3_clientVersion", QVariantList(), clientVersion);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"web3_sha3","params":["0x68656c6c6f20776f726c64"],"id":64}'

// Result
{
  "id":64,
  "jsonrpc": "2.0",
  "result": "0x47173285a8d7341e5e972fc677286384f802f8ef42a5ec5f03bbfa254cb01fad"
}
*/
bool EthRPC::web3_sha3(const EByteArray &rowData, EByteArray &hash)
{
    QVariantList params;
    params.append(rowData.toRawData());
    return m_p->call_rpc_method("web3_sha3", params, hash);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"net_version","params":[],"id":67}'

// Result
{
  "id":67,
  "jsonrpc": "2.0",
  "result": "59"
}
*/
bool EthRPC::net_version(EString &clientVersion)
{
    return m_p->call_rpc_method("net_version", QVariantList(), clientVersion);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"net_listening","params":[],"id":67}'

// Result
{
  "id":67,
  "jsonrpc":"2.0",
  "result":true
}
*/
bool EthRPC::net_listening(EBool &isListening)
{
    return m_p->call_rpc_method("net_listening", QVariantList(), isListening);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"net_peerCount","params":[],"id":74}'

// Result
{
  "id":74,
  "jsonrpc": "2.0",
  "result": "0x2" // 2
}
*/
bool EthRPC::net_peerCount(EInt &numberConnected)
{
    return m_p->call_rpc_method("net_peerCount", QVariantList(), numberConnected);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_protocolVersion","params":[],"id":67}'

// Result
{
  "id":67,
  "jsonrpc": "2.0",
  "result": "54"
}
*/
bool EthRPC::eth_protocolVersion(EString &clientVersion)
{
    return m_p->call_rpc_method("eth_protocolVersion", QVariantList(), clientVersion);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_syncing","params":[],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": {
    startingBlock: '0x384',
    currentBlock: '0x386',
    highestBlock: '0x454'
  }
}
// Or when not syncing
{
  "id":1,
  "jsonrpc": "2.0",
  "result": false
}
*/
bool EthRPC::eth_syncing(ESyncing &syncing)
{
    return m_p->call_rpc_method("eth_syncing", QVariantList(), syncing);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_coinbase","params":[],"id":64}'

// Result
{
  "id":64,
  "jsonrpc": "2.0",
  "result": "0x407d73d8a49eeb85d32cf465507dd71d507100c1"
}
*/
bool EthRPC::eth_coinbase(EByteArray &coinbaseAddress)
{
    return m_p->call_rpc_method("eth_coinbase", QVariantList(), coinbaseAddress);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_mining","params":[],"id":71}'

// Result
{
  "id":71,
  "jsonrpc": "2.0",
  "result": true
}
*/
bool EthRPC::eth_mining(EBool &isMining)
{
    return m_p->call_rpc_method("eth_mining", QVariantList(), isMining);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_hashrate","params":[],"id":71}'

// Result
{
  "id":71,
  "jsonrpc": "2.0",
  "result": "0x38a"
}
*/
bool EthRPC::eth_hashrate(EInt &hashesPerSec)
{
    return m_p->call_rpc_method("eth_hashrate", QVariantList(), hashesPerSec);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_gasPrice","params":[],"id":73}'

// Result
{
  "id":73,
  "jsonrpc": "2.0",
  "result": "0x09184e72a000" // 10000000000000
}
*/
bool EthRPC::eth_gasPrice(EInt &currentGasPrice)
{
    return m_p->call_rpc_method("eth_gasPrice", QVariantList(), currentGasPrice);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_accounts","params":[],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": ["0x407d73d8a49eeb85d32cf465507dd71d507100c1"]
}
*/
bool EthRPC::eth_accounts(EByteArrayList &ethAddresses)
{
    return m_p->call_rpc_method("eth_accounts", QVariantList(), ethAddresses);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_blockNumber","params":[],"id":83}'

// Result
{
  "id":83,
  "jsonrpc": "2.0",
  "result": "0x4b7" // 1207
}
*/
bool EthRPC::eth_blockNumber(EInt &currentBlockNumber)
{
    return m_p->call_rpc_method("eth_blockNumber", QVariantList(), currentBlockNumber);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getBalance","params":["0x407d73d8a49eeb85d32cf465507dd71d507100c1", "0x4b7"],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x0234c8a3397aab58" // 158972490234375000
}
*/
bool EthRPC::eth_getBalance(const EByteArray &ethAddress, const EVariant& blockId, EInt &currentBalance)
{
    QVariantList params;
    params.append(ethAddress.toRawData());
    params.append(blockId.toRawData());
    return m_p->call_rpc_method("eth_getBalance", params, currentBalance);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getStorageAt","params":["0x407d73d8a49eeb85d32cf465507dd71d507100c1", "0x0", "0x2"],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x03"
}
*/
bool EthRPC::eth_getStorageAt(const EByteArray &storageAddress, const EInt &position, const EVariant& blockId, EByteArray &value)
{
    QVariantList params;
    params.append(storageAddress.toRawData());
    params.append(position.toRawData());
    params.append(blockId.toRawData());
    return m_p->call_rpc_method("eth_getStorageAt", params, value);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getTransactionCount","params":["0x407d73d8a49eeb85d32cf465507dd71d507100c1","0x2"],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x1" // 1
}
*/
bool EthRPC::eth_getTransactionCount(const EByteArray &ethAddress, const EVariant& blockId, EInt &numberTransactions)
{
    QVariantList params;
    params.append(ethAddress.toRawData());
    params.append(blockId.toRawData());
    return m_p->call_rpc_method("eth_getTransactionCount", params, numberTransactions);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getTransactionCount","params":["0x407d73d8a49eeb85d32cf465507dd71d507100c1","latest"],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x1" // 1
}
*/
bool EthRPC::eth_getBlockTransactionCountByHash(const EByteArray &hashBlock, EInt &numberTransactions)
{
    QVariantList params;
    params.append(hashBlock.toRawData());
    return m_p->call_rpc_method("eth_getBlockTransactionCountByHash", params, numberTransactions);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getBlockTransactionCountByNumber","params":["0xe8"],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0xa" // 10
}
*/
bool EthRPC::eth_getBlockTransactionCountByNumber(const EVariant& blockId, EInt &numberTransactions)
{
    QVariantList params;
    params.append(blockId.toRawData());
    return m_p->call_rpc_method("eth_getBlockTransactionCountByNumber", params, numberTransactions);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getUncleCountByBlockHash","params":["0xb903239f8543d04b5dc1ba6579132b143087c68db1b2168786408fcbce568238"],"id"Block:1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x1" // 1
}
*/
bool EthRPC::eth_getUncleCountByBlockHash(const EByteArray &hashBlock, EInt &numberUncles)
{
    QVariantList params;
    params.append(hashBlock.toRawData());
    return m_p->call_rpc_method("eth_getUncleCountByBlockHash", params, numberUncles);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getUncleCountByBlockNumber","params":["0xe8"],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x1" // 1
}
*/
bool EthRPC::eth_getUncleCountByBlockNumber(const EVariant& blockId, EInt &numberUncles)
{
    QVariantList params;
    params.append(blockId.toRawData());
    return m_p->call_rpc_method("eth_getUncleCountByBlockNumber", params, numberUncles);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getCode","params":["0xa94f5374fce5edbc8e2a8697c15331677e6ebf0b", "0x2"],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x600160008035811a818181146012578301005b601b6001356025565b8060005260206000f25b600060078202905091905056"
}
*/
bool EthRPC::eth_getCode(const EByteArray &ethAddress, const EVariant& blockId, EByteArray &addressCode)
{
    QVariantList params;
    params.append(ethAddress.toRawData());
    params.append(blockId.toRawData());
    return m_p->call_rpc_method("eth_getCode", params, addressCode);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_sign","params":["0xd1ade25ccd3d550a7eb532ac759cac7be09c2719", "Schoolbus"],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x2ac19db245478a06032e69cdbd2b54e648b78431d0a47bd1fbab18f79f820ba407466e37adbe9e84541cab97ab7d290f4a64a5825c876d22109f3bf813254e8601"
}
*/
bool EthRPC::eth_sign(const EByteArray &ethAddress, const EByteArray &plainData, EByteArray &cipheredData)
{
    QVariantList params;
    params.append(ethAddress.toRawData());
    params.append(plainData.toRawData());
    return m_p->call_rpc_method("eth_sign", params, cipheredData);
}

/*
params: [{
  "from": "0xb60e8dd61c5d32be8058bb8eb970870f07233155",
  "to": "0xd46e8dd67c5d32be8058bb8eb970870f072445675",
  "gas": "0x76c0", // 30400,
  "gasPrice": "0x9184e72a000", // 10000000000000
  "value": "0x9184e72a", // 2441406250
  "data": "0xd46e8dd67c5d32be8d46e8dd67c5d32be8058bb8eb970870f072445675058bb8eb970870f072445675"
}]

// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_sendTransaction","params":[{see above}],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0xe670ec64341771606e55d6b4ca35a1a6b75ee3d5145a99d05921026d1527331"
}
*/
bool EthRPC::eth_sendTransaction(const ETransaction &transaction, EByteArray &transactionHash)
{
    QVariantList params;
    params.append(transaction.toRawData());
    return m_p->call_rpc_method("eth_sendTransaction", params, transactionHash);
}

/*
params: ["0xd46e8dd67c5d32be8d46e8dd67c5d32be8058bb8eb970870f072445675058bb8eb970870f072445675"]

// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_sendRawTransaction","params":[{see above}],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0xe670ec64341771606e55d6b4ca35a1a6b75ee3d5145a99d05921026d1527331"
}
*/
bool EthRPC::eth_sendRawTransaction(const EByteArray &signedData, EByteArray &transactionHash)
{
    QVariantList params;
    params.append(signedData.toRawData());
    return m_p->call_rpc_method("eth_sendRawTransaction", params, transactionHash);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_call","params":[{see above}],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x0"
}
*/
bool EthRPC::eth_call(const ETransaction &transaction, const EVariant& blockId, EByteArray &returnValue)
{
    QVariantList params;
    params.append(transaction.toRawData());
    params.append(blockId.toRawData());
    return m_p->call_rpc_method("eth_call", params, returnValue);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_estimateGas","params":[{see above}],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x5208" // 21000
}
*/
bool EthRPC::eth_estimateGas(const ETransaction &transaction, const EInt &blockNumber, EInt &gasUsed)
{
    QVariantList params;
    params.append(transaction.toRawData());
    params.append(blockNumber.toRawData());
    return m_p->call_rpc_method("eth_estimateGas", params, gasUsed);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_estimateGas","params":[{see above}],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x5208" // 21000
}
*/
bool EthRPC::eth_estimateGas(const ETransaction &transaction, const EString &blockTag, EInt &gasUsed)
{
    QVariantList params;
    params.append(transaction.toRawData());
    params.append(blockTag.toRawData());
    return m_p->call_rpc_method("eth_estimateGas", params, gasUsed);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getBlockByHash","params":["0xe670ec64341771606e55d6b4ca35a1a6b75ee3d5145a99d05921026d1527331", true],"id":1}'

// Result
{
"id":1,
"jsonrpc":"2.0",
"result": {
    "number": "0x1b4", // 436
    "hash": "0xe670ec64341771606e55d6b4ca35a1a6b75ee3d5145a99d05921026d1527331",
    "parentHash": "0x9646252be9520f6e71339a8df9c55e4d7619deeb018d2a3f2d21fc165dde5eb5",
    "nonce": "0xe04d296d2460cfb8472af2c5fd05b5a214109c25688d3704aed5484f9a7792f2",
    "sha3Uncles": "0x1dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347",
    "logsBloom": "0xe670ec64341771606e55d6b4ca35a1a6b75ee3d5145a99d05921026d1527331",
    "transactionsRoot": "0x56e81f171bcc55a6ff8345e692c0f86e5b48e01b996cadc001622fb5e363b421",
    "stateRoot": "0xd5855eb08b3387c0af375e9cdb6acfc05eb8f519e419b874b6ff2ffda7ed1dff",
    "miner": "0x4e65fda2159562a496f9f3522f89122a3088497a",
    "difficulty": "0x027f07", // 163591
    "totalDifficulty":  "0x027f07", // 163591
    "extraData": "0x0000000000000000000000000000000000000000000000000000000000000000",
    "size":  "0x027f07", // 163591
    "gasLimit": "0x9f759", // 653145
    "minGasPrice": "0x9f759", // 653145
    "gasUsed": "0x9f759", // 653145
    "timestamp": "0x54e34e8e" // 1424182926
    "transactions": [{...},{ ... }]
    "uncles": ["0x1606e5...", "0xd5145a9..."]
  }
}
*/
bool EthRPC::eth_getBlockByHash(const EByteArray &hashBlock, const EBool &full, EBlock &block)
{
    QVariantList params;
    params.append(hashBlock.toRawData());
    params.append(full.toRawData());
    return m_p->call_rpc_method("eth_getBlockByHash", params, block);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getBlockByNumber","params":["0x1b4", true],"id":1}'
*/
bool EthRPC::eth_getBlockByNumber(const EVariant &blockId, const EBool &full, EBlock &block)
{
    QVariantList params;
    params.append(blockId.toRawData());
    params.append(full.toRawData());
    return m_p->call_rpc_method("eth_getBlockByNumber", params, block);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getTransactionByHash","params":["0xb903239f8543d04b5dc1ba6579132b143087c68db1b2168786408fcbce568238"],"id":1}'

// Result
{
"id":1,
"jsonrpc":"2.0",
"result": {
    "hash":"0xc6ef2fc5426d6ad6fd9e2a26abeab0aa2411b7ab17f30a99d3cb96aed1d1055b",
    "nonce":"0x",
    "blockHash": "0xbeab0aa2411b7ab17f30a99d3cb9c6ef2fc5426d6ad6fd9e2a26a6aed1d1055b",
    "blockNumber": "0x15df", // 5599
    "transactionIndex":  "0x1", // 1
    "from":"0x407d73d8a49eeb85d32cf465507dd71d507100c1",
    "to":"0x85h43d8a49eeb85d32cf465507dd71d507100c1",
    "value":"0x7f110" // 520464
    "gas": "0x7f110" // 520464
    "gasPrice":"0x09184e72a000",
    "input":"0x603880600c6000396000f300603880600c6000396000f3603880600c6000396000f360",
  }
}
*/
bool EthRPC::eth_getTransactionByHash(const EByteArray &transactionHash, ETransaction &transaction)
{
    QVariantList params;
    params.append(transactionHash.toRawData());
    return m_p->call_rpc_method("eth_getTransactionByHash", params, transaction);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getTransactionByBlockHashAndIndex","params":[0xc6ef2fc5426d6ad6fd9e2a26abeab0aa2411b7ab17f30a99d3cb96aed1d1055b, "0x0"],"id":1}'
*/
bool EthRPC::eth_getTransactionByBlockHashAndIndex(const EByteArray &hashBlock, const EInt &transactionIndex, ETransaction &transaction)
{
    QVariantList params;
    params.append(hashBlock.toRawData());
    params.append(transactionIndex.toRawData());
    return m_p->call_rpc_method("eth_getTransactionByBlockHashAndIndex", params, transaction);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getTransactionByBlockNumberAndIndex","params":["0x29c", "0x0"],"id":1}'
*/
bool EthRPC::eth_getTransactionByBlockNumberAndIndex(const EVariant &blockId, const EInt &transactionIndex, ETransaction &transaction)
{
    QVariantList params;
    params.append(blockId.toRawData());
    params.append(transactionIndex.toRawData());
    return m_p->call_rpc_method("eth_getTransactionByBlockNumberAndIndex", params, transaction);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getTransactionReceipt","params":["0xb903239f8543d04b5dc1ba6579132b143087c68db1b2168786408fcbce568238"],"id":1}'

// Result
{
"id":1,
"jsonrpc":"2.0",
"result": {
     transactionHash: '0xb903239f8543d04b5dc1ba6579132b143087c68db1b2168786408fcbce568238',
     transactionIndex:  '0x1', // 1
     blockNumber: '0xb', // 11
     blockHash: '0xc6ef2fc5426d6ad6fd9e2a26abeab0aa2411b7ab17f30a99d3cb96aed1d1055b',
     cumulativeGasUsed: '0x33bc', // 13244
     gasUsed: '0x4dc', // 1244
     contractAddress: '0xb60e8dd61c5d32be8058bb8eb970870f07233155' // or null, if none was created
     logs: [{
         // logs as returned by getFilterLogs, etc.
     }, ...]
  }
}
*/
bool EthRPC::eth_getTransactionReceipt(const EByteArray &transactionHash, EReceipt &receipt)
{
    QVariantList params;
    params.append(transactionHash.toRawData());
    return m_p->call_rpc_method("eth_getTransactionReceipt", params, receipt);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getUncleByBlockHashAndIndex","params":["0xc6ef2fc5426d6ad6fd9e2a26abeab0aa2411b7ab17f30a99d3cb96aed1d1055b", "0x0"],"id":1}'
*/
bool EthRPC::eth_getUncleByBlockHashAndIndex(const EByteArray &hashBlock, const EInt &possition, EBlock &block)
{
    QVariantList params;
    params.append(hashBlock.toRawData());
    params.append(possition.toRawData());
    return m_p->call_rpc_method("eth_getUncleByBlockHashAndIndex", params, block);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getUncleByBlockNumberAndIndex","params":["0x29c", "0x0"],"id":1}'
*/
bool EthRPC::eth_getUncleByBlockNumberAndIndex(const EVariant &blockId, const EInt &possition, EBlock &block)
{
    QVariantList params;
    params.append(blockId.toRawData());
    params.append(possition.toRawData());
    return m_p->call_rpc_method("eth_getUncleByBlockNumberAndIndex", params, block);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getCompilers","params":[],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": ["solidity", "lll", "serpent"]
}
*/
bool EthRPC::eth_getCompilers(QStringList &compilers)
{
    Q_UNUSED(compilers);
    return false;
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_compileSolidity","params":["contract test { function multiply(uint a) returns(uint d) {   return a * 7;   } }"],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": {
      "code": "0x605880600c6000396000f3006000357c010000000000000000000000000000000000000000000000000000000090048063c6888fa114602e57005b603d6004803590602001506047565b8060005260206000f35b60006007820290506053565b91905056",
      "info": {
        "source": "contract test {\n   function multiply(uint a) constant returns(uint d) {\n       return a * 7;\n   }\n}\n",
        "language": "Solidity",
        "languageVersion": "0",
        "compilerVersion": "0.9.19",
        "abiDefinition": [
          {
            "constant": true,
            "inputs": [
              {
                "name": "a",
                "type": "uint256"
              }
            ],
            "name": "multiply",
            "outputs": [
              {
                "name": "d",
                "type": "uint256"
              }
            ],
            "type": "function"
          }
        ],
        "userDoc": {
          "methods": {}
        },
        "developerDoc": {
          "methods": {}
        }
      }

}
*/
bool EthRPC::eth_compileSolidity(const EString &sourceCode, EString &compiledCode)
{
    QVariantList params;
    params.append(sourceCode.toRawData());
    return m_p->call_rpc_method("eth_compileSolidity", params, compiledCode);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_compileLLL","params":["(returnlll (suicide (caller)))"],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x603880600c6000396000f3006001600060e060020a600035048063c6888fa114601857005b6021600435602b565b8060005260206000f35b600081600702905091905056" // the compiled source code
}
*/
bool EthRPC::eth_compileLLL(const EString &sourceCode, EString &compiledCode)
{
    QVariantList params;
    params.append(sourceCode.toRawData());
    return m_p->call_rpc_method("eth_compileLLL", params, compiledCode);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_compileSerpent","params":["/ some serpent /"],"id":1}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x603880600c6000396000f3006001600060e060020a600035048063c6888fa114601857005b6021600435602b565b8060005260206000f35b600081600702905091905056" // the compiled source code
}
*/
bool EthRPC::eth_compileSerpent(const EString &sourceCode, EString &compiledCode)
{
    QVariantList params;
    params.append(sourceCode.toRawData());
    return m_p->call_rpc_method("eth_compileSerpent", params, compiledCode);
}

/*
params: [{
  "fromBlock": "0x1",
  "toBlock": "0x2",
  "address": "0x8888f1f195afa192cfee860698584c030f4c9db1",
  "topics": ["0x000000000000000000000000a94f5374fce5edbc8e2a8697c15331677e6ebf0b", null, [0x000000000000000000000000a94f5374fce5edbc8e2a8697c15331677e6ebf0b, 0x000000000000000000000000aff3454fce5edbc8cca8697c15331677e6ebccc]]
}]

// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_newFilter","params":[{"topics":["0x12341234"]}],"id":73}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0x1" // 1
}
*/
bool EthRPC::eth_newFilter(const EFilter &filter, EInt &filterId)
{
    QVariantList params;
    params.append(filter.toRawData());
    return m_p->call_rpc_method("eth_newFilter", params, filterId);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_newBlockFilter","params":[],"id":73}'

// Result
{
  "id":1,
  "jsonrpc":  "2.0",
  "result": "0x1" // 1
}
*/
bool EthRPC::eth_newBlockFilter(EInt &filterId)
{
    return m_p->call_rpc_method("eth_newBlockFilter", QVariantList(), filterId);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_newPendingTransactionFilter","params":[],"id":73}'

// Result
{
  "id":1,
  "jsonrpc":  "2.0",
  "result": "0x1" // 1
}
*/
bool EthRPC::eth_newPendingTransactionFilter(EInt &filterId)
{
    return m_p->call_rpc_method("eth_newPendingTransactionFilter", QVariantList(), filterId);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_uninstallFilter","params":["0xb"],"id":73}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": true
}
*/
bool EthRPC::eth_uninstallFilter(const EInt &filterId, EBool &uninstalled)
{
    QVariantList params;
    params.append(filterId.toRawData());
    return m_p->call_rpc_method("eth_uninstallFilter", params, uninstalled);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getFilterChanges","params":["0x16"],"id":73}'

// Result
{
  "id":1,
  "jsonrpc":"2.0",
  "result": [{
    "logIndex": "0x1", // 1
    "blockNumber":"0x1b4" // 436
    "blockHash": "0x8216c5785ac562ff41e2dcfdf5785ac562ff41e2dcfdf829c5a142f1fccd7d",
    "transactionHash":  "0xdf829c5a142f1fccd7d8216c5785ac562ff41e2dcfdf5785ac562ff41e2dcf",
    "transactionIndex": "0x0", // 0
    "address": "0x16c5785ac562ff41e2dcfdf829c5a142f1fccd7d",
    "data":"0x0000000000000000000000000000000000000000000000000000000000000000",
    "topics": ["0x59ebeb90bc63057b6515673c3ecf9438e5058bca0f92585014eced636878c9a5"]
    },{
      ...
    }]
}
*/
bool EthRPC::eth_getFilterChanges(const EInt &filterId, EByteArrayList &logs)
{
    QVariantList params;
    params.append(filterId.toRawData());
    return m_p->call_rpc_method("eth_getFilterChanges", params, logs);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getFilterLogs","params":["0x16"],"id":74}'
*/
bool EthRPC::eth_getFilterLogs(const EInt &filterId, EByteArrayList &logs)
{
    QVariantList params;
    params.append(filterId.toRawData());
    return m_p->call_rpc_method("eth_getFilterLogs", params, logs);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"eth_getWork","params":[],"id":73}'

// Result
{
  "id":1,
  "jsonrpc":"2.0",
  "result": [
      "0x1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef",
      "0x5EED00000000000000000000000000005EED0000000000000000000000000000",
      "0xd1ff1c01710000000000000000000000d1ff1c01710000000000000000000000"
    ]
}
*/
bool EthRPC::eth_getWork(EByteArrayList &properties)
{
    return m_p->call_rpc_method("eth_getWork", QVariantList(), properties);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0", "method":"eth_submitWork", "params":["0x0000000000000001", "0x1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef", "0xD1GE5700000000000000000000000000D1GE5700000000000000000000000000"],"id":73}'

// Result
{
  "id":1,
  "jsonrpc":"2.0",
  "result": true
}
*/
bool EthRPC::eth_submitWork(const EByteArray &nonce, const EByteArray &powHash, const EByteArray &mixDigest, EBool &isValid)
{
    QVariantList params;
    params.append(nonce.toRawData());
    params.append(powHash.toRawData());
    params.append(mixDigest.toRawData());
    return m_p->call_rpc_method("eth_submitWork", params, isValid);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0", "method":"eth_submitHashrate", "params":["0x0000000000000000000000000000000000000000000000000000000000500000", "0x59daa26581d0acd1fce254fb7e85952f4c09d0915afd33d3886cd914bc7d283c"],"id":73}'

// Result
{
  "id":73,
  "jsonrpc":"2.0",
  "result": true
}
*/
bool EthRPC::eth_submitHashrate(const EByteArray &hashrate, const EByteArray &ID, EBool &isSubmited)
{
    QVariantList params;
    params.append(hashrate.toRawData());
    params.append(ID.toRawData());
    return m_p->call_rpc_method("eth_submitHashrate", params, isSubmited);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"db_putString","params":["testDB","myKey","myString"],"id":73}'

// Result
{
  "id":1,
  "jsonrpc":"2.0",
  "result": true
}
*/
bool EthRPC::db_putString(const EString &databaseName, const EString &keyName, const EString &stringValue, EBool &isStored)
{
    QVariantList params;
    params.append(databaseName.toRawData());
    params.append(keyName.toRawData());
    params.append(stringValue.toRawData());
    return m_p->call_rpc_method("db_putString", params, isStored);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"db_getString","params":["testDB","myKey"],"id":73}'

// Result
{
  "id":1,
  "jsonrpc":"2.0",
  "result": "myString"
}
*/
bool EthRPC::db_getString(const EString &databaseName, const EString &keyName, EString &stringValue)
{
    QVariantList params;
    params.append(databaseName.toRawData());
    params.append(keyName.toRawData());
    return m_p->call_rpc_method("db_getString", params, stringValue);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"db_putHex","params":["testDB","myKey","0x68656c6c6f20776f726c64"],"id":73}'

// Result
{
  "id":1,
  "jsonrpc":"2.0",
  "result": true
}
*/
bool EthRPC::db_putHex(const EString &databaseName, const EString &keyName, const EByteArray &hexValue, EBool &isStored)
{
    QVariantList params;
    params.append(databaseName.toRawData());
    params.append(keyName.toRawData());
    params.append(hexValue.toRawData());
    return m_p->call_rpc_method("db_putHex", params, isStored);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"db_getHex","params":["testDB","myKey"],"id":73}'

// Result
{
  "id":1,
  "jsonrpc":"2.0",
  "result": "0x68656c6c6f20776f726c64"
}
*/
bool EthRPC::db_getHex(const EString &databaseName, const EString &keyName, EByteArray &hexValue)
{
    QVariantList params;
    params.append(databaseName.toRawData());
    params.append(keyName.toRawData());
    return m_p->call_rpc_method("db_getHex", params, hexValue);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"shh_post","params":[{"from":"0xc931d93e97ab07fe42d923478ba2465f2..","topics": ["0x68656c6c6f20776f726c64"],"payload":"0x68656c6c6f20776f726c64","ttl":0x64,"priority":0x64}],"id":73}'

// Result
{
  "id":1,
  "jsonrpc":"2.0",
  "result": true
}
*/
bool EthRPC::shh_post(const SWhisper &message, EBool &wasSend)
{
    QVariantList params;
    params.append(message.toRawData());
    return m_p->call_rpc_method("shh_post", params, wasSend);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"shh_newIdentity","params":[],"id":73}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0xc931d93e97ab07fe42d923478ba2465f283f440fd6cabea4dd7a2c807108f651b7135d1d6ca9007d5b68aa497e4619ac10aa3b27726e1863c1fd9b570d99bbaf"
}
*/
bool EthRPC::shh_newIdentity(EByteArray &address)
{
    return m_p->call_rpc_method("shh_newIdentity", QVariantList(), address);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"shh_hasIdentity","params":["0x04f96a5e25610293e42a73908e93ccc8c4d4dc0edcfa9fa872f50cb214e08ebf61a03e245533f97284d442460f2998cd41858798ddfd4d661997d3940272b717b1"],"id":73}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": true
}
*/
bool EthRPC::shh_hasIdentity(const EByteArray &address, EBool &hasIdentity)
{
    QVariantList params;
    params.append(address.toRawData());
    return m_p->call_rpc_method("shh_hasIdentity", params, hasIdentity);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"shh_newIdentity","params":[],"id":73}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": "0xc65f283f440fd6cabea4dd7a2c807108f651b7135d1d6ca90931d93e97ab07fe42d923478ba2407d5b68aa497e4619ac10aa3b27726e1863c1fd9b570d99bbaf"
}
*/
bool EthRPC::shh_newGroup(EByteArray &address)
{
    return m_p->call_rpc_method("shh_newGroup", QVariantList(), address);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"shh_hasIdentity","params":["0x04f96a5e25610293e42a73908e93ccc8c4d4dc0edcfa9fa872f50cb214e08ebf61a03e245533f97284d442460f2998cd41858798ddfd4d661997d3940272b717b1"],"id":73}'

// Result
{
  "id":1,
  "jsonrpc": "2.0",
  "result": true
}
*/
bool EthRPC::shh_addToGroup(const EByteArray &address, EBool &wasAdded)
{
    QVariantList params;
    params.append(address.toRawData());
    return m_p->call_rpc_method("shh_addToGroup", params, wasAdded);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"shh_newFilter","params":[{"topics": ['0x12341234bf4b564f'],"to": "0x2341234bf4b2341234bf4b564f..."}],"id":73}'

// Result
{
  "id":1,
  "jsonrpc":"2.0",
  "result": "0x7" // 7
}
*/
bool EthRPC::shh_newFilter(const SFilter &filter, EInt &filterId)
{
    QVariantList params;
    params.append(filter.toRawData());
    return m_p->call_rpc_method("shh_newFilter", params, filterId);
}

/*
// Request
curl -X POST --data '{"jsonrpc":"2.0","method":"shh_getFilterChanges","params":["0x7"],"id":73}'

// Result
{
  "id":1,
  "jsonrpc":"2.0",
  "result": [{
    "hash": "0x33eb2da77bf3527e28f8bf493650b1879b08c4f2a362beae4ba2f71bafcd91f9",
    "from": "0x3ec052fc33..",
    "to": "0x87gdf76g8d7fgdfg...",
    "expiry": "0x54caa50a", // 1422566666
    "sent": "0x54ca9ea2", // 1422565026
    "ttl": "0x64" // 100
    "topics": ["0x6578616d"],
    "payload": "0x7b2274797065223a226d657373616765222c2263686...",
    "workProved": "0x0"
    }]
}
*/
bool EthRPC::shh_getFilterChanges(const EInt &filterId, QList<SFilterMessage> &messages)
{
    Q_UNUSED(filterId);
    Q_UNUSED(messages);

    return false;
}

bool EthRPC::shh_getMessages(const EInt &filterId, QList<SFilterMessage> &messages)
{
    Q_UNUSED(filterId);
    Q_UNUSED(messages);
    /*
    // Request
    curl -X POST --data '{"jsonrpc":"2.0","method":"shh_getMessages","params":["0x7"],"id":73}'
    */
    return false;
}
