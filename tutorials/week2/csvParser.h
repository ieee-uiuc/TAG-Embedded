#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define DEFAULT_COL_DELIMITER ','
#define DEFAULT_ROW_DELIMITER '\n'
#define DEFAULT_BUF_SIZE 1024
#define DEFAULT_ROWS 16
#define DEFAULT_COLS 16
#define DEFAULT_TOKEN_LEN 16
struct Parser {
    char colDelimiter;
    char rowDelimiter;
    int rows;
    int maxrows;
    int maxcols;
    int maxtokenlen;
    char ***data;
};

void mallocData(struct Parser *parser, int rows, int cols, int tokenLen);

void reallocData(struct Parser *parser, int rows, int cols, int tokenLen);

struct Parser* parser_init();

void setDelimiter (char rowdelim, char coldelim, struct Parser *parser);

void readLine(struct Parser *parser, FILE *fp, char **buf, size_t *buf_size);

void freeData(struct Parser *parser);

void reallocData(struct Parser *parser, int rows, int cols, int tokenLen);

void readCSV(struct Parser *parser, char *readfilename);

void printCSV (struct Parser *parser);

void writeCSV (struct Parser *parser, char *writefilename);
