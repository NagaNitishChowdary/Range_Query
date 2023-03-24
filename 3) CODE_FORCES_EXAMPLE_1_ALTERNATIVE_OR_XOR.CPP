// PROBLEM LINK --- https://codeforces.com/contest/339/problem/D

#include<bits/stdc++.h>
#define LL long long int 
#define EB emplace_back
#define PB pop_back
#define F first
#define S second
#define NEXT "\n" 
int mod=(int)(1e9+7);

using namespace std;

/*****************KNNC******************/

void buildSGTree(int ind,int low,int high,int arr[],int seg[],int orr){
	if(low == high){
		seg[ind] = arr[low] ;
		return ;
	}

	int mid = (low + high) >> 1 ;
	buildSGTree(2*ind+1,low,mid,arr,seg,!orr) ;
	buildSGTree(2*ind+2,mid+1,high,arr,seg,!orr) ;
	if(orr) seg[ind] = seg[2*ind+1] | seg[2*ind+2] ;
	else seg[ind] = seg[2*ind+1] ^ seg[2*ind+2] ;
}

void update(int ind,int low,int high,int arr[],int seg[],int i,int val,int orr){
	if(low == high){
		seg[ind] = val ;
		return ;
	}

	int mid = (low + high) >> 1 ;
	if(i <= mid) update(2*ind+1,low,mid,arr,seg,i,val,!orr) ;
	else update(2*ind+2,mid+1,high,arr,seg,i,val,!orr) ;
	if(orr) seg[ind] = seg[2*ind+1] | seg[2*ind+2] ;
	else seg[ind] = seg[2*ind+1] ^ seg[2*ind+2] ; 
}

void solve(){
	int n,m,orr ;  cin >> n >> m ;
	int size = (1<<n) ;
	int seg[4*size] , arr[size] ;
	for(int i=0 ; i<size ; i++) cin >> arr[i] ;
	if(n&1) orr = 1 ;
	else orr = 0 ;
	buildSGTree(0,0,size-1,arr,seg,orr) ;

	while(m--){
		int i,val ; cin >> i >> val ;
		update(0,0,size-1,arr,seg,i-1,val,orr) ;
		cout << seg[0] << endl ;
	}
}

int main(int argc,char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL) ; cout.tie(0) ;
	solve();
    return 0;  
}
