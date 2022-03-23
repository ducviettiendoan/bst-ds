#include<iostream>
#include"bst.cpp"
using namespace std;

int main(){
    BST<int> testBST = BST<int>();
    char* emptyStr = new char[0];
    testBST.root = testBST.insert(testBST.root, 10);
    testBST.insert(testBST.root, 5);
    testBST.insert(testBST.root, 15);
    testBST.insert(testBST.root, 3);
    testBST.insert(testBST.root, 7);
    testBST.insert(testBST.root, 11);
    testBST.insert(testBST.root, 17);
    testBST.insert(testBST.root, 2);
    testBST.insert(testBST.root, 4);
    testBST.insert(testBST.root, 8);
    testBST.insert(testBST.root, 6);
    cout<<testBST.in_order(testBST.root, emptyStr)<<endl;
    // cout<<testBST.minimum(testBST.root)->data<<endl;
    // cout<<testBST.maximum(testBST.root)->data<<endl;
    //test succ
    // Node<int>* getNode = testBST.get(testBST.root, 4);
    // cout<<testBST.successor(getNode)->data<<endl;

    // //test delete
    Node<int>* getNode1 = testBST.get(testBST.root, 5);
    // testBST.deleteNode(getNode1);
    // testBST.in_order(testBST.root);

    // vector<int>*test = new vector<int>();
    // test = testBST.getTrimVec(testBST.root, test, 2,8);
    // for (int i =0; i<(*test).size(); i++){
    //     cout<<(*test)[i]<<" ";
    // }

    //findRoot
    // vector<int>test;
    // // test.push_back(4); 
    // test.push_back(5);
    // test.push_back(6);
    // test.push_back(7);
    // test.push_back(8);
    // cout<<testBST.findRoot(testBST.root,test)->data<<endl;

    //getSubTree
    // queue<Node<int>*> final = testBST.getSubTree(getNode1);
    // while (!final.empty()){
    //     cout<<final.front()->data<<endl;
    //     final.pop();
    // }

    //test trim
    testBST.trim(6,15);
    //print the BST again (in-level order)
    Node<int>* getNode2 = testBST.get(testBST.root, 10);
    queue<Node<int>*> final = testBST.getSubTree(getNode2);
    while (!final.empty()){
        cout<<final.front()->data<<endl;
        final.pop();
    }
}