#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

class BedPositioningController {
public:
    enum BedPosition { Supine, Fowler };

    BedPositioningController();
    void changeBedPosition(BedPosition position);
    void logPositionChange(BedPosition position);
    static string getPositionName(BedPosition position);

private:
    string logFilePath = "BedPositionLog.txt";
};