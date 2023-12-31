#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include "../../hw2/Criterion/include/criterion/criterion.h"

#define TEST_TIMEOUT 15

#define PROGNAME "bin/grades"
#define TEST_REF_DIR "tests/rsrc"
#define TEST_OUTPUT_DIR "test_output"
#define STANDARD_LIMITS "ulimit -t 10; ulimit -f 2000;"

#define QUOTE1(x) #x
#define QUOTE(x) QUOTE1(x)

extern int errors, warnings;

extern char *test_infile;
extern char *test_output_dir;
extern char *test_outfile;
extern char *test_errfile;
extern char *test_altfile;

int setup_test(char *name);
int run_using_system(char *name, char *pre_cmd, char *valgrind_cmd,
                     char *program_options, char *limits);
void assert_normal_exit(int status);
void assert_error_exit(int status);
void assert_expected_status(int expected, int status);
void assert_expected_status(int expected, int status);
void assert_signaled(int sig, int status);
void assert_outfile_matches(char *name, char *filter);
void assert_errfile_matches(char *name, char *filter);
void assert_altfile_matches(char *name, char *filter);
void assert_no_valgrind_errors(int status);
void assert_binfile_matches(char *name);
