#include<stdio.h>
#include<stdlib.h>

#define CAPACITY 100
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


typedef struct student
{
        char name[50];
        int roll_no;
        int marks;
}student;


/************Creating Hash Table******************/

  student list[100];
  student sortedlist[100];
  student temp;

void create_hashtable( int roll , char nam[], int mark )
{
 
        list[roll%100].roll_no=roll;
        strcpy(list[roll%100].name , nam);
        list[roll%100].marks=mark;

        sortedlist[roll%100].roll_no=roll;
        strcpy(sortedlist[roll%100].name , nam);
        sortedlist[roll%100].marks=mark;

}

/****************************************Printing Hash Table*****************************************/

void print_hashtable(student *list)
{
   int j=0;
   printf(BOLDGREEN"==========================HASH TABLE============================\n");
   printf("================================================================\n"RESET);
   printf(BOLDRED"ROLLNO\t\t        NAME\t\t        MARK\n"RESET);
   for(j=0;j<100;j++)
   {
     if(list[j].marks!=0)
     {
       printf(BOLDWHITE"%d\t\t         %s\t\t         %d\n"RESET,list[j].roll_no,list[j].name,list[j].marks);
     }
   }
   printf(BOLDGREEN"================================================================\n"RESET);
}

/****************************************Sorting Hash Table*****************************************/

void sort_hashtable()
{
   int i=0;
   int j=0;
   temp=sortedlist[0];

   for(i=0;i<100;i++)
   {
     for(j=0;j<100;j++)
     {
       if( sortedlist[j].marks < sortedlist[j+1].marks )
       {
         temp=sortedlist[j];
         sortedlist[j]=sortedlist[j+1];
         sortedlist[j+1]=temp;
       }
     }
   }
}

/****************************************Searching Hash Table*****************************************/

void search_hashtable()
{

 int roll=0;
 printf("Enter the roll no:");
 scanf("%d",&roll);
 printf(BOLDGREEN"==========================HASH TABLE============================\n");
   printf("================================================================\n"RESET);
   printf(BOLDRED"ROLLNO\t\t        NAME\t\t        MARK\n"RESET);
 printf(BOLDWHITE"%d\t\t         %s\t\t         %d\n"RESET,list[roll%100].roll_no,list[roll%100].name,list[roll%100].marks);
 printf(BOLDGREEN"================================================================\n"RESET);

}

/************************* STARTING OF HEAP ***************************/ 
int heap[100];
int count_heap=0;
                         
typedef struct heap
{
    int arr[CAPACITY];
    int size;
}maxheap;

int p(int i)
{
    return i / 2;
}
int R(int i)
{
    return i * 2 + 1;
}
int L(int i)
{
    return 2 * i;
}
void initialise(maxheap *H)
{
    H->size = 0;
}

maxheap* tofindmax(maxheap *H, int i)
{
    int l = L(i);
    int r = R(i);
    int larg = i;
    if(l <= H->size && H->arr[l] > H->arr[larg])
        larg = l;
    if(r <= H->size && H->arr[r] > H->arr[larg])
    larg = r;
    if(larg != i)
    {
        int temp = H->arr[larg];
        H->arr[larg] = H->arr[i];
        H->arr[i] = temp;
        tofindmax(H, larg);
    }
    return H;
}

maxheap* build(int* a, int size)
{
    maxheap *H = (maxheap *) malloc( sizeof(maxheap) );
    H->size = size;
    int i;
    for(i = 1; i <= size; i++)
        H->arr[i] = a[i-1];
    for(i = size/2; i > 0; i--)
    {
        tofindmax(H, i);
    }
    return H;
}

maxheap* delete(maxheap *H, int x)
{
        int i, index = -1;
        for(i = 1; i <= H->size; i++)
        {
            if(H->arr[i] == x)
                index = i;
        }
        if(index == -1)
            return NULL;
        H->arr[index] = H->arr[H->size];
        --H->size;
        tofindmax(H, 1);
        return H;
}

void display_1(maxheap *H)
{
  int marks[100],rollno[100],i;
   char name[100][50];
    FILE *fp;
    fp = fopen("student.txt","r");
  
     i=0;
   while(! feof(fp))
    {
     fscanf(fp,"%d %s %d\n",&rollno[i],&name[i],&marks[i]);
     if(H->arr[1]==marks[i])
     {printf(BOLDRED"NAME OF STUDENT(ROLL NO) WITH HIGHEST MARKS %d is %s(%d)\n"RESET,marks[i],name[i],rollno[i]);
      break;
      }
     i=i+1;
     }
   printf("\n");
}

void display_all(maxheap *H)
{
  int marks[100],rollno[100],i,j,c=0;
   char name[100][50];
    FILE *fp;
    fp = fopen("student.txt","r");
 
   while(! feof(fp))
    { fscanf(fp,"%d %s %d\n",&rollno[c],&name[c],&marks[c]);
      c++;
    }

      printf(BOLDMAGENTA"========================MAX HEAP================================\n"RESET);
      printf(BOLDGREEN"================================================================\n"RESET);
      printf(BOLDRED"ROLLNO\t\t        NAME\t\t        MARK\n"RESET);
  
   for(j=1;j<=count_heap;j++)
   { for(i=0;i<c;i++)
    {if(H->arr[1]==marks[i])
     {
      printf(BOLDWHITE"%d\t\t         %s\t\t         %d\n"RESET,rollno[i],name[i],marks[i]);
      H=delete(H,marks[i]);
      break;
      }
    }
   }
   printf(BOLDMAGENTA"================================================================\n\n"RESET);
}
/************************* ENDING OF HEAP ***************************/

void avgmarks()
 {
    int marks[100],rollno[100],n,i,x=0;
    float avg;
    char name[100][50];
    FILE *fp;
    fp = fopen("student.txt","r");
    i=0;
    while(! feof(fp))
    {

     fscanf(fp,"%d %s %d\n",&rollno[i],&name[i],&marks[i]);
     x = x + marks[i];
     i=i+1;
    }
    n = i;
    avg = x/n;
  	printf(BOLDRED"AVERAGE MARKS OF %d STUDENTS ARE %f "RESET,n,avg);
  	fclose(fp);
  	printf("\n\n\nPRESS ANY KEY");
 }
 
/*********************** FILE WRITING FUNCTION ******************************/

void filewrite()
{
  int roll,ch,mark;
  char nam[50];
  FILE *fp;
  fp = fopen("student.txt","a");
  ch =1;
 
  while(ch)
  {
  printf(BOLDYELLOW"Enter Roll Number:");
  scanf("%d",&roll);
  printf("Name:");
  scanf("%s",&nam);
  printf("Marks:");
  scanf("%d"RESET,&mark);
  create_hashtable(roll,nam,mark);
 
  heap[count_heap]=mark;
  count_heap++;
  fprintf(fp,"%d %s %d\n",roll,nam,mark);
  printf(CYAN"\n Enter 1 to continue,0 to stop:"RESET);
  scanf("%d",&ch);
  }
 
  fclose(fp) ;
}

/******************** OUTPUTING DATA ON SCREEN***************/

void fileprint()
{
  int marks[100],rollno[100],x[100],i;
  char name[100][50];
  FILE *fp;
  fp = fopen("student.txt","r");
  i=0;

/************************************* Using File Handling ****************************************/
  printf(BOLDMAGENTA"========================FILE HANDLING===========================\n"RESET);
  printf(BOLDGREEN"================================================================\n"RESET);
  printf(BOLDRED"ROLLNO\t\t        NAME\t\t        MARK\n"RESET);
  while(!feof(fp))
  {
     fscanf(fp,"%d %s %d\n",&rollno[i],&name[i],&marks[i]);
     printf(BOLDWHITE"%d\t\t         %s\t\t         %d\n"RESET,rollno[i],name[i],marks[i]);
     i=i+1;
  }
  printf(BOLDGREEN"================================================================\n\n"RESET);
  fclose(fp);
  }


/**************** FUNC. ENDS************************/
void main()
{
  int marks[100],rollno[100],x[100],n,i,j,roll,c,mark,roll1;
  char name[100][10],nam[50];
  maxheap *H;
  printf(BOLDCYAN "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" RESET);
  printf(BOLDGREEN "\t\t\t\tWELCOME TO THE STUDET DATABASE MANAGEMENT\n");
  printf("\t\t\t\t\tOF SARDAR PATEL INSTITUTE\n" RESET);
  printf(BOLDCYAN "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" RESET);
  printf(BOLDYELLOW"\t\t\t\t\t\t\t\t\tProject Created by:\n"RESET);
  printf(BOLDRED"\t\t\t\t\t\t\t\t\t\t\tROHIT SHARMA - 54\n");
  printf("\t\t\t\t\t\t\t\t\t\t\tRAHIL SHETH - 55\n");
  printf("\t\t\t\t\t\t\t\t\t\t\tMUKUND VORA - 63\n"RESET);
 
  while(c!=8)
   {
     printf(BOLDBLUE"GIVE CHOICE--\n");
     printf("   1 TO ENTER STUDENT INFO.\n");
     printf("   2 TO SEE THE STUDENT DATABASE\n");
     printf("   3 TO DISPLAY INFO. OF RANK 1\n");
     printf("   4 TO SORT FILE ON BASIS OF MARKS AND PRINT IT USING HASH\n");
     printf("   5 TO PRINT INFO. USING MAX HEAP\n");
     printf("   6 TO PRINT STUDENT INFO. USING ROLL NO\n");
     printf("   7 TO PRINT AVERAGE MARKS OF ALL STUDENTS\n");
     printf("   8 TO EXIT\n\n--"RESET);
     scanf("%d",&c);
     printf(BOLDGREEN"YOUR CHOICE IS: %d\n"RESET,c);
   
     switch(c)
     {
     case 1:
          filewrite();
          break;
     case 2:
          fileprint();
          print_hashtable(list);
         break;
     case 3:  
         H = build(heap,count_heap);
         display_1(H);
         break;
     case 4:
         sort_hashtable();
         print_hashtable(sortedlist);
         break;
     case 5:
         H = build(heap,count_heap);
         display_all(H);
          break;
     case 6:
         search_hashtable();
          break;
     case 7:
         avgmarks();
          break;
     default:
          break;
     }
   }
   printf(BOLDMAGENTA"\n\n\nAdvantages of Using this System:\n"RESET);
   printf(BOLDYELLOW"1.It forms a file of all the students\n2.It can perform quick Sorting\n3.It instantly finds the Max Scorrer(Due to Max Heap)\n4.It instantly accesses the Data of Student Based on roll no.(Due to use of Hash)\n\n\n"RESET);

}
