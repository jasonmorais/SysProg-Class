#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
void* reverseString(char* originalString, char* reversedString, int length);
void wordPrint(char*);


int setup_buff(char *buff, char *user_str, int len){
    //TODO: #4:  Implement the setup buff as per the directions
    if (strlen(user_str) > 50){
        return -1;
    }

    char lastString = '\0';
    int outOfBounds = 0;
    for (int i = 0; i <= len; i++) {
        if(user_str[i] == ' ' && lastString != ' '){
            buff[i] = user_str[i];
        }
        else if(user_str[i] == '\0'){
            outOfBounds = 1;
            buff[i] = '.';
        }
        else if(outOfBounds == 1){
            buff[i] = '.';
        }
        else{
            buff[i] = user_str[i];
            lastString = user_str[i];
        }
    }
    return strlen(user_str); 
}

void print_buff(char *buff, int len){
    printf("Buffer: ");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){
    int count = 0;
    for(int i = 0; buff[i] != '\0'; i++){
        if(buff[i] == ' '){
            count += 1;
        }
        if(buff[i+1] == '.'){
            count += 1;
            break;
        }
    }
    return count;
}

void* reverseString(char* originalString, char* reversedString, int length){
    for (int i = 0; originalString[i] != '\0'; i++) {
        reversedString[i] = originalString[length - 1 - i];
    }
    reversedString[length] = '\0';
}

void wordPrint(char* inputString){
    int charCount = 0;
    int currentNumber = 1;
    printf("Word Print\n----------\n1. ");
    for(int i = 0; inputString[i] != '.'; i++){
        if(inputString[i] != ' '){
            printf("%c", inputString[i]);
        }
        if(inputString[i] == ' '){
            currentNumber += 1;
            printf(" (%i)\n", charCount);
            printf("%i. ", currentNumber);
            charCount = 0;
        }
        else if(inputString[i+1] == '.'){
            printf(" (%i)\n", charCount);
            break;
        }
        charCount += 1;
    }
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string
    char* reversedString;

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      It is safe because if arv[1] doesnt exist, it will just be null, since when we allocate
    // storage for an array in c it takes the space but sets the current unused values to null
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //    The purpose is to check if the number of arguments is more than the amount we can handle, ie
    // if the number of arguments is more than 3, we call the usage function which tells the user the correct
    // format of the input, and exits the program.
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    buff = malloc(BUFFER_SZ);
    if (buff == NULL){
        exit(99);
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
        case 'r':
            reversedString = malloc(BUFFER_SZ);
            reverseString(buff, reversedString, user_str_len);
            printf("Reversed String: %s\n", reversedString);
            break;
        case 'w':
            wordPrint(buff);
            break;
        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          Generally speaking it is good to remove the need to perform the length check operation for
//          any kind of more complex data structure like a string / char array in the case that you need
//          to allocate another equal sized array for copying or just checking length for any other procedures
//          Besides this, it also makes it so that in the case that we are using something besides the 50 byte
//          buffer size, so in the case there are multiple buffer sizes for whatever purpose, the function is
//          as dumb as possible. This is a good practice for functions as well, to keep thek as dumb as possible.