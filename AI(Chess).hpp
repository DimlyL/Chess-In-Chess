#include<bits/stdc++.h>
#include"PreInfo(Chess).hpp"
using namespace std;
bool check(int num)
{
	
}
void down()
{
	vector<int> x,y;x.clear();y.clear(); 
	if(place==10)
	{
		for(int i=1;i<=9;i++)
			for(int j=1;j<=9;j++)
				if(!complete(id[i][j]) and !board[i][j])
				{
					x.push_back(i);
					y.push_back(j);
				}
	}
	else
	{
		for(int i=1;i<=9;i++)
			for(int j=1;j<=9;j++)
				if(id[i][j]==place and !board[i][j])
				{
					x.push_back(i);
					y.push_back(j);
				}
	}
	int s=ran(0,x.size()-1);
	int px=x[s],py=y[s];
	board[px][py]=2;
	if(complete(to[px][py])) place=10;
	else place=to[px][py];
}
