/*
 * MaDocument.cpp
 *
 *  Created on: Dec 20, 2020
 *      Author: blanc
 */

#include "MaDocument.h"

MaDocument::MaDocument() {
	// TODO Auto-generated constructor stub
	this->head_doc =  nullptr;
	this->last_doc =  nullptr;
}

MaDocument::~MaDocument() {
	// TODO Auto-generated destructor stub
}

void MaDocument::Mac_Open(string filepath){
		cout << "Filename is " << filepath << endl;

		ifstream inFile;
		inFile.open(filepath);

		if (!inFile) {
		    cerr << "Unable to open file " << filepath << endl;
		      // call system to stop
		}

		string x;
		while (inFile >> x) {
			this->addlineTail(x);
		}

		//this->printAll();
		paginator();
		this->display_page(this->current_page);
}

void MaDocument::Mac_Next(){
	if(this->page_heads.size() < current_page + 1){
		this->display_page(this->current_page);
		cout << "This is the last page!" << endl;
	}
	else{
		this->display_page(this->current_page + 1);
		this->current_page += 1;
	}
}

void MaDocument::Mac_Prev(){
	if(current_page - 1 == 0){
		this->display_page(this->current_page);
		cout << "This is the first page!" << endl;
	}
	else{
		this->display_page(this->current_page - 1);
		this->current_page -= 1;
	}
}


void MaDocument::addlineTail(string data){
	MaLine* new_line = new MaLine();
	new_line->line_data = data;
	new_line->next = nullptr;
	new_line->prev = nullptr;

	if(this->head_doc == nullptr){
		this->head_doc = new_line;
		this->last_doc = new_line;
	}
	else{
		new_line->prev = this->last_doc;
		this->last_doc->next = new_line;
		this->last_doc = new_line;
	}
}

void MaDocument::paginator(){
	MaLine* temp = this->head_doc;
	for (int i = 0; temp != nullptr; ++i) {
		if(i % 10 == 0){
			this->page_heads.push_back(temp);
		}

		temp = temp->next;
	}
}

void MaDocument::display_page(int page_no){
	MaLine* temp = this->page_heads[page_no - 1];
	int page_no_limit = page_no * 10;

	cout << "---------- BEGIN DOCUMENT ------------" << endl;
	for (int line_no=(-10 + (page_no * 10) + 1); line_no <= page_no_limit; ++line_no) {
		if(temp == nullptr){
			break;
		}
		cout << line_no <<") " << temp->line_data << endl;
		temp = temp->next;
	}
	cout << "---------- END DOCUMENT ------------" << endl;

	cout << "\n\n --- Page "<< page_no <<" ---"<< endl;
}

//TEMPORARY METHOD WILL BE DELETED
void MaDocument::printAll(){
	MaLine* temp = this->head_doc;
	int line_no=1;
	cout << "---------- BEGIN DOCUMENT ------------" << endl;
	while(temp != nullptr && line_no < 11){
		cout << line_no <<") " << temp->line_data << endl;
		temp = temp->next;
		line_no++;
	}
	cout << "---------- END DOCUMENT ------------" << endl;

	cout << "\n\n --- Page 1 ---"<< endl;
}
