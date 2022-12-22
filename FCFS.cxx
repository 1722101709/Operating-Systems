#include<iostream>
using namespace std;
int orderness(int temp[],int n)
{ 
int a=1;
	for(int i=1;i<=n;i++)
	{
	  if(temp[i]>=temp[a] && temp[i]>=0)
	  {
			a=i;
		}
	}
	return a;
}
int main()
{
	int n;
	double avgtat=0,avgwt=0,throughput;
	cout<<"supply the processes count\n";
	cin>>n;
	int *at=new int[n+1];
	int *bt=new int[n+1];
	int *ct=new int[n+1];
	int *wt=new int[n+1];
	int *tat=new int[n+1];
	int *p=new int[n+1];
	int *temp=new int[n+1];
	cout<<"give the arrival and burst times of each process one after other\n";
	at[0]=0;
	bt[0]=0;
	p[0]=0;
	for(int i=1;i<=n;i++)
	{
		cin>>at[i]>>bt[i];
	}
	for(int i=0;i<=n;i++)
	{
		temp[i]=at[i];
	}
	for(int i=n;i>0;i--)
	{
		p[i]=orderness(temp,n);
		temp[p[i]]=-1;
	}
	ct[p[1]]=at[p[1]]+bt[p[1]];
	wt[p[1]]=0;
	tat[p[1]]=ct[p[1]]-at[p[1]];
	for(int i=2;i<=n;i++)
	{
ct[p[i]]=(ct[p[i-1]]>at[p[i]])?(ct[p[i-1]]+bt[p[i]]):(at[p[i]]+bt[p[i]]);
wt[p[i]]=(ct[p[i-1]]>at[p[i]])?(ct[p[i-1]]-at[p[i]]):0;
		tat[p[i]]=ct[p[i]]-at[p[i]];
	}
	for(int i=1;i<=n;i++)
	{
		avgtat=tat[i]+avgtat;
		avgwt=wt[i]+avgwt;
	}
	avgwt/=n;
	avgtat/=n;
	cout<<"pid  at   bt   ct   tat   wt  "<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<p[i]<<"   "<<at[p[i]]<<"    "<<bt[p[i]]<<"    "<<ct[p[i]]<<"    "<<tat[p[i]]<<"    "<<wt[p[i]]<<"    "<<endl;
	}
	cout<<endl<<endl<<"average wt="<<avgwt<<endl<<"average tat="<<avgtat<<endl;cout<<"throughput="<<n<<"/"<<ct[p[n]]<<endl;
}