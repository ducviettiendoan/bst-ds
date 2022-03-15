#include<iostream>
#include<vector>
#include<queue>
using namespace std;

template<typename T>
class Node{
    public:
        T data;
        Node<T>* left;
        Node<T>* right;
        Node(T val){
            data = val;
            left = nullptr;
            right = nullptr;
        };
        ~Node(){
            left = nullptr;
            right = nullptr;
        }
};

template<typename T>
class BST{
    public:
        Node<T>* root;
        BST();
        // ~BST();
        //utilities
        Node<T>* getParent(Node<T>*, Node<T>*);
        void transplant(Node<T>*, Node<T>* );
        void deleteTree(Node<T>*);
        Node<T>* findRoot(Node<T>*, vector<T>);
        vector<T>* getTrimVec(Node<T>*, vector<T>*, T, T);
        queue<Node<T>*> getSubTree(Node<T>*);
        //methods
        bool isEmpty();
        Node<T>* get(Node<T>*, T);
        Node<T>* insert(Node<T>*, T);
        void deleteNode(Node<T>*);
        Node<T>* maximum(Node<T>*);
        Node<T>* minimum(Node<T>*);
        Node<T>* successor(Node<T>*);
        //ask for this method
        void in_order(Node<T>*);
        void trim(T low, T high);
};

template<typename T>
BST<T>::BST(){
    root = nullptr;
}

template<typename T>
void BST<T>::deleteTree(Node<T>* root)
{
    if (!root) return;
 
    deleteTree(root->left);
    deleteTree(root->right);

    cout << "Deleting node: " << root->data<<endl;
    delete root;
}

// template<typename T>
// BST<T>::~BST(){
//     deleteTree(root);
// }

template <typename T>
bool BST<T>::isEmpty(){
    if (root){
        return true;
    }
    return false;
}

template<typename T>
Node<T>* BST<T>::get(Node<T>* root, T key){
    if (!root || root->data == key){
        return root;
    }
    if (root -> data < key){
        return get(root -> right, key);
    }
    else{
        return get(root -> left, key);
    }
}

template<typename T>
Node<T>* BST<T>::getParent(Node<T>*root, Node<T>* node){
    if (!root || node == root){
        return nullptr;
    }
    if (root->left->data == node->data || root->right->data == node->data){
        return root;
    }
    if (root -> data < node->data){
        return getParent(root -> right, node);
    }
    else{
        return getParent(root -> left, node);
    }
}

template<typename T>
Node<T>* BST<T>::insert(Node<T>* root, T val){
    if (!root){
        root = new Node<T>(val);
    }
    else if (val > root -> data){
        root -> right = insert(root -> right, val);
    }
    else{
        root -> left = insert(root -> left, val);
    }
    return root;
}

template<typename T>
Node<T>* BST<T>::minimum(Node<T>*root){
    if (!root || !(root ->left)){
        return root;
    }
    return minimum(root->left);
}

template<typename T>
Node<T>* BST<T>::maximum(Node<T>*root){
    if (!root || !(root ->right)){
        return root;
    }
    return maximum(root->right);
}

template<typename T>
Node<T>* BST<T>::successor(Node<T>* node){
    if (node->right){
        return minimum(node->right);
    }
    Node<T>* parent = getParent(root,node);
    //double check heap memory assignment
    while (parent && node == parent->right){
        node = parent;
        parent = getParent(root,parent);
    }
    return parent;
}

template<typename T>
void BST<T>::transplant(Node<T>* u, Node<T>* v){
    //no set parent
    if (u == root){
        root = v;
    }
    else if (u == getParent(root,u)->right){
        getParent(root,u)->right = v;
    }
    else{
        getParent(root,u)->left = v;
    }
}

template<typename T>
void BST<T>::deleteNode(Node<T>* node){
    if (!(node->right)){
        transplant(node, node->left);
    }
    else if (!(node->left)){
        transplant(node, node->right);
    } 
    else{
        //succ
        Node<T>*y = minimum(node->right);
        if (getParent(root,y) != node){
            transplant(y, y->right);
            y->right = node -> right;
        }
        transplant(node, y);
        y -> left = node -> left;
    }
}

template<typename T>
void BST<T>::in_order(Node<T>* root){
    if (!root){
        return;
    }
    in_order(root -> left);
    cout<<root -> data<<endl;
    in_order(root -> right);
}


//trim() section start from here
template<typename T>
Node<T>* BST<T>::findRoot(Node<T>* root, vector<T> range){
    std::vector<int>::iterator it;
    it = find(range.begin(), range.end(), root->data);
    if (it!=range.end()){
        return root;
    }
    else if (root->data > range[range.size()-1]){
        return findRoot(root->left, range);
    }
    else{
        return findRoot(root -> right, range);
    }
}

template<typename T>
vector<T>* BST<T>::getTrimVec(Node<T>* rootNode, vector<T>* emptyVec, T low, T high){
    if (!rootNode){
        return emptyVec;
    }
    getTrimVec(rootNode -> left, emptyVec, low, high);
    if (rootNode->data >= low && rootNode->data <= high){
        (*emptyVec).push_back(rootNode->data);
    }
    getTrimVec(rootNode -> right, emptyVec, low, high);    
    return emptyVec;
}

template<typename T>
queue<Node<T>*> BST<T>::getSubTree(Node<T>*rootNode){
    queue<Node<T>*> traverseQueue;
    queue<Node<T>*> treeToQueue;
    traverseQueue.push(rootNode);
    while (!traverseQueue.empty())
    {
        Node<T> *curr = traverseQueue.front();
        if (curr->left)
        {
            traverseQueue.push(curr->left);
        }
        if (curr->right)
        {
            traverseQueue.push(curr->right);
        }
        traverseQueue.pop();
        treeToQueue.push(curr);
    }
    return treeToQueue;
}

template<typename T>
void BST<T>::trim(T low, T high){
    //return 1 cai tree trong đó đã có root của cái tree -> base on tree cũ lần lượt add left and right 
    //get the trim vec
    vector<T> *trimVec = new vector<T>();
    trimVec = getTrimVec(root, trimVec, low, high);
    Node<T>* newRoot = findRoot(root, *trimVec);
    //store node cũ vào 1 queue lấy order(level trg tree cũ) rồi check coi head Queue có trg trimVec ko có thì dequeue
    //+ add vào tree mới ko thì chỉ dequeue. Continuous do this -> get đc new Tree
    queue<Node<T>*> originalSubTree = getSubTree(newRoot);
    root = newRoot;
    root -> left = nullptr;
    root -> right = nullptr;
    //pop the root out first
    originalSubTree.pop();
    Node<T>* head;
    while (!originalSubTree.empty()){
        head = originalSubTree.front();
        vector<int>::iterator it;
        it = find((*trimVec).begin(), (*trimVec).end(), head->data);
        if (it!= (*trimVec).end()){
            head -> left = nullptr;
            head -> right = nullptr;
            insert(root, head->data);
        }
        //pop every node that is already inserted
        originalSubTree.pop();
    }
}