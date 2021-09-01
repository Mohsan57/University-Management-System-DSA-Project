#pragma once
#include"Functions.h"

struct CEO_NODE {
	string programes_names;
	int HOD_ID;
	CEO_NODE* next;
	CEO_NODE* prev;
	
};
class CEO {
protected:
	bool File_Existing;
	string ceo_username;
	string ceo_password;
public:

	CEO_NODE* ceo_head;
	CEO_NODE* ceo_tail;
	CEO();
	~CEO();
	bool CEO_Login();
	void input_programes();		//		input Data and store in File
	void Store_programes_List();		//		Store Programes in list from file For future Use
	void Show_Programes();		//	Show available Programes
	void Modify_Programes();
	void Arrange_All_Functions();
	void push_back(int ,string);
	bool check_repetation(string);
	bool check_programe_in_list(string);
	int linked_list_size();
};

CEO::CEO() {
	File_Existing = false;
	ceo_password = "";
	ceo_username = "";
	ceo_head = NULL;
	ceo_tail = NULL;
}

bool CEO::CEO_Login() {
	cout << "\t\t\tEnter User Name: ";
	cin >> ceo_username;
	cout << "\t\t\tEnter Password: ";
	passw(ceo_password);
	if (ceo_username == "ceo" && ceo_password == "ceo")
		return true;
	else return false;
}

void CEO::input_programes() {
	int Temp_id = 100;	//	For auto Genrate Programe Code
	string Temp_names;	//	For Programe name input
	cin.ignore();
	ofstream file;
	file.open("Programes.txt", ios::app);
	cout << "\t\t\tFor Exit write \'exit()\'" << endl << endl;

	while (Temp_names != "exit()") {	//loop until user Enter "exit()"

		cout << "\t\t\tWrite Programe Name: ";
		getline(cin, Temp_names);
		if (Temp_names != "exit()") {

			bool condition = true;

			Store_programes_List();	//call the Funtion that store data in linked list. Beacause Repeat of Programe

			condition = check_repetation(Temp_names);
			if (condition == false) {
				cout << "\n\t\t\tThis Program Already Register" << endl;
			}
			

			CEO_NODE* current = ceo_head;
			if (ceo_head != NULL) {
				Temp_id = ceo_tail->HOD_ID;	// check last HOD ID from file
			}

			if (condition == true) {	// if Data is Not Repeat
				Charcter_Remover(Temp_names, ' ', '.');
				++Temp_id;
				file << Temp_id << "\t" << Temp_names << endl;	//	Enter Data in File
			}

		}
		else {
			cout << "\n\n\t\t\tGood Bye!" << (char)2 << endl;
		}
	}
	file.close();
}

void CEO::Store_programes_List() {
	ifstream file;
	int temp_ID;
	string temp_name;
	string line;

	//	Delete All data in Linked list
	CEO_NODE* temp;
	while (ceo_head != NULL) {
		temp = ceo_head;
		ceo_head = ceo_head->next;
		free(temp);
	}
	//***************************

	file.open("Programes.txt", ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			istringstream info(line);
			info >> temp_ID >> temp_name;	//Store Data in list Array

			Charcter_Remover(temp_name, '.', ' ');	// if data that in file contain ' . ' then change in space

			push_back(temp_ID, temp_name);
		}
		File_Existing = true;
	}
	else {
		File_Existing = false;
		cout << "\n\t\t\t\'Programes.txt\' This Name of File Not Exist " << (char)2 << endl;	//if File not Created 
	}
	file.close();
}

void CEO::push_back(int HOD_ID, string programes_names) {
	CEO_NODE* newNode = new CEO_NODE();
	newNode->HOD_ID = HOD_ID;
	newNode->programes_names = programes_names;
	if (ceo_head == NULL) {
		ceo_head = ceo_tail = newNode;
		ceo_head->prev = NULL;
		ceo_tail->next = NULL;
	}
	else {
		ceo_tail->next = newNode;
		newNode->prev = ceo_tail;
		ceo_tail = newNode;
		ceo_tail->next = NULL;
	}
}

bool CEO::check_repetation(string name) {
	CEO_NODE* current = ceo_head;
	if (ceo_head == NULL) {
		return true;
	}
	while (current != NULL) {
		if (current->programes_names == name) {
			return false;
		}
		current = current->next;
	}
	return true;
}

void CEO::Show_Programes() {
	Store_programes_List();	//call the Funtion that store data in List 
	if (ceo_head!=NULL) {
		cout << "\t\t\t\tProgrames That University Provide" << endl;
		cout << "\t\t**************************************************************" << endl;
		CEO_NODE* current = ceo_head;
		while (current != NULL) {
			cout << "\t\t\t\t\tPrograme: " << current->programes_names << endl;
			current = current->next;
		}
		cout << "\t\t**************************************************************" << endl;
	}
	else { cout << "\t\t\tSorry University does't provide Any Programe" << endl; }
}

void CEO::Modify_Programes()	// Erase Data
{
	Store_programes_List();
	bool bol = false;
	cin.ignore();
	if (File_Existing == true) {	// check File Existing. using Variable Declare in Private
		string Temp_Programe;
		cout << "\t\t\t\t\tErase Specific Programe" << endl;
		cout << "\t\t\t\t\tEnter Programe Name: ";
		getline(cin, Temp_Programe);	//input programe
		if ((ceo_head) == NULL)
			bol = false;
		else {
			CEO_NODE* current = ceo_head;
			CEO_NODE* next;
			while (current != NULL) {
				if (current->programes_names == Temp_Programe) {
					next = current->next;
					if (ceo_head == NULL || current == NULL)
						bol = false;
					else {
						if (ceo_head == current)
							ceo_head = current->next;
						if (current->next != NULL)
							current->next->prev = current->prev;
						if (current->prev != NULL)
							current->prev->next = current->next;
						free(current);
						bol = true;
					}
					current = next;
				}
				else
					current = current->next;
			}
		}


		/*
		CEO_NODE *temp = ceo_head;
		if (ceo_head == NULL) {
			bol = false;
		}else{
			if (temp->programes_names == Temp_Programe) {
				if (ceo_head->next == NULL) {
					ceo_head = ceo_tail = NULL;
				}
				else {
					ceo_head = temp->next;
					ceo_head->prev = NULL;

				}
				
			}
			else {
				while (temp->next != NULL) {
					if (temp->next->programes_names == Temp_Programe) {
						bol = true;
						if (temp->next == NULL) {
							CEO_NODE* temp2 = NULL;
							temp->next = NULL;
							temp2->next->prev = temp;
							free(temp2);
						}
						else {
							CEO_NODE* temp2 = temp->next;
							temp->next = temp2->next;
							temp2->next->prev = temp;
							free(temp2);
						}
						cout << "\t\t\t\t\tErase Successful" << endl;
						
					}
					temp = temp->next;
				}
			}
		}*/
		if (bol == true) {	//	if programe is in file And create New File
			ofstream file;
			file.open("Programes2.txt", ios::app);
			CEO_NODE* temp = ceo_head;
			while (temp != NULL) {
				file <<  temp->HOD_ID << "\t" << temp->programes_names << endl;
				temp = temp->next;
			}
			file.close();
			remove("Programes.txt");
			int b = rename("Programes2.txt", "Programes.txt");
			cout << "\t\t\t\t\tPrograme '" << Temp_Programe << "' Removed!" << (char)2 << endl;
		}
		if (bol == false) {	//	if programe not in file
			cout << "\n\t\t\t\t\tThis Programe Not Exist" << endl;
		}
	}
}

int CEO::linked_list_size() {
	int size=0;
	CEO_NODE* current = ceo_head;
	if (ceo_head == NULL) {
		size = 0;
	}
	while (current != NULL) {
		size++;
		current = current->next;
	}
	return size;
}

void CEO::Arrange_All_Functions() {
	int choice = 1;
	bool bol = CEO_Login();
	if (bol == true) {
		while (choice != 0) {
			system("cls");
			cout << "\t\t\t\t----->\tWelcome To CEO Page\t<-----" << endl;
			cout << "\t\t-----------------------------------------------------------------" << endl;
			cout << "\t\t|\t1: Register New Programes\t\t\t\t|" << endl;
			cout << "\t\t|\t2: Delete Programes\t\t\t\t\t|" << endl;
			cout << "\t\t|\t3: Show Programes\t\t\t\t\t|" << endl;
			cout << "\t\t|\t0: Exit\t\t\t\t\t\t\t|" << endl;
			cout << "\t\t-----------------------------------------------------------------" << endl;
			cout << "\t\t\tEnter Your Choice: ";
			cin >> choice;
			switch (choice) {
			case 1: {
				system("cls");
				input_programes();
				cout << "Enter Any Key to Continue..." << endl;
				_getch();
			}break;
			case 2: {
				system("cls");
				Modify_Programes();
				cout << "Enter Any Key to Continue..." << endl;
				_getch();
			}break;
			case 3: {
				system("cls");
				Show_Programes();
				cout << "Enter Any Key to Continue..." << endl;
				_getch();
			}break;
			default: {
				cout << "\t\t\tInvalid Input" << (char)2 << endl;
			}
				   break;
			}
		}
	}
	else {
		cout << "\n\t\t\t\tInvalid Password " << (char)2 << endl;
		cout << "Enter Any Key to Continue..." << endl;
		_getch();
	}
}

bool CEO::check_programe_in_list(string str) {
	Store_programes_List();
	CEO_NODE* ceo_temp = ceo_head;
	while (ceo_temp != NULL) { // if user Enter programe is Valid
		if (str == ceo_temp->programes_names) {
			return true;
		}
		ceo_temp = ceo_temp->next;
	}
	return false;
}
CEO::~CEO() {
}
