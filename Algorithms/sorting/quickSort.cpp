#include<iostream>
using namespace std;

void swap(int &a,int &b){
    int temp = a;
    a=b;
    b=temp;
}

int select (int arr[],int st,int end){
    int sum=0;
    for(int i=st;i<=end;i++){
        sum+=arr[i];
    }
    sum = (sum)/(end-st+1);
    int ipvt =0,pvt=sum-arr[0];
    int temp;
    for(int i=st+1;i<=end;i++){
        temp = arr[i]-sum;
        if(temp<0)
            temp*=(-1);
        if(temp<arr[pvt]){
            pvt=temp;
            ipvt=i;
        }
    }
    return ipvt;
}

int part(int arr[],int st,int end){
    int pvt=select(arr,st,end);
    int k=st;
    int l=end;
    while(k<=l){
        if(arr[k]<=arr[pvt])k++;
        else if(arr[l]>arr[pvt])l--;
        else{
            swap(arr[k],arr[l]);
        }
    }
    swap(arr[pvt],arr[l]);
    return l;
}

void qs(int arr[],int st,int end){
    if(st<end){
        int mid=part(arr,st,end);
        qs(arr,st,mid-1);
        qs(arr,mid+1,end);
    }
}

int main(){
    int n;cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)cin>>arr[i];
    qs(arr,0,n-1);
    cout<<"\nsorted array is \n";
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }

}
