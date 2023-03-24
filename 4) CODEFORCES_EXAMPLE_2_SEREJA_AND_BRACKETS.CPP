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

class info{
public:
	int open,close,full ;

	info(){
		open = 0 ;
		close = 0 ;
		full = 0 ;
	}

	info(int open,int close,int full){
		this -> open = open ;
		this -> close = close ;
		this -> full = full ;
	}
};

info merge(info left,info right){
	info ans = info() ;
	ans.open = left.open + right.open - min(left.open,right.close) ;
	ans.close = left.close + right.close - min(left.open , right.close) ;
	ans.full = left.full + right.full + min(left.open , right.close) ;
	return ans ;
}

void buildSGTree(int ind,int low,int high,string str,info seg[]){
	if(low == high){
		seg[ind].open = (str[low] == '(') ;
		seg[ind].close = (str[low] == ')') ;
		seg[ind].full = 0 ;
		return ;
	}
	int mid = (low + high) >> 1 ;
	buildSGTree(2*ind+1,low,mid,str,seg) ;
	buildSGTree(2*ind+2,mid+1,high,str,seg) ;
	seg[ind] = merge(seg[2*ind+1] , seg[2*ind+2]) ;
}

info query(int ind,int low,int high,int l,int r,string str,info seg[]){
	// no overlap 
	// low high l r (or) l r low high
	if((high < l) or (r < low)) return info() ;

	// full overlap
	// l low high r 
	if((low >= l) and (high <= r)) return seg[ind] ;

	// partial overlap 
	int mid = (low + high) >> 1 ;
	info left = query(2*ind+1,low,mid,l,r,str,seg) ;
	info right = query(2*ind+2,mid+1,high,l,r,str,seg) ;
	return merge(left , right) ;

}

void solve(){
	string str ; cin >> str ;
	int size = str.size() ;
	info seg[4*size] ;
	buildSGTree(0,0,size-1,str,seg) ;

	int q ; cin >> q ;
	while(q--){
		int l,r ; cin >> l >> r ;
		info ans = query(0,0,size-1,l-1,r-1,str,seg) ;
		cout << ans.full*2 << NEXT ;
	}
}

int main(int argc,char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL) ; cout.tie(0) ;
	solve();
    return 0;  
}
