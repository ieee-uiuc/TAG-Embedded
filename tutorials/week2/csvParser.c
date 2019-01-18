#include "csvParser.h"

int max(int a, int b) {
    return a > b ? a : b;
}
// "Hi, there\0"
char * stringtok(char * buf, char delim) {
    static char * firstPtr = NULL;
    static char * secondPtr = NULL;
    if (buf != NULL) {
        firstPtr = buf;
        secondPtr = buf;
    }
    if (buf == NULL && firstPtr == NULL && secondPtr == NULL) return NULL;
    while (*secondPtr != '\0' && firstPtr <= secondPtr) {
        if (*secondPtr == delim) {
            *secondPtr = '\0';
            char * tmp = firstPtr;
            firstPtr = secondPtr + 1;
            secondPtr = firstPtr;
            return tmp;
        }
        else {
            secondPtr += 1;
        }
    }
    char * tmp = firstPtr;
    firstPtr = NULL;
    secondPtr = NULL;
    return tmp;
}

struct Parser* parser_init() {
    struct Parser *parser = (struct Parser *) malloc(sizeof(struct Parser));
    parser->colDelimiter = DEFAULT_COL_DELIMITER;
    parser->rowDelimiter = DEFAULT_ROW_DELIMITER;
    parser->rows = 0;
    parser->maxrows = 0;
    parser->maxcols = 0;
    parser->maxtokenlen = 0;
    parser->data = NULL;
    mallocData(parser, DEFAULT_ROWS, DEFAULT_COLS);
    return parser;
}

void setDelimiter (struct Parser *parser, char rowDelim, char colDelim) {
    if (parser == NULL) {
        printf("Must specify a parser\n");
        return;
    }
    parser->rowDelimiter = rowDelim;
    parser->colDelimiter = colDelim;
}

void mallocData(struct Parser *parser, int rows, int cols) {
    if (parser == NULL) {
        printf("Must specify a parser\n");
        return;
    }
    parser->data = NULL;
    parser->data = (char ***) malloc(sizeof(char**) * rows);
    if (parser->data == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        parser->data[i] = NULL;
        parser->data[i] = (char**) malloc(sizeof(char*) * cols);
        if (parser->data[i] == NULL) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < cols; j++) {
            parser->data[i][j] = NULL;
        }
    }
    parser->endColIdx = (int *) malloc(sizeof(int) * rows);
    memset(parser->endColIdx, 0, sizeof(int) * rows);
    parser->maxrows = rows;
    parser->maxcols = cols;
    parser->maxtokenlen = 0;
}

// readLine will also resize the buffer when needed
void readLine(struct Parser *parser, FILE *fp, char **buf, size_t *buf_size) {
    if (parser == NULL) {
        printf("Must specify a parser\n");
        return;
    }
    if (fp == NULL || buf == NULL || buf_size == NULL) return;
    int current_index = 0;
    char current_char = 0;
    while (current_char != parser->rowDelimiter) {
        current_char = (unsigned char) fgetc(fp);
        if (feof(fp) || current_char == parser->rowDelimiter) {
            (*buf)[current_index] = '\0';
            return;
        }
        if (current_index >= *buf_size) {
            (*buf) = (char *) realloc(buf, sizeof(char) * *buf_size * 2);
            *buf_size *= 2;
        }
        (*buf)[current_index] = current_char;
        current_index++;
    }
    (*buf)[current_index] = '\0';
}
// Free the 3-dimensional char array
void freeParser (struct Parser *parser) {
    if (parser == NULL) return;
    for (int i = 0; i < parser->maxrows; i++) {
        for (int j = 0; j < parser->maxcols; j++) {
            if (parser->data[i][j] != NULL)
                free(parser->data[i][j]);
        }
        if (parser->data[i] != NULL)
            free(parser->data[i]);
    }
    free(parser->data);
    free(parser->endColIdx);
    free(parser);
    parser = NULL;
}
void reallocData(struct Parser *parser, int rows, int cols, int tokenLen) {
    if (parser == NULL) {
        printf("Must specify a parser\n");
        return;
    }
    parser->data = (char ***) realloc(parser->data, sizeof(char**) * rows);

    if (parser->data == NULL) {
        perror("realloc failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        parser->data[i] = (char**) realloc(parser->data[i], sizeof(char*) * cols);
        if (parser->data[i] == NULL) {
            perror("realloc failed");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < cols; j++) {
            if (parser->data[i][j] != NULL) {
                parser->data[i][j] = (char *) realloc(parser->data[i][j], sizeof(char) * tokenLen);
                if (parser->data[i][j] == NULL) {
                    perror("realloc failed");
                    exit(EXIT_FAILURE);
                }
                memset(parser->data[i][j] + parser->maxtokenlen, 0, tokenLen - parser->maxtokenlen * sizeof(char)); // Set new data to 0
            }
            else {
                parser->data[i][j] = (char *) malloc(sizeof(char) * tokenLen);
                if (parser->data[i][j] == NULL) {
                    perror("malloc failed");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    parser->endColIdx = (int *) realloc(parser->endColIdx, sizeof(int) * rows);
    parser->maxrows = rows;
    parser->maxcols = cols;
    parser->maxtokenlen = tokenLen;
}
void readCSV(struct Parser *parser, char *readfilename) {
    if (readfilename == NULL) {
        printf("No file specified to read from\n");
        return;
    }
    if (parser == NULL) {
        printf("No parser specified\n");
    }
    FILE *fp = fopen(readfilename, "r");
    if (fp == NULL) {
        perror("Opening file failed");
    }
    // Init default buffer
    size_t buf_size = DEFAULT_BUF_SIZE * sizeof(char);
    char *linebuf = (char *) malloc(sizeof(char) * buf_size);
    memset(linebuf, 0, buf_size * (sizeof(char)));
    int currentRow = 0;
    int currentCol = 0;
    int i = 0;
    while (!feof(fp)) {

        readLine(parser, fp, &linebuf, &buf_size);

        char *tok = stringtok(linebuf, (parser->colDelimiter));
        if (currentRow >= parser->maxrows) {
            //printf("Reallocate rows\n");
            reallocData(parser, 2 * currentRow, parser->maxcols, parser->maxtokenlen);
        }
        while (tok != NULL) {
            if (currentCol >= parser->maxcols - 1) {
                //printf("Reallocate cols\n");
                reallocData(parser, parser->maxrows, 2 * currentCol, parser->maxtokenlen);
            }
            int lenstr = strlen(tok);
            if (lenstr >= parser->maxtokenlen - 1) {
                //printf("Reallocate tokens\n");
                reallocData(parser, parser->maxrows, parser->maxcols, 2 * lenstr);
            }
            if (tok[0] == '\0') {
                parser->data[currentRow][currentCol] = NULL;
            }
            else strcpy(parser->data[currentRow][currentCol], tok);
            currentCol++;
            tok = stringtok(NULL, parser->colDelimiter);

        }
        parser->endColIdx[currentRow] = currentCol;
        currentCol = 0;
        currentRow++;
    }
    parser->rows = max(parser->rows, currentRow - 2);
    free(linebuf);
    if (fclose(fp) == -1) {
        perror("Can't close file");
        exit(EXIT_FAILURE);
    }
}

void printCSV(struct Parser *parser, FILE * outStream) {

    if (parser == NULL) {
        printf("No parser specified\n");
        return;
    }
    if (outStream == NULL) {
        printf("No out stream specified\n");
        return;
    }
    for (int i = 0; i <= parser->rows; i++) {
        int j = 0;
        while(parser->endColIdx[i] >= j) {

            if (parser->data[i][j] != NULL) {
                fprintf(outStream,"%s", parser->data[i][j]);
            }
            if (parser->endColIdx[i] > j + 1 && j + 1 <= parser->maxcols) {
                fprintf(outStream,"%c", parser->colDelimiter);
            }
            j++;
        }
        fprintf(outStream, "%c", parser->rowDelimiter);
    }
}

void writeCSV (struct Parser *parser, char *writefilename) {
    if (writefilename == NULL || writefilename == "") {
        printf("No file specified to write to\n");
    }
    if (parser == NULL) {
        printf("No parser specified\n");
    }

    FILE *fp = fopen(writefilename, "w");
    if (fp == NULL) {
        perror("Opening file failed");
    }
    int col = 0;
    for (int i = 0; i <= parser->rows; i++) {
        col = 0;
        while (col <= parser->endColIdx[i]) {
            if (parser->data[i][col] != NULL) {
                size_t len = strlen(parser->data[i][col]);
                size_t bytes_written = fwrite(parser->data[i][col], sizeof(char), len, fp);
                if (bytes_written != len) {
                    perror("Writing bytes");
                    exit(EXIT_FAILURE);
                }
                if (parser->endColIdx[i] > col + 1 && col + 1 <= parser->maxcols) {
                    unsigned ret_val = fputc(parser->colDelimiter, fp);
                    if (ret_val == EOF) {
                        perror("Writing delimiter");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            col++;
        }
        unsigned ret_val = fputc(parser->rowDelimiter, fp);
        if (ret_val == EOF) {
            perror("Writing delimiter");
            exit(EXIT_FAILURE);
        }
    }
    if (fclose(fp) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
}

void checkReallocate(struct Parser *parser, int row, int col, int tokenLen) {
    if (parser == NULL) {
        printf("Must specify a parser\n");
        return;
    }
    if (row >= parser->maxrows) reallocData(parser, 2 * row, col, tokenLen);
    if (col >= parser->maxcols) reallocData(parser, row, 2 * col, tokenLen);
    if (tokenLen >= parser->maxtokenlen) reallocData(parser, row, col, 2 * tokenLen);
}

// Must provide a large enough buffer
void getData(struct Parser * parser, int row, int col, char * buf, size_t buf_size) {
    if (parser == NULL) {
        printf("Must specify a parser\n");
        return;
    }
    if (buf_size < parser->maxtokenlen) {
        fprintf(stderr, "Buffer is not large enough to get data\n");
        return;
    }
    if (parser->data[row][col] == NULL) {
        fprintf(stderr, "Data is null at location row = %d col = %d\n", row, col);
        return;
    }
    if (row > parser->maxrows || col > parser->endColIdx[row]) {
        fprintf(stderr, "Accessed index out of bounds. No data at row = %d col = %d\n", row, col);
        return;
    }
    strcpy(buf, parser->data[row][col]);
}

void setData(struct Parser * parser, int row, int col, char * buf, size_t buf_size) {
    if (parser == NULL) {
        printf("Must specify a parser\n");
        return;
    }
    checkReallocate(parser, row, col, strlen(buf));
    if (parser->data[row][col] == NULL) {
        parser->data[row][col] = (char *) malloc(sizeof(char) * parser->maxtokenlen);
    }
    parser->rows = max(parser->rows, row);
    parser->endColIdx[row] = max(parser->endColIdx[row], col);
    strcpy(parser->data[row][col], buf);
}

int main() {
    struct Parser *parser = parser_init();
    readCSV(parser, "anotherfile.csv");
    char buf[1000];
    strcpy(buf, "eeee");
    FILE * f = fopen("anotherfile.csv", "r");
    setData(parser, 50, 3, buf, 1000);
    printCSV(parser, f);
    memset(buf, 0, 1000);
    getData(parser, 50, 2, buf, 1000);

    freeParser(parser);
}
