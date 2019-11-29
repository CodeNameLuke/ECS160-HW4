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
#define NUMBER_OF_RESULTS 10

struct topTenTweeters{
    
    char topTen[10][1024];
    
};

struct topTenTweeters maxTweeter(const char *filename){
    
    struct topTenTweeters tweeterArray;

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
    
    return tweeterArray;
    
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
    
    maxTweeter("/Users/LukeSilva/Downloads/cl-tweets-short-clean.csv");
    
    return 0;
    
}
