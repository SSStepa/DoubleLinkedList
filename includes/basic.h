/**
 * @file basic.h
 * @brief structs, consts and funcs i use daily.
 */
#ifndef BASIC_H
#define BASIC_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdio.h>
#include <getopt.h>
#include <time.h>
#include <stdarg.h>

// -------------------------------------------------------- Project basic only -----------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Work of function available results.
 */
enum WORK_RES {
    OK       = 0, // all good
    WRIN     = 1, // function got bad args
    NOMEM    = 2, // not enough memory
    FILEERR  = 4, // no file to open.
 
    STACK_STRUCT     = 10, // problem with struct
    STACK_DATA       = 11, // wrong data format
    STACK_CAP        = 12, // zero capacity
    STACK_OVERFLOW   = 13,  // size > capacity
    STACK_UNDERFLOW  = 14, // size < 0;
    STACK_CANARY_RIP = 15, // rip of stack canary;

    TAKEN_LABEL = 20, // label already has it's 
    NO_LABEL = 21, // label does not exist

    WRLINK = 30, // wrong link between nodes in list
};

/**
 * @brief struct to store info about string: length and pointer to first element
 * str - pointer to the first element of the string
 * len - length of the string (with no \0)
 */
struct string_t {
    char *str;
    size_t len;
};



/**
 * used to check that function run correctly
 * 
 * need to be variable statusCode initialized.
 */
#define RUN_COMMAND(func, errorMessage)           \
    if ((statusCode = func) != OK)                \
        return $ERR(statusCode, errorMessage)


/**
 * Const to say that number is zero(all numbers less than EPSILON are regarded as zeros)
 */
const double EPSILON = 0.0001;

/**
 * function to check if number is zero
 */
bool IsZero(double x);
//------------------------------------------------------------- COLORS ------------------------------------------------------------------------
/**
 * Basic colors
 */
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define COLOR_RESET "\e[0m"

//----------------------------------------------------- PRINTING VARS AND ERRORS ------------------------------------------------------------------------

/**
 * define to translate name of something into string (usually is used for debugging)
 */
#define TO_STR(str) #str

/**
 * basic log file name
 */
const char *const LOG_FILE = "mainLog.html";

/**
 * max length of error message
 */
const int MAX_MESS_LENGTH = 200;

/**
 * struct used to describe error info 
 */
struct debuggingInfo_t{
    const char *VariableName;           // Name of object variable 
    const char *fileCreationName;       // file where object was created
    const char *functionCreationName;   // function where object was created 
    int         lineCreationNumber;     // number of line where object was created 

    const char *errorText;              // error message if error had occurred
    WORK_RES    err;                    // error code 
};

/**
 * fuctions used  for debugging. With macro to create call shorter Usage pattern(for all):
 * $ind(variable) => <variable.name> = <variable.value>
 * with line of call
 */
void InfoPrintfInt      (int var, const char *varName, const char *file, int line);
void InfoPrintfStr      (const char *var, const char *varName, const char *file, int line);
void InfoPrintfC        (char var, const char *varName, const char *file, int line);
void InfoPrintfDouble   (double var, const char *varName, const char *file, int line);
void InfoPrintfLlu      (size_t var, const char *varName, const char *file, int line);

#define $int(Variable) InfoPrintfInt(Variable, TO_STR(Variable), __FILE__, __LINE__)
#define $str(Variable) InfoPrintfStr(Variable, TO_STR(Variable), __FILE__, __LINE__)
#define $ch(Variable) InfoPrintfC(Variable, TO_STR(Variable), __FILE__, __LINE__)
#define $dbl(Variable) InfoPrintfDouble(Variable, TO_STR(Variable), __FILE__, __LINE__)
#define $llu(Variable) InfoPrintfLlu(Variable, TO_STR(Variable), __FILE__, __LINE__)

/**
 * begining of new log session
 * prints divider form previous info
 */
WORK_RES SetUpLog();

/**
 * ending of log session(prints line that all good)
 */
WORK_RES EndLog();

WORK_RES LogPrintf(const char *messageType, const char *Mess, int line, const char *file, WORK_RES ErrCode, ...);
WORK_RES StartError();
WORK_RES EndError();

#define $ERR(ErrCode, ErrorMessage, ...)         LogPrintf("<font color=red>ERROR</font>", ErrorMessage, __LINE__, __FILE__, ErrCode, ##__VA_ARGS__)
#define $INFO(InfoMessage, ...)           ON_DBG(LogPrintf("<font color=blue>INFO</font>", InfoMessage, __LINE__, __FILE__, OK,  ##__VA_ARGS__))

 

#define LOG_START()                              \
    FILE *logFile = fopen(LOG_FILE, "a");        

#define LOG_END()                                \
    fclose(logFile);                             


#define LOG_PRINTF(...) \
    fprintf(logFile, __VA_ARGS__); \
    fflush(logFile);


#define DEBUGGER

#ifdef DEBUGGER
#define ON_DBG(...) __VA_ARGS__

#define MY_ASSERT(...) \
    if (!(__VA_ARGS__)) \
        return $ERR("MY ASSERTION FAILED: WRONG INPUT TO FUNCTION", WRIN); 
#else
#define ON_DBG(...) 

#define MY_ASSERT(...) 
#endif

const char *const OPTS = "i:o:h";

WORK_RES GetFileFull(const char *fileName, string_t *string);
WORK_RES GetFileFullBin(const char *fileName, string_t *string);

WORK_RES FlagsParse(int argc, char *const *argv, const char **FileToReadFrom, const char **FileToWriteTo);
void ShowHelp();

#endif
