#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <memory>
std::mutex coutMutex; // Mutex to guard std::cout

class Robot
{
    public:
        int number;
        int timeCompletetask;
        int totaltime;
        std::mutex* mutex0; // tool 0
        std::mutex* mutex1; // tool 1
    
        Robot(int _number, std::mutex &tool0, std::mutex &tool1)
        : number(_number), totaltime(0), mutex0(&tool0), mutex1(&tool1) {}

    
    void performTask()
    {
        {
            std::lock_guard<std::mutex> lock(coutMutex); // Lock access to std::cout
            std::cout << "Airplane " << number << " is requesting to land." << std::endl; // added
        }
        
        std::lock(*mutex0, *mutex1);
        std::lock_guard<std::mutex> leftLock( *mutex0, std::adopt_lock );
        std::lock_guard<std::mutex> rightLock( *mutex1, std::adopt_lock );
        
        
        {
            std::lock_guard<std::mutex> lock(coutMutex); // Lock access to std::cout
            std::cout << "Airplane " << number << " cleared to land." << std::endl;
        }
        
        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
        std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
        
        {
            std::lock_guard<std::mutex> lock(coutMutex); // Lock access to std::cout
            std::cout << "Airplane " << number << " finished the task and returning the tools." << std::endl;
        }

    }
};

class Arena
{
    private:
        std::vector<std::mutex> tools;
        std::vector<std::thread> tasks;
        std::vector<Robot> robots;
        int numRobots;
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point endTime;
    
    public:
    Arena(int _numRobots)
    : tools(_numRobots), numRobots(_numRobots)
    {
        for (int i = 0; i < _numRobots; ++i)
            { robots.emplace_back(i + 1, tools[i], tools[(i+1)%5]); }
    }
    
    void simulateTasks()
    {
        // Record the start time
        startTime = std::chrono::steady_clock::now();
        
        // create 5 mutex for tools. have robot constructor receive two mutex. create 5 strands
        // use sleep_for for time to grab tools/complete tasks
        std::vector<std::thread> threads;
        // Create threads for each robot to perform tasks simultaneously
        for (int i = 0; i < numRobots; ++i) 
        { threads.push_back(std::thread(&Robot::performTask, std::ref(robots[i]))); }
        // Wait for all threads to finish
        for (auto& thread : threads) { thread.join(); }

        // Record the end time
        endTime = std::chrono::steady_clock::now();
    }
    
    int getTotalTime() const
    { 
        // Calculate the duration between start and end times
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        return duration.count(); // Return the total duration in seconds
    }
};
int main() 
{

    std::cout << "QUESTION 2: \n" << std::endl;

    int numRobots = 10;
    Arena arena(numRobots);
    
    // Simulate the tasks
    arena.simulateTasks();
    
    // Get the total time taken by all robots to finish their tasks
    int totalTime = arena.getTotalTime();
    std::cout << "Duration: " << totalTime << " seconds" << std::endl;
    
}