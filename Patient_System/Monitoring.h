#pragma once
#include <string>
#include <vector>
#include "PatientDataHandler.h"  // Include for shared patient data management

using namespace std;

struct TemperatureThresholdData {
    string ageGroup;
    string disease;
    float normalTemperature;
    float minTemperature;
    float maxTemperature;
};

struct BodyWeightThresholdData {
    int age;
    string gender;
    float weight;
    float pressure;
    float thresholdPressure;
};

class BedTemperatureMonitor {
private:
    vector<TemperatureThresholdData> thresholds;
    vector<PatientData> patients;

public:
    BedTemperatureMonitor();
    void loadThresholdData(const string& filePath);
    void monitorPatientData();
    void sendAlert(const PatientData& patient, const string& alertType);
    void run();  // Run method to handle device-specific logic
};

class BodyWeightPressureMonitor {
private:
    vector<BodyWeightThresholdData> thresholds;
    vector<PatientData> patients;

public:
    BodyWeightPressureMonitor();
    void loadThresholdData(const string& filePath);
    void monitorPatientData();
    void sendAlert(const PatientData& patient);
    void run();  // Run method to handle device-specific logic
};