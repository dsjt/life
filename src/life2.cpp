/* life2.cpp */
#include <iostream>
#include <time.h>

#define SIZE 30

#define ALIVE 1
#define DEATH -1

int init(int (**world)[SIZE],int size);
int update(int (**world)[SIZE]);
int update_cell(int (*world)[SIZE],int y,int x,int (**future)[SIZE]);
int countFriend(int (*world)[SIZE],int y,int x);
int isOutside(int x, int y);
int isSatisfaction(int (*world)[SIZE]);
int realize(int (**world)[SIZE],int (*future)[SIZE]);
int draw(int (*world)[SIZE]);
int finalize(int (*world)[SIZE]);

int main(int argc, char *argv[]){
  int time=1;
  int (*world)[SIZE];

  init(&world,SIZE);
  for(time=0;;time++){
    update(&world);
    draw(world);
    if(isSatisfaction(world))break;
  }
  finalize(world);
  return 0;
}

int init(int (**world)[SIZE],int size){
  int i,j;
  double t;

  *world=(int (*)[SIZE])malloc(sizeof(int)*SIZE*SIZE);

  srand((unsigned)time(NULL));
  for(i=0;i<SIZE;i++){
    for(j=0;j<SIZE;j++){
      if(rand()%3)(*world)[i][j]=ALIVE;
      else (*world)[i][j]=DEATH;
    }
  }

  printf("lifegame starts.\n"
         "SIZE %d\n",SIZE);

  draw(*world);
  return 0;
}

int update(int (**world)[SIZE]){
  int i,j;
  int count;
  int (*future)[SIZE]=(int (*)[SIZE])malloc(sizeof(int)*SIZE*SIZE);

  for(i=0;i<SIZE;i++){
    for(j=0;j<SIZE;j++){
      update_cell(*world,j,i,&future);
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
  for(i=-1;i<2;i++){
    for(j=-1;j<2;j++){
      if(i==0 && j==0)continue;
      if(isOutside(y+j,x+i))continue;
      if(world[y+j][x+i]==ALIVE){
        count++;
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

int realize(int (**world)[SIZE],int (*future)[SIZE]){
  free(*world);
  *world=future;
  return 0;
}

int draw(int (*world)[SIZE]){
  char picture[SIZE*(2*SIZE+1)];
  char (*board)[2*SIZE+1];
  static char alive='@';
  static char death=' ';
  int i,j;

  board = (char (*)[2*SIZE+1])picture;
  for(i=0;i<SIZE;i++){
    for(j=0;j<SIZE;j++){
      if(world[i][j]==ALIVE){
        board[i][2*j]=alive;
      }else{
        board[i][2*j]=death;
      }
      board[i][2*j+1]=' ';
    }
    board[i][2*SIZE]='\n';
  }
  board[SIZE-1][2*SIZE]='\0';
  puts(picture);
  puts("--------------------");


  return 0;
}

int finalize(int (*world)[SIZE]){
  return 0;
}


// Local Variables:
// compile-command: "g++ life2.cpp"
// End:
