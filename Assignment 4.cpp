#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<vector>
using namespace std;

vector <int> bullx,bully;

void setcolor(int fg,int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg*16+fg);
}

void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console,&lpCursor);
}

void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE) , c);
}
void draw_ship(int x,int y)
{
    gotoxy(x,y);
    setcolor(2,4);
    cout << " <-0-> ";
    setcursor(0);
}

void erase_ship(int x,int y)
{

    setcolor(0,0);
    COORD c={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
    cout << "          ";
    setcursor(0);
}

void draw_bullet(int x,int y)
{
    gotoxy(x,y);
    setcolor(7,0);
    cout << "|";
    setcursor(0);
}

void erase_bullet(int x,int y)
{
    gotoxy(x,y);
    setcolor(0,0);
    cout << "   ";
    setcursor(0);
}


int main()
{
    char ch='s';
    int x=38,y=25,i;
    int dir=0;
    int c=-1; // count bullets
    int ca=1,cd=1; // direction status
    setcursor(0);
    draw_ship(x,y);

    do
    {
        if (_kbhit()) // direction
        {
            ch=_getch();
            if(ch=='a') { dir=1; cd=1; }
            else if(ch=='d') { dir=-1; ca=1; }
            else if(ch=='s') { dir=0; }
            else if(ch==' ')
            {
                if(c<4)
                {
                    bullx.push_back(x);
                    bully.push_back(y-1);
                    draw_bullet(bullx[i],bully[i]);
                    c++;
                }
            }
            fflush(stdin);
        }
        else
        {
            while(!_kbhit()||!(x>=0&&x<=76)) // move
            {
                if(ch!='s') erase_ship(x,y);
                if(x>=0&&x<=76)
                {
                    if(cd==0||ca==0) dir=0;
                    x+=dir;
                    draw_ship(x,y);
                    Sleep(100);

                    for(i=0;i<=c;i++)
                    {
                        erase_bullet(bullx[i],bully[i]);
                        bully[i]--;
                        if(bully[i]<0)
                        {
                            erase_bullet(bullx[i],bully[i]);
                            bullx.erase(bullx.begin()+i);
                            bully.erase(bully.begin()+i);
                            c--;
                        }
                        else draw_bullet(bullx[i],bully[i]);
                    }
                }

                    if(x==0) { cd=0; break; }
                    else if(x==76) { ca=0; break; }
                }
            }
    } while (ch!='x');

    return 0;
}
