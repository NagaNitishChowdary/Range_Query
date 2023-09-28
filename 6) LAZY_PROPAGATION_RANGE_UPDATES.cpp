// RANGE UPDATES 
// LAZY PROPAGATION 

#include<bits/stdc++.h>
using namespace std ; 

class ST {
	vector<int> seg,lazy ;
public:
	ST(int n){
		seg.resize(4*n) ;
		lazy.resize(4*n) ;
	}

public:
	void build(int ind,int low,int high,vector<int> &arr){
		if(low == high){
			seg[ind] = arr[low] ;
			return ; 
		}

		int mid = (low + high) >> 1 ; 
		build(2*ind+1, low, mid, arr) ;
		build(2*ind+2, mid+1, high, arr) ;
		seg[ind] = seg[2*ind+1] + seg[2*ind+2] ;
	}

	void update(int ind,int low,int high,int l,int r,int val){
		// UPDATE THE PREVIOUS REMAINING UPDATES
		// AND PROPAGATE DOWNWARDS 
		if(lazy[ind] != 0){
			seg[ind] += (high-low+1) * lazy[ind] ;
			// PROPAGATE THE LAZY UPDATE DOWNWARDS 
			// FOR THE REMAINING NODES TO GET UPDATED 
			if(low != high){
				lazy[2*ind+1] += lazy[ind] ;
				lazy[2*ind+2] += lazy[ind] ;
			}

			lazy[ind] = 0 ; 
		}


		// NO OVERLAP 
		// WE DONT DO ANYTHING AND RETURN 
		// low high l r  (or)  l r low high 
		if(high < l || r < low) return ; 

		// COMPLETE OVERLAP 
		// l low high r 
		if(l <= low && r >= high){
			seg[ind] += (high-low+1)*val ; 
			// IF NOT A LEAF NODE IT WILL HAVE CHILDREN
			if(low != high){
				lazy[2*ind+1] += val ; 
				lazy[2*ind+2] += val ; 
			}
			return ; 
		}

		int mid = (low + high) >> 1 ; 
		update(2*ind+1, low, mid, l, r, val) ;
		update(2*ind+2, mid+1, high, l, r, val) ;
		seg[ind] = seg[2*ind+1] + seg[2*ind+2] ;  
	}


	int query(int ind,int low,int high,int l,int r){

		// UPDATE THE PREVIOUS REMAINING UPDATES
		// AND PROPAGATE DOWNWARDS 
		if(lazy[ind] != 0){
			seg[ind] += (high-low+1) * lazy[ind] ;
			// PROPAGATE THE LAZY UPDATE DOWNWARDS 
			// FOR THE REMAINING NODES TO GET UPDATED 
			if(low != high){
				lazy[2*ind+1] += lazy[ind] ;
				lazy[2*ind+2] += lazy[ind] ;
			}

			lazy[ind] = 0 ; 
		}

		// NO OVERLAP 
		// low high l r  (or)  l r low high 
		if(high < l || r < low) return 0 ; 

		// COMPLETE OVERLAP 
		// l low high r 
		if(low >= l && high <= r) return seg[ind] ;

		// PARTIAL OVERLAP 
		int mid = (low + high) >> 1 ; 
		int left = query(2*ind+1,low,mid,l,r) ;
		int right = query(2*ind+2,mid+1,high,l,r) ;
		return left + right ;  
	}
};

int main(){
	int test ; cin >> test ;
	while(test--){
		int n ; cin >> n ; 
		vector<int> arr(n) ; 
		for(int i=0 ; i<n ; i++) cin >> arr[i] ;
		ST st(n) ; 
		st.build(0,0,n-1,arr) ; 

		int q ; cin >> q ; 
		while(q--){
			int type ; cin >> type ; 
			if(type == 1){
				int l,r ; cin >> l >> r ; 
				cout << st.query(0,0,n-1,l,r) << endl ;
			} else {
				int l,r,val ; cin >> l >> r >> val ; 
				st.update(0,0,n-1,l,r,val) ; 
			}
		}
	}
	return 0 ; 
}
