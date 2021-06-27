#include<iostream>
#define ll long long
using namespace std;

 //product fiinding function
string power(string s , int size);
string product(string t1 , string t2);
string strAdd(string a , string b);
void trailstr(string &s);
void addEqual(string &t1 , string &t2); 

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
    friend big operator*(big t1 , big t2);
    // friend big operator/(big t1 , big t2);
    // size checking and make equal size of both value to be perform
    friend void makeEqual(big &t1 , big &t2);
    friend void prodEqual(big &t1 , big &t2); 
    // to check given operation is valid
    friend char validOperation(big &t1 , big &t2 , char op);
    // trailing zeros
    void trailzero();
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
    if(validOperation(t1,t2,'+') == '-')
        return t1-t2;
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
    t.trailzero();
    return t;
}

big operator-(big t1 , big t2){
    if(validOperation(t1,t2,'-') == '+')
        return t1+t2;
    makeEqual(t1,t2);
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
    t.trailzero();
    return t;
}

big operator*(big t1 , big t2){
    big t;
    prodEqual(t1,t2);
    t.data = product(t1.data , t2.data);
    if(t1.sign != t2.sign)t.sign = '-';
    t.size = t.data.size();
    t.trailzero();
    return t;
}

string product(string t1 , string t2){
    if(t1.size()<=4 && t2.size()<=4){
        ll p = stoi(t1);
        ll q = stoi(t2);
        return to_string(p*q);
    }
    int size = t1.size();
    string a , b , c , d , ac,bd,ad,bc , adbc;
    a = t1.substr(0,size/2);
    b = t1.substr(size/2,size);
    c = t2.substr(0,size/2);
    d = t2.substr(size/2,size);

    ac = product(a , c);
    bd = product(b , d);
    ad = product(a , d);
    bc = product(b , c);

    return strAdd(strAdd(power(ac,size),power(strAdd(ad,bc),size/2)),bc);
}

string power(string s , int size){
    string b;
    while(size--)b+='0';
    return s+b;
}

string strAdd( string a , string b){
    string ans;
    addEqual(a,b);
    int x , y ,sum, carry=0;
    for(ll i=a.size()-1;i>=0;i--){
        x = a[i]-'0';
        y = b[i]-'0';
        sum = x + y + carry;
       
        carry = sum/10;
        sum = sum%10;
       ans  = to_string(sum) + ans;    
    }
    if(carry)ans = to_string(carry) + ans;
    trailstr(ans);
    return ans;
}

void trailstr(string &s){
    int count = 0,i=0;
    while(s[i++] == '0')count++;
    s = s.substr(count,s.size());
}

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

void prodEqual(big &t1 , big &t2){
    if(t1.size != t2.size){
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
    int var = 0;
    int count = t1.size;
    while(count%4){
        t1.data = '0' + t1.data;
        t2.data = '0' + t2.data;
        count++;
        var++;
    }
    t1.size=t2.size=t1.size+var;
}

void addEqual(string &t1 , string &t2){
    if(t1.size() != t2.size()){
        int length  = t1.size();
        length = t1.length() - t2.length();
        string b;
        if(length > 0){
            while(length--)b+='0';
            t2 = b + t2;
        }else{
            length*=-1;
            while(length--)b+='0';
            t1 = b+t1;
        }
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

void big::trailzero(){
    int count = 0,i=0;
    while(data[i++] == '0')count++;
    size = size-count;
    data = data.substr(count,size);
}
