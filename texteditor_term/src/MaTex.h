/*
 * MaTex.h
 *
 *  Created on: Dec 19, 2020
 *      Author: blanc
 */

#ifndef MATEX_H_
#define MATEX_H_

#include <vector>
#include <fstream>

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class MaTex {
private:
	bool close_app_flag = false;

public:
	MaTex();
	virtual ~MaTex();

	vector<string> command_reader();
	void command_router(vector<string> cmd);

	bool get_close_app_flag();
	void set_close_app_flag(bool val);

};

#endif /* MATEX_H_ */
