#include"iostream"
#include<algorithm>
#include<vector>

using namespace std;
template<typename T>

class min_heap{
private:
    vector<pair<T,int>>heap;
public:
    void push(T value , int priorty);
    void push(int value){push(value,value);}
    void remove();
    T top();
    bool isEmpty(){return (heap.size())?false:true;}
    int size(){return heap.size();} 
};

template<typename T>
void min_heap<T>::push(T value , int priorty){
    heap.push_back(make_pair(value,priorty));
    int child = size()-1 , parent;
    while(child > 0){
        parent = (child-1)/2;
        if(heap[child].second < heap[parent].second){
            swap(heap[child],heap[parent]);
            child = parent;
        }
        else break;
    }
}

template<typename T>
void min_heap<T>::remove(){
    if(isEmpty()){cout<<"\nerror heap underflow\n"; return;}
    heap[0] = heap[size()-1];
    heap.pop_back();
    int parent = 0,child1,child2;
    while(!isEmpty()){
        child1 = (parent*2)+1;
        child2 = (parent*2)+2;
        if(child1 < size() && heap[parent].second > heap[child1].second){
            if(child2 >= size() || heap[child1].second < heap[child2].second){
                swap(heap[parent],heap[child1]);
                parent = child1;
            }
        }else if(child1 < size() && heap[parent].second > heap[child2].second){
            if(child1 >= size() || heap[child2].second < heap[child1].second){
                swap(heap[parent],heap[child2]);
                parent = child2;
            }
        }else break;
    }
}

template<typename T>
T min_heap<T>::top(){
    if(isEmpty()){
        return -1;
    }
    return heap[0].first;
}
