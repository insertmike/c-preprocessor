/*
 * Author: 40342250
 * Purpose: Coursework Project 1
 * Language: C
*/
#include <stdlib.h>
#include <stdio.h>
#define bufSize 1024


// Function counting the number of Non-Empty Lines in a file 
void nonEmptyLines(const char* input);
//Function counting the number of comments in a file
void countComments(const char* input);
/* 
 * Function producing an outputfile, which is a copy of the input file but 
 * with preprocessed headers
*/
void replaceHeaders(const char* input, const char* output);
// Function removing the comments from an input file
void removeComments(const char* input);
// Function which is used to preprocess the define directives in a file
void replaceDefines(const char* input);
//Function which removes the new line character from a given string 
void remove_newline(char *str);

int main(int argc, char **argv) {
  

  if (argc == 4) {
	// Array of characters which will hold the input file name
	char inputFile[256]="";
	// A flag used in the while loop for finding file name
	int flag = 1;
	// A counter storing the argument index
	int counter = 0;
	
    // Loop until file name found
    while(flag) {
	  // If argument equals '-i' next argument is filename
      if (strcmp(argv[counter], "-i") == 0) {
		// Copy next argument to inputFile variable 
        strcpy(inputFile, argv[counter + 1]);
        flag = 0;
      }
	  // Securing against corrupted input from the user 
	  if(flag >= 4)
		{
			printf("Incorrect input.\n");
			printf("Exiting...");
			flag = 0;
			exit(0);
		}
		counter++;
    }

    char outputFile[256]; 
    char temp[256] = "";
    strcpy(temp, inputFile);
    // Tokenizing the input name to get rid of the .c part
    strcpy(outputFile, strtok(temp, "."));
    // Concatenating the tokenized input with the .o extension
    strcat(outputFile, ".o");
	printf("-----------------------------------------\n");
	printf("Input file: %s\n",inputFile);
	printf("Output file: %s\n",outputFile);
    // Running functions
	
	  // Count how many non-empty lines 
      nonEmptyLines(inputFile);
	  // Count how many comments 
      countComments(inputFile);
	  // Preprocess the inputFile headers to the outputFile
      replaceHeaders(inputFile, outputFile);
	  // Preprocess the define directives in the inputFile to the Output one 
      replaceDefines(outputFile);
  }

  else if (argc == 3) {
	// Array of characters which will hold the input file name
	char inputFile[256]="";
	// A flag used in the while loop for finding file name
	int flag = 1;
	// A counter storing the argument index
	int counter = 0;
	// Loop until file name found
    while(flag) {
	  // If argument equals '-i' next argument is filename
      if (strcmp(argv[counter], "-i") == 0) {
	    // Copy next argument to inputFile variable 
        strcpy(inputFile, argv[counter + 1]);
        flag = 0;
      }
	  // Securing against corrupted input from the user 
	  if(flag >= 4)
		{
			printf("Error message");
			flag = 0;
			exit(0);
		}
		counter++;
    }

    char outputFile[256]; 
    char temp[256] = "";
    strcpy(temp, inputFile);
    // Tokenizing the input name to get rid of the .c part
    strcpy(outputFile, strtok(temp, "."));
    // Concatenating the tokenized input with the .o extension
    strcat(outputFile, ".o");
	printf("-----------------------------------------\n");
	printf("Input file: %s\n",inputFile);
	printf("Output file: %s\n",outputFile);
    // Running functions
	
	  // Count how many non-empty lines 
      nonEmptyLines(inputFile);
	  // Count how many comments 
      countComments(inputFile);
	  // Preprocess the inputFile headers to the outputFile
      replaceHeaders(inputFile, outputFile);
	  // Update file with preprocessed comments ( removing comments )
	  removeComments(outputFile);
	  // Update file with preprocessed define directives 
      replaceDefines(outputFile);

  }

  // If arguments != 3 || != 4
  else {
    printf("********Invalid arguments********\n");
    printf("Exiting . . .\n");
    exit(0);
  }
  
  return 0;
}
/* 
 * Function: replaceDefines 
 * ------------------------
 * Function which is used to preprocess the define directives in a file
 * 
 * const char* input: Input file name of the file to be processed
 *
 * type: void 
*/
void replaceDefines(const char *input) {
  // Defining structure data type to store define directives
  struct defines {
    char consName[50];
    char value[50];
  };
  // File pointer for the input file
  FILE *in;
  // File pointer for a temporary file
  FILE *tempFile;
  // Declaring a buffer of defined buffer size
  char buf[bufSize];
  // Declaring constName and value used to store struct parameters
  char *constName = "";
  char *value = "";
  // Declaring how an identifier line begins
  char *word = "#define";
  // Declaring an array of 10 defines
  struct defines df[10];
  // Declaring a counter to store how many define structures we have used
  int counter = 0;
  // Declaring the name of our temporary file
  char *constFileName = "tempfile.c";

  // Attempting to open input file in read mode
  if ((in = fopen(input, "r")) == NULL) { /* Open source file. */
    perror("fopen source-file");
    exit(0);
  }
  // Opening temporary file in write mode
  tempFile = fopen(constFileName, "w");

  // Looping through input file line by line
  while (fgets(buf, sizeof(buf), in) != NULL) {
    // Check it is a define line
    if (buf[0] == word[0] && buf[1] == word[1] && buf[2] == word[2] &&
        buf[3] == word[3] && buf[4] == word[4] && buf[5] == word[5] 
        ) {
      // Tokenizing line with space delimiter
      strtok(buf, " ");
      // First value is variable name
      (int)constName = strtok(NULL, " ");
      // Second value is variable value
      (int)value = strtok(NULL, " ");
      // Copying name and value to the struct
      strcpy(df[counter].consName, constName);
      strcpy(df[counter].value, value);
      counter++;
    }
    // If not a define line
    else {
		
		remove_newline(buf);
		// Defining a token pointer which will point to the tokenized buffer
		char *token;
		// Tokenizing, pointing to the start of the buffer line
		(int)token = strtok(buf," ");
        // Looping until the end of the line 
		while(token != NULL)
		{
			// Defining a flag if there is occurencies of define directives
			int flag = 0;
			// Defining second buffer on which the line tokens are appended
			char buf2[256]="";
			// Looping for the number of times of found define structures 
			for(int i = 0; i < counter; i++)
			{
			// If the token equals the current define structure
			if(strcmp(df[i].consName,token) == 0)
			{
			    flag = 1;
				// Remove the newline chararacter of the value if there is 
			    remove_newline(df[i].value);
				// Replace buf2 with the value found
				strcpy(buf2,df[i].value);
			}
			}
			// If found define structure 
			if(flag)
			{
			// Write define structure into tempFile
			fputs(buf2,tempFile);
			}
			else 
			{
			//Write the current token and put a space character 
			fputs(token,tempFile);
			fputc(' ',tempFile);
			}
			// Get next token
			(int)token = strtok(NULL," ");
			
		}
		// Reached end of line, put new line character into tempFile
		fputs("\n",tempFile);

    }
  }
  // Closing files
  fclose(in);
  fclose(tempFile);
  // Removing input file and renaming the temporary file with the input file
  // name
  remove(input);
  rename(constFileName, input);
}
/* 
 * Function: replaceHeaders 
 * ------------------------
 * Function producing an outputfile, which is a copy of the input file but 
   with preprocessed headers
 * 
 * const char* input: Input file name of the file to be read
 *
 * const char* output: Output file name of the file to be produced
 * from the input file 
 *
 * type: void 
*/
void replaceHeaders(const char* input,const char* output) {
  // Input file
  FILE* in;
  // Temporary file
  FILE* temp;
  // Header file
  FILE* header;

  // Buffers
  char buf[bufSize];
  char buf2[bufSize];
  // How header file line starts
  char* headerDef = "#include \"";
  // Char array used for tokenizing header lines
  char* token;
  // Char array used for storing header file names
  char* headerFile = "";
  // Name of the temporary file
  char* constFileName = "tempfile.c";

  // Opening input file
  if ((in = fopen(input, "r")) == NULL) {
    perror("fopen source-file");
    exit(0);
  }
  // Creating the temporary file
  temp = fopen(output, "w");

  // Going through input file line by line
  while (fgets(buf, sizeof(buf), in) != NULL) 
  {
    // Check if line is a header file
    if (buf[0] == headerDef[0] && buf[1] == headerDef[1] && buf[2] == headerDef[2] && buf[3] == headerDef[3] && buf[4] == headerDef[4] && buf[5] == headerDef[5]) 
	{
	if(buf[9] == '"')
	{
      // Tokenizing the line to the find headerFile name
      (int)token = strtok(buf, "\"");
      (int)token = strtok(NULL, "\"");

      // Copying token into header file
      strcpy(headerFile, token);
      // Opening header file
      header = fopen(headerFile, "r");
      // Copying contents of header file into temporary file
      while (fgets(buf2, sizeof(buf2), header) != NULL) {
        buf[strlen(buf) - 0] = '\0';
        fputs(buf2, temp);
      }
      fputc('\n', temp);
      // Closing temporary file
      fclose(header);
	  }
    }
    // If not header file, copy line to temporary file
    else {
      fputs(buf, temp);
	  //printf("%s\n",buf);
    }
  }
  // Close temporary file and input file
  fclose(in);
  fclose(temp);
}
/* 
 * Function: removeComments 
 * ------------------------
 * Function removing the comments from an input file
 * 
 * const char* input: Input file name of the file to be processed
 *
 * type: void 
*/
void removeComments(const char* input) {
  // Input file
  FILE* in;
  // Temporary file
  FILE* temp;
  // Name of temporary file
  char* constFileName = "tempfile.c";

  // Opening input file
  if ((in = fopen(input, "r")) == NULL) {
    perror("fopen source-file");
    exit(0);
  }
  // Opening temporary file
  temp = fopen(constFileName, "w");

  int c;
  int startline = 1;
  // While End Of File
  while ((c = fgetc(in)) != EOF) {
    // Check if first character is : '
    if (c == '/') {
      // Getting next character
      c = fgetc(in);
      // Checking if next character is: '
      if (c == '/') {
        // If yes get characters until reaching newline
        while ((c = fgetc(in)) != '\n') {
          // if the last character equals EOF close files
          if (c == EOF) {
            fclose(in);
            fclose(temp);
          }
        }
        // If we are not on startline put newline on the comment place
        if (!startline) fputc('\n', temp);
        startline = 1;
      }
      // If second character is not / then is not comment
      else {
        fputc('/', temp);
        fputc(c, temp);
        startline = 0;
      }
    }
    // If character is not print it to the temp file
    else {
      fputc(c, temp);
      startline = (c == '\n');
    }
  }
  // Close file, remove input file and rename tempFile with input file name
  fclose(in);
  fclose(temp);
  remove(input);
  rename(constFileName, input);
}

/* 
 * Function: countComments 
 * ------------------------
 * Function counting the number of comments in a file
 * 
 * const char* input: Input file name of the input to be processed
 *
 * type: void 
*/
void countComments(const char* input) {
  // Input file
  FILE* in;
  // Try to open input file
  if ((in = fopen(input, "r")) == NULL) {
    perror("fopen source-file");
    exit(0);
  }
  // Variable store num of comments
  int commentsCount = 0;
  char ch;
  // Pointing to the beginning of the input file
  fseek(in, 0, 0);
  // while ch equals end of file
  while ((ch = fgetc(in)) != EOF) {
    // If initial character equals /
    if (ch == '/') {
      // If next character equals /
      if ((ch = fgetc(in)) == '/') {
        // Increment counter
        commentsCount++;
      }
    }
  }
  // Close input file
  fclose(in);

  printf("Number of comments : %i\n", commentsCount);
}

/* 
 * Function: nonEmptyLines 
 * ------------------------
 * Function counting the number of Non-Empty Lines in a file 
 * 
 * const char* input: File name of the input to be processed
 * 
 * type: void 
*/
void nonEmptyLines(const char* input) {
  // Input file
  FILE* in;
  // Trying to open input file in read mode
  if ((in = fopen(input, "r")) == NULL) {
    perror("fopen source-file");
    exit(0);
  }
  // Variable storing num of empty lines
  int emptyLineCount = 0;
  // Variable storing the num of lines 
  int numOfLines = 0;
  char line[bufSize];
  //
  while (fgets(line, bufSize, in) != NULL) {
    int i = 0;
    // Getting length of the line
    int len = strlen(line);
    emptyLineCount++;
	numOfLines++;
    for (i = 0; i < len; i++) {
      if (line[i] != '\n' && line[i] != '\t' && line[i] != ' ') {
        emptyLineCount--;
        break;
      }
    }
  }

  fclose(in);
  int nonEmpty = numOfLines - emptyLineCount;
  printf("Non-empty lines: %i\n",nonEmpty);
}
/* 
 * Function: remove_newline 
 * ------------------------
 * Function which removes the new line character from a given string 
 * 
 * char* str: The desired string for removing newline character 
 *
 * type: void 
*/
void remove_newline(char *str)
{
	int len = strlen(str);
	if(len > 0 && str[len-1] == '\n')
	str[len - 1] = '\0';
}
