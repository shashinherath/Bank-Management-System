#include <stdio.h>
#include <string.h>
#include <windows.h>

//global variable for account number
int account_global;

//function declaration
int main();
void create();
void login();
void account();
void deposit();
void withdraw();
void update();
void account_details();
void delete();
void color_code();

//Define colors
#define  LIGHTWHITE 15
#define LIGHTGREEN 10
#define LIGHTRED 12
#define LIGHTBLUE 9


struct details {
    char branch[50];
    char name[100];
    int acc_number;
    int pin;
    char id[20];
    char address[100];
    float balance;
};

void color_code(int color){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void create(){
    struct details user;

    FILE *details_file;
    details_file = fopen("details.txt","a"); // Create or open file and append details

    color_code(LIGHTBLUE);
    printf("************ CREATE NEW ACCOUNT ***********\n\n");

    color_code(LIGHTWHITE);
    printf("\n>>> Branch\t: ");
    scanf("%s", &user.branch);

    printf("\n>>> Username\t: ");
    scanf("%s", &user.name);

    printf("\n>>> Account No\t: ");
    scanf("%d", &user.acc_number);

    printf("\n>>> Pin\t\t: ");
    scanf("%d", &user.pin);

    printf("\n>>> ID No\t: ");
    scanf("%s", &user.id);

    printf("\n>>> Address\t: ");
    scanf("%s", &user.address);

    printf("\n>>> Deposit(LKR): ");
    scanf("%f", &user.balance);

    fwrite(&user, sizeof(user), 1, details_file); // Write data into a file.
    fclose(details_file);

    color_code(LIGHTGREEN);
    printf("\nAccount Created Successfully!\n\n\n");
    main();
}

void login(){
    char user_name[20];
    int user_pin;
    int tryagain = 1;
    FILE *details_file;
    struct details user;
    int logged = 0;

    color_code(LIGHTBLUE);
    printf("           ******* LOGIN *******           \n");

    start_login:
    details_file = fopen("details.txt", "r");
    if (details_file == NULL) {
        create();
    } else {
        color_code(LIGHTWHITE);
        printf("\n>>> Username\t: ");
        scanf("%s", &user_name);
        printf("\n>>> Pin\t\t: ");
        scanf("%d", &user_pin);
        color_code(LIGHTWHITE);
        while (fread(&user, sizeof(user), 1, details_file)) {
            if (!strcmp(user.name, user_name)) {
                if (user.pin == user_pin) {
                    account_global = user.acc_number;
                    fclose(details_file);
                    logged = 1;
                    color_code(LIGHTGREEN);
                    printf("\nAccount Logged In Successfully!\n");
                    account();
                }
            }
        }
        
        if (logged == 0 && tryagain < 3) {
            color_code(LIGHTRED);
            printf("\n\aInavalid Account number or Pin!\n");
            tryagain++;
            goto start_login;
        }
    }

    if (logged == 0) {
        color_code(LIGHTRED);
        printf("\n\aAccount is not found\n\n");
        main();
    }
}

void account(){
    
    int selection_2;
    color_code(LIGHTBLUE);
    printf("\n\n===========================================\n");
    printf("                  ACCOUNT                  \n");
    printf("===========================================\n\n");


    color_code(LIGHTWHITE);
    printf("\n[1] Cash Deposit\n");
    printf("\n[2] Cash Withdraw\n");
    printf("\n[3] Account Details\n");
    printf("\n[4] Update Account\n");
    printf("\n[5] Delete Account\n");
    printf("\n[6] Log out\n\n");

    select2:
    color_code(LIGHTWHITE);
    printf("Choose Option: ");
    scanf("%d", &selection_2);
    printf("\n===========================================\n\n");


    switch (selection_2){

    case 1:
        deposit();
        break;

    case 2:
        withdraw();
        break;
    
    case 3:
        account_details();
        break;

    case 4:
        update();
        break;

    case 5:
        delete();
        break;

    case 6:
        color_code(LIGHTGREEN);
        printf("Account Logged Out Successfully!\n\n\n");
        main();
        break;

    default:
        color_code(LIGHTRED);
        printf("\aWrong Selection!\n\n");

        goto select2;
        break;
    }
}

void deposit(){
    float amount;
    FILE *details_file;
    FILE *transaction_file;
    struct details user;

    color_code(LIGHTBLUE);
    printf("           ******* DEPOSIT *******           \n\n");
    
    color_code(LIGHTWHITE);
    printf(">>> Amount(LKR)\t: ");
    scanf("%f", &amount);

    transaction_file = fopen("transaction.txt","w");
    details_file = fopen("details.txt","r");
    while (fread(&user, sizeof(user), 1, details_file)) {
        if (account_global == user.acc_number) {

            user.balance = user.balance + amount;
            color_code(LIGHTGREEN);
            printf("\nDeposit Successfully!\n");
            color_code(LIGHTWHITE);
            printf("\nYour current balance is (LKR) %.2f\n", user.balance);
        }
        fwrite(&user, sizeof(user), 1, transaction_file);
    }
    fclose(transaction_file);
    fclose(details_file);

    details_file = fopen("details.txt", "w");
    transaction_file = fopen("transaction.txt", "r");

    while (fread(&user, sizeof(user), 1, transaction_file)) {
        fwrite(&user, sizeof(user), 1, details_file);
    }
    
    fclose(details_file);
    fclose(transaction_file);

    account();

}

void withdraw(){
    float amount;
    FILE *details_file;
    FILE *transaction_file;
    struct details user;
    color_code(LIGHTBLUE);
    printf("           ******* WITHDRAW *******           \n\n");

    color_code(LIGHTWHITE);
    printf(">>> Amount(LKR)\t: ");
    scanf("%f", &amount);

    transaction_file = fopen("transaction.txt","w");
    details_file = fopen("details.txt","r");
    while (fread(&user, sizeof(user), 1, details_file)) {
        if (account_global == user.acc_number) {

            user.balance = user.balance - amount;
            color_code(LIGHTGREEN);
            printf("\nWithdrawal Successfully!\n");
            color_code(LIGHTWHITE);
            printf("\nYour current balance is (LKR) %.2f\n", user.balance);
        }
        fwrite(&user, sizeof(user), 1, transaction_file);
    }
    fclose(transaction_file);
    fclose(details_file);

    details_file = fopen("details.txt", "w");
    transaction_file = fopen("transaction.txt", "r");

    while (fread(&user, sizeof(user), 1, transaction_file)) {
        fwrite(&user, sizeof(user), 1, details_file);
    }
    
    fclose(details_file);
    fclose(transaction_file);

    account();
}

void account_details(){
    struct details user;
    FILE *details_file;
    color_code(LIGHTBLUE);
    printf("       ******* ACCOUNT DETAILS *******       \n\n");

    details_file = fopen("details.txt", "r");

    color_code(LIGHTWHITE);
    while(fread(&user, sizeof(user), 1, details_file)){
        if (account_global == user.acc_number){
            printf("Branch\t\t: %s\n", user.branch);
            printf("\nUsername\t: %s\n", user.name);
            printf("\nAccount No\t: %d\n", user.acc_number);
            printf("\nID No\t\t: %s\n", user.id);
            printf("\nAddress\t\t: %s\n", user.address);
            printf("\nBalance(LKR)\t: %.2f\n", user.balance);
        }
        
    }

    fclose(details_file);

    account();
}

void update(){
    struct details user;
    FILE *details_file, *transaction_file;
    color_code(LIGHTBLUE);
    printf("       ******** ACCOUNT UPDATE *******       \n\n");

    transaction_file = fopen("transaction.txt","w");
    details_file = fopen("details.txt","r");
    while (fread(&user, sizeof(user), 1, details_file)) {
        if (account_global == user.acc_number) {
            color_code(LIGHTWHITE);
            printf(">>> Branch\t: ");
            scanf("%s", &user.branch);
            printf("\n>>> Username\t: ");
            scanf("%s", &user.name);
            printf("\n>>> Pin\t\t: ");
            scanf("%d", &user.pin);
            printf("\n>>> ID No\t: ");
            scanf("%s", &user.id);
            printf("\n>>> Address\t: ");
            scanf("%s", &user.address);
        }
        fwrite(&user, sizeof(user), 1, transaction_file);
    }
    fclose(transaction_file);
    fclose(details_file);

    details_file = fopen("details.txt", "w");
    transaction_file = fopen("transaction.txt", "r");

    while (fread(&user, sizeof(user), 1, transaction_file)) {
        fwrite(&user, sizeof(user), 1, details_file);
    }
    
    fclose(details_file);
    fclose(transaction_file);

    color_code(LIGHTGREEN);
    printf("\nAccount Updated Successfully!\n");
    account();

}

void delete(){
    struct details user;
    FILE *details_file, *transaction_file;
    int account_del;
    int check = 0;
    color_code(LIGHTBLUE);
    printf("       ******* DELETE ACCOUNT *******       \n\n");
    color_code(LIGHTWHITE);
    printf(">>> Enter Account No: ");
    scanf("%d", &account_del);


    transaction_file = fopen("transaction.txt","w");
    details_file = fopen("details.txt","r");
    while (fread(&user, sizeof(user), 1, details_file)) {
        if (account_del == user.acc_number) {
           
            color_code(LIGHTGREEN);
            printf("\nAccount Deleted Successfully!\n\n\n");
            check = 1;
        }
        else{
            fwrite(&user, sizeof(user), 1, transaction_file);
        }
            
    }
    fclose(transaction_file);
    fclose(details_file);

    transaction_file = fopen("transaction.txt", "r");
    details_file = fopen("details.txt", "w");

    while (fread(&user, sizeof(user), 1, transaction_file)) {
        fwrite(&user, sizeof(user), 1, details_file);
    }
    
    fclose(details_file);
    fclose(transaction_file);

    if (check == 1){
        main();
    }
    else{
        color_code(LIGHTRED);
        printf("\n\aAccount Number is invalid!\n");
        account();
    }
    


}

int main(){
    //color_code(LIGHTGRN);
    int selection;
    color_code(LIGHTBLUE);
    printf("===========================================\n");
    printf("          BANK MANAGEMENT SYSTEM           \n");
    printf("===========================================\n\n\n");
    color_code(LIGHTWHITE);
    printf("[1] Create New Account\n\n");
    printf("[2] Login\n\n");

    start:
    color_code(LIGHTWHITE);
    printf("Choose Option [1] or [2]: ");
    scanf("%d", &selection);
    printf("\n===========================================\n\n\n");
     

    switch (selection) {

    case 1:
        create();
        break;

    case 2:
        login();
        break;
    
    default:
        color_code(LIGHTRED);    
        printf("\aWrong selection!\n\n");
        goto start;
        break;
    }

    return 0;
}