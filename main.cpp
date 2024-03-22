#include <iostream>
#include <string>
#include <vector>

// Question 1
class Sensor 
{
    public:
        virtual void gatherData() = 0; // Pure virtual function
        virtual void processData() = 0; // Pure virtual function
        virtual ~Sensor() {} // Virtual destructor
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

class TemperatureSensor : public Sensor 
{
    public:
        void gatherData() override 
        {
            // Simulate data gathering process for temperature sensor
            std::cout << "Gathering data from Temperature Sensor." << std::endl;
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

// Question 2
class Robot 
{
    public:
    int number;
    int timeGrab;
    int timeCompletetask;
    int totaltime;

    Robot(int _number, int _timeGrab, int _timeCompletetask)
        : number(_number), timeGrab(_timeGrab), timeCompletetask(_timeCompletetask), totaltime(0) {}

    void performTask()
    {
        std::cout << "Robot " << number << " is collectingn data." << std::endl;
        std::cout << "Robot " << number << " acquired tools and starts performing a task." << std::endl;

        totaltime += timeGrab + timeCompletetask + timeGrab; // timeGrab twice for grabbing and returning tools

        std::cout << "Robot " << number << " finished the task and returning the tools." << std::endl;
    }
};

class Arena
{
    private:
    std::vector<Robot> robots;
    int numRobots;

    public:
    Arena( int _numRobots, std::vector<int> timeGrab, std::vector<int> timeCompletetask)
    : numRobots(_numRobots)
    {
        if (timeGrab.size() != _numRobots || timeCompletetask.size() != _numRobots)
        { 
            std::cerr << "Error: Mismatch in number of robots and provided times." << std::endl;
            return;
        }

        for (int i = 0; i < _numRobots; ++i)
        { robots.emplace_back(i + 1, timeGrab[i], timeCompletetask[i]); }
    }

    int simulateTasks() 
    {
        int totalTime = 0;
        for (int i = 0; i < numRobots; ++i) { robots[i].performTask(); }
        return totalTime;
    }

    int getTotalTime() const
    {
        int totalTime = 0;
        for (int i = 0; i < numRobots; ++i)
        { totalTime += robots[i].totaltime;}

        return totalTime;
    }
};
int main() 
{
    /*
    TemperatureSensor tempSensor;
    PressureSensor pressureSensor;
    PositionSensor positionSensor;

    tempSensor.gatherData();
    tempSensor.processData();

    pressureSensor.gatherData();
    pressureSensor.processData();

    positionSensor.gatherData();
    positionSensor.processData();

    Sensor* tempSensor = SensorFactory::createSensor("Temperature");
    if (tempSensor) {
        tempSensor->gatherData();
        tempSensor->processData();
        delete tempSensor;
    }

    Sensor* pressureSensor = SensorFactory::createSensor("Pressure");
    if (pressureSensor) {
        pressureSensor->gatherData();
        pressureSensor->processData();
        delete pressureSensor;
    }

    Sensor* positionSensor = SensorFactory::createSensor("Position");
    if (positionSensor) {
        positionSensor->gatherData();
        positionSensor->processData();
        delete pressureSensor;
    }

    return 0;
    */

   AerospaceControlSystem ctrlSys;

    // Adding sensors
    ctrlSys.addSensor(SensorFactory::createSensor("Temperature"));
    ctrlSys.addSensor(SensorFactory::createSensor("Pressure"));
    ctrlSys.addSensor(SensorFactory::createSensor("Position"));

    // Monitoring and adjusting
    ctrlSys.monitorAndAdjust();


    // Question 2
    std::cout << "\n \n \nQUESTION 2: \n" << std::endl;
    std::vector<int> timeToGrab = {1, 1, 1, 1, 1}; // Time for each robot to grab tools (1 second)
    std::vector<int> timeToCompleteTask = {5, 5, 5, 5, 5}; // Time for each robot to complete task (5 seconds)

    Arena arena(5, timeToGrab, timeToCompleteTask);
    arena.simulateTasks();
    int totalTime = arena.getTotalTime();
    std::cout << "duration: " << totalTime << " seconds." << std::endl;

    return 0;
}