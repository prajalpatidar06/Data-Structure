#include<iostream>
#define ll long long
using namespace std;
class big
{
private:
    string data;
    ll size=0;
    char sign = '+';
public:
    void operator=(string t);
    //cout function
    friend ostream & operator<<(ostream &out , big t);
    // cin function
    friend istream & operator>>(istream &out , big &t);
    // basic binary operation
    friend big operator+(big t1 , big t2);
    friend big operator-(big t1 , big t2);
    // friend big operator*(big t1 , big t2);
    // friend big operator/(big t1 , big t2);
    // size checking and make equal size of both value to be perform
    friend void makeEqual(big &t1 , big &t2); 
    // to check given operation is valid
    friend char validOperation(big &t1 , big &t2 , char op);
};

void big::operator=(string t){
    if(t[0] == '-'){
        sign = '-';
        data = t.substr(1,t.size()-1);
        size = t.size()-1;
    }else{
        data = t;
        size = t.size();
    }
}

ostream & operator<<(ostream &out,big t){
    if(t.sign == '-')
        out<<'-'; 
    out<<t.data;
    return out;
}

istream & operator>>(istream &out,big &t){
    out>>t.data;
    return out;
}

big operator+(big t1 , big t2){
    if(validOperation(t1,t2,'+') == '-')
        return t1;
    makeEqual(t1,t2);
    big t;
    int a , b ,sum, carry=0;
    for(ll i=t1.size-1;i>=0;i--){
        a = t1.data[i]-'0';
        b = t2.data[i]-'0';
        sum = a + b + carry;
       
        carry = sum/10;
        sum = sum%10;
        t.data = to_string(sum) + t.data;    
    }
    if(carry)t.data = to_string(carry) + t.data;
    t.size = t.data.size();
    t.sign = t1.sign;
    return t;
}

// big operator-(big t1 , big t2){
//     if(validOperation(t1,t2,'-') == '+')
//         return t1+t2;
//     makeEqual(t1,t2);
//     big t;
//     int a , b , ans , carry=0;
//     for(ll i = t1.size-1;i>=0;i--){
        
//     }
//     return t;
// }

// big operator*(big t1 , big t2){
//     big t;
//     t.data = t1.data*t2.data;
//     return t;
// }

// big operator/(big t1 , big t2){
//     big t;
//     t.data = t1.data/t2.data;
//     return t;
// }

void makeEqual(big &t1 , big &t2){
    if(t1.size == t2.size)return;
    
    ll temp = t1.size - t2.size;
    string b;
    if(temp > 0){
        while(temp--)b+='0';
        t2.data = b+t2.data;
        t2.size = t1.size;
    }else{
        temp*=-1;
        while(temp--)b+='0';
        t1.data = b+t1.data;
        t1.size = t2.size;
    }
    
}

char validOperation(big &t1 , big &t2 , char op){
    if(op == '+'){
        if(t1.sign==t2.sign)return '+';
        else return '-';
    }else{
        if(t2.sign == '-'){
            t2.sign = '+';
        }
        if(t1.sign==t2.sign)return '+';
        else return '-';
    }
}
