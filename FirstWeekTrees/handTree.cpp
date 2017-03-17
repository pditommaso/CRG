#include <iostream>
#include <chrono>   //to measure the time
#include <vector>	//vector
#include <fstream>	//I/O file
#include <algorithm>    // std::find

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

// Trie Tree class
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
    //Node* findNode(string sequence, Node* node);
    Node* findNode(int key, Node* node);
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
void Tree::freeNode(Node* node){
    if ( node != NULL ) {
		for(int i=0; i<node->Child().size(); i++){
			freeNode(node->Child()[i]);
		}
        delete node;
    }
}

void Tree::addNode(string sequence,int key){
    // No elements. Add the root
    if ( root == NULL ) {
        //cout<<"ADDED THE ROOT: "<<sequence<< " - "<<key<<endl;
	    Node* node = new Node();
	    node->setKey(key);
	    node->setParent(NULL);
	    node->setSequence(sequence);
	    node->setLeaf(true);
	    root = node;
    }
    else {
        addNode(sequence,key, root);
    }
}

void Tree::addNode(string sequence, int key, Node* leaf){
	//cout<<"FIRST LAYER : "<<sequence<< " - "<<key<<" PARENT: "<< leaf->Key()<<endl;
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
	//printVectorChild(leaf);
}
/*Node* findNode(string sequence, Node* node){
	//TODO ?is it possible to searcha node by the sequence?
}*/
Node* Tree::findNode(int key, Node* node){
	//cout<<"Find Node: "<<key<<" - "<< node->Key()<<endl;
	if(node->Key() == key){
		return node;
	}else {
		//check if it's a child
		for(int i=0; i<node->Child().size(); i++){
			if(node->Child()[i]->Key()== key){
				return node->Child()[i];
			}
			if(node->Child()[i]->Key() > key){ 	//nos lo hemos pasado
				return findNode(key,node->Child()[i-1]);
			}
		}
		return NULL;
	}
}
void Tree::printVectorChild(Node* node){
	cout<<"Sons of: "<<node->Key()<<endl;
	for(int i=0; i<node->Child().size(); i++){
		printNode(node->Child()[i]);
		//cout<<node->Child()[i]->Sequence()<<endl;
	}
}

// Print the tree
void Tree::walk(Node* node){
    if ( node ){
    	cout<<"***walk for: ";
    	printNode(node);
		for(int i=0; i<node->Child().size(); i++){
			walk(node->Child()[i]);
		}
    }
}

void Tree::printNode(Node* node){
	if(node->Parent()!=NULL){
		cout<<"Key: "<<node->Key()<<" Parent: "<< node->Parent()->Key()<<" Sequence: "<<node->Sequence()<<endl;
	}else{cout<<"Key: "<<node->Key()<<" Sequence: "<<node->Sequence()<<endl;} //ROOT node
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
	    infile;
	}
//########## Add nodes
//sort the sequences by lenght
    // the longest seq will be the root
    int tmp_index=0;
	tree->addNode(listSequence[tmp_index],tmp_index);
	tmp_index++;

//insert the first N sequences in the first level
	Node* node_tmp = new Node();
	for( int i=1; i <= n; i++ ) {
		tree->addNode(listSequence[tmp_index],tmp_index);
		
		node_tmp = tree->findNode(tmp_index, tree->Root()); //store the parent node for each iteration
		//cout<<"print node tmp>> "<<tree->printNode(node_tmp);
		tmp_index++;
		
//insert grouping by M elements
		for( int j=1; j < m; j++ ) {	//is m-1 because it will be the parent+the m-1 child = m
			tree->addNode(listSequence[tmp_index],tmp_index, node_tmp);
			tmp_index++;
	   	}
   	};
//find node
   	/*int valueToFind=16;
   	cout<< "Find Node: "<<endl;
   	if(tree->findNode(valueToFind,tree->Root())!=NULL){
   		cout<<tree->findNode(valueToFind,tree->Root())->Sequence();
   	}else{cout<<"Element: "<<valueToFind<<" Not found"<<endl;}
   	cout<<endl;*/
//Print tree
	cout<< "Walk around the tree: "<<endl;
    tree->walk(tree->Root());
    cout << endl;

//delete Tree
    cout<< "Delete Tree: ...";
    delete tree;
    cout<<"Tree DELETED"<<endl;

    return 0;
}