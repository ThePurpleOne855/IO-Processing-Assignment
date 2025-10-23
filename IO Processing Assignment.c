#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_LENGTH 50

// Function declarations
void loadFromBinary(char words[][MAX_LENGTH], int *wordCount);
void saveToBinary(char words[][MAX_LENGTH], int wordCount);
void addWord(char words[][MAX_LENGTH], int *wordCount);
void exportToTextFile(char words[][MAX_LENGTH], int wordCount);
void dumpAllWords(char words[][MAX_LENGTH], int *wordCount);

int main() {
    char words[MAX_WORDS][MAX_LENGTH];
    int wordCount = 0;
    int choice;
    int running = 1;

    // Load words from binary file if available
    loadFromBinary(words, &wordCount);

    printf("Welcome! Words loaded: %d\n", wordCount);

    while (running) {
        printf("\n===== MENU =====\n");
        printf("1) Add words\n");
        printf("2) Create text file with all words\n");
        printf("3) Dump all words\n");
        printf("4) Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                addWord(words, &wordCount);
                break;
            case 2:
                exportToTextFile(words, wordCount);
                break;
            case 3:
                dumpAllWords(words, &wordCount);
                break;
            case 4:
                saveToBinary(words, wordCount);
                printf("Exiting... All words saved.\n");
                running = 0;
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}

// Load words from binary file
void loadFromBinary(char words[][MAX_LENGTH], int *wordCount) {
    FILE *fp = fopen("data.bin", "rb");
    if (fp == NULL) {
        printf("No existing data found. Starting fresh.\n");
        return;
    }

    fread(wordCount, sizeof(int), 1, fp);
    fread(words, sizeof(char), (*wordCount) * MAX_LENGTH, fp);
    fclose(fp);
}

// Save words to binary file
void saveToBinary(char words[][MAX_LENGTH], int wordCount) {
    FILE *fp = fopen("data.bin", "wb");
    if (fp == NULL) {
        printf("Error saving data.\n");
        return;
    }

    fwrite(&wordCount, sizeof(int), 1, fp);
    fwrite(words, sizeof(char), wordCount * MAX_LENGTH, fp);
    fclose(fp);
}

// Add a word to the array
void addWord(char words[][MAX_LENGTH], int *wordCount) {
    if (*wordCount >= MAX_WORDS) {
        printf("Word limit reached (1000).\n");
        return;
    }

    printf("Enter a word: ");
    scanf("%s", words[*wordCount]);
    (*wordCount)++;
    printf("Word added successfully!\n");
}

// Export all words to a text file
void exportToTextFile(char words[][MAX_LENGTH], int wordCount) {
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        printf("Error creating text file.\n");
        return;
    }

    for (int i = 0; i < wordCount; i++) {
        fprintf(fp, "%s\n", words[i]);
    }

    fclose(fp);
    printf("All words written to output.txt successfully.\n");
}

// Clear all stored words
void dumpAllWords(char words[][MAX_LENGTH], int *wordCount) {
    *wordCount = 0;
    printf("All words deleted from memory.\n");
}
