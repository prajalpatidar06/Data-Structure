#include<bits/stdc++.h>
using namespace std;

struct node{
    int data [26]  = {0};
    int isend [26] = {0};
    node* next [26] = {0};
};

class tries
{
private:
    node* root = 0;
protected:
    node* insert(string word , int n , node* head);
    bool ispresent(string word , int n , node* head);
public:
    void insert(string word);
    bool ispresent(string word){return ispresent(word , word.size() , root);}
    bool erase(string word);
    bool clear();
};

void tries::insert(string word){
    root = insert(string(word.rbegin() , word.rend()) , word.size()-1 , root);
}

node* tries::insert(string word , int n ,  node* head){
    if(n < 0)return NULL;
    if(head == NULL)
        head = new node;
    head->data[word[n] - 'a']++;
    if(n == 0){
        head->isend[word[n] - 'a']++;
        return head;
    }
    else{
        head->next[word[n] - 'a'] = insert(word , n-1 , (head->next[word[n] - 'a']) ? head->next[word[n] - 'a'] : NULL);
        return head;
    }
}

bool tries::ispresent(string word , int n , node* head){
    static size_t i = 0;
    if(head == NULL)return false;
    if(head->data[word[i] - 'a']){
        if(i < n-1)
            return ispresent(word , n , head->next[word[i++] - 'a']);
        else if(i == n-1 && head->isend[word[i] - 'a'])
            return true;
        else false;
    }
    return false;
}
