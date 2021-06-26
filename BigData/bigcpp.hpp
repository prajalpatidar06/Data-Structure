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
    t = t.data;
    return out;
}

big operator+(big t1 , big t2){
    makeEqual(t1,t2);
    if(validOperation(t1,t2,'+') == '-')
        return t1-t2;
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

big operator-(big t1 , big t2){
    makeEqual(t1,t2);
    if(validOperation(t1,t2,'-') == '+')
        return t1+t2;
    big t;
    int a , b , ans , carry=0;
    for(ll i = t1.size-1;i>=0;i--){
        a = t1.data[i];
        b = t2.data[i];
        ans = a - b - carry;
        if(ans < 0){
            ans = (10 + a ) - b - carry;
            carry = 1;
        }else carry = 0;
        t.data = to_string(ans) + t.data;
    }
    t.sign = t1.sign;
    t.size = t.data.size();
    return t;
}

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

    // arrange order for easy operation 
    bool check = true;
    for(int i=0;i<t1.size;i++){
        if(t2.data[i] > t1.data[i]){
            check = false;
            break;
        }else if(t1.data[i] > t2.data[i]){
            check = true;
            break;
        }
    }
    big t3;
    if(check == false){
        t3 = t1;
        t1 = t2;
        t2 = t3;
    }
}

char validOperation(big &t1 , big &t2 , char op){
    if(op == '+'){
        if(t1.sign==t2.sign && op == '+')return '+';
        if(t1.sign != t2.sign){
            if(t2.sign == '-')t2.sign = '+';
            else if(t1.sign == '-')t2.sign = '-';
            return '-';
        }
        else return '+';
    }else if(op == '-'){
        if(t2.sign == '-'){
            t2.sign = '+';
            op = '+';
        }
        if(t1.sign==t2.sign && op == '+')return '+';
        else if(t1.sign=='-' && op == '-'){
            t2.sign = '-';
            return '+';
        }
        else return '-';
    }
    return op;
}
