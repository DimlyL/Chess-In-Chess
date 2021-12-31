#include<bits/stdc++.h>
#include<winsock2.h>
#include<windows.h>
#include<conio.h> 
#include<winsock.h>
#include"AI(Chess).hpp"
using namespace std;
SOCKADDR_IN addrServer,addrClient;
SOCKET Client;
WORD w_req;
WSADATA wsadata;
const int MAX_BUFF_LEN = 512;
char buffer[MAX_BUFF_LEN];
int WSAstart()
{
    w_req=MAKEWORD(2,2);
	return WSAStartup(w_req, &wsadata);
}
int TCP_initialize()
{
	closesocket(Client);
    if(server_mode==1)
	{
        SOCKET Listen=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        if(Listen==INVALID_SOCKET) return 1;
        addrServer.sin_family=AF_INET;
        addrServer.sin_port=htons(119);
        addrServer.sin_addr.S_un.S_addr=inet_addr("0.0.0.0");
        if(bind(Listen,(struct sockaddr*)&addrServer,sizeof(addrServer))) return 2;
        if(listen(Listen,1)) return 3;
        int sockaddr_siz=sizeof(sockaddr_in);
        Client=accept(Listen,(struct sockaddr*)&addrClient,&sockaddr_siz);
        closesocket(Listen);
    }
    else
	{
        char Server_addrstr[16]={0};
        scanf("%s",Server_addrstr);
        addrServer.sin_addr.S_un.S_addr=inet_addr(Server_addrstr);
        addrServer.sin_family=AF_INET;
        addrServer.sin_port=htons(119);
        Client=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        if(connect(Client,(struct sockaddr*)&addrServer,sizeof(addrServer)))
		{
            closesocket(Client);
			return -1;
        }
    }
    return 0;
}
void send_int(int t)
{
	memset(buffer, 0, sizeof(buffer));
	int len=0;
	if(t==0) len=1,buffer[0]='0';
	else
	{
		if(t<0) t=0-t,len++,buffer[0]='-';
		string g;
		while(t)
		{
			g.push_back(char('0'+t%10));
			t/=10;
		}	
		for(int i=g.size()-1;i>=0;i--)
			buffer[len++]=g[i];
	} 
	buffer[len]='\0';
    send(Client, buffer, len, 0);  
}
int recv_int()
{
	sockaddr_in addr;
    int len = sizeof(addr);
    int buflen = -1;
    while(buflen==-1)
	{
		while(!_kbhit())
		{
			buflen=recv(Client, buffer, MAX_BUFF_LEN, 0);
			if(buflen!=-1) break;
		}
		if(buflen!=-1) break;
		getch();
	}
    buffer[buflen] = 0x00;
    int sum=0,tt=1;
    if(buffer[0]=='-') tt=-1;
    for(int i=0;i<buflen;i++)
    	if(buffer[i]>='0' and buffer[i]<='9')
    		sum=sum*10+buffer[i]-'0';  
    return sum*tt;
}
void send_string(string t)
{
	memset(buffer, 0, sizeof(buffer));
	int len=0;
	for(int i=0;i<t.size();i++)
		buffer[len++]=t[i];
	buffer[len]='\0';
    send(Client, buffer, len, 0);  
}
string recv_string()
{
	sockaddr_in addr;
    int len = sizeof(addr);
    int buflen = -1;
    while(buflen==-1)
	{
		while(!_kbhit())
		{
			buflen=recv(Client, buffer, MAX_BUFF_LEN, 0);
			if(buflen!=-1) break;
		}
		if(buflen!=-1) break;
		getch();
	}
    buffer[buflen] = 0x00;
    string g;
    for(int i=0;i<buflen;i++)
    	g.push_back(buffer[i]);
    return g;
}
void send_int2(int t)
{
	send_int(t);
	string g=recv_string();
	while(g!="Sure") g=recv_string();
}
int recv_int2()
{
	int g=recv_int();
	send_string("Sure");
	return g;
}
void send_string2(string t)
{
	send_string(t);
	string g=recv_string();
	while(g!="Sure") g=recv_string();
}
string recv_string2()
{
	string g=recv_string();
	send_string("Sure");
	return g;
}
void send_vector_string(vector<string> &t)
{
	send_int2(t.size());
	for(int i=0;i<t.size();i++)
		send_string2(t[i]);
}
vector<string> recv_vector_string()
{
	vector<string> g;g.clear();
	int p=recv_int2();
	for(int i=0;i<p;i++)
		g.push_back(recv_string2());
	return g; 
}
void send_situation()
{
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			send_int2(board[i][j]);
	send_int2(place);
}
void recv_situation()
{
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			board[i][j]=recv_int2();
	place=recv_int2();
}
