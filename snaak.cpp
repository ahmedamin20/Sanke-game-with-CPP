#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
using namespace std;
//---------------------------------------------------------------
enum Direction {Top=1, Down , Right , Left };
struct map { int width , hight , fruitx , fruity;};
struct snake {int headx,heady,tail_n,tailx[50],taily[50]; Direction Dir;};
struct player {int score; bool lose;};
//---------------------------------------------------------------
map map1; snake snake1; player player1;
void shift_r(int arr[],int size){
	for (int i=size-2 ; i>=0 ; i--)
	arr [i+1]=arr[i];
}
void make_fruit(){
	srand(time(NULL));
	map1.fruitx= rand() % (map1.width-2)+1;
	map1.fruity= rand() % (map1.hight-2)+1;
}
void setup(){
	map1.width=40;
	map1.hight=20;
	make_fruit();
	//----------------
	snake1.headx = map1.width/2;
	snake1.heady = map1.hight/2;
	snake1.tail_n = 0;
	//-----------------
	player1.score=0;
	player1.lose=false;
}
void draw()
{
	system("cls");
	for (int i=0 ; i<map1.hight ; i++){
		for (int j=0 ; j<map1.width ; j++){
		if (i==0||i==map1.hight-1)cout<<"#";
		else if(j==0||j==map1.width-1)cout<<"#";
		else if (i==snake1.heady&&j==snake1.headx)cout<< "O";
		else if (i==map1.fruity&&j==map1.fruitx)cout<< "$";
		else 
		{
			bool printed = false;
			for (int z=0 ; z<snake1.tail_n ; z++)
			{
				if(snake1.tailx[z]==j && snake1.taily[z]==i){
					cout<<"*";
					printed=true;
					break;
				}
			}
		if (!printed)cout<<" ";	
	   }
	 }
	  	cout<<"\n";
   }
   cout<<"player score is ("<< player1.score<<")\n";
}


void input(){
	if (_kbhit())
	{
		char c = _getch();
		switch(c)
		{;
			case 'w': snake1.Dir = Top; break;
			case 's': snake1.Dir = Down; break;
			case 'd': snake1.Dir = Right; break;
			case 'a': snake1.Dir = Left; break;
			case 72: snake1.Dir = Top; break;
			case 80: snake1.Dir = Down; break;
			case 77: snake1.Dir = Right; break;
			case 75: snake1.Dir = Left; break;
			case 'x': exit(0);
			case 'p':system ("pause");
		}
	}
}
void move(){
	shift_r (snake1.tailx,50);
	shift_r (snake1.taily,50);
	snake1.tailx[0] = snake1.headx;
	snake1.taily[0] = snake1.heady;
	switch (snake1.Dir)
	{
		case Top: snake1.heady--;break;
		case Down:snake1.heady++;break;
		case Right:snake1.headx++;break;
		case Left:snake1.headx--;break;
	}
	if (snake1.heady >= map1.hight||snake1.heady<=0||snake1.headx>=map1.width||snake1.headx<=0)
	player1.lose = true;
	if (snake1.headx == map1.fruitx && snake1.heady==map1.fruity){
		make_fruit();
		player1.score+=1;
		snake1.tail_n++;
	}
}
int main()
{
	setup();
while (!player1.lose){
	draw();
	input();
	move();
	Sleep(100);
}
    system("mode 650");
	system("pause");
}
