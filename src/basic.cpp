#include "../includes/basic.h"

void InfoPrintfInt(int var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%d%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

void InfoPrintfStr(const char *var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%s%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

void InfoPrintfC(char var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%c%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

void InfoPrintfLlu(size_t var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%llu%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}


void InfoPrintfDouble(double var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%lg%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

WORK_RES ErrorPrintf(const char *errMess, int line, const char *file, WORK_RES ErrCode, ...)
{
    LOG_START();

    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char *time_str = asctime(timeinfo);
    time_str[strlen(time_str) - 1] = '\0';

    va_list argsPrintf = {};
    va_start(argsPrintf, ErrCode);
    char errMessText[MAX_MESS_LENGTH] = "";
    vsprintf(errMessText, errMess,  argsPrintf);


    #ifdef LOUD
    fprintf(stderr, CYN "[%s] %s:%d:%s %s:%d %s%s\n" COLOR_RESET, time_str, file, line, COLOR_RESET, TO_STR(ErrCode), ErrCode, RED, errMessText);
    #endif


    LOG_PRINTF("[%s\b\b] %s:%d: %s:%d %s\n", time_str, file, line, TO_STR(ErrCode), ErrCode, errMessText);

    LOG_END();

    va_end(argsPrintf);

    return ErrCode;
}

WORK_RES StartError()
{
    FILE *fileLog = fopen(LOG_FILE, "a");
    if (fileLog == NULL) return $ERR(FILEERR, "PROBLEM WITH LOG FILE");

    fwrite("# ", 1, 2, fileLog);

    fclose(fileLog);

    return OK;
}

WORK_RES EndError()
{
    FILE *fileLog = fopen(LOG_FILE, "a");
    if (fileLog == NULL) return $ERR(FILEERR, "PROBLEM WITH LOG FILE");

    fwrite("-------------------------------------------------------------------------------\n\n", 1, 80, fileLog);

    fclose(fileLog);

    return OK;
}

WORK_RES SetUpLog()
{
    FILE *fileLog = fopen(LOG_FILE, "a");
    if (fileLog == NULL) return $ERR(FILEERR, "PROBLEM WITH LOG FILE");

    fwrite("-------------------------------------------------------------------------------\n", 1, 80, fileLog);
    fwrite("                                 <<NEW RUN>>                                   \n", 1, 80, fileLog);
    fwrite("-------------------------------------------------------------------------------\n\n", 1, 80, fileLog);
    
    fclose(fileLog);
    return OK;
}

WORK_RES EndLog()
{
    FILE *fileLog = fopen(LOG_FILE, "a");

    fwrite("PROGRAM ENDED WITH ALL GOOD", 1, 28, fileLog);

    fclose(fileLog);
    return OK;

}

bool IsZero(double x)
{
    if (fabs(x) <= EPSILON)
        return true;
    else
        return false;
}

WORK_RES GetFileFull(const char *fileName, string_t *string)
{
    assert(fileName != NULL);
    assert(string);

    int fileDes = open(fileName, O_RDONLY, 0);
    if (fileDes == -1) return $ERR(FILEERR, "NO FILE TO READ FROM IN GetFAsmFileFull");

    struct stat st = {};
    if (fstat(fileDes, &st)) return $ERR(FILEERR, "ERROR IN FILE WHILE TRYING TO fstat");

    string -> str = (char *) calloc(st.st_size + 1, sizeof(char));
    if (string -> str == NULL) return $ERR(NOMEM, "NOT ENOUGH MEMORY TO READ FILE AS FULL");


    int fileLen = read(fileDes, (void *) string -> str, st.st_size);
    if (fileLen < 0) return $ERR(FILEERR, "ERROR WHILE READING FROM FILE");

    string -> str = (char *) realloc(string -> str, fileLen + 1);
    *(string -> str + fileLen) = '\0';
    
    string -> len = (size_t) fileLen;

    close(fileDes);

    return OK;
}

WORK_RES GetFileFullBin(const char *fileName, string_t *string)
{
    assert(fileName != NULL);
    assert(string);

    int fileDes = open(fileName, O_RDONLY | O_BINARY, 0);
    if (fileDes == -1) return $ERR(FILEERR, "NO FILE TO READ FROM IN GetFAsmFileFull");

    struct stat st = {};
    if (fstat(fileDes, &st)) return $ERR(FILEERR, "ERROR IN FILE WHILE TRYING TO fstat");

    string -> str = (char *) calloc(st.st_size + 1, sizeof(char));
    if (string -> str == NULL) return $ERR(NOMEM, "NOT ENOUGH MEMORY TO READ FILE AS FULL");


    int fileLen = read(fileDes, (void *) string -> str, st.st_size);
    if (fileLen < 0) return $ERR(FILEERR, "ERROR WHILE READING FROM FILE");

    string -> str = (char *) realloc(string -> str, fileLen + 1);
    *(string -> str + fileLen) = '\0';
    
    string -> len = (size_t) fileLen;

    close(fileDes);

    return OK;
}

WORK_RES FlagsParse(int argc, char *const *argv, const char **FileToReadFrom, const char **FileToWriteTo)
{
    int arg = 0;

    while((arg = getopt(argc, argv, OPTS)) != -1) {
        switch (arg)
        {
        case 'i':
            *FileToReadFrom = optarg;
            break;

        case 'o':
            *FileToWriteTo = optarg;
            break;

        case 'h':
            ShowHelp();
            break;

        default:
            $ERR(WRIN, "BAD FLAGS IN CALL");
            break;
        }
    }

    return OK;
}

void ShowHelp()
{
    printf("[-i]  Name of file to read from\n");
    printf("[-o]  Name of file to write to");
}