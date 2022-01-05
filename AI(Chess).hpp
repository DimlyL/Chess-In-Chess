#include<bits/stdc++.h>
#include"PreInfo(Chess).hpp"
using namespace std;
bool rightduan(int x,int y,int tor)
{
	if(board[x][y+1]==3-tor and board[x][y+2]==3-tor) return true;
	else return false;
}
bool leftduan(int x,int y,int tor)
{
	if(board[x][y-1]==3-tor and board[x][y-2]==3-tor) return true;
	else return false;
}
bool leftrightduan(int x,int y,int tor)
{
	if(board[x][y-1]==3-tor and board[x][y+1]==3-tor) return true;
	else return false;
}
bool upduan(int x,int y,int tor)
{
	if(board[x-1][y]==3-tor and board[x-2][y]==3-tor) return true;
	else return false;
}
bool downduan(int x,int y,int tor)
{
	if(board[x+1][y]==3-tor and board[x+2][y]==3-tor) return true;
	else return false;
}
bool updownduan(int x,int y,int tor)
{
	if(board[x-1][y]==3-tor and board[x+1][y]==3-tor) return true;
	else return false;
}
bool duan(int x,int y,int tor)
{
	int px=x%3,py=y%3;
	if(px==0) px=3;
	if(py==0) py=3;
	if(px==1) if(downduan(x,y,tor)) return true;
	if(px==2) if(updownduan(x,y,tor)) return true;
	if(px==3) if(upduan(x,y,tor)) return true;
	if(py==1) if(rightduan(x,y,tor)) return true;
	if(py==2) if(leftrightduan(x,y,tor)) return true;
	if(py==3) if(leftduan(x,y,tor)) return true;
	if(px==1 and py==1) if(board[x+1][y+1]==3-tor and board[x+2][y+2]==3-tor) return true;
	if(px==1 and py==3) if(board[x+1][y-1]==3-tor and board[x+2][y-2]==3-tor) return true;
	if(px==2 and py==2) if((board[x-1][y-1]==3-tor and board[x+1][y+1]==3-tor) or (board[x-1][y+1]==3-tor and board[x+1][y-1]==3-tor)) return true;
	if(px==3 and py==1) if(board[x-1][y+1]==3-tor and board[x-2][y+2]==3-tor) return true;
	if(px==3 and py==3) if(board[x-1][y-1]==3-tor and board[x-2][y-2]==3-tor) return true;
	return false;
}
int sameline(int a,int b,int c,int d)
{
	if(a==c) return 1;
	if(b==d) return 2;
	if(a-b==c-d) return 3;
	if(a+b==c+d) return 4;
	return 0;
}
bool lian(int x,int y,int tor)
{
	vector<pair<int,int> > f[5]; 
	f[1].clear();f[2].clear();f[3].clear();f[4].clear();
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			if(id[i][j]==id[x][y] and sameline(i,j,x,y) and !(i==x and j==y))
				f[sameline(i,j,x,y)].push_back(make_pair(i,j));
	for(int i=1;i<=4;i++)
		if(f[i].size()==2)
		{
			int sam=0,rival=0;
			for(int k=0;k<2;k++)
			{
				if(board[(f[i][k]).first][(f[i][k]).second]==tor) sam++;
				if(board[(f[i][k]).first][(f[i][k]).second]==3-tor) rival++;
			} 	
			if(sam==1 and rival==0) return true;
		}
	return false;
}
int adds[15][15][15];
tuple<int,int,int> check(int places,int tor,int dep) //tor �� place ���������洦 
{
	if(dep>3) return make_tuple(0,0,0);//����û�д�ֹ۵ģ�ȷ�ţ� 
	bool flag=0;
	for(int i=1;i<=9;i++)
		if(complete(i)==0)
			flag=1;
	if(flag==0) return make_tuple(0,0,0);
	vector<tuple<int,int,int> > choices;choices.clear();
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			if((id[i][j]==places or (places==10 and !complete(id[i][j]))) and !board[i][j])
			{
				board[i][j]=tor;
				int add=0;
				if(win(tor)) add+=114;
				if(complete(id[i][j])==tor) add+=3;
				if(duan(i,j,tor)) add++;
				if(lian(i,j,tor)) add+=2;
				int otherplace=to[i][j];
				if(complete(otherplace)) otherplace=10,add-=2;
				tuple<int,int,int> retu=check(otherplace,3-tor,dep+1);
				choices.push_back(make_tuple(i,j,add-(get<2>(retu))));
				adds[i][j][dep]=add;
				board[i][j]=0;
			}
	int maxn=-200,j;
	for(int i=0;i<choices.size();i++) 
		if((get<2>(choices[i]))>maxn)
		{
			maxn=(get<2>(choices[i]));
			j=i;
		}
		else if((get<2>(choices[i]))==maxn and ran(1,2)==1)
			j=i;
	return make_tuple(get<0>(choices[j]),get<1>(choices[j]),adds[get<0>(choices[j])][get<1>(choices[j])][dep]);
}
void down(int tor)
{
	/*
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
	*/
	tuple<int,int,int> retu=check(place,tor,0);
	int px=get<0>(retu),py=get<1>(retu);
	board[px][py]=tor;
	if(complete(to[px][py])) place=10;
	else place=to[px][py];
}
