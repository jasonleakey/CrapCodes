#include "stdio.h"
#include "malloc.h"
#define maxium 32767
#define maxver 9 /*defines the max number of vertexs which the programm can handle*/
#define OK 1
struct Point
{
       char vertex[3];
       struct Link *work;
       struct Point *next;
};
struct Link
{
       char vertex[3];
       int value;
       struct Link *next;
};
struct Table /*the workbannch of the algorithm*/
{
       int cost;
       int Known;
       char vertex[3];
       char path[3];
       struct Table *next;
};
int Dijkstra(struct Point *,struct Table *);
int PrintTable(int,struct Table *);
int PrintPath(int,struct Table *,struct Table *);
struct Table * CreateTable(int,int);
struct Point * FindSmallest(struct Table *,struct Point *);/*Find the vertex which has the smallest value reside in the table*/
int main()
{
       int i,j,num,temp,val;
       char c;
       struct Point *poinpre,*poinhead,*poin;
       struct Link *linpre,*linhead,*lin;
       struct Table *tabhead;
       poinpre=poinhead=poin=(struct Point *)malloc(sizeof(struct Point));
       poin->next=NULL;
       poin->work=NULL;
       restart:
       printf("Notice:if you wanna to input a vertex,you must use the format of number!\n");
       printf("Please input the number of points:\n");
       scanf("%d",&num);
       if(num>maxver||num<1||num%1!=0)
       {
              printf("\nNumber of points exception!");
              goto restart;
       }
       for(i=0;i<num;i++)
       {
              printf("Please input the points next to point %d,end with 0:\n",i+1);
              poin=(struct Point *)malloc(sizeof(struct Point));
              poinpre->next=poin;
              poin->vertex[0]='v';
              poin->vertex[1]='0'+i+1;
              poin->vertex[2]='\0';
              linpre=lin=poin->work;
              linpre->next=NULL;
              for(j=0;j<num-1;j++)
              {
              printf("The number of the %d th vertex linked to vertex %d:",j+1,i+1);
              scanf("%d",&temp);
              if(temp==0)
                     {
                     lin->next=NULL;
                     break;
                     }
              else
                     {
                     lin=(struct Link *)malloc(sizeof(struct Link));
                     linpre->next=lin;
                     lin->vertex[0]='v';
                     lin->vertex[1]='0'+temp;
                     lin->vertex[2]='\0';
                     printf("Please input the value betwixt %d th point towards %d th point:",i+1,temp);
                     scanf("%d",&val);
                     lin->value=val;
                     linpre=linpre->next;
                     lin->next=NULL;
                     }
              }
              poinpre=poinpre->next;
              poin->next=NULL;
       }
       printf("Please enter the vertex where Dijkstra algorithm starts:\n");
       scanf("%d",&temp);
       tabhead=CreateTable(temp,num);
       Dijkstra(poinhead,tabhead);
       PrintTable(temp,tabhead);
       return OK;
}
struct Table * CreateTable(int vertex,int total)
{
       struct Table *head,*pre,*p;
       int i;
       head=pre=p=(struct Table *)malloc(sizeof(struct Table));
       p->next=NULL;
       for(i=0;i<total;i++)
       {
              p=(struct Table *)malloc(sizeof(struct Table));
              pre->next=p;
              if(i+1==vertex)
              {
                     p->vertex[0]='v';
                     p->vertex[1]='0'+i+1;
                     p->vertex[2]='\0';
                     p->cost=0;
                     p->Known=0;
              }
              else
              {
                     p->vertex[0]='v';
                     p->vertex[1]='0'+i+1;
                     p->vertex[2]='\0';
                     p->cost=maxium;
                     p->Known=0;
              }
              p->next=NULL;
              pre=pre->next;
       }
       return head;
}
int Dijkstra(struct Point *p1,struct Table *p2) /* Core of the programm*/
{
       int costs;
       char temp;
       struct Point *poinhead=p1,*now;
       struct Link *linna;
       struct Table *tabhead=p2,*searc,*result;
       while(1)
       {
              now=FindSmallest(tabhead,poinhead);
              if(now==NULL)
                     break;
              result=p2;
              result=result->next;
              while(result!=NULL)
              {
                     if(result->vertex[1]==now->vertex[1])
                            break;
                     else
                            result=result->next;
              }
              linna=now->work->next;
              while(linna!=NULL) /* update all the vertexs linked to the signed vertex*/
              {
                     temp=linna->vertex[1];
                     searc=tabhead->next;
                     while(searc!=NULL)
                     {
                            if(searc->vertex[1]==temp)/*find the vertex linked to the signed vertex in the table and update*/
                            {
                                   if((result->cost+linna->value)<searc->cost)
                                   {
                                   searc->cost=result->cost+linna->value;/*set the new value*/
                                   searc->path[0]='v';
                                   searc->path[1]=now->vertex[1];
                                   searc->path[2]='\0';
                                   }
                                   break;
                            }
                            else
                                   searc=searc->next;
                     }
                     linna=linna->next;
              }
       }
       return 1;
}
struct Point * FindSmallest(struct Table *head,struct Point *poinhead)
{
       struct Point *result;
       struct Table *temp;
       int min=maxium,status=0;
       head=head->next;
       poinhead=poinhead->next;
       while(head!=NULL)
       {
              if(!head->Known&&head->cost<min)
              {
                     min=head->cost;
                     result=poinhead;
                     temp=head;
                     status=1;
              }
              head=head->next;
              poinhead=poinhead->next;
       }
       if(status)
       {
              temp->Known=1;
              return result;
       }
       else
              return NULL;
}
int PrintTable(int start,struct Table *head)
{
       struct Table *begin=head;
       head=head->next;
       while(head!=NULL)
       {
              if((head->vertex[1]-'0')!=start)
                     PrintPath(start,head,begin);
              head=head->next;
       }
       return OK;
}
int PrintPath(int start,struct Table *head,struct Table *begin)
{
       struct Table *temp=begin->next,*p,*t;
       p=head;
       t=begin;
       if((p->vertex[1]-'0')!=start&&p!=NULL)
       {
              while(temp->vertex[1]!=p->path[1]&&temp!=NULL)
                     temp=temp->next;
              PrintPath(start,temp,t);
              printf("%s",p->vertex);
       }
       else
              if(p!=NULL)
              printf("\n%s",p->vertex);
       return OK;
}
