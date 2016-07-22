#!/bin/bash
g++ ./src/common.cpp ./src/vps_server.cpp -g -o ./bin/vps_server
g++ ./src/common.cpp ./src/lan_client.cpp -g -o ./bin/lan_client
g++ ./src/common.cpp ./src/pc_client.cpp -g -o ./bin/pc_client
g++ ./src/common.cpp ./src/user_client.cpp -g -o ./bin/user_client
