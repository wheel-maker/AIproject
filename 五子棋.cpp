#include<iostream>
#include<cstring>
#include<cstdio>
#include<Windows.h>
using namespace std;


const int INF=999999999;
const int MAXDEPTH=4;
const char CH[100]={"╚╝═║╦╩╠╬╣╔╗●○"};
const int LINE=15;
int a[LINE+2][LINE+2];
int b[LINE+2][LINE+2];//aid
int maxb=-1;
struct MOVE{
	int x;
	int y;
}NEXT;
int QJMODE;
int duel()
{
	for(int i=1;i<=LINE;i++)
	{
		for(int j=1;j<=LINE;j++)
		{
			if(a[i][j]==0)
				return 0;
		}
	}
	return 1;
}
int gameover()
{
	int judge=0;
	for(int i=1;i<=LINE-4;i++)
	{
		for(int j=1;j<=LINE;j++)
		{
			if(j<=LINE-4)
			{
				if(a[i][j]==1&&a[i+1][j]==1&&a[i+2][j]==1&&a[i+3][j]==1&&a[i+4][j]==1)
					judge=1;
				else if(a[i][j]==2&&a[i+1][j]==2&&a[i+2][j]==2&&a[i+3][j]==2&&a[i+4][j]==2)
					judge=2;
				else if(a[i][j]==1&&a[i][j+1]==1&&a[i][j+2]==1&&a[i][j+3]==1&&a[i][j+4]==1)
					judge=1;
				else if(a[i][j]==2&&a[i][j+1]==2&&a[i][j+2]==2&&a[i][j+3]==2&&a[i][j+4]==2)
					judge=2;
				else if(a[i][j]==1&&a[i+1][j+1]==1&&a[i+2][j+2]==1&&a[i+3][j+3]==1&&a[i+4][j+4]==1)
					judge=1;
				else if(a[i][j]==2&&a[i+1][j+1]==2&&a[i+2][j+2]==2&&a[i+3][j+3]==2&&a[i+4][j+4]==2)
					judge=2;
			}
			if(j>=5)
			{
				if(a[i][j]==2&&a[i+1][j-1]==2&&a[i+2][j-2]==2&&a[i+3][j-3]==2&&a[i+4][j-4]==2)
					judge=2;
				if(a[i][j]==1&&a[i+1][j-1]==1&&a[i+2][j-2]==1&&a[i+3][j-3]==1&&a[i+4][j-4]==1)
					judge=1;
			}
		}
		if(judge!=0)
			break;
	}
	return judge;
}
int nbmove()//neighbormove
{
	maxb=-1;
	int cnt=0;
	memset(b,0,(LINE+2)*(LINE+2)*sizeof(int));
	for(int i=1;i<=LINE;i++)
	{
		for(int j=1;j<=LINE;j++)
		{
			if(a[i][j]==0&&(a[i-1][j]!=0||a[i+1][j]!=0||a[i][j+1]!=0||a[i][j-1]!=0
			||a[i-1][j-1]!=0||a[i-1][j+1]!=0||a[i+1][j-1]!=0||a[i+1][j+1]!=0))
			{
				b[i][j]=1;
				cnt++;
			}	
		}	
	}	
	return cnt;
} 
int value(int t)
{
	int op;//opponent
	op=3-t;
	int val=0;
	for(int i=1;i<=LINE;i++)
	{
		for(int j=1;j<=LINE;j++)
		{
			/*
			if(a[i][j]==0&&a[i][j+1]==t&&a[i][j+2]==0)
				val+=20;
			if(a[i][j]==op&&a[i][j+1]==t&&a[i][j+2]==0)
				val+=10;
			if(a[i][j]==0&&a[i][j+1]==t&&a[i][j+2]==op)
				val+=10;
			if(a[i][j]==0&&a[i+1][j]==t&&a[i+2][j]==0)
				val+=20;
			if(a[i][j]==op&&a[i+1][j]==t&&a[i+2][j]==0)
				val+=10;
			if(a[i][j]==0&&a[i+1][j]==t&&a[i+2][j]==op)
				val+=10;
			if(a[i][j]==0&&a[i+1][j+1]==t&&a[i+2][j+2]==0)
				val+=20;
			if(a[i][j]==op&&a[i+1][j+1]==t&&a[i+2][j+2]==0)
				val+=10;
			if(a[i][j]==0&&a[i+1][j+1]==t&&a[i+2][j+2]==op)
				val+=10;
			*/	
			
			if(i<=LINE-4&&j>=5)
			{
				
				if(a[i][j]==0&&a[i+1][j-1]==t&&a[i+2][j-2]==t&&a[i+3][j-3]==0&&a[i+4][j-4]==0)
					val+=100;
				if(a[i][j]==0&&a[i+1][j-1]==0&&a[i+2][j-2]==t&&a[i+3][j-3]==t&&a[i+4][j-4]==0)
					val+=100;
				if(a[i][j]==0&&a[i+1][j-1]==0&&a[i+2][j-2]==t&&a[i+3][j-3]==t&&a[i+4][j-4]==t)
					val+=1000;
				if(a[i][j]==t&&a[i+1][j-1]==t&&a[i+2][j-2]==t&&a[i+3][j-3]==0&&a[i+4][j-4]==0)
					val+=1000;
				//0tttt tttt0 t0ttt ttt0t tt0tt 0ttt0 ttttt
				if(a[i][j]==0&&a[i+1][j-1]==t&&a[i+2][j-2]==t&&a[i+3][j-3]==t&&a[i+4][j-4]==t)
					val+=10000;
				if(a[i][j]==t&&a[i+1][j-1]==t&&a[i+2][j-2]==t&&a[i+3][j-3]==t&&a[i+4][j-4]==0)
					val+=10000;	
				if(a[i][j]==t&&a[i+1][j-1]==0&&a[i+2][j-2]==t&&a[i+3][j-3]==t&&a[i+4][j-4]==t)
					val+=10000;
				if(a[i][j]==t&&a[i+1][j-1]==t&&a[i+2][j-2]==t&&a[i+3][j-3]==0&&a[i+4][j-4]==t)
					val+=10000;
				if(a[i][j]==t&&a[i+1][j-1]==t&&a[i+2][j-2]==0&&a[i+3][j-3]==t&&a[i+4][j-4]==t)
					val+=10000;
				if(a[i][j]==0&&a[i+1][j-1]==t&&a[i+2][j-2]==t&&a[i+3][j-3]==t&&a[i+4][j-4]==0)
					val+=10000;
				
				if(a[i][j]==t&&a[i+1][j-1]==t&&a[i+2][j-2]==t&&a[i+3][j-3]==t&&a[i+4][j-4]==t)
					val+=100000000;
				if(i<=LINE-5&&j>=5)
				{
					if(a[i][j]==0&&a[i+1][j-1]==t&&a[i+2][j-2]==0&&a[i+3][j-3]==t&&a[i+4][j-4]==t&&a[i+5][j-5]==0)
						val+=10000;
					if(a[i][j]==0&&a[i+1][j-1]==t&&a[i+2][j-2]==t&&a[i+3][j-3]==0&&a[i+4][j-4]==t&&a[i+5][j-5]==0)
						val+=10000;
					if(a[i][j]==0&&a[i+1][j-1]==t&&a[i+2][j-2]==t&&a[i+3][j-3]==t&&a[i+4][j-4]==t&&a[i+5][j-5]==0)
						val+=1000000;
				}
			}
			if(i<=LINE-4&&j<=LINE-4)
			{
				if(a[i][j]==0&&a[i][j+1]==t&&a[i][j+2]==t&&a[i][j+3]==0&&a[i][j+4]==0)
					val+=100;
				if(a[i][j]==0&&a[i][j+1]==0&&a[i][j+2]==t&&a[i][j+3]==t&&a[i][j+4]==0)
					val+=100;
				if(a[i][j]==0&&a[i+1][j]==t&&a[i+2][j]==t&&a[i+3][j]==0&&a[i+4][j]==0)
					val+=100;
				if(a[i][j]==0&&a[i+1][j]==0&&a[i+2][j]==t&&a[i+3][j]==t&&a[i+4][j]==0)
					val+=100;
				if(a[i][j]==0&&a[i+1][j+1]==t&&a[i+2][j+2]==t&&a[i+3][j+3]==0&&a[i+4][j+4]==0)
					val+=100;
				if(a[i][j]==0&&a[i+1][j+1]==0&&a[i+2][j+2]==t&&a[i+3][j+3]==t&&a[i+4][j+4]==0)
					val+=100;
				
				if(a[i][j]==0&&a[i][j+1]==0&&a[i][j+2]==t&&a[i][j+3]==t&&a[i][j+4]==t)
					val+=1000;
				if(a[i][j]==t&&a[i][j+1]==t&&a[i][j+2]==t&&a[i][j+3]==0&&a[i][j+4]==0)
					val+=1000;
				if(a[i][j]==0&&a[i+1][j]==0&&a[i+2][j]==t&&a[i+3][j]==t&&a[i+4][j]==t)
					val+=1000;
				if(a[i][j]==t&&a[i+1][j]==t&&a[i+2][j]==t&&a[i+3][j]==0&&a[i+4][j]==0)
					val+=1000;
				if(a[i][j]==0&&a[i+1][j+1]==0&&a[i+2][j+2]==t&&a[i+3][j+3]==t&&a[i+4][j+4]==t)
					val+=1000;
				if(a[i][j]==t&&a[i+1][j+1]==t&&a[i+2][j+2]==t&&a[i+3][j+3]==0&&a[i+4][j+4]==0)
					val+=1000;
				
				if(a[i][j]==0&&a[i][j+1]==t&&a[i][j+2]==t&&a[i][j+3]==t&&a[i][j+4]==t)
					val+=10000;
				if(a[i][j]==t&&a[i][j+1]==t&&a[i][j+2]==t&&a[i][j+3]==t&&a[i][j+4]==0)
					val+=10000;
				if(a[i][j]==0&&a[i+1][j]==t&&a[i+2][j]==t&&a[i+3][j]==t&&a[i+4][j]==t)
					val+=10000;
				if(a[i][j]==t&&a[i+1][j]==t&&a[i+2][j]==t&&a[i+3][j]==t&&a[i+4][j]==0)
					val+=10000;
				if(a[i][j]==0&&a[i+1][j+1]==t&&a[i+2][j+2]==t&&a[i+3][j+3]==t&&a[i+4][j+4]==t)
					val+=10000;
				if(a[i][j]==t&&a[i+1][j+1]==t&&a[i+2][j+2]==t&&a[i+3][j+3]==t&&a[i+4][j+4]==0)
					val+=10000;
				
				if(a[i][j]==t&&a[i][j+1]==0&&a[i][j+2]==t&&a[i][j+3]==t&&a[i][j+4]==t)
					val+=10000;
				if(a[i][j]==t&&a[i][j+1]==t&&a[i][j+2]==t&&a[i][j+3]==0&&a[i][j+4]==t)
					val+=10000;
				if(a[i][j]==t&&a[i+1][j]==0&&a[i+2][j]==t&&a[i+3][j]==t&&a[i+4][j]==t)
					val+=10000;
				if(a[i][j]==t&&a[i+1][j]==t&&a[i+2][j]==t&&a[i+3][j]==0&&a[i+4][j]==t)
					val+=10000;
				if(a[i][j]==t&&a[i+1][j+1]==0&&a[i+2][j+2]==t&&a[i+3][j+3]==t&&a[i+4][j+4]==t)
					val+=10000;
				if(a[i][j]==t&&a[i+1][j+1]==t&&a[i+2][j+2]==t&&a[i+3][j+3]==0&&a[i+4][j+4]==t)
					val+=10000;
					
				if(a[i][j]==t&&a[i][j+1]==t&&a[i][j+2]==0&&a[i][j+3]==t&&a[i][j+4]==t)
					val+=10000;
				if(a[i][j]==t&&a[i+1][j]==t&&a[i+2][j]==0&&a[i+3][j]==t&&a[i+4][j]==t)
					val+=10000;
				if(a[i][j]==t&&a[i+1][j+1]==t&&a[i+2][j+2]==0&&a[i+3][j+3]==t&&a[i+4][j+4]==t)
					val+=10000;
				if(a[i][j]==0&&a[i][j+1]==t&&a[i][j+2]==t&&a[i][j+3]==t&&a[i][j+4]==0)
					val+=10000;
				if(a[i][j]==0&&a[i+1][j]==t&&a[i+2][j]==t&&a[i+3][j]==t&&a[i+4][j]==0)
					val+=10000;
				if(a[i][j]==0&&a[i+1][j+1]==t&&a[i+2][j+2]==t&&a[i+3][j+3]==t&&a[i+4][j+4]==0)
					val+=10000;
				if(i<=LINE-5&&j<=LINE-5)
				{
					if(a[i][j]==0&&a[i][j+1]==t&&a[i][j+2]==0&&a[i][j+3]==t&&a[i][j+4]==t&&a[i][j+5]==0)
						val+=10000;
					if(a[i][j]==0&&a[i][j+1]==t&&a[i][j+2]==t&&a[i][j+3]==0&&a[i][j+4]==t&&a[i][j+5]==0)
						val+=10000;
					if(a[i][j]==0&&a[i+1][j]==t&&a[i+2][j]==0&&a[i+3][j]==t&&a[i+4][j]==t&&a[i+5][j]==0)
						val+=10000;
					if(a[i][j]==0&&a[i+1][j]==t&&a[i+2][j]==t&&a[i+3][j]==0&&a[i+4][j]==t&&a[i+5][j]==0)
						val+=10000;
					if(a[i][j]==0&&a[i+1][j+1]==t&&a[i+2][j+2]==0&&a[i+3][j+3]==t&&a[i+4][j+4]==t&&a[i+5][j+5]==0)
						val+=10000;
					if(a[i][j]==0&&a[i+1][j+1]==t&&a[i+2][j+2]==t&&a[i+3][j+3]==0&&a[i+4][j+4]==t&&a[i+5][j+5]==0)
						val+=10000;
				//a
					if(a[i][j]==0&&a[i][j+1]==t&&a[i][j+2]==t&&a[i][j+3]==t&&a[i][j+4]==t&&a[i][j+5]==0)
						val+=1000000;
					if(a[i][j]==0&&a[i+1][j]==t&&a[i+2][j]==t&&a[i+3][j]==t&&a[i+4][j]==t&&a[i+5][j]==0)
						val+=1000000;
					if(a[i][j]==0&&a[i+1][j+1]==t&&a[i+2][j+2]==t&&a[i+3][j+3]==t&&a[i+4][j+4]==t&&a[i+5][j+5]==0)
						val+=1000000;
				
				}
				if(a[i][j]==t&&a[i][j+1]==t&&a[i][j+2]==t&&a[i][j+3]==t&&a[i][j+4]==t)
					val+=100000000;
				if(a[i][j]==t&&a[i+1][j]==t&&a[i+2][j]==t&&a[i+3][j]==t&&a[i+4][j]==t)
					val+=100000000;
				if(a[i][j]==t&&a[i+1][j+1]==t&&a[i+2][j+2]==t&&a[i+3][j+3]==t&&a[i+4][j+4]==t)
					val+=100000000;
			}
		}	
	} 
	return val;
}

int cal_score(int t)
{
	return value(t)-value(3-t);
}
void printchess(int now)
{

	if(now==1)
		cout<<"●";
	else if(now==2)
		cout<<"○";
	else
		cout<<"  ";
	return;
}

void nextmove(int t)
{
	int ret=nbmove();
	for(int i=1;i<=LINE;i++)
	{
		for(int j=1;j<=LINE;j++)
		{
			if(b[i][j]==maxb)
			{
				a[i][j]=t;
			}
		}
	}
}

int maxab(int depth,int alpha,int beta,int mode);
int minab(int depth,int alpha,int beta,int mode)
{
	int val=cal_score(3-QJMODE);
	if(depth==0||gameover()||duel())
		return val;
	int best=INF;
	int k=nbmove();
	if(k==0)
	{
		NEXT.x=LINE/2+1;
		NEXT.y=LINE/2+1;
		return 0;
	}
	for(int i=1;i<=LINE;i++)
	{
		for(int j=1;j<=LINE;j++)
		{
			if(a[i][j]==0&&b[i][j]!=0)
			{
				a[i][j]=3-mode;
				best=min(best,maxab(depth-1,alpha,beta,3-mode));
				a[i][j]=0;
				if(best<=alpha)
				{
					return best;
				}
				beta=min(beta,best);
			}
		}
	}
	return best;
}
int maxab(int depth,int alpha,int beta,int mode)
{
	int val=cal_score(3-QJMODE);
	if(depth==0||gameover()||duel())
		return val;
	int best=-INF;
	int k=nbmove();
	if(k==0)
	{
		NEXT.x=LINE/2+1;
		NEXT.y=LINE/2+1;
		return 0;
	}
	for(int i=1;i<=LINE;i++)
	{
		for(int j=1;j<=LINE;j++)
		{
			if(a[i][j]==0&&b[i][j]!=0)
			{
				a[i][j]=3-mode;
				best=max(best,minab(depth-1,alpha,beta,3-mode));
				a[i][j]=0;
				if(best>=beta)
				{
					return best;
				}
				if(best>=alpha)
				{
					alpha=best;
					if(depth==MAXDEPTH)
					{
						NEXT.x=i;
						NEXT.y=j;
					}
				}
			}
		}
	}
	return best;
}
int abcutsearch(int depth,int alpha,int beta,int mode)
{ 

	int t=3-mode;
	int bestx;
	int besty;
	if(depth==0||duel()||gameover()!=0)
	{
		return cal_score(3-QJMODE);
	}
	int k=nbmove();
	if(k==0)
	{
		NEXT.x=LINE/2+1;
		NEXT.y=LINE/2+1;
		return 0;
	}
	for(int i=1;i<=LINE;i++)
	{
		for(int j=1;j<=LINE;j++)
		{
			if(a[i][j]==0&&b[i][j]!=0)
			{
				a[i][j]=t;
				int val=-abcutsearch(depth-1,-beta,-alpha,3-mode);
				a[i][j]=0;

				if(val>alpha)
				{

					alpha=val;
					if(depth==MAXDEPTH)
					{
						NEXT.x=i;
						NEXT.y=j;
					}
					if(val>=beta)
					{
						return beta;
					}
				}
			}
		}
	}

	return alpha;
}

void printboard()
{
	cout<<" ";
	for(int i=1;i<=LINE;i++)
	{
		if(i<=10)
			cout<<"   "<<i;
		else
			cout<<"  "<<i;
	}
	cout<<endl;
	cout<<"  ";
	cout<<"╔";
	for(int i=1;i<=LINE-1;i++)
		cout<<"═╦";
	cout<<"═╗" <<endl;
	for(int i=1;i<=2*LINE-1;i++)
	{
		
		if(i%2==1)
		{
			cout<<i/2+1;
			if(i/2+1<10)
				cout<<" ";
			cout<<"║";
			for(int j=1;j<=LINE;j++)
			{
				printchess(a[i/2+1][j]);
				cout<<"║";
			}
			cout<<endl;
		}
		else
		{
			cout<<"  ";
			cout<<"╠";
			for(int j=1;j<=LINE-1;j++)
			{
				cout<<"═╬";
			}
			cout<<"═╣"<<endl;
		}
	}
	cout<<"  ";
	cout<<"╚";
	for(int i=1;i<=LINE-1;i++)
		cout<<"═╩";
	cout<<"═╝" <<endl;
}


void getinput(int mode)
{
	cout<<"请输入你想下的位置（先行后列）"<<endl; 
	int row,col;
	cin>>row>>col;
	if(a[row][col]==0)
		a[row][col]=mode;
	else
	{
		cout<<"输入非法，请重新输入"<<endl;
		getinput(mode);
	} 
}

int menu()
{
	int mode=0;
	cout<<"---------------------"<<endl;
	cout<<"五子棋游戏：与AI对弈"<<endl;
	cout<<"请选择先后手"<<endl;
	cout<<"1.先手"<<endl;
	cout<<"2.后手"<<endl;
	cout<<"---------------------"<<endl;
	cout<<"请选择[1-2]:"; 
	char ch='\0';
	while(1)
	{
		ch=getchar();
		if(ch=='1'||ch=='2')
			break;
		cout<<"输入非法，请输入[1-2]"<<endl;
	}
	getchar();
	mode=ch-'0';
	QJMODE=mode;
	return mode; 
}

void gameprocess(int mode)
{
	int ret;
	int turn;
	if(mode==1)
	{
		turn=1;
	}
	else
		turn=0;
	while(1)
	{
		system("cls");
		printboard();
		ret=gameover();
		if(ret)
			break;

		if(turn==1)
		{
			int x=0;
			int y=0;
			cout<<"该你下了！"<<endl;
			cout<<"请输入坐标落子(先行后列)"<<endl;
			while(1)
			{

				cin>>x>>y;
				if(x>=1&&x<=LINE&&y>=1&&y<=LINE&&a[x][y]==0)
					break;
				else
					cout<<"输入非法！请重新输入"<<endl;
				cin.clear();
				cin.ignore(INF,'\n');
			}
			if(mode==1)
				a[x][y]=1;
			else
				a[x][y]=2;
		}
		else
		{
			int x;
			int y;
			abcutsearch(MAXDEPTH,-INF,INF,mode); 
			if(mode==2)
				a[NEXT.x][NEXT.y]=1;
			else
				a[NEXT.x][NEXT.y]=2;
			system("cls");
			printboard();
			cout<<"电脑下在了("<<NEXT.x<<","<<NEXT.y<<")(先行后列)"<<endl; 
			
			system("pause");
		}
		turn=!turn;
	}
	if(mode==ret)
		cout<<"你赢了！"<<endl;
	else
		cout<<"你输了！"<<endl;
} 
int main()
{
	int mode;
	system("cls");
	
	mode=menu();
	system("cls");
	printboard();
	gameprocess(mode);
	return 0;
} 
