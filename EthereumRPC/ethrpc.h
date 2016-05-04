#ifndef ETHRPC_H
#define ETHRPC_H

#include "ethrpc_global.h"
#include "ethobject.h"

class RPC_Private;

/**
 * @brief The EthRPC class that implement the interface for the JSON RTC API defined in the link:
 * https://github.com/ethereum/wiki/wiki/JSON-RPC
 */
class ETHRPCSHARED_EXPORT EthRPC
{

public:
    /**
     * @brief EthRPC Constructor
     */
    EthRPC();

    /**
     * @brief ~EthRPC Destructor
     */
    virtual ~EthRPC();

    /**
     * @brief connect Return true of the connection to the server
     * @param serverUri Uri to the server
     * @return true if can connect, otherwise false
     */
    bool connect(const EString& serverUri);

    /**
     * @brief web3_clientVersion Returns the current client version.
     * @param clientVersion The current client version.
     * @return Success of the RPC.
     */
    bool web3_clientVersion(EString& clientVersion);

    /**
     * @brief web3_sha3 Returns Keccak-256 (not the standardized SHA3-256) of the given data.
     * @param rowData The data to convert into a SHA3 hash.
     * @param SHA3Data The SHA3 result of the given string.
     * @return Success of the RPC.
     */
    bool web3_sha3(const EByteArray& rowData, EByteArray& hash);

    /**
     * @brief net_version Returns the current network protocol version.
     * @param clientVersion The current network protocol version.
     * @return Success of the RPC.
     */
    bool net_version(EString& clientVersion);

    /**
     * @brief net_listening Returns true if client is actively listening for network connections.
     * @param isListening true when listening, otherwise false.
     * @return Success of the RPC.
     */
    bool net_listening(EBool& isListening);

    /**
     * @brief net_peerCount Returns number of peers currenly connected to the client.
     * @param numberConnected integer of the number of connected peers.
     * @return Success of the RPC.
     */
    bool net_peerCount(EInt& numberConnected);

    /**
     * @brief eth_protocolVersion Returns the current ethereum protocol version.
     * @param clientVersion The current ethereum protocol version
     * @return Success of the RPC.
     */
    bool eth_protocolVersion(EString& clientVersion);

    /**
     * @brief eth_syncing Returns an object with data about the sync status.
     * @param syncing An object with sync status data.
     * @return Success of the RPC.
     */
    bool eth_syncing(ESyncing& syncing);

    /**
     * @brief eth_coinbase Returns the client coinbase address.
     * @param coinbaseAddress DATA, 20 bytes - the current coinbase address.
     * @return Success of the RPC.
     */
    bool eth_coinbase(EByteArray& coinbaseAddress);

    /**
     * @brief eth_mining Returns true if client is actively mining new blocks.
     * @param isMining Returns true of the client is mining, otherwise false.
     * @return Success of the RPC.
     */
    bool eth_mining(EBool& isMining);

    /**
     * @brief eth_hashrate Returns the number of hashes per second that the node is mining with.
     * @param hashesPerSec Number of hashes per second.
     * @return Success of the RPC.
     */
    bool eth_hashrate(EInt& hashesPerSec);

    /**
     * @brief eth_gasPrice Returns the current price per gas in wei.
     * @param currentGasPrice Integer of the current gas price in wei.
     * @return Success of the RPC.
     */
    bool eth_gasPrice(EInt& currentGasPrice);

    /**
     * @brief eth_accounts Returns a list of addresses owned by client.
     * @param ethAddresses Array of DATA, 20 Bytes - addresses owned by the client.
     * @return Success of the RPC.
     */
    bool eth_accounts(EByteArrayList& ethAddresses);

    /**
     * @brief eth_blockNumber Returns the number of most recent block.
     * @param currentBlockNumber integer of the current block number the client is on.
     * @return Success of the RPC.
     */
    bool eth_blockNumber(EInt& currentBlockNumber);

    /**
     * @brief eth_getBalance Returns the balance of the account of given address.
     * @param ethAddress DATA, 20 Bytes - address to check for balance.
     * @param blockId Integer block number or string "latest", "earliest" or "pending".
     * @param currentBalance Integer of the current balance in wei.
     * @return Success of the RPC.
     */
    bool eth_getBalance(const EByteArray& ethAddress, const EVariant& blockId, EInt& currentBalance);

    /**
     * @brief eth_getStorageAt Returns the value from a storage position at a given address.
     * @param storageAddress DATA, 20 Bytes - address of the storage.
     * @param position Integer of the position in the storage.
     * @param blockId Integer block number or string "latest", "earliest" or "pending".
     * @param value The value at this storage position.
     * @return Success of the RPC.
     */
    bool eth_getStorageAt(const EByteArray& storageAddress, const EInt& position, const EVariant& blockId, EByteArray& value);

    /**
     * @brief eth_getTransactionCount Returns the number of transactions sent from an address.
     * @param ethAddress DATA, 20 Bytes - address.
     * @param blockId Integer block number or string "latest", "earliest" or "pending".
     * @param numberTransactions Integer of the number of transactions send from this address.
     * @return Success of the RPC.
     */
    bool eth_getTransactionCount(const EByteArray& ethAddress, const EVariant& blockId, EInt& numberTransactions);

    /**
     * @brief eth_getBlockTransactionCountByHash Returns the number of transactions in a block from a block matching the given block hash.
     * @param hashBlock DATA, 32 Bytes - hash of a block
     * @param numberTransactions Integer of the number of transactions in this block.
     * @return Success of the RPC.
     */
    bool eth_getBlockTransactionCountByHash(const EByteArray& hashBlock, EInt& numberTransactions);

    /**
     * @brief eth_getBlockTransactionCountByNumber Returns the number of transactions in a block from a block matching the given block number.
     * @param blockId Integer block number or string "latest", "earliest" or "pending".
     * @param numberTransactions Integer of the number of transactions in this block.
     * @return Success of the RPC.
     */
    bool eth_getBlockTransactionCountByNumber(const EVariant& blockId, EInt& numberTransactions);

    /**
     * @brief eth_getUncleCountByBlockHash Returns the number of uncles in a block from a block matching the given block hash.
     * @param hashBlock DATA, 32 Bytes - hash of a block
     * @param numberUncles Integer of the number of uncles in this block.
     * @return Success of the RPC.
     */
    bool eth_getUncleCountByBlockHash(const EByteArray& hashBlock, EInt& numberUncles);

    /**
     * @brief eth_getUncleCountByBlockNumber Returns the number of uncles in a block from a block matching the given block number.
     * @param blockId Integer block number or string "latest", "earliest" or "pending".
     * @param numberUncles Integer of the number of uncles in this block.
     * @return Success of the RPC.
     */
    bool eth_getUncleCountByBlockNumber(const EVariant& blockId, EInt& numberUncles);

    /**
     * @brief eth_getCode Returns code at a given address.
     * @param ethAddress DATA, 20 Bytes - address
     * @param blockId Integer block number or string "latest", "earliest" or "pending".
     * @param addressCode DATA - the code from the given address.
     * @return Success of the RPC.
     */
    bool eth_getCode(const EByteArray& ethAddress, const EVariant& blockId, EByteArray& addressCode);

    /**
     * @brief eth_sign Signs data with a given address.
     * Note the address to sign must be unlocked.
     * @param ethAddress DATA, 20 Bytes - address
     * @param plainData DATA, Data to sign
     * @param cipheredData DATA: Signed data
     * @return Success of the RPC.
     */
    bool eth_sign(const EByteArray& ethAddress, const EByteArray& plainData, EByteArray& cipheredData);

    /**
     * @brief eth_sendTransaction Creates new message call transaction or a contract creation, if the data field contains code.
     * @param transaction The transaction object
     * 	from: DATA, 20 Bytes - The address the transaction is send from.
     * 	to: DATA, 20 Bytes - (optional when creating new contract) The address the transaction is directed to.
     * 	gas: QUANTITY - (optional, default: 90000) Integer of the gas provided for the transaction execution. It will return unused gas.
     * 	gasPrice: QUANTITY - (optional, default: To-Be-Determined) Integer of the gasPrice used for each paid gas
     * 	value: QUANTITY - (optional) Integer of the value send with this transaction
     * 	data: DATA - The compiled code of a contract OR the hash of the invoked method signature and encoded parameters. For details see Ethereum Contract ABI
     * 	nonce: QUANTITY - (optional) Integer of a nonce. This allows to overwrite your own pending transactions that use the same nonce.
     * @param transactionHash DATA, 32 Bytes - the transaction hash, or the zero hash if the transaction is not yet available.
     * @return Success of the RPC.
     */
    bool eth_sendTransaction(const ETransaction& transaction, EByteArray& transactionHash);

    /**
     * @brief eth_sendRawTransaction Creates new message call transaction or a contract creation for signed transactions.
     * @param signedData DATA, The signed transaction data.
     * @param transactionHash DATA, 32 Bytes - the transaction hash, or the zero hash if the transaction is not yet available.
     * @return Success of the RPC.
     */
    bool eth_sendRawTransaction(const EByteArray& signedData, EByteArray& transactionHash);

    /**
     * @brief eth_call Executes a new message call immediately without creating a transaction on the block chain.
     * @param transaction The transaction call object
     * 	from: DATA, 20 Bytes - (optional) The address the transaction is send from.
     * 	to: DATA, 20 Bytes - The address the transaction is directed to.
     * 	gas: QUANTITY - (optional) Integer of the gas provided for the transaction execution. eth_call consumes zero gas, but this parameter may be needed by some executions.
     * 	gasPrice: QUANTITY - (optional) Integer of the gasPrice used for each paid gas
     * 	value: QUANTITY - (optional) Integer of the value send with this transaction
     * 	data: DATA - (optional) Hash of the method signature and encoded parameters.
     * @param blockId Integer block number or string "latest", "earliest" or "pending".
     * @param returnValue DATA - the return value of executed contract.
     * @return Success of the RPC.
     */
    bool eth_call(const ETransaction& transaction, const EVariant& blockId, EByteArray& returnValue);

    /**
     * @brief eth_estimateGas Makes a call or transaction, which won't be added to the blockchain and returns the used gas, which can be used for estimating the used gas.
     * See eth_call parameters, expect that all properties are optional.
     * @param gasUsed QUANTITY - the amount of gas used.
     * @return Success of the RPC.
     */
    bool eth_estimateGas(const ETransaction& transaction, const EInt& blockNumber, EInt& gasUsed);

    /**
     * @brief eth_estimateGas Makes a call or transaction, which won't be added to the blockchain and returns the used gas, which can be used for estimating the used gas.
     * See eth_call parameters, expect that all properties are optional.
     * @param gasUsed QUANTITY - the amount of gas used.
     * @return Success of the RPC.
     */
    bool eth_estimateGas(const ETransaction& transaction, const EString& blockTag, EInt& gasUsed);

    /**
     * @brief eth_getBlockByHash Returns information about a block by hash.
     * @param hashBlock DATA, 32 Bytes - Hash of a block.
     * @param full Boolean - If true it returns the full transaction objects, if false only the hashes of the transactions.
     * @param block Object - A block object, or null when no block was found.
     * @return Success of the RPC.
     */
    bool eth_getBlockByHash(const EByteArray& hashBlock, const EBool& full, EBlock& block);

    /**
     * @brief eth_getBlockByNumber Returns information about a block by block number.
     * @param blockId Integer block number or string "latest", "earliest" or "pending".
     * @param full Boolean - If true it returns the full transaction objects, if false only the hashes of the transactions.
     * @param block Object - A block object, or null when no block was found.
     * @return Success of the RPC.
     */
    bool eth_getBlockByNumber(const EVariant& blockId, const EBool& full, EBlock& block);

    /**
     * @brief eth_getTransactionByHash Returns the information about a transaction requested by transaction hash.
     * @param transactionHash DATA, 32 Bytes - hash of a transaction
     * @param transaction Object - A transaction object, or null when no transaction was found.
     * 	hash: DATA, 32 Bytes - hash of the transaction.
     * 	nonce: QUANTITY - the number of transactions made by the sender prior to this one.
     * 	blockHash: DATA, 32 Bytes - hash of the block where this transaction was in. null when its pending.
     * 	blockNumber: QUANTITY - block number where this transaction was in. null when its pending.
     * 	transactionIndex: QUANTITY - integer of the transactions index position in the block. null when its pending.
     * 	from: DATA, 20 Bytes - address of the sender.
     * 	to: DATA, 20 Bytes - address of the receiver. null when its a contract creation transaction.
     * 	value: QUANTITY - value transferred in Wei.
     * 	gasPrice: QUANTITY - gas price provided by the sender in Wei.
     * 	gas: QUANTITY - gas provided by the sender.
     * 	input: DATA - the data send along with the transaction.
     * @return Success of the RPC.
     */
    bool eth_getTransactionByHash(const EByteArray& transactionHash, ETransaction& transaction);

    /**
     * @brief eth_getTransactionByBlockHashAndIndex Returns information about a transaction by block hash and transaction index position.
     * @param hashBlock DATA, 32 Bytes - hash of a block.
     * @param transactionIndex QUANTITY - integer of the transaction index position.
     * @param transaction Object - A transaction object, or null when no transaction was found.
     * @return Success of the RPC.
     */
    bool eth_getTransactionByBlockHashAndIndex(const EByteArray& hashBlock, const EInt& transactionIndex, ETransaction& transaction);

    /**
     * @brief eth_getTransactionByBlockNumberAndIndex Returns information about a transaction by block number and transaction index position.
     * @param blockId Integer block number or string "latest", "earliest" or "pending".
     * @param transactionIndex The transaction index position.
     * @param transaction Object - A transaction object, or null when no transaction was found.
     * @return Success of the RPC.
     */
    bool eth_getTransactionByBlockNumberAndIndex(const EVariant& blockId, const EInt& transactionIndex, ETransaction& transaction);

    /**
     * @brief eth_getTransactionReceipt Returns the receipt of a transaction by transaction hash.
     * Note That the receipt is not available for pending transactions.
     * @param transactionHash DATA, 32 Bytes - hash of a transaction
     * @param receipt A transaction receipt object, or null when no receipt was found
     * @return Success of the RPC.
     */
    bool eth_getTransactionReceipt(const EByteArray& transactionHash, EReceipt& receipt);

    /**
     * @brief eth_getUncleByBlockHashAndIndex Returns information about a uncle of a block by hash and uncle index position.
     * @param hashBlock DATA, 32 Bytes - hash a block.
     * @param possition QUANTITY - the uncle's index position.
     * @param block See eth_getBlockByHash
     * @return Success of the RPC.
     */
    bool eth_getUncleByBlockHashAndIndex(const EByteArray& hashBlock, const EInt& possition, EBlock& block);

    /**
     * @brief eth_getUncleByBlockNumberAndIndex Returns information about a uncle of a block by number and uncle index position.
     * @param blockId Integer block number or string "latest", "earliest" or "pending".
     * @param possition The uncle's index position.
     * @param block See eth_getBlockByHash
     * @return Success of the RPC.
     */
    bool eth_getUncleByBlockNumberAndIndex(const EVariant& blockId, const EInt& possition, EBlock& block);

    /**
     * @brief eth_getCompilers Returns a list of available compilers in the client.
     * @param compilers Array - Array of available compilers.
     * @return Success of the RPC.
     */
    bool eth_getCompilers(QStringList& compilers);

    /**
     * @brief eth_compileSolidity Returns compiled solidity code.
     * @param sourceCode The source code.
     * @param compiledCode The compiled source code.
     * @return Success of the RPC.
     */
    bool eth_compileSolidity(const EString& sourceCode, EString& compiledCode);

    /**
     * @brief eth_compileLLL Returns compiled LLL code.
     * @param sourceCode String - The source code.
     * @param compiledCode DATA - The compiled source code.
     * @return Success of the RPC.
     */
    bool eth_compileLLL(const EString& sourceCode, EString& compiledCode);

    /**
     * @brief eth_compileSerpent Returns compiled serpent code.
     * @param sourceCode String - The source code.
     * @param compiledCode DATA - The compiled source code.
     * @return Success of the RPC.
     */
    bool eth_compileSerpent(const EString& sourceCode, EString& compiledCode);

    /**
     * @brief eth_newFilter Creates a filter object, based on filter options, to notify when the state changes (logs).
     * @param filter The filter options
     * @param filterId QUANTITY - A filter id.
     * @return Success of the RPC.
     */
    bool eth_newFilter(const EFilter& filter, EInt& filterId);

    /**
     * @brief eth_newBlockFilter Creates a filter in the node, to notify when a new block arrives.
     * @param filterId  A filter id.
     * @return Success of the RPC.
     */
    bool eth_newBlockFilter(EInt& filterId);

    /**
     * @brief eth_newPendingTransactionFilter Creates a filter in the node, to notify when new pending transactions arrive.
     * @param filterId QUANTITY - A filter id.
     * @return Success of the RPC.
     */
    bool eth_newPendingTransactionFilter(EInt& filterId);

    /**
     * @brief eth_uninstallFilter Uninstalls a filter with given id. Should always be called when watch is no longer needed.
     * @param filterId The filter id.
     * @param uninstalled Boolean - true if the filter was successfully uninstalled, otherwise false.
     * @return Success of the RPC.
     */
    bool eth_uninstallFilter(const EInt& filterId, EBool& uninstalled);

    /**
     * @brief eth_getFilterChanges Polling method for a filter, which returns an array of logs which occurred since last poll.
     * @param filterId QUANTITY - the filter id.
     * @param logs Array - Array of log objects, or an empty array if nothing has changed since last poll.
     * @return Success of the RPC.
     */
    bool eth_getFilterChanges(const EInt& filterId, EByteArrayList& logs);

    /**
     * @brief eth_getFilterLogs Returns an array of all logs matching filter with given id.
     * @param filterId QUANTITY - the filter id.
     * @param logs Array - Array of log objects, or an empty array if nothing has changed since last poll.
     * @return Success of the RPC.
     */
    bool eth_getFilterLogs(const EInt& filterId, EByteArrayList& logs);

    /**
     * @brief eth_getWork Returns the hash of the current block, the seedHash, and the boundary condition to be met ("target").
     * @param properties Array - Array with the following properties:
     *  DATA, 32 Bytes - current block header pow-hash
     *  DATA, 32 Bytes - the seed hash used for the DAG.
     *  DATA, 32 Bytes - the boundary condition ("target"), 2^256 / difficulty.
     * @return Success of the RPC.
     */
    bool eth_getWork(EByteArrayList& properties);

    /**
     * @brief eth_submitWork Used for submitting a proof-of-work solution.
     * @param nonce DATA, 8 Bytes - The nonce found (64 bits)
     * @param powHash DATA, 32 Bytes - The header's pow-hash (256 bits)
     * @param mixDigest DATA, 32 Bytes - The mix digest (256 bits)
     * @param isValid Boolean - returns true if the provided solution is valid, otherwise false.
     * @return Success of the RPC.
     */
    bool eth_submitWork(const EByteArray& nonce, const EByteArray& powHash, const EByteArray& mixDigest, EBool& isValid);

    /**
     * @brief eth_submitHashrate Used for submitting mining hashrate.
     * @param hashrate A hexadecimal string representation (32 bytes) of the hash rate.
     * @param ID String - A random hexadecimal(32 bytes) ID identifying the client.
     * @param isSubmited Boolean - returns true if submitting went through succesfully and false otherwise.
     * @return Success of the RPC.
     */
    bool eth_submitHashrate(const EByteArray& hashrate, const EByteArray& ID, EBool& isSubmited);

    /**
     * @brief db_putString Stores a string in the local database.
     *  Note this function is deprecated and will be removed in the future.
     * @param databaseName String - Database name.
     * @param keyName String - Key name.
     * @param stringValue String - String to store.
     * @param isStored Boolean - returns true if the value was stored, otherwise false.
     * @return Success of the RPC.
     */
    bool db_putString(const EString& databaseName, const EString& keyName, const EString& stringValue, EBool& isStored);

    /**
     * @brief db_getString Returns string from the local database.
     *  Note this function is deprecated and will be removed in the future.
     * @param databaseName String - Database name.
     * @param keyName String - Key name.
     * @param stringValue String - The previously stored string.
     * @return Success of the RPC.
     */
    bool db_getString(const EString& databaseName, const EString& keyName, EString& stringValue);

    /**
     * @brief db_putHex Stores binary data in the local database.
     *  Note this function is deprecated and will be removed in the future.
     * @param databaseName String - Database name.
     * @param keyName String - Key name.
     * @param hexValue DATA - The data to store.
     * @param isStored Boolean - returns true if the value was stored, otherwise false.
     * @return Success of the RPC.
     */
    bool db_putHex(const EString& databaseName, const EString& keyName, const EByteArray& hexValue, EBool& isStored);

    /**
     * @brief db_getHex Returns binary data from the local database.
     *  Note this function is deprecated and will be removed in the future.
     * @param databaseName String - Database name.
     * @param keyName String - Key name.
     * @param hexValue DATA - The previously stored data.
     * @return Success of the RPC.
     */
    bool db_getHex(const EString& databaseName, const EString& keyName, EByteArray& hexValue);

    /**
     * @brief shh_version Returns the current whisper protocol version.
     * @param version String - The current whisper protocol version
     * @return Success of the RPC.
     */
    bool shh_version(EString& version);

    /**
     * @brief shh_post Sends a whisper message.
     * @param message The whisper post object:
     *  from: DATA, 60 Bytes - (optional) The identity of the sender.
     *  to: DATA, 60 Bytes - (optional) The identity of the receiver. When present whisper will encrypt the message so that only the receiver can decrypt it.
     *  topics: Array of DATA - Array of DATA topics, for the receiver to identify messages.
     *  payload: DATA - The payload of the message.
     *  priority: QUANTITY - The integer of the priority in a rang from ... (?).
     *  ttl: QUANTITY - integer of the time to live in seconds.
     * @param wasSend Boolean - returns true if the message was send, otherwise false.
     * @return Success of the RPC.
     */
    bool shh_post(const SWhisper& message, EBool& wasSend);

    /**
     * @brief shh_newIdentity Creates new whisper identity in the client.
     * @param address DATA, 60 Bytes - the address of the new identiy.
     * @return Success of the RPC.
     */
    bool shh_newIdentity(EByteArray& address);

    /**
     * @brief shh_hasIdentity Checks if the client hold the private keys for a given identity.
     * @param address DATA, 60 Bytes - The identity address to check.
     * @param hasIdentity Boolean - returns true if the client holds the privatekey for that identity, otherwise false.
     * @return Success of the RPC.
     */
    bool shh_hasIdentity(const EByteArray& address, EBool& hasIdentity);

    /**
     * @brief shh_newGroup Creates new whisper group in the client.
     * @param address DATA, 60 Bytes - the address of the new group.
     * @return Success of the RPC.
     */
    bool shh_newGroup(EByteArray& address);

    /**
     * @brief shh_addToGroup Add identity address to the group
     * @param address DATA, 60 Bytes - The identity address to add to a group.
     * @param wasAdded Boolean - returns true if the identity was successfully added to the group, otherwise false.
     * @return Success of the RPC.
     */
    bool shh_addToGroup(const EByteArray& address, EBool& wasAdded);

    /**
     * @brief shh_newFilter Creates filter to notify, when client receives whisper message matching the filter options.
     * @param filter Object - The filter options
     * @param filterId QUANTITY - The newly created filter.
     * @return Success of the RPC.
     */
    bool shh_newFilter(const SFilter& filter, EInt& filterId);

    /**
     * @brief shh_uninstallFilter Uninstalls a filter with given id. Should always be called when watch is no longer needed.
     * @param filterId The filter id.
     * @param wasUninstalled Boolean - true if the filter was successfully uninstalled, otherwise false.
     * @return Success of the RPC.
     */
    bool shh_uninstallFilter(const EInt& filterId, EBool& wasUninstalled);

    /**
     * @brief shh_getFilterChanges Polling method for whisper filters.
     * Returns new messages since the last call of this method.
     * Note calling the shh_getMessages method,
     * will reset the buffer for this method, so that you won't receive duplicate messages.
     * @param filterId The filter id.
     * @param messages Array - Array of messages received since last poll.
     * @return Success of the RPC.
     */
    bool shh_getFilterChanges(const EInt& filterId, QList<SFilterMessage>& messages);

    /**
     * @brief shh_getMessages Get all messages matching a filter. Unlike shh_getFilterChanges this returns all messages.
     * @param filterId The filter id.
     * @param messages Array - Array of messages received since last poll.
     * @return Success of the RPC.
     */
    bool shh_getMessages(const EInt& filterId, QList<SFilterMessage>& messages);

private:
    RPC_Private* m_p;
};

#endif // ETHRPC_H

