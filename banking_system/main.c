#include <stdio.h>
#include <stdlib.h>
struct bank_acc
{
    int acc_no;
    char name[100];
    int balance;
};

void acc_creation()
{
    system("CLS");
    struct bank_acc user;
    int accnum=1;
    FILE *bank;
    bank=fopen("bank_sys.bin","r+b");
    fseek(bank,0,SEEK_END);
    if(ftell(bank)==0)
    {
        user.acc_no=accnum;
    }
    else
    {
        fseek(bank,-1*sizeof(struct bank_acc),SEEK_END);
        fread(&user,sizeof(struct bank_acc),1,bank);
        user.acc_no++;
        fseek(bank,0,SEEK_END);
    }
    printf("\nEnter your name:");
    scanf("%s",user.name);
    user.balance=0;
    fwrite(&user,sizeof(struct bank_acc),1,bank);
    printf("\nAccount number:%d",user.acc_no);
    printf("\n Account created successfully");
    fclose(bank);

}

void deposit()
{
    system("CLS");
    struct bank_acc user;
    FILE *bank ;
    bank = fopen("bank_sys.bin","rb+");
    int accnum,temp=0;
    printf("\nEnter the account number:");
    scanf("%d",&accnum);
    int flag = 0;
    while(fread(&user,sizeof(struct bank_acc),1,bank))
    {
        if(user.acc_no==accnum)
        {
            printf("\nEnter the amount to be deposited:");
            scanf("%d",&temp);
            user.balance = user.balance + temp;
            flag = 1;
            break;
        }
    }
    if(flag == 0)
    {
        printf("\nInvalid Account Number");
    }
    else
    {
            fseek(bank,-1*sizeof(struct bank_acc),SEEK_CUR);
            fwrite(&user,sizeof(struct bank_acc),1,bank);
            printf("\nAmount Deposited");
    }
    fclose(bank);
}


void withdraw()
{
    system("CLS");
    struct bank_acc user;
    FILE *bank ;
    bank = fopen("bank_sys.bin","rb+");
    int accnum,temp=0;
    printf("\nEnter the account number:");
    scanf("%d",&accnum);
    int flag = 0;
    while(fread(&user,sizeof(struct bank_acc),1,bank))
    {
        if(user.acc_no==accnum)
        {
            flag =1;
            printf("\nEnter the amount to be withdraw:");
            scanf("%d",&temp);
            if(user.balance>=temp)
            {
                user.balance = user.balance - temp;
                break;
            }
            else
            {
                printf("\nBalance Insufficient");
                flag == 2;
                break;
            }
        }
    }
    if(flag == 0)
    {
        printf("\nInvalid Account Number");
    }
    if(flag == 1 )
    {
        fseek(bank,-1*sizeof(struct bank_acc),SEEK_CUR);
        fwrite(&user,sizeof(struct bank_acc),1,bank);
        printf("\nAmount Detected");
    }
    fclose(bank);
}

void transfer()
{
    system("CLS");
    struct bank_acc user;
    FILE *bank ;
    bank = fopen("bank_sys.bin","r+b");
    int flag = 0,accnum1,accnum2,temp;
    printf("\nEnter your account number :");
    scanf("%d",&accnum1);
    printf("\nEnter your 2nd party account number :");
    scanf("%d",&accnum2);
    while(fread(&user,sizeof(struct bank_acc),1,bank))
    {
        if(user.acc_no==accnum1 || user.acc_no == accnum2)
        {
            flag++;
        }
    }
    if(flag==2)
    {
        flag =0;
        fseek(bank,0,SEEK_SET);
        while(fread(&user,sizeof(struct bank_acc),1,bank))
        {
            if(user.acc_no==accnum1)
            {
                printf("\nEnter the amount to be transferred:");
                scanf("%d",&temp);
                if(user.balance>temp)
                {
                    user.balance = user.balance - temp;
                    break;
                }
                else
                {
                    printf("\nBalance Insufficient");
                    flag =1;
                }
            }
        }
        if(flag == 0)
        {
            fseek(bank,-1*sizeof(struct bank_acc),SEEK_CUR);
            fwrite(&user,sizeof(struct bank_acc),1,bank);
            fseek(bank,0,SEEK_SET);
            while(fread(&user,sizeof(struct bank_acc),1,bank))
            {
                if(user.acc_no==accnum2)
                {
                    user.balance = user.balance + temp;
                    fseek(bank,-1*sizeof(struct bank_acc),SEEK_CUR);
                    fwrite(&user,sizeof(struct bank_acc),1,bank);
                    printf("\nAmount Transferred");
                    break;
                }
            }
        }
    }
    else
    {
        printf("\nInvalid account number entered");

    }
    fclose(bank);

}

void acc_details()
{
    system("CLS");
    struct bank_acc user;
    FILE *bank ;
    int accnum,flag =0;
    bank = fopen("bank_sys.bin","rb+");
    printf("\nEnter the account number: \n");
    scanf("%d",&accnum);
    while(fread(&user,sizeof(struct bank_acc),1,bank))
    {
        if(accnum == user.acc_no)
        {
            printf("\nAccount holder name:%s",user.name);
            printf("\nBalance:%d",user.balance);
            flag = 1;
        }
    }
    if(flag == 0)
    {
        printf("\nInvalid account number");
    }
    fclose(bank);
}

void acc_close()
{
    struct bank_acc olduser,newuser;
    system("CLS");
    FILE *bank,*temp;
    int accnum,flag=0;
    bank=fopen("bank_sys.bin","rb+");
    temp=fopen("temp.bin","ab+");
    printf("\nEnter Account number:");
    scanf("%d",&accnum);
    while(fread(&olduser,sizeof(struct bank_acc),1,bank))
    {
        if(olduser.acc_no==accnum)
        {
            flag=1;
            continue;
        }
        else
        {
         newuser = olduser;
         fwrite(&newuser,sizeof(struct bank_acc),1,temp);
        }
    }
    if(flag==0)
    {
        printf("\nAccount Unavailable");
    }
    else
    {
        printf("Account Deleted");
    }
    fclose(bank);
    fclose(temp);
    remove("bank_sys.bin");
    rename("temp.bin","bank_sys.bin");

}

int main()
{
    FILE *bank ;
    bank = fopen("bank_sys.bin","ab+");
    fclose(bank);
    int ch,cont;
    do
    {
        printf("1.Open an account \n");
        printf("2.Deposit money \n");
        printf("3.Withdraw money \n");
        printf("4.Transfer money \n");
        printf("5.Amount Details \n");
        printf("6.Close an account \n");
        printf("\nEnter the choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:acc_creation();
            break;
            case 2:deposit();
            break;
            case 3:withdraw();
            break;
            case 4:transfer();
            break;
            case 5:acc_details();
            break;
            case 6:acc_close();
            break;
            default:printf("\n Invalid choice:");
        }
        printf("\nPress 1 to continue:");
        scanf("%d",&cont);

    }while(cont == 1);

}

