#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex coutMutex;
std::mutex ATCMutex;
std::mutex trafficPatternMutex;

bool ATCSleeping = true;
int aircraftInPattern = 0;

void airplane(int number) {
    // Request to land
    {
        std::lock_guard<std::mutex> lock(ATCMutex);
        if (ATCSleeping) {
            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::cout << "Airplane " << number << " is waking up the ATC." << std::endl;
            ATCSleeping = false;
        }
        if (aircraftInPattern < 3) {
            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::cout << "Airplane " << number << " is requesting to land." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate ATC response time
            std::cout << "Airplane " << number << " is cleared to land." << std::endl;
            aircraftInPattern++;
        } else {
            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::cout << "Airplane " << number << " needs to divert to another airport." << std::endl;
            return;
        }
    }
    
    // Land
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate landing
    
    // Remove from traffic pattern
    aircraftInPattern--;
    if (aircraftInPattern == 0) {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Runway clear." << std::endl;
    }
    
    // Fall asleep if no more airplanes in traffic pattern
    {
        std::lock_guard<std::mutex> lock(ATCMutex);
        if (aircraftInPattern == 0) {
            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::cout << "ATC is falling asleep." << std::endl;
            ATCSleeping = true;
        }
    }
}

int main() {
    std::vector<std::thread> aircraftThreads;
    
    for (int i = 1; i <= 10; ++i) {
        aircraftThreads.emplace_back(airplane, i);
    }
    
    for (auto& thread : aircraftThreads) {
        thread.join();
    }
    
    return 0;
}
