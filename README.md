# SafeSpaces - Hackathon 2024 St. Gallen - Team Bitbaumeister


## Table of Contents

-    Introduction
-    Hacker
-    Contribution

## Introduction

SafeSpaces is a practical solution for emergency situations which assists in locating and tracking individuals in need of assistance. Built on the Cisco Spaces API, it leverages Wi-Fi-based device location technology to maximize responsiveness. This powerful technology can help reduce human error and save lives in emergency situations. It is particularly targeted towards companies that are already using Cisco Spaces, offering them an easy, effective, and cost-efficient addition to their safety plan.

## Hacker
- Pendi
- Meierlohr
- Hörter
- Huber

## Structure
### Cisco_STARTHACK24
Contains all files neccessary to access and use the Cisco Firehose API

### SafeSpacesApp
Frontend: Contains the UI written in Swift and the client side of the system. The clients can call an emergency (in one of 3 categories, Fire, Medical or Hazard) which is communicated to the server.
When the server communicates back with location data, the client will (depending on the type of emergency) throw a notification to alert the user. The user then has the option to (depending on the type of emergency) get led the way to the nearest exit (in case of fire) or get led to the emergency location (in case of a medical emergency and a person in need of help).

### SafeSpacesCPPServer
Backend: Contains the CPP server that pulls data from the Firehose API, processes it and logs it into a database.The server also analyzes it on request from the mobile App. The clients on the app are connected to the server and when an emergy call is sent from a client, the server fetches the clients positions via IP or MAC address, to communicate location data of the emergency and type of emergency to all clients in the network.

### SafeSpacesPythonServer
Does the exact same thing as the CPP server but in Python.


Contributions, issues, and feature requests are welcome! Feel free to check issues page. Please follow the contribution guidelines when making contributions.
