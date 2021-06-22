#include<iostream>
using namespace std;

void swap(int &a,int &b){
    int temp = a;
    a=b;
    b=temp;
}

int part(int arr[],int st,int end){
    int pvt=st;
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
