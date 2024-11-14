#include "Monitoring.h"
#include "Controlling.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>
#include <ctime>
#include <cmath> // For std::abs

using namespace std;

const float WEIGHT_TOLERANCE = 0.01;

BodyWeightPressureMonitor::BodyWeightPressureMonitor() {}

void BodyWeightPressureMonitor::loadThresholdData(const string& filePath) {
    ifstream file("BodyWeight.csv");
    if (!file) {
        cerr << "Error opening Body Weight and Pressure data file: " << filePath << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header line
    int count = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        ThresholdData threshold;
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
    cout << "Threshold data loaded successfully. " << endl;
}


void BodyWeightPressureMonitor::loadPatientData(const string& filePath) {
    ifstream file("Patient_data.csv");
    if (!file) {
        cerr << "Error opening patient data file: " << filePath << endl;
        return;
    }
    string line;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        istringstream iss(line);
        PatientData patient;
        string id, roomNumber, age, gender, weight, currentPressure;
        string unused; // For any extra fields

        // Parse fields according to the expected structure
        getline(iss, id, ',');
        getline(iss, roomNumber, ',');
        getline(iss, age, ',');
        getline(iss, gender, ',');

        // Skip the medical condition field
        getline(iss, unused, ',');

        // Continue parsing the necessary numeric fields
        getline(iss, weight, ',');
        getline(iss, currentPressure, ',');

        // Direct conversion without exception handling
        if (!id.empty()) patient.id = stoi(id);
        if (!roomNumber.empty()) patient.roomNumber = stoi(roomNumber);
        if (!age.empty()) patient.age = stoi(age);
        patient.gender = gender; // Assume gender is a string and valid
        if (!weight.empty()) patient.weight = stof(weight);
        if (!currentPressure.empty()) patient.currentPressure = stof(currentPressure);

        // Add patient data to the vector
        patients.push_back(patient);
    }

    cout << "Patient data loaded successfully." << endl;
    file.close();
}


void BodyWeightPressureMonitor::monitorRandomPatientData() {
    if (patients.empty()) {
        cerr << "No patient data available to monitor." << endl;
        return;
    }

    // Seed for random number generation
    srand(static_cast<unsigned int>(time(0)));

    // Select a random patient
    int randomIndex = rand() % patients.size();
    const PatientData& randomPatient = patients[randomIndex];

    cout << "Monitoring body pressure on bed for Patient ID " << randomPatient.id
        << " in Room " << randomPatient.roomNumber << "..." << endl;

    bool thresholdExceeded = false;
    bool matchedThreshold = false;

    for (const auto& threshold : thresholds) {
        if (randomPatient.age == threshold.age &&
            randomPatient.gender == threshold.gender &&
            abs(randomPatient.weight - threshold.weight) < WEIGHT_TOLERANCE) {

            matchedThreshold = true; // Patient's data matches threshold criteria
            //cout << "  - Checking threshold for Patient ID " << randomPatient.id << "..." << endl;
            //cout << "    Current Pressure: " << randomPatient.currentPressure << " Pa" << endl;
            //cout << "    Threshold Pressure: " << threshold.thresholdPressure << " Pa" << endl;

            if (randomPatient.currentPressure > threshold.thresholdPressure) {
                sendAlert(randomPatient);
                thresholdExceeded = true;
                break;
            }
            else {
                cout << "    Patient ID " << randomPatient.id << " in Room " << randomPatient.roomNumber
                    << " is within safe limits." << endl;
            }
        }
    }

}

void BodyWeightPressureMonitor::sendAlert(const PatientData& patient) {
    cout << "ALERT: Patient ID " << patient.id << " in Room " << patient.roomNumber
        << " exceeds the pressure threshold with current pressure " << patient.currentPressure << "Pa" << endl;

    // Prompt caregiver to use bed positioning control
    BedPositioningController bedController;
    int choice;

    cout << "\nWould you like to adjust the bed position?" << endl;
    cout << "1. Supine\n2. Fowler\n3. Skip\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        bedController.changeBedPosition(BedPositioningController::Supine);
    }
    else if (choice == 2) {
        bedController.changeBedPosition(BedPositioningController::Fowler);
    }
    else {
        cout << "No changes made to bed position." << std::endl;
    }
}
