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
#include <stdlib.h>
#include <stdbool.h>

// Include '\n' but exclude '\0'
#define MAX_LINE_LENGTH 1024 // Line size will not exceed 1024 bytes.
#define MAX_ROWS 20000 // 20,000 Lines Max CSV.

typedef struct Tweets tweets;

struct Tweets{
    
    char* name;
    int numberOfTweets;
    struct Tweets *nextTweet;
    
};

void addTweetToList(struct Tweets **tweets, char *name, int numberOfTweets){
    
    struct Tweets *tmp = (struct Tweets*) malloc(sizeof(struct Tweets));
    tmp->name = name;
    tmp->numberOfTweets = numberOfTweets;
    tmp->nextTweet = *tweets;
    *tweets = tmp;
}

bool checkListForName(struct Tweets **tweetList, char *nameCheck){
    // Keep boolean value for if the name was found or not.
    bool found = false;
    struct Tweets *tweet;
    // Iterate through the LinkedList to find a matching name.
    for(tweet = *tweetList; tweet != NULL; tweet = tweet->nextTweet){
        if(strcmp(tweet->name, nameCheck) == 0){
            tweet->numberOfTweets = tweet->numberOfTweets + 1;
            found = true;
        }
    }
    return found;
}

typedef struct Tweeter tweeter;

struct Tweeter {
   char  *Name;
   int   numberOfTweets;
   struct Tweeter *nextTweeter;
};


void addTweeter(struct Tweeter **tweet, char *tweeterName, int numTweets){
    struct Tweeter *tempTweet = (struct Tweeter*) malloc(sizeof(struct Tweeter));
    tempTweet->Name = tweeterName;
    tempTweet->numberOfTweets = numTweets;
    tempTweet->nextTweeter = *tweet;
    *tweet = tempTweet;
}


void removeFirstAndLast(char *targetString){
    
    size_t length = strlen(targetString);
    //assert(length >= 2); // Need to make sure the string is not of length 2.
    memmove(targetString, targetString + 1, length - 2);
    targetString[length - 2] = 0;
    
    
}

// Checks Entries and Headers for valid quotes.
char* removeOutermostQuotes(char* string){
    
    int lastCharPosition = strlen(string) - 1;
    
    printf("First character = %c, Last Character = %c\n", string[0],string[lastCharPosition]);
    return "hello";
    
}


// Return invalid file if there is more than one empty file header.
int getEmptyColumnCount(char *headerline){
    
    return 0;
}

// Gets number of columns from splitting the csv...
// This must be called during every line read to check if the # of columns is the same for all lines.
int getNumberOfColumns(char* line){
    
    int count = 0;
    char buffer[1024];
    
    strcpy(buffer, line);
    
    char *tmp = strdup(buffer);
    char *token;
    
    while((token = strsep(&tmp, ","))){
        count+=1;
    }
    
    return count;
}

// Return column number of the "name" or ""name"" column.
// Also check if there are other "name" or ""name"" columns...making file invalid.
int getNameColNumber(char *headerLine){
    
    // Need to keep track of a 'count' variable just in case there are multiple 'name' fields...
    int count = 0;
    int actualColNum = 0;
    int currentCol = 0;
    // On piazza TA said that maximum size of name could by whole line?
    char possibleName1[10];
    char possibleName2[10];
    
    // Copy valid name columns into char arrays.
    strcpy(possibleName1, "name");
    strcpy(possibleName2, "\"name\"");
    
    char *token;
    token = strsep(&headerLine, ",");
    if(strcmp(token, possibleName1) == 0 || strcmp(token, possibleName2) == 0){
        actualColNum = 0;
        count += 1;
    }
    
    while((token = strsep(&headerLine, ","))){
        currentCol += 1;
        if(strcmp(token, possibleName1) == 0 || strcmp(token, possibleName2) == 0){
            actualColNum = currentCol;
            count += 1;
        }
    }
    
    if(count != 1){
        printf("Invalid File Format\n");
        return -1;
    }

    return actualColNum;
}

// Checks if end of string matches desired string.
int endsWith (char *str, char *end) {
    size_t slen = strlen (str);
    size_t elen = strlen (end);
    if (slen < elen)
        return 0;
    return (strcmp (&(str[slen-elen]), end) == 0);
}

bool isValidCSV(char *filename){
    
    // Check if the file actually ends in .csv.
    if(endsWith(filename, ".csv")){
        printf("Valid File Extension\n");
        return true;
    }else{
        printf("Invalid File Format\n");
        exit(-1);
    }
    return false;
}

void maxTweeter(const char *filename){
    
    FILE *file = fopen(filename, "r");
    
    if(!file){
        perror("Invalid Input Format\n");
    }
    
    int row_count = 0;
    int column_count = 0;
    int namePOS = 0;
    char *columnNames[1024];
    
    // Array to store all csv information.
//    char csvToArray[MAX_ROWS][MAX_LINE_LENGTH];
    // temp buffer to store line contents.
    char buffer[MAX_LINE_LENGTH];
    
    
    while(fgets(buffer, MAX_LINE_LENGTH, file)){
        
        // Need to check if it is empty csv.
        // Check if first line is null.
        // Check for empty first line ... " ,   ,  ,,,  ,, , ,"
        
        char *tmp = strdup(buffer);
        
        row_count++;
        
        // Process the header... check for "name" column.
        if(row_count == 1){
            
            column_count = getNumberOfColumns(buffer);
            printf("Column_count = %d\n", column_count);
            
            namePOS = getNameColNumber(buffer);
            printf("Name Column Found @ index = %d\n", namePOS);
            
            // Gets pointer to first element.
            columnNames[0] = strsep(&tmp, ",");
            column_count++;
            
            // Gets every comma seperated header.
            char *token;
            int i = 0;
            while((token = strsep(&tmp, ","))){
                i+=1;
                column_count+=1;
                printf("Iteration : %d Value: %s\n", i, token);
                columnNames[i] = token;
                
                printf("ColumnName Value = %s\n", columnNames[i]);
            }
            
            continue;
            
        }
        
    } // fgets()
    
} // maxTweeter



// Just a single quote as a name is invalid ,", or ,',

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
    
    char filename[] = "/Users/celestinosilva/Downloads/test-tweets.csv";
//    maxTweeter(filename);
    
    isValidCSV(filename);
    char targetString[] = "\"Hello\"";
    
    removeFirstAndLast(targetString);
    printf(targetString);
    
    return 0;
    
}
