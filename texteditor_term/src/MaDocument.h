/*
 * MaDocument.h
 *
 *  Created on: Dec 20, 2020
 *      Author: blanc
 */

#ifndef MADOCUMENT_H_
#define MADOCUMENT_H_

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "MaLine.h"

using namespace std;

class MaDocument {

public:
	MaLine* head_doc;
	MaLine* last_doc;

	int current_page = 1;
	vector<MaLine*> page_heads;
	MaDocument();
	virtual ~MaDocument();
	void Mac_Open(string cmd);
	void Mac_Next();
	void Mac_Prev();
	void addlineTail(string data);

	void paginator();
	void display_page(int page_no);

	void printAll();

};

#endif /* MADOCUMENT_H_ */
