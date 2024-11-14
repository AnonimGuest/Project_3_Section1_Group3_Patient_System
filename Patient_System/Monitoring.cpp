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

    cout << "\nAdjust the bed position." << endl;
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

BedTemperatureMonitor::BedTemperatureMonitor() {}

void BedTemperatureMonitor::loadThresholdData(const string& filePath) {
    ifstream file("Bed_Temperature.csv");
    if (!file) {
        cerr << "Error opening Bed Temperature data file: " << filePath << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header line
    int count = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        ThresholdDataBedTemp thresholdBedTemp;
        string ageGroup, disease, normalTemperature, minimumTemperature, maximumTemperature;

        getline(iss, ageGroup, ',');
        getline(iss, disease, ',');
        getline(iss, normalTemperature, ',');
        getline(iss, minimumTemperature, ',');
        getline(iss, maximumTemperature, ',');

        thresholdBedTemp.ageGroup = stoi(ageGroup);
        thresholdBedTemp.disease = disease;
        thresholdBedTemp.normalTemperature = stof(normalTemperature);
        thresholdBedTemp.minimumTemperature = stof(minimumTemperature);
        thresholdBedTemp.maximumTemperature = stof(maximumTemperature);

        thresholds.push_back(thresholdBedTemp);

    }
    file.close();
    cout << "Threshold data loaded successfully. " << endl;
}


void BedTemperatureMonitor::loadPatientData(const string& filePath) {
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
        string id, roomNumber, age, disease, temperature;
        string unused; // For any extra fields

        // Parse fields according to the expected structure
        getline(iss, id, ',');
        getline(iss, roomNumber, ',');
        getline(iss, age, ',');

        //skip gender column
        getline(iss, unused, ',');

        getline(iss, disease, ',');
        // skip weight and currentPressure column
        getline(iss, unused, ',');
        getline(iss, unused, ',');

        getline(iss, temperature, ',');

        // Direct conversion without exception handling
        if (!id.empty()) patient.id = stoi(id);
        if (!roomNumber.empty()) patient.roomNumber = stoi(roomNumber);
        if (!age.empty()) patient.age = stoi(age);
        patient.disease = disease; // Assume gender is a string and valid
        if (!temperature.empty()) patient.temperature = stof(temperature);
       

        // Add patient data to the vector
        patients.push_back(patient);
    }

    cout << "Patient data loaded successfully." << endl;
    file.close();
}


void BedTemperatureMonitor::monitorRandomPatientData() {
    if (patients.empty()) {
        cerr << "No patient data available to monitor." << endl;
        return;
    }

    // Seed for random number generation
    srand(static_cast<unsigned int>(time(0)));

    // Select a random patient
    int randomIndex = rand() % patients.size();
    const PatientData& randomPatient = patients[randomIndex];

    cout << "Monitoring bed temperature for Patient ID " << randomPatient.id
        << " in Room " << randomPatient.roomNumber << "..." << endl;

    bool matchedThreshold = false;

    // Iterate through the threshold data to find a match
    for (const auto& thresholdBedTemp : thresholds) {
        if (randomPatient.age == thresholdBedTemp.ageGroup &&
            randomPatient.disease == thresholdBedTemp.disease) {

            matchedThreshold = true; // Patient's data matches threshold criteria
           // cout << "  - Checking temperature for Patient ID " << randomPatient.id << "..." << endl;
            //cout << "    Current Temperature: " << randomPatient.temperature << "°C" << endl;
            //cout << "    Normal Temperature: " << thresholdBedTemp.normalTemperature << "desgree Celsius" << endl;
            //cout << "    Minimum Temperature: " << thresholdBedTemp.minimumTemperature << "degree Celsius" << endl;
            //cout << "    Maximum Temperature: " << thresholdBedTemp.maximumTemperature << " degree Celsius" << endl;


            if (randomPatient.temperature < thresholdBedTemp.minimumTemperature) {
                cout << " ALERT: Patient ID " << randomPatient.id << " has low temperature ("
                    << randomPatient.temperature << " degree Celsius). Action required." << endl;
                sendAlert(randomPatient, thresholdBedTemp);
                break;
            }
            else if (randomPatient.temperature > thresholdBedTemp.maximumTemperature) {
                cout << "ALERT: Patient ID " << randomPatient.id << " has high temperature ("
                    << randomPatient.temperature << " degree Celsius). Action required." << endl;
                sendAlert(randomPatient, thresholdBedTemp);
                break;
            }
            else {
                // If the temperature is within the safe range, but not exactly normal
                cout << "Patient ID " << randomPatient.id << " in Room " << randomPatient.roomNumber
                    << " has a body temperature within acceptable limits (" << randomPatient.temperature << "degree Celsius)." << endl;
            }
        }
    }

    if (!matchedThreshold) {
        cout << "No matching threshold found for Patient ID " << randomPatient.id << "." << endl;
    }
}

void BedTemperatureMonitor::sendAlert(const PatientData& patient, const ThresholdDataBedTemp& threshold) {
    
    cout << "Normal Range: " << threshold.minimumTemperature << " degree Celsius - "
        << threshold.maximumTemperature << "degree Celsius" << endl;

    BedTemperatureController tempController;
    int choice;

    cout << "\nAdjust the bed temperature." << endl;
    cout << "1. Increase temperature\n2. Decrease temperature\n3. Skip adjustment\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        tempController.adjustTemperature(TemperatureAdjustment::Increase);
    }
    else if (choice == 2) {
        tempController.adjustTemperature(TemperatureAdjustment::Decrease);
    }
    else {
        cout << "No changes made to bed temperature." << endl;
    }
}

OxygenSaturationMonitoringDevice::OxygenSaturationMonitoringDevice() {
}
void OxygenSaturationMonitoringDevice::loadPatientData(const string& filePath) {
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
        string id, roomNumber, oxygenSaturation;
        string unused; // For any extra fields

        // Parse fields according to the expected structure
        getline(iss, id, ',');
        getline(iss, roomNumber, ',');

        // Skip the medical condition field
        getline(iss, unused, ',');
        getline(iss, unused, ',');
        getline(iss, unused, ',');
        getline(iss, unused, ',');
        getline(iss, unused, ',');
        getline(iss, unused, ',');
        getline(iss, unused, ',');

        // Continue parsing the necessary numeric fields
        getline(iss, oxygenSaturation, ',');

        // Direct conversion without exception handling
        if (!id.empty()) patient.id = stoi(id);
        if (!roomNumber.empty()) patient.roomNumber = stoi(roomNumber);
        if (!oxygenSaturation.empty()) patient.oxygenSaturation = stoi(oxygenSaturation);

        // Add patient data to the vector
        patients.push_back(patient);
    }

    cout << "Patient data loaded successfully." << endl;
    file.close();
}

void OxygenSaturationMonitoringDevice::monitorPatientData() {
    if (patients.empty()) {
        std::cerr << "No patient data loaded." << std::endl;
        return;
    }

    srand(static_cast<unsigned int>(time(0)));

    // Select a random patient
    int randomIndex = rand() % patients.size();
    const PatientData& randomPatient = patients[randomIndex];

    cout << "Monitoring bed temperature for Patient ID " << randomPatient.id
        << " in Room " << randomPatient.roomNumber << "..." << endl;

    if (randomPatient.oxygenSaturation < oxygenSaturationLowerThreshold) {
        sendAlert(randomPatient.id, randomPatient.roomNumber, randomPatient.oxygenSaturation, "Below");
    }
    else if (randomPatient.oxygenSaturation > oxygenSaturationUpperThreshold) {
        sendAlert(randomPatient.id, randomPatient.roomNumber, randomPatient.oxygenSaturation, "Above");
    }
    else {
        // If the temperature is within the safe range, but not exactly normal
        cout << "Patient ID " << randomPatient.id << " in Room " << randomPatient.roomNumber
            << " has a oxygen Saturation within acceptable limits" << endl;
    }
}

// Send alert if oxygen saturation is outside the threshold range
void OxygenSaturationMonitoringDevice::sendAlert(int patientId, int roomNumber, int oxygenSaturation, const string& message) {
    cout << "ALERT: Patient ID " << patientId << " has " << message << " threshold oxygen saturation!\n"
        << "Oxygen Saturation: " << oxygenSaturation << "% (Threshold range: "
        << oxygenSaturationLowerThreshold << "% - " << oxygenSaturationUpperThreshold << "%)\n" << endl;

    OxygenSaturationController oxygenController;
    int choice;

    cout << "\nAdjust the oxygen flow." << endl;
    cout << "1. Start oxygen flow\n2. Stop oxygen flow\n3. Skip adjustment\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        oxygenController.adjustOxygenFlow(true);  // Start the oxygen flow
    }
    else if (choice == 2) {
        oxygenController.adjustOxygenFlow(false); // Stop the oxygen flow
    }
    else {
        cout << "No changes made to oxygen flow." << endl;
    }
}

GlucoseLevelMonitor::GlucoseLevelMonitor(){}

void GlucoseLevelMonitor::loadPatientData(const string& filePath) {
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
        string id, roomNumber, glucoseLevel;
        string unused; // For any extra fields

        // Parse fields according to the expected structure
        getline(iss, id, ',');
        getline(iss, roomNumber, ',');

        // Skip the medical condition field
        getline(iss, unused, ',');
        getline(iss, unused, ',');
        getline(iss, unused, ',');
        getline(iss, unused, ',');
        getline(iss, unused, ',');
        getline(iss, unused, ',');
        getline(iss, unused, ',');
        getline(iss, unused, ',');

        // Continue parsing the necessary numeric fields
        getline(iss, glucoseLevel, ',');

        // Direct conversion without exception handling
        if (!id.empty()) patient.id = stoi(id);
        if (!roomNumber.empty()) patient.roomNumber = stoi(roomNumber);
        if (!glucoseLevel.empty()) patient.glucoseLevel = stoi(glucoseLevel);

        // Add patient data to the vector
        patients.push_back(patient);
    }

    cout << "Patient data loaded successfully." << endl;
    file.close();
}

void GlucoseLevelMonitor::monitorPatientData() {
    if (patients.empty()) {
        std::cerr << "No patient data loaded." << std::endl;
        return;
    }

    srand(static_cast<unsigned int>(time(0)));

    // Select a random patient
    int randomIndex = rand() % patients.size();
    const PatientData& randomPatient = patients[randomIndex];

    cout << "Monitoring bed temperature for Patient ID " << randomPatient.id
        << " in Room " << randomPatient.roomNumber << "..." << endl;

    if (randomPatient.glucoseLevel < glucoseLevelLowerThreshold) {
        sendAlert(randomPatient.id, randomPatient.roomNumber, randomPatient.glucoseLevel, "Below");
    }
    else if (randomPatient.glucoseLevel > glucoseLevelUpperThreshold) {
        sendAlert(randomPatient.id, randomPatient.roomNumber, randomPatient.glucoseLevel, "Above");
    }
    else {
        // If the temperature is within the safe range, but not exactly normal
        cout << "Patient ID " << randomPatient.id << " in Room " << randomPatient.roomNumber
            << " has a oxygen Saturation within acceptable limits" << endl;
    }
}

// Send alert if oxygen saturation is outside the threshold range
void GlucoseLevelMonitor::sendAlert(int patientId, int roomNumber, int glucoseLevel, const string& message) {
    cout << "ALERT: Patient ID " << patientId << " has " << message << " threshold glucose level!\n"
        << "Glucose Level: " << glucoseLevel << "% (Threshold range: "
        << glucoseLevelLowerThreshold << "% - " << glucoseLevelUpperThreshold << "%)\n" << endl;

    GlucoseLevelController glucoseController;
    int choice;

    cout << "\nAdjust the Glucose Flow." << endl;
    cout << "1. Start glucose flow\n2. Stop glucose flow\n3. Skip adjustment\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        glucoseController.adjustGlucoseFlow(true);  // Start the oxygen flow
    }
    else if (choice == 2) {
        glucoseController.adjustGlucoseFlow(false); // Stop the oxygen flow
    }
    else {
        cout << "No changes made to glucose flow." << endl;
    }
}

