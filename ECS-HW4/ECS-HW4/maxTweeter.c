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

#define MAX_LINE_LENGTH 1024 // Line size will not exceed 1024 bytes.
#define MAX_ROWS 20000 // 20,000 Lines Max CSV.

typedef struct Tweets tweets;

struct Tweets {
    char* name;
    int numberOfTweets;
    struct Tweets *nextTweet;
};

bool nameIsQuoted = false;
bool nameIsInLastColumn = false;

// MergeSort adapted from: https://www.geeksforgeeks.org/merge-sort-for-linked-list/
struct Tweets* SortedMerge(struct Tweets* a, struct Tweets* b) {
    struct Tweets* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (a->numberOfTweets >= b->numberOfTweets) {
        result = a;
        result->nextTweet = SortedMerge(a->nextTweet, b);
    } else {
        result = b;
        result->nextTweet = SortedMerge(a, b->nextTweet);
    }
    return (result);
}

// Split the nodes of the given list into front and back halves,
// If the length is odd, the extra node should go in the front list.
// Adapted from: https://www.geeksforgeeks.org/merge-sort-for-linked-list/
void FrontBackSplit(struct Tweets* source, struct Tweets** frontRef, struct Tweets** backRef) {
    struct Tweets* fast;
    struct Tweets* slow;
    slow = source;
    fast = source->nextTweet;

    // Advance 'fast' two nodes, and advance 'slow' one node */
    // Move 'fast' ptr twice as fast as 'slow' ptr so once fast ptr is null slow will be a midpoint...
    while (fast != NULL) {
        fast = fast->nextTweet;
        if (fast != NULL) {
            slow = slow->nextTweet;
            fast = fast->nextTweet;
        }
    }
    // Split the list in two.
    *frontRef = source;
    *backRef = slow->nextTweet;
    slow->nextTweet = NULL;
}

void MergeSort(struct Tweets** headRef) {
    struct Tweets* head = *headRef;
    struct Tweets* a;
    struct Tweets* b;

    // Base case.
    if ((head == NULL) || (head->nextTweet == NULL)) {
        return;
    }
    // Split head into 'a' and 'b' sublists
    FrontBackSplit(head, &a, &b);

    // Recursive sort of sublists.
    MergeSort(&a);
    MergeSort(&b);

    // Merge the two sublists.
    *headRef = SortedMerge(a, b);
}

void addTweetToList(struct Tweets **tweets, char *name, int numberOfTweets) {

    struct Tweets *tmp = (struct Tweets*) malloc(sizeof(struct Tweets));
    tmp->name = name;
    tmp->numberOfTweets = numberOfTweets;
    tmp->nextTweet = *tweets;
    *tweets = tmp;
}

// if name exists,  this function will add to number of tweets
bool checkListForName(struct Tweets **tweetList, char *nameCheck) {
    // Keep boolean value for if the name was found or not.
    bool found = false;
    struct Tweets *tweet;
    // Iterate through the LinkedList to find a matching name.
    for(tweet = *tweetList; tweet != NULL; tweet = tweet->nextTweet){
        if(strcmp(tweet->name, nameCheck) == 0) {
            tweet->numberOfTweets = tweet->numberOfTweets + 1;
            found = true;
        }
    }
    return found;
}

void addTweeter(struct Tweets **tweet, char *tweeterName, int numTweets) {
    struct Tweets *tempTweet = (struct Tweets*) malloc(sizeof(struct Tweets));
    tempTweet->name = tweeterName;
    tempTweet->numberOfTweets = numTweets;
    tempTweet->nextTweet = *tweet;
    *tweet = tempTweet;
}

void printLinkedList(struct Tweets **tweets){

    struct Tweets *temp;
    int numLines = 0;
    // only print the top 10 or less tweeters, depending on number of tweeters
    for(temp = *tweets; temp != NULL; temp = temp->nextTweet){
        if(numLines >= 10) {
          break;
        }
        printf("%s: %d\n", temp->name, temp->numberOfTweets);
        numLines++;
    }

}

void removeFirstAndLast(char *targetString) {

    size_t length = strlen(targetString);
    if(length < 2) {
      // then we cannot remove first and last
      printf("Invalid File Format\n");
      exit(-1);
    }

    memmove(targetString, targetString + 1, length - 2);
    targetString[length - 2] = 0;
}

// counts the number of quotes surrounding the string
int numQuotesForString(char* string) {

    int numQuotes = 0;
    int lastCharPosition = (int)strlen(string) - 1;

    if(string[0] == '\"') {
      numQuotes++;
    }

    if(string[lastCharPosition] == '\"') {
      numQuotes++;
    }
    return numQuotes;
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

char* getStringFromPos(char *line, int pos){

    int column = 0;
    char *tmp = strdup(line);
    char *token;
    token = strsep(&tmp, ",");
    if(pos == column){
        return token;
    } else {
        while ((token = strsep(&tmp, ","))) {
            column += 1;
            if (pos == column){
                return token;
            }
        }
    }
    return "NULL";
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
    char possibleName3[10];
    char possibleName4[10];
    char possibleName5[10];
    char possibleName6[10];
    char possibleName7[10];
    char possibleName8[10];

    // Copy valid name columns into char arrays.
    strcpy(possibleName1, "name");
    strcpy(possibleName2, "\"name\"");
    strcpy(possibleName3, "name\n");
    strcpy(possibleName4, "\"name\n\"");
    strcpy(possibleName5, "name\r\n");
    strcpy(possibleName6, "\"name\r\n\"");
    strcpy(possibleName7, "\"name\"\n");
    strcpy(possibleName8, "\"name\"\r\n");


    char *token;
    token = strsep(&headerLine, ",");
    if(strcmp(token, possibleName1) == 0 || strcmp(token, possibleName2) == 0 || strcmp(token, possibleName3) == 0
      || strcmp(token, possibleName4) == 0 || strcmp(token, possibleName5) == 0 || strcmp(token, possibleName6) == 0
      || strcmp(token, possibleName7) == 0 || strcmp(token, possibleName8) == 0){

        // Check if name is quoted. If it is we need to make sure that all the entries are quoted too.
        if((strcmp(token, possibleName2) == 0) || (strcmp(token, possibleName4) == 0)
        || (strcmp(token, possibleName7) == 0 || strcmp(token, possibleName8) == 0)){
            nameIsQuoted = true;
        }

        actualColNum = currentCol;
        count += 1;
    }

    while((token = strsep(&headerLine, ","))){
        currentCol += 1;
        if(strcmp(token, possibleName1) == 0 || strcmp(token, possibleName2) == 0 || strcmp(token, possibleName3) == 0 || strcmp(token, possibleName4) == 0 || strcmp(token, possibleName5) == 0 || strcmp(token, possibleName6) == 0){

            if((strcmp(token, possibleName2) == 0) || (strcmp(token, possibleName4) == 0)){
                nameIsQuoted = true;
            }

            actualColNum = currentCol;
            count += 1;
        }
    }

    if(count > 1){
        //printf("More than one 'name' in header\n");
        printf("Invalid File Format - too many names\n");
        exit(-1);
    } else if (count == 0) {
      //printf("No name header found\n");
      printf("Invalid File Format - no name column\n");
      exit(-1);
    }
    return actualColNum;
}

// Checks if end of string matches desired string.
int endsWith(char *str, char *end) {
    size_t slen = strlen (str);
    size_t elen = strlen (end);
    if (slen < elen)
        return 0;
    return (strcmp (&(str[slen-elen]), end) == 0);
}

bool isValidCSV(char *filename){

    // Check if the file actually ends in .csv
    // and that it does not start with ".csv"
    // i.e., it has at least something in front of the ".csv"
    char *check = strstr(filename, ".csv");
    if(endsWith(filename, ".csv") && (check != filename)) {
        return true;
    } else {
        printf("Invalid File Format\n");
        exit(-1);
    }
    return false;
}

// the main function; handles processing of the csv file
void maxTweeter(const char *filename){

    FILE *file = fopen(filename, "r");
    // unable to open file, or the file does not exist
    if(!file){
        printf("Invalid Input Format\n");
        exit(-1);
    }

    // Move ptr to end of file and check the length using ftell..
    fseek(file, 0, SEEK_END);
    long fileLength = ftell(file);

    //need at least one line in the file, the header line
    if (fileLength == 0){
        printf("Invalid Input Format\n");
        exit(-1);
    }
    // Move ptr back to the beginning of the file.
    fseek(file, 0, SEEK_SET);

    int row_count = 0;
    int column_count = 0;
    int tmp_column_count = 0;
    int namePOS = 0;
    struct Tweets *tweetList = NULL;

    // temp buffer to store line contents.
    char buffer[MAX_LINE_LENGTH];

    while(fgets(buffer, MAX_LINE_LENGTH, file)){
        // Need to check if it is empty csv.
        // Check if first line is null.
        // Check for empty first line ... " ,   ,  ,,,  ,, , ,"
        row_count++;

        if(row_count > MAX_ROWS){
            printf("Invalid Input Format");
            exit(-1);
        }

        // Process the header... check for "name" column.
        if(row_count == 1){
            column_count = getNumberOfColumns(buffer);
            //printf("Column_count = %d\n", column_count);
            // Position of name column.
            namePOS = getNameColNumber(buffer);
            //printf("Name Column Found @ index = %d\n", namePOS);
            if(namePOS == column_count - 1) {
              // the name is in the last column, which means we might have to strip
              // the newline character from it
              nameIsInLastColumn = true;
            }
            continue;
        }
        // if the current line is an empty line, we can just skip over it
        if(strcmp(buffer, "\n") == 0 ) {
          // skip any empty lines
          continue;
        }

        char *name = getStringFromPos(buffer, namePOS);
        // the number of columns that we have found in the current row of the file
        tmp_column_count = getNumberOfColumns(buffer);

        if(tmp_column_count != column_count){
            //printf("Column Count != Header Column Count\n");
            printf("Invalid Input Format\n");
            exit(-1);
        }

        if(nameIsInLastColumn) {
          // then we want to remove any potential newline and retrurn characters inside the name
          char *pos;
          // find the position of the newline character, and replace it with NULL if the newline exists
          if ((pos=strchr(name, '\n')) != NULL) {
            *pos = '\0';
          }
          if ((pos=strchr(name, '\r')) != NULL) {
            *pos = '\0';
          }
        }

        if(nameIsQuoted) {
          if(numQuotesForString(name) == 2) {
            // have the proper number of quotes
            removeFirstAndLast(name); // remove both quotes if we have both
          } else {
            // we have 0 or 1 quotes when expecting 2
            //printf("Error: Quote Mismatch\n");
            printf("Invalid Input Format\n");
            exit(-1);
          }
        } else {
          // the name column has no quotes
          if(numQuotesForString(name) != 0) {
            // but we have some quotes even though we are expecting none
            //printf("Error: Quote Mismatch\n");
            printf("Invalid Input Format\n");
            exit(-1);
          }
        }

        // If the name is not in the list then add it.
        // if checkListForName finds the tweeter within the list, then the function
        // will add 1 to the number of tweets
        // if the tweeter is not found, then we will create a new list entry
        if(!checkListForName(&tweetList, name)){
            addTweeter(&tweetList, name, 1);
        }
    } // fgets()

    // run the sort on the list, then print the top 10 (or less) tweeters, in order
    MergeSort(&tweetList);
    printLinkedList(&tweetList);

    // close the file:
    fclose(file);
    return;
} // maxTweeter

int main(int argc, char *argv[]){
    // If argc != 2 that means there is either less than 1 argument or more (an invalid number of arguments given)
   if(argc != 2){
       printf("Invalid Input Format\n");
       return -1;
   }
   // argv[1] is where we expect to find the filename.
   // check if it is a valid csv file, and then run maxTweeter
   if(isValidCSV(argv[1])){
        maxTweeter(argv[1]);
   }
    return 0;
}
