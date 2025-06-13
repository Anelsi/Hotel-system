
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
	try {
		int num1;
		std::cout << "Enter num for desired activity:\n"
			<< "(1) Add room\n"
			<< "(2) Registrate a guest\n"
			<< "(3) Create Reservation\n"
			<< "(4) Get available rooms and reservations\n"
			<< "(5) Remove Room\n"
			<< "(6) Stop program\n";

		while (true) {

			std::cin >> num1;
			switch (num1) {
			case 1:
				try {
					Accommodation myAccommodation(EnumClasses::MAX_CAPACITY);
					createAndAddRoom(myAccommodation);
				}
				catch (const std::exception& e) {
					std::cerr << "Error adding room: " << e.what() << std::endl;
				}
				break;
			case 2:
				try {
					createAndSaveGuest();
				}
				catch (const std::exception& e) {
					std::cerr << "Error registering guest: " << e.what() << std::endl;
				}
				break;
			case 3:
				try {
					createAndSaveReservation();
				}
				catch (const std::exception& e) {
					std::cerr << "Error creating reservation: " << e.what() << std::endl;
				}
				break;
			case 4:
				try {
					Accommodation hotel(EnumClasses::MAX_CAPACITY);
					loadRoomsFromFile(hotel);
					std::vector<Reservation> allRes = loadReservationsFromFile();
					
				}
				catch (const std::exception& e) {
					std::cerr << "Error loading or printing rooms/reservations: " << e.what() << std::endl;
				}
				break;
			case 5:
				try {
					displayAndDeleteRoomFromFile();
				}
				catch (const std::exception& e) {
					std::cerr << "Error removing reservation: " << e.what() << std::endl;
				}
				break;
			case 6:
				return; 
			default:
				std::cout << "Invalid option, try again.\n";
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Critical error in Receptionist menu: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error in Receptionist menu.\n";
	}
	
	}



void showManagerMenu() {
	try {
		int num1;
		std::cout << "Enter num for desired activity:\n"
			<< "(1) Add room\n"
			<< "(2) Registrate a guest\n"
			<< "(3) Create Reservation\n"
			<< "(4) Get available rooms and reservations\n"
			<< "(5) Remove room\n"
			<< "(6) Get revenue info\n";
		std::cout<< "(7) View client loyalty\n"
			<< "(8) Exit manager menu\n";
		    

		while (true) {
			std::cin >> num1;
			switch (num1) {
			case 1:
				try {
					Accommodation hotel(EnumClasses::MAX_CAPACITY);
					createAndAddRoom(hotel);
				}
				catch (const std::exception& e) {
					std::cerr << "Error adding room: " << e.what() << std::endl;
				}
				break;
			case 2:
				try {
					createAndSaveGuest();
				}
				catch (const std::exception& e) {
					std::cerr << "Error registering guest: " << e.what() << std::endl;
				}
				break;
			case 3:
				try {
					createAndSaveReservation();
				}
				catch (const std::exception& e) {
					std::cerr << "Error creating reservation: " << e.what() << std::endl;
				}
				break;
			case 4:
				try {
					Accommodation hotel(EnumClasses::MAX_CAPACITY);
					loadRoomsFromFile(hotel);
					std::vector<Reservation> allRes = loadReservationsFromFile();
			
				}
				catch (const std::exception& e) {
					std::cerr << "Error loading data: " << e.what() << std::endl;
				}
				break;
			case 5:
				try {
					displayAndDeleteRoomFromFile();
				}
				catch (const std::exception& e) {
					std::cerr << "Error deleting room: " << e.what() << std::endl;
				}
				break;
			case 6: displayRevenueReportFromFile();
			case 7: displayCustomerLoyalty();
			case 8:
				return;
			default:
				std::cout << "Invalid option, try again.\n";
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Critical error in Manager menu: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error in Manager menu.\n";
	}
};
void showAccountantMenu() {
	
	try {
		std::cout << "Enter 1 to get revenue info, 2 to stop the program\n";
		int n;
		std::cin >> n;
		if (n == 1) {
			try {
				displayRevenueReportFromFile();
			}
			catch (const std::exception& e) {
				std::cerr << "Error generating revenue report: " << e.what() << std::endl;
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Critical error in Accountant menu: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error in Accountant menu.\n";
	}

};



int MAX_SIZE = 100;

int main() {
	try {
		
		char* name = new char[MAX_SIZE];
		char* password = new char[MAX_SIZE];

		std::cout << "Enter username: " << std::endl;
		std::cin.getline(name, 100);
		std::cout << std::endl << "Enter password: ";
		std::cin.getline(password, 100);
		std::cout << std::endl;

		int num;
		std::cout << "Enter number for your role:\n"
			<< "1 for Accountant \n"<<"2 for Manager \n"<<"3 for Receptionist\n";
		std::cin >> num;

		if (num == 1) {
			showAccountantMenu();
		}
		else if (num == 2) {
			showManagerMenu();
		}
		else if (num == 3) {
			showReceptionistMenu();
		}
		else {
			std::cout << "Invalid role";
		}

		delete[] name;
		delete[] password;
		

		return 0;
	}
	catch (const std::ios_base::failure& e) {
		std::cerr << "I/O error in main(): " << e.what() << std::endl;
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Memory allocation failed in main(): " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Unhandled exception in main(): " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error in main()." << std::endl;
	}
	return 1;
}

	

	