#include<iostream>
using namespace std;

struct node{
    int data=0;
    bool color = true; // true = red color , false = black color
    node* left=0 , *right=0;
};

class tree{
    private:
        node* root=0;
    public:
        void insert(int x){root = insert(x,root);}
        node* insert(int x , node* p);
        node* search(int x);
};

int main(){
    tree t;
    t.insert(3);
    t.insert(5);
    t.insert(7);
    t.insert(14);
    t.insert(17);
    t.insert(13);
    t.insert(12);
    t.insert(8);
    t.insert(60);
    return 0;
}

node* tree::insert(int x , node* p){
    static  bool signal = 0;
    node* temp;
    if(p == NULL){
        p= new node;
        p->data = x;
        x = 0;
    }
    else if(p->data == x)return p;
    else if(p-> data < x){
        p->right = insert(x,p->right);
        if(signal && (p->left == NULL || p->left->color == false )){
            if(p->right->left && p->right->left->color == true){
                temp = p->right->left;
                p->right->left = temp->right;
                temp->right  = p->right;
                p->right = temp->left;
                temp->left = p;
            }else{
                temp = p->right;
                p->right = temp->left;
                temp->left = p;
            }
            temp->color = false;
            temp->left->color = true;
            p = temp;
            signal = 0;
        }else if(signal && p->left && p->left->color == true){
            p->color = true;
            p->left->color = p->right->color = false;
            signal = 0;
        }
    }
    else if(p-> data > x){
         p->left = insert(x,p->left);
          if(signal && (p->right == NULL || p->right->color == false )){
            if(p->left->right && p->left->right->color == true){
                temp = p->left->right;
                p->left->right = temp->left;
                temp->left = p->left;
                p->left = temp->right;
                temp->right = p;
            }else{
                temp = p->left;
                p->left = temp->right;
                temp->right = p;
            }
            temp->color = false;
            temp->right->color = true;
            p = temp;
            signal = 0;
        }else if(signal && p->right && p->right->color == true){
            p->color = true;
            p->left->color = p->right->color = false;
            signal = 0;
        }
    }
    
    if( p == root) p->color = false;
    if(p->color == 1 && (p->left && p->left->color == 1 || p->right && p->right->color == 1)) signal = true;

    return p;
}
