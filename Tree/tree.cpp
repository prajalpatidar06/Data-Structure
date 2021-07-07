#include <iostream>
using namespace std;

void fn( string s){
    cout<<endl<<s <<" = ";
}
template<typename T>
struct list{
    list *left;
    T data;
    list *right;
};

template<typename T>
class tree
{
public:
int size;
    tree(T*s , int size){
        list<T> *p;
        this->size = size;
        int size();
        arraycreate( p,s,0);
        fn("inordertraverse");
        inordertraverse(p);
        fn("preorder traversal");
        preordertraverse(p);
        fn("postorder traverse");
        postordertraverse(p);
    }
    void create(list <T> *&p,int b , string s);
    void arraycreate(list<T> *&p,T *s , int i);
    void inordertraverse(list<T> *&p);
    void preordertraverse(list<T> *&p);
    void postordertraverse(list<T> *&p);
    // std::cout<<endl;
};

template<typename T>
void tree<T>:: create(list<T> * &p,int b, string s)
{
    int x;
    cout << s << " element of " << b << endl;
    cin >> x;
    if (x > 0)
    {
        p = new list<T>;
        p->data = x;
        p->left = NULL;
        p->right = NULL;
        create(p->left, x, "left");
        create(p->right, x, "right");
    }
}
template<typename T>
void tree<T>:: arraycreate(list<T>* &p,T *s , int i)
{
    if(i<size){
        p= new list<T>;
        p->data = s[i];
        p->left=NULL;
        p->right = NULL;
        arraycreate(p->left,s,((i+1)*2)-1);
        arraycreate(p->right,s,((i+1)*2));
    }
}
template<typename T>
void tree<T>:: inordertraverse(list <T> * &p)
{
    if (p)
    {
        inordertraverse(p->left);
        cout << p->data << " ";
        inordertraverse(p->right);
    }
}
template<typename T>
void tree<T>:: preordertraverse(list <T> * &p)
{
    if (p)
    {
        cout << p->data << " ";
        preordertraverse(p->left);
        preordertraverse(p->right);
    }
}
template<typename T>
void tree<T>:: postordertraverse(list <T> * &p)
{
    if (p)
    {
        postordertraverse(p->left);
        postordertraverse(p->right);
        cout << p->data << " ";
    }
}
int main()
{
    string s = "abcdefg";
    float arr[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14.8,15};
    tree<float>t(arr ,15 );
    cout << endl;
    return 0;
}
