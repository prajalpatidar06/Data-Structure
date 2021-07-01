#include<iostream>
using namespace std;

struct node{
    int key1=0,key2=0;
    node* left=0,*mid=0,*right=0;
    int height=1;
};

struct tree{
    node*root=NULL;
    void insert(int x){root = insert(x,root);}
    node* insert(int x , node* p);
    node* midElement(int k1 , int k2 , int x);
    node* mid(node *p , node* temp);
    int height(node*p);
    void remove(int x);
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
    // t.insert(8);
    // t.insert(60);
    return 0;
}

node* tree::insert(int x , node* p){
    node * temp=NULL;
    if(p==NULL){
        p = new node;
        p->key1=x;
        return p;
    }
    if(x < p->key1){
        if(p->left)
            temp = insert(x,p->left);
        else if(p->key2 == 0){
            p->key2 = p->key1;
            p->key1 = x;
        }
    }else if(x> p->key1 && p->key2 == 0){
        if(p->mid){
           temp = insert(x,p->mid);
        }
        else{
            p->key2 = x;
        }
    }else if(x>p->key1 && x<p->key2){
        if(p->mid)
            temp = insert(x,p->mid);
        else{
            node*q = new node;
            q->key1 = x;
            p =mid(p,q);
        }
            
    }else if(x > p->key2){
        if(p->right)
            temp = insert(x,p->right);
        else{
            node*q = new node;
            q->key1 = x;
            p =mid(p,q);
        }
    }

    p->height = height(p);

    if(temp && p->height-temp->height==0){
        if(temp->key2)
            return p;
        if(p->key2 == 0){
            if(temp->key1 < p->key1){
                p->key2 = p->key1;
                p->right = p->mid;
                p->key1 = temp->key1;
                p->left = temp->left;
                p->mid = temp->mid;
            }
            else{
                p->key2 = temp->key1;
                p->mid = temp->left;
                p->right = temp->mid;
            }
        }else{
            p = mid(p,temp);
        }
    }
    x = 0;
    return p;
}

node* tree::mid(node* p,node* t){
    node* q=NULL;
    int k1 = p->key1 , k2 = p->key2 , x = t->key1;
    if(k1 < x && x < k2){
        q =new node;
        q->key1 = x;
        t->key1 = k1;
        p->mid = t->mid;
        t->mid = t->left;
        t->left = p->left;
        p->key1 = k2;
        p->key2 = 0;
        p->left= p->mid;
        p->mid = p->right;
        p->right = NULL;
        q->left = t;
        q->mid = p;
    }
    else if(k2 < x){
        q =new node;
        q->key1 = k2;
        q->mid = t;
        p->key2 = 0;
        p->right = NULL;
        q->left = p;
    }
    else if(k1 > x){
       q =new node;
        q->key1 = k1;
        q->left = t;
        p->key1=k2;
        p->left = p->mid;
        p->mid = p->right;
        p->right = NULL;
        q->mid = p;
    }
    return q;
}

node* tree::midElement(int k1 , int k2 , int x){
    node* temp=NULL;
    if(k1 < x && x < k2){
        temp = new node;
        temp->key1 = x;
        temp->left = new node;
        temp->left->key1 = k1;
        temp->mid = new node;
        temp->mid->key1 = k2;
    }
    else if(k2 < x){
        temp = new node;
        temp->key1 = k2;
        temp->left = new node;
        temp->left->key1 = k1;
        temp->mid = new node;
        temp->mid->key1 = x;
    }
    else if(k1 > x){
        temp = new node;
        temp->key1 = k1;
        temp->left = new node;
        temp->left->key1 = x;
        temp->mid = new node;
        temp->mid->key1 = k2;
    }
    return temp;
}

int tree::height(node* p){
    if(p==NULL)return 0;
    int hl,hm,hr;
    hl = (p->left)?p->left->height:0;
    hm = (p->mid)?p->mid->height:0;
    hr = (p->right)?p->right->height:0;

    return max(max(hl,hm),hr)+1;
}
