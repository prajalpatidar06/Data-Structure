#include<iostream>
#include<vector>
#include<algorithm>
#define tt template<typename T>
#define nod node<T>
using namespace std;

tt
struct node{
    T data=0;
    int height=1;
    nod* left=0 , *right = 0;
};

tt
class set{
private:
    nod* root = 0;
    bool isUpdated = false;
protected:
    nod* LRrotation(nod* P);
    nod* RLrotation(nod* P);
    nod* LLrotation(nod* P);
    nod* RRrotation(nod* P);
    int height(nod* p);
    int balance_factor(nod* p);
    nod* insert(T key , nod*p);
    void preorderTraverse(nod* p);
    void delete_tree(nod* p);
    void makeUpdate();

public:
    vector<T>arr;
    void insert(T key){root = insert(key,root); isUpdated = false;}
    auto begin(){makeUpdate();return (arr.empty())?NULL: &arr[0];}
    auto end(){makeUpdate();return (arr.empty())? NULL: &arr[arr.size()-1];}
    void erase(T key);
    void erase(T* begin , T* end);
    T* find(T key);
    int size(){makeUpdate(); return arr.size();}
    bool empty(){makeUpdate(); return arr.empty();}
    void clear(){delete_tree(root);arr.clear();root = NULL;isUpdated = true;}
    void print(){
        for(auto i:arr)cout<<i<<" ";
    }
};

tt
nod* set<T>::insert(T key , nod* p){
    if(p == NULL){
        p = new nod;
        p->data = key;
        return p;
    }
    else if(p->data == key)return p;
    else if(p->data > key){
        p->left = insert(key , p->left);
    }
    else{
        p->right = insert(key , p->right);
    }

    p->height = height(p);
    int bf = balance_factor(p);

    if(bf == 0 || bf == -1 || bf == 1)return p;
    else if(bf == -2){
        if(balance_factor(p->right) == 1)
            p = RLrotation(p);
        else
            p = RRrotation(p);
    }else if(bf == 2){
        if(balance_factor(p->left) == 1)
            p = LLrotation(p);
        else
            p = LRrotation(p);
    }
    return p;
}

tt
int set<T>::height(nod* p){
    int hl , hr;
    hl = (p && p->left)?p->left->height:0;
    hr = (p && p->right)?p->right->height:0;
    return (hl>hr)?hl+1:hr+1;
}

tt
int set<T>::balance_factor(nod* p){
    int hl,hr;
    hl = (p->left)?height(p->left):0;
    hr = (p->right)?height(p->right):0;
    return hl-hr;
}

tt
nod* set<T>::LLrotation(nod* p){
    nod* temp = p->left;
    p->left = temp->right;
    temp->right = p;
    p->height = height(p);
    temp->height = height(temp);
    return temp;
}

tt
nod* set<T>::LRrotation(nod* p){
    nod* temp = p->left->right;
    p->left->right = temp->left;
    temp->left = p->left;
    p->left = temp->right;
    temp->right = p;
    temp->left->height = height(temp->left);
    temp->right->height = height(temp->right);
    temp->height = height(temp);
    return temp;
}

tt
nod* set<T>::RRrotation(nod* p){
    nod* temp = p->right;
    p->right = temp->left;
    temp->left = p;
    p->height = height(p);
    temp->height = height(temp);
    return temp;
}

tt
nod* set<T>::RLrotation(nod* p){
    nod* temp = p->right->left;
    p->right->left = temp->right;
    temp->right = p->right;
    p->right = temp->left;
    temp->left = p;
    temp->left->height = height(temp->left);
    temp->right->height = height(temp->right);
    temp->height = height(temp);
    return temp;
}

tt
void set<T>::makeUpdate(){
    if(isUpdated)return;
    arr.clear();
    preorderTraverse(root);
    isUpdated = true;
}

tt
void set<T>::preorderTraverse(nod* p){
    if(p == NULL)return;
    preorderTraverse(p->left);
    arr.push_back(p->data);
    preorderTraverse(p->right);
}

tt
void set<T>::delete_tree(nod* p){
    if(p == NULL)return;
    delete_tree(p->left);
    delete_tree(p->right);
    delete p;
}

tt
T* set<T>::find(T key){
    makeUpdate();
    int l=0,r=arr.size()-1,m;
    while(l<=r){
        m = (l+r)/2;
        if(arr[m] == key)return &arr[m];
        else if(arr[m] > key)r = m-1;
        else l = m+1;
    }
    return NULL;
}

