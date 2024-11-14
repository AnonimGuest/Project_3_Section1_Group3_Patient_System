#define _CRT_SECURE_NO_WARNINGS
#include "Controlling.h"
#include "Monitoring.h"
#include <ctime>
#include <iostream>

BedPositioningController::BedPositioningController() {
    // Constructor can initialize additional settings if needed
}

void BedPositioningController::changeBedPosition(BedPosition position) {
    std::cout << "Changing bed position to " << getPositionName(position) << "..." << std::endl;

    // Log the change after adjusting the bed position
    logPositionChange(position);
}

void BedPositioningController::logPositionChange(BedPosition position) {
    // Open the log file in append mode
    std::ofstream logFile(logFilePath, std::ios_base::app);

    if (!logFile) {
        std::cerr << "Error opening log file: " << logFilePath << std::endl;
        return;
    }

    // Get current time
    std::time_t currentTime = std::time(nullptr);
    char* timeStr = std::ctime(&currentTime);
    timeStr[std::strlen(timeStr) - 1] = '\0';  // Remove newline character

    // Log the position change with a timestamp
    logFile << "Timestamp: " << timeStr
        << " | Bed Position Changed to: " << getPositionName(position) << endl;

    logFile.close();
}

std::string BedPositioningController::getPositionName(BedPosition position) {
    return (position == Supine) ? "Supine" : "Fowler";
}
