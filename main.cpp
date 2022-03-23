#include<iostream>
#include<stack>
#include<string>
#include "utility.cpp"
using namespace std;

template <typename T>
void createBSTFromCSV(BST<T>* csvBST, vector< vector<string> >csvVec){
    csvBST->root = insertHex(csvBST->root, csvVec[0][0], csvVec[0][1]);
    for (int i =1; i<csvVec.size(); i++){
        insertHex(csvBST->root, csvVec[i][0], csvVec[i][1]);
    }
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