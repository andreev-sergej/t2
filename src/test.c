#include "test.h"
#include "tree.h"
#include "memory.h"

int main()
{
    run_all_tests();
    return 0;
}

void run_test(char* testfile_path, int chain_start, int chain_end)
{
    Tree *tree = tree_create(chain_start, chain_end);
    memory_fill(tree);
    tree_print_to_file(tree, "output.txt");
    tree_free(tree);
    FILE *file1 = fopen("output.txt", "r");
    FILE *file2 = fopen(testfile_path, "r");
    printf("\033[1m\033[33m%s\t\033[0m", testfile_path);
    if(compare_files(file1, file2))
        printf("\033[1m\033[32mPASSED\033[0m\n");
    else
        printf("\033[1m\033[31mNOT PASSED\033[0m\n");
    fclose(file1); 
    fclose(file2);
}

int compare_files(FILE *file1, FILE *file2)
{
    char ch1 = getc(file1);
    char ch2 = getc(file2);
    while (ch1 != EOF && ch2 != EOF)
    {
        if (ch1 != ch2)
        {
            return 0;
        }
        ch1 = getc(file1);
        ch2 = getc(file2);
    }
    return 1; 
}

void run_all_tests()
{
    run_test("tests/test1-13.txt", 1, 13);
    run_test("tests/test17-17.txt", 17, 17);
    run_test("tests/test32-32.txt", 32, 32);
    run_test("tests/test40-50.txt", 40, 50);
    run_test("tests/test99-100.txt", 99, 100);
    run_test("tests/test100-110.txt", 100, 110);
    run_test("tests/test111-112.txt", 111, 112);
    run_test("tests/test525-531.txt", 525, 531);
    run_test("tests/test666-670.txt", 666, 670);
    run_test("tests/test999-1000.txt", 999, 1000);
}