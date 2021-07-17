#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
enum PaddingType { LEFT, RIGHT };

 //product fiinding function
string karatsuba(string num1,string num2); // karatsuba algo. for multiplying two strings
string trailzero(string num); // removes '0' from left side of string
bool isZero(string num); //checking if string containing all '0'
string mulIntStringByChar(string num1 , char num2); // multiplying string by character
string sumIntString(string num1 , string num2); //substracting two integer string
string subIntString(string num1 , string num2); // adding two integer string
string padString(string toPad , size_t paddingCountToAdd , char paddingChar , PaddingType paddingType); //adding zeros in string

// divide functions
int judge(string a,string b);
string dezero(string a);
string minuss(string a,string b);
string divide(string a,string b);

class big
{
protected:
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
    friend big operator/(big t1 , big t2);
    // sorting two string
    friend void arrange_Order(big &t1 , big &t2); 
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

// data type converter
template<typename T>
big to_big(T x);

// big class function start
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

// addition ans substraction operation
big operator+(big t1 , big t2){
    if(validOperation(t1,t2,'+') == '-')
        return t1-t2;
    arrange_Order(t1,t2);
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
    arrange_Order(t1,t2);
    big ans;
    ans.data = subIntString(t1.data , t2.data);
    ans.sign = t1.sign;
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

// divide function
big operator/(big t1 , big t2){
    big t;
    t.data = divide(t1.data,t2.data);
    t.size = t.data.size();
    t.sign =(t1.sign == t2.sign)? '+': '-';
    return t;
}

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

void arrange_Order(big &t1 , big &t2){
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
    if(t1.size < t2.size || (t1.sign == '-' && t2.sign == '+'))return true;
    else if(t1.size > t2.size)return false;
    else
        for(ll i=0; i<t1.size;i++)
            if(t1.data[i]>=t2.data[i])
                return false;
            else
                return true;
    return true;
}

bool operator<=(big t1 , big t2){
    if(t1<t2 || t1==t2)return true;
    else return false;
}

bool operator==(big t1 , big t2){
    if(t1.size < t2.size || t1.size > t2.size || (t1.sign != t2.sign ))return false;
    else
        for(ll i=0; i<t1.size;i++)
            if(t1.data[i]>t2.data[i] || t1.data[i] < t2.data[i])
                return false;
    return true;
}

bool operator>(big t1 , big t2){
    if(t1.size > t2.size || (t1.sign == '+' && t2.sign == '-'))return true;
    else if(t1.size < t2.size)return false;
    else
        for(ll i=0; i<t1.size;i++)
            if(t1.data[i]<= t2.data[i])
                return false;
            else
                return true;
    return true;
}

bool operator>=(big t1 , big t2){
    if(t1>t2 || t1==t2)return true;
    else return false;
}

// other datatype to big converting
template<typename T>
big to_big(T x){
    big t;
    t = to_string(x);
    return t;
}

