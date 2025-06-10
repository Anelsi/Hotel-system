//#include <iostream>
//#include <fstream>
//#include <string>
//#include "Guest.h"
//#include "Date.h"
//#include "Reservation.h"
//#include "Room.h"
//#include "EnumClasses.h"
//
//int main() {
//    // --- СЦЕНАРИЙ 1: Регистрация на чисто нов Guest ---
//    {
//        std::cout << "=== РЕГИСТРИРАЙ НОВ GUEST ===\n";
//        // 1) Въвеждаме информация за госта от конзолата:
//        std::string name, email, statusStr;
//        int guestNum;
//        int phoneDigits[EnumClasses::MAX_NUMBERS];
//
//        std::cout << "Име на гост: ";
//        std::getline(std::cin, name);
//
//        std::cout << "Email: ";
//        std::getline(std::cin, email);
//
//        std::cout << "Guest Num (положително цяло число): ";
//        std::cin >> guestNum;
//
//        std::cout << "Телефонни цифри (натиснете " << EnumClasses::MAX_NUMBERS
//            << " цифри, разделени със спейс, напр. 0 5 8 9 ...): ";
//        for (int i = 0; i < EnumClasses::MAX_NUMBERS; ++i) {
//            std::cin >> phoneDigits[i];
//        }
//
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//        std::cout << "Статус на госта (Gold / Platinium / Regular): ";
//        std::getline(std::cin, statusStr);
//
//        // 2) Създаваме обект Guest:
//        Guest newGuest(name.c_str(), email.c_str(), guestNum, phoneDigits, statusStr.c_str(), 0);
//
//        // 3) Записваме го във файл (binary)
//        std::ofstream fout("guests.bin", std::ios::binary | std::ios::app);
//        if (!fout) {
//            std::cerr << "Грешка: Не мога да отворя guests.bin за писане!\n";
//            return 1;
//        }
//        newGuest.saveToFile(fout);
//        fout.close();
//
//        std::cout << "\nУспешно регистрирахте гост: " << newGuest.getName()
//            << " (GuestNum = " << newGuest.getGuestNum() << ")\n\n";
//    }
//
//    // --- СЦЕНАРИЙ 2: Регистрация на нов Guest + Създаване на Reservation ---
//    {
//        std::cout << "=== РЕГИСТРИРАЙ НОВ GUEST И РЕЗЕРВАЦИЯ ===\n";
//        // 1) Отново въвеждаме информация за един Guest:
//        std::string name2, email2, status2;
//        int guestNum2;
//        int phoneDigits2[EnumClasses::MAX_NUMBERS];
//
//        std::cout << "Име на гост: ";
//        std::getline(std::cin, name2);
//
//        std::cout << "Email: ";
//        std::getline(std::cin, email2);
//
//        std::cout << "Guest Num (положително число): ";
//        std::cin >> guestNum2;
//
//        std::cout << "Телефонни цифри (натиснете " << EnumClasses::MAX_NUMBERS
//            << " цифри, напр. 0 4 7 9 ...): ";
//        for (int i = 0; i < EnumClasses::MAX_NUMBERS; ++i) {
//            std::cin >> phoneDigits2[i];
//        }
//
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//        std::cout << "Статус на госта (Gold / Platinium / Regular): ";
//        std::getline(std::cin, status2);
//
//        Guest guest2(name2.c_str(), email2.c_str(), guestNum2, phoneDigits2, status2.c_str(), 0);
//
//        // 2) Създаваме един Date за Check-in и един Date за Check-out:
//        int cd, cm, cy;
//        int od, om, oy;
//        std::cout << "Check-in дата (дд мм гггг), напр. 15  8 2023: ";
//        std::cin >> cd >> cm >> cy;
//        Date checkIn(cd, cm, cy);
//
//        std::cout << "Check-out дата (дд мм гггг), напр. 18  8 2023: ";
//        std::cin >> od >> om >> oy;
//        Date checkOut(od, om, oy);
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//        // 3) Избиране на Room (примерно хардкодваме някаква стая):
//        //    Допускаме, че вече имаме една Room с определени характеристики:
//        Room sampleRoom(301, 120.0, EnumClasses::RoomType::Double, EnumClasses::Status::Available, nullptr);
//        //    (нямаме стратегия, понеже подадохме nullptr в конструктора)
//        //    Ако искаме да добавим стратегия, може примерно:
//        //    sampleRoom.setStrategyByName("Weekend", "Saturday");
//
//        // 4) Създаваме Reservation:
//        Reservation res(guest2, checkIn, checkOut, sampleRoom);
//
//        std::cout << "\nСъздадохте резервация #" << res.getReservationID()
//            << " за гост " << guest2.getName() << "\n";
//        std::cout << "Нощувки: " << res.getNumNights()
//            << ", Обща цена: " << res.getTotalPrice() << " BGN\n\n";
//
//        // 5) Записваме Guest (сега вече с 1 резервация) + самата Reservation в отделни файлове:
//        //    – ъпдейтваме броя на резервациите у госта: (трябва да добавим res в масива на guest2)
//        guest2.addReservation(res);
//
//        // Записваме guest2
//        std::ofstream foutG("guests.bin", std::ios::binary | std::ios::app);
//        if (!foutG) {
//            std::cerr << "Грешка: Не мога да отворя guests.bin за писане!\n";
//            return 1;
//        }
//        guest2.saveToFile(foutG);
//        foutG.close();
//
//        // Записваме res
//        std::ofstream foutR("reservations.bin", std::ios::binary | std::ios::app);
//        if (!foutR) {
//            std::cerr << "Грешка: Не мога да отворя reservations.bin за писане!\n";
//            return 1;
//        }
//        res.saveToFile(foutR);
//        foutR.close();
//
//        std::cout << "Записахте Guest и Reservation във файловете.\n\n";
//    }
//
//    std::cout << "Край на програмата.\n";
//    return 0;
//}
