//// main.cpp
//#include <iostream>
//
//#include <string>
//#include <vector>
//#include <memory>
//#include <limits>       // за std::numeric_limits
//
//// ----------------- INCLUDES (зависимости) -----------------
//// Тук включете вашите класове. Ако имената са различни, нагласете.
//// В примера приемаме, че файловете са в същата директория.
//#include "Employee.h"
//#include "Receptionist.h"
//#include "Accountant.h"
//#include "Room.h"
//#include "Guest.h"
//#include "Reservation.h"
//#include "ReservationsManagement.h"
//#include "RevenueInfo.h"
//#include "EnumClasses.h"
//
//// -----------------------------------------------------------
//
//// Помощна функция: прочитане на цяло число от конзолата, с проверка за некоректен вход
//int readInt(const std::string& prompt) {
//    int x;
//    while (true) {
//        std::cout << prompt;
//        if (std::cin >> x) {
//            // успешно прочетено число
//            return x;
//        }
//        else {
//            // неуспешно конвертиране (например написали буква)
//            std::cout << "Невалидно въвеждане. Моля, въведете число." << std::endl;
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//        }
//    }
//}
//
//// Помощна функция: прочитане на низ (цяла линия) от конзолата
//std::string readLine(const std::string& prompt) {
//    std::string line;
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    std::cout << prompt;
//    std::getline(std::cin, line);
//    return line;
//}
//
//// ----------------------------------------------------------------------------
//// Глобални / статични данни (в много прост пример ги оставяме тук като вектори):
//// ----------------------------------------------------------------------------
//
//// Списък с всички служители (включително рецепционисти, счетоводители, мениджъри и т.н.)
//// В реален проект може да ги зареждате от файл, тук ще ги hard-code-ваме за пример.
//std::vector<std::unique_ptr<Employee>> allEmployees;
//
//// Списък с всички стаи
//std::vector<Room> allRooms;
//
//// Списък с всички гости (регистр. в хотела)
//std::vector<Guest> allGuests;
//
//// Мениджър на резервации
//ReservationsManagement reservationsManager;
//
//// Клас за изчисляване на приходи (може да бъде създаван с указател към reservationsManager)
//RevenueInfo revenueInfo(reservationsManager);
//
//// -----------------------------------------------------------
//// Функция: инициализиране (hard‐code) на някои служители и няколко стаи
//// -----------------------------------------------------------
//void initializeData() {
//    // 1) Създаваме няколко предварителни служители
//    //    За прост пример: two receptionists, one accountant, one manager
//    allEmployees.push_back(std::make_unique<Receptionist>("Ivan"));      // конструктор с име
//    allEmployees.push_back(std::make_unique<Receptionist>("Maria"));
//    allEmployees.push_back(std::make_unique<Accountant>("Petar"));
//    // ако имате Manager клас, добавете и него. Пример:
//    // allEmployees.push_back(std::make_unique<Manager>("Georgi"));
//
//    // 2) Нека допълним потребителски имена и пароли (ако имате сетъри в класа Employee):
//    //    (Това е само илюстрация – вие може да имате по-различен конструктор)
//    //    Предполагаме, че при `Receptionist(const char* username, const char* password, const Role& role)`
//    //    role ще е Role::Receptionist, аналогично Accountant, Manager.
//    //    Примерно:
//    //    dynamic_cast<Receptionist*>(allEmployees[0].get())->setUserName("ivan");
//    //    dynamic_cast<Receptionist*>(allEmployees[0].get())->setPassword("1234");
//    //    dynamic_cast<Receptionist*>(allEmployees[1].get())->setUserName("maria");
//    //    dynamic_cast<Receptionist*>(allEmployees[1].get())->setPassword("abcd");
//    //    dynamic_cast<Accountant*>(allEmployees[2].get())->setUserName("petar");
//    //    dynamic_cast<Accountant*>(allEmployees[2].get())->setPassword("qwerty");
//
//    // 3) Създаваме няколко стаи (статично):
//    //    Примерен конструктор: Room(int roomNumber, double basePrice, RoomType type, Status status, PricingStrategy* strat)
//    //    – ако конструкторът е различен, просто поправете параметрите.
//    allRooms.emplace_back(101, 50.0, EnumClasses::RoomType::Single, EnumClasses::Status::Available, nullptr);
//    allRooms.emplace_back(102, 80.0, EnumClasses::RoomType::Double, EnumClasses::Status::Available, nullptr);
//    allRooms.emplace_back(201, 120.0, EnumClasses::RoomType::Apartment, EnumClasses::Status::Available, nullptr);
//
//    // 4) Зареждане на вече записани данни от файл (ако имате такава функционалност)
//    //    Например: reservationsManager.loadFromFile("reservations.dat");
//    //               RevenueInfo може да зареди запазените приходи, и т.н.
//    //
//    //    Ако нямате, просто пропуснете.
//}
//
//// -----------------------------------------------------------
//// Функция: вход в системата (по потребителско име и парола)
//// Връща указател към логнатия служител (nullptr при неуспех)
//// -----------------------------------------------------------
//Employee* login() {
//    std::string username, password;
//    std::cout << "\n=== Вход в системата ===\n";
//    std::cout << "Потребителско име: ";
//    std::cin >> username;
//    std::cout << "Парола: ";
//    std::cin >> password;
//
//    // Търсим в allEmployees по username & password
//    for (auto& ptr : allEmployees) {
//        // Предполагаме, че имате методи getUserName(), getPassword(), getRole()
//        if (ptr->getUserName() == username && ptr->getPassword() == password) {
//            std::cout << "Успешен вход. Влизате като ";
//            switch (ptr->getRole()) {
//            case Role::Receptionist:
//                std::cout << "Рецепционист\n";
//                break;
//            case Role::Accountant:
//                std::cout << "Счетоводител\n";
//                break;
//            case Role::Manager:
//                std::cout << "Мениджър\n";
//                break;
//            default:
//                std::cout << "Неизвестна роля\n";
//            }
//            return ptr.get();
//        }
//    }
//
//    std::cout << "Невалидни данни. Опитайте пак.\n";
//    return nullptr;
//}
//
//// -----------------------------------------------------------
//// МЕНЮ ПРИ РЕЦЕПЦИОНИСТ
//// -----------------------------------------------------------
//void menuReceptionist(Receptionist* user) {
//    int choice = 0;
//    while (true) {
//        std::cout << "\n=== МЕНЮ (РЕЦЕПЦИОНИСТ) ===\n";
//        std::cout << "1) Добавяне на стая\n";
//        std::cout << "2) Регистрация на гост\n";
//        std::cout << "3) Създаване на резервация\n";
//        std::cout << "4) Преглед на налични стаи\n";
//        std::cout << "5) Преглед на текущи резервации\n";
//        std::cout << "6) Анулиране на резервация\n";
//        std::cout << "7) Изход в основното меню\n";
//        std::cout << "Ваш избор: ";
//        std::cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            // ------------- Добавяне на стая -------------
//            int roomNum = readInt("Номер на стаята: ");
//            double price;
//            std::cout << "Базова цена: "; std::cin >> price;
//            std::cout << "Въведете тип стая (0=Single, 1=Double, 2=Suite): ";
//            int t; std::cin >> t;
//            EnumClasses::RoomType type = static_cast<EnumClasses::RoomType>(t);
//            // Статус по подразбиране: Available
//            EnumClasses::Status status = EnumClasses::Status::Available;
//            // Ще пропуснем PricingStrategy (nullptr)
//            Room newRoom(roomNum, price, type, status, nullptr);
//            allRooms.push_back(newRoom);
//            std::cout << "Стая успешно добавена.\n";
//            break;
//        }
//        case 2: {
//            // ------------- Регистрация на гост -------------
//            std::string fname, lname, id, phone;
//            fname = readLine("Име: ");
//            lname = readLine("Фамилия: ");
//            id = readLine("ЕГН/Личен код: ");
//            phone = readLine("Телефон: ");
//            // Предполагаме, че Guest конструкторът е: Guest(const char* fname, const char* lname, const char* id, const char* phone)
//            Guest g(fname.c_str(), lname.c_str(), id.c_str(), phone.c_str());
//            allGuests.push_back(g);
//            std::cout << "Гост регистриран успешно.\n";
//            break;
//        }
//        case 3: {
//            // ------------- Създаване на резервация -------------
//            if (allGuests.empty() || allRooms.empty()) {
//                std::cout << "Няма налични гости или стаи! Регистрирайте първо гост и/или добавете стаи.\n";
//                break;
//            }
//
//            // Изберете гост (показваме индекс 0..N-1):
//            std::cout << "Изберете гост (0 .. " << allGuests.size() - 1 << "):\n";
//            for (size_t i = 0; i < allGuests.size(); ++i) {
//                std::cout << i << ") " << allGuests[i].getFullName() << "\n";
//            }
//            int gi = readInt("Номер на гост: ");
//            if (gi < 0 || gi >= (int)allGuests.size()) {
//                std::cout << "Невалиден избор.\n";
//                break;
//            }
//
//            // Изберете стая (по аналогичен начин):
//            std::cout << "Изберете стая (0 .. " << allRooms.size() - 1 << "):\n";
//            for (size_t i = 0; i < allRooms.size(); ++i) {
//                std::cout << i << ") Стая №" << allRooms[i].getRoomNum()
//                    << ", Цена: " << allRooms[i].getBasePrice() << "\n";
//            }
//            int ri = readInt("Индекс на стая: ");
//            if (ri < 0 || ri >= (int)allRooms.size()) {
//                std::cout << "Невалиден избор.\n";
//                break;
//            }
//
//            // Дати (въведете 3 цели числа: ден, месец, година)
//            std::cout << "Въведете дата на настаняване (ден месец година): ";
//            int d1, m1, y1; std::cin >> d1 >> m1 >> y1;
//            Date checkIn(d1, m1, y1);
//            std::cout << "Въведете броя нощувки: ";
//            int nights; std::cin >> nights;
//            Date checkOut = checkIn.addDays(nights); // предполагаме, че имате метод addDays()
//
//            // Създаваме обект Reservation
//            Reservation r(allGuests[gi], allRooms[ri], checkIn, checkOut);
//            // Добавяме в мениджъра
//            reservationsManager.addReservation(
//                allGuests[gi], checkIn, checkOut, allRooms[ri]
//            );
//            std::cout << "Резервация добавена успешно.\n";
//            break;
//        }
//        case 4: {
//            // ------------- Преглед на налични стаи -------------
//            std::cout << "\nНалични стаи:\n";
//            for (const Room& rr : allRooms) {
//                // Предполага се, че статусът е Available или Occupied
//                if (rr.getStatus() == EnumClasses::Status::Available) {
//                    std::cout << "Стая №" << rr.getRoomNum()
//                        << " | Тип: " << rr.getRoomType()
//                        << " | Цена: " << rr.getBasePrice() << "\n";
//                }
//            }
//            break;
//        }
//        case 5: {
//            // ------------- Преглед на текущи резервации -------------
//            std::cout << "\nТекущи резервации:\n";
//            int total = reservationsManager.getResCounter();
//            for (int i = 0; i < total; ++i) {
//                Reservation* rr = reservationsManager.getReservationAt(i);
//                if (rr != nullptr) {
//                    std::cout << i << ") Гост: " << rr->getGuest().getFullName()
//                        << " | Стая: " << rr->getRoom().getRoomNum()
//                        << " | Дата на настаняване: " << rr->getCheckInDate().toString()
//                        << " | Дата на напускане: " << rr->getCheckOutDate().toString()
//                        << "\n";
//                }
//            }
//            break;
//        }
//        case 6: {
//            // ------------- Анулиране на резервация -------------
//            std::cout << "\nИзберете индекс на резервация за анулиране (0 .. "
//                << reservationsManager.getResCounter() - 1 << "): ";
//            int idx = readInt("");
//            if (idx < 0 || idx >= reservationsManager.getResCounter()) {
//                std::cout << "Невалиден индекс.\n";
//                break;
//            }
//            Reservation* toCancel = reservationsManager.getReservationAt(idx);
//            if (toCancel) {
//                // Предполагаме, че имате метод removeReservation(const Guest&, const Date&, const Date&, const Room&)
//                reservationsManager.removeReservation(
//                    toCancel->getGuest(),
//                    toCancel->getCheckInDate(),
//                    toCancel->getCheckOutDate(),
//                    toCancel->getRoom()
//                );
//                std::cout << "Резервацията е анулирана.\n";
//            }
//            else {
//                std::cout << "Резервация не съществува.\n";
//            }
//            break;
//        }
//        case 7:
//            // излизане към основното меню
//            return;
//        default:
//            std::cout << "Невалиден избор. Опитайте пак.\n";
//        }
//    }
//}
//
//// -----------------------------------------------------------
//// МЕНЮ ПРИ СЧЕТОВОДИТЕЛ
//// -----------------------------------------------------------
//void menuAccountant(Accountant* user) {
//    int choice = 0;
//    while (true) {
//        std::cout << "\n=== МЕНЮ (СЧЕТОВОДИТЕЛ) ===\n";
//        std::cout << "1) Приходи за определен ден\n";
//        std::cout << "2) Приходи за определен месец\n";
//        std::cout << "3) Приходи за определена година\n";
//        std::cout << "4) Изход в основното меню\n";
//        std::cout << "Ваш избор: ";
//        std::cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            int d, m, y;
//            std::cout << "Въведете ден, месец, година: ";
//            std::cin >> d >> m >> y;
//            Date sample(d, m, y);
//            double revDay = revenueInfo.getTotalRevenuePerDay(sample);
//            std::cout << "Приход за " << sample.toString() << ": " << revDay << " лв.\n";
//            break;
//        }
//        case 2: {
//            int m, y;
//            std::cout << "Въведете месец и година: ";
//            std::cin >> m >> y;
//            double revMonth = revenueInfo.getTotalRevenuePerMonth(m, y);
//            std::cout << "Приход за месец " << m << "/" << y << ": " << revMonth << " лв.\n";
//            break;
//        }
//        case 3: {
//            int y;
//            std::cout << "Въведете година: ";
//            std::cin >> y;
//            double revYear = revenueInfo.getTotalRevenuePerYear(y);
//            std::cout << "Приход за година " << y << ": " << revYear << " лв.\n";
//            break;
//        }
//        case 4:
//            return;
//        default:
//            std::cout << "Невалиден избор. Опитайте пак.\n";
//        }
//    }
//}
//
//// -----------------------------------------------------------
//// МЕНЮ ПРИ МЕНИДЖЪР (преглед на клиентска активност и лоялност)
//// -----------------------------------------------------------
//void menuManager(Employee* /*user*/) {
//    // Тук можете да имплементирате логика по ваш вкус:
//    // Например, да се обиколи списък от гости (allGuests) и да се покаже:
//    // – брой резервации на гост
//    // – обща похарчена сума (ако имате такава стойност)
//    // Тъй като детайлите зависят от това как сте направили класа Guest/GuestActivity,
//    // тук давам само едни примерни съобщения:
//    std::cout << "\n=== МЕНЮ (МЕНИДЖЪР) ===\n";
//    if (allGuests.empty()) {
//        std::cout << "Няма регистрирани гости.\n";
//    }
//    else {
//        for (const Guest& g : allGuests) {
//            // Предполагаме, че имате метод getNumberOfReservations() и getTotalSpent()
//            std::cout << "Гост: " << g.getFullName()
//                << " | Брой резервации: " << g.getNumberOfReservations()
//                << " | Изразходвани суми: " << g.getTotalSpent() << " лв.\n";
//        }
//    }
//    std::cout << "Натиснете Enter, за да се върнете…";
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    std::cin.get();
//}
//
//// -----------------------------------------------------------
//// ОСНОВЕН ЦИКЪЛ НА ПРОГРАМАТА
//// -----------------------------------------------------------
//int main() {
//    initializeData();
//
//    while (true) {
//        Employee* logged = nullptr;
//        // Още един цикъл: до успешен вход
//        do {
//            logged = login();
//        } while (logged == nullptr);
//
//        // След успешен login(), проверяваме ролята:
//        Role r = logged->getRole();
//        if (r == Role::Receptionist) {
//            menuReceptionist(static_cast<Receptionist*>(logged));
//        }
//        else if (r == Role::Accountant) {
//            menuAccountant(static_cast<Accountant*>(logged));
//        }
//        else if (r == Role::Manager) {
//            menuManager(logged);
//        }
//        else {
//            std::cout << "Ролята ви не е разпозната.\n";
//        }
//
//        // Връщаме се в началото (вход)
//        char c;
//        std::cout << "\nИскате ли да излезете от програмата? (d/n): ";
//        std::cin >> c;
//        if (c == 'd' || c == 'Д' || c == 'D') {
//            break;
//        }
//    }
//
//    // -----------------------------------------------------------
//    // При затваряне: запазване на данни (ако има такава функционалност)
//    // -----------------------------------------------------------
//    // Например:
//    // reservationsManager.saveToFile("reservations.dat");
//    // revenueInfo.saveReportToFile("revenues.bin");
//    // allGuests – ако имате метод да записвате гости, извикате го тук
//
//    std::cout << "Данните са записани. Програмата приключва.\n";
//    return 0;
//}
