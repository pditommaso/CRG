/*  
Binary tree
    Used to perform alignment from botton to the top
    between the child and the parent.
    1- we need to discover the nodes of the tree
    2- once we arrive to a leaf we have to go UP performing the op
    3- from TOP to BOTTOM replace the alignment structure

Date= 3/8/2017      version=0.03
Performed to introduce the sequence as String
*/
#include <iostream>
#include <iomanip>  //map setwd()
#include <map>      //map
#include <string>   //to_string
#include <fstream>  //I/O file
#include <chrono>   //to measure the time
#include <vector>   //vector
#include <algorithm>    // std::sort

using namespace std;
using namespace chrono;

//**BINARY TREE ** http://www.sourcetricks.com/2011/06/binary-search-trees-in-c.html#.WLkqUWelvsQ
//**DEBUG ** http://cs.baylor.edu/~donahoo/tools/gdb/tutorial.html
//**MAP ** http://www.dreamincode.net/forums/topic/57446-stl-maps/
//**TIME ** http://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c

enum Direction_Enum{
    left_t,
    right_t
};
enum OpDirection_Enum{
    leftLeft_t,
    rightLeft_t,
    leftRight_t,
    rightRight_t
};
// A generic tree node class
class Node {
    int sequenceID;
    string sequence;
    Node* left;
    Node* right;
    Node* parent;
    bool leave;

public:
    Node() { 
        sequenceID=-1; 
        sequence="";
        left=NULL;
        right=NULL; 
        parent = NULL;
        leave = NULL;
    };
    void setSequenceID(int aSequenceID) { 
        sequenceID = aSequenceID; 
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
    int SequenceID() { 
        return sequenceID; 
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
    void addRoot(int sequenceID, string sequence);
    void addNode(int sequenceID, string sequence, Node* parent, Direction_Enum direction);
    
    void mountTree(Tree* tree,vector<string> seqName, vector<string> seqString);
    void walk(Node* node);
    vector<Node*> findLeaves(Node* node);
    vector<Node*> getGroupNodes(Node* node,int bucketSize);
    void findAllMSA(Node* node, vector<Node*> &vectorLeaves, int bucketSize);
private:
    void freeNode(Node* leaf);
    //void addNode(Node* child, Node* parent);
    Node* newNode(int sequenceID,string sequence);
    Node* getNode(Node* node, Direction_Enum direction);
    void removeLeaves(vector<Node*> msaLeaves, vector<Node*> &leaves);
    void printVector(vector<Node*> vector);
    void printNode(Node* node);
    vector<Node*> getNextLevel(vector<Node*> parentsList/*,vector<Node*> &nodesToMSA*/ );
};

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
void Tree::addRoot(int sequenceID, string sequence){
    if ( root == NULL ) {
        //cout << "add root node ... " << key << endl;
        Node* node = new Node();
        node->setSequenceID(sequenceID);
        node->setSequence(sequence);
        node->setLeave(true);
        root = node;
    }else{
        cout<<"Root already exist"<<endl;
    }
}
// Add a node [O(height of tree) on average]
void Tree::addNode(int sequenceID, string sequence, Node* parent, Direction_Enum direction){
    // No elements. Add the root
    if ( root == NULL ) {
        //cout << "add root node ... " << key << endl;
        Node* node = new Node();
        node->setSequenceID(sequenceID);
        node->setSequence(sequence);
        node->setLeave(true);
        root = node;
    }
    else {
        //cout << "add other node ... " << key << endl;
        Node* node = new Node();
        node->setSequenceID(sequenceID);
        node->setSequence(sequence);
        node->setParent(parent);
        node->setLeave(true);
        
        parent->setLeave(false);
        if(direction == left_t){
            parent->setLeft(node);
        }else{
            parent->setRight(node);
        }
    }
}
Node* newNode(int sequenceID,string sequence){
    Node* node = new Node();
    node->setSequenceID(sequenceID);
    node->setSequence(sequence);
    node->setLeave(true);

    return node;
}
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

vector<Node*> Tree::getNextLevel(vector<Node*> parentsList/*,vector<Node*> &nodesToMSA*/ ){
	vector<Node*> parentsVector;
	for (auto &parent : parentsList){
		/*nodesToMSA.push_back(getNode(parent,left_t));
		nodesToMSA.push_back(getNode(parent,right_t));*/

		parentsVector.push_back(getNode(parent,left_t));
		parentsVector.push_back(getNode(parent,right_t));		
	}
	cout<<"getNextLevel vector"<<endl;
	printVector(parentsVector);
	return parentsVector;
}
/*
Public method
This function receive a node, and it will print out the set of nodes to perform the MSA
*/
vector<Node*> Tree::getGroupNodes(Node* node, int bucketSize ){
    vector<Node*> bucketVector;
    vector<Node*> sonsBucket;
    vector<Node*> auxVector;

    bucketVector.push_back(node);
        cout<<"getGroupNodes - bucketVector"<<endl;
        cout<<"***** ";
        printVector(bucketVector);
        cout<<"////"<<endl;
    if(bucketVector.size() < bucketSize){
        auxVector=getNextLevel(bucketVector);
        bucketVector.insert( bucketVector.end(), auxVector.begin(), auxVector.end() );

        cout<<"if"<<endl;
        cout<<"auxVector:  "<<endl;
        printVector(auxVector);
        cout<<"bucketVectorBIS:  "<<endl;
        printVector(bucketVector);

        cout<<"fi"<<endl;
        for (auto &auxNode : auxVector){
            cout<<"GO FOR SONS: ";
            printNode(auxNode);
            sonsBucket = getGroupNodes(auxNode, bucketSize);
            bucketVector.insert( bucketVector.end(), sonsBucket.begin(), sonsBucket.end() );
            cout<<"inside loop SONS:"<<endl;
            printVector(bucketVector);
        }
    }
    return bucketVector;


	/*cout<< "bucketSize: "<<bucketSize<<" node: "<<node->SequenceID()<<endl;
	vector<Node*> parents;
    vector<Node*> nodesToMSA;


    nodesToMSA.push_back(node);
    parents.push_back(node);

    cout<<"getGroup"<<endl;
    printVector(parents);
    cout<<"----"<<endl;
    parents=getNextLevel(parents, nodesToMSA);
    getNextLevel(parents, nodesToMSA);
    cout<<"****"<<endl;*/

    /*nodesToMSA.push_back(node);
    if (!node->isLeave()&& nodesToMSA.size() < bucketSize){
    //FIRST LEVEL NODES
    	//LR
    		nodesToMSA.push_back(getNode(node,left_t));
    		nodesToMSA.push_back(getNode(node,right_t));

    //SECOND LEVEL NODES
    	//RR
    		nodesToMSA.push_back(getNode(node->Left(),right_t));
    		nodesToMSA.push_back(getNode(node->Right(),right_t));
    	//LL
    		nodesToMSA.push_back(getNode(node->Left(),left_t));
    		nodesToMSA.push_back(getNode(node->Right(),left_t));


        //cout<<"NodeToMSA vector_getGroupNodes"<<endl;
        //printVector(nodesToMSA);
    }else{
        getGroupNodes(nodesToMSA,bucketSize);
        
    }*/
    //return nodesToMSA;
}
/*
                process (Node X)
                    -start at Node X
                    -go down till N - record the sequences
                    -keep going down 2N
                                -if the 2N contains ALL the leaf of X -> align the 2N
                                 Else align the N and process the remaining nodes   
*/
/*
Private method.
The input is a node and an integer (direction). 
And we will return a descenden another node situated in the direction indicated
*/
Node* Tree::getNode(Node* node, Direction_Enum direction){                        //leftLeft_t,   0
    switch ( direction ) {                                                          //rightLeft_t,  1
        case left_t:                                                            //leftRight_t,  2
            if (node->Left()!=NULL){                                        //rightRight_t  3
                return node->Left();
            }
            break;
        case right_t:
            if (node->Right()!=NULL){
                return node->Right();
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
void Tree::findAllMSA(Node* node, vector<Node*> &leavesVector, int bucketSize){
//cout<<"**********************node-KEY "<<node->SequenceID()<<endl;
    vector <Node*> mSAVector;

    if (!leavesVector.empty()){             //we still have leaves
        mSAVector=getGroupNodes(node, bucketSize);

        if(!mSAVector.empty()) {            //we have more deep
            /*cout<< "MSA Bucket from node "<<node->Sequence()<<" ("<<node->SequenceID()<<")"<<endl;
            printVector(mSAVector);
            for(int i=0; i<mSAVector.size(); i++){
                //cout << mSAVector[i]->Sequence() << " ("<<mSAVector[i]->SequenceID()<<")"<<endl;
                findAllMSA(mSAVector[i],leavesVector, bucketSize);
            }
            cout<<endl;*/
            
            //perform the MSA alignment

            //delete from LeavesVector
            removeLeaves(mSAVector,leavesVector);

            //recursivity L/R
            //findAllMSA(node->Left(),leavesVector);
            //findAllMSA(node->Right(),leavesVector);
        }

    }/*else{}*/
    if(!leavesVector.empty()){
        //cout<<"Leaves Remaining: ";
        //printVector(leavesVector);
    }else{
        //cout<<"Finished with EXIT :)"<<endl;
    }
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
}

// Print the tree
void Tree::walk(Node* node){
    if ( node ){
        printNode(node);
        walk(node->Left());
        walk(node->Right());
    }
}

void Tree::printVector(vector<Node*> vector){
    for(int i=0; i<vector.size(); i++){
        printNode(vector[i]);
    }
    cout<<endl;
}
void Tree::printNode(Node* node){
    if (node->Parent()!=NULL){
        cout << node->SequenceID() << " - "<<node->Sequence()<<" - Parent: "<<node->Parent()->SequenceID()<<" - "<<node->isLeave()<<endl;
    }else{
        cout << node->SequenceID() << " - "<<node->Sequence()<<" - Parent: ROOT - "<<node->isLeave()<<endl;
    }
}
/*void Tree::mountTree(Tree* tree, vector<string> seqName, vector<string> seqString){
    int key=0;
    for(int i=0; i<seqString.size(); i+2){
        Node* node1= new newNode(seqName[i],seqString[i]);
        Node* node2= new newNode(seqName[i+1],seqString[i+1]);
        
        if (seqString[i].size()<=seqString[i+1].size()){
            Node* parent = new newNode(seqName[i+1],seqString[i+1]);
            
            parent->setLeft(node1);
            parent->setRight(node2);
        }
    }
}    */
// Test main program
int main() {
    Tree* tree = new Tree();
    int bucketSize= 3;

    // Add nodes
	tree->addRoot(0,"Seq_07");

    tree->addNode(1,"Seq_07",tree->Root(),left_t);
    tree->addNode(2,"Seq_10",tree->Root(),right_t);

    tree->addNode(3,"Seq_03",tree->Root()->Left(),left_t);
    tree->addNode(4,"Seq_07",tree->Root()->Left(),right_t);
    tree->addNode(5,"Seq_10",tree->Root()->Right(),left_t);
    tree->addNode(6,"Seq_13",tree->Root()->Right(),right_t);

    tree->addNode(7,"Seq_02",tree->Root()->Left()->Left(),left_t);
    tree->addNode(8,"Seq_03",tree->Root()->Left()->Left(),right_t);
    tree->addNode(9,"Seq_05",tree->Root()->Left()->Right(),left_t);
    tree->addNode(10,"Seq_07",tree->Root()->Left()->Right(),right_t);
    tree->addNode(11,"Seq_10",tree->Root()->Right()->Left(),left_t);
    tree->addNode(12,"Seq_12",tree->Root()->Right()->Left(),right_t);
    tree->addNode(13,"Seq_13",tree->Root()->Right()->Right(),left_t);
    tree->addNode(14,"Seq_15",tree->Root()->Right()->Right(),right_t);

    /*tree->addNode(16,"Seq_01",tree->Root()->Left()->Left()->Left(),left_t);
    tree->addNode(17,"Seq_02",tree->Root()->Left()->Left()->Left(),right_t);
    tree->addNode(18,"Seq_03",tree->Root()->Left()->Left()->Right(),left_t);
    tree->addNode(19,"Seq_04",tree->Root()->Left()->Left()->Right(),right_t);
    tree->addNode(20,"Seq_05",tree->Root()->Left()->Right()->Left(),left_t);
    tree->addNode(21,"Seq_06",tree->Root()->Left()->Right()->Left(),right_t);
    tree->addNode(22,"Seq_07",tree->Root()->Left()->Right()->Right(),left_t);
    tree->addNode(23,"Seq_08",tree->Root()->Left()->Right()->Right(),right_t);
    tree->addNode(24,"Seq_09",tree->Root()->Right()->Left()->Left(),left_t);
    tree->addNode(25,"Seq_10",tree->Root()->Right()->Left()->Left(),right_t);
    tree->addNode(26,"Seq_11",tree->Root()->Right()->Left()->Right(),left_t);
    tree->addNode(27,"Seq_12",tree->Root()->Right()->Left()->Right(),right_t);
    tree->addNode(28,"Seq_13",tree->Root()->Right()->Right()->Left(),left_t);
    tree->addNode(29,"Seq_14",tree->Root()->Right()->Right()->Left(),right_t);
    tree->addNode(30,"Seq_15",tree->Root()->Right()->Right()->Right(),left_t);
    tree->addNode(31,"Seq_16",tree->Root()->Right()->Right()->Right(),right_t);*/

    // Traverse the tree
    /*cout<< "Walk around the tree: "<<endl;
    tree->walk(tree->Root());
    cout << endl;*/
    
    // Find Leaves
    //cout<< "***Find the leaves*** "<<endl;
    high_resolution_clock::time_point timeLeaveIni = high_resolution_clock::now();

    vector<Node*> resultLeaves = tree->findLeaves(tree->Root());

    high_resolution_clock::time_point timeLeaveEnd = high_resolution_clock::now();
    auto timeLeave=duration_cast<microseconds>( timeLeaveEnd - timeLeaveIni).count();

    /*cout<<"Leaves: ";
    for(int i=0; i<resultLeaves.size(); i++){
        cout<<resultLeaves[i]->Sequence()<<" ("<<resultLeaves[i]->SequenceID()<<") - ";
    }cout<<endl;*/

    cout <<"Time for findLeave (microSec): "<< timeLeave <<endl;
    
    tree->findAllMSA(tree->Root(),resultLeaves, bucketSize);


    //delete & clean elements
    delete tree;
    return 0;
}
