#include<stdio.h>
#include<conio.h>//system()
#include<stdlib.h>//rand(), srand()
#include<time.h>//time()
//fibonacci sequence
int fibonacci(int n)
{
    if (n==1||n==2)
    return 1;
    else
    return fibonacci(n-1)+fibonacci(n-2);
}

//consecutive fibonacci number checker
int cfnc(int a,int b)
{
	int t,i;
	t=a+b;
	for(i=3;i<25;i++)
	{
		if(t==fibonacci(i))
		return 1;
	}
	return 0;
}
//sliding functions
void slidecolumns(int F[][4], int j, int m)
{
	int i,k,lim;
	for(k=m-1;k>0;k--)
	{
		lim=m;
		for(i=0;i<=k;i++)
		{
			if(F[i][j]!=0)
			lim=i;
		}
		if((lim!=m)&&(lim!=k))
		{
			F[k][j]=F[lim][j];
			F[lim][j]=0;
		}
	}
}

void sliderowd(int F[][4], int i, int m)
{
	int j,k,lim;
	for(k=m-1;k>0;k--)
	{
		lim=m;
		for(j=0;j<=k;j++)
		{
			if(F[i][j]!=0)
			lim=j;
		}
		if((lim!=m)&&(lim!=k))
		{
			F[i][k]=F[i][lim];
			F[i][lim]=0;
		}
	}
}

void sliderowa(int F[][4], int i, int m)
{
	int j,k,lim;
	for(k=m-1;k<3;k++)
	{
		lim=5;
		for(j=3;j>=k;j--)
		{
			if(F[i][j]!=0)
			lim=j;
		}
		if((lim!=5)&&(lim!=k))
		{
			F[i][k]=F[i][lim];
			F[i][lim]=0;
		}
	}
}

void slidecolumnw(int F[][4], int j, int m)
{
	int i,k,lim;
	for(k=m-1;k<3;k++)
	{
		lim=5;
		for(i=3;i>=k;i--)
		{
			if(F[i][j]!=0)
			lim=i;
		}
		if((lim!=5)&&(lim!=k))
		{
			F[k][j]=F[lim][j];
			F[lim][j]=0;
		}
	}
}

//adding functions
void addcolumns(int F[][4], int sum)
{
	int i,j;
	for(j=0;j<4;j++)
	{
		for(i=3;i>0;i--)
		{
			if(cfnc(F[i-1][j],F[i][j]))
			{
				F[i][j]=F[i-1][j]+F[i][j];
				sum=sum+F[i][j];
				F[i-1][j]=0;
				slidecolumns(F,j,i);
			}
		}
	}
}

void addrowd(int F[][4], int sum)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=3;j>0;j--)
		{
			if(cfnc(F[i][j-1],F[i][j]))
			{
				F[i][j]=F[i][j-1]+F[i][j];
				sum=sum+F[i][j];
				F[i][j-1]=0;
				sliderowd(F,i,j);
			}
		}
	}
}

void addrowa(int F[][4],int sum)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<3;j++)
		{
			if(cfnc(F[i][j],F[i][j+1]))
			{
				F[i][j]=F[i][j]+F[i][j+1];
				sum=sum+F[i][j];
				F[i][j+1]=0;
				sliderowa(F,i,j+2);
			}
		}
	}
}

void addcolumnw(int F[][4], int sum)
{
	int i,j;
	for(j=0;j<4;j++)
	{
		for(i=0;i<3;i++)
		{
			if((cfnc(F[i][j],F[i+1][j])))
			{
				F[i][j]=F[i][j]+F[i+1][j];
				sum=sum+F[i][j];
				F[i+1][j]=0;
				slidecolumnw(F,j,i+2);
			}
		}
	}
}
int main()
{
	
	
	char move;
	int score=0,p;
	int count,numnull;
	int i,j;
	int a1,b1,a2,b2;
	int A[4][4], B[4][4];
	int nullpos[16][2];
	int randloc;
	int win=0;
	int endgamevar;
	
	//variables specially for generating 1 or 2 tiles
	long long int x=1;
    const long long int a=22695477;
    const int c=1;
    const long long int m=4294967296;
    const long long int d=3900000000;
    
    //initializing the starting grid to zero
    for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
		A[i][j]=0;
		B[i][j]=0;
	}
	}
	//using the random number generator to generate starting indices
	srand(time(NULL));
	a1=rand()%4;
	b1=rand()%4;
	a2=rand()%4;
	b2=rand()%4;
	if((a1==a2)&&(b1==b2))
	{
		A[a1][b1]=1;
	}
	else
	{
		A[a1][b1]=1;
		A[a2][b2]=1;
	}//initialization complete
	
	//output the first grid
	for(i=0;i<4;i++)
	{
		printf("\t\t\t\t");
		for(j=0;j<4;j++)
		printf("%d\t",A[i][j]);
		printf("\n\n\n");
	}
	
	for(i=0;i<4;i++)
	{
		//copying
		for(j=0;j<4;j++)
		B[i][j]=A[i][j];
	}//copying complete
	
	//entering the game 
	for(p=1; ;p++)
	{
		printf("Next move:\n");
		scanf(" %c",&move);
		printf("\n");
		
		//sliding and adding
		if(move=='s')
		{
			for(j=0;j<4;j++)
			slidecolumns(A,j,4);
			addcolumns(A,score);
		}
		if(move=='w')
		{
			for(j=0;j<4;j++)
			slidecolumnw(A,j,1);
			addcolumnw(A,score);
		}
		if(move=='d')
		{
			for(i=0;i<4;i++)
			sliderowd(A,i,4);
			addrowd(A,score);
		}
		if(move=='a')
		{
			for(i=0;i<4;i++)
			sliderowa(A,i,1);
			addrowa(A,score);
		}
		
		//comparison
		count=0;
		numnull=0;
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				if(A[i][j]==B[i][j])
				count++;
				if(A[i][j]==0)
				{
					nullpos[numnull][0]=i;
					nullpos[numnull][1]=j; //initialising the array containing locations of empty tiles
					numnull++;
			}
			}
		}
		if(count==16)
		printf("\t\t\t\tInvalid move!!!\n");
		else
		{
			//generate a random position among the indices 0,1,..,numnull-1
			randloc=rand()%numnull;
			x=((a*x)+c)%m;
			if(x<=d)
			A[nullpos[randloc][0]][nullpos[randloc][1]]=1;
			else
			A[nullpos[randloc][0]][nullpos[randloc][1]]=2;
		}
		
		//output new grid and copy to B
			system("cls");
		for(i=0;i<4;i++)
		{    printf("\t\t\t\t");
			for(j=0;j<4;j++)
			{
				printf("%d\t",A[i][j]);
				B[i][j]=A[i][j];
			}
			printf("\n\n\n");
		}
		
		//cout<<"\t"<<"\t"<<"\t"<<"\t"<<"Your score:"<<score<<endl; (This is marked as a comment since we are not getting the correct score in the output.
		
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				if(A[i][j]==144)
				win++;
			}
		}
		if(win==1)
		printf("\t\t\t\t\t\t\tYOU WIN!!!\n\n");
		
		//endgame condition
		
		if(numnull==0)
		{
			endgamevar=0;
			for(i=0;i<4;i++)
			{
				for(j=0;j<3;j++)
				{
					if(!(cfnc(A[i][j],A[i][j+1])))
					endgamevar++;
				}
			}
			for(j=0;j<4;j++)
			{
				for(i=0;i<3;i++)
				{
					if((!cfnc(A[i][j],A[i+1][j])))
					endgamevar++;
				}
			}
		}
		if(endgamevar==24)
		{
			printf("\t\t\t\t\t\tGAME OVER!!!!");
			break;
		}
	}
	
}
