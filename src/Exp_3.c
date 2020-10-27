#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct File{
    char fileName[15];
    struct File * nextFile;
};

struct Folder{
    char folderName[15];
    struct File * firstFile;
    struct Folder * firstFolder;
    struct Folder * nextFolder;
    struct Folder * parentFolder;
};

struct Folder rootSingle = {"Single-level", NULL, NULL, NULL, NULL};
struct Folder rootDouble = {"Double-level", NULL, NULL, NULL, NULL};
struct Folder rootMultiple = {"Hierarchial", NULL, NULL, NULL, NULL};

void addFileHandle(struct Folder *);
void addFile(struct Folder **, char *);
void addFolder(struct Folder *, char *);
void showAll(struct Folder *);
void showAllUsers(struct Folder *);
void deleteFileHandle(struct Folder *);
void deleteFolderHandle(struct Folder *);
struct File * checkIfFileExists(struct Folder *, char *);
struct Folder * checkIfFolderExists(struct Folder *, char *);

void getIntoSingleLevel(struct Folder *);
void getIntoDoubleLevel();
void getIntoMultiLevel(struct Folder *);


void main(){
    int choice;

    while(1){
        printf("\n\nMain Menu\n");
        printf("==========");

        printf("\nEnter Choice:     1. Single-level     2. Double-level      3. Hierarchical    4.Exit: ");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                printf("\n\nSingle-level Directory\n");
                printf("============================");
                
                getIntoSingleLevel(&rootSingle);
                break;
                
            case 2:
                printf("\n\nDouble-level Directory\n");
                printf("============================");

                getIntoDoubleLevel();
                break;

            case 3:
                printf("\n\nMulti-level Directory\n");
                printf("============================");

                getIntoMultiLevel(&rootMultiple);
                break;

            case 4:
                printf("\nEXITING");
                exit(0);

            default:
                break;
        }
    }
}

void getIntoSingleLevel(struct Folder * root){
    int choice;

    while(1){
        printf("\nEnter Choice:     1. Add File     2. Delete File      3. Show All Files       4. Main Menu : ");
        scanf("%d", &choice);
        switch (choice){
        case 1:
            addFileHandle(root);
            break;
        
        case 2:
            deleteFileHandle(root);
            break;

        case 3:
            showAll(root);
            break;

        case 4:
            return ;
            break;
            
        default:
            break;
        }
    }
}

void getIntoDoubleLevel(){
    int choice;
    char userName[15];
    struct Folder * result;

    while(1){
        printf("\nEnter Choice:     1. Create User      2. Choose User      3. Delete User      4. Show All Users   4. Main Menu : ");
        scanf("%d", &choice);
        switch (choice){
        case 1:
            printf("Enter User Name: ");
            scanf("%s", userName);
            if(checkIfFolderExists(&rootDouble, userName) == 0){
                printf("USER ADDED");
                addFolder(&rootDouble, userName);
            }else{
                printf("USER ALREADY EXISTS");
            }
            break;
        
        case 2:
            printf("Enter User Name: ");
            scanf("%s", userName);
            result = checkIfFolderExists(&rootDouble, userName);
            if(result == 0){
                printf("\n USER DOES NOT EXIST");
            }else{
                printf("\n\n%s", result->folderName);
                printf("\n=============");
                getIntoSingleLevel(result);
            }
            
            break;

        case 3:


        case 4:
            showAllUsers(&rootDouble);
            break;

        case 5:
            return ;
            break;
            
        default:
            break;
        }
        printf("\n");
    }
}

void getIntoMultiLevel(struct Folder * directory){
    int choice;
    char folderName[15];
    char fileName[15];
    struct Folder * result;

    while(1){
        printf("\nEnter Choice:     1. Create Folder    2. Create File      3. Choose Directory     4. Go Up    5. Show all \n\t\t  6. Delete File      7. Delete Folder    8. Main Menu    \t\t\t\t  : ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice){
        case 1:
            printf("Enter Folder Name: ");
            scanf("%s", folderName);
            if(checkIfFolderExists(directory, folderName) == 0){
                printf("FOLDER ADDED");
                addFolder(directory, folderName);
            }else{
                printf("FOLDER ALREADY EXISTS");
            }
            break;

        case 2: 
            addFileHandle(directory);
            break;

        case 3:
            printf("Enter Folder Name: ");
            scanf("%s", folderName);
            result = checkIfFolderExists(directory, folderName);
            if(result == 0){
                printf("\n FOLDER DOES NOT EXIST");
            }else{
                system("cls");
                printf("\n\n%s", result->folderName);
                printf("\n=============");
                getIntoMultiLevel(result);
            }
            
            break;

        case 4:
            if(directory->parentFolder == NULL){
                printf("REACHED TOP");
                break;
            }
            system("cls");
            printf("\n\n%s", directory->parentFolder);
            printf("\n=============");
            getIntoMultiLevel(directory->parentFolder);
            break;
        case 5:
            showAll(directory);
            break;

        case 6:
            deleteFileHandle(directory);
            break;
        
        case 7:
            deleteFolderHandle(directory);
            break;
        
        case 8:
            return ;
            break;
            
        default:
            break;
        }
        printf("\n");
    }
}

void addFileHandle(struct Folder * directory){
    char fileName[15];
    
    printf("Enter File Name: ");
    scanf("%s", fileName);
    
    if(checkIfFileExists(directory, fileName) == 0){
        addFile(&directory, fileName);
    }else{
        printf("\nFILE ALREADY EXISTS\n");
    }
}

void addFile(struct Folder ** directory, char * fileName){
    
    struct File * newFile = (struct File *) malloc(sizeof(struct File));
    for(int i = 0; i< 15; i++){
        newFile->fileName[i] = fileName[i];
    }
    newFile->nextFile = NULL;
    if((*directory)->firstFile == NULL){
        (*directory)->firstFile = newFile;
        return ;
    }
    
    struct File * traverse = (*directory)->firstFile;
    while(traverse->nextFile != NULL){
        traverse = traverse->nextFile;
    }

    traverse->nextFile = newFile;
}

void addFolder(struct Folder * directory, char * folderName){

    struct Folder * newFolder = (struct Folder *) malloc(sizeof(struct Folder));
    newFolder->nextFolder = NULL;
    newFolder->firstFile = NULL;
    newFolder->firstFolder = NULL;
    newFolder->parentFolder = directory;
    strcpy(newFolder->folderName, folderName);

    if(directory->firstFolder == NULL){
        directory->firstFolder = newFolder;
        return ;
    }

    struct Folder * traverse = directory->firstFolder;
    while(traverse->nextFolder != NULL){
        traverse = traverse->nextFolder;
    }
    traverse->nextFolder = newFolder;
}

void showAll(struct Folder * directory){
    if(directory->firstFile == NULL && directory->firstFolder == NULL){
        printf("EMPTY DIRECTORY\n");
        return ;
    }

    if(directory->firstFile != NULL){
        printf("\n FILES:");
        struct File * fileTraverse = directory->firstFile;
        do{
            printf("\n\t%s", fileTraverse->fileName);
            fileTraverse = fileTraverse->nextFile;
        }while(fileTraverse != NULL);
    }
    
    if(directory->firstFolder != NULL){
        struct Folder * folderTraverse = directory->firstFolder;
        printf("\n FOLDERS:");
        do{
            printf("\n\t%s", folderTraverse->folderName);
            folderTraverse = folderTraverse->nextFolder;
        }while(folderTraverse != NULL);
    }
}

void showAllUsers(struct Folder * directory){
    
    if(directory->firstFolder == NULL){
        printf("EMPTY DIRECTORY\n");
        return ;
    }

    printf("USERS: ");
    struct Folder * traverse = directory->firstFolder;

    do{
        printf("\n\t%s", traverse->folderName);
        traverse = traverse->nextFolder;
    }while(traverse != NULL);
}

void deleteFileHandle(struct Folder * directory){
    char fileName[15];

    printf("Enter File Name: ");
    scanf("%s", fileName);
    struct File * result = checkIfFileExists(directory, fileName);

    if(result == 0){
        printf("\nFILE DOES NOT EXIST");
    }else{
        struct File * traverse = directory->firstFile;

        if(traverse == result){
            printf("\nDELETED");
            directory->firstFile = traverse->nextFile;
            return ;
        }
        do{
            if(traverse->nextFile == result){
                traverse->nextFile = result->nextFile;
                printf("\nDELETED");
                return ;
            }
            traverse = traverse->nextFile;
        }while(traverse != NULL);

        printf("Error in DELETING");
    }
}

void deleteFolderHandle(struct Folder * directory){
    char folderName[15];

    printf("Enter Folder Name: ");
    scanf("%s", folderName);
    struct Folder * result = checkIfFolderExists(directory, folderName);

    if(result == 0){
        printf("\nFOLDER DOES NOT EXIST");
    }else{
        struct Folder * traverse = directory->firstFolder;

        if(traverse == result){
            printf("\nDELETED");
            directory->firstFolder = traverse->nextFolder;
            return ;
        }
        do{
            if(traverse->nextFolder == result){
                traverse->nextFolder = result->nextFolder;
                printf("\nDELETED");
                return ;
            }
            traverse = traverse->nextFolder;
        }while(traverse != NULL);

        printf("Error in DELETING");
    }
}

struct File * checkIfFileExists(struct Folder * directory, char * fileName){
    
    if(directory->firstFile == NULL){
        return 0;
    }
    struct File * traverse = directory->firstFile;
    do{
        if(strcmp(traverse->fileName, fileName) == 0){
            return traverse;
        }
        traverse = traverse->nextFile;
    }while(traverse != NULL);
    return 0;
}

struct Folder * checkIfFolderExists(struct Folder * directory, char * folderName){
    if(directory->firstFolder == NULL){
        return 0;
    }

    struct Folder * traverse = directory->firstFolder;

    do{
        if(strcmp(folderName, traverse->folderName) == 0){
            return traverse;
        }
        traverse = traverse->nextFolder;
    }while(traverse != NULL);

    return 0;
}