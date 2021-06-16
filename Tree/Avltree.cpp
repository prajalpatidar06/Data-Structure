#include<iostream>
using namespace  std;

struct node
{
    node*left=NULL;
    int data;
    int height=0;
    node*right=NULL;
};
struct Avltree{
private:
    node*root = NULL;
public:
    void push(int x){
        if(!root)
            root = insert(root,x);
        else insert(root,x);
    }
    node* insert(node*p,int x);
    int nodeHeight(node*p);
    int balanceFactor(node*p);
    node* LLrotaion(node*p);
    node* LRrotaion(node*p);
    node* RLrotaion(node*p);
    node* RRrotaion(node*p);
    void display(){ display(root);}
    void display(node *p);
    node* search(int x);
    void remove(int x){
        remove(root ,x);
    };
    node* remove(node* p,int x);
    node* inorderprefix(node*p);
    node* inordersuffix(node*p);
};

int main(){
    Avltree t;
    t.push(4);
    t.push(2);
    t.push(6);
    t.push(1);
    t.push(3);
    t.push(5);
    t.push(7);

    t.remove(4);
    t.remove(1);
    t.remove(3);
    t.remove(6);
    // cout<<t.search(10)->data<<endl;
    t.display();
    return 0;
}

node* Avltree::insert(node* p,int x){
    node*t = NULL;
    if(p==NULL){
        t = new node;
        t->data = x;
        t->height = 1;
        t->left=t->right=NULL;
        return t;
    }
    if(p->data > x)
        p->left = insert(p->left,x);
    else if(p->data < x)
        p->right = insert(p->right,x);

    p->height = nodeHeight(p);

    if(balanceFactor(p) == 2 && balanceFactor(p->left) == 1)
        return LLrotaion(p);
    else if(balanceFactor(p) == 2 && balanceFactor(p->left) == -1)
        return LRrotaion(p);
    else if(balanceFactor(p) == -2 && balanceFactor(p->right) == 1)
        return RLrotaion(p);
    else if(balanceFactor(p) == -2 && balanceFactor(p->right) == -1)
        return RRrotaion(p);
    return p;
}

int Avltree::nodeHeight(node*p){
    int hl,hr;
    hl = (p && p->left)?p->left->height:0;
    hr = (p && p->right)?p->right->height:0;
    return (hl>hr)?hl+1:hr+1;
}

int Avltree::balanceFactor(node*p){
    int hl,hr;
    hl = (p && p->left)?p->left->height:0;
    hr = (p && p->right)?p->right->height:0;
    return hl-hr;
}

node* Avltree::LLrotaion(node*p){
    node*pl= p->left;
    node*plr = pl->right;

    pl->right = p;
    p->left=plr;
    p->height = nodeHeight(p);
    pl->height = nodeHeight(pl);
    if(root == p)
        root = pl;
    return pl;
}

node* Avltree::LRrotaion(node*p){
    node*pl= p->left;
    node*plr = pl->right;

    p->left = plr->right;
    pl->right = plr->left;
    plr->right = p;
    plr->left = pl;

    p->height = nodeHeight(p);
    pl->height = nodeHeight(pl);
    plr->height = nodeHeight(plr);
    if(root == p)
        root = plr;
    return plr;
}

node* Avltree::RRrotaion(node*p){
    node*pr= p->right;

    p->right = pr->left;
    pr->left = p;
    if(root==p)
        root = pr;
    p->height = nodeHeight(p);
    pr->height = nodeHeight(pr);
    return pr;
}

node* Avltree::RLrotaion(node*p){
    node*pr = p->right;
    node*prl = pr->left;

    pr->left = prl->right;
    p->right = prl->left;

    prl->left=p;
    prl->right = pr;

    p->height = nodeHeight(p);
    pr->height = nodeHeight(pr);
    prl->height = nodeHeight(prl);
    if(root == root)
        root = prl;
    return prl;
}

void Avltree::display(node*p){
    if(p){
        cout<<p->data<<" ";
        display(p->left);
        display(p->right);
    }
}

node* Avltree::search(int x){
    static node *p =root;
    while(p){
        if(p->data == x)return p;
        else if(p->data > x)
            p=p->left;
        else
            p=p->right; 
    }
    return NULL;
}

node* Avltree::inorderprefix(node*p){
    node*t=NULL;
    if(p->left){
        p=p->left;
        while(p->right){
            t=p;
            p=p->right;
        }
    }
    return t;
}

node* Avltree::inordersuffix(node*p){
    node*t=NULL;
    if(p->right){
        p=p->right;
        while(p->left){
            t = p;
            p=p->left;
        }
    }
    return t;
}

node* Avltree::remove(node* p,int x){
    if(p->data == x){
        node*t = NULL,*t2=NULL;
        int hl,hr;
        hl = nodeHeight(p->left);
        hr = nodeHeight(p->right);

        if(hl>hr){
            t=inorderprefix(p);
            if(!t && p->left){
                t2=p->left;
                p->data=t2->data;
                p->left=t2->right;
                delete t2;
            }else if(!t){
                t2 = p->right;
                delete p;
                return t2;
            }
            else{
                t2=t->right;
                p->data=t2->data;
                t->right = t2->left;
                delete t2;
            }
        }else{
            t=inordersuffix(p);
            if(!t && p->right){
                t2=p->right;
                p->data=t2->data;
                p->right=t2->left;
                delete t2;
            }else if(!t){
                t2 = p->left;
                delete p;
                return t2;
            }
            else{
                t2=t->left;
                p->data=t2->data;
                t->left = t2->right;
                delete t2;
            }
        }
    }
    else if(p->data > x)
        p->left = remove(p->left,x);
    else if(p->data < x)
        p->right = remove(p->right,x);
    p->height = nodeHeight(p);
    if(balanceFactor(p) == 2 && balanceFactor(p->left) == 1)
        return LLrotaion(p);
    else if(balanceFactor(p) == 2 && balanceFactor(p->left) == -1)
        return LRrotaion(p);
    else if(balanceFactor(p) == -2 && balanceFactor(p->right) == 1)
        return RLrotaion(p);
    else if(balanceFactor(p) == -2 && balanceFactor(p->right) == -1)
        return RRrotaion(p);
    return p;
}
