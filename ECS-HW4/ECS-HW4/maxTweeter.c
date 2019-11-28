//
//  maxTweeter.c
//  ECS-HW4
//
//  Created by Luke Silva on 11/27/19.
//  Copyright © 2019 Luke Silva. All rights reserved.
//


#include "maxTweeter.h"
#include <stdio.h>

#define NUMBER_OF_RESULTS 10
#define MAX_LINE_LENGTH 1024

struct topTenTweeters{
    
    char topTen[10][1024];
    
};

struct topTenTweeters maxTweeter(const char *filename){
    
    struct topTenTweeters tweeterArray;

    FILE *file = fopen(filename, "r");
    if(!file){
        printf("Invalid Input Format");
    }
    
    char buffer[MAX_LINE_LENGTH];
    int row_count = 0;
    int column_count = 0;
    char *columnNames[1024];
    
    while(fgets(buffer, MAX_LINE_LENGTH, file)){
        
        // Need to check if it is empty csv.
        // Check if first line is null.
        // Check for empty first line ... " ,   ,  ,,,  ,, , ,"
        
        row_count++;
        
        // Process the header... check for "name" column.
        if(row_count == 1){
            
            columnNames[0] = strtok(buffer, ",");
            
            int i = 0;
            
            while(columnNames[i] != NULL){
                
                
                
            }
        
            continue;
            
        }
        
        
        
        
        
    }
    
    
    
    return tweeterArray;
    
}

int main(int argc, char *argv[]){
    
    if(argc != 2){
        
        printf("Invalid Input Format\n");
        return -1;
        
    }
    char* fileName = argv[2];
    
//    maxTweeter(fileName);
    
    
    
    return 0;
    
}
