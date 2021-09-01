#pragma once
#include"CEO.h"
#include"Functions.h"
// Queue
struct REG_NODE {
	int Student_Id;
	string Student_Program;
	REG_NODE* next;
};

class Registration_office {
protected:
	CEO ceo;
	int ids = 1224;
	REG_NODE* reg_front;
	REG_NODE* reg_rear;
public:
	void Register_new_student();	// new Students Registration
	void Reg_push_back(int, string);
	bool check_Enter_ids(int,string*);
};

void Registration_office::Register_new_student() {
	string programes;
	cin.ignore();
	// Delete All data in Linked list
	REG_NODE* current = reg_front;
	REG_NODE* next = NULL;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	reg_front=reg_rear= NULL;
	//***************************
	while (1) {
		ceo.Show_Programes();		// Show the Programes That CEO Provide
		cout << "\t\t\tEnter Your Program: ";
		getline(cin, programes);
		if (programes == "exit()") {	// Close Programe Enter "exit()" like a command
			cout << "\t\t\tThese \'ID's\' will be Delete After Some Time" << endl;
			break;
		}
		bool bol = ceo.check_programe_in_list(programes);	// Checking the Programs and User Enter

		if (bol == true) {	// if Valid Programe is Enter

			if (reg_front != NULL) {	// liste not Empty
				ids = reg_rear->Student_Id;
			}
			ids++;	// Auto create an Id

			Reg_push_back(ids, programes); // Store in Linked list

			cout << "\n\t\t\tStudent ID: " << ids << endl << endl;	// Show ID
		}
		else if (bol == false) { cout << "\n\t\t\tThis Programe we not Offer\n"; }	// if Programe is not Valid
	}
}

void Registration_office::Reg_push_back(int id, string programe) {
	REG_NODE* tmp = new REG_NODE;
	tmp->Student_Id = id;
	tmp->Student_Program = programe;
	tmp->next = NULL;
	if (reg_front != NULL) {
		reg_rear->next = tmp;
		reg_rear = tmp;
	}
	else {
		reg_front = reg_rear = tmp;
	}
}

bool Registration_office::check_Enter_ids(int id,string *programes) {
	REG_NODE* temp = reg_front;
	if (temp != NULL) {
		int n = reg_rear->Student_Id;
		while (temp->Student_Id != id) {
			if (temp->Student_Id == n) {
				return false;
			}
			 else{
				int Student_Id = temp->Student_Id;
				string Student_Program = temp->Student_Program;
				reg_front = reg_front->next;
				free(temp);
				temp = reg_front;
				Reg_push_back(Student_Id, Student_Program);
			}
		}
		if (temp->Student_Id == id) {
			*programes = temp->Student_Program;
			reg_front = reg_front->next;
			free(temp);
			return true;
		}
	}
	return false;
}