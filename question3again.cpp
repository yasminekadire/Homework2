#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono> // Include chrono for time measurements

std::mutex coutMutex;
std::mutex ATCMutex;

bool ATCSleeping = true;
int aircraftInPattern = 0;
bool redirected = false;
bool lastAirplaneLanded = false;

void airplane(int number) {
    // Request to land
    {
        std::unique_lock<std::mutex> lock(ATCMutex);
        if (ATCSleeping) {
            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::cout << "Airplane #" << number << " is establishing communication with the ATC." << std::endl;
            ATCSleeping = false;
        }
        if (aircraftInPattern >= 3 && !redirected) {
            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::cout << "Airplane #" << number << " requesting landing." << std::endl;
            std::cout << "Approach pattern full. Airplane #" << number << " redirected to another airport." << std::endl;
            redirected = true;
            return;
        }
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Airplane #" << number << " requesting landing." << std::endl;
        std::cout << "Airplane #" << number << " is cleared to land." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate landing
        aircraftInPattern++;
    }
    
    // Land
     std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate landing
    
    // Remove from traffic pattern
    {
        std::lock_guard<std::mutex> lock(ATCMutex);
        aircraftInPattern--;
        if (aircraftInPattern == 0) {
            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::cout << "Runway is now free." << std::endl;
            ATCSleeping = true;
            redirected = false;
        }
    }

    // Check if this is the last airplane to land at this airport
    if (number == 10) {
        lastAirplaneLanded = true;
    }
}

int main() {
    auto start = std::chrono::steady_clock::now(); // Start the timer
    
    std::vector<std::thread> aircraftThreads;
    
    for (int i = 1; i <= 10; ++i) {
        aircraftThreads.emplace_back(airplane, i);
    }

    // Join all threads
    for (auto& thread : aircraftThreads) {
        thread.join();
    }
    
    auto end = std::chrono::steady_clock::now(); // End the timer
    std::chrono::duration<double> elapsed_seconds = end - start; // Calculate the duration
    
    std::cout << "Program duration: " << elapsed_seconds.count() << " seconds." << std::endl;
    
    return 0;
}
