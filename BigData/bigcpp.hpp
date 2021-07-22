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
int judge(string a,string b);
string dezero(string a);
string minuss(string a,string b);
string divide(string a,string b);

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
    t.data = divide(t1.data,t2.data);
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
    int count;
    for(auto i :num){
        if(i !=0)break;
        count++;
    }
    return num.substr(0,count);
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

string dezero(string a)//Used to remove the zero before the positive number, that is to say, you can enter 000001 like this number
{
	long int i;
	for(i=0;i<a.length();i++)
	{
		if(a.at(i)>48) break;
	}
	if(i==a.length()) return "0";
	a.erase(0,i);
	return a;
}
 int judge(string a,string b)//Judge the size of two positive numbers
{
	if(a.length()>b.length()) return 1;
	if(a.length()<b.length()) return -1;
	long int i;
	for(i=0;i<a.length();i++)
	{
		if(a.at(i)>b.at(i)) return 1;
		if(a.at(i)<b.at(i)) return -1;
	}
	return 0;
}
string minuss(string a,string b)//subtraction of natural numbers
{
	a=dezero(a);
	b=dezero(b);
	long int i,j=0;
	string c="0";
	string c1,c2;
	string d="-";
	if(judge(a,b)==0) return c;
	if(judge(a,b)==1)
	{
		c1=a;
		c2=b;
	}
	if(judge(a,b)==-1)
	{
		c1=b;
		c2=a;
		j=-1;
	}
	reverse(c1.begin(),c1.end());
	reverse(c2.begin(),c2.end());
	for(i=0;i<c2.length();i++)
	{
		if(c2.at(i)>=48&&c2.at(i)<=57) c2.at(i)-=48;
		if(c2.at(i)>=97&&c2.at(i)<=122) c2.at(i)-=87;
	}
	for(i=0;i<c1.length();i++)
	{
		if(c1.at(i)>=48&&c1.at(i)<=57) c1.at(i)-=48;
		if(c1.at(i)>=97&&c1.at(i)<=122) c1.at(i)-=87;
	}
	for(i=0;i<c2.length();i++)
	{
		c1.at(i)=c1.at(i)-c2.at(i);
	}
	for(i=0;i<c1.length()-1;i++)
	{
		if(c1.at(i)<0)
		{
			c1.at(i)+= 10;
			c1.at(i+1)--;
		}
	}
	for(i=c1.length()-1;i>=0;i--)
	{
		if(c1.at(i)>0) break;
	}
	c1.erase(i+1,c1.length());
	for(i=0;i<c1.length();i++)
	{
		if(c1.at(i)>=10) c1.at(i)+=87;
		if(c1.at(i)<10) c1.at(i)+=48;
	}
	reverse(c1.begin(),c1.end());
	if(j==-1) c1.insert(0,d);
	return c1;
}
 string divide(string a,string b)//Division of natural numbers
{
	if(b.length()==1&&b.at(0)==48) return "error";
	long int i,j;
	string c1,c2,d,e;
	if(judge(a,b)==0) return "1";
	if(judge(a,b)==-1)
	{
		return "0";
	}
	c1=dezero(a);
	c2=dezero(b);
	d="";
	e="";
	for(i=0;i<c1.length();i++)
	{
		j=0;
		d=d+c1.at(i);
		d=dezero(d);
		while(judge(d,b)>=0)
		{
			 d=minuss(d,b);//Call the minus function minus before, also added in this article
			d=dezero(d);
			j++;
		}
		e=e+"0";
		e.at(i)=j;
	}
	for(i=0;i<e.length();i++)
	{
		if(e.at(i)>=10) e.at(i)+=87;
		if(e.at(i)<10) e.at(i)+=48;
	}
	e=dezero(e);
	return e;
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
    ans.decimal_index = num1.decimal_index + num2.decimal_index;
    ans.floating = ans.filter_data.get_data();
    if(num1.isdecimal || num2.isdecimal){
        ans.floating.insert(ans.floating.size() - ans.decimal_index , 1 , '.');
        ans.isdecimal = false; 
    }
    if(ans.floating[0] == '.')ans.floating.insert(0 , 1 , '0');
    if(ans.sign == '-')ans.floating.insert(0 , 1 , '-');
    return ans;
}

void trail_left_zero_both_string(string &p , string &q){
    int i=p.size() - 1 , j = q.size() - 1;
    while(i>0 && j > 0 && p[i] == '0' && q[j] == '0'){
        i--,j--;
    }
    p = p.substr(0 , i+1);
    q = q.substr(0 , j+1);
}

string float_divide(string num1 , int num1_deci_idx , string num2 , int &ans_deci_idx){
    if(num1_deci_idx == 0) trail_left_zero_both_string(num1 , num2);
    if(num2 == "0" || num2.empty())return "nan";

    ll count = 0;
    string p = num1.substr(0,num1.size() - num1_deci_idx);
    string ans = "";
    string multiple = "1";
    string temp;
    bool ans_isdecimal = false;
    bool is_multiply = false;
    int precision = 0;
    do{
        while(to_big(p) < to_big(num2)){
            if(ans.empty())ans = "0";
            if(ans_isdecimal)
                ans = (ans[ans.size()-1] == '0' || ans[ans.size()] == ans_deci_idx) ? ans + '0' : ans;
            else{
                ans_deci_idx = ans.size();
                ans_isdecimal = true;
            }
            p += ((num1_deci_idx > 0) ? num1[num1.size() - num1_deci_idx] : '0');
            num1_deci_idx--;
            precision++;
        }
        count = 0;
        while(to_big(p) >= to_big(num2)){
            if(!ans_isdecimal)
                temp = karatsuba(num2 , num2);
            if(!ans_isdecimal && to_big(p) >= to_big(temp)){
                multiple = karatsuba(multiple , num2);
                is_multiply = false;
                num2 = temp;
            }
            else{
                if(count >= LLONG_MAX){
                    ans = sumIntString(ans ,to_string(count));
                    count = 0;
                }
                p = subIntString(p , num2);
                count++;
            }
        }
    ans = (count > 0) ? ans + to_string(count) : ans;
    if(is_multiply){
        multiple = karatsuba(multiple , ans);
        is_multiply = false;
        ans = "";
    }
    }while(to_big(p) >= to_big("1") && precision < 20);
    ans_deci_idx = ans.size()- ans_deci_idx;
    ans = karatsuba(ans,multiple);
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
    int ans_deci_idx = -1;
    ans.floating = float_divide(t1.filter_data.get_data() , (t1.isdecimal) ? t1.decimal_index : 0 , t2.filter_data.get_data() , ans_deci_idx);
    if(ans_deci_idx > -1){
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
