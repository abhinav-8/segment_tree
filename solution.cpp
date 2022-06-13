#include <bits/stdc++.h>
using namespace std;

void build(int index , int low , int high , int arr[] , int seg[]){

	if(high == low) 
	        seg[index] = arr[low];

	else{
		
		int mid = (low + high) >>1 ;

		build(2 * index + 1 , low , mid , arr , seg);

		build(2 * index + 2 , mid + 1 , high , arr , seg);

		seg[index] = min(seg[2*index+1],seg[2*index+2]);
	 
	 }

}
int query(int index , int low , int high , int l , int r , int arr[] , int seg[]){

	//No overlap l r low high l r
	if(r < low or l > high) return INT_MAX;

	//Full overlap l low  high r
	if(l <= low and r >= high) return seg[index];

	//Parial overlap
	int mid  = (low + high) >> 1;

	int left = query(2 * index + 1 , low , mid , l , r , arr , seg);

	int right = query(2 * index + 2 , mid + 1 , high , l , r , arr ,seg);

	return min(left , right); 
}

void update(int index , int low  , int high , int i , int val , int arr[] , int seg[]){
		
	if(low == high)
		seg[index] = val;

	else {

		int mid = (low + high) >> 1;

		if(i <= mid) update(2 * index + 1 , low , mid , i , val , arr , seg);

		else update(2 * index + 2 , mid + 1 ,high , i , val , arr , seg);

		seg[index] = min (seg[2 * index + 1] , seg[2 * index + 2]);

	}

}
void solution()
{
	int n ;
	cin >> n ;
	int seg[4*n];
	int arr[n];
	for(int i = 0 ; i < n ; i ++ )
		cin >> arr[i] ; 
	
	build(0,0,n-1,arr,seg);
	
	int q;
	cin >> q ;

	while(q--){
	
		int type;
	
		cin>>type;
	
		if(type == 1) 
		{
			int l , r ;
			cin >> l >> r ;
			cout << query( 0 , 0 , n-1, l , r , arr , seg) << endl ;
		}

		else {
			int i , val ;
			cin >> i >> val;
			update( 0 , 0 ,n-1 , i , val , arr ,seg);
			arr[i] = val ;
		}
	}
}


signed main()
{

#ifndef ONLINE_JUDGE
	freopen("check.txt", "w", stderr);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

		solution();

}

// 								1 2 3 4
// 							      0 0 3 seg[0] = 1
// 	    1 0 1 seg[1]=1       								   2 2 3  seg[2]=3
// 3 0 0 	               4 1 1  							5 2 2				 6 3 3
//seg[3]=1 		      seg[4]=2  					       seg[5]=3 			seg[6]=4	

