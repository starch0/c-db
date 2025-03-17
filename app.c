#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGHT 50
#define DB_FILE "db.dat"

typedef struct {
    int id;
    char name[MAX_NAME_LENGHT];
    int age;

} User;

typedef struct {
    User *users;
    int size;
    int capacity;

} Database;

void initDatabase(Database *db, int capacity);
void addUser(Database *db);
void listUsers(Database *db);
void updateUser(Database *db);
void deleteUser(Database *db);
void saveToFile(Database *db);
void loadFromFile(Database *db);
void freeDatabase(Database *db);

int main(){
    Database db;
    int choice;

    initDatabase(&db, 5);
    loadFromFile(&db);

    do{
        printf("1. Add user\n");
        printf("2. List users\n");
        printf("3. Update user\n");
        printf("4. Delete user\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
    
        switch(choice){
            case 1:
                addUser(&db);
                break;
            case 2:
                listUsers(&db);
                break;
            case 3:
                updateUser(&db);
                break;
            case 4:
                deleteUser(&db);
                break;
            case 5:
                saveToFile(&db);
                break;
            default:
                printf("Invalid choice\n");
        }
    
    }while(choice != 5);
    freeDatabase(&db);
    return 0;
}

void initDatabase(Database *db, int capacity){
    db->users = (User *)malloc(capacity * sizeof(User));
    db->size = 0;
    db->capacity = capacity;
}

void addUser(Database *db){
    if(db->size == db->capacity){
        db->capacity *= 2;
        db->users = (User *)realloc(db->users, db->capacity * sizeof(User));

    }

    User newUser;
    printf("Enter id: ");
    newUser.id - db->size + 1;

    printf("new user: \n");
    scanf("%49s", newUser.name);

    db->users[db->size] = newUser;
    db->size++;
}

void listUsers(Database *db){
    for(int i = 0; i < db->size; i++){
        printf("id: %d, name: %s\n", db->users[i].id, db->users[i].name);
    }
}

void updateUser(Database *db){
    int id;
    printf("Enter id: ");
    scanf("%d", &id);

    for (int i = 0; i < db->size; i++){
        if (db->users[i].id == id){
            printf("New name: ");
            scanf("%49s", db->users[i].name);
            return;
        }
    }
}

