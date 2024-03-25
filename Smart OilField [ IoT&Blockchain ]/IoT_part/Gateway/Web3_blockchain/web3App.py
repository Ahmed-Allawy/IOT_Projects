from web3 import Web3
import json

# ulrRPC = 'https://mainnet.infura.io/v3/f5678441ae9948189dc46b5368d834a7'
# contractABI = json.loads('[{"inputs":[{"internalType":"address","name":"s_priceFeed","type":"address"}],"stateMutability":"nonpayable","type":"constructor"},{"inputs":[],"name":"FundMe_NotOwner","type":"error"},{"stateMutability":"payable","type":"fallback"},{"inputs":[],"name":"Min_USD","outputs":[{"internalType":"uint256","name":"","type":"uint256"}],"stateMutability":"view","type":"function"},{"inputs":[],"name":"cheaperWithdraw","outputs":[],"stateMutability":"payable","type":"function"},{"inputs":[],"name":"fund","outputs":[],"stateMutability":"payable","type":"function"},{"inputs":[],"name":"priceFeed","outputs":[{"internalType":"contract AggregatorV3Interface","name":"","type":"address"}],"stateMutability":"view","type":"function"},{"inputs":[{"internalType":"uint256","name":"","type":"uint256"}],"name":"sender","outputs":[{"internalType":"address","name":"","type":"address"}],"stateMutability":"view","type":"function"},{"inputs":[],"name":"withdraw","outputs":[],"stateMutability":"nonpayable","type":"function"},{"stateMutability":"payable","type":"receive"}]')
# contractAddress = '0x2A7A19c821d6565219Cd9c2CDe1525c0D26b424D'

# ulrRPC = 'https://eth-sepolia.g.alchemy.com/v2/u8_uLJJIlQkZqdD_S69kowsov-pFQ_V4'
# contractABI = json.loads('[{"inputs":[{"internalType":"string","name":"_name","type":"string"},{"internalType":"uint256","name":"_favNum","type":"uint256"}],"name":"addPerson","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"string","name":"","type":"string"}],"name":"nameToNum","outputs":[{"internalType":"uint256","name":"","type":"uint256"}],"stateMutability":"view","type":"function"},{"inputs":[{"internalType":"uint256","name":"","type":"uint256"}],"name":"people","outputs":[{"internalType":"uint256","name":"faveNum","type":"uint256"},{"internalType":"string","name":"name","type":"string"}],"stateMutability":"view","type":"function"},{"inputs":[],"name":"retrieve","outputs":[{"internalType":"uint256","name":"","type":"uint256"}],"stateMutability":"view","type":"function"},{"inputs":[],"name":"retrieveStr","outputs":[{"internalType":"string","name":"","type":"string"}],"stateMutability":"view","type":"function"},{"inputs":[{"internalType":"uint256","name":"_favNum","type":"uint256"}],"name":"store","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"string","name":"name","type":"string"}],"name":"storeStr","outputs":[],"stateMutability":"nonpayable","type":"function"}]')
# contractAddress = '0x44bF73bcdFbf14a5E0faEaF3cbA1cd37293a7245'

ulrRPC = 'https://eth-sepolia.g.alchemy.com/v2/u8_uLJJIlQkZqdD_S69kowsov-pFQ_V4'
contractABI = json.loads('[{"inputs":[],"name":"OilField__NotAdmin","type":"error"},{"inputs":[],"name":"OilField__NotOwner","type":"error"},{"anonymous":false,"inputs":[{"indexed":true,"internalType":"address","name":"owner","type":"address"},{"indexed":false,"internalType":"string","name":"data","type":"string"}],"name":"appData","type":"event"},{"inputs":[{"internalType":"address","name":"_user","type":"address"}],"name":"addPerson","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"string","name":"data","type":"string"}],"name":"storeAppData","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"string","name":"data","type":"string"}],"name":"storeIoTData","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"uint256","name":"","type":"uint256"}],"name":"users","outputs":[{"internalType":"address","name":"","type":"address"}],"stateMutability":"view","type":"function"}]')
contractAddress = '0xd0ae9F331d306dA48E7119028413771b0F36FdC1'

web3 = Web3(Web3.HTTPProvider(ulrRPC))

if web3.is_connected()==True:
    print('connected')
    contract = web3.eth.contract(address=contractAddress, abi=contractABI)
    # contract.functions.store(100).transact({})
    # contractName = contract.functions.retrieve().call()
    # print(contractName)
    # contractPName = contract.functions.retrieveStr().call()
    # print(contractPName)
    # data = json.loads(contractPName)
    # topic = data["topic"]
    # payload = json.loads(data["payload"])
    # print(f"topic: {topic}")
    # print(f"payload: {payload}")
    # print(f"temperature: {payload['temperature']}")
# block = web3.eth.get_block('latest')
# print(block.hash)
# print(web3.to_hex(block.hash))
# balance = web3.eth.get_balance('0x90437f445861b58380C840144C55628203aE2fA9')
# ethr = web3.from_wei(balance,'ether')
# print(ethr)
# print(web3.eth._gas_price())
# 67e12ada4f7470595e3f50101efb993db79a6bd391b2a9281660e34b88362c96
nonce = web3.eth.get_transaction_count('0x90437f445861b58380C840144C55628203aE2fA9')
gasprice =  web3.eth._gas_price()
payload = json.dumps({'temperature' : 34.34})
data = json.dumps({"topic":'allawy/asd',"payload":payload})
# data = '{"tem":24}'
transaction = contract.functions.storeAppData(data).build_transaction({
    'gas': 100000,
    'gasPrice': gasprice,
    'from': '0x90437f445861b58380C840144C55628203aE2fA9',
    # 'value':web3.to_wei('0.03', 'wei'),
    #  'value':30000000000000000,
     'value':0,
    'nonce': nonce
    }) 
private_key = "67e12ada4f7470595e3f50101efb993db79a6bd391b2a9281660e34b88362c96" 

# Sign the transaction
signed_txn = web3.eth.account.sign_transaction(transaction, private_key=private_key)

# Send the signed transaction
tx_hash = web3.eth.send_raw_transaction(signed_txn.rawTransaction)

# Wait for the transaction to be mined
receipt = web3.eth.wait_for_transaction_receipt(tx_hash)
print(type(tx_hash))
# Print the transaction receipt
print(f"Transaction successful. Transaction hash: {tx_hash.hex()}")
print(f"Gas used: {receipt['gasUsed']}")
    

# # dwarf hub glimpse tower settle lab limb cause wrap wave inhale trumpet
