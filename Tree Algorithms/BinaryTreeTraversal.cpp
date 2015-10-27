#include<iostream>
using namespace std;

struct Node{
	char data;
	struct Node* right;
	struct Node* left;
};

void Preorder(struct Node *root);

void Inorder(struct Node *root);

void Postorder(struct Node *root);

Node* Insert(Node *root, char data);

void Print_Node(Node *root);

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
	//Print Nodes in Preorder. 
	Print_Node(root);
	Print_Node(root->left);
	Print_Node(root->left->left);
	cout<<"Preorder: ";
	Preorder(root);
	cout<<"\n";
	cout<<"Inorder: ";
	Inorder(root);
	cout<<"\n";
	cout<<"Postorder: ";
	Postorder(root);
	cout<<"\n";
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
		cout<<"root : "<<root->data<<endl;
		if(root->left != NULL){
			cout<<"left node : "<<root->left->data<<endl;
		}
		if(root->right != NULL){
			cout<<"right node : "<<root->right->data<<endl;
		}
	}	
}

void Preorder(struct Node *root){
	if(root == NULL) return;
	cout<<root->data;
	Preorder(root->left);
	Preorder(root->right);
}

void Inorder(struct Node *root){
	if(root == NULL) return;
	Inorder(root->left);
	cout<<root->data;
	Inorder(root->right);
}

void Postorder(struct Node *root){
	if(root == NULL) return;
	Postorder(root->left);
	Postorder(root->right);
	cout<<root->data;
}
