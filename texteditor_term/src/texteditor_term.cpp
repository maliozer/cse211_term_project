//============================================================================
// Name        : texteditor_term.cpp
// Author      : maliozer
// Version     :
// Copyright   : Copyright Mehmet Ali Özer
// Description : term project
//============================================================================

#include "MaTex.h"

using namespace std;



int main() {
	MaTex app = MaTex();

	while(!app.get_close_app_flag()){
		app.command_router(app.command_reader());
	}

	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
