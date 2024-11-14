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
    float temperature;
    string disease;
    int respiratoryRate;
    int oxygenSaturation;
    int glucoseLevel;
};

struct ThresholdData {
    int age;
    string gender;
    float weight;
    float pressure;
    float thresholdPressure;
};

/*struct PatientDataBedTemp {
    int id;
    int age;
    int roomNumber;
    float temperature;
    string disease;

};*/

struct ThresholdDataBedTemp {
    int ageGroup;
    string disease;
    float normalTemperature;
    float minimumTemperature;
    float maximumTemperature;
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

class BedTemperatureMonitor {
private:
    vector<ThresholdDataBedTemp> thresholds;
    vector<PatientData> patients;

public:
    BedTemperatureMonitor();

    void loadThresholdData(const string& filePath);
    void loadPatientData(const string& filePath);
    void monitorRandomPatientData();
    void sendAlert(const PatientData& patient, const ThresholdDataBedTemp& threshold);
};

class OxygenSaturationMonitoringDevice {
public:
     OxygenSaturationMonitoringDevice();
    void loadPatientData(const string& filePath);
    void monitorPatientData();
    void sendAlert(int patientId, int roomNumber, int oxygenSaturation, const std::string& message);
    
  // std::vector<std::tuple<int, int, int>> patientData; // (PatientID, RespiratoryRate, OxygenSaturation)
    
private:
    vector<PatientData> patients;
    static const int oxygenSaturationLowerThreshold = 90; // Lower threshold value
    static const int oxygenSaturationUpperThreshold = 95; // Upper threshold value
    
};

class GlucoseLevelMonitor {
public:
    GlucoseLevelMonitor();
    void loadPatientData(const string& filePath);
    void monitorPatientData();
    void sendAlert(int patientId, int roomNumber, int glucoseLevel , const std::string& message);

private:
    vector<PatientData> patients;
    static const int glucoseLevelLowerThreshold = 85; // Lower threshold value
    static const int glucoseLevelUpperThreshold = 100; // Upper threshold value

};

