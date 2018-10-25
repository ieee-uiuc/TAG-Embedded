#include "csvParser.h"

struct Parser* parser_init() {
    struct Parser *parser = (struct Parser *) malloc(sizeof(struct Parser));
    parser->colDelimiter = DEFAULT_COL_DELIMITER;
    parser->rowDelimiter = DEFAULT_ROW_DELIMITER;
    parser->rows = 0;
    parser->maxrows = 0;
    parser->maxcols = 0;
    parser->maxtokenlen = 0;
    parser->data = NULL;
    mallocData(parser, DEFAULT_ROWS, DEFAULT_COLS, DEFAULT_TOKEN_LEN);
    return parser;
}

void setDelimiter (char rowDelim, char colDelim, struct Parser *parser) {
    if (parser == NULL) {
        printf("Must specify a parser\n");
        return;
    }
    parser->rowDelimiter = rowDelim;
    parser->colDelimiter = colDelim;
}

void mallocData(struct Parser *parser, int rows, int cols, int tokenLen) {
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
            parser->data[i][j] = (char *) malloc(sizeof(char) * tokenLen);
            if (parser->data[i][j] == NULL) {
                perror("malloc failed");
                exit(EXIT_FAILURE);
            }
        }
    }
    parser->maxrows = rows;
    parser->maxcols = cols;
    parser->maxtokenlen = tokenLen;
}

// readLine will also resize the buffer when needed
void readLine(struct Parser *parser, FILE *fp, char **buf, size_t *buf_size) {
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
    free(parser);
    parser = NULL;
    // if (parser == NULL) return;
    // if (parser->data = NULL) return;
    // for (int i = 0; i < parser->maxrows; i++) {
    //     for (int j = 0; j < parser->maxcols; j++) {
    //         printf("%d, %d\n", i, j);
    //         printf("%s", parser->data[i][j]);
    //         if (parser->data[i][j] != NULL)
    //             free(parser->data[i][j]);
    //         parser->data[i][j] = NULL;
    //     }
    //     if (parser->data[i] != NULL)
    //         free(parser->data[i]);
    //     parser->data[i] = NULL;
    // }
    // free(parser->data);
    // parser->data = NULL;
    // free(parser);
    // parser = NULL;
}
void reallocData(struct Parser *parser, int rows, int cols, int tokenLen) {
    printf("Reallocing\n");
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
            parser->data[i][j] = (char *) realloc(parser->data[i][j], sizeof(char) * tokenLen);
            if (parser->data[i][j] == NULL) {
                perror("realloc failed");
                exit(EXIT_FAILURE);
            }
        }
    }
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

    int currentRow = 0;
    int currentCol = 0;
    int i = 0;
    while (!feof(fp)) {
        readLine(parser, fp, &linebuf, &buf_size);
        char *tok = strtok(linebuf, &(parser->colDelimiter));
        if (currentRow >= parser->maxrows) {
            printf("Reallocate rows\n");
            reallocData(parser, 2 * currentRow, parser->maxcols, parser->maxtokenlen);
        }
        while (tok != NULL) {
            printf("%d %d\n", currentRow, currentCol);
            printf("%s\n", tok);
            // maxcols -1 so a "" can be allocated
            if (currentCol >= parser->maxcols - 1) {
                printf("Reallocate cols\n");
                reallocData(parser, parser->maxrows, 2 * currentCol, parser->maxtokenlen);
            }
            int lenstr = strlen(tok);
            // maxtokenlen - 1 so there is space to allocate a ""
            if (lenstr >= parser->maxtokenlen - 1) {
                printf("Reallocate tokens\n");
                reallocData(parser, parser->maxrows, parser->maxcols, 2 * lenstr);
            }
            strcpy(parser->data[currentRow][currentCol], tok);
            currentCol++;
            tok = strtok(NULL, &(parser->colDelimiter));

        }
        strcpy(parser->data[currentRow][currentCol], "");
        currentCol = 0;
        currentRow++;
    }
    parser->rows = currentRow - 1;
    free(linebuf);
    puts("Freing\n");
    if (fclose(fp) == -1) {
        perror("Can't close file");
        exit(EXIT_FAILURE);
    }
}

void printCSV(struct Parser *parser) {
    for (int i = 0; i < parser->rows; i++) {
        int j = 0;
        while(strcmp(parser->data[i][j], "") != 0 && j < parser->maxcols) {
            printf("%s", parser->data[i][j]);
            if (strcmp(parser->data[i][j + 1], "") != 0 && j + 1 < parser->maxcols) {
                printf("%c", parser->colDelimiter);
            }
            j++;
        }
        printf("%c", parser->rowDelimiter);
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
    for (int i = 0; i < parser->rows; i++) {
        col = 0;
        while (col < parser->maxcols && strcmp(parser->data[i][col], "") != 0) {
            size_t len = strlen(parser->data[i][col]);
            size_t bytes_written = fwrite(parser->data[i][col], sizeof(char), len, fp);
            if (bytes_written != len) {
                perror("Writing bytes");
                exit(EXIT_FAILURE);
            }
            if (strcmp(parser->data[i][col + 1], "") != 0 && col + 1 < parser->maxcols) {
                unsigned ret_val = fputc(parser->colDelimiter, fp);
                if (ret_val == EOF) {
                    perror("Writing delimiter");
                    exit(EXIT_FAILURE);
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

int main() {
    struct Parser *parser = parser_init();
    readCSV(parser, "file.csv");
    printCSV(parser);
    //writeCSV(parser, "anotherfile.csv");
    //freeParser(parser);
}
