/* knight_life.c */
/* チェスのナイトの八近傍でライフゲームを行うとどうなるか */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 30

#define ALIVE 1
#define DEATH -1

int init(int (**world)[SIZE],int (**future)[SIZE]);
int update(int (**world)[SIZE],int (**future)[SIZE]);
int update_cell(int (*world)[SIZE],int y,int x,int (**future)[SIZE]);
int countFriend(int (*world)[SIZE],int y,int x);
int isOutside(int x, int y);
int isSatisfaction(int (*world)[SIZE]);
int realize(int (**world)[SIZE],int (**future)[SIZE]);
int draw(int (*world)[SIZE]);
int finalize(int (*world)[SIZE],int (*future)[SIZE]);

int main(int argc, char *argv[]){
  int time;
  int (*world)[SIZE], (*future)[SIZE];

  init(&world,&future);
  draw(world);
  for(time=0;;time++){
    update(&world,&future);
    draw(world);
    if(isSatisfaction(world))break;
  }
  finalize(world,future);
  return 0;
}

int init(int (**world)[SIZE],int (**future)[SIZE]){
  int i,j;

  srand((unsigned)time(NULL));

  *world=(int (*)[SIZE])malloc(sizeof(int)*SIZE*SIZE);
  *future=(int (*)[SIZE])malloc(sizeof(int)*SIZE*SIZE);
  /* printf("world %p, future %p\n",*world,*future); */

  for(i=0;i<SIZE;i++){
    for(j=0;j<SIZE;j++){
      if(rand()%2)(*world)[i][j]=ALIVE;
      else (*world)[i][j]=DEATH;
    }
  }

  printf("lifegame starts.\n"
         "SIZE %d\n",SIZE);

  return 0;
}

int update(int (**world)[SIZE],int (**future)[SIZE]){
  int i,j;
  int count;

  /* printf("world %p,future %p\n",*world,*future); */

  for(i=0;i<SIZE;i++){
    for(j=0;j<SIZE;j++){
      update_cell(*world,j,i,future);
    }
  }
  realize(world,future);
  return 0;
}

int update_cell(int (*world)[SIZE],int y,int x,int (**future)[SIZE]){
  int count=0;

  count = countFriend(world,y,x);
  if(world[y][x]==ALIVE){
    if(count>3) (*future)[y][x]=DEATH;
    else if(count<2) (*future)[y][x]=DEATH;
    else (*future)[y][x]=ALIVE;
  }else{
    if(count==3) (*future)[y][x]=ALIVE;
    else (*future)[y][x]=DEATH;
  }

  return 0;
}

int countFriend(int (*world)[SIZE],int y,int x){
  int i,j;
  int count=0;
  for(i=-2;i<=2;i++){
    for(j=-2;j<=2;j++){
      if(isOutside(y+j,x+i))continue;
      if((abs(i)==1 && abs(j)==2)
         || (abs(i)==2 && abs(j)==1)){
        if(world[y+j][x+i]==ALIVE){
          count++;
        }
      }
    }
  }
  return count;
}

int isOutside(int y, int x){
  if(x < 0 || y < 0) return -1;
  if(x > SIZE-1 || y > SIZE-1) return -1;
  return 0;
}

int isSatisfaction(int (*world)[SIZE]){
  char hmm[30];
  printf("satisfaction? (1/-1)");
  gets(hmm);
  if(hmm[0]=='-' && hmm[1]=='1')return -1;
  if(hmm[0]=='q')return -1;
  return 0;
}

int realize(int (**world)[SIZE],int (**future)[SIZE]){
  int (*p)[SIZE];
  p = *world;
  *world=*future;
  *future = p;
  return 0;
}

int draw(int (*world)[SIZE]){
  static char picture[SIZE][2*SIZE+1];
  static char alive='o';
  static char death='.';
  int i,j;

  for(i=0;i<SIZE;i++){
    for(j=0;j<SIZE;j++){
      if(world[i][j]==ALIVE){
        picture[i][2*j]=alive;
      }else{
        picture[i][2*j]=death;
      }
      picture[i][2*j+1]=' ';
    }
    picture[i][2*SIZE]='\n';
  }
  picture[SIZE-1][2*SIZE]='\0';
  puts((char*)picture);
  puts("--------------------");

  return 0;
}

int finalize(int (*world)[SIZE],int (*future)[SIZE]){
  free(world);
  free(future);
  return 0;
}
