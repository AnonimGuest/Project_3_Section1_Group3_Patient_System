#include "Monitoring.h"
#include <iostream>

using namespace std;

int main() {
    BodyWeightPressureMonitor monitor;

    monitor.loadThresholdData("BodyWeight.csv"); // Load threshold data from BodyWeight.csv
    monitor.loadPatientData("Patient_data.csv"); // Load patient data from Patient_data.csv

    int choice;
    do {
        cout << "\n--- Body Weight Pressure Monitoring System ---" << endl;
        cout << "1. Monitor Patient's Pressure on Bed" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            monitor.monitorRandomPatientData();  // Monitor random patient data
            break;
        case 2:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 2);

    return 0;
}