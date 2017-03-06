/*  
Trie tree
    Used to perform alignment from botton to the top
    between the child and the parent.
    1- we need to discover the nodes of the tree
    2- once we arrive to a leaf we have to go UP performing the op
    3- from TOP to BOTTOM replace the alignment structure

Date= 6/2/2017      version=0.03
New type of tree more adecuated for our purpose
*/
#include <iostream>
#include <iomanip>  //map setwd()
#include <map>      //map
#include <string>   //to_string
#include <chrono>   //to measure the time
#include <vector>	//vector
#include <fstream>	//I/O file

using namespace std;
using namespace chrono;
// A generic tree node class
class Node {
    int key;
    string sequence;
    Node* parent;
    vector<Node*> child; //Node** child_ptr; //use a vector of Nodes ??
    bool leaf;

public:
    Node() { 
        key=-1; 
        sequence=""; 
        parent = NULL;
        leaf = NULL;
    };
    void setKey(int aKey) { 
        key = aKey; 
    };
    void setSequence(string aSequence){
    	sequence = aSequence;
    };
    void setParent (Node* aParent){
    	parent = aParent;
    };
    void setChild(vector<Node*> aChild){
    	child = aChild;
    };
    void setLeaf(bool aLeaf){
    	leaf = aLeaf;
    };
    int Key() { 
        return key; 
    };
    string Sequence(){
    	return sequence;
    };
    Node* Parent(){
    	return parent;
    }
    vector<Node*> Child(){
    	return child;
    };
    bool Leaf(){
    	return leaf;
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
    void addNode(string sequence, int key);
    void addNode (string sequence, int key, Node* leaf);
    Node* findNode(string sequence, Node* node);
    void walk(Node* node);
    void printNode(Node* node);
private:
	void freeNode(Node* leaf);
	void printVectorChild(Node* node);
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
		std::vector<Node*>::iterator iter, end;
		for(iter = leaf->Child().begin(), end = leaf->Child().end() ; iter != end; ++iter) {
			freeNode(*iter);
		}
        delete leaf;
    }
}
void Tree::addNode(string sequence,int key){
    // No elements. Add the root
    if ( root == NULL ) {
        cout<<"ADDED THE ROOT: "<<sequence<< " - "<<key<<" "<<sequence.length()<<endl;
	    Node* node = new Node();
	    node->setKey(key);
	    //node->setParent(NULL);
	    node->setSequence(sequence);
	    node->setLeaf(true);
	    root = node;
    }
    else {
        addNode(sequence,key, root);
    }
}
//private metohd
void Tree::addNode(string sequence, int key, Node* leaf){
	cout<<"FIRST LAYER : "<<sequence<< " - "<<key<<" - "<<sequence.length()<<" PARENT: "<< leaf->Key()<<endl;

	//create the new node, it will be a leaf
	Node* node = new Node();
	node->setKey(key);
	node-> setParent(leaf);
	node->setSequence(sequence);
	node->setLeaf(true);
	//parent is not a leaf now
	leaf->setLeaf(false);
	//the parent will have a pointer to the new node
	//and set back the new vector with the added value
	vector<Node*> tmp_child= leaf->Child();
	tmp_child.push_back(node);
	leaf->setChild(tmp_child);
	//cout<<"addNode: "<<endl;
	//printVectorChild(leaf);

}
void Tree::printVectorChild(Node* node){
	cout<<"Sons of: "<<node->Key()<<endl;
	for(int i=0; i<node->Child().size(); i++){
		cout<<node->Child()[i]->Sequence()<<endl;
	}
}
// Print the tree
void Tree::walk(Node* node){
    if ( node ){
    	cout<<"***walk for: ";
    	printNode(node);

        vector<Node*>::iterator iter, end;
		for(int i=0; i<node->Child().size(); i++){
			//cout<<node->Child()[i]->Sequence()<<endl;
			walk(node->Child()[i]);
		}
    }
}
void Tree::printNode(Node* node){
	cout<<"Key: "<<node->Key()<<" - "<<node->Sequence()<<endl;
}

int main() {
    Tree* tree = new Tree();
    int n, m;
    string dummySequence;
    vector<string> listSequence;
    n=10;
    m=3;

//read the sequences from txt
    std::ifstream infile("dummyTest.txt");
    while (infile >> dummySequence ){
	    listSequence.push_back(dummySequence);
	}
//########## Add nodes
//sort the sequences by lenght
    // the longest seq will be the root
    int tmp_index=0;
	tree->addNode(listSequence[tmp_index],tmp_index);
	tmp_index++;

//insert the first N sequences in the first level
	for( int i=1; i <= n; i++ ) {
		tree->addNode(listSequence[tmp_index],tmp_index);
		tmp_index++;
		//node_tmp= findNode(tmp_index, tree->Root()); //save the *Node durinf each iteration
//insert grouping by M elements
		for( int j=1; j < m; j++ ) {	//is m-1 because it will be the parent+the m-1 child = m
			//tree->addNode(listSequence[tmp_index],tmp_index, node_tmp);
			tmp_index++;
	   	}
   	};

//Print tree
	cout<< "Walk around the tree: "<<endl;
    tree->walk(tree->Root());
    cout << endl;

//delete Tree
    //segmentation fault
    cout<< "Delete Tree: "<<endl;
    //delete tree;

    return 0;
}