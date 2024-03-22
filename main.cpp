#include <iostream>
#include <string>
#include <vector>

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

// Factory class for creating sensors
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

    return 0;
}