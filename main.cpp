#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <memory>

// Question 1
class Sensor 
{
    public:
        virtual void gatherData() = 0; // Pure virtual function
        virtual void processData() = 0; // Pure virtual function
        virtual ~Sensor() {} // Virtual destructor
};

class TemperatureSensor : public Sensor 
{
    public:
        void gatherData() override 
        {
            // Simulate data gathering process for temperature sensor
            std::cout << "\nGathering data from Temperature Sensor." << std::endl;
        }

        void processData() override 
        {
            // Simulate data processing for temperature sensor
            std::cout << "Processing data from Temperature Sensor." << std::endl;
        }
};

class PressureSensor : public Sensor 
{
    public:
        void gatherData() override 
        {
            // Simulate data gathering process for pressure sensor
            std::cout << "Gathering data from Presure Sensor." << std::endl;
        }

        void processData() override 
        {
            // Simulate data processing for pressure sensor
            std::cout << "Processing data from Pressure Sensor" << std::endl;
        }
};

class PositionSensor : public Sensor
{
    public:
        void gatherData() override
        {
            // Simulate data gathering process for position sensor
            std::cout << "Gathering data from Position Sensor." << std::endl;
        }

        void processData() override
        {
            // Simulate data processing for position sensor
            std::cout << "Processing data from Position Sensor." << std::endl;
        }
};

class SensorFactory
{
    public:
    static Sensor* createSensor(const std::string& sensortype)
    {
        if (sensortype == "Temperature") { return new TemperatureSensor(); }
        else if (sensortype == "Pressure") { return new PressureSensor(); }
        else if (sensortype == "Position") { return new PositionSensor(); }
        else 
        { 
            std::cout << "Unknown sensor type: " << sensortype << std::endl;
            return nullptr;
        }
    }
};

class AerospaceControlSystem 
{
    private:
        std::vector<Sensor*> sensors;

    public:
        void addSensor(Sensor* sensor) {
            sensors.push_back(sensor);
        }

        void monitorAndAdjust() {
            for (Sensor* sensor : sensors) {
                sensor->gatherData();
                sensor->processData();
                std::cout << "Adjusting controls based on sensor data." << std::endl;
            }
        }
};

// Question 2 
/*
class Robot 
{
public:
    int number;
    int timeCompletetask;
    int totaltime;
    std::mutex* mutex0; 
    std::mutex* mutex1; 

    Robot(int _number, std::mutex &tool0, std::mutex &tool1) // include mutex 1,2 
        : number(_number), totaltime(0), mutex0(&tool0), mutex1(&tool1) {}

    void performTask()
    {
        // std::lock_guard<std::mutex> lock(*mutex); use std::lock
        std::lock(*mutex0, *mutex1);

        std::cout << "Robot " << number << " starts performing a task." << std::endl;
        totaltime += timeCompletetask;
        std::cout << "Robot " << number << " finished the task." << std::endl;

        // release locks
        mutex0->unlock();
        mutex1->unlock();
    }
};

class Arena
{
private:
    std::vector<std::mutex> tools;
    std::vector<std::thread> tasks;
    std::vector<Robot> robots;
    int numRobots;

public:
    Arena(int _numRobots)
        : tools(_numRobots), numRobots(_numRobots)
       
    {


        for (int i = 0; i < _numRobots; ++i)
        { 
            robots.emplace_back(i + 1, tools[i], tools[(i+1)%5]); 
        }
    }

    void simulateTasks() 
    {
        // create 5 mutex for tools. have robot constructor receive two mutex. create 5 strands
        // use sleep_for for time to grab tools/complete tasks
        std::vector<std::thread> threads;

        // Create threads for each robot to perform tasks simultaneously
        for (int i = 0; i < numRobots; ++i) {
            std::thread t(&Robot::performTask, std::ref(robots[i]));
            threads.push_back(t);
        }

        // Wait for all threads to finish
        for (auto& thread : threads) {
            thread.join();
        }
    }

    int getTotalTime() const
    {
        int totalTime = 0;
        for (const auto& robot : robots) {
            totalTime = std::max(totalTime, robot.totaltime);
        }
        return totalTime;
    }
};


// void PerformTask (int id) {
// int leftChannel = id;
// int rightChannel = (id + 1) % tools.size();
// if (leftChannel > rightChannel) std::swap( leftChannel, rightChannel)
// std::vector<std::mutex> tools;
// std::lock( tools[leftChannel]. tools[rightChannel]);
// std::lock_guard<std::mutex> leftLock ( tools[leftChannel], std::adopt_lock)
// std::lock_guard<std::mutex> rightLock ( tools[rightChannel], std::adopt_lock)
// std::cout << "Robot" << id<< "i s reaching and grabbing tools"
// }

*/

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

        std::cout << "Robot " << number << " is starting the process." << std::endl; // added
            
        std::lock(*mutex0, *mutex1);
        std::lock_guard<std::mutex> leftLock( *mutex0, std::adopt_lock );
        std::lock_guard<std::mutex> rightLock( *mutex1, std::adopt_lock );
        std::cout << "Robot " << number << " is reaching and grabbing the tools." << std::endl;
        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
        std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
        std::cout << "Robot " << number << " finished the task and returning the tools." << std::endl;

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
   std::cout << "\n \n \nQUESTION 1: \n" << std::endl;
   AerospaceControlSystem ctrlSys;

    // Adding sensors
    ctrlSys.addSensor(SensorFactory::createSensor("Temperature"));
    ctrlSys.addSensor(SensorFactory::createSensor("Pressure"));
    ctrlSys.addSensor(SensorFactory::createSensor("Position"));

    // Monitoring and adjusting
    ctrlSys.monitorAndAdjust();

    std::cout << "QUESTION 2: \n" << std::endl;

    int numRobots = 5;
    Arena arena(numRobots);
    
    // Simulate the tasks
    arena.simulateTasks();
    
    // Get the total time taken by all robots to finish their tasks
    int totalTime = arena.getTotalTime();
    std::cout << "Total time taken by all robots: " << totalTime << " seconds" << std::endl;
    
    return 0;
}