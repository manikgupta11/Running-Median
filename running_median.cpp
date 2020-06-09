#include<bits/stdc++.h>
using namespace std;
class node{
  public:
  int data, height, count; 
  node* left; node*right;
};  

int height(node* node){
  int  height=(node==NULL)? -1 : node->height;	//height of null is -1
  return height;
}

int count(node* node){
  int  count=(node==NULL)? 0 : node->count;	 //count of null is 0
  return count;
}

node *rightrotate(node *grandparent)  {  
  node *parent=grandparent->left;     
  node *parentright = grandparent->left->right;  //save left child of parent
  grandparent->left->right = grandparent;  //make gp right child of parent
  grandparent->left = parentright;         

  grandparent->count = count(grandparent->left)+ count(grandparent->right)+ 1;
  parent->count = count(parent->left)+ count(parent->right) + 1; 

  // parent->height = max(height(parent->left), height(parent->right)) + 1;  
  grandparent->height = max(height(grandparent->left),height(grandparent->right)) + 1;
  parent->height = max(height(parent->left), height(parent->right)) + 1;   //Calculate parent height after grandparent because gp is now child of parent

  return parent;
}  


node *leftrotate(node *grandparent)  {  
  node *parent=grandparent->right;
  node *parentleft = grandparent->right->left;
  grandparent->right->left = grandparent;  //make gp right child of parent
  grandparent->right = parentleft;  

  grandparent->count = count(grandparent->left)+ count(grandparent->right)+ 1;
  parent->count = count(parent->left)+ count(parent->right) + 1; 

  grandparent->height = max(height(grandparent->left),height(grandparent->right)) + 1;
  parent->height = max(height(parent->left), height(parent->right)) + 1;   //Calculate parent height after grandparent because gp is now child of parent
  return parent;   
}   

node *lrrotate(node *grandparent){
  grandparent->left = leftrotate(grandparent->left);  //First apply left rotation on parent so it becomes LL case
  return rightrotate(grandparent);            //Height will be adjusted in RR case so no need here        
}  

node *rlrotate(node *grandparent) {
  grandparent->right = rightrotate(grandparent->left);  //First apply right rotation on parent so it becomes RR case  
  return leftrotate(grandparent);  
}


node* insert(node *root, int key){
  if(root==NULL){
    node *root = new node(); 
    root->data = key;
    root->left = NULL; 
    root->right = NULL;
    root->height = 0;   //height of new node is 0
    root->count=1;     //count of new node is 1
    return root;	  
  }
  
  if(key>=root->data){
    root->right=insert(root->right,key);  //If equal nodes, insert in right child
  }
  else{
  	root->left=insert(root->left,key);
  }

int leftheight=(root->left==NULL)? -1 : root->left->height;
int rightheight=(root->right==NULL)? -1 : root->right->height;
root->height=1+max( leftheight , rightheight );  
int diff=(leftheight-rightheight);  // diff will act as balancing factor

int leftcount=(root->left==NULL)? 0 : root->left->count;
int rightcount=(root->right==NULL)? 0 : root->right->count;
root->count=1+leftcount+rightcount;

 if (diff==2)                   //LL or LR case
 {  if(key<root->left->data)  {    // dont take = here becasue we are inserting equal nodes only in right so equal case with LL or LR wont arise
     return rightrotate(root);   //LL case
    }
    else if(key>root->left->data){
       root->left = leftrotate(root->left);  //LR case First left rotate parent then right rotate grandparent  
      return rightrotate(root); 	
    }
  }
  else if(diff==-2)         //RR or RL case
  {
     if(key >= root->right->data)  {  //taking = here cz inserting equal nodes in right 
       return leftrotate(root);
     }
     else if(key <= root->right->data) {
       root->right = rightrotate(root->right);  
     return leftrotate(root);  //RL
    }
  }    

// cout<<root->data<<" "<<diff<<" "<<leftheight<<" "<<rightheight<<" "<< root->height<<endl;
return root;  
}

int ksmall(node* root, int k)  {
  int leftcount=count(root->left);
  if(leftcount+1==k) {
  	return root->data;
  }
  else if(leftcount+1>k) {
  	return ksmall(root->left, k);
  }
  else return ksmall(root->right, k-leftcount-1);   //subtract leftcount cz every node in left subtree is smaller and subtract 1 for root
}


float median(node* root){
	int rootcount=count(root);
	if(rootcount%2==0)    // if even nodes then median is average of 2 mid values
	{
		float median1=ksmall( root ,rootcount/2);
		float median2=ksmall( root ,rootcount/2+1);
		return (median1+median2)/2;
	}
	else          //odd
	{
	 return  ksmall(root, (rootcount+1)/2);	
	}
}


int main(){

  node *root =NULL;
  int arr[6]={12,4,5,3,8,7};

  for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++){
  	root=insert(root,arr[i]);
    cout<<median(root)<<" ";
  }

	return 0;
}