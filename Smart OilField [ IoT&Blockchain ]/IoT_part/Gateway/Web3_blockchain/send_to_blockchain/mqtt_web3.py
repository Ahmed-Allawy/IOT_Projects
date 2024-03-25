import paho.mqtt.client as mqtt
import json
import time
from web3 import Web3

ulrRPC = 'https://eth-sepolia.g.alchemy.com/v2/u8_uLJJIlQkZqdD_S69kowsov-pFQ_V4'
contractABI = json.loads('[{"inputs":[],"name":"OilField__NotAdmin","type":"error"},{"inputs":[],"name":"OilField__NotOwner","type":"error"},{"anonymous":false,"inputs":[{"indexed":true,"internalType":"address","name":"owner","type":"address"},{"indexed":false,"internalType":"string","name":"data","type":"string"}],"name":"appData","type":"event"},{"inputs":[{"internalType":"address","name":"_user","type":"address"}],"name":"addPerson","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"string","name":"data","type":"string"}],"name":"storeAppData","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"string","name":"data","type":"string"}],"name":"storeIoTData","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"uint256","name":"","type":"uint256"}],"name":"users","outputs":[{"internalType":"address","name":"","type":"address"}],"stateMutability":"view","type":"function"}]')
contractAddress = '0xd0ae9F331d306dA48E7119028413771b0F36FdC1'
public_key = '0x90437f445861b58380C840144C55628203aE2fA9'
private_key = "67e12ada4f7470595e3f50101efb993db79a6bd391b2a9281660e34b88362c96" 

id = 'ahmed@Allawy_2023'
client_name = id + 'mqtt_to_web3'
devices_topic = id + '/#'

mqtt_client = mqtt.Client(client_name)
mqtt_client.connect('127.0.0.1')
print('connected with broker')
mqtt_client.loop_start()

def sendtoBlockchain(data):
    web3 = Web3(Web3.HTTPProvider(ulrRPC))
    print(f"Is client connected with blocktain?: {web3.is_connected()}")
    if web3.is_connected()==True:
        print('connected with blockchain')

        contract = web3.eth.contract(address=contractAddress, abi=contractABI)
        
        # dataFromBlock = contract.functions.retrieveStr().call()
        # print(f"last data:{dataFromBlock}")
        
        nonce = web3.eth.get_transaction_count(public_key)
        print(f"nonce: {nonce}")
        gasprice =  web3.eth._gas_price()
        print(f"Gas price: {gasprice}")
        
        transaction = contract.functions.storeAppData(data).build_transaction({
        'gas': 100000,
        'gasPrice': gasprice,
        'from': public_key,
        # 'value':web3.to_wei('0', 'wei'),
        'value':0,
        'nonce': nonce
        }) 

        # Sign the transaction
        signed_txn = web3.eth.account.sign_transaction(transaction, private_key=private_key)

        # Send the signed transaction
        tx_hash = web3.eth.send_raw_transaction(signed_txn.rawTransaction)

        # Wait for the transaction to be mined
        receipt = web3.eth.wait_for_transaction_receipt(tx_hash)

        # Print the transaction receipt
        print(f"Transaction successful. Transaction hash: {tx_hash.hex()}")
        print(f"Gas used: {receipt['gasUsed']}")

def call_back(client, userdata, message):
    payload = json.loads(message.payload.decode())
    print("Topic is:", message.topic)
    print("Message received:", payload)
    # send data to blockchain with web3
    data = json.dumps({"topic":message.topic,"payload":message.payload.decode()})
    sendtoBlockchain(data)

mqtt_client.subscribe(devices_topic)
mqtt_client.on_message = call_back

while True:
    time.sleep(5)