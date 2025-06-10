//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
//#include "Room.h"
//#include "PricingStrategyFactory.h"   
//#include "EnumClasses.h"
//
//int main() {
//    
//    int nRooms = 0;
//    std::cout << "Enter number of rooms: ";
//    std::cin >> nRooms;
//
//    
//    std::vector<Room*> roomsList;
//    roomsList.reserve(nRooms);
//
//    for (int i = 0; i < nRooms; ++i) {
//        int roomNum;
//        double basePrice;
//        std::string typeStr, statusStr;
//        std::string strategyName, strategyParam;
//
//        
//        std::cin >> roomNum
//            >> basePrice
//            >> typeStr
//            >> statusStr
//            >> strategyName
//            >> strategyParam;
//
//       
//        Room* newRoom = new Room();
//
//        
//        newRoom->setRoomNum(roomNum);
//        newRoom->setBasePrice(basePrice);
//
//        
//        newRoom->setRoomType(typeStr.c_str());
//        newRoom->setStatus(statusStr.c_str());
//
//       
//        if (strategyName != "null") {
//            newRoom->setStrategyByName(strategyName.c_str(), strategyParam.c_str());
//        }
//        
//        roomsList.push_back(newRoom);
//    }
//
//    
//    std::ofstream outFile("rooms.txt");
//    if (!outFile) {
//        std::cerr << "Error: could not open 'rooms.txt' for writing.\n";
//        
//        for (Room* r : roomsList) {
//            delete r;
//        }
//        return 1;
//    }
//
//    
//    outFile << roomsList.size() << '\n';
//
//    
//    for (Room* r : roomsList) {
//        r->saveToFile(outFile);  
//    }
//
//    outFile.close();
//    std::cout << "Saved " << roomsList.size() << " rooms to 'rooms.txt'.\n";
//
//   
//    for (Room* r : roomsList) {
//        delete r;
//    }
//    roomsList.clear();
//
//    return 0;
//}
