#include "lib/Gate.h"
#include "lib/Timer.h"
#include <iostream>
#include <array>
#include <atomic>
#include <memory>
#include <variant>
#include <thread>

int main() {
    std::atomic<bool> isProgramRunning = true;
    auto gate = Gate();
    auto timer = &Timer::getInstance();
    std::vector<char> raw;
    
    while (isProgramRunning) {
        raw = gate.sensorGate->ReceiveRaw(true);
        Utils::printVector(raw);
        auto [ph_raw, msg] = Utils::divideHeader(sizeof(PHeader), raw);
        auto [sh_raw, data] = Utils::divideHeader(sizeof(DocumentHeader), msg);
        Utils::printVector(data);
        Utils::printVector(ph_raw);
        Utils::printVector(sh_raw);
        auto sh = Utils::deserializeStruct<DocumentHeader>(sh_raw);
        auto ph = Utils::deserializeStruct<PHeader>(ph_raw);
        std::cout << sh.documentId << "\n";
        std::cout << unsigned(sh.documentType)<< "\n" ;
        std::cout <<unsigned(sh.type) << "\n";
    }
}