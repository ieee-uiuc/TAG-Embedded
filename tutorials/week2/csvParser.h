#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define DEFAULT_COL_DELIMITER ','
#define DEFAULT_ROW_DELIMITER '\n'
#define DEFAULT_BUF_SIZE 1024 // Line buffer size
#define DEFAULT_ROWS 500 // Initial mem allocated for each col
#define DEFAULT_COLS 500 // Initial mem allocated for each row
#define DEFAULT_TOKEN_LEN 50 // Initial mem allocated for each string
struct Parser {
    char colDelimiter; // Set delimiter for col (usually ',')
    char rowDelimiter; // Set delimiter for row (usually '\n')
    int rows; // Number of rows filled so far
    int maxrows; // Maximum row mem allocated
    int maxcols; // Max col mem allocated
    int maxtokenlen; // Max token mem allocated
    char ***data; // The data for the matrix of strings
    int * endColIdx; // The end of every column
};

void mallocData(struct Parser *parser, int rows, int cols);

void reallocData(struct Parser *parser, int rows, int cols, int tokenLen);

struct Parser* parser_init();

void setDelimiter (char rowdelim, char coldelim, struct Parser *parser);

void readLine(struct Parser *parser, FILE *fp, char **buf, size_t *buf_size);

void freeData(struct Parser *parser);

void reallocData(struct Parser *parser, int rows, int cols, int tokenLen);

void checkReallocate(struct Parser *parser, int row, int col, int tokenLen);

void readCSV(struct Parser *parser, char *readfilename);

void printCSV (struct Parser *parser);

void writeCSV (struct Parser *parser, char *writefilename);

void getData(struct Parser *parser, int row, int col, char * buf, size_t buf_size);

void setData(struct Parser *parser, int row, int col, char * buf, size_t buf_size);
