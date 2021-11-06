#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include "header.h"
int main()
{
   printf("************************************************************************************************************************\n");

   printf("***********************************************WELCOME TO ABC STORES****************************************************\n");
   printf("1. CUSTOMER\n");
   printf("2. ADMINISTRATION\n");
   printf("3. EXIT\n");
   int n;
   char pass[20]="admin";
   char password[50];
   scanf("%d",&n);
   if(n==1)
   {
     int k;
     printf("HELLO CUSTOMER\n");
     printf("1. SHOP\n");
     printf("2. PAY DUES\n");
     printf("3. ADD MEMBERSHIP\n");
     printf("4. EXIT\n");
     scanf("%d",&k);
     switch(k)
     {
  	case 1:
  		billing();
                  break;
          case 2:
  		pay_dues();
  		break;
     	case 3:
  		add_mem();
  		break;
  	case 4:
  		printf("Thank you\n");
  		exit(0);
  		break;
      default:
      printf("Terminating\n");
      exit(0);
     }

   }
   else if(n==2)
   {
   	 printf("HELLO ADMIN\n");
     printf("ENTER THE PASSWORD TO PROCEED\n");
     fflush(stdin);
     int p=0;
      do
      {
          password[p]=getch();
          if(password[p]!='\r')
          {
              printf("*");
          }
          p++;
      }while(password[p-1]!='\r');
      password[p-1]='\0';
      //printf("\nYou have entered %s as password.",password);
      //getch();
     if (!(strcmp(password,pass)))
      printf("\nAUTHENTICATION SUCCESSFUL\n");
     else
     {
      printf("\nAUTHENTICATION FAILED..... EXITING\n");
      exit(0);
     }
     int u;
     printf("1. VIEW MEMBERS\n");
     printf("2. ADD ITEMS\n");
     printf("3. SEARCH CUSTOMER BY NUMBER\n");
     printf("4. SEARCH CUSTOMER BY NAME\n");
     printf("5. EXIT\n");
     scanf("%d",&u);
     if (u==1)
     {
        disp_mem();
     }
     else if(u==2)
     {
        disp_items();
        add_items();
     }
     else if(u==3)
     {
        char str[100];
       	printf("Enter the number of the member to be searched\n");
       	scanf("%s",str);
       	int a=search_by_numb(str);
     }
     else if(u==4)
     {
        char str[100];
       	printf("Enter the name of the member to be searched\n");
       	scanf("%s",str);
       	int a=search_by_name(str);
     }
     else
     {
       printf("THANK YOU");
       exit(0);
     }

   }
  else
  {
       printf("THANK YOU");
       exit(0);
  }
  return 0;
}
