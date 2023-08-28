#pragma once
#include <string>
#include <vector>

// Controls if functions are "imp." or "exp."
#ifdef NOTELIBRARY_EXPORTS
	#define NOTELIBRARY_API __declspec(dllexport)
#else
	#define NOTELIBRARY_API __declspec(dllimport)
#endif

// Initialize the note-taking system
extern "C" NOTELIBRARY_API void notes_init();

// Add a new , T if added, F if not
extern "C" NOTELIBRARY_API bool add_note();

// Delete note by index
// True on sucess; False if filename does not exist
extern "C" NOTELIBRARY_API bool delete_note(const char* filename);

// Used to edit notes of a file
extern "C" NOTELIBRARY_API bool edit_note(const char* filename);

// Load file based on filename
extern "C" NOTELIBRARY_API bool load_note(const char* filename);

// View all the notes
extern "C" NOTELIBRARY_API void view_directory(const std::string& directory);

// Helper function to help display lines with corresponding lne numbers
extern "C" NOTELIBRARY_API void displayLinesWithNumbers(const std::vector <std::string> lines);