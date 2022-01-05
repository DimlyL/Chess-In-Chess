#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<conio.h>
#include<assert.h>
#include<tchar.h>
#include"Socket(Chess).hpp"
#define iv inline void
#define REP(x) for(int i=1;i<=x;i++)
using namespace std;
using namespace __gnu_pbds;
iv straight_init_server_mode()
{
	cin>>server_mode;
	WSAstart();
	if(server_mode==1)
	{
		system("cls");
		char hostname[256]={0},ip[256]={0};
		gethostname(hostname,sizeof(hostname));
		HOSTENT* host=gethostbyname(hostname);
		strcpy(ip,inet_ntoa(*(in_addr*)*host->h_addr_list));
		printf("���ip��ַ��:%s\n\n�ȴ��������...",ip);   
	}
	if(server_mode==2)
		printf("input ip:");
	if(server_mode==3 or server_mode==4)
		return;
	if(TCP_initialize()!=0)
	{
		system("cls");
		if(server_mode==1)
		{
			print("�޷����������...�����Ƿ���ͬһ�����������л����Ժ�����...\n");
			getch();
		}
		else
		{
			print("�޷�������������...��������״�����������Ƿ���������...\n");
			getch();
		}
	}	
}
inline void printground(int num,int back)
{
	moveto(0,0);
	if(num==10)
	{
		int col[15];
		for(int i=1;i<=9;i++)
		{
			int g=complete(i);
			if(g!=0) col[i]=g+2;
			else col[i]=back;
		}
		for(int i=1;i<=9;i++)
			if(col[i]==back) printground(i,back);
		for(int i=1;i<=9;i++)
			if(col[i]!=back) printground(i,col[i]);
		return;
	}
	int x,y,tx,ty;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			if((i-1)*3+j==num)
			{
				x=3*(i-1)+1;
				y=3*(j-1)+1;
				tx=4*(i-1);
				ty=7*(j-1);
				break;
			}
	void (*say_white)(string),(*say_red)(string),(*say_blue)(string);
	if(back==0) say_white=white,say_red=red,say_blue=blue;
	if(back==1) say_white=green_white,say_red=green_red,say_blue=green_blue;
	if(back==2) say_white=yellow_white,say_red=yellow_red,say_blue=yellow_blue;
	if(back==3) say_white=red_white,say_red=red_red,say_blue=red_blue;
	if(back==4) say_white=blue_white,say_red=blue_red,say_blue=blue_blue;
	if(back==5) say_white=purple_white,say_red=purple_red,say_blue=purple_blue;
	moveto(ty,tx);say_white("+------+");
	for(int i=x;i<=x+2;i++)
	{
		moveto(ty,tx+i-x+1);
		say_white("|");
		for(int j=y;j<=y+2;j++)
		{
			if(board[i][j]==0) say_white("  ");
			if(board[i][j]==1) say_red("��");
			if(board[i][j]==2) say_blue("��");
			if(board[i][j]==3) say_white("��");
		}
		say_white("|");
	}
	moveto(ty,tx+4);say_white("+------+");
}
void game()
{
	mouse(0);
	system("mode con cols=22 lines=13");
	printground(10,0);
	if(server_mode==turn or server_mode==3)
	{
		int lastx=-1,lasty=-1,x=0,y=0;
		while(1)
		{
			POINT pt;
	  		GetPos(pt);
	  		bool flag=0;
	  		for(int i=1;i<=9;i++)
			{
	  			for(int j=1;j<=9;j++)
	  				if((id[i][j]==place or (place==10 and !complete(id[i][j]))) and board_x[i][j]==pt.x and (board_y[i][j]==pt.y or board_y[i][j]+1==pt.y) and (board[i][j]==0 or board[i][j]==3))
	  				{
		  				x=i,y=j,flag=1;
		  				break;	
					}
				if(flag) break;
			}
	  		if(!flag) x=0,y=0;
	  		if(x!=lastx or y!=lasty) 
			{
				if(server_mode!=3) send_int2(x);
				if(server_mode!=3) send_int2(y);
				for(int i=1;i<=9;i++)
					for(int j=1;j<=9;j++)
						if(board[i][j]==3)
						{
							board[i][j]=0;
							break;
						}
				board[x][y]=3;
				if(server_mode!=3) send_situation();
			 	printground(10,0);
			 	if(place!=0) printground(place,2);
				if(x!=0 and y!=0) 
				{
					if(complete(to[x][y])) printground(10,1);
					else printground(to[x][y],1);
				}
			}
	  		lastx=x,lasty=y;
	  		if(KEY_DOWN(MOUSE_MOVED) and x!=0 and y!=0) break;
		}
		if(server_mode!=3) send_int2(-1);
		if(server_mode!=3) send_int2(-1);
		if(server_mode!=3) board[x][y]=server_mode;
		else board[x][y]=1;
		if(complete(to[x][y])) place=10;
		else place=to[x][y];
		if(server_mode!=3) send_situation();
	}
	else
	{
		int x=0,y=0;
		while(1)
		{
			x=recv_int2();
			y=recv_int2();
			recv_situation();
			if(x==-1 and y==-1) break;
			printground(10,0);
			if(place!=0) printground(place,2);
			if(x!=0 and y!=0) 
			{
				if(complete(to[x][y])) printground(10,1);
				else printground(to[x][y],1);
			}
		}
	}
	turn=3-turn;
	printground(10,0);
	Sleep(100);
	if(server_mode==3)
	{
		Sleep(900);
		down(2);
		turn=1;
	}
	game();
}
int main()
{
	init();
	straight_init_server_mode();
	if(server_mode==4)
	{
		mouse(0);
		system("mode con cols=22 lines=13");
		while(1)
		{
			printground(10,0);
			printground(place,2);
			tot++;
			down(1);
			printground(10,0);
			printground(place,2);
			tot++;
			down(2);
		}
	}
	game();
}
//����Ҫ�ڱ���ѡ������� -lwsock32 ���ܽ��б��� 
