# Smart Oilfield 

## Project Overview:
The project aims to develop a robust and secure system for monitoring and controlling oilfield operations using IoT (Internet of Things) and blockchain technology. It integrates a smart contract on the blockchain for secure and transparent data transactions, a frontend built with Next.js (a React framework) for user interaction, and a Node.js backend for additional services.

## System Design Diagram:
<center>
<img src="images\architecture.png" alt="" > 
</center>

## Components:
#### IoT devices:
- sensors that collect data from oilfield as temperature sensors.
- actuators to perform action at any machine in oilfiled
- gateway
    - our broker that run localy, and connect with all sensors and acuators.
    - web3 server that listen to blockchain to get data
#### Smart Contract (Solidity):
- Purpose: To record IoT sensor data (like machine temperature, speed, running time, oil pressure, and temperature) and control commands (on/off) securely on the blockchain.
- Features: Functions to log sensor data, change control states, and emit events for new sensor data and state changes.
#### Frontend (Next.js):
- Setting up the Next.js project, creating React components, and implementing state management.
- Connecting the frontend to the smart contract using ethers.js or web3.js for data fetching and transaction sending.

#### Backend (Node.js):
- Creating a Node.js project, setting up an express server, and implementing required API endpoints.
- Ensuring secure and efficient interaction between the backend, frontend, and blockchain.


## At this repo you will find first component [IoT devices] for athor Components ->  [link](https://www.youtube.com/playlist?list=PLT7V65iweHPHmZhDeHxaFKk1YfSPd9cn9)




