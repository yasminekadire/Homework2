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
    return 0;
}
