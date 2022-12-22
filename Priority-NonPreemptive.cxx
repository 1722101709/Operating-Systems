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
int prion(int prt[],int at[],int p[],int arv,int n)
{
	int a=0,count=0;
	for(int i=1;i<=n;i++)
	{
	 if(at[p[i]]>=0)
	 {
	   count++;
	   if(count==1 && at[p[i]]<=arv)
	   {
	   	a=p[i];
	   }
	   if(at[p[i]]<=arv&&  prt[p[i]]>prt[a])
    	{
	  	a=p[i];
     	}
  	}
	}
	if(a)
	{
       return a;
	}
	return prion(prt,at,p,arv+1,n);
}
int main()
{
	int n;
	double avgtat=0,avgwt=0;
	cout<<"supply the processes count\n";
	cin>>n;
	int *at=new int[n+1];
	int *bt=new int[n+1];
	int *ct=new int[n+1];
	int *wt=new int[n+1];
	int *tat=new int[n+1];
	int *p=new int[n+1];
	int *temp=new int[n+1];
	int *q=new int[n+1];
	int *temparv=new int[n+1];
	int *prt=new int[n+1];
	cout<<"give the arrival time, burst time and priority of each process one after other\n";
	at[0]=0;
	bt[0]=0;
	p[0]=0;
	for(int i=1;i<=n;i++)
	{
		cin>>at[i]>>bt[i]>>prt[i];
	}
	for(int i=0;i<=n;i++)
	{
		temp[i]=at[i];
		temparv[i]=at[i];
	}
	for(int i=n;i>0;i--)
	{
		p[i]=orderness(temp,n);
		temp[p[i]]=-1;
	}
		for(int i=0;i<=n;i++)
	{
		temp[i]=prt[i];
	}
	ct[0]=at[p[1]];
	q[0]=0;
	for(int i=1;i<=n;i++)
	{
		q[i]=prion(temp,temparv,p,ct[q[i-1]],n);
	    ct[q[i]]=(ct[q[i-1]]>at[q[i]])?(ct[q[i-1]]+bt[q[i]]):(at[q[i]]+bt[q[i]]);
		temparv[q[i]]=-1;
	}
	wt[q[1]]=0;
	tat[q[1]]=ct[q[1]]-at[q[1]];
	for(int i=2;i<=n;i++)
	{
wt[q[i]]=(ct[q[i-1]]>at[q[i]])?(ct[q[i-1]]-at[q[i]]):0;
		tat[q[i]]=ct[q[i]]-at[q[i]];
	}
	for(int i=1;i<=n;i++)
	{
		avgtat=tat[i]+avgtat;
		avgwt=wt[i]+avgwt;
	}
	avgwt/=n;
	avgtat/=n;
	cout<<"pid  at   bt   prt   ct   tat   wt  "<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<q[i]<<"    "<<at[q[i]]<<"    "<<bt[q[i]]<<"    "<<prt[q[i]]<<"     "<<ct[q[i]]<<"     "<<tat[q[i]]<<"    "<<wt[q[i]]<<"    "<<endl;
	}
	cout<<endl<<endl<<"average wt="<<avgwt<<endl<<"average tat="<<avgtat<<endl;cout<<"throughput="<<n<<"/"<<ct[q[n]]<<endl;
}