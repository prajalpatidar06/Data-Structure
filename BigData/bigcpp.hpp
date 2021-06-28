#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#define n 10;
using namespace std;
#define ll long long

 //product fiinding function
string multiply(string num1, string num2);

// divide functions
int judge(string a,string b);
string dezero(string a);
string minuss(string a,string b);
string divide(string a,string b);

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
    friend big operator/(big t1 , big t2);
    // size checking and make equal size of both value to be perform
    friend void makeEqual(big &t1 , big &t2);
    friend void prodEqual(big &t1 , big &t2); 
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
big to_big(int x);



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
// multiply operation
big operator*(big t1 , big t2){
    big t;
    prodEqual(t1,t2);
    t.data = multiply(t1.data , t2.data);
    if(t1.sign != t2.sign)t.sign = '-';
    t.size = t.data.size();
    t.trailzero();
    return t;
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

string multiply(string num1, string num2)
{
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1 == 0 || len2 == 0)
	return "0";

	// will keep the result number in vector
	// in reverse order
	vector<int> result(len1 + len2, 0);

	// Below two indexes are used to find positions
	// in result.
	int i_n1 = 0;
	int i_n2 = 0;
	
	// Go from right to left in num1
	for (int i=len1-1; i>=0; i--)
	{
		int carry = 0;
		int n1 = num1[i] - '0';

		// To shift position to left after every
		// multiplication of a digit in num2
		i_n2 = 0;
		
		// Go from right to left in num2			
		for (int j=len2-1; j>=0; j--)
		{
			// Take current digit of second number
			int n2 = num2[j] - '0';

			// Multiply with current digit of first number
			// and add result to previously stored result
			// at current position.
			int sum = n1*n2 + result[i_n1 + i_n2] + carry;

			// Carry for next iteration
			carry = sum/10;

			// Store result
			result[i_n1 + i_n2] = sum % 10;

			i_n2++;
		}

		// store carry in next cell
		if (carry > 0)
			result[i_n1 + i_n2] += carry;

		// To shift position to left after every
		// multiplication of a digit in num1.
		i_n1++;
	}

	// ignore '0's from the right
	int i = result.size() - 1;
	while (i>=0 && result[i] == 0)
	i--;

	// If all were '0's - means either both or
	// one of num1 or num2 were '0'
	if (i == -1)
	return "0";

	// generate the result string
	string s = "";
	
	while (i >= 0)
		s += std::to_string(result[i--]);

	return s;
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
			c1.at(i)+=n;
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

void big::trailzero(){
    int count = 0,i=0;
    while(data[i++] == '0')count++;
    size = size-count;
    data = data.substr(count,size);
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
// int to big converting
big to_big(int x){
    big t;
    t = to_string(x);
    return t;
}

