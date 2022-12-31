/*This program was written by Yabanzhi Aleksey.
  The final result looks like a massive of numbers, where:
  <0> means, that we have never been to this point,
  <2> means, that we have been twice here, so it marks a dead end branch
  <1> marks the right way through the labyrinth.
*/
#include <stdio.h>
#include <stdlib.h>

#define MSIZEX 11
#define MSIZEY 11
#define NOWALL (labyrinth[cursorv][cursorh]==0)
#define NOMETKA (metka[cursorv][cursorh]<2)
#define MIN(a,b) (((a)<(b))?(a):(b))

#include "main.h"

struct //this structure is created for memorizing the position of the cursor
  {
    int v; //vertical position 0...10
    int h; //horizontal position 0...10
  }cursor={0,0}; //default

const int x=0; //for marking free spaces in the labyrinth
               //<1> means that there is a wall here
const int labyrinth[MSIZEY][MSIZEX]= //labirynth
  {
     {1,1,1,1,1,x,1,1,1,1,1},
     {1,x,x,x,x,x,1,x,x,x,1},
     {1,1,1,1,1,x,1,1,1,x,1},
     {1,x,x,x,1,x,x,x,x,x,1},
     {1,x,1,x,1,1,1,1,1,x,1},
     {1,x,1,x,x,x,x,x,x,x,1},
     {1,1,1,x,1,1,1,x,1,x,1},
     {1,x,x,x,1,x,x,x,1,x,1},
     {1,x,1,1,1,1,1,1,1,x,1},
     {1,x,x,x,x,x,1,x,x,x,1},
     {1,1,1,1,1,x,1,1,1,1,1} 
  };
int metka[MSIZEY][MSIZEX]= //for marking my way in the labyrinth
  {
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0}
  };
//-------------------------------------------MAIN-----------------------------------------
int main()
  {
    cursor.h=LookForEntrance(); //Look for the massive entrance
    while(cursor.v!=MSIZEY-1)
      {
        DecisionToMove(cursor.v, cursor.h); // we retrieve the current position of the cursor and decide where to move
      }
    metka[cursor.v][cursor.h]++; //marking our last position for the way in the labyrinth to be complete
    PrintResult(labyrinth, metka);
    return 0;
  }
//----------------------------------------------------------------------------------------
int LookForEntrance(void)
  {
    int i=0;
    while((labyrinth[0][i])!=0&&i<MSIZEX)
      {i++;}
    return i;
  }
  //----------------------------------------------------------------------------------------
int DeadEndDetect(int cursorv, int cursorh) //detects whether there is the dead end of the labyrinth
  {
   int count=0;
   if ((labyrinth[cursorv+1][cursorh]==1))
    {count++;}
   if ((labyrinth[cursorv-1][cursorh]==1))
     {count++;}
   if ((labyrinth[cursorv][cursorh+1]==1))
     {count++;}
   if ((labyrinth[cursorv][cursorh-1]==1))
     {count++;}
   if (count>2)
     {return 1;}
   else 
     {return 0;}
  }
//----------------------------------------------------------------------------------------
void CheckMetka(int cursorv, int cursorh)
{
  metka[cursorv][cursorh]++; //place mark that we attended here, so metka=1 and later we can return here if we need
     /*The next part of the function was entered with only one purpose.
       After exit the dead end branch, it's crossroads point
       with the true way has the value <2> in the massive metka[][].
       With this function we convert it to <1>, for the correct result presenting.
    */
  if (metka[cursorv][cursorh]==2)
    {
        if(metka[cursorv][cursorh-1]==0&&labyrinth[cursorv][cursorh-1]==0)
            {metka[cursorv][cursorh]--;}
        if(metka[cursorv][cursorh+1]==0&&labyrinth[cursorv][cursorh+1]==0)
            {metka[cursorv][cursorh]--;}
        if(metka[cursorv-1][cursorh]==0&&labyrinth[cursorv-1][cursorh]==0)
            {metka[cursorv][cursorh]--;}
        if(metka[cursorv+1][cursorh]==0&&labyrinth[cursorv+1][cursorh]==0)
          {  metka[cursorv][cursorh]--;}
    }
  if (DeadEndDetect(cursorv, cursorh))
    {metka[cursorv][cursorh]++;} //we needn't return to this point, so metka=2
}
//----------------------------------------------------------------------------------------
int CheckDown(int cursorv, int cursorh)
  {
    /*TRYING DOWN*/
    cursorv++;//try down...
    if (NOWALL&&NOMETKA) //check that there is no wall here and we were here less than twice
      {
        cursor.v++;
        return 1;
      }
    else
      {
        cursorv--;
        return 0;
      }
  }
//----------------------------------------------------------------------------------------
int CheckLeft(int cursorv, int cursorh)
  {
    /* TRYING LEFT*/
    cursorh--;//try left...
    if (NOWALL&&NOMETKA) //check that there is no wall here and we were here less than twice
      {
        cursor.h--;
        return 1;
      }
    else
      {
        cursorh++;
        return 0;
      }
  }
//----------------------------------------------------------------------------------------
int CheckRight(int cursorv, int cursorh)
  {
    /*TRYING RIGHT*/
    cursorh++;//try right...
    if (NOWALL&&NOMETKA) //check that there is no wall here and we were here less than twice
      {
        cursor.h++;
        return 1;
      }
    else
      {
        cursorh--;
        return 0;
      }
  }
//----------------------------------------------------------------------------------------
int CheckUp(int cursorv, int cursorh)
  {
    /*TRYING UP*/
    cursorv--;//try up...
    if (NOWALL&&NOMETKA) //check that there is no wall here and we were here less than twice
      {
        cursor.v--;
        return 1;
      }
    else
      {
        cursorv++;
        return 0;
      }
  }
//----------------------------------------------------------------------------------------
int DirectionDetect(int cursorv, int cursorh) //we will try to go to the side where the <metka> is the lowest
  {
    if (metka[cursorv+1][cursorh]==0&&labyrinth[cursorv+1][cursorh]==0) // if we have never been to the next position and there is no wall here...
      {return 1;}
    else if (metka[cursorv][cursorh-1]==0&&labyrinth[cursorv][cursorh-1]==0)
      {return 2;}
    else if (metka[cursorv][cursorh+1]==0&&labyrinth[cursorv][cursorh+1]==0)
      {return 3;}
    else if (metka[cursorv-1][cursorh]==0&&labyrinth[cursorv-1][cursorh]==0)
      {return 4;}
    else if (metka[cursorv+1][cursorh]==1&&labyrinth[cursorv+1][cursorh]==0) // else if we have been to the next position only once and there is no wall here...
      {return 1;}
    else if (metka[cursorv][cursorh-1]==1&&labyrinth[cursorv][cursorh-1]==0)
      {return 2;}
    else if (metka[cursorv][cursorh+1]==1&&labyrinth[cursorv][cursorh+1]==0)
      {return 3;}
    else if (metka[cursorv-1][cursorh]==1&&labyrinth[cursorv-1][cursorh]==0)
      {return 4;}
    else 
      {printf ("Something went wrong in DirectionDetect");}
    return 0;
  }
//----------------------------------------------------------------------------------------
void DecisionToMove(int cursorv, int cursorh)
  {
    CheckMetka(cursorv, cursorh);
    int cnt=0;
    cnt=DirectionDetect(cursorv, cursorh);
    int desresult=0;
    switch (cnt)
      {
        case 1:
          if ( (desresult=CheckDown(cursor.v, cursor.h))!=0)
          {return;}
          //break;
        case 2:
          if ( (desresult=CheckLeft(cursor.v, cursor.h))!=0)
          {return;}
          //break;
        case 3:
          if ( (desresult=CheckRight(cursor.v, cursor.h))!=0)
          {return;}
          //break;
        case 4:
          if ( (desresult=CheckUp(cursor.v, cursor.h))!=0)
          {return;}
          //break;
        default:
          printf ("Something went wrong in switch DirectionDetect()");
      }
  }
//----------------------------------------------------------------------------------------
void PrintResult(const int massive1[MSIZEX][MSIZEY], int massive2[MSIZEX][MSIZEY])
{

  printf("The massive that ve have to pass through:\r\n");
  printf("<1> means, that there is the wall here\r\n");
  printf("<0> means, that there is a passage here\r\n\r\n");
  for(int i=0;i<MSIZEX;i++)
    {
      for(int j=0;j<MSIZEY;j++)
        {
          printf("%d  ",massive1[i][j]);
        }
          printf("\r\n");
    }
  printf("\r\n\r\n\r\nThe result of passing through the labyrinth is presented in this massive:\r\n");
  printf("<0> means, that we have never been to this point,\r\n");
  printf("<2> means, that we have been twice here, so it marks a dead end branch\r\n");
  printf("<1> marks the right way through the labyrinth.\r\n\r\n");
  for(int i=0;i<MSIZEX;i++)
    {
      for(int j=0;j<MSIZEY;j++)
        {
          printf("%d  ",massive2[i][j]);
        }
          printf("\r\n");
    }
}


