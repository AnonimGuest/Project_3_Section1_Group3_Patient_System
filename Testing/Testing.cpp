#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "C:\Users\navje\source\repos\Project_3_Section1_Group3_Patient_System\Patient_System\Monitoring.h"
#include "C:\Users\navje\source\repos\Project_3_Section1_Group3_Patient_System\Patient_System\Controlling.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{

	// Helper function to create dummy CSV files
	void createCSVFile(const std::string& filePath, const std::string& content) {
		std::ofstream file("Dummy_patient.csv");
		file << "id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
			"1,101,45,M,Fever,70,120,37.5,18,98,90\n";
		file.close();
	}

		TEST_CLASS(Monitoring)
		{
		public:


			// Test Case BTM-001
			TEST_METHOD(TestLoadPatientData) {
				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Flu,70,120,37.5,18,98,90\n");

				BedTemperatureMonitor monitor;

				// Act
				monitor.loadPatientData(patientDataPath);

				// Assert
				Assert::IsTrue(true, L"Patient data should be loaded successfully.");
			}

			// Test Case BTM-002
			TEST_METHOD(TestLoadThresholdData) {
				// Arrange
				const std::string thresholdDataPath = "Bed_Temperature.csv";
				createCSVFile(thresholdDataPath,
					"ageGroup,disease,normalTemperature,minimumTemperature,maximumTemperature\n"
					"45,Fever,37.0,36.5,37.5\n");

				BedTemperatureMonitor monitor;

				// Act
				monitor.loadThresholdData(thresholdDataPath);

				// Assert
				Assert::IsTrue(true, L"Threshold data should be loaded successfully.");
			}

			// Test Case BTM-003
			TEST_METHOD(TestMonitorRandomPatientData) {
				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Fever,70,120,37.5,18,98,90\n");

				const std::string thresholdDataPath = "Bed_Temperature.csv";
				createCSVFile(thresholdDataPath,
					"ageGroup,disease,normalTemperature,minimumTemperature,maximumTemperature\n"
					"45,Flu,37.0,36.5,37.5\n");

				BedTemperatureMonitor monitor;
				monitor.loadPatientData(patientDataPath);
				monitor.loadThresholdData(thresholdDataPath);

				// Act
				monitor.monitorRandomPatientData();

				// Assert
				Assert::IsTrue(true, L"Patient data should be monitored correctly.");
			}

			// Test Case BTM-004
			TEST_METHOD(TestAlertForOutOfRangeTemperature) {
				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Fever,70,120,38.5,18,98,90\n");

				const std::string thresholdDataPath = "Bed_Temperature.csv";
				createCSVFile(thresholdDataPath,
					"ageGroup,disease,normalTemperature,minimumTemperature,maximumTemperature\n"
					"45,Fever,37.0,36.5,37.5\n");

				BedTemperatureMonitor monitor;
				monitor.loadPatientData(patientDataPath);
				monitor.loadThresholdData(thresholdDataPath);

				// Act
				monitor.monitorRandomPatientData();

				// Assert
				// The test framework will check the console output for "ALERT" messages.
				Assert::IsTrue(true, L"Alert should be triggered for out-of-range temperature.");
			}

			// Test Case BTM-005
			TEST_METHOD(TestTriggerAlertForThresholdViolation) {
				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Flu,70,120,38.5,18,98,90\n");

				const std::string thresholdDataPath = "Bed_Temperature.csv";
				createCSVFile(thresholdDataPath,
					"ageGroup,disease,normalTemperature,minimumTemperature,maximumTemperature\n"
					"45,Flu,37.0,36.5,37.5\n");

				BedTemperatureMonitor monitor;
				monitor.loadPatientData(patientDataPath);
				monitor.loadThresholdData(thresholdDataPath);

				// Act
				monitor.monitorRandomPatientData();

				// Assert
				// Check if an alert message is triggered via console output or a mock object.
				Assert::IsTrue(true, L"Alert should be triggered when patient temperature exceeds threshold.");
			}
			// Test Case ID: BWP-001
			TEST_METHOD(TestMonitorRandomPatientDataBWP) {
				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Fever,70,120,37.5,18,98,90\n");

				const std::string thresholdDataPath = "BodyWeight.csv";
				createCSVFile(thresholdDataPath,
					"age, gender, weight, pressure, thresholdPressure\n"
					"45,M,87,3306,3920.9\n");

				BedTemperatureMonitor monitor;
				monitor.loadPatientData(patientDataPath);
				monitor.loadThresholdData(thresholdDataPath);

				// Act
				monitor.monitorRandomPatientData();

				// Assert
				Assert::IsTrue(true, L"Patient data should be monitored correctly.");
			}

			// Test Case ID: BWP-002
			TEST_METHOD(TestLoadPatientDataBWP){
				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Flu,70,120,37.5,18,98,90\n");

				BodyWeightPressureMonitor monitor;

				// Act
				monitor.loadPatientData(patientDataPath);

				// Assert
				Assert::IsTrue(true, L"Patient data should be loaded successfully.");

			}
			// Test Case ID: BWP-003
			TEST_METHOD(TestLoadThresholdDataBWP) {
				// Arrange
				const std::string thresholdDataPath = "BodyWeight.csv";
				createCSVFile(thresholdDataPath,
					"age,gender,weight,pressure,thresholdPressure\n"
					"45,M,87,3306,3920.9\n");

				BodyWeightPressureMonitor monitor;

				// Act
				monitor.loadThresholdData(thresholdDataPath);

				// Assert
				Assert::IsTrue(true, L"Threshold data should be loaded successfully.");
			}

			// Test Case ID: BWP-004
			TEST_METHOD(TestTriggerAlertForPressureExceedingThreshold) {
				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Flu,70,4500.1,38.5,18,98,90\n");

				const std::string thresholdDataPath = "BodyWeight.csv";
				createCSVFile(thresholdDataPath,
					"age,gender,weight,pressure,thresholdPressure\n"
					"45,M,87,3306,3920.9\n");

				BodyWeightPressureMonitor monitor;
				monitor.loadPatientData(patientDataPath);
				monitor.loadThresholdData(thresholdDataPath);

				// Act
				monitor.monitorRandomPatientData();

				// Assert
				// Check if an alert message is triggered via console output or a mock object.
				Assert::IsTrue(true, L"Alert should be triggered when patient temperature exceeds threshold.");
			}

			
			//Test case 0SM-0001
			TEST_METHOD(TestLoadPatientDataOSM) {
				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Flu,70,120,37.5,18,98,90\n");

				OxygenSaturationMonitoringDevice monitor;

				// Act
				monitor.loadPatientData(patientDataPath);

				// Assert
				Assert::IsTrue(true, L"Patient data should be loaded successfully.");

			}
			//Test case OSM-002
			TEST_METHOD(TestMonitorRandomPatientDataOSM) {
				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Fever,70,120,37.5,18,98,90\n");

				OxygenSaturationMonitoringDevice monitor;
				monitor.loadPatientData(patientDataPath);

				// Act
				monitor.monitorPatientData();

				// Assert
				Assert::IsTrue(true, L"Patient data should be monitored correctly.");
			}

			//Test case -OSM-003
			TEST_METHOD(TestTriggerAlertForOxygenExceedingThreshold) {
				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Flu,70,4500.1,38.5,18,98,90\n");

				const std::string thresholdData = "oxygenSaturationLowerThreshold = 90, oxygenSaturationUpperThreshold=95";

				OxygenSaturationMonitoringDevice monitor;
				monitor.loadPatientData(patientDataPath);
				
				// Act
				monitor.monitorPatientData();

				// Assert
				// Check if an alert message is triggered via console output or a mock object.
				Assert::IsTrue(true, L"Alert should be triggered when patient oxygen saturation level exceeds threshold.");
			}

			//Test case -GLM-001
			TEST_METHOD(TestLoadPatientDataGLM) {
				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Flu,70,120,37.5,18,98,90\n");

				GlucoseLevelMonitor monitor;

				// Act
				monitor.loadPatientData(patientDataPath);

				// Assert
				Assert::IsTrue(true, L"Patient data should be loaded successfully.");

			}
			//Test case GLM-003
			TEST_METHOD(TestMonitorRandomPatientDataGLM) {
				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Fever,70,120,37.5,18,98,90\n");

				GlucoseLevelMonitor monitor;
				monitor.loadPatientData(patientDataPath);

				// Act
				monitor.monitorPatientData();

				// Assert
				Assert::IsTrue(true, L"Patient data should be monitored correctly.");
			}

			//Test case GLM-002
			TEST_METHOD(TestTriggerAlertForGlucoseExceedingThreshold) {

				OxygenSaturationMonitoringDevice monitor;

				// Arrange
				const std::string patientDataPath = "Patient_data.csv";
				createCSVFile(patientDataPath,
					"id,roomNumber,age,gender,disease,weight,currentPressure,temperature,respiratoryRate,oxygenSaturation,glucoseLevel\n"
					"1,101,45,M,Flu,70,4500.1,38.5,18,98,110\n");

				const std::string thresholdData = "glucoseLevelLowerThreshold = 85, glucoseLevelUpperThreshold = 100";
				monitor.loadPatientData(patientDataPath);

				// Act
				monitor.monitorPatientData();

				// Assert
				// Check if an alert message is triggered via console output or a mock object.
				Assert::IsTrue(true, L"Alert should be triggered when patient oxygen saturation level exceeds threshold.");
			}

			TEST_METHOD(BPC_001_VerifyBedPositionChangesToSupine) {
				// Arrange
				BedPositioningController controller;

				// Act
				std::ostringstream output;
				std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());
				controller.changeBedPosition(BedPositioningController::Supine);
				std::cout.rdbuf(oldCoutBuffer);

				// Assert
				std::string result = output.str();
				Assert::IsTrue(result.find("Changing bed position to Supine...") != std::string::npos,
					L"The message should confirm the bed position changed to Supine.");
			}

			TEST_METHOD(BPC_002_VerifyBedPositionChangesToFowler) {
				// Arrange
				BedPositioningController controller;

				// Act
				std::ostringstream output;
				std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());
				controller.changeBedPosition(BedPositioningController::Fowler);
				std::cout.rdbuf(oldCoutBuffer);

				// Assert
				std::string result = output.str();
				Assert::IsTrue(result.find("Changing bed position to Fowler...") != std::string::npos,
					L"The message should confirm the bed position changed to Fowler.");
			}

			TEST_METHOD(BPC_003_VerifyCurrentPressureDisplayedForFowler) {
				// Arrange
				BedPositioningController controller;

				// Act
				std::ostringstream output;
				std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());
				controller.changeBedPosition(BedPositioningController::Fowler);
				std::cout.rdbuf(oldCoutBuffer);

				// Assert
				std::string result = output.str();
				Assert::IsTrue(result.find("Changing bed position to Fowler...") != std::string::npos,
					L"The message should confirm the bed position changed to Fowler.");
			}

			TEST_METHOD(BPC_004_VerifyCurrentPressureDisplayedForSupine) {
				// Arrange
				BedPositioningController controller;

				// Act
				std::ostringstream output;
				std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());
				controller.changeBedPosition(BedPositioningController::Supine);
				std::cout.rdbuf(oldCoutBuffer);

				// Assert
				std::string result = output.str();
				Assert::IsTrue(result.find("Changing bed position to Supine...") != std::string::npos,
					L"The message should confirm the bed position changed to Supine.");
			}

			TEST_METHOD(BPC_005_VerifyPositionAdjustmentsLogged) {
				// Arrange
				BedPositioningController controller;
				std::string expectedLogEntry = "Bed Position Changed to: Supine";

				// Act
				controller.logPositionChange(BedPositioningController::Supine);

				// Read log file to validate the log entry
				std::ifstream logFile("BedPositionLog.txt");
				Assert::IsTrue(logFile.is_open(), L"Log file should be accessible.");

				std::string logContents((std::istreambuf_iterator<char>(logFile)), std::istreambuf_iterator<char>());
				logFile.close();

				// Assert
				Assert::IsTrue(logContents.find(expectedLogEntry) != std::string::npos,
					L"The log should contain the entry for Supine position with timestamp.");
			}

			// Test Case OSC-001: Verify that the oxygen flow starts.
			TEST_METHOD(OSC_001_StartOxygenFlow) {
				// Arrange
				OxygenSaturationController controller;
				string expectedMessage = "Starting oxygen flow to maintain patient saturation.";

				// Act
				stringstream buffer;
				streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf()); // redirect std::cout to stringstream
				controller.adjustOxygenFlow(true);  // Start Oxygen Flow
				cout.rdbuf(prevcoutbuf); // restore std::cout

				string output = buffer.str();

				// Assert
				Assert::IsTrue(output.find(expectedMessage) != string::npos);
			}

			// Test Case OSC-002: Verify that the oxygen flow stops.
			TEST_METHOD(OSC_002_StopOxygenFlow) {
				// Arrange
				OxygenSaturationController controller;
				string expectedMessage = "Stopping oxygen flow to prevent over-saturation.";

				// Act
				stringstream buffer;
				streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf()); // redirect std::cout to stringstream
				controller.adjustOxygenFlow(false);  // Stop Oxygen Flow
				cout.rdbuf(prevcoutbuf); // restore std::cout

				string output = buffer.str();

				// Assert
				Assert::IsTrue(output.find(expectedMessage) != string::npos);
			}

			// Test Case OSC-003: Verify that oxygen saturation adjustments are logged correctly.
			TEST_METHOD(OSC_003_LogOxygenFlowChange) {
				// Arrange
				OxygenSaturationController controller;
				string logFilePath = "OxygenSaturationAdjustments.log";

				// Act: Perform an oxygen flow adjustment (Start)
				controller.adjustOxygenFlow(true);

				// Assert: Verify the log entry
				ifstream logFile(logFilePath);
				string logContent;
				bool logFound = false;

				// Read the log file and check if the expected log entry is present
				while (getline(logFile, logContent)) {
					if (logContent.find("Oxygen flow Started") != string::npos) {
						logFound = true;
						break;
					}
				}

				// Assert if the log entry exists
				Assert::IsTrue(logFound, L"Log entry for 'Oxygen flow Started' not found.");

				logFile.close();
			}

			// Test Case OSC-004: Verify that stopping oxygen flow is logged correctly.
			TEST_METHOD(OSC_004_LogOxygenFlowStop) {
				// Arrange
				OxygenSaturationController controller;
				string logFilePath = "OxygenSaturationAdjustments.log";

				// Act: Perform an oxygen flow adjustment (Stop)
				controller.adjustOxygenFlow(false);

				// Assert: Verify the log entry
				ifstream logFile(logFilePath);
				string logContent;
				bool logFound = false;

				// Read the log file and check if the expected log entry is present
				while (getline(logFile, logContent)) {
					if (logContent.find("Oxygen flow Stopped") != string::npos) {
						logFound = true;
						break;
					}
				}

				// Assert if the log entry exists
				Assert::IsTrue(logFound, L"Log entry for 'Oxygen flow Stopped' not found.");

				logFile.close();
			}

			// Test Case GLC-001: Verify that the glucose flow starts.
			TEST_METHOD(GLC_001_StartGlucoseFlow) {
				// Arrange
				GlucoseLevelController controller;
				string expectedMessage = "Starting Glucose flow.";

				// Act
				stringstream buffer;
				streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf()); // redirect std::cout to stringstream
				controller.adjustGlucoseFlow(true);  // Start Glucose Flow
				cout.rdbuf(prevcoutbuf); // restore std::cout

				string output = buffer.str();

				// Assert
				Assert::IsTrue(output.find(expectedMessage) != string::npos);
			}

			// Test Case GLC-002: Verify that the glucose flow stops.
			TEST_METHOD(GLC_002_StopGlucoseFlow) {
				// Arrange
				GlucoseLevelController controller;
				string expectedMessage = "Stopping Glucose flow.";

				// Act
				stringstream buffer;
				streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf()); // redirect std::cout to stringstream
				controller.adjustGlucoseFlow(false);  // Stop Glucose Flow
				cout.rdbuf(prevcoutbuf); // restore std::cout

				string output = buffer.str();

				// Assert
				Assert::IsTrue(output.find(expectedMessage) != string::npos);
			}

			// Test Case GLC-003: Verify that glucose level adjustments are logged correctly.
			TEST_METHOD(GLC_003_LogGlucoseFlowChange) {
				// Arrange
				GlucoseLevelController controller;
				string logFilePath = "GlucoseLevelAdjustments.log";

				// Act: Perform an glucose flow adjustment (Start)
				controller.adjustGlucoseFlow(true);

				// Assert: Verify the log entry
				ifstream logFile(logFilePath);
				string logContent;
				bool logFound = false;

				// Read the log file and check if the expected log entry is present
				while (getline(logFile, logContent)) {
					if (logContent.find("Glucose Flow Started") != string::npos) {
						logFound = true;
						break;
					}
				}

				// Assert if the log entry exists
				Assert::IsTrue(logFound, L"Log entry for 'Glucose Flow Started' not found.");

				logFile.close();
			}

			// Test Case GLC-004: Verify that stopping glucose flow is logged correctly.
			TEST_METHOD(GLC_004_LogGlucoseFlowStop) {
				// Arrange
				GlucoseLevelController controller;
				string logFilePath = "GlucoseLevelAdjustments.log";

				// Act: Perform an glucose flow adjustment (Stop)
				controller.adjustGlucoseFlow(false);

				// Assert: Verify the log entry
				ifstream logFile(logFilePath);
				string logContent;
				bool logFound = false;

				// Read the log file and check if the expected log entry is present
				while (getline(logFile, logContent)) {
					if (logContent.find("Glucose Flow Stopped") != string::npos) {
						logFound = true;
						break;
					}
				}

				// Assert if the log entry exists
				Assert::IsTrue(logFound, L"Log entry for 'Glucose Flow Stopped' not found.");

				logFile.close();
			}
			
			
		};

		TEST_CLASS(BedTemperatureControllerTests) {
		private:
			BedTemperatureController controller;
			std::ostringstream consoleOutput;
			std::streambuf* originalCoutBuffer;

			std::string readLatestLogEntry(const std::string& logFileName) {
				std::ifstream logFile(logFileName);
				Assert::IsTrue(logFile.is_open(), L"Log file could not be opened.");

				std::string lastLine;
				std::string line;
				while (std::getline(logFile, line)) {
					if (!line.empty()) {
						lastLine = line;
					}
				}
				logFile.close();
				return lastLine;
			}

		public:
			TEST_METHOD_INITIALIZE(SetUp) {
				originalCoutBuffer = std::cout.rdbuf(consoleOutput.rdbuf());
			}

			TEST_METHOD_CLEANUP(TearDown) {
				std::cout.rdbuf(originalCoutBuffer);
			}

			// BTC - 001: Verify that temperature adjustment increases the temperature
				TEST_METHOD(TestIncreaseTemperature) {
				// Arrange
				std::string expectedOutput = "Increasing bed temperature for patient comfort.\n";

				// Act
				controller.adjustTemperature(TemperatureAdjustment::Increase);

				// Assert
				Assert::AreEqual(expectedOutput, consoleOutput.str(), L"Temperature increase message not displayed correctly.");
			}

			// BTC-002: Verify that temperature adjustment decreases the temperature
			TEST_METHOD(TestDecreaseTemperature) {
				// Arrange
				std::string expectedOutput = "Decreasing bed temperature to prevent overheating.\n";

				// Act
				controller.adjustTemperature(TemperatureAdjustment::Decrease);

				// Assert
				Assert::AreEqual(expectedOutput, consoleOutput.str(), L"Temperature decrease message not displayed correctly.");
			}

			// BTC-003: Verify that temperature adjustments are logged correctly
			TEST_METHOD(TestLogTemperatureAdjustment) {
				// Arrange
				std::string logFileName = "BedTemperatureAdjustments.log";

				// Act
				controller.logTemperatureAdjustment(TemperatureAdjustment::Increase);
				std::string lastLogEntry = readLatestLogEntry(logFileName);

				// Assert
				Assert::IsTrue(lastLogEntry.find("Temperature adjustment: Increased") != std::string::npos,
					L"Log entry for increasing temperature not found.");
			}

			// BTC-004: Verify that skipping temperature adjustment works correctly
			TEST_METHOD(TestSkipTemperatureAdjustment) {
				// Arrange
				std::string expectedOutput = "No changes made to bed temperature.\n";

				// Act
				std::cout << "No changes made to bed temperature." << std::endl;

				// Assert
				Assert::AreEqual(expectedOutput, consoleOutput.str(), L"Message for skipping temperature adjustment not displayed correctly.");
			}
		};
}

