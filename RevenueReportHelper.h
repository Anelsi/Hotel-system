// File: RevenueReportHelper.h
#pragma once

#include <iostream>
#include <fstream>
#include <string>

/// Функция, която позволява на потребителя да прегледа съдържанието
/// на файла "revenue_report.txt". Ако файлът липсва или не може да се отвори,
/// извежда подходящо съобщение за грешка.
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
