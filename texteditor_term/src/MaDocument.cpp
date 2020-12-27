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
		}

		string x;
		while (inFile >> x) {
			this->addlineTail(x);
		}

}

void MaDocument::Mac_Next(){
	if(this->page_heads.size() < current_page + 1){
		this->display_page(this->current_page);
		cout << "This is the last page!" << endl;
	}
	else{
		this->display_page(this->current_page + 1);
	}
}

void MaDocument::Mac_Prev(){
	if(current_page - 1 == 0){
		this->display_page(this->current_page);
		cout << "This is the first page!" << endl;
	}
	else{
		this->display_page(this->current_page - 1);
	}
}

void MaDocument::Mac_Insert(int n, string new_text){
	int distance = n - this->doc_size;

	if(distance <= 0){
		MaLine* temp = this->head_doc;
		for (int i = 1; i <= n; ++i) {
			if(i == n){
				MaLine* new_line = new MaLine();
				new_line->line_data = new_text;

				new_line->prev = temp->prev;
				if(n != 1){
					temp->prev->next = new_line;
				}
				else{
					this->head_doc = new_line;
				}

				new_line->next = temp;
				temp->prev = new_line;

				this->doc_size++;
				break;
			}

			temp = temp->next;
		}
	}

	else{
		while(distance >= 1){
			if(distance == 1){
				this->addlineTail(new_text);
			}
			else if(distance > 1){
				this->addlineTail("__BLANK__");
			}
			distance--;
			// send message to undo -> delete(this->doc_size (ıncı satırı sil))
		}
	}

}

void MaDocument::Mac_Delete(int n){
	int distance = this->doc_size - n;
	if(distance < 0){
		cout << "The line does not exist!" << endl;
	}
	else if(n == 1){
		if(this->head_doc->next == nullptr){
			this->addlineTail("__BLANK_DEL__");
		}

		MaLine* temp = this->head_doc;
		this->head_doc = this->head_doc->next;
		free(temp);

		this->doc_size--;

	}
	else if(distance == 0){
		MaLine* temp = this->last_doc;
		last_doc = last_doc->prev;
		last_doc->next = nullptr;
		this->doc_size--;
		free(temp);
	}
	else{
		MaLine* searcher_ptr = this->head_doc;
		for (int i = 1; i <= this->doc_size; ++i) {
			if(i == n){
				searcher_ptr->prev->next = searcher_ptr->next;
				searcher_ptr->next->prev = searcher_ptr->prev;
				this->doc_size--;
				free(searcher_ptr);
				break;
			}
			searcher_ptr = searcher_ptr->next;
		}
	}
}

void MaDocument::Mac_Move(int n, int m){
	if(this->doc_size < n){
		cout << "Line " << n << " does not exist!" << endl;
	}
	else{
		MaLine* n_ptr = this->head_doc;
		MaLine* m_ptr = this->head_doc;
		for (int i = 1; i <= n; ++i) {
			if(i == n){
				break;
			}

			n_ptr = n_ptr->next;
		}
		string moved_data =  n_ptr->line_data;
		this->Mac_Delete(n);
		this->Mac_Insert(m,moved_data);

	}

}

void MaDocument::Mac_Replace(int n, string new_text){
	if(n <= this->doc_size){
		MaLine* searcher_ptr = this->head_doc;
		for (int i = 1; i < n; ++i) {
			searcher_ptr = searcher_ptr->next;
		}

		searcher_ptr->line_data = new_text;
	}
	else{
		cout << "Line does not exist!" << endl;
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

	this->doc_size++;
}



void MaDocument::paginator(){
	this->page_heads.clear();

	MaLine* temp = this->head_doc;
	for (int i = 0; temp != nullptr; ++i) {
		if(i % 10 == 0){
			this->page_heads.push_back(temp);
		}

		temp = temp->next;
	}
}

void MaDocument::display_page(int page_no){
	int max_page = this->page_heads.size();
	if(page_no > max_page){
		page_no = max_page;
	}
	this->current_page = page_no;

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
