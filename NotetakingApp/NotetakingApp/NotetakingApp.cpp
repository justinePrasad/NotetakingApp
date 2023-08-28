// NotetakingApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <filesystem>
#include "NotetakingLibrary.h"
namespace fs = std::filesystem;

fs::path notes_dir("C:/MyNotes");


int main()
{	
	int choice;
	std::string noteName;

	// Checks if there is a directory for notes
	notes_init();

	do {
		std::cout << "Notetaking App Menu: \n";
		std::cout << "1. Edit Note\n";
		std::cout << "2. Load Note\n";
		std::cout << "3. Delete Note\n";
		std::cout << "4. View Directory\n";
		std::cout << "5. Add Notes\n";
		std::cout << "0. Exit\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1: 
			std::cout << "Enter the name of the note you want to edit: ";
			std::cin >> noteName;
			// Converts string to a C-style string
			edit_note(noteName.c_str()); 
			break;
		case 2: 
			std::cout << "Enter the note you want to load: ";
			std::cin >> noteName;
			load_note(noteName.c_str());
			break;
		case 3: 
			std::cout << "Enter the note you want to delete: ";
			std::cin >> noteName;
			load_note(noteName.c_str());
			delete_note(noteName.c_str());
			break;
		case 4: view_directory(notes_dir.string()); break;
		case 5: add_note(); break;
		case 0: std::cout << "Exiting...\n"; break;
		default: std::cout << "Invalid choice, try again.\n"; break;
		}
	} while (choice != 0);
	

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
