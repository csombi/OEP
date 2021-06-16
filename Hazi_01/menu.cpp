#include "menu.h"
#include "complex.h"

#include <iostream>

using namespace std;

void Menu::start() {
	int c = -1;
	while( c!= 0 ){
		write_menu();
		cin >> c;
		switch( c ) {
			case 0:
				return;
			case 1:
				Menu::add();
				break;
			case 2:
				Menu::sub();
				break;
			case 3:
				Menu::mul();
				break;
			case 4:
				Menu::div();
				break;
		}
	}
}

void Menu::write_menu() {
	cout << "\n\tMenu\n";
	cout << "0: exit \n";
	cout << "1: add two complex numbers \n";
	cout << "2: substract two complex numbers \n";
	cout << "3: multiply two complex numbers \n";
	cout << "4: divide two complex numbers \n";
	cout << "Input form: <REAL><SIGN><IMAGINARY><i> \n";
}

void Menu::add(){
	Complex a, b, c;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << c.add(a,b);
}

void Menu::sub(){
	Complex a, b, c;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << c.sub(a,b);
}

void Menu::mul(){
	Complex a, b, c;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << c.mul(a,b);
}

void Menu::div(){
	Complex a, b, c;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << c.div(a,b);
}

