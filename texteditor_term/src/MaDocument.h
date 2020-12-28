/*
 * MaDocument.h
 *
 *  Created on: Dec 20, 2020
 *      Author: maliozer
 */

#ifndef MADOCUMENT_H_
#define MADOCUMENT_H_

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stack>

#include "MaLine.h"

using namespace std;

class MaDocument {

public:
	//properties
	MaLine* head_doc;
	MaLine* last_doc;
	stack<vector<vector<string>>> doc_history;
	vector<vector<string>> hist;
	vector<MaLine*> page_heads;
	unsigned int current_page = 1;
	int doc_size = 0;
	
	//methods
	MaDocument();
	virtual ~MaDocument();

	bool Mac_Open(string filepath);
	void Mac_Save(string filename);
	void Mac_Next(bool from_undo = false);
	void Mac_Prev(bool from_undo = false);
	void Mac_Insert(int n, string new_text, bool from_undo = false);
	void Mac_Delete(int n,bool from_undo = false);
	void Mac_Move(int n, int m, bool from_undo = false);
	void Mac_Replace(int n, string new_text, bool from_undo = false);

	void addlineTail(string data);
	void paginator();
	void display_page(int page_no);
	void clear_screen();
	void deleteAll();
};

#endif /* MADOCUMENT_H_ */
