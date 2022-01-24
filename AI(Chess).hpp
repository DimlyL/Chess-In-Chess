#include<bits/stdc++.h>
#include"PreInfo(Chess).hpp"
using namespace std;
int duan(int x,int y,int tor)
{
	int px=x%3,py=y%3;
	if(px==0) px=3;
	if(py==0) py=3;
	int ans=0,otor=3-tor;
	if(px==1) if(board[x+1][y]==otor and board[x+2][y]==otor) ans++;
	if(px==2) if(board[x-1][y]==otor and board[x+1][y]==otor) ans++;
	if(px==3) if(board[x-1][y]==otor and board[x-2][y]==otor) ans++;
	if(py==1) if(board[x][y+1]==otor and board[x][y+2]==otor) ans++;
	if(py==2) if(board[x][y-1]==otor and board[x][y+1]==otor) ans++;
	if(py==3) if(board[x][y-1]==otor and board[x][y-2]==otor) ans++;
	if(px==1 and py==1) if(board[x+1][y+1]==otor and board[x+2][y+2]==otor) ans++;
	if(px==1 and py==3) if(board[x+1][y-1]==otor and board[x+2][y-2]==otor) ans++;
	if(px==2 and py==2) if(board[x-1][y-1]==otor and board[x+1][y+1]==otor) ans++;
	if(px==2 and py==2) if(board[x-1][y+1]==otor and board[x+1][y-1]==otor) ans++;
	if(px==3 and py==1) if(board[x-1][y+1]==otor and board[x-2][y+2]==otor) ans++;
	if(px==3 and py==3) if(board[x-1][y-1]==otor and board[x-2][y-2]==otor) ans++;
	return ans;
}
int sameline(int a,int b,int c,int d)
{
	if(a==c) return 1;
	if(b==d) return 2;
	if(a-b==c-d) return 3;
	if(a+b==c+d) return 4;
	return 0;
}
int lian(int x,int y,int tor)
{
	vector<pair<int,int> > f[5]; 
	f[1].clear();f[2].clear();f[3].clear();f[4].clear();
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			if(id[i][j]==id[x][y] and sameline(i,j,x,y) and !(i==x and j==y))
				f[sameline(i,j,x,y)].push_back(make_pair(i,j));
	int ans=0;
	for(int i=1;i<=4;i++)
		if(f[i].size()==2)
		{
			int sam=0,rival=0;
			for(int k=0;k<2;k++)
			{
				if(board[(f[i][k]).first][(f[i][k]).second]==tor) sam++;
				if(board[(f[i][k]).first][(f[i][k]).second]==3-tor) rival++;
			} 	
			if(sam==1 and rival==0) ans++;
		}
	return ans;
}
int big_duan(int places,int tor)
{
	int xx[15];
	for(int i=1;i<=9;i++)
		xx[i]=complete(i);
	int ans=0,otor=3-tor;
	int t1,t2;
	
	if(places%3==1) t1=places+1,t2=places+2;
	else if(places%3==2) t1=places-1,t2=places+1;
	else t1=places-2,t2=places-1;
	if(xx[t1]==otor and xx[t2]==otor) ans++;
	
	if(places<=3) t1=places+3,t2=places+6;
	else if(places<=6) t1=places-3,t2=places+3;
	else t1=places-6,t2=places-3;
	if(xx[t1]==otor and xx[t2]==otor) ans++;
	
	if(places==1 and xx[5]==otor and xx[9]==otor) ans++;
	if(places==3 and xx[5]==otor and xx[7]==otor) ans++;
	if(places==5 and xx[1]==otor and xx[9]==otor) ans++;
	if(places==5 and xx[3]==otor and xx[7]==otor) ans++;
	if(places==7 and xx[5]==otor and xx[3]==otor) ans++;
	if(places==9 and xx[5]==otor and xx[1]==otor) ans++;
	
	return ans;
}
int big_sameline(int places1,int places2)
{
	int px1=(places1-1)/3+1,py1=places1-(px1-1)*3;
	int px2=(places2-1)/3+1,py2=places2-(px2-1)*3;
	if(px1==px2) return 1;
	if(py1==py2) return 2;
	if(px1-py1==px2-py2) return 3;
	if(px1+py1==px2+py2) return 4;
	return 0;
}
int big_lian(int places,int tor)
{
	int xx[15];
	for(int i=1;i<=9;i++)
		xx[i]=complete(i);
	vector<int> f[5]; 
	f[1].clear();f[2].clear();f[3].clear();f[4].clear();
	for(int i=1;i<=9;i++)
		if(big_sameline(places,i) and i!=places)
			f[big_sameline(places,i)].push_back(i);
	int ans=0;
	for(int i=1;i<=4;i++)
		if(f[i].size()==2)
		{
			int sam=0,rival=0;
			for(int k=0;k<2;k++)
			{
				if(xx[f[i][k]]==tor) sam++;
				if(xx[f[i][k]]==3-tor) rival++;
			} 	
			if(sam==1 and rival==0) ans++;
		}
	return ans;
}
int adds[15][15][15];
tuple<int,int,int> check(int places,int tor,int dep) //tor 在 place 下棋的最大益处 
{
	if(dep>4) return make_tuple(0,0,0);//人是没有大局观的（确信） 
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
				if(win(tor)) 
				{
					add+=114;
					choices.push_back(make_tuple(i,j,add));
				}
				else
				{
					if(complete(id[i][j])==tor)
					{
						add+=4+big_duan(id[i][j],tor);
						int k=big_lian(id[i][j],tor);
						if(k) add+=k+1;
					}
					else
					{
						add+=duan(i,j,tor);
						int k=lian(i,j,tor);
						if(k) add+=k+1; 
					}
					int otherplace=to[i][j];
					if(complete(otherplace)) otherplace=10,add-=3;
					tuple<int,int,int> retu=check(otherplace,3-tor,dep+1);
					choices.push_back(make_tuple(i,j,add-(get<2>(retu))));	
				}
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
