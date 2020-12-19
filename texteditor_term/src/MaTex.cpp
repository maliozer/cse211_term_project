/*
 * MaTex.cpp
 *
 *  Created on: Dec 19, 2020
 *      Author: blanc
 */

#include "MaTex.h"


//use enum to use commands in switch statement as case key. because it don't accept string as key.
// In that way I tried to avoid using lots of if else statements.
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

void MaTex::command_router(vector<string> cmd){
	bool exit_flag = false;
	switch (hash_cmd(cmd[0])) {
		case ma_open:
			//code
			cout << "Open File" << endl;
			if(cmd.size() > 1){
				string filename;
				filename = cmd[1];
				cout << "Filename is " << filename << endl;

				ifstream inFile;
				inFile.open(filename);

				if (!inFile) {
				    cerr << "Unable to open file " << filename << endl;
				      // call system to stop
				}

				string x;
				while (inFile >> x) {
				  cout << x << endl;
				}

			}
			else{
				cout << "open command need a filename" << endl;
			}
			break;
		case ma_save:
			//code
			cout << "Save File" << endl;
			break;
		case ma_insert:
			cout << "Insert Cmd" << endl;
			//code
			break;
		case ma_delete:
			cout << "Delete Cmd" << endl;
			//code
			break;
		case ma_move:
			cout << "Move Cmd" << endl;
			//code
			break;
		case ma_replace:
			//code
			cout << "Replace Cmd" << endl;
			break;
		case ma_next:
			//code
			cout << "Next Cmd" << endl;
			break;
		case ma_prev:
			//code
			cout << "Prev Cmd" << endl;
			break;
		case ma_undo:
			//code
			cout << "Undo Cmd" << endl;
			break;
		case ma_exit:
			cout << "Exit" << endl;
			this->close_app_flag = true;
			break;
		default:
			cout << "Command not found!" << endl;
			break;
	}//end of switch
}

bool MaTex::get_close_app_flag(){
	return this->close_app_flag;
};

void MaTex::set_close_app_flag(bool val){
	this->close_app_flag = val;
};

