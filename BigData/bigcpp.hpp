#include<iostream>
#include<string>
#include<algorithm>
#include<climits>
using namespace std;
#define ll long long
enum PaddingType { LEFT, RIGHT };


//string arithmatic
string karatsuba(string num1,string num2); // karatsuba algo. for multiplying two strings
string padString(string toPad , size_t paddingCountToAdd , char paddingChar , PaddingType paddingType); //adding zeros in string
string trailzero(string num); // removes '0' from left side of string
bool isZero(string num); //checking if string containing all '0'
string mulIntStringByChar(string num1 , char num2); // multiplying string by character
string sumIntString(string num1 , string num2); //substracting two integer string
string subIntString(string num1 , string num2); // adding two integer string

// divide functions
string int_divide(string p , string q);
string float_divide(string num1 , int num1_deci_idx , string num2 , int &ans_idx , bool &ans_isdecimal);
void trail_left_zero_both_string(string &p , string &q);
string long_division(string *p , string q);

class big{
protected:
    string data;
    ll size=0;
    char sign = '+';
public:
    void operator=(string t);
    string get_data(){return data;}
    int get_size(){return data.size();}
    void set_sign(char sign){ this->sign = sign ;}
    char get_sign(){return sign;}
    //cout function
    friend ostream & operator<<(ostream &out , big t);
    // cin function
    friend istream & operator>>(istream &out , big &t);
    // basic binary operation
    friend big operator+(big t1 , big t2);
    friend big operator-(big t1 , big t2);
    friend big operator*(big t1 , big t2);
    friend big operator/(big t1 , big t2);
    // to check given operation is valid
    friend char validOperation(big &t1 , big &t2 , char op);
    // trailing zeros
    void trailzero();
    // conditional operator
    friend bool operator<(big t1 , big t2);
    friend bool operator>(big t1 , big t2);
    friend bool operator==(big t1 , big t2);
    friend bool operator>=(big t1 , big t2);
    friend bool operator<=(big t1 , big t2);
};

// big class function start
void big::operator=(string t){
    if(t[0] == '-' || t[0] == '+'){
        sign = (t[0] == '-')? '-' : '+';
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

// addition ans substraction operation
big operator+(big t1 , big t2){
    if(validOperation(t1,t2,'+') == '-')
        return t1-t2;
    big ans;
    ans.data = sumIntString(t1.data , t2.data);
    ans.size = ans.data.size();
    ans.sign = t1.sign;
    ans.trailzero();
    return ans;
}

big operator-(big t1 , big t2){
    if(validOperation(t1,t2,'-') == '+')
        return t1+t2;
    big ans;
    ans.sign = (t2 > t1) ? '-' : '+';
    ans.data = subIntString((t2 > t1) ? t2.data : t1.data , (t2 > t1) ? t1.data : t2.data);
    ans.size = ans.data.size();
    ans.trailzero();
    return ans;
}

// multiply operation
big operator*(big t1 , big t2){
    big t;
    t.data = karatsuba(t1.data , t2.data);
    if(t1.sign != t2.sign)t.sign = '-';
    t.size = t.data.size();
    t.trailzero();
    return t;
}

// divide function
big operator/(big t1 , big t2){
    big t;
    t.data = int_divide(t1.data,t2.data);
    t.size = t.data.size();
    t.sign =(t1.sign == t2.sign)? '+': '-';
    return t;
}

char validOperation(big &t1 , big &t2 , char op){
    if(op == '+'){
        if(t1.sign==t2.sign && op == '+')return '+';
        if(t1.sign != t2.sign){
            if(t2.sign == '-')t2.sign = '+';
            else if(t1.sign == '-'){
                big t3 = t1;
                t1 = t2;
                t2 = t3;
                t2.sign = '+';
            }
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
    data = data.substr(count,size);
    if(data.size() == 0){
        data = "0";
    }
    size = data.size();
}

// conditional operation
bool operator<(big t1 , big t2){
    int i = 0 ; 
    while(t1.data[i] == '0') i++;
    t1.data = t1.data.substr(i , t1.size);
    t1.size = t1.data.size();
    i = 0;
    while(t2.data[i] == '0') i++;
    t2.data = t2.data.substr(i , t2.size);
    t2.size = t2.data.size();

    if(t1.size < t2.size || (t1.sign == '-' && t2.sign == '+'))return true;
    else if(t1.size > t2.size)return false;
    else
        for(ll j=0; j<t1.size;j++)
            if(t1.data[j] > t2.data[j])
                return false;
            else if(t1.data[j] == t2.data[j]) i++;
            else return true;
    return i != t1.data.size();
}

bool operator<=(big t1 , big t2){
    if(t1<t2 || t1==t2)return true;
    else return false;
}

bool operator==(big t1 , big t2){
    int i = 0 ; 
    while(t1.data[i] == '0') i++;
    t1.data = t1.data.substr(i , t1.size);
    t1.size = t1.data.size();
    i = 0;
    while(t2.data[i] == '0') i++;
    t2.data = t2.data.substr(i , t2.size);
    t2.size = t2.data.size();

    if(t1.size < t2.size || t1.size > t2.size || (t1.sign != t2.sign ))return false;
    else
        for(ll i=0; i<t1.size;i++)
            if(t1.data[i]>t2.data[i] || t1.data[i] < t2.data[i])
                return false;
    return true;
}

bool operator>(big t1 , big t2){
    int i = 0 ; 
    while(t1.data[i] == '0') i++;
    t1.data = t1.data.substr(i , t1.size);
    t1.size = t1.data.size();
    i = 0;
    while(t2.data[i] == '0') i++;
    t2.data = t2.data.substr(i , t2.size);
    t2.size = t2.data.size();
    i = 0;
    if(t1.size > t2.size || (t1.sign == '+' && t2.sign == '-'))return true;
    else if(t1.size < t2.size)return false;
    else
        for(ll j=0; j<t1.size;j++)
            if(t1.data[j] < t2.data[j])
                return false;
            else if(t1.data[j] == t2.data[j]) i++;
            else return true;
    return i != t1.data.size() ;
}

bool operator>=(big t1 , big t2){
    if(t1>t2 || t1==t2)return true;
    else return false;
}

// other datatype to big converting
big to_big(string x){big t; t = x; return t;}
big to_big(int x){return to_big(to_string(x));}
big to_big(long long x){return to_big(to_string(x));}

// big class end

// + , -  ans * string functions
string karatsuba(string num1 , string num2){
    if(isZero(num1) || isZero(num2))
        return "0";
    // removes zeros from left side
    num1 = trailzero(num1);
    num2= trailzero(num2);
    int len1 = num1.size() , len2 = num2.size();

    if(len1 == 1 || len2 == 1){
        return mulIntStringByChar(len1 == 1 ? num2 : num1, len1 == 1 ? num1[0] : num2[0]);
    }
    size_t n = max(len1 , len2);
    n += (n&1);
    size_t n2 = n/2;

    num1 = padString(num1 , n - len1 , '0' , LEFT);
    num2 = padString(num2 , n - len2 , '0' , LEFT);

    string a = num1.substr(0, n2);
    string b = num1.substr(n2, n);
    string c = num2.substr(0, n2);
    string d = num2.substr(n2, n);

    string ac = karatsuba(a , c);
    string bd = karatsuba(b , d);

    string _ab = sumIntString(a , b);
    string _cd = sumIntString(c , d);
    string abcd = karatsuba(_ab , _cd);
    abcd = subIntString(abcd , ac);
    abcd = subIntString(abcd , bd);

    ac = padString(ac, n, '0', RIGHT);
    abcd = padString(abcd, n2, '0', RIGHT);
    string res = sumIntString(ac, abcd);
    res = sumIntString(res, bd);
    return res;
}   

string padString(string toPad , size_t paddingCountToAdd , char paddingChar , PaddingType paddingType){
    string s(paddingCountToAdd , paddingChar);
    return paddingType == LEFT ? s + toPad : toPad + s;
}

string trailzero(string num){
    int i=0;
    for(; i < num.size() ; i++){
        if(num[i] != '0')break;
    }
    return num.substr(i);
}

bool isZero(string num){
    for(auto i:num)
        if(i != '0')return false;
    return true;
}

string mulIntStringByChar(string num1 , char num2){
    if(num2 == '0')return "0";
    else if(num2 == '1')return num1;

    int carry = 0;
    int d0 = num2 - '0' , d1 , d;
    string ans = "";
    for(int i = num1.size()-1; i >= 0; i--){
        d1 = num1[i] - '0';
        d = (d0 * d1) + carry;
        carry = d/10;
        d = d%10;
        ans += d + '0';
    }
    if(carry) ans += carry + '0';
    reverse(ans.begin(),ans.end());
    return ans;
}

string sumIntString(string num1 , string num2){
    if(num2 == "") return num1;
    if(num1 == "") return num2;
    string ans = "";
    size_t num1size = num1.size();
    size_t num2size = num2.size();
    size_t m = max(num1size , num2size);

    int c1,c2,c,carry = 0;
    for(int i = 0 ; i < static_cast<int>(m); i++){
        c1 = i < num1size ? num1[num1size - 1 - i] - '0' : 0;
        c2 = i < num2size ? num2[num2size - 1 - i] - '0' : 0;
        c = c1 + c2 + carry;
        carry = c/10;
        ans += (c%10) + '0';
    }
    if(carry) ans += (carry + '0');
    reverse(ans.begin(), ans.end());
    return ans;
}

string subIntString(string num1 , string num2){
    if(num2 == "")return num1;

    string ans = "";
    size_t num1size = num1.size();
    size_t num2size = num2.size();
    int c1,c2,carry = 0;
    for(int i = 0 ; i<num1.size();i++){
        c1 = num1[num1size - 1 - i] - '0' - carry;
        c2 = i < num2size ? num2[num2size - 1 - i] - '0' : 0;
        carry = 0;
        if (c1 < c2){
            carry = 1;
            c1 += 10;
        }
        ans += (c1 - c2) + '0';
    }
    reverse(ans.begin() , ans.end());
    return isZero(ans) ? "0" : trailzero(ans);
}

// dividing string functions

string float_divide(string dividend , int deci_idx , string divisor , int &ans_deci_idx , bool &ans_isdecimal){
    if(deci_idx == 0) trail_left_zero_both_string(dividend , divisor);
    if(divisor == "0" || divisor.empty())return "nan";
    string quotient = "" , remainder = "";
    int i = 0 ; 
    do{
        while(to_big(remainder) < to_big(divisor)){
            if(!ans_isdecimal && i >= dividend.size() - deci_idx){
                ans_isdecimal = true;
                ans_deci_idx = quotient.size();
            }
            if(i >= dividend.size()){
                remainder += '0';
                ans_deci_idx = (ans_isdecimal) ? ans_deci_idx : quotient.size();
                ans_isdecimal = true;
            }
            else remainder += dividend[i];
            i++;
        }
        quotient += long_division(&remainder , divisor);
        
    }while(i < (dividend.size()+16) && trailzero(remainder) != "");
    i = quotient.size();
    if(quotient[i-1] >= '5' && quotient[i-2] < '9'){
        quotient[i-2]++;
        quotient.erase(i-1);
    }
    ans_deci_idx = quotient.size() - ans_deci_idx;
    return quotient;
}

string int_divide(string dividend , string divisor){
    trail_left_zero_both_string(dividend , divisor);
    if(divisor == "0" || divisor.empty())return "nan";
    string quotient = "" , remainder = "";
    int i = 0 ; 
    do{
        while(to_big(remainder) < to_big(divisor)){
            if(i >= dividend.size()){
                break;
            }
            else remainder += dividend[i];
            i++;
        }
        quotient += long_division(&remainder , divisor);
        
    }while(i < dividend.size() && trailzero(remainder) != "");
    return quotient;
}

void trail_left_zero_both_string(string &p , string &q){
    int i=p.size() - 1 , j = q.size() - 1;
    while(i>0 && j > 0 && p[i] == '0' && q[j] == '0'){
        i--,j--;
    }
    p = p.substr(0 , i+1);
    q = q.substr(0 , j+1);
}

string long_division(string *p , string q){
    ll count = 0;
    while( to_big(*p) >= to_big(q)){
        *p = subIntString(*p,q);
        count++;
    }
    return to_string(count);
}

// bigfloat class start
class bigfloat{
private:
    string floating = "";
    big filter_data;
    char sign = '+';
    bool isdecimal = false;
    ll decimal_index = 0;
public:
    void operator= (string t);
    friend ostream & operator<<(ostream& out , bigfloat t);
    friend istream & operator>>(istream& in , bigfloat &t);
    // basic binary operation
    friend bigfloat operator+(bigfloat t1 , bigfloat t2);
    friend bigfloat operator-(bigfloat t1 , bigfloat t2);
    friend bigfloat operator*(bigfloat t1 , bigfloat t2);
    friend bigfloat operator/(bigfloat t1 , bigfloat t2);
    // conditional operator
    friend bool operator<(bigfloat t1 , bigfloat t2);
    friend bool operator>(bigfloat t1 , bigfloat t2);
    friend bool operator==(bigfloat t1 , bigfloat t2);
    friend bool operator>=(bigfloat t1 , bigfloat t2);
    friend bool operator<=(bigfloat t1 , bigfloat t2);
};

// bigfloat I/O and assignment operation
ostream& operator<<(ostream& out , bigfloat t){
    if(t.floating[0] != '-' && t.sign == '-')
        out<<'-';
    out<<t.floating;
    return out;
}

istream& operator>>(istream& in , bigfloat &t){
    in>>t.floating;
    t = t.floating;
    return in;
}

void bigfloat::operator=(string t){
    floating = t;
    if(floating[0] == '-' || floating[0] == '+'){
        sign = (floating[0] == '-') ? '-' : '+';
        floating = floating.substr(1,floating.size());
    }
    for(auto i = 0 ; i < floating.size() ; i++){
        if(floating[i] == '.'){
            isdecimal = true;
            decimal_index = floating.size() - i - 1;
            floating.erase(i,1);
            break;
        }    
    }
    filter_data = floating;
    filter_data.set_sign(sign);
    floating = t;
}

// bigfloat arithematic operation
bigfloat operator+(bigfloat t1 , bigfloat t2){
    if(t1.sign != t2.sign){
        if(t1.sign == '-'){
            t1.sign = '+';
            t1.filter_data.set_sign('+');
            return t2 - t1;
        }
        return t1 - t2;
    }
    bigfloat ans;
    string t1data = t1.filter_data.get_data();
    string t2data = t2.filter_data.get_data();
    string a , b , c , d;
    a = (t1.isdecimal) ? t1data.substr(0 , t1data.size() - t1.decimal_index) : t1data;
    b = (t1.isdecimal) ? t1data.substr(t1data.size() - t1.decimal_index , t1data.size()) : "0";
    c = (t2.isdecimal) ? t2data.substr(0 , t2data.size() - t2.decimal_index) : t2data;
    d = (t2.isdecimal) ? t2data.substr(t2data.size() - t2.decimal_index , t2data.size()) : "0";
    int diff = t1.decimal_index - t2.decimal_index;
    if(diff < 0) b.append(diff* -1 , '0');
    else if(diff > 0) d.append(diff , '0');
    t1data = sumIntString(a , c);
    t2data = sumIntString(b , d);
    if(t1.isdecimal || t2.isdecimal){
        ans.decimal_index = max(t1.decimal_index , t2.decimal_index);
        ans.isdecimal = true;
    }
    if(t2data.size() > ans.decimal_index){
        t1data = sumIntString(t1data , t2data.substr(0 , t2data.size() - ans.decimal_index));
        t2data = t2data.erase(0 , t2data.size() - ans.decimal_index);
    }
    ans.filter_data = t1data + t2data;
    ans.floating = t1data;
    ans.floating.append(ans.isdecimal ? '.' + t2data  : "");
    ans.sign = t1.sign;
    ans.filter_data.set_sign(ans.sign);
    return ans;
}

bigfloat operator-(bigfloat t1 , bigfloat t2){
    char op = '-';
    if(t2.sign == '-'){
        op = '+';
        t2.sign = '+';
        t2.filter_data.set_sign('+');
    }
    if(t1.sign == t2.sign && op == '+') return t1+t2;
    if(t1.sign == '-' && op == '-'){
        t2.sign = '-';
        t2.filter_data.set_sign('-');
        return t1+t2;
    }
    bigfloat ans;
    string t1data = t1.filter_data.get_data();
    string t2data = t2.filter_data.get_data();

    int decidiff = t1.decimal_index - t2.decimal_index;
    if(decidiff < 0) t1data.append(decidiff* -1 , '0');
    else if(decidiff > 0) t2data.append(decidiff , '0');

    int intdiff = t1data.size() - t2data.size();
    if(intdiff < 0) t1data.insert(0 , intdiff* -1 , '0');
    else if(intdiff > 0) t2data.insert(0 , intdiff , '0');
    string sub = subIntString( t1 >= t2 ? t1data : t2data , t1 < t2 ? t1data : t2data);
    if(t1.isdecimal || t2.isdecimal){
        ans.decimal_index = max(t1.decimal_index , t2.decimal_index);
        ans.isdecimal = true;
    }
    ans.filter_data = sub;
    ans.floating = sub;
    if(ans.isdecimal)
        ans.floating.insert(ans.decimal_index , 1 , '.');
    ans.sign = (t1 >= t2 ) ? '+' : '-';
    ans.filter_data.set_sign(ans.sign);
    return ans;
}

bigfloat operator*(bigfloat num1 , bigfloat num2){
    bigfloat ans;
    ans.filter_data = num1.filter_data * num2.filter_data;
    ans.sign = (num1.filter_data.get_sign() == num2.filter_data.get_sign()) ? '+' : '-';
    ans.decimal_index = (num1.isdecimal) ? num1.decimal_index : 0;
    ans.decimal_index += (num2.isdecimal) ? num2.decimal_index : 0;
    ans.floating = ans.filter_data.get_data();
    if(num1.isdecimal || num2.isdecimal){
        ans.floating.insert(ans.floating.size() - ans.decimal_index , 1 , '.');
        ans.isdecimal = false; 
    }
    if(ans.floating[0] == '.')ans.floating.insert(0 , 1 , '0');
    if(ans.sign == '-')ans.floating.insert(0 , 1 , '-');
    return ans;
}

bigfloat operator/(bigfloat t1 , bigfloat t2){
    bigfloat ans;
    int diff = (t2.isdecimal) ? t2.decimal_index : 0;
    int padding_size  = t1.decimal_index - diff ;
    if(t1.isdecimal){
        if(padding_size > 0){
            t1.decimal_index = padding_size;
            t1.floating  = t1.filter_data.get_data();
            t1.floating.insert(t1.floating.size() - t1.decimal_index , 1 , '.');
        }else{
            t1.isdecimal = false;
            t1.floating  = padString(t1.filter_data.get_data() ,padding_size * -1 , '0' , RIGHT);
            t1.filter_data = t1.floating;
        }   
    }else{
        t1.floating  = padString(t1.filter_data.get_data() , diff , '0' , RIGHT);
        t1.filter_data = t1.floating;
    }
    t2.floating = t2.filter_data.get_data();
    t2.isdecimal = false;
    int ans_deci_idx = INT_MIN;
    bool ans_isdecimal=false;
    ans.floating = float_divide(t1.filter_data.get_data() , (t1.isdecimal) ? t1.decimal_index : 0 , t2.filter_data.get_data() , ans_deci_idx , ans_isdecimal);
    if(ans_isdecimal){
        ans.decimal_index = (ans.isdecimal) ? ans.decimal_index + ans_deci_idx : ans_deci_idx;
        ans.isdecimal = true;
        ans.filter_data = ans.floating;
        ans.floating.insert(ans.floating.size() - ans.decimal_index , 1 , '.');
    }
    ans.sign = (t1.sign == t2.sign) ? '+' : '-';
    return ans;
} 

// bigfloat comparision operation 
bool operator<(bigfloat t1 , bigfloat t2){
    if(t1.sign == '-' && t2.sign == '+')
        return true;
    if(t1.sign == '+' && t2.sign == '-')
        return false;
    if(t1.decimal_index < t2.decimal_index)
        return (t1.sign == t2.sign == '-') ? false : true;
    else if(t1.decimal_index > t2.decimal_index)
        return (t1.sign == t2.sign == '+') ? false : true;
    else 
        return (t1.filter_data < t2.filter_data);
}

bool operator>(bigfloat t1 , bigfloat t2){
    if(t1.sign == '-' && t2.sign == '+')
        return false;
    if(t1.sign == '+' && t2.sign == '-')
        return true;
    if(t1.decimal_index < t2.decimal_index)
        return (t1.sign == t2.sign == '-') ? true : false;
    else if(t1.decimal_index > t2.decimal_index)
        return (t1.sign == t2.sign == '+') ? true : false;
    else 
        return (t1.filter_data > t2.filter_data);
}

bool operator==(bigfloat t1 , bigfloat t2){
    if(t1.sign != t2.sign || t1.floating.size() != t2.floating.size() || t1.isdecimal != t2.isdecimal || t1.decimal_index != t2.decimal_index)
        return false;
    else{
        return t1.filter_data == t2.filter_data;
    }
}

bool operator>=(bigfloat t1 , bigfloat t2){
    return (t1 > t2 || t1 == t2);
}

bool operator<=(bigfloat t1 , bigfloat t2){
    return ( t1 < t2 || t1 == t2);
}

//any data type to big_float converting
bigfloat to_bigfloat(string a){
    bigfloat t;
    t = "a";
    return t;
}
