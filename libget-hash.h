


typedef struct _pack{
    char *file_path;
    void *hash;
}Pack;

void help(void);
FILE *file_read_routine(void *file_path_str);