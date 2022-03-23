#include<iostream>
#include<fstream>
#include<string>
#include <sstream> 
#include<vector>
#include <typeinfo>
#include "bst.cpp"
using namespace std;

//read a CSV file into C++ vector.
vector< vector<string> >readCSV(string filePath){
    vector< vector<string> > content;
	vector<string> row;
	string line, word;
 
	fstream file (filePath, ios::in);
	if(file.is_open())
	{
        //get the all the line of csv file
		while(getline(file, line))
		{
			row.clear();
			stringstream str(line);
            //seperate the word with ','
			while(getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
    return content;
}

//print a vector of string vectors.
void printVector(vector< vector<string> > content){
    for(int i=0;i<content.size();i++)
	{
		for(int j=0;j<content[i].size();j++)
		{
			cout<<content[i][j]<<" ";
		}
		cout<<"\n";
	}
}

//challenge only
template<typename T>
Node<T>* insertHex(Node<T>* root, T val, T hexVal){
    if (!root){
        root = new Node<T>(val, hexVal);
    }
    else if (val > root -> data){
        root -> right = insertHex(root -> right, val, hexVal);
    }
    else{
        root -> left = insertHex(root -> left, val, hexVal);
    }
    return root;
}

Node<string>* getNodeFromHex(Node<string>* root, string key){
    if (!root || root->hex == key){
        return root;
    }
    if (stoi(root -> hex) < stoi(key)){
        return getNodeFromHex(root-> right, key);
    }
    else{
        return getNodeFromHex(root -> left, key);
    }
}