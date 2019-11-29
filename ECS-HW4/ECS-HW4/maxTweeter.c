//
//  maxTweeter.c
//  ECS-HW4
//
//  Created by Luke Silva on 11/27/19.
//  Copyright © 2019 Luke Silva. All rights reserved.
//


#include "maxTweeter.h"
#include <stdio.h>
#include <string.h>


#define MAX_LINE_LENGTH 1024 // Line size will not exceed 1024 bytes.
#define MAX_ROWS 20000 // 20,000 Lines Max CSV.

// Checks Entries and Headers for valid quotes.
char* removeOutermostQuotes(char* string){
    
    int lastCharPosition = strlen(string) - 1;
    
    printf("First character = %c, Last Character = %c\n", string[0],string[lastCharPosition]);
    
    
    
    return "hello";
    
}

int getNumberOfColumns(char* line){
    
    int count = 0;
    char buffer[1024];
    
    strcpy(buffer, line);
    
    char *word;
    
    for(word = strtok(buffer, "'"); word && *word; word = strtok(NULL, ",\n"), count+=1 ){
        // nothing
    }
    return count;
}

// Return column number of the "name" or ""name"" column.
// Also check if there are other "name" or ""name"" columns...making file invalid.
int getNameColNumber(char *headerLine){
    
    int colNum;
    int count = 0;
    // On piazza TA said that maximum size of name could by whole line?
    char possibleName1[1024];
    char possibleName2[1024];
    
    // Copy valid name columns into char arrays.
    strcpy(possibleName1, "name");
    strcpy(possibleName2, "\"name\"");
    
    const char* tok;
    
    for (colNum = 0, tok = strtok(headerLine, ",");tok && *tok;tok = strtok(NULL, ",\n"), colNum += 1){
        // Increment count for possible matches...
        if (strcmp(tok, possibleName1) == 0 || strcmp(tok, possibleName2) == 0){
            count += 1;
        }
    }
    
    if(count != 1){
        printf("Invalid File Format");
        return -1;
    }

    return colNum;
}

void maxTweeter(const char *filename){

    FILE *file = fopen(filename, "r");
    if(!file){
        printf("Invalid Input Format");
    }
    
    
    int row_count = 0;
    int column_count = 0;
    char *columnNames[1024];
    
    // Array to store all csv information.
    char csvToArray[MAX_ROWS][MAX_LINE_LENGTH];
    // temp buffer to store line contents.
    char buffer[MAX_LINE_LENGTH];
    
    
    while(fgets(buffer, MAX_LINE_LENGTH, file)){
        
        // Need to check if it is empty csv.
        // Check if first line is null.
        // Check for empty first line ... " ,   ,  ,,,  ,, , ,"
        
        row_count++;
        
        // Process the header... check for "name" column.
        if(row_count == 1){
            
            // Gets pointer to first element.
            columnNames[0] = strtok(buffer, ",");
            column_count++;
            
            // Check if first value == "name"
            
            
            // Gets every comma seperated header.
            int i = 0;
            while(columnNames[i] != NULL){
                i++;
                column_count++;
                columnNames[i] = strtok(NULL, ",");
            }
            
            
            
            // Printing header items
            for (int j=0; j<=i-1; j++) {
                printf("%s\n", columnNames[j]);
            }
            
            continue;
            
        }
    }
    
    
}

int main(int argc, char *argv[]){
    
    // If argc != 2 that means there is either less than 1 argument or more.
    // Commented out to test with direct path.
    
    
//    if(argc != 2){
//
//        printf("Invalid Input Format\n");
//        return -1;
//
//    }
//    char* fileName = argv[2];
    
//    maxTweeter("/Users/LukeSilva/Downloads/cl-tweets-short-clean.csv");
    
    char* string = "YOUNGMONEYMILITIA";
    
    checkForQuotes(string);
    
    
    return 0;
    
}
