#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

int id;
typedef struct general_food{
    int id;
    char food_name[50];
    int food_price,food_weight,food_kcal;
    int food_allergens[50];
}food;
void display_message_administrator();
void administrator_main_menu();
food add_dish(food *f);
int set_id();
void menu_look();
void add_to_menu();
int check_food(char s[]);
void delete_from_menu();
void show_allergens();
void add_to_allergens();
void delete_from_allergens();
void display_message_customer();
void customer_main_menu();
void add_to_order();
void delete_from_order();
void see_order();
void pay_bill();
void set_password();
void check_password();
void menu_manager();
void init();
void display_message_administrator(){
    printf("\n\n0. Change password.\n");
    printf("1. Have a look at the menu.\n");
    printf("2. Add items to the menu.\n");
    printf("3. Delete item from menu.\n");
    printf("4. Have a look at the allergens.\n");
    printf("5. Add item to allergens.\n");
    printf("6. Delete from allergens.\n");
    printf("7. Exit.\n");
    printf("\n\n");

}
void administrator_main_menu(){
    int choice=0;
    display_message_administrator();
    while(choice!=7){
        scanf("%d",&choice);
        switch(choice){
            case 0:
                set_password();
                display_message_administrator();
                break;
            case 1:
                printf("The menu available for today: \n\n");
                menu_look();
                display_message_administrator();
                break;
            case 2:
                printf("What item do you wish to add to your menu?\n");
                add_to_menu();
                display_message_administrator();
                break;
            case 3:
                printf("Enter the food name you wish to delete:\n");
                delete_from_menu();
                display_message_administrator();
                break;
            case 4:
                printf("Allergens list:\n");
                show_allergens();
                display_message_administrator();
                break;
            case 5:
                printf("Enter the allergen you wish to add to the list (e.g. number.allergen ):\n");
                add_to_allergens();
                display_message_administrator();
                break;
            case 6:
                printf("Enter the allergen you wish to delete from the list :\n");
                delete_from_allergens();
                display_message_administrator();

                break;
            case 7:
                printf("Changes saved successfully.\n\n");
                break;
            default:
                printf("\nINVALID SELECTION...Please try again");
                display_message_administrator();
        }
    }
}
food add_dish(food *f){
    char buffer;
    f->id=set_id();
    printf("Enter the food name:\n");
    scanf("%c",&buffer);
    scanf("%[^\n]",&f->food_name);
    printf("Enter the price: \n");
    scanf("%d",&f->food_price);
    printf("Enter the weight (in grams or numbers of objects from that item): \n");
    scanf("%d",&f->food_weight);
    printf("Enter the food kcal: \n");
    scanf("%d",&f->food_kcal);
    printf("Enter the food allergens: \n");
    scanf("%c",&buffer);
    scanf("%[^\n]",&f->food_allergens);
    return *f;
}
int set_id(){
    id++;
    return id;
}
void menu_look(){
    printf("id|food name|food price|food weight|food kcal|food allergens\n");
    FILE* fptr=fopen("data.txt", "r");
    char line[500];
    if(fptr==NULL){ //make sure the file is not empty and handle possible errors.
                printf("Could not open the file.");
    }
    else{
        while(fgets(line,sizeof line,fptr)){
            printf("%s",line);
        }
        fseek(fptr,0,SEEK_SET);
    }
    fclose(fptr);
}
void add_to_menu(){
    food f;
    f =add_dish(&f);
    FILE* fptr=fopen("data.txt", "a");
    if(fptr==NULL){ //make sure the file is not empty and handle possible errors.
                printf("Could not open the file.");
    }
    if(check_food(f.food_name))
        fprintf(fptr,"%d|%s|%d|%d|%d|%s\n",f.id,f.food_name,f.food_price,f.food_weight,f.food_kcal,f.food_allergens);
    else
    printf("Already an option in the menu. Please delete section if you want to modify it.\n\n");
    fclose(fptr);
}
int check_food(char s[]){ //making sure there are no duplicates in the menu.
            s=strlwr(s);
    FILE* fptr=fopen("data.txt", "r");
    char line[500];
    if(fptr==NULL){
        printf("Could not open the file."); //make sure the file is not empty and handle possible errors.
    }
    else{
        while(fgets(line,sizeof line,fptr)){
            if(strstr(line,s))
                return 0;

        }
        fseek(fptr,0,SEEK_SET);
        return 1;
    }
    fclose(fptr);
}
void delete_from_menu(){
    int ok=0; //used to check if the desired item have an entry in the dataset.
    char food_delete[50];
    char buffer;
    scanf("%c",&buffer);
    scanf("%[^\n]",food_delete);
    int len = strlen(food_delete);
    for(int i=0;i<len;i++){
        if(food_delete[i]>='0'&&food_delete[i]<='9'){
            printf("Please enter just the name of the item (e.g. no digits).");
            return;
        }
    }
    FILE* fptr=fopen("data.txt", "r");
    FILE* auxi=fopen("auxi.txt","w+");
    char line[500];
    if(fptr==NULL){ //make sure the file is not empty and handle possible errors.
                printf("Could not open the file.");
    }
    else if(auxi==NULL){ //make sure the file is not empty and handle possible errors.
                printf("Could not open the file auxi.");
    }
    else{
        while(fgets(line,sizeof line,fptr)){
            if(strstr(line,food_delete)!=NULL && ok==0){
                ok=1;
            }
        }

        fseek(fptr,0,SEEK_SET);
        fseek(auxi,0,SEEK_SET);
        while(fgets(line,sizeof line,fptr)){
            if(strstr(line,food_delete)==NULL){
                fprintf(auxi, "%s", line);
            }
        }
        fseek(fptr,0,SEEK_SET);
        fseek(auxi,0,SEEK_SET);
        FILE* fptr2=fopen("data.txt", "w");
        while(fgets(line,sizeof line,auxi)){
            fprintf(fptr2,"%s",line);
        }
        fseek(fptr2,0,SEEK_SET);
        fseek(auxi,0,SEEK_SET);
        fclose(fptr2);
    }
    if(ok==0){
        printf("No such item in the menu.");
    }
    fclose(fptr);
    fclose(auxi);
}
void show_allergens(){
    FILE* fptr=fopen("allergens.txt", "r");
    char line[500];
    if(fptr==NULL){
        printf("Could not open the file."); //make sure the file is not empty and handle possible errors.
    }
    else{
        while(fgets(line,sizeof line,fptr)){
            printf("%s",line);
        }
        fseek(fptr,0,SEEK_SET);
    }
    fclose(fptr);
}
void add_to_allergens(){

    char food_allergen[50];
    char buffer;
    scanf("%c",&buffer);
    scanf("%[^\n]",food_allergen);
    FILE* fptr=fopen("allergens.txt", "a");
    if(fptr==NULL){ //make sure the file is not empty and handle possible errors.
                printf("Could not open the file.");
    }
    else{
        fprintf(fptr,"%s",food_allergen);
        fprintf(fptr,"\n");
    }
    fclose(fptr);
}
void delete_from_allergens(){
    int ok=0;
    char food_delete[50];
    char buffer;
    scanf("%c",&buffer);
    scanf("%[^\n]",food_delete);
    int len = strlen(food_delete);
    for(int i=0;i<len;i++){
        if(food_delete[i]>='0'&&food_delete[i]<='9'){
            printf("Please enter just the name of the allergen. (e.g. no digits)");
            return;
        }
    }
    FILE* fptr=fopen("allergens.txt", "r");
    FILE* auxi=fopen("auxi.txt","w+");
    char line[500];
    if(fptr==NULL){ //make sure the file is not empty and handle possible errors.
                printf("Could not open the file.");
    }
    else if(auxi==NULL){ //make sure the file is not empty and handle possible errors.

                printf("Could not open the file auxi.");
    }
    else{
        while(fgets(line,sizeof line,fptr)){
            if(strstr(line,food_delete)!=NULL && ok==0){
                ok=1;
            }
        }
        fseek(fptr,0,SEEK_SET);
        fseek(auxi,0,SEEK_SET);
        while(fgets(line,sizeof line,fptr)){
            if(strstr(line,food_delete)==NULL){
                fprintf(auxi, "%s", line);
            }
        }
        fseek(fptr,0,SEEK_SET);
        fseek(auxi,0,SEEK_SET);
        FILE* fptr2=fopen("allergens.txt", "w");
        while(fgets(line,sizeof line,auxi)){
            fprintf(fptr2,"%s",line);
        }
        fseek(fptr2,0,SEEK_SET);
        fseek(auxi,0,SEEK_SET);
        if(ok==0){
            printf("No such item in the allergens list.");
        }
    }
}
void display_message_customer(){
    printf("\n\nWelcome to Restaurant 'Plaza Del Aur'. We are thankful for your choice. Please select one action.\n\n");
    printf("\n\n1. Have a look at the menu.\n");
    printf("2. Add to order.\n");
    printf("3. Have a look at the allergens.\n");
    printf("4. Have a look at your order.\n");
    printf("5. Delete item from order.\n");

    printf("6. Pay your bill.\n");
    printf("7. Leave table.\n");
    printf("\n\n");
}
void customer_main_menu(){
    int choice=0;
    display_message_customer();
    while(choice!=7 && choice!=6){
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("The menu available for today: \n\n");
                menu_look();
                display_message_customer();
                break;
            case 2:
                printf("Enter the food name you wish to order:\n");
                add_to_order();
                display_message_customer();
                break;
            case 3:
                printf("Allergens list:\n");
                show_allergens();
                display_message_customer();
                break;
            case 4:
                printf("Your order is:\n\n");
                see_order();
                display_message_customer();
                break;
            case 5:
                printf("Enter the food name you wish to delete from your order:\n");
                delete_from_order();
                display_message_customer();
                break;
            case 6:
                printf("Your total bill is: ");
                pay_bill();
                printf("Have a good day.\n\n");
                break;
            case 7:
                printf("Have a good day.\n\n");
                break;
            default:
                printf("\nINVALID SELECTION...Please try again");
                display_message_customer();

        }
    }
}
void add_to_order(){
    char food_order[50];
    char buffer;
    int ok=0;
    scanf("%c",&buffer);
    scanf("%[^\n]",food_order);
    FILE* fptr=fopen("data.txt", "r");
    FILE* order_pointer=fopen("order.txt","a");
    if(fptr==NULL){
        printf("Could not open the file data.txt .");
    }
    else if(order_pointer==NULL){
        printf("Could not open the file order.txt.");
    }
    else{
        char line[500];
        while(fgets(line,sizeof line,fptr)){
            if(strstr(line,food_order)!=NULL){
                fprintf(order_pointer, "%s", line);
                ok=1;
            }
        }
        if(ok==0)
            printf("The item is not present on the menu, please try again.");
    }
    fclose(fptr);
    fclose(order_pointer);
}
void delete_from_order(){
    int ok=0;
    char food_delete[50];
    char buffer;
    scanf("%c",&buffer);
    scanf("%[^\n]",food_delete);
    int len = strlen(food_delete);

    for(int i=0;i<len;i++){
        if(food_delete[i]>='0'&&food_delete[i]<='9'){
            printf("Please enter just the name of the food. (e.g. no digit) ");
            return;
        }
    }
    FILE* fptr=fopen("order.txt", "r");
    FILE* auxi=fopen("auxi.txt","w+");
    char line[500];
    if(fptr==NULL){
        printf("Could not open the file.");
    }
    else if(auxi==NULL){
        printf("Could not open the file auxi.");
    }
    else{
        while(fgets(line,sizeof line,fptr)){
            if(strstr(line,food_delete)!=NULL && ok==0){
                ok=1;
            }
        }
        fseek(fptr,0,SEEK_SET);
        fseek(auxi,0,SEEK_SET);
        while(fgets(line,sizeof line,fptr)){
            if(strstr(line,food_delete)==NULL){
                fprintf(auxi, "%s", line);
            }
        }
        fseek(fptr,0,SEEK_SET);
        fseek(auxi,0,SEEK_SET);
        FILE* fptr2=fopen("order.txt", "w");
        while(fgets(line,sizeof line,auxi)){
            fprintf(fptr2,"%s",line);
        }
        fseek(fptr2,0,SEEK_SET);
        fseek(auxi,0,SEEK_SET);
        if(ok==0){

            printf("No such item in the order.");
        }
    }
}
void see_order(){
    printf("id|food name|food price|food weight|food kcal|food allergens\n");
    FILE* fptr=fopen("order.txt", "r");
    char line[500];
    if(fptr==NULL){
        printf("Could not open the file.");
    }
    else{
        while(fgets(line,sizeof line,fptr)){
            printf("%s",line);
        }
        fseek(fptr,0,SEEK_SET);
    }
    fclose(fptr);
}
void pay_bill(){
    FILE* fptr=fopen("order.txt", "r");
    int total_sum=0;
    char line[500];
    if(fptr==NULL){
        printf("Could not open the file.");
    }
    else{
        while(fgets(line,sizeof line,fptr)){
            char *ptr=strtok(line,"|");
            ptr=strtok(NULL,"|");
            ptr=strtok(NULL,"|");
            total_sum+=atoi(ptr);
        }
        fseek(fptr,0,SEEK_SET);
    }
    printf("%d ron\n",total_sum);
    fclose(fptr);
}
void set_password(){

    FILE* fptr=fopen("password.txt","w");
    if(fptr==NULL){ //make sure the file is not empty and handle possible errors.
                printf("Could not open the file.");
    }
    char password[50];
    printf("Please set a password:\n");
    scanf("%s",password);
    fprintf(fptr,"%s",password);
    fclose(fptr);
}
void check_password() {
    FILE *fptr = fopen("password.txt", "r");
    if (fptr == NULL) {
        printf("Could not open the file.");
    }
    char temp_password[50];
    char password[50];
    fgets(password, sizeof password, fptr);
    int number_of_tries = 0;
    while (number_of_tries != 3) {
        printf("Please enter the password:\n");
        scanf("%s", temp_password);
        if (strcmp(temp_password, password) != 0){
            printf("\nIncorrect password.\n");
            number_of_tries+=1;
        }
        else {
            printf("Acces granted.\n");
            break;
        }
    }
    if(number_of_tries == 3){
        printf("\nYou enter the incorrect password too many times.");
        exit(0);
    }
    fclose(fptr);
}
void menu_manager()

{
    int choice=0;
    printf("Please select one of the action:\n1.Administrator\n2.Customer\n3.Exit\n");
    while(choice!=3){
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("You enterd administrator mode: \n\n");
                init();
                check_password();
                administrator_main_menu();
                printf("Please select one of the action:\n1.Administrator\n2.Customer\n3.Exit\n");
                break;
            case 2:
                printf("You enterd customer mode: \n\n");
                FILE* fptr=fopen("order.txt","w");
                fclose(fptr);
                customer_main_menu();
                printf("Please select one of the action:\n1.Administrator\n2.Customer\n3.Exit\n");
                break;
            case 3:
                printf("Quitting...");
                break;
            default:
                printf("\nINVALID SELECTION...Please try again\n");
                printf("Please select one of the action:\n1.Administrator\n2.Customer\n3.Exit\n");
        }
    }
}
void init()
{
    FILE* fptr6=fopen("password.txt","r");




    if(fptr6==NULL){ //check if this is the first time when the user uses the program (needed to set a password if it's the first time and initialize all the proper files).
        FILE* fptr=fopen("data.txt", "w");
        fclose(fptr);
        FILE* fptr2=fopen("order.txt", "w");
        fclose(fptr2);

        FILE* fptr3=fopen("allergens.txt", "w");
        fclose(fptr3);
        FILE* fptr4=fopen("auxi.txt", "w");
        fclose(fptr4);
        FILE* fptr5=fopen("password.txt","w");
        fclose(fptr5);
        set_password();
    }
}
int main()
{
    printf("Welcome to Restaurant 'Plaza Del Aur'. We are thankful for your choice. Please select one action.\n\n");
    menu_manager();
}