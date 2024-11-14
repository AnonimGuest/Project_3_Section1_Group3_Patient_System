#include "Monitoring.h"
#include <iostream>

using namespace std;

int main() {
    BodyWeightPressureMonitor monitor;
    BedTemperatureMonitor monitor1;
    OxygenSaturationMonitoringDevice monitor2;
    GlucoseLevelMonitor monitor3;

    monitor.loadThresholdData("BodyWeight.csv"); // Load threshold data from BodyWeight.csv
    monitor.loadPatientData("Patient_data.csv"); // Load patient data from Patient_data.csv
    monitor1.loadThresholdData("Bed_Temperature.csv");
    monitor1.loadPatientData("Patient_data.csv");
    monitor2.loadPatientData("Patient_data.csv");
    monitor3.loadPatientData("Patient_data.csv");

    int choice;
    do {
        cout << "\n--- Body Weight Pressure Monitoring System ---" << endl;
        cout << "1. Monitor Patient's Pressure on Bed" << endl;
        cout << "2. Monitor Bed Temperature" << endl;
        cout << "3. Monitor Oxygen Saturation" << endl;
        cout << "4. Monitor Glucose Level" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            monitor.monitorRandomPatientData();  // Monitor random patient data
            break;
        case 2:
            monitor1.monitorRandomPatientData();
            break;
        case 3:
            monitor2.monitorPatientData();
            break;
        case 4:
            monitor3.monitorPatientData();
            break;
        case 5:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}