#include<iostream>
#include<vector>
#define nod node<T1,T2>
#define tt template<typename T1 , typename T2>
#define maptt map<T1 ,T2>
using namespace std;

tt
struct node{
    T1 key;
    T2 data;
    int height = 1;
    nod* left = 0,*right = 0;
};

tt
class map{
private:
    nod* root = 0;
    bool isUpdated = false;
protected:
    nod* insert(T1 key , T2 data, nod* p);
    nod* LRrotation(nod* P);
    nod* RLrotation(nod* P);
    nod* LLrotation(nod* P);
    nod* RRrotation(nod* P);
    int height(nod* p);
    int balance_factor(nod* p);
    void makeUpdate();
    void preorderTraverse(nod* p);
    void delete_tree(nod* p);
    nod* get_address(T1 key , nod* p);
public:
    vector<pair<T1,T2>>arr;
    auto operator()(T1 key , T2 data){
        root = insert(key,data,root);
        isUpdated = false;
    }
    T2* operator[](T1 key);
    int size(){makeUpdate(); return arr.size();}
    bool empty(){makeUpdate(); return (arr.empty())?true:false;}
    void clear(){delete_tree(root); root = NULL;arr.clear();isUpdated = true;}
    void erase(T1 key);
    nod* find(T1 key);
};

tt
nod* maptt::insert(T1 key , T2 data , nod* p){
    if(p == NULL){
        p = new nod;
        p->key = key;
        p->data = data;
        return p;
    }
    if(p->key == key){
        p->data = data;
        return p;
    }
    else if(p->key > key)p->left = insert(key,data,p->left);
    else if(p->key < key)p->right = insert(key,data,p->right);

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
int maptt::height(nod* p){
    int hl , hr;
    hl = (p && p->left)?p->left->height:0;
    hr = (p && p->right)?p->right->height:0;
    return (hl>hr)?hl+1:hr+1;
}

tt
int maptt::balance_factor(nod* p){
    int hl,hr;
    hl = (p->left)?height(p->left):0;
    hr = (p->right)?height(p->right):0;
    return hl-hr;
}

tt
nod* maptt::LLrotation(nod* p){
    nod* temp = p->left;
    p->left = temp->right;
    temp->right = p;
    p->height = height(p);
    temp->height = height(temp);
    return temp;
}

tt
nod* maptt::LRrotation(nod* p){
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
nod* maptt::RRrotation(nod* p){
    nod* temp = p->right;
    p->right = temp->left;
    temp->left = p;
    p->height = height(p);
    temp->height = height(temp);
    return temp;
}

tt
nod* maptt::RLrotation(nod* p){
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
nod* maptt::get_address(T1 key , nod* p){
    if(p->key == key)return p;
    else if(p->key > key)
        return get_address(key,p->left);
    else
        return get_address(key,p->right);
}

tt
T2* maptt::operator[](T1 key){
        root = insert(key ,(T2)0,root);
        nod* p = get_address(key, root);
        isUpdated = false;
        return &p->data;
}

tt
void maptt::makeUpdate(){
    if(isUpdated)return;
    arr.clear();
    preorderTraverse(root);
    isUpdated = true;
}

tt
void maptt::preorderTraverse(nod* p){
    if(p == NULL)return;
    preorderTraverse(p->left);
    arr.push_back(make_pair(p->key,p->data));
    preorderTraverse(p->right);
}


tt
void maptt::delete_tree(nod* p){
    if(p){
    delete_tree(p->left);
    delete_tree(p->right);
    delete p;
    }
}

tt
nod* maptt::find(T1 key){
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

// tt
// void maptt::erase(T1 key){
//     nod* p = get_address(key,root);

// }

