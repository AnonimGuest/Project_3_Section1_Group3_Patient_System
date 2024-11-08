#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct PatientData {
    int id;
    int roomNumber;
    int age;
    string disease;
    string gender;
    float weight;
    float currentTemperature;
    float currentPressure;
};

void enterPatientData(vector<PatientData>& patients);
void readPatientData(const string& filePath, vector<PatientData>& patients);