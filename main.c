/*BANK MANGEMENT SYSTEM*/

/*LIMITATIONS*/
//1.You Can't Enter Your Name with spaces Ex.:veesam yugandhar(wrong);;VeesamYugandhar(correct)
//2.The Bank Can Hold Only 10,000 accounts
//3.your password should not start with digit 0 and alphabets

#include <stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>//to get the use rand function
#include<time.h>//to use rand function with respect to time
#include<ctype.h>//to use isdigit function
int n,deposite_amount=0,withdraw_amount=0,balance=0,i=0;
char customer_name[50],father_name[50],dob[12],sel[10];

/*thank you message*/
void thanku()
{
    printf("\n\t\t\t\t***THANK YOU***\n");
}

/*refering file for getting last stored data*/
void refer_file(char *z,int *c,int *l)
{
    char a[100],b[20];
    int d;
    //Open the file and get the data of last line and store it in a string
    FILE *fp;
    fp=fopen(z,"a+");//opening file in append+read mode
    fseek(fp,-100, SEEK_END);//setting the file pointer position to End position using SEEK_END and moving back to 100th character from last
    while(!(feof(fp)))//while file pointer not equal to end get the data from file and store it in variable a
    {
        fgets(a,100,fp);
    }
    fclose(fp);
    d=strlen(a);
    //convert the string into an integer array 
   int i=0,j=0,num[40]={0,1,2,3,4,5,6,7,8,9};
   int k=0,n=0,m=0,x,count;
   *l=0;
   while(a[i]!='\0')
   {
       x=0;n=0;
       for(j=i;a[j]!='\0';j++)
       {
           count=0;
           for(k=0;k<10;k++)
           {
               if(a[j]-48==num[k])
               {
                  count=1;
                  break;
               }
           }
           if(count==1)
           {
               b[j-i]=a[j];
           }
           else
           {
               x=1;
               break;
           }
       }
       i=j+1;
       
       if((a[i]!=32)&&(a[i]!=9)&&(a[i]!=10))//ascii 32=white space,9=tab space,10=new line
       {
             for(j=0;b[j]!='\0';j++)
        	{
	               if((b[j]==9)||(b[j]==32)||(b[j]==10))
	                 {
	                    b[j]=00;
	                    break;
	                  }
      	     }
      	     
              for(j=0;b[j]!='\0';j++){
                  n+=(b[j]-48)*pow(10,strlen(b)-j-1);
                 m++;
              }
              
              for(j=0;j<m;j++){b[j]=00;}
              c[*l]=n;
              (*l)++;
       }
   }
   for(j=0;j<100;j++){a[j]=00;}
}

/*generating last 4 digits of account number*/
int fun_random()
{
    //generate a random no. between 1000 and 9999 using rand function 
    int lw=1000,up=9999,n,i=0;
    srand(time(NULL));//srand is used to update the random no. after everytime excution
    n=(rand()%(up-lw+1)+lw);//rand()%n gives a random no. in the range(0,n) 
 
    int c[100],l,k=0;
    char z[20]="Database186.txt";//giving the name of the database
    refer_file(z,c,&l);//get the account no.s existing previously
    for(i=0;i<l;i++){
    if(n==c[i])//check whether present random is existed previously or not
        fun_random();//if it exists again generate a new random number
    else
    {
        k++;//if not return the present random no.
    }}
    if(k==i){return n;}    
    
}

/*password setting*/
int ps_set(int psw)
{
    char a[6];
    printf("Enter a 5 digit password:");
    scanf("%s",a);
    int count=0,i;
    for(i=0;a[i]!='\0';i++){
        if(isdigit(a[i]))//check is every character is digit or not
           count++;
    }
    if(strlen(a)==count && strlen(a)==5 && a[0]!='0'){
        for(i=0;a[i]!='\0';i++){
            psw+=(a[i]-48)*pow(10,strlen(a)-i-1);//convert the string into integer
        }
        return psw;
    }
    else{
        printf("incorrect format!!!\n");
        printf("Try Again!\n");
        ps_set(0);
    }
}


/*creating a new account*/
void create_account( )
{
    printf("\nTo Create A New Account, You Need To Deposite A Minimum Amount Of RS.1000/-\n");
    printf("\nIf You Want To Create Account, press 1.If not, press any number to exit\n");
    scanf("%s",sel);
    if(sel[0]=='1' && sel[1]=='\0')
    {
        printf("ENTER AMOUNT TO BE DEPOSITED:");
        scanf("%d",&deposite_amount);
        if(deposite_amount>=1000)
        {
            printf("ENTER YOUR NAME:");
            scanf("%s",customer_name);// DRAW BACK IS, DOESN'T ACCEPT SPACES IN NAMES.USE '_' INSTEAD OF SPACES..
            
            printf("ENTER YOUR FATHER/MOTHER/WIFE/HUSBAND NAME:");
            scanf("%s",father_name);
            
            printf("ENTER YOUR DATE OF BIRTH AS DD/MM/YYYY :");
            scanf("%s",dob);
            
            balance=deposite_amount;
            //generating account number
            int p,i=0;
            p=fun_random();//getting the last 4 digits
            FILE *fp;
            fp=fopen("Database186.txt","a");//upload the present opening account no. into database
            fprintf(fp," %d",p);
            fclose(fp);
    
            char c[5],x[20]={'3','7','0','1','0'},y[5]=".txt",z[20];
            sprintf(c,"%d",p);//convert the integer into a string 
            strcat(x,c);//append the random no. to the bank code  
            strcpy(z,x);//keep a copy of account no. with you
            strcat(x,y);//add the .txt extension to account no.; To open a file with account no.
            //Opening a file with account number
            fp=fopen(x,"w");//Add the data into file
            fprintf(fp,"\n\t\t\t\t\t\t\t\t\t***YUGANDHAR BANK OF INDIA***\n\n");
            fprintf(fp,"ACCOUNT NO. :%s\n",z);
            fprintf(fp,"CUSTOMER NAME:Mr./Mrs: %s\n",customer_name);
            fprintf(fp,"S/D/W/H/O NAME : %s\n",father_name);
            fprintf(fp,"D.O.B:%s\n",dob);
            fprintf(fp,"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tBranch Manger\n");
            fprintf(fp,"\n\n=================================================================================================================================================\n\n");
            fprintf(fp,"\n\nS.NO\t\t\tDEPOSITE\t\tWITHDRAWL\t\t\tBALANCE\n");
            fprintf(fp,"1   \t\t\t %d \t\t\t %d \t\t\t\t\t %d\n",deposite_amount,withdraw_amount,balance);
            fclose(fp);
            int psw;
            psw=ps_set(0);
            fp=fopen("Database186.txt","a");
            fprintf(fp," %d",psw);
            fclose(fp);
            printf("ACCOUNT CREATED SUCCESSFULLY.....\n");
            printf("Your Account Number is :%s\n",z);
        }
        else
        {
            printf("YOUR ACCOUNT CAN'T OPEN, AS YOUR DEPOSITED AMOUNT IS LESSTHAN RS.1000/-\n");
        }
        thanku();
    }
    else
    {
        thanku();
    }
}

/*password verification*/
int psw_verification(int ac_no)
{
   char z[20]="Database186.txt";
   int c[1000],l,i,count=0,psw;
   printf("Enter your 5 digit password:");
   scanf("%d",&psw);
   refer_file(z,c,&l);//check whether password present in database or not
   for(i=0;i<l;i++){
       if((c[i]==ac_no)&&(c[i+1]==psw)){
           count=1;
           break;
       }
   }
   if(count==1){
       return 1;
   }
   else{
       return 0;
   }
}

/*to check whether account no. present or not*/
int ac_num_check(char *ac)
{
    
    int i=0,nu=0,c[1000],l,cou=0;
    for(i=(strlen(ac)-4);ac[i]!='\0';i++)//get the last 4 characters from account no.
    {
        nu+=(ac[i]-48)*pow(10,strlen(ac)-i-1);//convert the characters into no.s
    }
    int code_check=0;
    for(i=0;i<5;i++){
        code_check+=(ac[i]-48)*pow(10,4-i);//to check the bank code is 37010 or not checking
    }
    char z[20]="Database186.txt";
    refer_file(z,c,&l);
    for(i=0;i<l;i++){
        if(nu==c[i])//check whether account number is present in database or not
        {
           cou=1;break;}
    }
    if((cou==1)&&(code_check==37010)){
       int psReceive;
       psReceive=psw_verification(nu);//check the password
       if(psReceive==1)
            return 2;
       else
            return 1;
    }
    else 
       return 0;
}

/*To Deposite Amount*/
void depo_amount()
{
    int c[4],l,ac_check;
    char account_number[20],y1[5]=".txt";
    printf("Please Enter Your Account Number:");
    scanf("%s",account_number);
    ac_check=ac_num_check(account_number);//get the confirmation from database
    if(ac_check==2){
    strcat(account_number,y1);
    refer_file(account_number,c,&l);
    deposite_amount=c[1];//get the previous deposited ammount
    withdraw_amount=0;//keep the withdraw amount to zero as we are depositing only 
    balance=c[3];//get the previous balance
    printf("ENTER AMOUNT TO BE DEPOSITED:");
    scanf("%d",&deposite_amount);
    balance+=deposite_amount;//update the balance by adding with deposited amount
    
    FILE *fp;//upload the data into record
    fp=fopen(account_number,"a");
    fprintf(fp,"%d   \t\t\t %d \t\t\t %d \t\t\t\t\t %d\n",c[0]+1,deposite_amount,withdraw_amount,balance);
    fclose(fp);
    printf("SUCCESSFULLY DEPOSITED...");}
    else if(ac_check==1){printf("Please check your password!!!");}
    else{printf("Please Enter valid account number..\n");}
    thanku();
}
/*To Withdraw Amount*/
void wdraw_amount()
{
    int c[4],l,ac_check;
    char account_number[20],y1[5]=".txt";
    printf("Please Enter Your Account Number:");
    scanf("%s",account_number);
    ac_check=ac_num_check(account_number);//get the confirmation from database whether account number exists or not
    if(ac_check==2){
    strcat(account_number,y1);//add the extension
    refer_file(account_number,c,&l);
    deposite_amount=0;//keep the deposite amount to zero as we are withdrawing
    balance=c[3];//get the previous balance
    printf("ENTER AMOUNT TO BE WITHDRAWN:");
    scanf("%d",&withdraw_amount);
    if(balance>=withdraw_amount)
    {
        balance-=withdraw_amount;//update the balance by subtracting withdraw_amount
        FILE *fp;//upload the data into file
        fp=fopen(account_number,"a");
        fprintf(fp,"%d   \t\t\t %d  \t\t\t %d \t\t\t     %d\n",c[0]+1,deposite_amount,withdraw_amount,balance);
        fclose(fp);
        printf("SUCCESSFULLY  WITHDRAWN....\n");
        printf("Your Remaining Balance is:%d",balance);
    }
    else
    {
        printf("INSUFFICIENT BALACENCE....");
    }
    }
    else if(ac_check==1){printf("Please check your password!!!");}
    else
       printf("Please Enter valid account number..\n");
    thanku();
}
/*to know the balance*/
void balance_enquiry()
{
    int c[40],l,ac_check;
    char account_number[20],y1[5]=".txt";
    printf("Please Enter Your Account Number:");
    scanf("%s",account_number);
    ac_check=ac_num_check(account_number);//get the confirmation from database
    if(ac_check==2){
    strcat(account_number,y1);
    refer_file(account_number,c,&l);//get the data from file 
    printf("Your Current Balance is:%d",c[3]);
    }
    else if(ac_check==1){printf("Please check your password!!!");}
    else
       printf("Please Enter valid account number..\n");
    thanku();
}

/*main function*/
int main()
{
    printf("\n\t\t\t***WELCOME TO YUGANDHAR BANK OF INDIA***\n\n");
    printf("choose...\n1----->TO CREATE A NEW ACCOUNT\n2---->TO DEPOSITE AMOUNT\n3----->TO WITHDRAW AMOUNT\n4---->TO CHECK CURRENT BALANCE\n5---->TO EXIT\n");
    scanf("%d",&n);
    switch(n)
    {
        case 1:create_account();
                 break;
        case 2:depo_amount();
                break;
        case 3:wdraw_amount();
                break;
        case 4:balance_enquiry();
                break;
        case 5:thanku();
                return 0;
        default : printf("YOUR CHOICE IS WRONG...");
                  thanku();
    }
    
    return 0;
}
