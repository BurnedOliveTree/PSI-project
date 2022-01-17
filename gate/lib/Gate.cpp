#include "Gate.h"
#include <iostream>

Gate::Gate(std::string ip, int pt, int nsv){
    ipAdress = "127.0.0.1";
    port = 8000;
    nServers = 4;
    sensorI = new SocketUDP(ipAdress, port,true);
    sensorGate = new Host(sensorI);
    for(int i =0; i<4; i++){
        serwerI.push_back(new SocketTCP(ipAdress, port+1+i,true));
        serwerGate.push_back(new Host(serwerI[i]));
    }
}

Gate::~Gate(){
    delete sensorI;
    delete sensorGate;
    for(int i =0; i<4; i++){
        delete serwerI[i];
        delete serwerGate[i];
    }
}
