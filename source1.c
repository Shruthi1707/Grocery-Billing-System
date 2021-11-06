#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include "header.h"

typedef struct member_info{
  char name[50];
  char phone[20];
  char points[10];
}MEM_INFO_T;

typedef struct customer_info{
  char name[50];
  char phone[20];
  char amount[10];
}INFO_T;

void disp_items()
{

  FILE* fp = fopen("items.csv", "r");
    if (!fp)
        printf("Can't open file\n");

    else
    {
	      printf("The Items available are:\n");
        char buffer[1024];

        int row = 0;
        int column = 0;

        while (fgets(buffer,1024, fp))
        {
            column = 0;
            row++;

            if (row == 1)
                continue;

            // Splitting the data
            char* value = strtok(buffer, ",");

            while (value)
                {
                // Column 1
                if (column == 0) {
                    printf("SL.no: ");
                }

                // Column 2
                if (column == 1) {
                    printf("\tItem Name: ");
                }

                // Column 3
                if (column == 2) {
                    printf("\t\tItem Code: ");
                }
		            if (column == 3)
                {
                    printf("\tMRP: ");
                }
                printf("%s", value);
                value = strtok(NULL, ",");
                column++;
            }

            printf("\n");
    }
	fclose(fp);
    }
}

void disp_mem()
{
 FILE* fp = fopen("member_details.csv", "r");
    if (!fp)
        printf("Can't open file\n");

    else {
        char buffer[1024];

        int row = 0;
        int column = 0;

        while (fgets(buffer,1024, fp))
        {
            column = 0;
            row++;

            //if (row == 1)
              //  continue;

            // Splitting the data
            char* value = strtok(buffer, ",");

            while (value){

                printf("%s\t", value);
                value = strtok(NULL, ",");
                column++;
            }

            printf("\n");
    }

	    fclose(fp);
    }
}

void add_mem()
{
 FILE* fp1=fopen("member_details.csv","a+");
 char name[100];
 char num[20];
 int points = 750;
 if (!fp1)
 {
  printf("FILE NOT FOUND\n");
 }
 else
 {
   char ch;
   printf("ENTER YOUR NAME\n");
   fflush(stdin);
   scanf("%[^\n]s",name);
   printf("ENTER YOUR NUMBER\n");
   fflush(stdin);
   scanf("%s",num);
   while(strlen(num)!=10)
    {
      printf("Phone number has to be ten digits, enter phone number again: \n");
      scanf("%s",num);
    }
   fprintf(fp1,"\n%s,%s,%d\n",name,num,points);
   printf("Please pay Rs 1500 as advance to obtain membership(Y OR N)\n");
   fflush(stdin);
   scanf("%c",&ch);
   if(ch == 'Y' || ch == 'y')
   	payment_membership();
   else
  	printf("Hope to see you next time\n");
 }
 fclose(fp1);
}
int payment(char name1[],char number[],int amount1)
{
	int choice;
	printf("1.Pay now\n2.Add to tab\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			printf("Payment successful\n");
			return 1;
      break;
		case 2:
			printf("Balance added to tab\n");
      balance_due(name1,number,amount1);
			return 0;
	}

}
void balance_due(char name1[],char number[],int amount1)
{
	int i = 0;
	int y;
	INFO_T info[100];
	FILE* fp2 = fopen("file.csv", "r");

	if (!fp2)
  	{
		printf("Can't open file\n");
	}
	else
	{
		char buffer[1024];

      int row = 0;
      int column = 0;

      while (fgets(buffer,1024,fp2))
      {
        column = 0;
        row++;
        //if(row==1)
          //continue;
        // Splitting the data
        char* value = strtok(buffer, ", ");
        while (value)
        {
          // Column 1
          if (column == 0)
          {
            //printf("name: %s\n",value);
            strcpy(info[i].name,value);
          }

          // Column 2
          if (column == 1)
          {
            //printf("phone no. :%s\n",value);
            strcpy(info[i].phone,value);
          }
	  if (column == 2)
	  {
		strcpy(info[i].amount,value);
	  }
          value=strtok(NULL,", ");
          column++;

        }
        i++;
        //printf("i1 is %d\n",i);
     }
	int j;
	for(j=0;j<=i;j++)
    		{
      			//printf("1-->%s\n",phone);
      			//printf("2-->%s\n",info[j].phone);
      			if ((strcmp(number,info[j].phone))==0)
      			{
        			//printf("Welcome %s\n",info[j].name);
        			y=0;
        			break;
      			}

    		}
		fclose(fp2);
		FILE* fpp1= fopen("file.csv","w");
 		if (!fpp1)
 		{
 			 printf("FILE NOT FOUND\n");
			 exit(0);
 		}
    		if(y!=0)
    		{
  	 		strcpy(info[j].name,name1);
			strcpy(info[j].phone,number);
			itoa(amount1,info[j].amount,10);
			for(int k = 0;k<j;k++)
			{
				//printf("%s,%s,%s\n",info[k].name,info[k].phone,info[k].amount);
				fprintf(fpp1,"%s,%s,%s\n",info[k].name,info[k].phone,info[k].amount);
			}
		 	fclose(fpp1);
    		}
		else
		{
			itoa(amount1,info[j].amount,10);
			for(int k = 0;k<i;k++)
			{
				//printf("%s,%s,%s\n",info[k].name,info[k].phone,info[k].amount);
				fprintf(fpp1,"%s,%s,%s\n",info[k].name,info[k].phone,info[k].amount);
			}
		 	fclose(fpp1);
		}
}
}
void pay_dues()
{
  char phone[20];
  printf("Please enter your phone number: \n");
  scanf("%s",phone);
  while(strlen(phone)!=10)
  {
    printf("Phone number has to be ten digits, enter phone number again: \n");
    scanf("%s",phone);
  }

  payment_due(phone);
}
void payment_due(char phone[20])
{
	int i = 0;
	int y;
	INFO_T info[100];
	FILE* fp2 = fopen("file.csv", "r");

	if (!fp2)
  	{
		printf("Can't open file\n");
	}
	else
	{
		char buffer[1024];

      int row = 0;
      int column = 0;

      while (fgets(buffer,1024,fp2))
      {
        column = 0;
        row++;
        //if(row==1)
          //continue;
        // Splitting the data
        char* value = strtok(buffer, ", ");
        while (value)
        {
          // Column 1
          if (column == 0)
          {
            //printf("name: %s\n",value);
            strcpy(info[i].name,value);
          }

          // Column 2
          if (column == 1)
          {
            //printf("phone no. :%s\n",value);
            strcpy(info[i].phone,value);
          }
	  if (column == 2)
	  {
		strcpy(info[i].amount,value);
	  }
          value=strtok(NULL,", ");
          column++;

        }
        i++;
        //printf("i1 is %d\n",i);
     }
	int j;
	for(j=0;j<=i;j++)
    		{
      			//printf("1-->%s\n",phone);
      			//printf("2-->%s\n",info[j].phone);
      			if ((strcmp(phone,info[j].phone))==0)
      			{
        			printf("Welcome %s\n",info[j].name);
        			y=0;
        			break;
      			}

    		}
    		if(y!=0)
    		{
  	 		printf("\nCustomer not found..\n");

    		}
		else
		{
			printf("Amount due is %s\n",info[j].amount);
			printf("Enter the amount you are willing to pay:\n");
			int pay_amount;
			scanf("%d",&pay_amount);
			//printf("%d\n",pay_amount);
			int final_amount = atoi(info[j].amount) - pay_amount;
			final_amount = 0-final_amount;
			printf("Balance left = %d\n",final_amount);
			itoa(final_amount,info[j].amount,10);
			//printf("%s %s %s\n",info[j].name,info[j].phone,info[j].amount);
			fclose(fp2);
			FILE* fpp1= fopen("file.csv","w");
 				if (!fpp1)
 				{
 					 printf("FILE NOT FOUND\n");
 				}
				else
				{
					//fprintf(fpp1,"%s,%s,%s\n","Name","Phone","Amount");
					for(int k = 0;k<i;k++)
					{
						//printf("%s,%s,%s\n",info[k].name,info[k].phone,info[k].amount);
 						fprintf(fpp1,"%s,%s,%s\n",info[k].name,info[k].phone,info[k].amount);
					}
				 	fclose(fpp1);
				}

		}

	}
}

void add_items()
{
	FILE* fp = fopen("items.csv", "a+");
    	if (!fp)
        	printf("Can't open file\n");
	else
	{
		char item_name[100];
 		int item_code;
 		int sl_no;
 		int mrp;
 		printf("ENTER THE SL.NO\n");
 		scanf("%d",&sl_no);
 		printf("ENTER THE NAME OF THE ITEM\n");
 		fflush(stdin);
 		scanf("%[^\n]s",item_name);
 		printf("ENTER THE CODE OF THE ITEM\n");
 		scanf("%d",&item_code);
 		printf("ENTER THE MRP OF THE ITEM\n");
 		scanf("%d",&mrp);
 		fprintf(fp,"%d,%s,%d,%d\n",sl_no,item_name,item_code,mrp);
 		printf("Added items successfully\n");
		fclose(fp);
	}
}
void payment_membership()
{
	printf("Payment Successful\n");
 	printf("You have been awarded 750 points\n");
  printf("MEMBERSHIP ADDED SUCCESSFULLY......WELCOME TO ABC STORE DEAR MEMBER\n");
}

int search_by_name(char *str)
{
    FILE *file1=fopen("file.csv","r");
    int find_result = 0;
    char temp[40];

    if(file1 == NULL)
    {
        printf("File not found\n");
    }

    while(fgets(temp, 40, file1) != NULL)
    {
      char *NAME=strtok(temp,",");
        char *NUMBER=strtok(NULL,",");
  char *POINTS=strtok(NULL,",");
        //if((strstr(NAME, str)) != NULL)
        if((strcmp(NAME, str))==0)
  {
      printf("Customer Found\n\n");
      printf("NAME\tPHONE NUMBER\tBALANCE_DUE\n");
            printf("%s\t",temp);
      printf("%s\t ",NUMBER);
      printf("%s",POINTS);
            find_result++;
        }
    }

    if(find_result == 0)
    {
        printf("\nSorry, couldn't find a match.\n");
    }
    fclose(file1);
    return(0);
}

int search_by_numb(char *str)
{
    FILE *file2=fopen("file.csv","r");
    int find_result = 0;
    char temp[1000];
    char temp1[40];
    //fgets(temp1,40,file2);
    if(file2 == NULL)
    {
        printf("File not found\n");
    }

    while(fgets(temp, 1000, file2) != NULL)
    {
    	char *NAME=strtok(temp,",");
        char *NUMBER=strtok(NULL,",");
	char *POINTS=strtok(NULL,",");
        //if((strstr(NUMBER, str)) != NULL)
        if((strcmp(NUMBER, str)) == 0)
	{
	    printf("Customer Found\n\n");
	    printf("NAME\tPHONE NUMBER\tBALANCE_DUE\n");
            printf("%s\t",temp);
	    printf("%s\t ",NUMBER);
	    printf("%s",POINTS);
            find_result++;
            break;
        }
    }

    if(find_result == 0)
    {
        printf("\nSorry, couldn't find a match.\n");
    }
    fclose(file2);
    return(0);
}

float billing_member(char* phone,float amount1)
{
  int i = 0;
	float amount;
  MEM_INFO_T info[100];
  char name[100];
	FILE* fp2 = fopen("member_details.csv", "r");
	if (!fp2)
  {
		printf("Can't open file\n");
	}
  else
  {
  	char buffer[1024];

      int row = 0;
      int column = 0;

      while (fgets(buffer,1024,fp2))
      {
        column = 0;
        row++;
        //if(row==1)
          //continue;
        // Splitting the data
        char* value = strtok(buffer, ", ");
        while (value)
        {
          // Column 1
          if (column == 0)
          {
            //printf("name: %s\n",value);
            strcpy(info[i].name,value);
          }

          // Column 2
          if (column == 1)
          {
            //printf("phone no. :%s\n",value);
            strcpy(info[i].phone,value);
          }
	  if (column == 2)
	  {
		strcpy(info[i].points,value);
	  }
          value=strtok(NULL,", ");
          column++;

        }
        i++;
        //printf("i1 is %d\n",i);
     }


      // Close the file
      fclose(fp2);
    }
	FILE* fp3 = fopen("member_details.csv", "a+");

	if (!fp3)
  	{
		printf("Can't open file\n");
	}
        else
  	{
    		int y=1;
    		int j;
  		// Saving data in file
    		//printf("i2 is = %d\n",i);
    		for(j=0;j<i;j++)
    		{
      			//printf("1-->%s\n",phone);
      			//printf("2-->%s\n",info[j].phone);
      			if ((strcmp(phone,info[j].phone))==0)
      			{
        			printf("Welcome %s\n",info[j].name);
        			y=0;
        			break;
      			}

    		}
    		if(y!=0)
    		{
  	 		printf("\nMember not found..\n");
		        return -1;
    		}
		else

		{
			printf("Thank you for being a member\n");
			float amount_init = amount1;
			int points_mem = atoi(info[j].points);
			float amount_points = points_mem*0.5;
			printf("\nNumber of points currently in your balance = %d\n",points_mem);
			printf("Amount the points correspond to = %.2f\n",amount_points);
			printf("Would you like to redeem your points (y/n)?\n");
			char ch;
			fflush(stdin);
			scanf("%c",&ch);
			if(ch == 'N' || ch == 'n')
			{
				amount = amount_init;
				printf("Congratulations! you have earned 50 points\n");
				int points_add = atoi(info[j].points) + 50;
				itoa(points_add,info[j].points, 10);
				//printf("%s %s %s\n",info[j].name,info[j].phone,info[j].points);
				FILE* fpp1=fopen("member_details.csv","w");
 				if (!fpp1)
 				{
 					 printf("FILE NOT FOUND\n");
 				}
				else
				{
					fprintf(fpp1,"%s,%s,%s","Name","Phone","Points");
					for(int k = 0;k<i;k++)
					{
 						fprintf(fpp1,"%s,%s,%s",info[k].name,info[k].phone,info[k].points);
					}
				 	fclose(fpp1);
				}

			}
			else
			{
				if(amount_init>amount_points)
        {

        	amount = amount_init - amount_points;
                amount_points=(int)0;
        }
        else
				{
					amount = 0;
					amount_points = (int)((amount_points-amount_init)/0.5);
                                        itoa(amount_points,info[j].points, 10);
				}
				printf("Congratulations! you have earned 50 points\n");
                                int total_points = (amount_points) + 50;
				itoa(total_points,info[j].points, 10);
                                printf("Points remaining = %d\n",total_points);
				FILE* fpp=fopen("member_details.csv","w");
 				if (!fpp)
 				{
 					 printf("FILE NOT FOUND\n");
 				}
				else
				{
					//printf("%d\n",i);
					for(int k = 0;k<i;k++)
					{

						//printf("%s,%s,%s\n",info[k].name,info[k].phone,info[k].points);
 						fprintf(fpp,"%s,%s,%s",info[k].name,info[k].phone,info[k].points);
					}
				 	fclose(fpp);
				}


			}
		}
	}
	return amount;
}
