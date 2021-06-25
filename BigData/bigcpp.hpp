#include<iostream>
using namespace std;
class big
{
private:
    int data;
public:
    void operator=(int t);
    //cout function
    friend ostream & operator<<(ostream &out , big t);
    // cin function
    friend istream & operator>>(istream &out , big &t);
    // basic binary operation
    friend big operator+(big t1 , big t2);
    friend big operator*(big t1 , big t2);
    friend big operator/(big t1 , big t2);
    friend big operator-(big t1 , big t2);
    // //basic unary operation
    // void operator++(big &t){
    //     t.data++;
    // }
};

void big::operator=(int t){
    data=t;
}

ostream & operator<<(ostream &out,big t){
    out<<t.data;
    return out;
}

istream & operator>>(istream &out,big &t){
    out>>t.data;
    return out;
}

big operator+(big t1 , big t2){
    big t;
    t.data = t1.data+t2.data;
    return t;
}

big operator-(big t1 , big t2){
    big t;
    t.data = t1.data-t2.data;
    return t;
}
big operator*(big t1 , big t2){
    big t;
    t.data = t1.data*t2.data;
    return t;
}
big operator/(big t1 , big t2){
    big t;
    t.data = t1.data/t2.data;
    return t;
}
