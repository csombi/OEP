#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "halmaz.h"

class Menu {
	public:
		Menu();
		void start();

	private:
		void write_menu( );
		void setEmpty( Halmaz& );
		void isEmpty( Halmaz& );
		void add( Halmaz& );
		void del( Halmaz& );
		void isElement( Halmaz& );
		void countEven( Halmaz& );
		void printMethod( Halmaz& );
		void printOperator( Halmaz& );
		void fileReader( Halmaz& );
};

#endif
