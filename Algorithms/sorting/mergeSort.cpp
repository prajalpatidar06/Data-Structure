#include<iostream>
using namespace std;
void sort(int arr[],int st,int end){
    if(st>=end)return;
    int mid = (st+end)/2;
    sort(arr,st,mid);
    sort(arr,mid+1,end);
    int i=st,j=mid+1,k=0;
    int *b = new int[end+1-st];
    while(i<=mid && j<=end){
        b[k++] = (arr[i]<arr[j])?arr[i++]:arr[j++];
    }
    while(i<=mid){
        b[k++]=arr[i++];
    }
    while(j<=end){
        b[k++]=arr[j++];
    }
    i=0;
    for(k=st;k<=end;k++){
        arr[k]=b[i];
        i++;
    }
}

int main(){
    int arr[] ={9,8,7,6,5,4,3,2,1};
    sort(arr,0,8);
    return 0;
}
