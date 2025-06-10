
#include <iostream>
#include "RoomDeletionHelper.h"
#include "Accommodation.h"
#include "RoomCreationHelper.h"
#include "GuestCreationHelper.h"
#include "ReservationCreationHelper.h"
#include "FileLoadHelper.h"
#include "RevenueReportHelper.h"
#include "CustomerLoyaltyHelper.h"



void showReceptionistMenu() {
	int num1;
	std::cout << "Enter num for desired activity: " << std::endl << "(1)Add room" << std::endl <<
		"(2)Registrate a guest" << std::endl << "(3)Create Reservation" << std::endl <<
		"(4)Get available rooms and reservatios"
		<< std::endl << "(5)Remove Reservatons"  "(6) Stop programm" << "/n";

	
	while (true) {

		std::cin >> num1;

		if (num1 == 1) {

			Accommodation myAccommodation(EnumClasses::MAX_CAPACITY);
			createAndAddRoom(myAccommodation);

		}
		else if (num1 == 2) {

			createAndSaveGuest();

		}
		else if (num1 == 3) {
			createAndSaveReservation();


		}
		else if (num1 == 4) {
			Accommodation hotel(EnumClasses::MAX_CAPACITY);
			loadRoomsFromFile(hotel);


			std::cout << "Loaded rooms: " << hotel.getUsed() << "\n";


			std::vector<Reservation> allRes = loadReservationsFromFile();
			std::cout << "Loaded reservations: " << allRes.size() << "\n";


			for (const auto& r : allRes) {
				r.print();
				std::cout << "------------------------\n";
			}



		}
		else if (num1 == 5) {


			displayAndDeleteRoomFromFile();

		}

		else if (num1 == 6) {
			break;


		}
		else {
			break;
		}
	}


};
void showManagerMenu() {

int num1;
std::cout << "Enter num for desired activity: " << std::endl << "(1)Add room" << std::endl <<
"(2)Registrate a guest" << std::endl << "(3)Create Reservation" << std::endl <<
"(4)Get available rooms and reservatios"
<< std::endl << "(5)Remove Reservatons" << std::endl << "(6)Get revenue info" << std::endl
<< "(7)Get view of clent loyalty" << "\n" << "(8) Stop programm" << "\n";

while (true) {

	std::cin >> num1;

	if (num1 == 1) {

		Accommodation myAccommodation(EnumClasses::MAX_CAPACITY);
		createAndAddRoom(myAccommodation);

	}
	else if (num1 == 2) {

		createAndSaveGuest();

	}
	else if (num1 == 3) {
		createAndSaveReservation();


	}
	else if (num1 == 4) {
		Accommodation hotel(EnumClasses::MAX_CAPACITY);
		loadRoomsFromFile(hotel);

		
		std::cout << "Loaded rooms: " << hotel.getUsed() << "\n";

	
		std::vector<Reservation> allRes = loadReservationsFromFile();
		std::cout << "Loaded reservations: " << allRes.size() << "\n";

		
		for (const auto& r : allRes) {
			r.print();
			std::cout << "------------------------\n";
		}



	}
	else if (num1 == 5) {


		displayAndDeleteRoomFromFile();

	}
	else if (num1 == 6) {

		displayRevenueReportFromFile();

	}
	else if (num1 == 7) {
		displayCustomerLoyalty();

	}
	else if (num1 == 8) {
		break;
		
	
	}
	else {
		break;
	}
}

};
void showAccountantMenu() {
	std::cout << "Enter 1 to Get revenue info, press 2  to stop the programm" << "/n";
	int n;
	std::cin>>n;
	if (n == 1) {
		displayRevenueReportFromFile();
	
	}

};



int MAX_SIZE = 100;

int main() {

	

	char* name = new char[MAX_SIZE];
	char* password = new char[MAX_SIZE];



	std::cout << "Enter username: " << std::endl;
	std::cin.getline(name,100);
	std::cout << std::endl<<"Enter password: ";
	std::cin.getline(password,100);
    std::cout<<std::endl;

	int num;
	std::cout << "Enter number for your role:" << "\n" << "1 for Accountant"
		<< "2 for Manager" <<"\n"<< "3 for Receptionist" << "\n";
	std::cin >> num;
	if (num == 1) {
	
		showAccountantMenu();
	
	}
	else if(num==2){
	
		showManagerMenu();
	}
	else if (num == 3) {
		showReceptionistMenu();
	
	
	}
	else {
	
		std::cout << "Invalid role";
	
	}
	return 0;



	delete[] name;
	delete[] password;

}