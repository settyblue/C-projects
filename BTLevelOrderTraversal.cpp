#include<iostream>
#include<queue>
using namespace std;

struct Node{
	char data;
	Node* left;
	Node* right;
	int level;
};

Node* Insert(Node *root, char data);

void Print_Node(Node *root);

void Levelorder(struct Node *root);

int main(){
	Node* root = NULL;
	root = Insert(root,'M'); root = Insert(root,'D');
	root = Insert(root,'Q'); root = Insert(root,'Z'); 
	root = Insert(root,'A'); root = Insert(root,'C');
	//          M
	//        /  \
	//      D     Q
	//     /       \
	//    A         Z
	//     \ 
	//     C
	Levelorder(root);
	Print_Node(root);
	Print_Node(root->left);
	Print_Node(root->right);
	Print_Node(root->left->left);
	Print_Node(root->left->left->right);
	return 0;
}

Node* Insert(Node *root,char data) {
	if(root == NULL) {
		root = new Node();
		root->data = data;
		root->left = root->right = NULL;
	}
	else if(data <= root->data)
		root->left = Insert(root->left,data);
	else 
		root->right = Insert(root->right,data);
	return root;
}

void Print_Node(Node * root){
	if(root != NULL){
		cout<<"root : "<<root->data<<"  level : "<<root->level<<endl;
		/*
		if(root->left != NULL){
			cout<<"left node : "<<root->left->data<<endl;
		}
		if(root->right != NULL){
			cout<<"right node : "<<root->right->data<<endl;
		}
		*/
	}	
}

void Levelorder(struct Node *root){
	queue <Node*> all_nodes;
	Node* temp;
	if(!root) return;
	all_nodes.push(root);
	//root->level = 0;
	while(!all_nodes.empty()){
		temp = all_nodes.front();all_nodes.pop();
		if(temp->left ){
			temp->left->level = temp->level+1;
			all_nodes.push(temp->left);
		}
		if(temp->right ){
			temp->right->level = temp->level+1;
			all_nodes.push(temp->right);
		}
		
	}
	//while(all_nodes.)
}
