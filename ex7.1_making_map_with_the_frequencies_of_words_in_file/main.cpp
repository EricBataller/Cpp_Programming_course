// ex 7.1.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;

map<string, int> word_counter_map(string file_path) { //create a function that returns a map -> string,int
	ifstream file;
	file.open(file_path); //the function open the file_path of the argument
	if (!file.is_open()) {
		std::cerr << "Error: Could not open the file!" << std::endl;
		exit(1);
	}
	else {cout << "The file was opened correctly" << endl;}
	
	map<string, int> wordcountmap; //this is the map that the function will return
	string word;
	while (file >> word) { //go through all the words in the file 
		for (int i = 0; i < word.size(); i++) { //Get rid of all the wierd chars that don't belong to the words
			if (word[i] < 'A' || word[i] > 'Z' && word[i] < 'a' || word[i] > 'z') {
				word.erase(i, 1);
				i--; 
			}
		}
		if (word != "") { wordcountmap[word] += 1;		}
	}
	file.close();
	return wordcountmap;
}


int main() {
	map<string, int> wordcountmap;
	wordcountmap = word_counter_map("example.txt");
	cout << "------ List of words and their frequencies in example.txt: ------" << endl;
	for (auto i : wordcountmap) {
		cout << i.first << " [" << i.second << "]" << endl;
	}
}
