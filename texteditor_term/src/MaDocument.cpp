/*
 * MaDocument.cpp
 *
 *  Created on: Dec 20, 2020
 *      Author: maliozer
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

bool MaDocument::Mac_Open(string filepath){
		cout << "Filename is " << filepath << endl;

		ifstream inFile(filepath);

		if(inFile.peek() == EOF){
			this->deleteAll();
			this->addlineTail(" ");
		}
		else{
			if (!inFile) {
				cerr << "Unable to open file " << filepath << endl;
				return 0;
			}

			this->deleteAll();

			string x;
			while (getline(inFile, x)) {
				this->addlineTail(x);
			}
			
		}

		return 1;
}

void MaDocument::Mac_Save(string filename){
	MaLine* temp = this->head_doc;

	ofstream MaDocumentObject;
	MaDocumentObject.open (filename + ".txt");
	while(temp != nullptr){
		if(temp->next != nullptr){
			MaDocumentObject << temp->line_data << endl;
		}
		else{
			MaDocumentObject << temp->line_data;
		}

		temp = temp->next;
	}

	MaDocumentObject.close();
}

void MaDocument::Mac_Next(bool from_undo){
	if(this->page_heads.size() < this->current_page + 1){
		this->display_page(this->current_page);
		cout << "This is the last page!" << endl;
	}
	else{
		/* UNCOMMENT IF NEXT IS NEEDED IN UNDO */

		/*
		if(!from_undo){
			vector<string> command;
			command.push_back("prev");
			this->hist.push_back(command);
			this->doc_history.push(this->hist);
			this->hist.clear();
		}
		*/
		this->display_page(this->current_page + 1);
	}
}

void MaDocument::Mac_Prev(bool from_undo){
	if(current_page - 1 == 0){
		this->display_page(this->current_page);
		cout << "This is the first page!" << endl;
	}
	else{

		/* UNCOMMENT IF PREV IS NEEDED IN UNDO */

		/*
		if(!from_undo){
			vector<string> command;
			command.push_back("next");
			this->hist.push_back(command);
			this->doc_history.push(this->hist);
			this->hist.clear();
		}
		*/
		this->display_page(this->current_page - 1);
	}
}

void MaDocument::Mac_Insert(int n, string new_text, bool from_undo){
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

		if(!from_undo){
			vector<string> command;
			command.push_back("delete");
			command.push_back(to_string(n));
			this->hist.push_back(command);
			this->doc_history.push(this->hist);
			this->hist.clear();
		}
	}

	else{
		while(distance >= 1){
			if(distance == 1){
				this->addlineTail(new_text);
			}
			else if(distance > 1){
				this->addlineTail(" ");
				/* change with uncommented line to see effect */
				// this->addlineTail("__BLANK__");
			}
			distance--;

			if(!from_undo){
				vector<string> command;
				command.push_back("delete");
				command.push_back(to_string(this->doc_size));
				this->hist.push_back(command);
			}

		}
			if(!from_undo){
				this->doc_history.push(this->hist);
				this->hist.clear();
			}
	}

}

void MaDocument::Mac_Delete(int n,bool from_undo){
	int distance = this->doc_size - n;
	if(distance < 0){
		cout << "The line does not exist!" << endl;
	}
	else if(n == 1){
		if(this->head_doc->next == nullptr){
			this->addlineTail(" ");
			/* change with uncommented line to see effect */
			// this->addlineTail("__BLANK_DEL__");
		}

		MaLine* temp = this->head_doc;
		this->head_doc = this->head_doc->next;
		if(!from_undo){
			vector<string> command;
			command.push_back("insert");
			command.push_back(to_string(n));
			command.push_back(temp->line_data);
			this->hist.push_back(command);
			this->doc_history.push(this->hist);
			this->hist.clear();
		}

		free(temp);

		this->doc_size--;

	}
	else if(distance == 0){
		MaLine* temp = this->last_doc;
		if(!from_undo){
			vector<string> command;
			command.push_back("insert");
			command.push_back(to_string(n));
			command.push_back(temp->line_data);
			this->hist.push_back(command);
			this->doc_history.push(this->hist);
			this->hist.clear();
		}
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
				break;
			}
			searcher_ptr = searcher_ptr->next;
		}

		if(!from_undo){
			vector<string> command;
			command.push_back("insert");
			command.push_back(to_string(n));
			command.push_back(searcher_ptr->line_data);
			this->hist.push_back(command);
			this->doc_history.push(this->hist);
			this->hist.clear();
		}
		free(searcher_ptr);
	}
}

void MaDocument::Mac_Move(int n, int m, bool from_undo){
	if(this->doc_size < n){
		cout << "Line " << n << " does not exist!" << endl;
	}
	else{
		MaLine* n_ptr = this->head_doc;
		for (int i = 1; i <= n; ++i) {
			if(i == n){
				break;
			}

			n_ptr = n_ptr->next;
		}
		string moved_data =  n_ptr->line_data;
		this->Mac_Delete(n, true);
		this->Mac_Insert(m,moved_data, true);
		

		if(!from_undo){
			vector<string> command;
			command.push_back("move");
			command.push_back(to_string(m));
			command.push_back(to_string(n));
			this->hist.push_back(command);
			this->doc_history.push(this->hist);
			this->hist.clear();
		}

	}

}

void MaDocument::Mac_Replace(int n, string new_text, bool from_undo){
	if(n <= this->doc_size){
		MaLine* searcher_ptr = this->head_doc;
		for (int i = 1; i < n; ++i) {
			searcher_ptr = searcher_ptr->next;
		}

		string old_data = searcher_ptr->line_data;

		searcher_ptr->line_data = new_text;

		if(!from_undo){
			vector<string> command;
			command.push_back("replace");
			command.push_back(to_string(n));
			command.push_back(old_data);
			this->hist.push_back(command);
			this->doc_history.push(this->hist);
			this->hist.clear();
		}
	}
	else{
		cout << "Line does not exist!" << endl;
	}

}

void MaDocument::addlineTail(string data){
	MaLine* new_line = new MaLine();
	if(data == ""){
		data = " ";
	}
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
	this->clear_screen();
	cout << "---------- BEGIN PAGE ------------" << endl;
	for (int line_no=(-10 + (page_no * 10) + 1); line_no <= page_no_limit; ++line_no) {
		if(temp == nullptr){
			break;
		}
		cout << line_no <<") " << temp->line_data << endl;
		temp = temp->next;
	}
	cout << "---------- END PAGE ------------" << endl;

	cout << "\n\n --- Page "<< page_no <<" ---"<< endl;
}

void MaDocument::clear_screen(){
	cout << string( 100, '\n' );
}

void MaDocument::deleteAll(){
	MaLine* temp = this->head_doc;
	while(temp != nullptr){
		if(temp->next != nullptr){
			temp = temp->next;
			temp->prev = nullptr;
			free(this->head_doc);

			this->doc_size--;
			this->head_doc = temp;
		}
		else{
			free(temp);
			this->head_doc = nullptr;
			break;
		}
	}

	this->current_page = 1;

	while(this->doc_history.size()>0){
		this->doc_history.pop();
	}
	
}
