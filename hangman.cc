#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

// characters positions in string function

bool char_pos(string wtbg, char c, short start, bool found);
void give_answer(string wtbg, int a);

// Main function
int main(void) {
	
		// Initialize the dictionary
	ifstream dictionary("hangman_dictionary.txt");

		// Create a vector where to hold the words
	vector<string> words;
		// Character positions in word_to_be_guessed
	vector<char> character_positions;

		// Temporary string
	string temp;

		// Initialize random seed
	srand(time(NULL));

		// Random number
	int rand_num;

	string word_to_be_guessed;

		// Wanna play or not?
	char c;

		// String where to hold the making word
	string word_making = "";

		// Position of the character in the string word_to_be_guessed
	int position;

		// Blank line
	cout << endl;

	if(dictionary.is_open()) {

			// Read the dictionary and add all the words to the vector called  "words"
		while(getline(dictionary, temp)) {
			words.push_back(temp);
		}

			// Close the dictionary since i no longer need it

		dictionary.close();

			// Initialize the random number between 0 and words.size()

		rand_num = rand() % words.size();

		word_to_be_guessed = words[rand_num];
	}
	else {
		cout << "Dictionary is missing." << endl;

		return 0;
	}

		// This is where the program begins for real
	cout << "Hi, this is Hangman .001." << endl
		 << endl
		 <<	"wanna play a game? ";

		 // Wanna play or not?
	cin >> c;

	if((c == 'y') || (c == 'Y')) {
		cout << endl
			 << "Let's start!"
			 << endl
			 << endl
			 << "I have a word in mind, can you guess what that word is?"
			 << endl
			 << endl
			 << "You can either enter a character at a time (3 possibilities to go wrong), or guess the entire word."
			 << endl
			 << endl
			 << "Press 1 at any time to give the answer!"
			 << endl
			 << endl
			 << "GO!"
			 << endl;

			 	// The user have three possibilities to go wrong
			cout << endl << "The word is " << word_to_be_guessed.length()-1 << " characters long." << endl << endl;
				
			for(int i = 0; i < 3; ++i) {

			 		// Check if the character is in the string
				cin >> c;

				if(c == '1') {
					give_answer(word_to_be_guessed, 1);

					return 0;
				}

				cout << endl;
				
				if(char_pos(word_to_be_guessed, c, 0, false) == true) {
					i--;
				}
			}

			cout << "So... do you know the word or not!? ";

				// Ask for the answer
			give_answer(word_to_be_guessed, 0);
	}
	else {
		cout << endl << "OK, no problem! =)" << endl;
	}

	return 0;
}
			// if character position is minus or equal to the string lenght, continue
		


// char_pos function implementation

// c = character to find
// start = at what point of the string should we start searching for c
// wtbg = word from dictionary

bool char_pos(string wtbg, char c, short start = 0, bool found = false) {

	size_t position;

	if((position = wtbg.find(c, start)) != string::npos) {
			// position+1 to not write "Character at position 0"
		cout <<"Character found at position number " << short(position)+1 << "." << endl;

			// position+1 to go 1 character further in the string
		char_pos(wtbg, c, short(position)+1, true);
	}
	else {
			// If found is true, that means that at least a character has been found
		if(found == true) {
			cout << endl;

				// Returns true so the program give the user another possibilities because the character was indeed found
			return true;
		}
		else {
			cout << "Character not found." << endl << endl;

			return false;
		}
	}
}


// give_answer function

void give_answer(string wtbg, int a) {

		// Answer to the game
	string answer;

	if(a == 1) {
		cout << "So you know the answer huh!? What is it? ";
	}

	cin.ignore();
	getline(cin, answer);

	if((wtbg.compare(answer) == 0) && (a == 0)) {

		cout << endl << "Great! You're right, the word was indeed " << answer << "!!" << endl;
	}
	else if((wtbg.compare(answer) == 0) && (a == 1)) {

		cout << endl << "WOW, it's the correct answer! HOW DID YOU DO THAT!? You cheated, didn't you!?" << endl;
	}
	else {
		cout << endl << "You know how to play this game, right? YOU LOSE! The word was " << wtbg << endl;
	}
}