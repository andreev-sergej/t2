#include <stdio.h>
#ifndef TEST
#define TEST
    void run_test(char* testfile_path, int chain_start, int chain_end);
    int compare_files(FILE *file1, FILE *file2);
    void run_all_tests();
#endif