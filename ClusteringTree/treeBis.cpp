/*  
Binary tree
    Used to perform alignment from botton to the top
    between the child and the parent.
    1- we need to discover the nodes of the tree
    2- once we arrive to a leaf we have to go UP performing the op
    3- from TOP to BOTTOM replace the alignment structure

Date= 3/2/2017      version=0.02
Performed to introduce the sequence as String
*/
#include <iostream>
#include <iomanip>  //map setwd()
#include <map>      //map
#include <string>   //to_string
#include <chrono>   //to measure the time
#include <vector>   //vector
#include <algorithm>    // std::sort

using namespace std;
using namespace chrono;

//**BINARY TREE ** http://www.sourcetricks.com/2011/06/binary-search-trees-in-c.html#.WLkqUWelvsQ
//**DEBUG ** http://cs.baylor.edu/~donahoo/tools/gdb/tutorial.html
//**MAP ** http://www.dreamincode.net/forums/topic/57446-stl-maps/
//**TIME ** http://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c

// A generic tree node class
class Node {
    int key;
    string sequence;
    Node* left;
    Node* right;
    Node* parent;
    bool leave;

public:
    Node() { 
        key=-1; 
        left=NULL;
        sequence="";    //error with NULL
        right=NULL; 
        parent = NULL;
    };
    void setKey(int aKey) { 
        key = aKey; 
    };
    void setSequence(string aSequence) { 
        sequence = aSequence; 
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
    void setLeave(bool aLeave){
        leave = aLeave;
    }
    int Key() { 
        return key; 
    };
    string Sequence() { 
        return sequence; 
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
    bool isLeave(){
        return leave;
    }
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
    void addNode(int key, string sequence);
    Node* findNode(int key, Node* parent);
    //Node* findSequence(string sequence, Node* parent);
    void walk(Node* node);
    vector<Node*> findLeaves(Node* node);
    //void alignmentChildParent(Node* child);
    //void deleteNode(int key);
    //Node* min(Node* node);
    //Node* max(Node* node);
    //Node* successor(int key, Node* parent);
    //Node* predecessor(int key, Node* parent);
    vector<Node*> getGroupNodes(Node* node);
    void findAllMSA(Node* node, vector<Node*> &vectorLeaves);
private:
    void addNode(int key,string sequence, Node* leaf);
    void freeNode(Node* leaf);
    Node* getNode(Node* node, int direction);
    void removeLeaves(vector<Node*> msaLeaves, vector<Node*> &leaves);
};

// Map to store the operation btwn child&parent
map <string, string> alignments_Map;

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
void Tree::addNode(int key, string sequence){
    // No elements. Add the root
    if ( root == NULL ) {
        //cout << "add root node ... " << key << endl;
        Node* n = new Node();
        n->setKey(key);
        n->setSequence(sequence);
        n->setLeave(true);
        root = n;
    }
    else {
        //cout << "add other node ... " << key << endl;
        addNode(key, sequence, root);
    }
}

// Add a node (private)
void Tree::addNode(int key, string sequence, Node* leaf) {
    if ( key <= leaf->Key() ){
        if ( leaf->Left() != NULL ){
            addNode(key, sequence, leaf->Left());
        }
        else {
            Node* n = new Node();
            n->setKey(key);
            n-> setSequence(sequence);
            n->setParent(leaf);
            leaf->setLeft(n);
            n->setLeave(true);
            leaf->setLeave(false);
        }
    }
    else{
        if ( leaf->Right() != NULL ){
            addNode(key, sequence, leaf->Right());
        }
        else {
            Node* n = new Node();
            n->setKey(key);
            n-> setSequence(sequence);
            n->setParent(leaf);
            leaf->setRight(n);
            n->setLeave(true);
            leaf->setLeave(false);
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

/*Node* Tree::findSequence(string sequence, Node* node){
    if ( node == NULL ){
        return NULL;
    }
    else if ( node->Sequence() == sequence ){
        //cout <<"FIND NODE: "<< node->Key()<< endl;
        return node;
    }
    //TODO 
    //How to search recursively the sequence :( 
    //How will be sorted the sequences in the tree??
    else{
        return NULL;
    }
}*/

/*
Public method
The input is the "root" of the tree, and we will receive a vector<Node*> with all the leaves
*/ 
vector<Node*> Tree::findLeaves(Node* node){
    vector <Node*> leaves;
    vector <Node*> leavesLeft;
    vector <Node*> leavesRight;
    if ( node ){
        //if (node->Left()==NULL && node->Right()==NULL){
        if (node->isLeave()){
            //cout<< "Node: "<< node->Key() <<" is a leaf."<<endl;
            leaves.push_back(node);
        }
        //recursvity L/R
        leavesLeft=findLeaves(node->Left());
        leavesRight=findLeaves(node->Right());

        //merged all the vectors
        leaves.insert( leaves.end(), leavesLeft.begin(), leavesLeft.end() );
        leaves.insert( leaves.end(), leavesRight.begin(), leavesRight.end() );

        //TODO remove duplicates?? Tree dont have to have it.
    }
    return leaves;
}
/*
Public method
This function receive a node, and it will print out the set of nodes to perform the MSA
*/
vector<Node*> Tree::getGroupNodes(Node* node){
    vector<Node*> nodesToMSA;
    if (!node->isLeave() && 
            node->Left()!=NULL && node->Right()!=NULL &&
            !node->Left()->isLeave() && !node->Right()->isLeave()){
        //vector<Node*> nodesToMSA;
        nodesToMSA.push_back(node);                 //beginning node
        nodesToMSA.push_back(getNode(node,0));      //LR
        nodesToMSA.push_back(getNode(node,1));      //RR
        nodesToMSA.push_back(getNode(node,2));      //LL

        /*  //Print the vector
        cout<< "NodesToMSA from key "<<node->Key()<<" - "<< node->Sequence()<<" size: "<<nodesToMSA.size()<<endl;
        for(int i=0; i<nodesToMSA.size(); i++){
           cout<<"Node: "<< nodesToMSA[i]->Key()<<" - "<<nodesToMSA[i]->Sequence()<<endl;
        }*/
    }else{
        //cout<<"The node: "<<node->Key()<<" has not enough deep"<<endl;
    }
    return nodesToMSA;
    //try to reach 2n nodes
    //if this is not posible, the set will be only 3 nodes
}

/*
Private method.
The input is a node and an integer (direction). 
And we will return another node situated in the direction indicated
*/
Node* Tree::getNode(Node* node, int direction){    //TODO use ENUM
    switch ( direction ) {
        case 0:
            if (node->Left()!=NULL && node->Left()->Right()!=NULL){
                return node->Left()->Right();
            }
            break;
        case 1:
            if (node->Right()->Right()!=NULL){
                return node->Right()->Right();
            }
            break;
        case 2:
            if (node->Left()->Left()!=NULL){
                return node->Left()->Left();
            }
            break;
        }
}
/* 
Private method 
Used to sort a vector using the KEY value of the nodes
*/
bool sortVector (Node* i,Node* j) { return (i->Sequence()<j->Sequence()); }

/*
*/
void Tree::findAllMSA(Node* node, vector<Node*> &leavesVector){
cout<<"**********************node-KEY "<<node->Key()<<endl;
    vector <Node*> mSAVector;
    if (!leavesVector.empty()){             //we still have leaves
        mSAVector=getGroupNodes(node);
        if(!mSAVector.empty()) {            //we have more deep
            cout<< "mSAVector from key "<<node->Key()<<endl<<"*** ";
            for(int i=0; i<mSAVector.size(); i++){
                cout/*<<" >> Node: "<< mSAVector[i]->Key()<<" - "*/<<mSAVector[i]->Sequence()<<endl;
            }cout<<endl;
            
            //perform the MSA alignment

            //delete from LeavesVector
            removeLeaves(mSAVector,leavesVector);

            //recursivity L/R
            findAllMSA(node->Left(),leavesVector);
            findAllMSA(node->Right(),leavesVector);
        }

    }/*else{}*/
    if(!leavesVector.empty()){
        /*cout<<"Leaves Remaining: ";
        for(int i=0; i<leavesVector.size(); i++){
            cout<<leavesVector[i]->Key()<<" - ";
        }cout<<endl;*/
    }else{cout<<"Finished with EXIT :)"<<endl;}
}
/*
Private method
Receive by REFERENCE 2 vectors, and will substract the common elements to the leavesVector
*/
void Tree::removeLeaves(vector<Node*> mSAVector, vector<Node*> &leavesVector){
        //inverse deletion to be able to do "raw" on the vector
        //http://stackoverflow.com/questions/8628951/remove-elements-of-a-vector-inside-the-loop
        sort (mSAVector.begin(), mSAVector.end(), sortVector);
        sort (leavesVector.begin(), leavesVector.end(), sortVector);
        for(int i=0; i<mSAVector.size(); i++){
            if(!leavesVector.empty()) {
                for(int j = leavesVector.size() - 1; j >= 0; j--) {
                    if(leavesVector.at(j)->Sequence() == mSAVector[i]->Sequence()) {
                        leavesVector.erase( leavesVector.begin() + j ); 
                    }
                }
            }
        }
        /*cout<<endl<< "------Remaining AFTER delete: "<<endl;
        for(int i=0; i<leavesVector.size(); i++){
            cout<<"Node: "<< leavesVector[i]->Key()<<" - "<<leavesVector[i]->Sequence()<<endl;
        }*/
}
// Perform operation between CHILD and PARENT
/*void Tree::alignmentChildParent(Node* child){
    if(child->Parent()){
        string keyResult;
        keyResult = to_string(child->Key()) +"-"+ to_string(child->Parent()->Key());
        if(!alignments_Map.count(keyResult)){
            cout<<"child "<<child->Key()<<" parent: "<<child->Parent()->Key()<<endl;
            //operation2Nodes(child, child);
            string operation="";
            //child->Sequence() +"-"+ child->Parent()->Sequence();
            alignments_Map[keyResult] = operation;
            //cout<<"*** child-parent: "<<child->Key()<<" - "<<child->Parent()->Key()<<" Sum of Sequences: " << operation <<endl;
            alignmentChildParent(child->Parent());
        }
    }
}*/

// Print the tree
void Tree::walk(Node* node){
    if ( node ){
        cout << node->Key() << " - "<<node->Sequence()<<" -"<<node->isLeave()<<endl;
        walk(node->Left());
        walk(node->Right());
    }
}

void printMap(map <string,string> alignmentMap){
    // Output the size
    cout << "\n\tTotal size: " << alignmentMap.size() << endl; 
    //Create an iterator
    map <string, string>::iterator it;
    for (it = alignmentMap.begin(); it != alignmentMap.end(); ++it)
        //Output first (which is the string) and second (which is the int)
        cout << setw(7) << it->first << setw(20) << it->second << endl;
    cout << endl; 
}

// Test main program
int main() {
    Tree* tree = new Tree();

    // Add nodes
           tree->addNode(8,"Seq_07");

    tree->addNode(4,"Seq_03");
    tree->addNode(12,"Seq_07");

    tree->addNode(2,"Seq_02");
    tree->addNode(6,"Seq_03");
    tree->addNode(10,"Seq_05");
    tree->addNode(14,"Seq_07");

    tree->addNode(1,"Seq_01");
    tree->addNode(3,"Seq_02");
    tree->addNode(5,"Seq_03");
    tree->addNode(7,"Seq_04");
    tree->addNode(9,"Seq_05");
    tree->addNode(11,"Seq_06");
    tree->addNode(13,"Seq_07");
    tree->addNode(15,"Seq_08");
    // Traverse the tree
    /*
    cout<< "Walk around the tree: "<<endl;
    tree->walk(tree->Root());
    cout << endl;
    */


    // Find Leaves & sum pairs
    //cout<< "***Find the leaves*** "<<endl;
    high_resolution_clock::time_point timeLeaveIni = high_resolution_clock::now();

    vector<Node*> resultLeaves = tree->findLeaves(tree->Root());

    high_resolution_clock::time_point timeLeaveEnd = high_resolution_clock::now();
    auto timeLeave=duration_cast<microseconds>( timeLeaveEnd - timeLeaveIni).count();

    cout<<"Leaves: ";
    for(int i=0; i<resultLeaves.size(); i++){
        cout<<resultLeaves[i]->Key()<<" - ";
    }cout<<endl;

    cout <<"Time for findLeave (microSec): "<< timeLeave <<endl;
    
    tree->findAllMSA(tree->Root(),resultLeaves);


    //delete & clean elements
    delete tree;
    alignments_Map.clear();
    return 0;
}
