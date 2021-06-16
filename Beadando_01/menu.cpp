#include "menu.h"
#include "halmaz.h"
#include <iostream>

Menu::Menu() {}

void Menu::start(){
	Halmaz h;
	int err, c;
	std::string tmp;

	while( c != 0 ){
		do {
			write_menu();
			std::cout << "--> option: ";
			std::cin >> c;
			err = std::cin.fail() || c < 0 || c > 9;
			if( err ) {
				std::cerr << "--> Wrong input! \n";
				std::cin.clear();
				std::getline( std::cin, tmp );
			} else {
				switch( c ) {
					case 0:
						return;
					case 1:
						Menu::setEmpty( h );
						break;
					case 2:
						Menu::fileReader( h );
						break;
					case 3:
						Menu::isEmpty( h );
						break;
					case 4:
						Menu::add( h );
						break;
					case 5:
						Menu::del( h );
						break;
					case 6:
						Menu::isElement( h );
						break;
					case 7:
						Menu::countEven( h );
						break;
					case 8:
						Menu::printMethod( h );
						break;
					case 9:
						Menu::printOperator( h );
						break;
				}
			}

		} while( err );
	}

}

void Menu::write_menu(){
	std::cout << "\n\t----------Menu----------\n";
	std::cout << "0: exit\n";
	std::cout << "1: clear the set\n";
	std::cout << "2: fill the set by file\n";
	std::cout << "3: check if set is empty\n";
	std::cout << "4: add element to the set\n";
	std::cout << "5: delete element from the set\n";
	std::cout << "6: check if an element is in the set\n";
	std::cout << "7: print the number of even numbers in the set\n";
	std::cout << "8: print the set by method\n";
	std::cout << "9: print the set by operator overloading\n";
}

void Menu::setEmpty( Halmaz& h ){
	h.Halmaz::setEmpty();
	std::cout << "--> Set is cleared.\n";
}

void Menu::isEmpty( Halmaz& h ){
	if( h.Halmaz::isEmpty() ) std::cout << "--> Set is empty.\n";
	else std::cout << "--> Set is not empty.\n";
}

void Menu::add( Halmaz& h ){
	int err, e;
	std::string tmp;
	do {
		std::cout << "--> Element to add: ";
		std::cin >> e;
		err = std::cin.fail();
		if( err ) {
			std::cerr << "--> Wrong input! \n";
			std::cin.clear();
			std::getline( std::cin, tmp );
		} else  h.Halmaz::add( e );
	} while( err );
}

void Menu::del( Halmaz& h ){
	int err, e;
	std::string tmp;
	do {
		std::cout << "--> Element to delete: ";
		std::cin >> e;
		err = std::cin.fail();
		if( err ) {
			std::cerr << "--> Wrong input! \n";
			std::cin.clear();
			std::getline( std::cin, tmp );
		} else  h.Halmaz::del( e );
	} while( err );
}

void Menu::isElement( Halmaz& h ){
	int err, e;
	unsigned int i;
	std::string tmp;
	do {
		std::cout << "--> Element to check: ";
		std::cin >> e;
		err = std::cin.fail();
		if( err ) {
			std::cerr << "--> Wrong input! \n";
			std::cin.clear();
			std::getline( std::cin, tmp );
		} else {
			if( h.Halmaz::isElement( e, i ) ) std::cout << "--> Element is in set. \n";
			else std::cout << "--> Element is not in set. \n";
		}
	} while( err );
}

void Menu::countEven( Halmaz& h ){
	std::cout << "--> Number of even numbers in set: " << h.Halmaz::countEven() << "\n";
}

void Menu::printMethod( Halmaz& h){
	h.Halmaz::print();
}

void Menu::printOperator( Halmaz& h){
	std::cout << h;
}

void Menu::fileReader( Halmaz& h ){
	try {
		std::string path;
		std::cout << "--> Name of file: ";
		std::cin >> path;
		h.Halmaz::fileReader( path );
	} catch( Halmaz::Exception e ) {
		if( e == Halmaz::FileOpenError ) std::cerr << "--> File open error! \n";
	}
}
