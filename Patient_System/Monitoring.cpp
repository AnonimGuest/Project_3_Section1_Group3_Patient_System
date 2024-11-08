#include "Monitoring.h"
#include <fstream>
#include <iostream>
#include <sstream>

BedTemperatureMonitor::BedTemperatureMonitor() {}

void BedTemperatureMonitor::loadThresholdData(const string& filePath) {
    ifstream file("Patient_data.txt");
    if (!file) {
        cerr << "Error opening data file." << endl;
        return;
    }

    string line;
    getline(file, line);  // Skip header
    while (getline(file, line)) {
        istringstream iss(line);
        TemperatureThresholdData threshold;
        string ageGroup, disease, normalTemp, minTemp, maxTemp;

        getline(iss, ageGroup, ',');
        getline(iss, disease, ',');
        getline(iss, normalTemp, ',');
        getline(iss, minTemp, ',');
        getline(iss, maxTemp, ',');

        threshold.ageGroup = ageGroup;
        threshold.disease = disease;
        threshold.normalTemperature = stof(normalTemp);
        threshold.minTemperature = stof(minTemp);
        threshold.maxTemperature = stof(maxTemp);

        thresholds.push_back(threshold);
    }
    file.close();
}

void BedTemperatureMonitor::monitorPatientData() {

    if (patients.empty()) {
        cout << "No patient data available." << endl;
        return;
    }

    for (const auto& patient : patients) {
        // Add debugging statement inside the loop to ensure it's iterating over patients
        cout << "Monitoring Patient ID: " << patient.id << ", Age: " << patient.age << endl;
        cout << "Patient ID: " << patient.id << endl;
        cout << "Room Number: " << patient.roomNumber << endl;
        cout << "Age: " << patient.age << endl;
        cout << "Disease: " << patient.disease << endl;
        cout << "Gender: " << patient.gender << endl;
        cout << "Weight: " << patient.weight << endl;
        cout << "Temperature: " << patient.currentTemperature << endl;
        cout << "Pressure: " << patient.currentPressure << endl;

        bool alertSent = false;
        for (const auto& threshold : thresholds) {
            if (patient.age >= stoi(threshold.ageGroup.substr(0, threshold.ageGroup.find('-'))) &&
                patient.age <= stoi(threshold.ageGroup.substr(threshold.ageGroup.find('-') + 1)) &&
                patient.disease == threshold.disease) {
                if (patient.currentTemperature > threshold.maxTemperature) {
                    sendAlert(patient, "bed temperature exceeds");
                    alertSent = true;
                    break;
                }
                else if (patient.currentTemperature < threshold.minTemperature) {
                    sendAlert(patient, "bed temperature is low");
                    alertSent = true;
                    break;
                }
            }
        }
        if (!alertSent) {
            cout << "Patient ID " << patient.id << " temperature is within safe limits." << endl;
        }
    }
}

void BedTemperatureMonitor::sendAlert(const PatientData& patient, const string& alertType) {
    cout << "ALERT: Patient ID " << patient.id << " " << alertType << "!" << endl;
}


// BodyWeightPressureMonitor Implementation

BodyWeightPressureMonitor::BodyWeightPressureMonitor() {}

void BodyWeightPressureMonitor::loadThresholdData(const string& filePath) {
    ifstream file("Patient_data.txt");
    if (!file) {
        cerr << "Error opening data file." << endl;
        return;
    }

    string line;
    getline(file, line);  // Skip header
    while (getline(file, line)) {
        istringstream iss(line);
        BodyWeightThresholdData threshold;
        string age, gender, weight, pressure, thresholdPressure;

        getline(iss, age, ',');
        getline(iss, gender, ',');
        getline(iss, weight, ',');
        getline(iss, pressure, ',');
        getline(iss, thresholdPressure, ',');

        threshold.age = stoi(age);
        threshold.gender = gender;
        threshold.weight = stof(weight);
        threshold.pressure = stof(pressure);
        threshold.thresholdPressure = stof(thresholdPressure);

        thresholds.push_back(threshold);
    }
    file.close();
}

void BodyWeightPressureMonitor::monitorPatientData() {
    for (const auto& patient : patients) {
        bool thresholdExceeded = false;
        for (const auto& threshold : thresholds) {
            if (patient.age == threshold.age &&
                patient.gender == threshold.gender &&
                patient.weight == threshold.weight) {

                //Debug output for comparison
                cout << "Comparing Patient ID " << patient.id << " in Room " << patient.roomNumber << endl;
                cout << "  - Patient's Current Pressure: " << patient.currentPressure << endl;
                cout << "  - Patient's Weight: " << patient.weight << endl;
                cout << "  - Threshold Pressure: " << threshold.thresholdPressure << endl;

                if (patient.currentPressure > threshold.thresholdPressure) {
                    //thresholdExceeded = true;
                    sendAlert(patient);
                    break;
                }
                else {
                    cout << "Patient ID " << patient.id << "in Room" << patient.roomNumber << " pressure is within safe limits." << endl;
                }
            }
        }
    }
}

void BodyWeightPressureMonitor::sendAlert(const PatientData& patient) {
    cout << "ALERT: Patient ID " << patient.id << " exceeds the pressure threshold!" << endl;
}

