
#pragma once

#include <iostream>
#include <fstream>
#include <string>

inline void displayRevenueReportFromFile() {
    std::ifstream inFile("revenue_report.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: cannot open file for reading: revenue_report.txt\n";
        return;
    }

    std::cout << "=== Contents of revenue_report.txt ===\n";
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << '\n';
    }

    inFile.close();
}
