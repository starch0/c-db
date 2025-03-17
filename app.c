#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define DB_FILE "db.dat"

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
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

int main() {
    Database db;
    int choice;

    initDatabase(&db, 5);
    loadFromFile(&db);

    do {
        printf("\n1. Add user\n");
        printf("2. List users\n");
        printf("3. Update user\n");
        printf("4. Delete user\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
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
    } while (choice != 5);

    freeDatabase(&db);
    return 0;
}

void initDatabase(Database *db, int capacity) {
    db->users = (User *)malloc(capacity * sizeof(User));
    db->size = 0;
    db->capacity = capacity;
}

void addUser(Database *db) {
    if (db->size == db->capacity) {
        db->capacity *= 2;
        User *temp = (User *)realloc(db->users, db->capacity * sizeof(User));
        if (!temp) {
            printf("Memory allocation failed!\n");
            return;
        }
        db->users = temp;
    }

    User newUser;
    newUser.id = db->size + 1;

    printf("Enter name: ");
    scanf("%49s", newUser.name);
    printf("Enter age: ");
    scanf("%d", &newUser.age);

    db->users[db->size] = newUser;
    db->size++;
    printf("User added successfully. ID: %d\n", newUser.id);
}

void listUsers(Database *db) {
    if (db->size == 0) {
        printf("No users in the database.\n");
        return;
    }

    printf("\n%-5s %-20s %s\n", "ID", "Name", "Age");
    for (int i = 0; i < db->size; i++) {
        printf("%-5d %-20s %d\n", 
               db->users[i].id, 
               db->users[i].name, 
               db->users[i].age);
    }
}

void updateUser(Database *db) {
    int id;
    printf("Enter user ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < db->size; i++) {
        if (db->users[i].id == id) {
            printf("Enter new name: ");
            scanf("%49s", db->users[i].name);
            printf("Enter new age: ");
            scanf("%d", &db->users[i].age);
            printf("User updated successfully.\n");
            return;
        }
    }
    printf("User with ID %d not found.\n", id);
}

void deleteUser(Database *db) {
    int id;
    printf("Enter user ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < db->size; i++) {
        if (db->users[i].id == id) {
            for (int j = i; j < db->size - 1; j++) {
                db->users[j] = db->users[j + 1];
            }
            db->size--;
            printf("User deleted successfully.\n");
            return;
        }
    }
    printf("User with ID %d not found.\n", id);
}

void saveToFile(Database *db) {
    FILE *file = fopen(DB_FILE, "wb");
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    fwrite(&db->size, sizeof(int), 1, file);

    for (int i = 0; i < db->size; i++) {
        fwrite(&db->users[i], sizeof(User), 1, file);
    }

    fclose(file);
    printf("Database saved to file.\n");
}

void loadFromFile(Database *db) {
    FILE *file = fopen(DB_FILE, "rb");
    if (!file) {
        printf("No existing database found.\n");
        return;
    }

    int size;
    fread(&size, sizeof(int), 1, file);

    if (size > db->capacity) {
        db->capacity = size;
        User *temp = (User *)realloc(db->users, db->capacity * sizeof(User));
        if (!temp) {
            printf("Memory allocation failed!\n");
            fclose(file);
            return;
        }
        db->users = temp;
    }

    db->size = size;
    for (int i = 0; i < size; i++) {
        fread(&db->users[i], sizeof(User), 1, file);
    }

    fclose(file);
    printf("Database loaded from file.\n");
}

void freeDatabase(Database *db) {
    free(db->users);
    db->users = NULL;
    db->size = 0;
    db->capacity = 0;
}