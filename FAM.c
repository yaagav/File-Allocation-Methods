#include<stdio.h>
#include<process.h>
#include<conio.h>
#include<stdlib.h>
#define TB 100

struct Link
{
	char n[30];
 	int len;
 	int st;
 	struct node
 	{
 		int index;
 		struct node *next;
 	}*Start,*current,*newnode,*temp;
}F[30];
int Table[TB+1],pos=0,r,i,j,ch,B=0;
char fn[30];
int BFull()
{
 	for(i=1,B=0;i<=pos;i++)
 	B=B+F[i].len;
 	if(B>TB)
 	return 1;
 	else
  	return 0;
}

void sequential()
{
	int f[50],i,st,j,len,c,k;
	for(i=0;i<50;i++)
	f[i]=0;
	X:
	printf("\nEnter the starting block & length of file: "); 
	scanf("%d%d",&st,&len);
	for(j=st;j<(st+len);j++)
	if(f[j]==0)
	{
		f[j]=1;
		printf("\n%d->%d",j,f[j]);
	}
	else
	{
		printf("Block already allocated");
		break;
	}
	if(j==(st+len))
	printf("\n the file is allocated to disk");
	printf("\n if u want to enter more files?(y-1/n-0)"); 
	scanf("%d",&c);
	if(c==1)
	goto X;
	else
	{
 		exit(0);
	}
}

void linked()
{
 	pos++;
 	printf("\nEnter File Name: ");
 	scanf("%s",&(F[pos].n));
 	printf("\nEnter File Length: ");
 	scanf("%d",&(F[pos].len));
 	F[pos].Start=NULL;
 	if(BFull())
 	{
 		pos--;
 		printf("\n\nNo Enough Free Space Available \n");
 		return;
 	}
 	for(i=1;i<=F[pos].len;i++)
 	{
 		F[pos].newnode=(struct node *)malloc(sizeof(struct node));
  		while(1)
 		{
 			r=rand()%TB+1;
 			if(Table[r]==0)
 			{
 				F[pos].newnode->index =r;
 				F[pos].newnode->next=NULL;
 				if(F[pos].Start==NULL)
 				{
 					F[pos].Start=F[pos].newnode;
 					F[pos].current=F[pos].newnode;
 				}
 				else
 				{
					F[pos].current->next=F[pos].newnode;
 					F[pos].current=F[pos].newnode;
 				}
 				Table[r]=1;
 				break;
 			}
 		}
 	}
 	F[pos].st=F[pos].Start->index;
 	for(i=r;i<r+F[pos].len;i++)
 	Table[i]=1;
  	printf("\n\tFile Allocation Table\n");
 	printf("\nFileName\tStart\tEnd\tLength\n");
 	for(i=1;i<=pos;i++)
 	{
 		printf("\n%s\t\t%d\t%d\t%d",F[i].n,F[i].st,F[pos].current->index,F[i].len);
 		printf("\n");
 	}
 	printf("\nEnter The File Name to be displayed : ");
 	scanf("%s",fn);
 	printf("\nBlocks Allocated Are : ");
 	for(i=1;i<=pos;i++)
 	{
 		if(strcmp(F[i].n,fn)==0)
 		{
 			F[i].current=F[i].Start;
 			while(F[i].current)
 			{
 				printf(">--%d-->",F[i].current->index);
 				F[i].current=F[i].current->next;
 			}
 			break;
 		}
	}
	if(i==pos+1)
	{
 		printf("\n\nNo File Found\n");
  	}
}

void indexed()
{
	int f[50], index[50],i, n, st, len, j, c, k, ind,count=0;
	for(i=0;i<50;i++)
	f[i]=0;
	x:printf("Enter the index block: ");
	scanf("%d",&ind);
	if(f[ind]!=1)
	{
		printf("Enter no of blocks needed and no of files for the index %d on the disk : \n", ind);
		scanf("%d",&n);
	}
	else
	{
		printf("%d index is already allocated \n",ind);
		goto x;
	}
	y: count=0;
	for(i=0;i<n;i++)
	{
		scanf("%d", &index[i]);
		if(f[index[i]]==0)
		count++;
	}
	if(count==n)
	{
		for(j=0;j<n;j++)
		f[index[j]]=1;
		printf("Allocated\n");
		printf("File Indexed\n");
		for(k=0;k<n;k++)
		printf("%d-------->%d : %d\n",ind,index[k],f[index[k]]);
	}
	else
	{
		printf("File in the index is already allocated \n");
		printf("Enter another file indexed");
		goto y;
	}
	printf("Do you want to enter more file(Yes - 1/No - 0): ");
	scanf("%d", &c);
	if(c==1)
	goto x;
	else
	{
		exit(0);
	}	
}

int main()
{ 
	int opt;
 	while(1)
	{
		printf("\nFile Allocation Methods in OS");
 		printf("\n1.Sequential\n2.Linked\n3.Indexed\n\nEnter the option: ");
 		scanf("%d", &opt);
 		switch(opt)
 		{
 			case 1 :
 				sequential();
 				break;
 			case 2 :
				linked();
				break;
 			case 3 : 
				indexed();
 				break;
 		}
 	}	
 	getch();
 	return 0;
}
