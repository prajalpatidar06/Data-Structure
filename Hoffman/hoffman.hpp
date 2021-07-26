#include<bits/stdc++.h>
using namespace std;

struct node{
    int data [26]  = {0};
    bool isend [26] = {0};
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
    vector<string> search(string key);
    void search(string key , node* head , vector<string>& result);
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
        head->isend[word[n] - 'a'] = true;
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

vector<string> tries::search(string key){
    static node* head = root;
    vector<string> result;
    int key_size = key.size();
    for(int i = 0 ;i < key_size ; i++){
        if(head->data[key[i] - 'a']){
            head =  head->next[key[i] - 'a'];
        }
        else return result;
    }
    search(key , head , result);
    return result;
}

void tries::search(string key , node* head , vector<string>& result){
    if(head == NULL)return;
    for(int i = 0 ; i < 26 ; i++){
        if(head->data[i]){
            if(head->isend[i])
                result.push_back(key + (char)(i + 'a'));
            search(key + char(i + 'a') , head->next[i] , result);
        }
    }
}
