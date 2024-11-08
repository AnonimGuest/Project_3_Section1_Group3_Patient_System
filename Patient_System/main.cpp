#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Monitoring.h"
#include "PatientDataHandler.h"

using namespace std;

int main() {
    vector<PatientData> patients; // Shared patient data across all monitoring systems
    vector<TemperatureThresholdData> temperatureThresholds;
    vector<BodyWeightThresholdData> weightThresholds;

    BodyWeightPressureMonitor BWmonitor;
    BedTemperatureMonitor BTmonitor;
   
    
    int choice;
    do {
        cout << "--- Monitoring System ---" << endl;
        cout << "1. Bed Temperature Monitor" << endl;
        cout << "2. Body Weight & Pressure Monitor" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int bedChoice;
            // Inner loop for Bed Temperature Monitor
            do {
                cout << "\n--- Bed Temperature Monitoring ---" << endl;
                cout << "1. Enter Patient Data" << endl;
                cout << "2. Load Patient Data" << endl;
                cout << "3. Monitor Patient Data" << endl;
                cout << "4. Load Threshold Data" << endl;
                cout << "5. Return to Main Menu" << endl;
                cout << "Enter your choice: ";
                cin >> bedChoice;

                switch (bedChoice) {
                case 1:
                    enterPatientData(patients);  // Enter patient data and save it to file
                    break;
                case 2:
                    readPatientData("Patient_data.txt", patients); // Load patient data
                    cout << "Patient data loaded. Total patients: " << patients.size() << endl;
                    break;
                case 3:
                    BWmonitor.monitorPatientData();  // Monitor loaded patient data
                    break;
                case 4:
                    BWmonitor.loadThresholdData("BodyWeight.csv"); // Load Threshold Data
                    break;
                case 5:
                    cout << "Returning to main menu." << endl;
                    break;
                default:
                    cout << "Invalid choice, please try again." << endl;
                    break;
                }
            } while (bedChoice != 5);  // Repeat this loop until the user chooses to return to the main menu
            break;
        }
        case 2: {
            int weightChoice;
            // Inner loop for Body Weight & Pressure Monitor
            do {
                cout << "\n--- Body Weight & Pressure Monitoring ---" << endl;
                cout << "1. Enter Patient Data" << endl;
                cout << "2. Load Patient Data" << endl;
                cout << "3. Monitor Patient Data" << endl;
                cout << "4. Load Threshold Data" << endl;
                cout << "5. Return to Main Menu" << endl;
                cout << "Enter your choice: ";
                cin >> weightChoice;

                switch (weightChoice) {
                case 1:
                    enterPatientData(patients); // Function to enter patient data
                    break;
                case 2:
                    readPatientData("Patient_data.txt", patients); // Load patient data
                    cout << "Patient data loaded. Total patients: " << patients.size() << endl;
                    break;
                case 3:
                    BTmonitor.monitorPatientData(); // Monitor Patient Data
                    break;
                case 4:
                    BTmonitor.loadThresholdData("Bed_Temperature.csv"); // Load Threshold Data
                    break;
                case 5:
                    cout << "Returning to main menu." << endl;
                    break;
                default:
                    cout << "Invalid choice, please try again." << endl;
                    break;
                }
            } while (weightChoice != 5);  // Repeat this loop until the user chooses to return to the main menu
            break;
        }
        case 3:
            cout << "Exiting the system." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    } while (choice != 3);  // Repeat the main menu loop until the user chooses to exit

    return 0;
}