from web3 import Web3
from web3.providers.websocket import WebsocketProvider
import json

# Set up the connection to the WebSocket provider
websocket_url = "wss://eth-sepolia.g.alchemy.com/v2/u8_uLJJIlQkZqdD_S69kowsov-pFQ_V4"  # Replace with your WebSocket provider URL
web3 = Web3(WebsocketProvider(websocket_url))

# Load the contract ABI and address
contractABI = json.loads('[{"inputs":[],"name":"OilField__NotAdmin","type":"error"},{"inputs":[],"name":"OilField__NotOwner","type":"error"},{"anonymous":false,"inputs":[{"indexed":true,"internalType":"address","name":"owner","type":"address"},{"indexed":false,"internalType":"string","name":"data","type":"string"}],"name":"appData","type":"event"},{"inputs":[{"internalType":"address","name":"_user","type":"address"}],"name":"addPerson","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"string","name":"data","type":"string"}],"name":"storeAppData","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"string","name":"data","type":"string"}],"name":"storeIoTData","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"uint256","name":"","type":"uint256"}],"name":"users","outputs":[{"internalType":"address","name":"","type":"address"}],"stateMutability":"view","type":"function"}]')
contractAddress = '0xd0ae9F331d306dA48E7119028413771b0F36FdC1'

# Instantiate the contract
contract = web3.eth.contract(address=contractAddress, abi=contractABI)

print(web3.is_connected())

# Define the event to listen to
event_name = 'appData'
my_event = contract.events[event_name]

# Define a callback function for the event
def handle_event(event):
    # Extract relevant data from the event
    data = event.args
    # print(data)
    data_json = Web3.to_json(data)
    # data_json = json.dumps(data)
    # print(data_json)
    data_json = json.loads(data_json)
    print(data_json)
    temp = data_json['data']
    print(temp)

# Start listening for the event
event_filter = my_event.create_filter(fromBlock='latest')

while True:
    for event in event_filter.get_new_entries():
        handle_event(event)



# pragma solidity ^0.8.0;

# contract StringStorage {
#     string public storedString;

#     event StringUpdated(string updatedString);

#     function storeString(string memory newString) public {
#         storedString = newString;
#         emit StringUpdated(newString);
#     }
# }