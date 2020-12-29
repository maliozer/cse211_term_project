/*
 * MaTex.cpp
 *
 *  Created on: Dec 19, 2020
 *      Author: maliozer
 */

#include "MaTex.h"

enum matex_code {
    ma_open,
    ma_save,
    ma_insert,
    ma_delete,
	ma_move,
	ma_replace,
	ma_next,
	ma_prev,
	ma_undo,
	ma_exit,
	ma_hist,
	ma_none
};

matex_code hash_cmd (std::string const& command_text) {
    if (command_text == "open") return ma_open;
    else if (command_text == "save") return ma_save;
    else if (command_text == "insert") return ma_insert;
    else if (command_text == "delete") return ma_delete;
    else if (command_text == "move") return ma_move;
    else if (command_text == "replace") return ma_replace;
    else if (command_text == "next") return ma_next;
    else if (command_text == "prev") return ma_prev;
    else if (command_text == "undo") return ma_undo;
    else if (command_text == "history") return ma_hist;
    else if (command_text == "exit") return ma_exit;

    else return ma_none;
}

MaTex::MaTex() {
	// TODO Auto-generated constructor stub

}

MaTex::~MaTex() {
	// TODO Auto-generated destructor stub
}

vector<string> MaTex::command_reader(){
	string user_input;
	vector<string> tokens;

	cout << "open | save | insert | delete | move | replace | next | prev | undo | history | exit" << endl;

	getline(cin,user_input);

	istringstream iss(user_input);

    do
    {
        string subs;
        iss >> subs;
        tokens.push_back(subs);
    } while (iss);

    tokens.pop_back();
    return tokens;

}

void MaTex::command_router(vector<string> cmd, bool undo_trigger){
	switch (hash_cmd(cmd[0])) {
		case ma_open:
			//code
			if(cmd.size() > 1){
				bool success = 0;
				success = this->matex_document.Mac_Open(cmd[1]);
				if(success){
					this->matex_document.paginator();
					this->matex_document.display_page(this->matex_document.current_page);
				}

			}
			else{
				cout << "open command need a filepath" << endl;
			}

			break;
		case ma_save:
			//code
			if(cmd.size() > 1){
				this->matex_document.Mac_Save(cmd[1]);
				cout << "Document saved as " << cmd[1] << ".txt" << endl;
			}
			else{
				cout << "Provide a filename to save document!" << endl;
			}
			cout << "Save File" << endl;
			break;
		case ma_insert:
			if(cmd.size() > 2){
				int line_no = stoi(cmd[1]);
				string line_text = "";
				for (unsigned int i = 2; i < cmd.size(); ++i) {
					line_text += cmd[i] + " ";
				}

				this->matex_document.Mac_Insert(line_no, line_text,undo_trigger);

				this->matex_document.paginator();
				this->matex_document.display_page(this->matex_document.current_page);
			}
			else{
				cout << "Please enter the line content!" << endl;
			}
			break;
		case ma_delete:
			if(cmd.size() > 1){
				int n = stoi(cmd[1]);
				if (n < 0){n *= -1;} //get absolute value of n
				this->matex_document.Mac_Delete(n, undo_trigger);
				
				this->matex_document.paginator();
				this->matex_document.display_page(this->matex_document.current_page);
				
			}
			//code
			break;
		case ma_move:
			if(cmd.size() > 2){
				int n = stoi(cmd[1]);
				int m = stoi(cmd[2]);
				this->matex_document.Mac_Move(n, m, undo_trigger);

				this->matex_document.paginator();
				this->matex_document.display_page(this->matex_document.current_page);
			}
			else{
				cout << "Give the line to from n to m!" << endl;
			}
			//code
			break;
		case ma_replace:
			//code
			if(cmd.size() > 2){
				int line_no = stoi(cmd[1]);
				string line_text = "";
				for (unsigned int i = 2; i < cmd.size(); ++i) {
					line_text += cmd[i] + " ";
				}

				this->matex_document.Mac_Replace(line_no, line_text,undo_trigger);

				this->matex_document.paginator();
				this->matex_document.display_page(this->matex_document.current_page);
			}
			else{
				cout << "Please enter the line content!" << endl;
			}
			break;
		case ma_next:
			this->matex_document.Mac_Next(undo_trigger);
			break;
		case ma_prev:
			this->matex_document.Mac_Prev(undo_trigger);
			break;
		case ma_undo:
			//code
			if(this->matex_document.doc_history.size() > 0){
				vector<vector<string>> last_commands = this->matex_document.doc_history.top();
				int cmd_size = last_commands.size();
				for (int i = cmd_size-1; i >= 0; i--) {
					this->command_router(last_commands[i], true);
				}

				this->matex_document.doc_history.pop();
			}
			else{
				cout << "Nothing changed on document!" << endl;
			}
			break;
		case ma_hist:
			//code
			if(this->matex_document.head_doc != nullptr){
				this->matex_document.display_page(this->matex_document.current_page);
			}
			if(this->matex_document.doc_history.size() > 0){
				cout << "Number of Completed Actions: " << this->matex_document.doc_history.size() << endl;
			}
			else{
				cout << "Number of Completed Actions: " << 0 << endl;
			}

			break;
		case ma_exit:
			cout << "Exit" << endl;
			this->close_app_flag = true;
			break;
		default:
			cout << "Command not found!" << endl;
			cout << cmd[0] << endl;
			break;
	}//end of switch
}

bool MaTex::get_close_app_flag(){
	return this->close_app_flag;
};

void MaTex::set_close_app_flag(bool val){
	this->close_app_flag = val;
};
