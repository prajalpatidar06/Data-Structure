#include<iostream>
using namespace std;

struct node{
    int key1=0,key2=0,key3=0 ,height = 1;
    node *left=0,*lmid=0,*rmid=0,*right=0;
};

class tree
{
private:
    node *root=0;
public:
    void insert(int x){ root = insert(x,root);}
    node* insert(int x , node* p);
    int height(node* p);
    node* mid(node* p , node* t);
    void search(int x);
    void remove(int x);
};

int main(){
    tree t;
    t.insert(3);
    t.insert(5);
    t.insert(7);
    t.insert(7);
    t.insert(14);
    t.insert(17);
    t.insert(13);
    t.insert(12);
    t.insert(8);
    t.insert(60);
    return 0;
}

node* tree::insert(int x , node *p){
    if(p == NULL){
        p = new node;
        p->key1 = x;
        return p;
    }
    if(x == p->key1 || x == p->key2 || x == p->key3) return p;
    node *temp = NULL;
    node *q = NULL;
    if(x < p->key1){
        if(p->left){
            temp = insert(x,p->left);
        }
        else if(p->key2 == 0){
            p->key2 = p->key1;
            p->key1 = x;
        }
        else if(p->key3 == 0){
            p->key3 = p->key2;
            p->key2 = p->key1;
            p->key1 = x;
        }else{
            q = new node;
            q->key1 = x;
            temp = mid(p,q);
        }
    }
    else if(x > p->key1 && p->key2 == 0){
        if(p->lmid) temp = insert(x,p->lmid);
        else p->key2 = x;
    }
    else if(x > p->key1 && x < p->key2){
        if(p->lmid) temp = insert(x,p->lmid);
        else if(p->key3 == 0){
            p->key3 = p->key2;
            p->key2 = x;
        }
        else{
            q = new node;
            q->key1 = x;
            temp = mid(p,q);
        }
    }
    else if(x > p->key1 && x > p->key2 && p->key3 == 0){
        if(p->rmid)temp = insert(x,p->rmid);
        else p->key3 = x;
    }
    else if(x > p->key1 && x > p->key2 && x < p->key3){
        if(p->rmid)temp = insert(x,p->rmid);
        else{
            q = new node;
            q->key1 = x;
            temp = mid(p,q);
        }
    }
    else if(x > p->key1 && x > p->key2 && x > p->key3){
        if(p->right)temp = insert(x,p->right);
        else{
            q = new node;
            q->key1 = x;
            temp = mid(p,q);
        }
    }

    p->height = height(p);
    if(temp && p->height - temp->height == 0){
        if(temp->key2)return p;
        else if(p->key1 > temp->key1){
            if(p->key2 == 0){
                p->key2 = p->key1;
                p->rmid = p->lmid;
                p->key1 = temp->key1;
                p->left = temp->left;
                p->lmid = temp->lmid;
            }else if(p->key3 == 0){
                p->key3 = p->key2;
                p->key2 = p->key1;
                p->right = p->rmid;
                p->rmid = p->lmid;
                p->key1 = temp->key1;
                p->left = temp->left;
                p->lmid = temp->lmid;
            }
            else p = mid(p,temp);
        }
        else if(p->key1 < temp->key1 && p->key2 == 0);
        else if(p->key1 < temp->key1 && p->key2 > temp->key1);
        else if(p->key2 < temp->key1 && p->key3 == 0);
        else if(p->key2 < temp->key1 && p->key3 > temp->key1);
    }
    return p;
}

node* tree::mid(node *p , node *t){
    int k1 = p->key1,k2 = p->key2,k3 = p->key3 ,t1 = t->key1;
    node * q = new node;
    if(k2 > t1){
        q->key1 = k2;
        if(k1 > t1){
            t->key2 = k1;
            t->lmid = p->left;
            t->rmid = p->lmid;
        }else{
            t->key2 = t1;
            t->key1 = k1;
            t->left = p->left;
            t->lmid = p->lmid;
        }
        p->key1 = k3;
        p->key2 = p->key3 = 0;
        p->left = p->rmid;
        p->lmid = p->right;
        p->rmid = p->right = NULL;
        q->left = t;
        q->lmid = p;
    }
    else{
        q->key1 = k2;
        if(k3 > t1){
            t->key2 = k3;
            t->lmid = p->rmid;
            t->rmid = p->right;
        }else{
            t->key2 = t1;
            t->key1 = k3;
            t->left = p->rmid;
            t->lmid = p->right;
        }
        p->key2 = p->key3 = 0;
        p->rmid = p->right = NULL;
        q->left = p;
        q->lmid = t;
    }
    q->height = height(q);
    return q;
}

int tree::height(node*p){
    int hl,hlm,hrm,hr;
    hl = (p && p->left)?p->left->height:0;
    hlm = (p && p->lmid)?p->lmid->height:0;
    hrm = (p && p->rmid)?p->rmid->height:0;
    hr = (p && p->right)?p->right->height:0;
    return max(max(hl,hlm),max(hrm,hr))+1;
}
