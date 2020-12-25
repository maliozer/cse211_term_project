/*
 * MaLine.h
 *
 *  Created on: Dec 22, 2020
 *  Author: blanc
 */

#ifndef MALINE_H_
#define MALINE_H_

#include <string>

using namespace std;

class MaLine {

public:
	string line_data;
	MaLine *prev;
	MaLine *next;

	MaLine();
	virtual ~MaLine();

};

#endif /* MALINE_H_ */
