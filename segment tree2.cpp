#include<bits/stdc++.h>
using namespace std;

void buildTree(int* arr,int start,int end,int* tree,int treeindex){
	if(start==end){
		tree[treeindex]=arr[start];
		return;
	}
	
	int mid =(start+end)/2;
	buildTree(arr,start,mid,tree,2*treeindex);
	buildTree(arr,mid+1,end,tree,2*treeindex+1);
	
	
	tree[treeindex] = min(tree[2*treeindex],tree[2*treeindex+1]);
	return;
}

void update(int* arr,int start,int end,int* tree,int treeindex,int index,int value){
	if(start==end){   // start = end = index
		arr[start]=value;
		tree[treeindex]=value;
		return;
	}
	
	int mid=(start+end)/2;
	
	if(index<=mid) // move left side
	update(arr,start,mid,tree,2*treeindex,index,value);
	
	else if(index>mid) // move right side
	update(arr,mid+1,end,tree,2*treeindex+1,index,value);
	
	tree[treeindex] = min(tree[2*treeindex],tree[2*treeindex+1]);
	return;
}

int findMin(int start,int end,int left,int right,int* tree,int treeindex){
	if(start>right || end<left){  // out of bounds, return greatest int as we have to find min value
		return INT_MAX;
	}
	
	if(start>=left && end<=right){  // completely lie inside range
		return tree[treeindex];
	}
	
	int mid=(start+end)/2;
	int ans1 = findMin(start,mid,left,right,tree,2*treeindex);
	int ans2 = findMin(mid+1,end,left,right,tree,2*treeindex+1);
	
	return min(ans1,ans2);
}

int main(){
	int n;  //size of input array
	cin>>n;
	
	int arr[n];
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	
	int* tree = new int[4*n];   //segment tree
	buildTree(arr,0,n-1,tree,1);
	
	int q;
	cin>>q;
	
	char c;
	while(q--){
		cin>>c;
		
		if(c=='U'){   //update type of query
			int index,val;
			cin>>index>>val;
			update(arr,0,n-1,tree,1,index,val);
		}
		else{  // find minimum in range[left,right]
			int left,right;
			cin>>left>>right;
			cout<<findMin(0,n-1,left,right,tree,1)<<endl;
		}
	}
	
	return 0;
}








