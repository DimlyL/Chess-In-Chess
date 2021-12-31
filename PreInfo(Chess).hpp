#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define iv inline void
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
using namespace __gnu_pbds;
iv moveto(int a,int b) //�� �� 
{
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen={short(a),short(b)};
	SetConsoleCursorPosition(hConsole,coordScreen);
}
iv mouse(int a)
{
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle,&CursorInfo);
	CursorInfo.bVisible=a;
	SetConsoleCursorInfo(handle,&CursorInfo);
}
inline int ran(int l,int r)
{
	return rand()%(r-l+1)+l;
}
bool found(vector<string> &t,string a)
{
	vector<string>::iterator it=find(t.begin(),t.end(),a);
    if(it!=t.end()) return true;
    else return false;
}
int founds(vector<string> &t,string a)
{
	for(int i=0;i<t.size();i++)
		if(t[i]==a)
			return i;
}
void SetColor(short x);
#define Set SetColor(7)
iv print(string a){for(int i=0;i<a.size();i++){putchar(a[i]);}}
iv red(string u){SetColor(12);print(u);Set;}
iv green_red(string u){SetColor(2*16+12);print(u);Set;}
iv yellow_red(string u){SetColor(14*16+12);print(u);Set;}
iv red_red(string u){SetColor(4*16+12);print(u);Set;}
iv blue_red(string u){SetColor(1*16+12);print(u);Set;}
iv purple_red(string u){SetColor(13*16+12);print(u);Set;}

iv blue(string u){SetColor(9);print(u);Set;}
iv green_blue(string u){SetColor(2*16+9);print(u);Set;}
iv yellow_blue(string u){SetColor(14*16+9);print(u);Set;}
iv red_blue(string u){SetColor(4*16+9);print(u);Set;}
iv blue_blue(string u){SetColor(1*16+9);print(u);Set;}
iv purple_blue(string u){SetColor(13*16+9);print(u);Set;}

iv green(string u){SetColor(10);print(u);Set;}
iv yellow(string u){SetColor(14);print(u);Set;}
iv cyan(string u){SetColor(11);print(u);Set;}
iv purple(string u){SetColor(13);print(u);Set;}

iv white(string u){SetColor(7);print(u);Set;}
iv green_white(string u){SetColor(2*16+7);print(u);Set;}
iv yellow_white(string u){SetColor(14*16+7);print(u);Set;}
iv red_white(string u){SetColor(4*16+7);print(u);Set;} 
iv blue_white(string u){SetColor(1*16+7);print(u);Set;} 
iv purple_white(string u){SetColor(13*16+7);print(u);Set;} 

iv grey(string u){SetColor(8);print(u);Set;}
iv putspace(int t){for(int i=1;i<=t;i++) putchar(' ');}
template <typename T>
inline string change(T a){stringstream ss;string s;ss.clear();ss.str("");ss<<a;ss>>s;return s;} 
template <typename T>
inline int change2(T a){stringstream ss;int s;ss.clear();ss.str("");ss<<a;ss>>s;return s;}

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define ENTER 13
bool upc(char c){if(c=='W' or c=='w' or c==UP) return true;return false;}
bool downc(char c){if(c=='S' or c=='s' or c==DOWN) return true;return false;}
bool leftc(char c){if(c=='A' or c=='a' or c==LEFT) return true;return false;}
bool rightc(char c){if(c=='D' or c=='d' or c==RIGHT) return true;return false;}
bool surec(char c){if(c==SPACE or c==ENTER) return true;return false;}
bool usec(char c){if(c=='Z' or c=='z' or c=='+') return true;return false;}
bool magicc(char c){if(c=='X' or c=='x' or c=='-') return true;return false;}

int board[15][15];
int board_x[15][15],board_y[15][15];
int id[15][15],to[15][15];
int server_mode;
int place=5;

int turn=1;
inline int chan(int x)
{
	if(x==3) return turn;
	return x;
}
inline int complete(int num)
{
	int x=0,y=0;
	for(int i=1;i<=9;i++)
	{
		for(int j=1;j<=9;j++)
			if(id[i][j]==num)
			{
				x=i,y=j;
				break;
			}
		if(x!=0) break;
	}
	for(int k=1;k<=2;k++)
	{
		for(int i=0;i<=2;i++)
			if(chan(board[x+i][y])==k and chan(board[x+i][y+1])==k and chan(board[x+i][y+2])==k) return k;
		for(int j=0;j<=2;j++)
			if(chan(board[x][y+j])==k and chan(board[x+1][y+j])==k and chan(board[x+2][y+j])==k) return k;
		if(chan(board[x][y])==k and chan(board[x+1][y+1])==k and chan(board[x+2][y+2])==k) return k;
		if(chan(board[x+2][y])==k and chan(board[x+1][y+1])==k and chan(board[x][y+2])==k) return k;
	}
	bool flag=0;
	for(int i=0;i<=2;i++)
		for(int j=0;j<=2;j++)
			if(board[x+i][y+j]==0)
			{
				flag=1;
				break;
			}
	if(flag==0) return 3;
	return 0;
}

iv init()
{
	srand(time(NULL));
	mouse(0);
	system("mode con cols=22 lines=13");
	SetConsoleTitle("Chess");
	
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
		{
			if(i==1) board_x[i][j]=1;
			else
			{
				board_x[i][j]=board_x[i-1][j]+1;
				if(i%3==1) board_x[i][j]++;
			}
			if(j==1) board_y[i][j]=1;
			else
			{
				board_y[i][j]=board_y[i][j-1]+2;
				if(j%3==1) board_y[i][j]++;
			}
		}
	for(int i=1;i<=9;i++)
		id[1][i]=(i-1)/3+1;
	for(int i=2;i<=9;i++)
		for(int j=1;j<=9;j++)
		{
			id[i][j]=id[i-1][j];
			if(i%3==1) id[i][j]+=3;
		} 
	/*
	1 1 1 2 2 2 3 3 3
	1 1 1 2 2 2 3 3 3
	1 1 1 2 2 2 3 3 3
	4 4 4 5 5 5 6 6 6
	4 4 4 5 5 5 6 6 6
	4 4 4 5 5 5 6 6 6
	7 7 7 8 8 8 9 9 9
	7 7 7 8 8 8 9 9 9
	7 7 7 8 8 8 9 9 9
	*/
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
		{
			int sum=0;
			for(int k=(i-1)*3+1;k<=(i-1)*3+3;k++)
				for(int l=(j-1)*3+1;l<=(j-1)*3+3;l++)
					to[k][l]=++sum;
		}
	/*
	1 2 3 1 2 3 1 2 3
	4 5 6 4 5 6 4 5 6
	7 8 9 7 8 9 7 8 9
	1 2 3 1 2 3 1 2 3
	4 5 6 4 5 6 4 5 6
	7 8 9 7 8 9 7 8 9
	1 2 3 1 2 3 1 2 3
	4 5 6 4 5 6 4 5 6
	7 8 9 7 8 9 7 8 9
	*/
}

//From Hape Flying Game
void GetPos(POINT &pt){
    HWND hwnd=GetForegroundWindow();
    GetCursorPos(&pt);
    ScreenToClient(hwnd,&pt);
    pt.y=pt.y/36,pt.x=pt.x/18;
    swap(pt.x,pt.y);
}

//From CARD-GAME
void SetColor(short x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void Shake(int power,int time){
	int shake_time = 25;
    int shake_distance = power;
    RECT rect;
    HWND window = NULL, oldwindow = NULL;
    int x, y, width, height;
    int i;
    for (i = 0; i < time; i++) {
        window = GetForegroundWindow();
        if (window != oldwindow) {
            GetWindowRect(window, &rect);
            x = rect.left;
            y = rect.top;
            width = rect.right - x;
            height = rect.bottom - y;
            oldwindow = window;
        }
        MoveWindow(window, x - shake_distance, y, width, height, TRUE); 
        Sleep(shake_time); 
        MoveWindow(window, x - shake_distance, y - shake_distance, width, height, TRUE);
        Sleep(shake_time);
        MoveWindow(window, x, y - shake_distance, width, height, TRUE);
        Sleep(shake_time);
        MoveWindow(window, x, y, width, height, TRUE);
        Sleep(shake_time);
    }
    return;
}
