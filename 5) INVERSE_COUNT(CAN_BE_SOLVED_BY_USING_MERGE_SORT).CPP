// PROBLEM LINK --- https://www.spoj.com/problems/INVCNT/

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

class SGTree{

public:
    vector<int> seg ;

    SGTree(int n){
        seg.resize(4*n+1) ;
    }

    void build(int ind,int low,int high,int arr[]){
        if(low == high){
            seg[ind] = arr[low] ;
            return ;
        }
        int mid = (low + high)/2 ;
        build(2*ind+1,low,mid,arr) ;
        build(2*ind+2,mid+1,high,arr) ;
        seg[ind] = seg[2*ind+1] + seg[2*ind+2] ;
    }

    int query(int ind,int low,int high,int l,int r){
        // no overlap 
        // l r low high  (or)  low high l r 
        if((r < low) or (high < l)) return 0 ;

        // full overlap 
        // l low high r 
        if((low >= l) and (high <= r)) return seg[ind] ;

        // partial overlap
        int mid = (low + high)/2 ;
        int left = query(2*ind+1,low,mid,l,r) ;
        int right = query(2*ind+2,mid+1,high,l,r) ;
        return left + right ;
    }

    void update(int ind,int low,int high,int i,int val){
        if(low == high){
            seg[ind] += val ;
            return ;
        }
        int mid = (low + high) >> 1 ;
        if(i <= mid) update(2*ind+1,low,mid,i,val) ;
        else update(2*ind+2,mid+1,high,i,val) ;
        seg[ind] = seg[2*ind+1] + seg[2*ind+2] ;
    }
};

void solve(){
	int n ; cin >> n ;
	int arr[n] , maxi = -1 ;
	for(int i=0 ; i<n ; i++){ 
		cin >> arr[i] ;
		maxi = max(maxi , arr[i]) ;
	}
	int freq[maxi+1] = {0} ;
	for(int i=0 ; i<n ; i++) freq[arr[i]]++ ;

	SGTree sgt(maxi+1) ;
	sgt.build(0,0,maxi,freq) ;

	int cnt = 0 ;
	for(int i=0 ; i<n ; i++){
		freq[arr[i]]-- ;
		sgt.update(0,0,maxi,arr[i],-1) ;

		cnt += sgt.query(0,0,maxi,1,arr[i]-1) ;
	}
	cout << cnt << NEXT ;
}

int main(int argc,char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL) ; cout.tie(0) ;
    LL testCases ; cin >> testCases ;
    while(testCases--) solve();
    return 0;  
}
