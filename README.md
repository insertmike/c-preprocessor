# C Module Coursework :blue_book:
This file reports details about my C Module Coursework for `Edinburgh Napier University`

*Submitted:*  1 March 2019

*Grade:* 100% ( 24/24 )

*Graded on:* 16 March 2019


## General Description
A command line application containing basic functionality of a C language preprocessor. 

The application is reading a `.c` file containing source code written in the C programming language, and outputting a preprocessed version of that file according to the specification.

**Overall Approach:** 
- Meaningful variable names.
- Correct indentation.
- Suitable comments.

### Application Specification
The preprocess application is reading a `.c` file and is outputting the following to the console:

1. **Number of non-empty lines**
   - Non-empty lines are defined as those that contain at least one character that is not a newline,    space or a tab

2. **Number of comments**
   - A comment is defined as beginning with '//' and ending at the end of that line.
   - Multiline comments are not considered.
  
The preprocess application is reading a `.c` file and is outputting modified `.o` file as follows:

1. **All comments are removed**
   - All comments in the processed versions are removed. 
   - Multiline comments are not considered.
  
2. **Header files are replaced with contents**
   - All lines that are including a header files are replaced with the entire contents of the file called.
   - It is assumed that the files are located in the same directory
   
3. **Defines are processed**
   - A line that begins with *#define constant_name value* are processed.
   - The line is removed.
   - Through the rest of the file, wherever *constant name* appears it is removed and replaced with the *value* in the output file.
   
4. **Application input arguments**
   - The application understands the command line arguments shown in the table below.
  
        <img src="https://user-images.githubusercontent.com/45242072/63803780-4ed08100-c91e-11e9-844d-33febef29355.png" alt="app arguments table" >
          
Input arg examples: *preprocess -i myprog.c*, *preprocess -i myprog.c -c*

7. **Make file**
  - The makefile include operations to clean cached preprocessed files *(.o)* and to execute the program with the different argument options. 
  
### How to run locally
Build chain: *Microsoft Developer Command Prompt ( VS 2017 )*
1. Open your *build chain* and navigate to the application folder.
2. Extract the test files from the *test-files* folder.
2. Make use of the *makefile* using the target commands.
3. Run nmake clean to clean the folder after your tests.

*NOTE:* In the *test-files* folder, the files with `.o` extension are the resulted files after running the application.
