#include <string>
#include <sstream>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

#include "inverter.h"

using namespace std;

bool isNotAlpha(char c){
	return !isalpha(c);
}

/*
A basic inverted index function that parses through text files to create
am index. This technique is important to speedy searches.

Precondition:  a single text file (ala an index of a book) that contains
							 an input text file in each line
Postcondition: a list of every word along with a list of indicies
 							 (the line number of one of the input files)
*/
string build_inverted_index(string filename){
	fstream files;
	fstream input;
	map<string, set<int>> invertedIndex;
	string fileBuffer;
	string inputBuffer;
	//dynamic array for the list of input files
	vector<string> fileList(2, "");
	unsigned i = 0;

	//loop through inputs.txt to get all the filenames
	files.open(filename, ios::in);
	while (getline(files, fileBuffer)) {
		if(i+1 > fileList.size()){
			fileList.resize(i+1);
		}
		//checks if the string is a text file before adding to the array
		if(fileBuffer.substr(fileBuffer.size()-4,fileBuffer.size()) == ".txt"){
			fileList.at(i) = fileBuffer;
			i++;
		}
	}
	files.close();

	//loop through each filename in inputs.txt and insert each word,
	//if it is not already in the map, and the index of the filename f
	//rom the array
	for (unsigned i = 0; i < fileList.size(); i++) {
		input.open(fileList.at(i), ios::in);
		while (getline(input, inputBuffer)) {
			//gets rid of all non alpha
			replace_if(inputBuffer.begin(), inputBuffer.end(), isNotAlpha, ' ');
			istringstream iss(inputBuffer);
			//loops through each word on the line
			do {
				string word;
				iss >> word;
				//checks for EOF
				if (int(word[0]) > 0) {
					invertedIndex[word].insert(i);
				}
			} while (iss);
		}
		input.close();
	}

	string result = "";

	//loops through the map to generate the output
	for (auto& x: invertedIndex) {
		result += x.first + ": ";
		string intList;
		//loops through the set
	  for (auto& y: x.second) {
			intList += to_string(y) + " ";
		}
		//gets rid of the space at the end
		intList = intList.substr(0,intList.size()-1);
		result += intList + '\n';
	}

	return result;
}
