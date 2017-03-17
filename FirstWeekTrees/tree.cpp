/*  
Binary tree
    Used to perform alignment from botton to the top
    between the child and the parent.
    1- we need to discover the nodes of the tree
    2- once we arrive to a leaf we have to go UP performing the op
    3- from TOP to BOTTOM replace the alignment structure

Date= 3/2/2017      version=0.01
*/
#include <iostream>
#include <iomanip>  //map setwd()
#include <map>      //map
#include <string>   //to_string
#include <chrono>   //to measure the time

using namespace std;
using namespace chrono;

//**BINARY TREE ** http://www.sourcetricks.com/2011/06/binary-search-trees-in-c.html#.WLkqUWelvsQ
//**DEBUG ** http://cs.baylor.edu/~donahoo/tools/gdb/tutorial.html
//**MAP ** http://www.dreamincode.net/forums/topic/57446-stl-maps/
//**TIME ** http://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c

// A generic tree node class
class Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;

public:
    Node() { 
        key=-1; 
        left=NULL; 
        right=NULL; 
        parent = NULL;
    };
    void setKey(int aKey) { 
        key = aKey; 
    };
    void setLeft(Node* aLeft) {
        left = aLeft; 
    };
    void setRight(Node* aRight) { 
        right = aRight; 
    };
    void setParent(Node* aParent) { 
        parent = aParent; 
    };
    int Key() { 
        return key; 
    };
    Node* Left() { 
        return left; 
    };
    Node* Right() { 
        return right; 
    };
    Node* Parent() { 
        return parent; 
    };
};

// Binary Search Tree class
class Tree {
    Node* root;
public:
    Tree();
    ~Tree();
    Node* Root() { 
        return root; 
    };
    void addNode(int key);
    Node* findNode(int key, Node* parent);
    void walk(Node* node);
    void findLeaves(Node* node);
    void alignmentChildParent(Node* child);
    void deleteNode(int key);
    Node* min(Node* node);
    Node* max(Node* node);
    Node* successor(int key, Node* parent);
    Node* predecessor(int key, Node* parent);
    //Node* getParent(int key, Node* parent);
private:
    void addNode(int key, Node* leaf);
    void freeNode(Node* leaf);
};

// Map to store the operation btwn child&parent
map <string, int> alignments_Map;

// Constructor
Tree::Tree() {
    root = NULL;
}

// Destructor
Tree::~Tree() {
    freeNode(root);
}

// Free the node
void Tree::freeNode(Node* leaf){
    if ( leaf != NULL ) {
        freeNode(leaf->Left());
        freeNode(leaf->Right());
        delete leaf;
    }
}

// Add a node [O(height of tree) on average]
void Tree::addNode(int key){
    // No elements. Add the root
    if ( root == NULL ) {
        //cout << "add root node ... " << key << endl;
        Node* n = new Node();
        n->setKey(key);
        root = n;
    }
    else {
        //cout << "add other node ... " << key << endl;
        addNode(key, root);
    }
}

// Add a node (private)
void Tree::addNode(int key, Node* leaf) {
    if ( key <= leaf->Key() ){
        if ( leaf->Left() != NULL ){
            addNode(key, leaf->Left());
        }
        else {
            Node* n = new Node();
            n->setKey(key);
            n->setParent(leaf);
            leaf->setLeft(n);
        }
    }
    else{
        if ( leaf->Right() != NULL ){
            addNode(key, leaf->Right());
        }
        else {
            Node* n = new Node();
            n->setKey(key);
            n->setParent(leaf);
            leaf->setRight(n);
        }
    }
}

// Find a node [O(height of tree) on average]
Node* Tree::findNode(int key, Node* node){
    if ( node == NULL ){
        return NULL;
    }
    else if ( node->Key() == key ){
        //cout <<"FIND NODE: "<< node->Key()<< endl;
        return node;
    }
    else if ( key <= node->Key() ){
        findNode(key, node->Left());
    }
    else if ( key > node->Key() ){
        findNode(key, node->Right());
    }
    else{
        return NULL;
    }
}

// Find the Leaves
void Tree::findLeaves(Node* node){
    if ( node ){
        if (node->Left()==NULL && node->Right()==NULL){
            cout<< "Node: "<< node->Key() <<" is a leaf."<<endl;
            alignmentChildParent(node);
        }
        findLeaves(node->Left());
        findLeaves(node->Right());
    }
}

// Perform operation between CHILD and PARENT
void Tree::alignmentChildParent(Node* child){
    if(child->Parent()){
        string keyResult;
        keyResult = to_string(child->Key()) +"-"+ to_string(child->Parent()->Key());
        if(!alignments_Map.count(keyResult)){
            int operation = child->Key() + child->Parent()->Key();
            alignments_Map[keyResult] = operation;
            cout<<"*** child-parent: "<<child->Key()<<" - "<<child->Parent()->Key()<<" Sum of keys: " << operation <<endl;
            alignmentChildParent(child->Parent());
        }
    }
}

// Print the tree
void Tree::walk(Node* node){
    if ( node ){
        cout << node->Key() << " ";
        walk(node->Left());
        walk(node->Right());
    }
}

// Find the node with min key
// Traverse the left sub-tree recursively
// till left sub-tree is empty to get min
Node* Tree::min(Node* node){
    if ( node == NULL ){
        return NULL;
    }
    if ( node->Left() ){
        min(node->Left());
    }
    else{
        return node;
    }
}

// Find the node with max key
// Traverse the right sub-tree recursively
// till right sub-tree is empty to get max
Node* Tree::max(Node* node){
    if ( node == NULL ){
        return NULL;
    }
    if ( node->Right() ){
        max(node->Right());
    }
    else{
        return node;
    }
}

//Find successor to a node
//Find the node, get the node with max value
//for the right sub-tree to get the successor
Node* Tree::successor(int key, Node *node){
    Node* thisKey = findNode(key, node);
    if ( thisKey ){
        return max(thisKey->Right());
    }
}

//Find predecessor to a node
//Find the node, get the node with max value
//for the left sub-tree to get the predecessor
Node* Tree::predecessor(int key, Node *node){
    Node* thisKey = findNode(key, node);
    if ( thisKey ){
        return max(thisKey->Left());
    }
}

// Delete a node
// (1) If leaf just delete
// (2) If only one child delete this node and replace
// with the child
// (3) If 2 children. Find the predecessor (or successor).
// Delete the predecessor (or successor). Replace the
// node to be deleted with the predecessor (or successor).
void Tree::deleteNode(int key){
    // Find the node.
    Node* thisKey = findNode(key, root);

    // (1)
    if ( thisKey->Left() == NULL && thisKey->Right() == NULL ){
        if ( thisKey->Key() > thisKey->Parent()->Key() ){
            thisKey->Parent()->setRight(NULL);
        }
        else{
            thisKey->Parent()->setLeft(NULL);
        }
        delete thisKey;
    }

    // (2)
    if ( thisKey->Left() == NULL && thisKey->Right() != NULL ){
        if ( thisKey->Key() > thisKey->Parent()->Key() ){
            thisKey->Parent()->setRight(thisKey->Right());
        }
        else{
            thisKey->Parent()->setLeft(thisKey->Right());
        }
        delete thisKey;
    }
    if ( thisKey->Left() != NULL && thisKey->Right() == NULL ){
        if ( thisKey->Key() > thisKey->Parent()->Key() ){
            thisKey->Parent()->setRight(thisKey->Left());
        }
        else{
            thisKey->Parent()->setLeft(thisKey->Left());
        }
        delete thisKey;
    }

    // (3)
    if ( thisKey->Left() != NULL && thisKey->Right() != NULL ){
        Node* sub = predecessor(thisKey->Key(), thisKey);
        if ( sub == NULL ){
            sub = successor(thisKey->Key(), thisKey);        
        }
        if ( sub->Parent()->Key() <= sub->Key() ){
            sub->Parent()->setRight(sub->Right());
        }
        else{
            sub->Parent()->setLeft(sub->Left());
        }
        thisKey->setKey(sub->Key());
        delete sub;
    }
}

void printMap(map <string,int> alignmentMap){
    // Output the size
    cout << "\n\tTotal size: " << alignmentMap.size() << endl; 
    //Create an iterator
    map <string, int>::iterator it;
    for (it = alignmentMap.begin(); it != alignmentMap.end(); ++it)
        //Output first (which is the string) and second (which is the int)
        cout << setw(10) << it->first << setw(5) << it->second << endl;
    cout << endl; 
}

// Test main program
int main() {
    high_resolution_clock::time_point createTreeIni = high_resolution_clock::now();
    Tree* tree = new Tree();
    // Add nodes
    tree->addNode(300);
    tree->addNode(100);
    tree->addNode(200);
    tree->addNode(400);
    tree->addNode(500);
    tree->addNode(50);
    tree->addNode(350);
    high_resolution_clock::time_point createTreeEnd = high_resolution_clock::now();
    auto timeTree=duration_cast<microseconds>( createTreeEnd - createTreeIni).count();

    // Traverse the tree
    cout<< "Walk around the tree: ";
    tree->walk(tree->Root());
    cout << endl;

    // Find Leaves & sum pairs
    cout<< "***Find the leaves*** "<<endl;
    high_resolution_clock::time_point timeLeaveIni = high_resolution_clock::now();
    tree->findLeaves(tree->Root());
    high_resolution_clock::time_point timeLeaveEnd = high_resolution_clock::now();
    auto timeLeave=duration_cast<microseconds>( timeLeaveEnd - timeLeaveIni).count();

    //print the sum of pairs
    printMap(alignments_Map);
    cout <<"Time for createTree (microSec): "<< timeTree <<endl;
    cout <<"Time for findLeave (microSec): "<< timeLeave <<endl;
    
    //step3-- From TOP to BOTTOM


    //delete & clean elements
    delete tree;
    alignments_Map.clear();
    return 0;
}
