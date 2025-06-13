//
//#include <iostream>
//#include "ReservationsManagement.h"
//#include "RevenueInfo.h"
//
//
//int main() {
//    try {
//       
//        ReservationsManagement resMgmt;
//
//        
//
//        
//        int phone1[EnumClasses::MAX_NUMBERS] = { 8,8,2,1,2,3,4,5,6,7 };
//        Guest guest1(
//            "Ivan Ivanov",          
//            "ivan@example.com",      
//            1,                       
//            phone1,                 
//            "Regular",               
//            0                       
//        );
//
//        int phone2[EnumClasses::MAX_NUMBERS] = { 8,8,7,6,5,4,3,2,1,0 };
//        Guest guest2(
//            "Maria Petrova",
//            "maria@example.com",
//            2,
//            phone2,
//            "Regular",
//            0
//        );
//
//       
//        Room room101(
//            101,
//            80.0,
//            EnumClasses::RoomType::Single,
//            EnumClasses::Status::Available,
//            nullptr
//        );
//
//        
//        Room room202(
//            202,
//            120.0,
//            EnumClasses::RoomType::Deluxe,
//            EnumClasses::Status::Available,
//            nullptr
//        );
//
//        
//        Date dateIn1(2025, 5, 10);
//        Date dateOut1(2025, 5, 13);  
//
//        Date dateIn2(2025, 5, 12);
//        Date dateOut2(2025, 5, 15);  
//
//        
//        resMgmt.addReservation(guest1, dateIn1, dateOut1, room101);
//        resMgmt.addReservation(guest2, dateIn2, dateOut2, room202);
//
//       
//        RevenueInfo revenue(resMgmt);
//
//        const char* reportFile = "revenue_report.txt";
//        revenue.saveReportToFile(reportFile);
//
//        std::cout << "The report is saved to a file.: " << reportFile << std::endl;
//
//        std::cout << "\n=== Contents of \"" << reportFile << "\" ===\n";
//        revenue.loadReportFromFile(reportFile);
//
//    }
//    catch (const std::exception& ex) {
//        std::cerr << "Error: " << ex.what() << std::endl;
//        return 1;
//    }
//
//    return 0;
//}
