#include<iostream>
using namespace std;

void print(int x[][10],int n,int m){
	int i,j;
	for(i=0;i<n;i++){
		cout<<"\n";
		for(j=0;j<m;j++){
			cout<<"\t"<<x[i][j];
		}
	}	
}

//Resource Request algorithm
void res_request(int A[10][10],int N[10][10],int AV[10][10],int pid,int m)
{
	int reqmat[1][10];
	int i;
	cout<<"\n Enter additional request :- \n";
	for(i=0;i<m;i++){
		cout<<" Request for resource  : "<<i+1;
		cin>>reqmat[0][i];
	}
	
	for(i=0;i<m;i++)
		if(reqmat[0][i] > N[pid][i]){
		cout<<"\n Error encountered.\n";
			exit(0);
	}

	for(i=0;i<m;i++)
		if(reqmat[0][i] > AV[0][i]){
			cout<<"\n Resources unavailable.\n";
			exit(0);
		}
	
	for(i=0;i<m;i++){
		AV[0][i]-=reqmat[0][i];
		A[pid][i]+=reqmat[0][i];
		N[pid][i]-=reqmat[0][i];
	}
}

//Safety algorithm
int safety(int A[][10],int N[][10],int AV[1][10],int n,int m,int a[]){

	int i,j,k,x=0;
	int F[10],W[1][10];
	int pflag=0,flag=0;
	for(i=0;i<n;i++)
		F[i]=0;
	for(i=0;i<m;i++)
		W[0][i]=AV[0][i];

	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			if(F[i] == 0){
				flag=0;
				for(j=0;j<m;j++){
					if(N[i][j] > W[0][j])
						flag=1;
				}
				if(flag == 0 && F[i] == 0){
					for(j=0;j<m;j++)
						W[0][j]+=A[i][j];
					F[i]=1;
					pflag++;
					a[x++]=i;
				}
			}
		}
		if(pflag == n)
			return 1;
	}
	return 0;
}


//Banker's Algorithm
void accept(int A[][10],int N[][10],int M[10][10],int W[1][10],int *n,int *m){
	int i,j;
	cout<<"\n Enter total no. of processes : ";
	cin >> *n;
	cout<<"\n Enter total no. of resources : ";
		cin>>*m;
	for(i=0;i<*n;i++){
		cout<<"\n Process "<<i+1<<"\n";
		for(j=0;j<*m;j++){
		cout<<" Allocation for resource "<<j+1<<": ";
			cin>>A[i][j];
		cout<<" Maximum for resource "<<j+1<<": ";
				cin>>M[i][j];
		}
	}
	cout<<"\n Available resources : \n";
	for(i=0;i<*m;i++){
		cout<<" Resource "<<i+1<<": ";
			cin>>W[0][i];
	}

	for(i=0;i<*n;i++)
		for(j=0;j<*m;j++)
			N[i][j]=M[i][j]-A[i][j];

	cout<<"\n Allocation Matrix";
	print(A,*n,*m);
	cout<<"\n Maximum Requirement Matrix";
	print(M,*n,*m);
	cout<<"\n Need Matrix";
	print(N,*n,*m);

}

int banker(int A[][10],int N[][10],int W[1][10],int n,int m){
	int j,i,a[10];
	j=safety(A,N,W,n,m,a);
	if(j != 0 ){
		cout<<"\n\n";
		for(i=0;i<n;i++)
		     cout<<" P "<<a[i];
		cout<<"\n A safety sequence has been detected.\n";
		return 1;
	}else{
	cout<<"\n Deadlock has occured.\n";
		return 0;
	}
}


int main(){
	int ret;
	int A[10][10];
	int M[10][10];
	int N[10][10];
	int W[1][10];
	int n,m,pid,ch;
	cout<<"\n DEADLOCK AVOIDANCE USING BANKER'S ALGORITHM\n";
	accept(A,N,M,W,&n,&m);
	ret=banker(A,N,W,n,m);
	
	return 0;
}
