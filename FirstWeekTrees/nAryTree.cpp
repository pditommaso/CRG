//to check
//https://www.codeproject.com/Tips/890425/Tree-Container-in-Cplusplus-n-ary-Tree-Part


//http://deadrow.tumblr.com/
#include <iostream>
#include <cstring>
#include <queue>
#define N 50   //Max number of nodes
#define MAX 50 //Max size of set
using namespace std;
//node datastrcuture
typedef struct node{
  char data[50];
  int node_count;
  struct node *child[N]; //this could be done with *child and *sibling to save storage.Will do it in free time.
}node;

//root node
typedef struct Tree {
  node *root;
}Tree;

//creating new node
node *getNode(const char *data){
  node *parent_node = NULL;
  parent_node = new node;
  parent_node->node_count=0;
  if( parent_node ){
    memset(parent_node->data,0,sizeof(parent_node->data));
    strcpy(parent_node->data,data);
    for(int i = 0; i < N; i++){
      parent_node->child[i] = NULL;
    }
  }
  return parent_node;
}

void initialize(Tree *ptree)
{
   //initialize root node and node count
   ptree->root = getNode("Home");
   ptree->root->node_count=0;
}
void print(node* pnode)
{
   //level order traversal of tree
   queue<node*>qu;
   qu.push(pnode);
   int level=0;
   while(1)
   {
       int nodeCount = (int)qu.size();
       if (nodeCount == 0)
           return ;
       level++;
       while (nodeCount > 0)
       {
           node *temp=qu.front();
           qu.pop();
           cout<<temp->data<<" ";
           for(int i=1;i<=temp->node_count;i++)
           {
               if(temp->child[i]!=NULL)
                   qu.push(temp->child[i]);
           }
           nodeCount--;
       }
       cout<<endl;
   }
}
node* search_node(node* pnode,const char *data)
{
   if(pnode==NULL)
       return NULL;
   if(strcmp(data,pnode->data)==0)
       return pnode;
   //search a node like a backtrack
   for(int i=1;i<=pnode->node_count;i++)
   {
       node* t = search_node(pnode->child[i],data);
       if(t!=NULL)
       {
           return t;
       }
   }
   return NULL;
}
node* insert(Tree *tree,const char *root,const char *data)
{
   node *pnode=tree->root;
   node *parent=search_node(pnode,root);
   node *node_data=search_node(pnode,data);
   //check whether this parent and this data is already in subtree or not
   //if yes return null
   if(parent!=NULL && node_data!=NULL)
   {
       for(int i=1;i<=parent->node_count;i++)
       {
           if(strcmp(parent->child[i]->data,data)==0)
               return NULL;
       }
   }
   //check whether the parent of this node is already present
   //or not.if yes add this node as a child node
   //if not add to Root node
   if(parent!=NULL)
   {
       parent->node_count++;
       parent->child[parent->node_count]=getNode(data);
   }
   else
   {
       pnode->node_count++;
       pnode->child[pnode->node_count]=getNode(data);
   }
   return pnode;
}
int main()
{  
  Tree Nary_tree;
   initialize(&Nary_tree);
   node *pcrawl=Nary_tree.root;
   char root[50],child[50];
   memset(root,0, sizeof(root));
   memset(root,0, sizeof(child));
   int edges;
   cout<<"introduce the edges: "<<endl;
   cin>>edges;
   for(int i=0;i<edges;i++)
   {
      cout<< "insett root and child: "<<endl;
       cin>>root>>child;
       pcrawl=insert(&Nary_tree,root,child);
   }
   print(pcrawl);
}