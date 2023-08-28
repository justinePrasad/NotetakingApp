// NotetakingLibrary.cpp: Defines the functions for the DLL

#include "pch.h"
#include "NotetakingLibrary.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#undef max
//need to undef max due to error with windows macro

namespace fs = std::filesystem;

fs::path notes_dir("C:/MyNotes");

void notes_init() {
	// creates a directory for notes, if DNE
	// where does it check
	if (!fs::exists(notes_dir)) {
		fs::create_directory(notes_dir);
	}
	
}

bool load_note(const char* filename) {
	//Input should be the filename path
	// Creates filestream object
	
	std::string line;	// used to get each line of file
	std::string path = "C:/MyNotes/" + std::string(filename);
	std::ifstream file(path);

	//String that outputs loading this file
	std::cout << "Loading file: " << filename << "\n";

	if (!file.is_open()) {
		std::cerr << "Cannot open the file. \n";
		return false;
	}

	//Read and write operater that loads the txt file to the console
	while (std::getline(file, line)) {
		std::cout << line << '\n';
	}

	file.close();
	return true;

}

//Prompt user for a note, and then add it to file or data 
bool add_note() {

	//clear buffer
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	std::string noteName;
	std::cout << "What is the title of the note? (don't include file extension)\n";
	std::getline(std::cin, noteName);

	//Prompt user for input
	std::string note;
	std::cout << "Enter the note: \n";
	std::getline(std::cin, note);		// reads the entire line of input

	//generate filename
	std::string filename = "note_" + noteName + ".txt";

	//creating full path to that file name
	fs::path note_path = notes_dir / filename;

	//open the file and writing the note
	std::ofstream note_file(note_path);
	if (!note_file) {
		std::cerr << "Failed to create the file. \n";
		return false;
	}

	note_file << note;
	note_file.close();

	std::cout << "Note added successfully. \n";
	return true;
}

//Prompt user for identifier and delete note
bool delete_note(const char* filename) {
	char confirmation;
	std::string path = "C:/MyNotes/" + std::string(filename);

	// Check if filePath exists
	//If not print, it does DNE
	if (!fs::exists(path)) {
		std::cout << "File does not exist! \n";
		return false;
	}

	//Propmt for confirmation
	//If not equal to Yes, then delete
	std::cout << "Are you sure you want to delete this file(Y/N)\n";
	std::cin >> confirmation;

		if (confirmation != 'Y' && confirmation != 'y')
		{
			std::cout << "Deletion of file cancelled. \n";
			return false;
		}

		//Run delete command
		if (fs::remove(path)) {
			std::cout << "File was deleted successfully \n";
		}
		else {
			std::cout << "An error occured while deleting the file\n";
		}
		
	return true;
}

bool edit_note(const char* filename) {
	std::vector <std::string> lines;

	// Open existing file, first have to read
	std::string path = "C:/MyNotes/" + std::string(filename);
	std::ifstream inputFile(path);

	// Save and Store existing content to lines
	if (inputFile.is_open()) {
		std::string line;	// for storage of line of text
		while (std::getline(inputFile, line)) {
			lines.push_back(line);
		}
	}
	else {
		std::cerr << "Failed to open the file for proper reading. \n";
	}
	inputFile.close();


	// Allow user to edit content by first displaying each line with a linenumber
	displayLinesWithNumbers(lines);
		
	std::cout << lines[0];

	// Ask user for line number
	int lineNumber;
	std::cout << "Enter line number to edit: ";
	std::cin >> lineNumber;
	
	// Display current line
	std::cout << "This is the current line: " << lines[lineNumber-1] << "\n";

	// Enter new line
	std::string newLine;
	std::cout << "Please enter the new line: \n";
	std::cin >> newLine;

	// Confirm and display
	std::cout << "This is the line you entered: " << newLine <<"\n";

	//need to save new line to note
	lines[lineNumber - 1] = newLine;

	// Save vector of strings as the new filename as .txt
	std::ofstream newFile(path);

	if (newFile.is_open()) {
		// pass by reference
		for (const auto& line : lines) {
			newFile << line << '\n';
		}
		// close file after writing
		newFile.close();
	}

	// Display new note
	std::cout << "This is the " << filename << " note now: \n";
	load_note(filename);
	
	return true;

}




void view_directory(const std::string& directory) {

	std::cout << "The files in this current directory are: \n";

	try {
		//iterate through the directory
		for (const auto& entry : std::filesystem::directory_iterator(directory)) {
			std::cout << entry.path().filename() << '\n';
		}
	}
	catch (const std::filesystem::filesystem_error& erro) {
		std::cerr << "An error occured: " << erro.what() << '\n';
	}
}

// add line numbers to lines
void displayLinesWithNumbers(std::vector <std::string> lines) {
	//Count the lines with numbers 
	for (int i = 0; i < lines.size(); i++) {
		std::cout << "Line " << (i + 1) << ": " << lines[i] << '\n';
	}
}
