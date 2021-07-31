#include<iostream>
#include<queue>
#include<vector>
#include<unordered_map>
using namespace std;

unordered_map<char , string>encrypt_keys;

struct node{
    char data;
    int freq;
    node* left, *right;
    node(char data , int freq){
        this->data = data;
        this->freq = freq;
        left = right = 0;
    }
};

class compare{
public:
    bool operator()(node* x , node* y){
        return x->freq > y->freq;
    }
};

node* generateTree(priority_queue<node*,vector<node*> , compare>pq){
    while(pq.size() != 1){
        node* left = pq.top();
        pq.pop();
        node*right =  pq.top();
        pq.pop();
        node* sumnode = new node('$' , left->freq + right->freq);
        sumnode->left = left;
        sumnode->right = right;
        pq.push(sumnode);
    }
    return pq.top();
}

void printCodes(node* root , string arr){
    if(root->left){
        arr += '0';
        printCodes(root->left , arr);
    }
    if(root->right){
        arr += '1';
        printCodes(root->right , arr);
    }
    if(!root->right && !root->left){
        auto itr = 0;
        while(arr[itr] == '0')itr++;
        if(itr >= arr.size())itr--;
        encrypt_keys[root->data] = arr;
    }
}


void huffmanCodes(unordered_map<char,int>mp){
    priority_queue<node* , vector<node*> , compare>pq;
    auto itr = mp.begin();
    while(itr != mp.end()){
        node* newNode = new node(itr->first , itr->second);
        itr++;
        pq.push(newNode);
    }
    node *root = generateTree(pq);
    string arr;
    printCodes(root ,arr);
}

