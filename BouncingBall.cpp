#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <bitset>

#define DELAY 30000
#define N 100

int main(int argc, char *argv[]) 
{
	int x[N], y[N], k=0, c=0;
	int max_y = 0, max_x = 0, i, j;
	int distanceX[N],distanceY[N] ;
	initscr();
	noecho();
	curs_set(FALSE);
	getmaxyx(stdscr, max_y, max_x);

	for(k=0;k<N;k++)
	{
		distanceX[k]=1;
		distanceY[k]=1;
		x[k]=rand()%max_x;
		y[k]=rand()%max_y;
	}

	//int ss=max_x*max_y;
	int bv[max_x][max_y];
	for(i=0;i<max_x;i++)
		for(j=0;j<max_y;j++)
			bv[i][j]=0;

	distanceX[max_y]=-1;
	while(1) 
    	{
		c++;
		clear();
		for(i=0;i<max_x;i++)
            for(j=0;j<max_y;j++)
                bv[i][j]=0;
		for(k=0;k<N;k++)
		{
			if(bv[x[k]][y[k]]==1)
			{
				distanceX[k]*=-1;
				distanceY[k]*=-1;
				//x[k]+=distanceX[k];
				//y[k]+=distanceY[k];


				mvprintw(y[k],x[k],"|");
			}
			else
			{
				bv[x[k]][y[k]]=1;
				
				mvprintw(y[k],x[k],"o");

			}
		}
/*
		for(k=0;k<N;k++)
		{
			mvprintw(y[k],x[k],"o");
		}
*/
		refresh();
		usleep(DELAY);
		
		for(k=0;k<N;k++)
		{
            if(x[k]+distanceX[k]>=max_x || x[k]+distanceX[k]<0) 
            {
                distanceX[k]*= -1;
            }
            if((y[k]+distanceY[k]) >= max_y || (y[k]+distanceY[k]) < 0) 
            {
                distanceY[k]*=-1;
            }
            x[k]+= distanceX[k];
            y[k]+=distanceY[k];
		}
    	}

    	endwin();
}

