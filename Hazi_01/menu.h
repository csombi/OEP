#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <iostream>

class Menu {
	public:
		Menu() {};
		void start();

	private:
		void write_menu();
		void output();
		void add();
		void sub();
		void mul();
		void div();
};

#endif
