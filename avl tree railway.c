#include<stdio.h>
#include<stdlib.h>
#include<string.h>



//15 seats in each sl,ac1,ac2
struct node{
    int key;  //key as passenger id 
    char name[20];
    int class; //1-sl, 2-ac1, 3-ac2
    int seat;
    char source[30];
    char des[30];
    int day,month,year;
    char tme[10];
    struct node*left;
    struct node*right;
    int height;
};  //nodes of the tree structure
struct trainlink{
    int trainnum;
    int totalp;
    int totalsl;
    int totalac1;
    int totalac2;
    struct trainlink*next;
    struct trainlink*prev;
    struct node*start;
};  //a linked list to link the roots of all the trees and store it in linked list
struct trainlink*head;
struct sorttrain{
    int data;
    int trainno;
    struct sorttrain*next;
};
struct sorttrain*val=NULL;
struct sorttrain*sorted=NULL;


int checkseats(int class,int trainnum,int n);
int countptrain();
void printsortedtrains();
int height(struct node*n);
int heightdel(struct node*n);
struct node*newnode(int key,char name[],int class,char sor[],char des[],char tme[],int day,int month,int year,int seatnum);
struct node *rightRotate(struct node *y);
struct node *rightRotatedel(struct node *y);
struct node *leftRotate(struct node *x);
struct node *leftRotatedel(struct node *x);
int getbalance(struct node* n);
int getBalancedel(struct node *n);
struct node* insert(struct node* point,int key,char name[],int class,char sor[],char des[],char tme[],int day,int month,int year,int seatnum);
void insertnode(char name[],int key,int class,int trainnum);
void availabilitycheck();
struct trainlink* createlist(int i);
void initialise();
void book();
struct node * minValueNode(struct node* node);
struct node* deleteNode(struct node* root, int key);
void cancel();
void printticket(struct node* root,int id);
void checkyourticket();
void sortbytraveldate();
void printlistdes(struct node*root);
void getlistdestination();
int countclass(struct node*tree,int i);
int count(struct node *tree);
void transfer(int data,int trainid);
void sortvalues();
void sortedInsert(struct sorttrain* newnode);
void insertionsort();
void printsortedtrains();



int max(int a,int b)
{
    if(a>b)
    {
        return a;
    }
    else{
        return b;
    }
}
int height(struct node*n)
{
    if(n==NULL)
    {
        return 0;
    }
    return(1+max(height(n->left),height(n->right)));
}
int heightdel(struct node*n)
{
    if(n==NULL)
    {
        return 0;
    }
    return n->height;
}
struct node*newnode(int key,char name[],int class,char sor[],char des[],char tme[],int day,int month,int year,int seatnum)
{
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->key=key;
    temp->class=class;
    strcpy(temp->name,name);
    strcpy(temp->source,sor);
    strcpy(temp->des,des);
    strcpy(temp->tme,tme);
    temp->seat=seatnum;
    temp->day=day;
    temp->month=month;
    temp->year=year;
    temp->left=NULL;
    temp->right=NULL;
    temp->height=0;
    return temp;
}
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;
 
    x->right = y;
    y->left = T2;
    y->height = height(y);
    x->height = height(x);
 
    return x;
}
struct node *rightRotatedel(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = max(heightdel(y->left), heightdel(y->right))+1;
    x->height = max(heightdel(x->left), heightdel(x->right))+1;
 
    return x;
}
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = height(x);
    y->height = height(y);
 
    return y;
}
struct node *leftRotatedel(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;
    y->left = x;
    x->right = T2;

    x->height = max(heightdel(x->left), heightdel(x->right))+1;
    y->height = max(heightdel(y->left), heightdel(y->right))+1;
 
    return y;
}
int getbalance(struct node* n)
{
    if(n==NULL)
    {
        return 0;
    }
    return(height(n->left) - height(n->right));
}
int getBalancedel(struct node *n)
{
    if (n == NULL)
        return 0;
    return (heightdel(n->left) - heightdel(n->right));
}
struct node* insert(struct node* point,int key,char name[],int class,char sor[],char des[],char tme[],int day,int month,int year,int seatnum)
{
    if(point==NULL)
    {
        return(newnode(key,name,class,sor,des,tme,day,month,year,seatnum));
    }
    if(key<point->key)
    {
        point->left=insert(point->left,key,name,class,sor,des,tme,day,month,year,seatnum);
    }
    else if(key>point->key)
    {
        point->right=insert(point->right,key,name,class,sor,des,tme,day,month,year,seatnum);
    }
    else{
        return point;//equal keys not allowed
    }
    point->height=height(point);
    int balance=getbalance(point);
    if(balance>1 && key<point->left->key)
    {
        return rightRotate(point);
    }
    if(balance<-1 && key>point->right->key)
    {
        return leftRotate(point);
    }
    if(balance>1 && key>point->left->key)
    {
        point->left=leftRotate(point->left);
        return rightRotate(point);
    }
    if (balance < -1 && key < point->right->key)
    {
        point->right = rightRotate(point->right);
        return leftRotate(point);
    }
    return point;
}
void insertnode(char name[],int key,int class,int trainnum)
{
    countptrain();
    struct trainlink*temp=head;
    for(int i=1;i<trainnum;i++)
    {
        temp=temp->next;
    }
    
    int seatnum;
    if(class==1)
    {
        seatnum=1+temp->totalsl;
    }
    if(class==2)
    {
        seatnum=1+temp->totalac1;
    }
    if(class==3)
    {
        seatnum=1+temp->totalac2;
    }
    char sor[30];
    char des[30];
    char tme[10];
    int day,month,year;
     if(trainnum==1)
    {
      strcpy(sor,"THANE");
      strcpy(des,"NAGPUR");
      strcpy(tme,"9:00AM");
      day=2;
      month=4;
      year=2022;
    }
    if(trainnum==2)
    {
        strcpy(sor,"NAGPUR");
      strcpy(des,"PUNE");
      strcpy(tme,"12:30PM");
      day=3;
      month=4;
      year=2022;
        
    }
    if(trainnum==3)
    {
        strcpy(sor,"NASHIK");
      strcpy(des,"PUNE");
      strcpy(tme,"1:30PM");
      day=5;
      month=4;
      year=2022;
    }
    if(trainnum==4)
    {
        strcpy(sor,"MULUND");
      strcpy(des,"PUNE");
      strcpy(tme,"3:00PM");
      day=6;
      month=4;
      year=2022;
    }
    if(trainnum==5)
    {
        strcpy(sor,"NAGPUR");
      strcpy(des,"THANE");
      strcpy(tme,"7:30PM");
      day=7;
      month=4;
      year=2022;
    }
    temp->start=insert(temp->start,key,name,class,sor,des,tme,day,month,year,seatnum);
    
    
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
struct trainlink* createlist(int i)
{
    struct trainlink* temp=(struct trainlink*)malloc(sizeof(struct trainlink));
    temp->next=NULL;
    temp->prev=NULL;
    temp->start=NULL;
    temp->trainnum=i;
    return temp;
}
void initialise()
{
    if(head==NULL)
    {
        head=createlist(1);
    }
    struct trainlink*temp=head;
    struct trainlink*temp2=(struct trainlink*)malloc(sizeof(struct trainlink));
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

void book()
{
    availabilitycheck();
     int trainnum;
    printf("PLEASE CHOOSE THE TRAIN ID FROM LEFTMOST COLUMN :");
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
        printf("Enter PASSENGER ID:");
        scanf("%d",&id);
        printf("Enter PASSENGER name:");
        scanf("%s",name);
        insertnode(name,id,c,trainnum);
        printf("BOOKING SUCCESSFULL!!!!\n");
    }
    }
    else{
        printf("NOT ENOUGH SEATS AVAILABLE!!!");
    }
}
struct node * minValueNode(struct node* node)
{
    struct node* current = node;
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
struct node* deleteNode(struct node* root, int key)
{
 
    if (root == NULL)
        return root;
    if ( key < root->key )
    {
        root->left = deleteNode(root->left, key);
    }
    else if( key > root->key )
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct node *temp = root->left ? root->left :
                                             root->right;
 
           
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
            {
             *root = *temp;
            }
            free(temp);
        }
        else
        {
            
            struct node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (root == NULL)
      return root;
    root->height = 1 + max(heightdel(root->left),
                           heightdel(root->right));
 
    int balance = getBalancedel(root);
 
    if (balance > 1 && getBalancedel(root->left) >= 0)
        return rightRotatedel(root);
 
    
    if (balance > 1 && getBalancedel(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotatedel(root);
    }
 
    if (balance < -1 && getBalancedel(root->right) <= 0)
        return leftRotatedel(root);
 
    if (balance < -1 && getBalancedel(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotatedel(root);
    }
 
    return root;
}
void cancel()
{
    int id,train;
    printf("Enter thr PASSENGER id to cancel the ticket:");
    scanf("%d",&id);
    printf("Enter the train id for that ticket:");
    scanf("%d",&train);
    struct trainlink*temp=head;
    for(int i=1;i<train;i++)
    {
        temp=temp->next;
    }
    temp->start=deleteNode(temp->start,id);
    printf("TICKET CANCELLATION SUCCESSFULL !!!\n");
}
void printticket(struct node* root,int id)
{
    countptrain();
    if(root!=NULL)
    {
        if(root->key==id)
        {
            printf("PASSENGER ID: %d   ",id);
            printf("PASSENGER NAME: %s \n",root->name);
            printf("PASSENGER SOURCE: %s  ----> ",root->source);
            printf("PASSENGER DESTINATION: %s \n",root->des);
            printf("TIME OF DEPARTURE: %s ",root->tme);
            printf("DATE OF JOURNEY: %d / %d / %d \n",root->day,root->month,root->year);
            printf("YOUR SEAT NUMBER : %d\n",root->seat);
            if(root->class==1)
            {
                printf("YOUR BERTH CLASS : SL\n");
            }
             if(root->class==2)
            {
                printf("YOUR BERTH CLASS : AC1\n");
            }
             if(root->class==3)
            {
                printf("YOUR BERTH CLASS : AC2\n");
            }
        }
        printticket(root->left,id);
        printticket(root->right,id);
    }
}
void checkyourticket()
{
    int id,train;
    printf("Enter your PASSENGER ID:");
    scanf("%d",&id);
    printf("Enter the trainID for which you had booked:");
    scanf("%d",&train);
    struct trainlink*temp=head;
    for(int i=1;i<train;i++)
    {
        temp=temp->next;
    }
    printticket(temp->start,id);

}
void sortbytraveldate()
{
    countptrain();
    int id;
    printf("Enter your PASSENGER ID:");
    scanf("%d",&id);
    struct trainlink*temp=head;
    struct node*traverse=(struct node*)malloc(sizeof(struct node));
    while(temp!=NULL)
    {
        traverse=temp->start;
        printticket(traverse,id);
        printf("\n");
        temp=temp->next;
    }
}
void printlistdes(struct node*root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        printf("%s  ",root->name);
        printf("SEAT NUMBER: %d",root->seat);
        if(root->class==1)
        {
            printf("CLASS: SL\n");
        }
        if(root->class==2)
        {
            printf("CLASS: AC1\n");
        }
        if(root->class==3)
        {
            printf("CLASS: AC2\n");
        }
        
        printlistdes(root->left);
        printlistdes(root->right);
    }
}
void getlistdestination()
{
    countptrain();
    int train;
    printf("Enter the trainID:");
    scanf("%d",&train);
    struct trainlink*temp=head;
    for(int i=1;i<train;i++)
    {
        temp=temp->next;
    }
    printlistdes(temp->start);
}

int countclass(struct node*tree,int i)
{
    int c=1;
    if(tree==NULL)
    {
        return 0;
    }
    else if(tree->class==i)
    {
        c+=countclass(tree->left,i);
        c+=countclass(tree->right,i);
        return c;
    }
}
int count(struct node *tree)
{
    int c =  1;             //Node itself should be counted
    if (tree ==NULL)
    {
        return 0;
    }
    else
    {
        c += count(tree->left);
        c += count(tree->right);
        return c;
    }
}

int countptrain()
{
    struct trainlink*temp=head;
    for(temp;temp->next!=NULL;temp=temp->next)
    {
        temp->totalp=count(temp->start);
        temp->totalsl=countclass(temp->start,1);
        temp->totalac1=countclass(temp->start,2);
        temp->totalac2=countclass(temp->start,3);
    }
    while(temp->prev!=NULL)
    {
        temp=temp->prev;
    }
    head=temp;
    
}
void transfer(int data,int trainid)
{
    struct sorttrain*temp=(struct sorttrain*)malloc(sizeof(struct sorttrain));
    temp->data=data;
    temp->trainno=trainid;
    temp->next=NULL;
    if(val==NULL)
    {
        val=temp;
        return;
    }
    struct sorttrain*temp2=val;
    for(temp2;temp2->next!=NULL;temp2=temp2->next)
    {}
    temp2->next=temp;
    return;
}
void sortvalues()
{
    
    struct trainlink*trav=head;
    for(trav;trav!=NULL;trav=trav->next)
    {
        transfer(trav->totalp,trav->trainnum);
    }
}
void sortedInsert(struct sorttrain* newnode)
{
    
    if (sorted == NULL || sorted->data >= newnode->data) {
        newnode->next = sorted;
        sorted = newnode;
    }
    else {
        struct sorttrain* current = sorted;
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
 
    struct sorttrain* current = val;
    while (current != NULL) {
        struct sorttrain* next = current->next;
        sortedInsert(current);
        current = next;
    }
    val = sorted;
}

void printsortedtrains()
{
    insertionsort();
    while (val != NULL) {
        printf("FOR TRAINID 1000%d TOTAL PASSENGERS === %d\n", val->trainno,val->data);
        val = val->next;
    }
}
int checkseats(int class,int trainnum,int n) //n is for how many seats you WANT
{
    countptrain();
    struct trainlink*temp=head;
    for(int i=1;i<trainnum;i++)
    {
        temp=temp->next;
    }
    if(class==1)
    {
        if((15-temp->totalsl-n)>=0)
        {
            return 1;
        }
        else{
            return 0;
        }
    }
    if(class==2)
    {
        if((15-temp->totalac1-n)>=0)
        {
            return 1;
        }
        else{
            return 0;
        }
    }
    if(class==3)
    {
        if((15-temp->totalac2-n)>=0)
        {
            return 1;
        }
        else{
            return 0;
        }
    }
    
}
void rangesearch()
{
    int t1,t2;
    printf("Enter from trainID[value between 1and 5(inclusive)]:");
    scanf("%d",&t1);
    printf("Enter to TrainID[value between 1and 5(inclusive)]:");
    scanf("%d",&t2);
    for(int i=t1;i<=t2;i++)
  {
    if(i==1)
    {
      printf("\n  1  \t10001\tTRAIN \t\tThane     Nagpur\t9:00AM\t2/04/2022");
    }
    if(i==2)
    {
        printf("\n  2  \t10002\tTRAIN \t\tNagpur    Pune\t        12:30PM\t3/04/2022");
        
    }
    if(i==3)
    {
        printf("\n  3  \t10003\tTRAIN \t\tNashik    Pune\t        1:30PM\t5/04/2022");
    }
    if(i==4)
    {
    	printf("\n  4  \t10004\tTRAIN \t\tMulund    Pune\t        3:00PM\t6/04/2022");
    }
    if(i==5)
    {
       printf("\n  5  \t10005\tTRAIN \t\tNagpur    Thane\t        7:30PM\t7/04/2022 \n");
    }
  }
}
int main()
{
    head=NULL;
    initialise();
    int num;
    int trainnum;
    jump:
    printf("\nENTER ONE OF THE OPTIONS :\n0-EXIT\n1-BOOK A TICKET\n2-CANCEL YOUR TICKET\n3-CHECK TICKET DETAILS\n4-AVAILABLE TRAINS\n5-PRINT MY TRAIN BOOKINGS\n6-GET LIST OF PEOPLE WITH SAME DESTINATION\n7-SORT TRAINS BASED ON NUMBER OF PASSENGERS\n8-RANGE SEARCH:\n");
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
           sortbytraveldate();
           goto jump;
           break;
        case 6:
           getlistdestination();
           goto jump;
           break;
        case 7:
           countptrain();
           sortvalues();
           printsortedtrains();
           val=NULL;
           sorted=NULL;
           goto jump;
           break;
        case 8:
           rangesearch();
           goto jump;
           break;
        default:
           printf("enter a valid choice !!!");
           goto jump;
           break;
    }
}

