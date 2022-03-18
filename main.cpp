#include<iostream>
#include<fstream>
#include<string>
#include <sstream> 
#include <typeinfo>
#include<stack>
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

template <typename T>
void createBSTFromCSV(BST<T>* csvBST, vector< vector<string> >csvVec){
    // BST<T> csvBST = BST<T>();
    csvBST->root = csvBST->insertHex(csvBST->root, csvVec[0][0], csvVec[0][1]);
    for (int i =1; i<csvVec.size(); i++){
        csvBST->insertHex(csvBST->root, csvVec[i][0], csvVec[i][1]);
    }
    // return csvBST;
}

string binToHex(BST<string> bst, string input){
	stack<char> s1;
	stack<string> s;
	string tempBin;
	string result;
	for (int i=0; i<input.length();i++){
		s1.push(input[i]);
	}
	while (!s1.empty()){
		tempBin += s1.top();
		s1.pop();
		if (tempBin.length() == 4){
			//reverse temp bin since it's stored the reverse version of input in stack
			reverse(tempBin.begin(),tempBin.end());
			Node<string>* tempNode = getNodeFromHex(bst.root, tempBin);
			s.push(tempNode->data);
			tempBin = "";
		}
	}
	//handle additional bin numbers (when s1 has <4 elements left)
	if (!tempBin.empty()){
		reverse(tempBin.begin(),tempBin.end());
		while (tempBin.length()<4){
			tempBin = "0"+tempBin;
		}
		cout<<"Add: "<<tempBin<<endl;
		tempBin = getNodeFromHex(bst.root, tempBin)->data;
		cout<<"Additional: "<<tempBin<<endl;
	}
	while (!s.empty()){
		result += s.top();
		s.pop();
	}
	return tempBin+result;
}

int main(){
    vector< vector<string> >readBin = readCSV("binhexdata.csv");
    BST<string>*binHexBST = new BST<string>();
	createBSTFromCSV(binHexBST, readBin);
	string userInput;
	cout<<"Please enter a binary number"<<endl;
	cin>>userInput;
	cout<<"The hex number of your input is: "<<binToHex(*binHexBST, userInput)<<endl;
}