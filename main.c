#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include<time.h>

void firstPage();  //display the first page
void instructions();        //display the instruction to game
void border();       //display the side wall of the game
void patternOfGrass();
void patternOfPipes();
void birdFlies(int);
void birdFliesCont();
int  getkey();
int  gameOver();
void gotoxy(int, int);
void continueGame();
void youLose();


int length_of_pipes[80],speed=700,score=0,flag=0,level=1;


void main()
{
char ch;
int gd=DETECT,gm,x,y;
clrscr();
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
firstPage();
getch();
closegraph();
restorecrtmode();
instructions();
getch();
start:
  clrscr();
  patternOfPipes();
  patternOfGrass();
//  if(flag==0)
	{
	birdFlies(4);
//	flag=1;
	}
//  else
//	birdFliesCont();
  clrscr();
  textcolor(2);
  gotoxy(26,11);
  cprintf("Do you want to play more..?");
  gotoxy(31,13);
  cprintf("Press Y for Yes, ");
  gotoxy(37,14);
  cprintf("N for NO: ");
  gotoxy(46,14);
  while(1){
  if(kbhit()){
      ch=getkey();
	if(ch=='y' || ch=='Y'){
	    level=1;
	    goto start;
	}else if(ch=='n' || ch=='N'){
		    exit(0);
		}
    }
  }
}


void firstPage()    //create first page
{
   setbkcolor(RED);
   setcolor(YELLOW);
   settextstyle(8,HORIZ_DIR,3);
   outtextxy(220,150,"!! FLAPPYBIRD !!");
   outtextxy(155,280," Press any key to start ");
}

void instructions()
{
   textcolor(2);
   gotoxy(22,10);
   cprintf("To fly the bird use the up arrow key");
   gotoxy(27,11);
   cprintf("To PAUSE the game press P");
   gotoxy(24,12);
   cprintf("Press any key to Start the Game:-");
   getch();
}

int getkey()		//get a key stroke
{
  int ch;
  ch=getch();
  if(ch==0)
  {
    ch=getch();
    return ch;
  }
  return ch;
}

void border() //create a wall
{
  int i;
  textcolor(6);
  for(i=2;i<75;i++)
  {
    gotoxy(i,2);
    cprintf("=");
    gotoxy(i,25);
    cprintf("=");
     if(i<27)
     {
      gotoxy(2,i);
      cprintf("|");
      gotoxy(75,i);
      cprintf("|");
     }
  }
}

void patternOfGrass()      // to make track more difficult
{
   int j,k,r,a[5];
       a[0]=length_of_pipes[4];
       a[1]=length_of_pipes[9];
       a[2]=length_of_pipes[14];
       a[3]=length_of_pipes[19];
       a[4]=length_of_pipes[24];
      for(j=4;j<=72;j++)
	  {
		   r=4;
	       for(k=0;k<=random(r);k++)
	     {
		textcolor(2 + BLINK);
		gotoxy(j,24-k);
		cprintf("\\*/\n");
	     }
	  }
}

void birdFlies(int a)
{
int i=4,j=13,key,x,y;
i=a;
for(i,j=length_of_pipes[0]+5;i<70;i++,j++)
{
   textcolor(11);
   gotoxy(3,1);
   cprintf("Level=%d",level);
   gotoxy(61,1);
   score = score+level;
   cprintf("Total score=%d",score);
   textcolor(1);
   if(!kbhit())
 {
    gotoxy(i,j);
    cprintf("##\1");
    x=wherex();
    y=wherey();
    if(gameOver(x,y)==1)
    {
       break;
    }
    delay(speed);
    gotoxy(i,j);
    printf("    ");
 }
  else
  {
     key=getkey();
   if(key==72)
    {
     textcolor(11);
     gotoxy(i,j);
     printf("   ");
     gotoxy(i++,j=j-2);
     cprintf("#\3\1");
     x=wherex();
     y=wherey();
     if(gameOver(x,y)==1)
     {
       break;
     }
     delay(speed);
     gotoxy(i-1,j);
     printf("   ");
     sound(1900);
     delay(50);
     nosound();
    }
    else
     {
       if(key=='p' || key=='P')
       {
	 gotoxy(35,13);
	 cprintf("PAUSED..!");
	 getch();
	 gotoxy(35,13);
	 printf("         ");

       }
     }
   }
 if(i>68)
    {
      speed=speed-50;
      level++;
      clrscr();
      patternOfPipes();
      patternOfGrass();
      birdFlies(28);
    }
 if(j==22)
   break;
}
}


int gameOver(int i,int j) // for game lose
{
   if(i>=7&&i<=13)
   {
    if(j<=length_of_pipes[4]+2||j>=length_of_pipes[4]+6)
    {
	youLose();
	return 1;
    }
   }else
   if(i>=21&&i<=27)
   {
    if(j<=length_of_pipes[9]+2||j>=length_of_pipes[9]+6)
    {
       youLose();
       return 1;
     }
   }else
    if(i>=35&&i<=41)
   {
    if(j<=length_of_pipes[14]+2||j>=length_of_pipes[14]+6)
    {
       youLose();
       return 1;
    }
   }else
   if(i>=49&&i<=55)
   {
    if(j<=length_of_pipes[19]+2||j>=length_of_pipes[19]+6)
    {
       youLose();
       return 1;
    }
   }else
   if(i>=63&&i<=69)
   {
    if(j<=length_of_pipes[24]+2||j>=length_of_pipes[24]+6)
    {
       youLose();
       return 1;
    }
   }
   return 0;
}

void youLose()
{
   FILE *fp;
   struct total
   {
     int t;
   };
   struct total to;
   to.t=0;
   flag=0;
   clrscr();
   textcolor(4);
   fp=fopen("TOT.DAT","rb+");
   if(fp==NULL)
     fp=fopen("TOT.DAT","wb+");
   fread(&to,sizeof(to),1,fp);
   if(score<to.t)
   {
     gotoxy(33,12);
     textcolor(18);
     cprintf("High Score=%d",to.t);
     gotoxy(33,14);
     textcolor(4);
     cprintf("Your Score=%d",score);
   }else
   {
    textcolor(18);
    to.t=score;
    rewind(fp);
    fwrite(&to,sizeof(to),1,fp);
    fread(&to,sizeof(to),1,fp);
    gotoxy(31,12);
    cprintf("New High Score=%d",to.t);
    gotoxy(33,14);
    cprintf("Your Score=%d",score);
   }
   fclose(fp);
   score=0;
       gotoxy(27,16);
       cprintf("Press C key to continue:-");
	textcolor(4 + BLINK);
       gotoxy(35,3);
       cprintf("GAME OVER");
       gotoxy(52,16);
//       cprintf(" ");
       continueGame();
}

void continueGame(){
    int ch;
    while(1)
    {
	if(kbhit())
	{
	   ch=getkey();
	   if(ch==99)
		break;
	}
    }
}

void patternOfPipes()
{
  int i,j,x,y,r2,c,t=0;
  border();
  randomize();
 for(c=1;c<=70;c++)
  {
      x=c;
      r2=random(13);
      if(r2<4)
	r2=13-r2;
    if(c%7==0)
     {
	    c=c+7;
       for(i=0;i<5;i++)
	{
	       textcolor(4);
	    x++; y=3;
	  for(j=0;j<r2;j++)
	     {
	      gotoxy(x,y++);
	      cprintf("|");
	     }
	       length_of_pipes[t++]=r2;
	       y=24;
	  for(j=0;j<18-r2;j++)
	     {
	      gotoxy(x,y--);
	      cprintf("|");
	     }
	    y=3;
	}
     }
  }
//  printf("%d,%d,%d,%d,%d",length_of_pipes[4],length_of_pipes[9],length_of_pipes[14],length_of_pipes[19],length_of_pipes[24]);
}
