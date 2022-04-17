/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct class{
    int id;
    char name[20];
    char SOURCE[30];
    char DESTINATION[30];
    int day;
    int month;
    int year;
    char tme[10];
    int seat;
    struct class* next;
    struct class* prev;
};

typedef struct train{
    int trainno;
    struct train* next;
    struct train* prev;
    struct class* SL;
    struct class* AC1;
    struct class* AC2;
};

typedef struct node
{
  int data;
  int trainnumber;
  struct node *next;
};

struct node*ptr;
struct node*sorted=NULL;

struct train* head; 

void printmytrip(int p_id);
void insertlink(int count,int trainid);
void sortbynumber();
void sortedInsert(struct node* newnode);
void insertionsort();
void printsortedtrains();
void availabilitycheck();
struct class* getnewnode(int id,char name[],int trainnum);
int checkseats(int c,int trainnum,int n);
void insertnode(char name[],int id,int c,int trainnum);
void book();
void cancel();
void printsrcdes(int id);
void checkyourticket();
struct train* createlist(int i);
void inittialise();


void printmytrip(int p_id)
{
    struct train*temp=head;
    struct class*t=(struct class*)malloc(sizeof(struct class));
    for(int i=1;i<=5;i++)
    {
        t=temp->SL;
        for(t;t!=NULL;t=t->next)
        {
            if(t->id==p_id)
            {
                printf("TRAIN NO.:1000%d TIME:%s \nSOURCE:%s DESTINATION:%s DATE:%d/%d/%d\nSEAT NUMBER:%d CLASS: SL\n",i,t->tme,t->SOURCE,t->DESTINATION,t->day,t->month,t->year,t->seat);
            }
        }
        t=temp->AC1;
        for(t;t!=NULL;t=t->next)
        {
            if(t->id==p_id)
            {
                printf("TRAIN NO.:1000%d TIME:%s \nSOURCE:%s DESTINATION:%s DATE:%d/%d/%d\nSEAT NUMBER:%d CLASS: AC1\n",i,t->tme,t->SOURCE,t->DESTINATION,t->day,t->month,t->year,t->seat);
            }
        }
        t=temp->AC2;
        for(t;t!=NULL;t=t->next)
        {
            if(t->id==p_id)
            {
                printf("TRAIN NO.:1000%d TIME:%s \nSOURCE:%s DESTINATION:%s DATE:%d/%d/%d\nSEAT NUMBER:%d CLASS: AC2\n",i,t->tme,t->SOURCE,t->DESTINATION,t->day,t->month,t->year,t->seat);
            }
        }
        temp=temp->next;
        
    }
}

void insertlink(int count,int trainid)
{
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->data=count;
    temp->trainnumber=trainid;
    temp->next=NULL;
    if(ptr!=NULL)
    {
        temp->next=ptr;
    }
    ptr=temp;
}
void sortbynumber()
{
    struct train*temp=head;
    struct class*t=(struct class*)malloc(sizeof(struct class));
    int count=0;
    for(int i=1;i<=5;i++)
    {
        count=0;
        t=temp->SL;
        for(t;t!=NULL;t=t->next)
        {
           count+=1; 
        }
        t=temp->AC1;
        for(t;t!=NULL;t=t->next)
        {
           count+=1; 
        }
        t=temp->AC2;
        for(t;t!=NULL;t=t->next)
        {
           count+=1; 
        }
        temp=temp->next;
        insertlink(count,i);
    }
    printsortedtrains();
}
void sortedInsert(struct node* newnode)
{
    
    if (sorted == NULL || sorted->data >= newnode->data) {
        newnode->next = sorted;
        sorted = newnode;
    }
    else {
        struct node* current = sorted;
        while (current->next != NULL
               && current->next->data < newnode->data) {
            current = current->next;
        }
        newnode->next = current->next;
        current->next = newnode;
    }
}
void insertionsort()
{
 
    struct node* current = ptr;
    while (current != NULL) {
        struct node* next = current->next;
        sortedInsert(current);
        current = next;
    }
    ptr = sorted;
}

void printsortedtrains()
{
    insertionsort();
    while (ptr != NULL) {
        printf("FOR TRAINID 1000%d TOTAL PASSENGERS === %d\n", ptr->trainnumber,ptr->data);
        ptr = ptr->next;
    }
}

void availabilitycheck()
{
	
	printf("\n--------------------------------AVAILABLE TRAINS--------------------------------\n");
	printf("________________________________________________________________________________");
	printf("\n\n Tr.Id\tTr.No\tTrain Name\tOrigin   Destination\tTime\tDate\n");
	printf("________________________________________________________________________________\n");
	printf("\n  1  \t10001\tTRAIN \t\tThane     Nagpur\t9:00AM\t2/04/2022");
	printf("\n  2  \t10002\tTRAIN \t\tNagpur    Pune\t        12:30PM\t3/04/2022");
	printf("\n  3  \t10003\tTRAIN \t\tNashik    Pune\t        1:30PM\t5/04/2022");
	printf("\n  4  \t10004\tTRAIN \t\tMulund    Pune\t        3:00PM\t6/04/2022");
	printf("\n  5  \t10005\tTRAIN \t\tNagpur    Thane\t        7:30PM\t7/04/2022");
	printf("\n________________________________________________________________________________\n");
}
struct class* getnewnode(int id,char name[],int trainnum)
{
    struct class*temp=(struct class*)malloc(sizeof(struct class));
    strcpy(temp->name,name);
    temp->id=id;
    temp->next=NULL;
    temp->prev=NULL;
    if(trainnum==1)
    {
      strcpy(temp->SOURCE,"THANE");
      strcpy(temp->DESTINATION,"NAGPUR");
      strcpy(temp->tme,"9:00AM");
      temp->day=2;
      temp->month=4;
      temp->year=2022;
    }
    if(trainnum==2)
    {
        strcpy(temp->SOURCE,"NAGPUR");
      strcpy(temp->DESTINATION,"PUNE");
      strcpy(temp->tme,"12:30PM");
      temp->day=3;
      temp->month=4;
      temp->year=2022;
        
    }
    if(trainnum==3)
    {
        strcpy(temp->SOURCE,"NASHIK");
      strcpy(temp->DESTINATION,"PUNE");
      strcpy(temp->tme,"1:30PM");
      temp->day=5;
      temp->month=4;
      temp->year=2022;
    }
    if(trainnum==4)
    {
        strcpy(temp->SOURCE,"MULUND");
      strcpy(temp->DESTINATION,"PUNE");
      strcpy(temp->tme,"3:00PM");
      temp->day=6;
      temp->month=4;
      temp->year=2022;
    }
    if(trainnum==5)
    {
        strcpy(temp->SOURCE,"NAGPUR");
      strcpy(temp->DESTINATION,"THANE");
      strcpy(temp->tme,"7:30PM");
      temp->day=7;
      temp->month=4;
      temp->year=2022;
    }
    return temp;
}

int checkseats(int c,int trainnum,int n)
{
    int count=0;
     struct train*temp=head;
    for(int i=1;i<trainnum;i++)
    {
        temp=temp->next;
    }
    if(c==1)
    {
        struct class* t=temp->SL;
        while(t!=NULL)
        {
            if(t!=NULL)
            {
                count++;
            
            }
            t=t->next;
        }
        if((15-count-n)>=0)
        {
            return 1;
        }
        else{
            return 0;
        }
    }
    if(c==2)
    {
        struct class* t=temp->AC1;
        while(t!=NULL)
        {
            if(t!=NULL)
            {
                count++;
            
            }
            t=t->next;
        }
        if((15-count-n)>=0)
        {
            return 1;
        }
        else{
            return 0;
        }
    }
    if(c==3)
    {
        struct class* t=temp->AC2;
        while(t!=NULL)
        {
            if(t!=NULL)
            {
                count++;
            
            }
            t=t->next;
        }
        if((15-count-n)>=0)
        {
            return 1;
        }
        else{
            return 0;
        }
    }
    
}
void insertnode(char name[],int id,int c,int trainnum)
{
    struct train*temp=head;
    for(int i=1;i<trainnum;i++)
    {
        temp=temp->next;
    }
    if(c==1)
    {
           struct class* newnode=getnewnode(id,name,trainnum);
           struct class*t=temp->SL;
           if(t==NULL)
           {
              temp->SL=newnode;
               while(temp->prev!=NULL)
               {
                   temp=temp->prev;
               }
               head=temp;
               return;
           }
           for(t;t->next!=NULL;t=t->next)
           {
            
           }
           t->next=newnode;
           t->next->prev=t;
           while(t->prev!=NULL)
           {
               t=t->prev;
           }
           temp->SL=t;
           while(temp->prev!=NULL)
               {
                   temp=temp->prev;
               }
           head=temp;
    }
    if(c==2)
    {  
         struct class* newnode=getnewnode(id,name,trainnum);
           struct class*t=temp->AC1;
           if(t==NULL)
           {
              temp->AC1=newnode;
              while(temp->prev!=NULL)
               {
                   temp=temp->prev;
               }
               head=temp;
               return;
           }
           for(t;t->next!=NULL;t=t->next)
           {
            
           }
           t->next=newnode;
           t->next->prev=t;
           while(t->prev!=NULL)
           {
               t=t->prev;
           }
           temp->AC1=t;
           while(temp->prev!=NULL)
               {
                   temp=temp->prev;
               }
           head=temp;
        
    }
    if(c==3)
    {
          struct class* newnode=getnewnode(id,name,trainnum);
           struct class*t=temp->AC2;
           if(t==NULL)
           {
              temp->AC2=newnode;
              while(temp->prev!=NULL)
               {
                   temp=temp->prev;
               }
               head=temp;
               return;
           }
           for(t;t->next!=NULL;t=t->next)
           {
            
           }
           t->next=newnode;
           t->next->prev=t;
           while(t->prev!=NULL)
           {
               t=t->prev;
           }
           temp->AC2=t;
           while(temp->prev!=NULL)
               {
                   temp=temp->prev;
               }
           head=temp;
        
    }
}

void book()
{
    availabilitycheck();
    int trainnum;
    printf("PLEASE CHOOSE THR TRAIN ID FROM LEFTMOST COLUMN :");
    scanf("%d",&trainnum);
    int n;
    int id;
    char name[20];
    printf("ENTER NUMBER OF SEATS REQUIRED :");
    scanf("%d",&n); // n is for how many
    int c;
    printf("CHOOSE CLASS OF TRAIN YOU WANT: \n 1- SL\n 2-AC1\n 3- AC2 :\n");
    scanf("%d",&c);  //c is for class
    if(checkseats(c,trainnum,n))
    {
         for(int i=1;i<=n;i++)
        {
             printf("ENTER PASSENGER ID :");
             scanf("%d",&id);
             printf("ENTER NAME OF PASSENGER :");
             scanf("%s",name);
             insertnode(name,id,c,trainnum);
             printf("BOOKING SUCCESSFUL !!\n");
             
             
        }
    }
    else{
        printf("NOT ENOUGH SEATS LEFT IN THIS CLASS!!!\n ");
    }
}
void cancel()
{
    int id,trainid,class;
    char name[20];
    printf("enter your id :");
    scanf("%d",&id);
    printf("enter your class number :");
    scanf("%d",&class);
    printf("enter your train id :");
    scanf("%d",&trainid);
    struct train*temp=head;
    struct class*x=(struct class*)malloc(sizeof(struct class));
    for(int i=1;i<trainid;i++)
    {
        temp=temp->next;
    }
    if(class==1)
    {
        struct class*t=temp->SL;
        for(t;t!=NULL;t=t->next)
        {
            if(temp->SL->id==id)
            {
                temp->SL=temp->SL->next;
                while(temp->prev!=NULL)
               {
                   temp=temp->prev;
               }
                head=temp;
                return;
            }
            if((t->next)->id==id)
            {
                t->next=t->next->next;
                t->next->prev=t;
                while(t->prev!=NULL)
                {
                    t=t->prev;
                }
                temp->SL=t;
                while(temp->prev!=NULL)
               {
                   temp=temp->prev;
               }
                head=temp;
                return;
            }
        }
        printf("INVALID data given!!!!");
    }
    if(class==2)
    {
        struct class*t=temp->AC1;
        for(t;t!=NULL;t=t->next)
        {
            if(temp->AC1->id==id)
            {
                temp->AC1=temp->AC1->next;
                while(temp->prev!=NULL)
               {
                   temp=temp->prev;
               }
                head=temp;
                return;
            }
            if((t->next)->id==id)
            {
                t->next=t->next->next;
                t->next->prev=t;
                while(t->prev!=NULL)
                {
                    t=t->prev;
                }
                temp->AC1=t;
                while(temp->prev!=NULL)
               {
                   temp=temp->prev;
               }
                head=temp;
                return;
            }
        }
        printf("INVALID data given!!!!");
    }
    if(class==3)
    {
        struct class*t=temp->AC2;
        for(t;t!=NULL;t=t->next)
        {
            if(temp->AC2->id==id)
            {
                temp->AC2=temp->SL->next;
                while(temp->prev!=NULL)
               {
                   temp=temp->prev;
               }
                head=temp;
                return;
            }
            if((t->next)->id==id)
            {
                t->next=t->next->next;
                t->next->prev=t;
                while(t->prev!=NULL)
                {
                    t=t->prev;
                }
                temp->AC2=t;
                while(temp->prev!=NULL)
               {
                   temp=temp->prev;
               }
                head=temp;
                return;
            }
        }
        printf("INVALID data given!!!!");
    }
    
}

void printsrcdes(int id)
{
    if(id==1)
    {
        printf("SOURCE: THANE\t\t DESTINATION: NAGPUR\t TIME:9:00AM\n");
    }
    if(id==2)
    {
        printf("SOURCE: NAGPUR\t\t DESTINATION: PUNE\t TIME:12:30PM\n");
    }
    if(id==3)
    {
        printf("SOURCE: NASHIK\t\t DESTINATION: PUNE\t TIME:1:30PM\n");
    }
    if(id==4)
    {
        printf("SOURCE: MULUND\t\t DESTINATION: PUNE\t TIME:3:00PM\n");
    }
    if(id==5)
    {
        printf("SOURCE: NAGPUR\t\t DESTINATION: THANE\t TIME:7:00PM\n");
    }
}
void checkyourticket()
{
     int id,c,trainid;;
     int seat=0;
     printf("enter your id number :");
     scanf("%d",&id);
     printf("enter your selected class :");
     scanf("%d",&c);
     printf("enter train id: ");
     scanf("%d",&trainid);
     int status=0;
     struct train* temp=head;
     struct class* t=(struct class*)malloc(sizeof(struct class));
     for(int i=1;i<trainid;i++)
     {
         temp=temp->next;
     }
          if(c==1)
          {
              t=temp->SL;
              for(t;t!=NULL;t=t->next)
              {
                  seat+=1;
                  if(t->id==id)
                  {
                      printsrcdes(trainid);
                      printf("YOUR TRAIN NUMBER:1000%d\nYOUR SEAT NUMBER:%d \n",trainid,seat);
                      if(seat%3==0)
                      {
                          printf("YOUR SEAT TYPE: UPPER BERTH\n");
                      }
                      else{
                          printf("YOUR SEAT TYPE: LOWER BERTH\n");
                      }
                      seat=0;
                      status=0;
                      return;
                  }
                  
              }
              seat=0;
              status=1;
          }
          if(c==2)
          {
              t=temp->AC1;
              for(t;t!=NULL;t=t->next)
              {
                  seat+=1;
                  if(t->id==id)
                  {
                      printsrcdes(trainid);
                      printf("YOUR TRAIN NUMBER:1000%d\nYOUR SEAT NUMBER:%d \n",trainid,seat);
                      if(seat%3==0)
                      {
                          printf("YOUR SEAT TYPE: UPPER BERTH\n");
                      }
                      else{
                          printf("YOUR SEAT TYPE: LOWER BERTH\n");
                      }
                      seat=0;
                      status=0;
                      return;
                  }
                  
              }
              seat=0;
              status=1;
          }
          if(c==3)
          {
              t=temp->AC2;
              for(t;t!=NULL;t=t->next)
              {
                  seat+=1;
                  if(t->id==id)
                  {
                      printsrcdes(trainid);
                      printf("YOUR TRAIN NUMBER:1000%d\nYOUR SEAT NUMBER:%d \n",trainid,seat);
                      
                      if(seat%3==0)
                      {
                          printf("YOUR SEAT TYPE: UPPER BERTH\n");
                      }
                      else{
                          printf("YOUR SEAT TYPE: LOWER BERTH\n");
                      }
                      seat=0;
                      status=0;
                      return;
                  }
                  
              }
              seat=0;
              status=1;
             
          }
     if(status==1)
     {
         printf("INVALID ID!!!\n");
     }
}

struct train* createlist(int i)
{
    struct train* temp=(struct train*)malloc(sizeof(struct train));
    temp->next=NULL;
    temp->prev=NULL;
    temp->trainno=i;
    temp->SL=NULL;
    temp->AC1=NULL;
    temp->AC2=NULL;
    return temp;
}
void inittialise()
{
    if(head==NULL)
    {
        head=createlist(1);
    }
    struct train*temp=head;
    struct train*temp2=(struct train*)malloc(sizeof(struct train));
    for(int i=2;i<=5;i++)
    {
        temp2=createlist(i);
        temp2->prev=temp;
        temp->next=temp2;
        temp=temp->next;
    }
    while(temp->prev!=NULL)
    {
        temp=temp->prev;
    }
    head=temp;
}
void getlistdestination(int trainid)
{
    struct train*temp=head;
    for(int i=1;i<trainid;i++)
    {
        temp=temp->next;
    }
    struct class*t=(struct class*)malloc(sizeof(struct class));
    t=temp->SL;
    while(t!=NULL)
    {
        printf("PASSENGER ID: %d PASSENGER NAME:%s CLASS: SL\n",t->id,t->name);
        t=t->next;
    }
    t=temp->AC1;
    while(t!=NULL)
    {
        printf("PASSENGER ID: %d PASSENGER NAME:%s CLASS: AC1\n",t->id,t->name);
        t=t->next;
    }
    t=temp->AC2;
    while(t!=NULL)
    {
        printf("PASSENGER ID: %d PASSENGER NAME:%s CLASS: AC2\n",t->id,t->name);
        t=t->next;
    }
    
    
}
int main()
{
    ptr=NULL;
    struct train* temp=(struct train*)malloc(sizeof(struct train));
    head=NULL;
    inittialise();
    int p_id;
    int num;
    jump:
    printf("ENTER ONE OF THE OPTIONS :\n0-EXIT\n1-BOOK A TICKET\n2-CANCEL YOUR TICKET\n3-CHECK TICKET DETAILS\n4-AVAILABLE TRAINS\n5-PRINT MY TRAIN BOOKINGS\n6-PRINT SORTED TRAINS(BASED ON NUMBER OF PASSENGER)\n7-GET LIST OF PEOPLE WITH SAME DESTINATION:\n");
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
        case 0:
           break;
        case 1:
           book();
           goto jump;
           break;
        case 2:
           cancel();
           goto jump;
           break;
        case 4:
           availabilitycheck();
           goto jump;
           break;
        case 3:
           checkyourticket();
           goto jump;
           break;
        case 5:
           printf("ENTER PASSENGER ID: ");
           scanf("%d",&p_id);
           printmytrip(p_id);
           goto jump;
           break;
        case 6:
           sortbynumber();
        case 7:
           printf("ENTER THE TRAIN ID TO GET ITS PASSENGERS DATA: ");
           scanf("%d",&num);
           getlistdestination(num);
        default:
           printf("enter a valid choice !!!");
           goto jump;
           break;
    }
    
    
}
