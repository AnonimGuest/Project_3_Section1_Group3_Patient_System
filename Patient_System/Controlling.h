#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

class BedPositioningController {
public:
    enum BedPosition { Supine, Fowler };

    BedPositioningController();
    void changeBedPosition(BedPosition position);
    void logPositionChange(BedPosition position);
    static string getPositionName(BedPosition position);

private:
    string logFilePath = "BedPositionLog.txt";
};

enum class TemperatureAdjustment {
    Increase,
    Decrease
};

class BedTemperatureController {
public:
    void adjustTemperature(TemperatureAdjustment adjustment);
    void logTemperatureAdjustment(TemperatureAdjustment adjustment);
    string readLatestLogEntry(const std::string& logFileName);
};

class OxygenSaturationController {
public:
    void adjustOxygenFlow(bool startFlow);  // true for start, false for stop
    void logOxygenFlowChange(bool startFlow);
};

class GlucoseLevelController {
public:
    void adjustGlucoseFlow(bool startFlow);  // true for start, false for stop
    void logGlucoseFlowChange(bool startFlow);
};