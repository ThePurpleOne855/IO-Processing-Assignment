#include <stdio.h>

int main(){
    FILE *fptr; // A pointer of type File for the file
    int selection; // Used on Switch for the cases
    char text[1000]; // The test is going to be input into this variable them send to the file from this variable
    int on = 1; // Used on our while loop to keep it alive

    do {
        printf("1) Add words to the program.\n");
        printf("2) Dump all words from the program.\n");
        printf("3) Exit.\n");

        scanf("%d", &selection);

        switch(selection){
            case 1:
                fptr = fopen("file.txt", "a");
                printf("Type what you want to write to the new file:\n");
                scanf(" %[^\n]", text); // reads until a newline is found
                fprintf(fptr, "%s\n", text);
                fclose(fptr);
                break;

            case 2:
                if(fptr != NULL){  // close file if open
                    fclose(fptr);
                    fptr = NULL;
                }
                if(remove("file.txt") == 0){
                    printf("Successfully Deleted\n");
                } else{
                    printf("Error Deleting.\n");
                }
                break;

            case 3:
                on = 0;
                break;

            default:
                printf("Invalid option.\n");
        }
    } while(on == 1);

    return 0;
}
