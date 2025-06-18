#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// sign up or sign in
// cake designing
// designed cake
// numbers of cake designs

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 6
#define FILENAME "users.txt"

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN + 1];
}User;

void signUp() {
    User user;
    FILE *file = fopen(FILENAME, "a");
    if(file == NULL) {
        perror("No file exist");
        return;
    }

    printf("Sign up\n");
    printf("Enter user name: \n");
    scanf("%49s", user.username);
    getchar();

    do{
     printf("Enter 6 digit password: \n");
     scanf("%6s", user.password);
     getchar();
    } while (strlen(user.password) != 6);

    fprintf(file, "%s %s\n", user.username, user.password);
    fclose(file);
    printf("Signed up successfully!\n");
}

int signIn() {
    User user;
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN + 1];
    int found = 0;

    printf("log in\n");
    printf("Enter your user name: ");
    scanf("%49s", username);
    getchar();
    printf("Enter your 6 digit password: ");
    scanf("%6s", password);
    getchar();

    FILE *file = fopen(FILENAME, "r");
    if(file == NULL) {
        perror("No file exist");
        return found;
    }

    while (fscanf(file, "%49s  %6s", user.username, user.password) == 2) {
        if(strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (found) {
        printf("Sign in successful!\n");
    }
    else {
        printf("Invalid username or password\n");
    }
    return found;
}
#define MAX_CAKES 100
#define MAX_FLAVOR_LEN 50
#define MAX_DEC_LEN 50
#define MAX_SIZE 10

typedef struct {
    char size[MAX_SIZE];
    char flavor[MAX_FLAVOR_LEN];
    char decor[MAX_DEC_LEN];
}Cake;

void desCake(Cake *cake) {
    printf("Customizing your cake\n");

   printf("Choose a flavor (Chocolate, Vanilla, Red Velvet): ");
   if(scanf("%49[^\n]",cake->flavor) != 1) {
    printf("Error reading flavor.\n");
    return;
   }
   getchar();// reads a string with spaces

   printf("choose a size (small, Medium, Large): ");
   if(scanf("%9[^\n]",cake->size) != 1) {
    printf("Error in reading size.\n");
    return;
   }
   getchar();

   printf("\nChoose a decor (Sprinkles, fruits, Choco Chips): ");
   if(scanf("%49[^\n]",cake->decor)!= 1) {
    printf("Error in reading decor.\n");
    return;
   }
   getchar();

   printf("\nYour cake has been designed!\n");
}

void disCake(const Cake *cake) {
    printf("\t\t--Your customized cakes--\t\t\n");
    printf("Flavor: %s\n",cake->flavor);
    printf("Size: %s\n",cake->size);
    printf("Decor: %s\n",cake->decor);
}

int main() {
    int choice, ch;
    Cake myCakes[MAX_CAKES];
    int cakeCount = 0;

    do {
        printf("1. sign up\n");
        printf("2. Sign in\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            signUp();
            break;
        case 2:
            if (signIn()) {
               do {
                printf("1. customise your cake\n");
                printf("2. Display cake\n");
                printf("3. number of cake you have customise\n");
                printf("4. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &ch);
                getchar();

                switch(ch) {
                    case 1:
                        if(cakeCount < MAX_CAKES) {
                            desCake(&myCakes[cakeCount]);
                            cakeCount++;
                        }
                        else{
                            printf("\nLimit is over!!");
                        }
                        break;
                    case 2:
                        if (cakeCount > 0) {
                            for (int i = 0; i < cakeCount; i++) {
                                printf("\nCake %d: ",i+1);
                                disCake(&myCakes[i]);
                            }
                        }
                            else{
                                printf("\nNo cake is customized!!");
                            }
                            break;
                    case 3:
                        printf("\nYou have designed %d cakes\n", cakeCount);
                        break;
                    case 4:
                        exit(0);
                    default:
                        printf("Invalid input\n");
                }
                }while(ch != 4);

            }
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    }while(choice!=3);


    return 0;
}
