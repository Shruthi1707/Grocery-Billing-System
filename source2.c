#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"header.h"
#include<stdlib.h>

typedef struct customer_info{
  char name[50];
  char phone[20];
}INFO_T;

typedef struct shopping{
  char item_name[50];
  int qty;
  int slno;
}SHOP_T;

typedef struct items{
  int slno;
  char item[50];
  int code;
  int mrp;
}ITEM_T;


void billing()
{
  int i = 0;
  INFO_T info[100];
  char name[100],phone[20];
  printf("Welcome! Please enter your full name: \n");
  fflush(stdin);
  scanf("%[^\n]s",name);
  fflush(stdin);
  printf("Please enter your phone number: \n");
  scanf("%s",phone);
  while(strlen(phone)!=10)
  {
    printf("Phone number has to be ten digits, enter phone number again: \n");
    scanf("%s",phone);
  }


  printf("Welcome, %s!\n",name);
  disp_items();
  printf("Enter the items you would like to buy from the list and the quantity : \n");
  FILE* fp1 = fopen("bill.csv","w");
  fprintf(fp1,"slno,item,qty\n");
  char q = 'Y';
  char item[50];
  int qty,price,slno=0;
  while(q=='Y'|| q=='y')
  {
    slno++;

    printf("Enter item: ");
    scanf("%s",item);
    fflush(stdin);
    printf("Enter qty(in kg/no. of packets): ");
    scanf("%d",&qty);
    printf("Do you want more items(Y or N): ");
    fflush(stdin);
    scanf("%c",&q);
    fprintf(fp1,"%d, %s, %d \n",slno,item,qty);
  }
  fclose(fp1);

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
        if(row==1)
          continue;
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
          value=strtok(NULL,", ");
          column++;

        }
        i++;
        //printf("i1 is %d\n",i);
     }


      // Close the file
      fclose(fp2);
    }
    
   
	FILE* fp3 = fopen("file.csv", "a+");

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
    for(j=0;j<=i;j++)
    {
      //printf("1-->%s\n",phone);
      //printf("2-->%s\n",info[j].phone);
      if ((strcmp(phone,info[j].phone))==0)
      {
        printf("Thank you for shopping with us again\n");
        y=0;
        break;
      }

    }
    if(y!=0)
    {
  	 fprintf(fp3,"\n%s, %s, %d", name,phone,0);
  	 printf("\nNew Account added to record\n");
    }
    fclose(fp3);
    disp_bill(name,phone);
  }

}

void disp_bill(char name[],char phone[])
{
  int i = 0;
  int n;
  SHOP_T arr[50];
  ITEM_T list[100];

  FILE* fp4=fopen("bill.csv","r");
  if(!fp4)
    printf("File cannot be opened\n");
  else
  {
    char buffer[1024];

      int row = 0;
      int column = 0;

      while (fgets(buffer,1024,fp4))
      {
        column = 0;
        row++;
        if(row==1)
          continue;
        // Splitting the data
        char* value = strtok(buffer, ", ");
        while (value)
        {
          // Column 1

          if(column==0)
          {
            int slno=atoi(value);
            arr[i].slno=slno;
          }
          if (column == 1)
          {
            strcpy(arr[i].item_name,value);
            //printf("%s\t",arr[i].item_name);
          }
          if (column == 2)
          {
            int qty=atoi(value);
            arr[i].qty=qty;
            //printf("%d\n",arr[i].qty);

          }

          value=strtok(NULL,", ");
          column++;

        }
        i++;
        //printf("i1 is %d\n",i);
     }

     n=i;
      // Close the file
      fclose(fp4);
  }


  FILE* fp5=fopen("items.csv","r");
  if(!fp5)
    printf("File cannot be opened\n");
  else
  {
    char buffer[1024];

      int row = 0;
      int column = 0;
      i=0;
      while (fgets(buffer,1024,fp4))
      {
        column = 0;
        row++;
        if(row==1)
          continue;
        // Splitting the data
        char* value = strtok(buffer, ", ");
        while (value)
        {
          // Column 1

          if(column==0)
          {
            int slno=atoi(value);
            list[i].slno=slno;
          }
          if (column == 1)
          {
            strcpy(list[i].item,value);
            //printf("%s\t",arr[i].item_name);
          }
          if (column == 2)
          {
            int code=atoi(value);
            list[i].code=code;
            //printf("%d\n",list[i].code);
          }
          if(column == 3)
          {
            int mrp=atoi(value);
            list[i].mrp=mrp;
          }

          value=strtok(NULL,", ");
          column++;

        }
        i++;
        //printf("i1 is %d\n",i);
     }

      // Close the file
      fclose(fp5);
  }
  float total=0,tax;
  FILE* fp6 = fopen("final_bill.csv","w");
  if(!fp6)
    printf("File can't be opened");
  else
  {
    fprintf(fp6,"slno,item_code,item_name,quantity,total price\n");
    for(int j=0;j<n;j++)//arr-item_name,qty,slno
    {
      for(int k=0;k<i;k++)//list-code,mrp,item,slno
      {
        if(strcmp((arr[j].item_name),(list[k].item))==0)
        {
          fprintf(fp6,"%d,%d,%s,%d,%d\n",arr[j].slno,list[k].code,arr[j].item_name,arr[j].qty,((arr[j].qty)*(list[k].mrp)));
          total+=((arr[j].qty)*(list[k].mrp));
        }
      }
    }
    tax=(total*8/100);

  }
  fclose(fp6);
  //displaying

  FILE* fp7=fopen("final_bill.csv","r");

	if (!fp7)
		printf("Can't open file\n");

	else
  {
		// Here we have taken size of
		// array 1024 you can modify it
		char buffer[1024];

		int row = 0;
		int column = 0;

		while (fgets(buffer,1024, fp7))
    {
			column = 0;
			row++;

			// To avoid printing of column
			// names in file can be changed
			// according to need
			if (row == 1)
				continue;

			// Splitting the data
			char* value = strtok(buffer, ", ");

			while (value) {
				// Column 1
				if (column == 0) {
					printf("Sl.No :");
				}

				// Column 2
				if (column == 1) {
					printf("\tItem code :");
				}

				// Column 3
				if (column == 2) {
					printf("\tItem name :");
				}

        if (column == 3) {
					printf("\tQuantity :");
				}

        if (column == 4) {
					printf("\tTotal price :");
				}

				printf("%s", value);
				value = strtok(NULL, ", ");
				column++;
			}

			printf("\n");
		}

		// Close the file
		fclose(fp7);
	}
  
  printf("Total bill without tax is %.2f rupees\n",total);
  printf("Total balance including tax (8 percent of total bill) = %.2f+%.2f = %.2f rupees\n",total,tax,-(total+tax) );
  float amount=(total+tax);
  int check_amount = billing_member(phone,amount);
  if(check_amount == -1)
  {
	payment(name,phone,amount);
  }
  else if(check_amount != 0)
  {
        printf("Final amount after discount = %f\n",check_amount);
	payment(name,phone,check_amount);
  }
  else
  {
	printf("Thank you for shopping\n");
  }
}
