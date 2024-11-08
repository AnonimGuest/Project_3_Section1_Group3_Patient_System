#include "PatientDataHandler.h"
#include <iostream>

void enterPatientData(vector<PatientData>& patients) {
    PatientData patient;
    cout << "Enter Patient ID: ";
    cin >> patient.id;
    cout << "Enter Room Number: ";
    cin >> patient.roomNumber;
    cout << "Enter Age: ";
    cin >> patient.age;
    cout << "Enter Disease: ";
    cin >> patient.disease;
    cout << "Enter Gender: ";
    cin >> patient.gender;
    cout << "Enter Weight: ";
    cin >> patient.weight;
    cout << "Enter Temperature: ";
    cin >> patient.currentTemperature;
    cout << "Enter Pressure: ";
    cin >> patient.currentPressure;

    ofstream file("patient_data.txt", ios::app);
    if (file) {
        file << patient.id << "," << patient.roomNumber << "," << patient.age << "," <<patient.disease << ","
            << patient.gender << "," << patient.weight << "," << patient.currentTemperature<< "," << patient.currentPressure << endl;
        file.close();
    }
    else {
        cerr << "Error saving patient data to file." << endl;
    }

    patients.push_back(patient);
}

void readPatientData(const string& filePath, vector<PatientData>& patients) {
    ifstream file("Patient_data.txt");
    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        istringstream iss(line);
        PatientData patient;
        string id, room, age, disease, gender, weight, temperature, pressure;

        getline(iss, id, ',');
        getline(iss, room, ',');
        getline(iss, age, ',');
        getline(iss, disease, ',');
        getline(iss, gender, ',');
        getline(iss, weight, ',');
        getline(iss, temperature, ',');
        getline(iss, pressure, ',');

        patient.id = stoi(id);
        patient.roomNumber = stoi(room);
        patient.age = stoi(age);
        patient.disease = disease;
        patient.gender = gender;
        patient.weight = stof(weight);
        patient.currentTemperature = stof(temperature);
        patient.currentPressure = stof(pressure);

        patients.push_back(patient);
    }
}