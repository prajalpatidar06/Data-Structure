#include<iostream>
// #include<string>
using namespace std;
#define ll long long int

ll power(ll n , ll p){
    if(p == 1)return n;
    else if(p == 0)return 1;
    return n*power(n,p-1);
}

void sizecheck(string &sp,int &sizep,string &sq,int &sizeq){
    int diff = sizep - sizeq;
    string temp;
   
     if(diff > 0){
        sizeq+=diff;
        while(diff--)temp+='0';
        sq = temp + sq;
    }else if(diff<0){
        diff = diff*(-1);
        sizep+=diff;
        while(diff--)temp+='0';
        sp = temp + sp;
    }
    if(sizep&1 == 1){
        sp = '0'+sp;
        sq = '0'+sq;
        sizeq++;
        sizep++;
    }
}

ll product(ll p,ll q){
    string sp,sq;
    int a,b,c,d,sizep,sizeq;
    sp = to_string(p);
    sq = to_string(q);
    sizep = sp.size();
    sizeq = sq.size();
    if(sizep==1 || sizeq==1)return p*q;
    sizecheck(sp,sizep,sq,sizeq);
    a=stoi(sp.substr(0,sizep/2));
    b=stoi(sp.substr(sizep/2,sizep));
    c=stoi(sq.substr(0,sizeq/2));
    d=stoi(sq.substr(sizeq/2,sizeq));
    ll ac,bd,ad,bc;
    ac = product(a,c);
    bd = product(b,d);
    ad = product(a,d);
    bc = product(b,c);
    return power(10,sizep)*ac + power(10,sizep/2)*(ad+bc) + bd;
}

int main(){
    cout<<product(123768,458687898);
}
