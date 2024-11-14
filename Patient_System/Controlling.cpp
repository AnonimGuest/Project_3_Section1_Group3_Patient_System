#define _CRT_SECURE_NO_WARNINGS
#include "Controlling.h"
#include "Monitoring.h"
#include <ctime>
#include <iostream>

using namespace std;

BedPositioningController::BedPositioningController() {
    // Constructor can initialize additional settings if needed
}

void BedPositioningController::changeBedPosition(BedPosition position) {
    cout << "Changing bed position to " << getPositionName(position) << "..." << endl;

    // Log the change after adjusting the bed position
    logPositionChange(position);
}

void BedPositioningController::logPositionChange(BedPosition position) {
    // Open the log file in append mode
    ofstream logFile(logFilePath, ios_base::app);

    if (!logFile) {
        cerr << "Error opening log file: " << logFilePath << endl;
        return;
    }

    // Get current time
    time_t currentTime = time(nullptr);
    char* timeStr = ctime(&currentTime);
    timeStr[strlen(timeStr) - 1] = '\0';  // Remove newline character

    // Log the position change with a timestamp
    logFile << "Timestamp: " << timeStr
        << " | Bed Position Changed to: " << getPositionName(position) << endl;

    logFile.close();
}

string BedPositioningController::getPositionName(BedPosition position) {
    return (position == Supine) ? "Supine" : "Fowler";
}
void BedTemperatureController::adjustTemperature(TemperatureAdjustment adjustment) {
    if (adjustment == TemperatureAdjustment::Increase) {
        cout << "Increasing bed temperature for patient comfort." << endl;
    }
    else {
        cout << "Decreasing bed temperature to prevent overheating." << endl;
    }
    logTemperatureAdjustment(adjustment);
}

void BedTemperatureController::logTemperatureAdjustment(TemperatureAdjustment adjustment) {
    ofstream logFile("BedTemperatureAdjustments.log", ios::app);
    if (logFile.is_open()) {
        time_t now = time(nullptr);
        logFile << "Time: " << std::ctime(&now)
            << "Temperature adjustment: "
            << (adjustment == TemperatureAdjustment::Increase ? "Increased" : "Decreased")
            << "\n" << endl;
        logFile.close();
    }
    else {
        cerr << "Error: Unable to open log file for bed temperature adjustments." << endl;
    }
}

void OxygenSaturationController::adjustOxygenFlow(bool startFlow) {
    if (startFlow) {
        cout << "Starting oxygen flow to maintain patient saturation." << endl;
    }
    else {
        cout << "Stopping oxygen flow to prevent over-saturation." << endl;
    }
    logOxygenFlowChange(startFlow);
}

void OxygenSaturationController::logOxygenFlowChange(bool startFlow) {
    ofstream logFile("OxygenSaturationAdjustments.log", ios::app);
    if (logFile.is_open()) {
        time_t now = time(nullptr);
        logFile << "Time: " << ctime(&now)
            << "Oxygen flow " << (startFlow ? "Started" : "Stopped")
            << "\n" << endl;
        logFile.close();
    }
    else {
        cerr << "Error: Unable to open log file for oxygen saturation adjustments." << endl;
    }
}

void GlucoseLevelController::adjustGlucoseFlow(bool startFlow) {
    if (startFlow) {
        cout << "Starting Glucose flow." << endl;
    }
    else {
        cout << "Stopping Glucose flow." << endl;
    }
    logGlucoseFlowChange(startFlow);
}

void GlucoseLevelController::logGlucoseFlowChange(bool startFlow) {
    ofstream logFile("GlucoseLevelAdjustments.log", ios::app);
    if (logFile.is_open()) {
        time_t now = time(nullptr);
        logFile << "Time: " << ctime(&now)
            << "Glucose Flow " << (startFlow ? "Started" : "Stopped")
            << "\n" << endl;
        logFile.close();
    }
    else {
        cerr << "Error: Unable to open log file for glucose level adjustments." << endl;
    }
}