#pragma once
#include <string>
#include <vector>

using namespace std;

struct PatientData {
    int id;
    int roomNumber;
    int age;
    string gender;
    float weight;
    float currentPressure;
};

struct ThresholdData {
    int age;
    string gender;
    float weight;
    float pressure;
    float thresholdPressure;
};

class BodyWeightPressureMonitor {
private:
    vector<ThresholdData> thresholds;
    vector<PatientData> patients;

public:
    BodyWeightPressureMonitor();

    void loadThresholdData(const string& filePath);
    void loadPatientData(const string& filePath);
    void monitorRandomPatientData();
    void sendAlert(const PatientData& patient);
};
