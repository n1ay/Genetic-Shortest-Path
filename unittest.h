//
// Created by n1ay on 07.07.18.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#ifndef C_UNIT_TEST_H
#define C_UNIT_TEST_H

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define ANSI_BOLD         "\x1b[1m"


#define TEST_ERROR_FLAG_FILENAME "test-result-failed.flag"
#define SET_ERROR_FLAG creat(TEST_ERROR_FLAG_FILENAME, S_IRWXU)
#define UNSET_ERROR_FLAG unlink(TEST_ERROR_FLAG_FILENAME)
#define DETECT_ERROR_FLAG access(TEST_ERROR_FLAG_FILENAME, F_OK ) != -1

#define TEST_FAILED_MSG(msg) \
    fprintf(stdout, ANSI_BOLD ANSI_COLOR_RED msg ANSI_COLOR_RESET);

#define TEST_PASSED_MSG(msg) \
    fprintf(stdout, ANSI_BOLD ANSI_COLOR_GREEN msg ANSI_COLOR_RESET);

#define TEST(NAME) \
    UNSET_ERROR_FLAG; \
    NAME(); \
    if(DETECT_ERROR_FLAG) { \
        TEST_FAILED_MSG("in test "#NAME".\n"); \
        TEST_FAILED_MSG("Test "#NAME" FAILED.\n"); \
        UNSET_ERROR_FLAG; \
    } else TEST_PASSED_MSG("Test "#NAME" PASSED.\n"); \


#define ASSERT_EQUALS(VAL1, VAL2) \
    if((VAL1)!=(VAL2)) {\
        TEST_FAILED_MSG("Assertion failed: "#VAL1" is not equal "#VAL2 "\n"); \
        SET_ERROR_FLAG; \
    }

#define ASSERT_NOT_EQUALS(VAL1, VAL2) \
    if((VAL1)==(VAL2)) {\
        TEST_FAILED_MSG("Assertion failed: "#VAL1" is equal "#VAL2 "\n"); \
        SET_ERROR_FLAG; \
    }

#define ASSERT_GREATER(VAL1, VAL2) \
    if((VAL1)<=(VAL2)) {\
        TEST_FAILED_MSG("Assertion failed: "#VAL1" is not greater than "#VAL2 "\n"); \
        SET_ERROR_FLAG; \
    }

#define ASSERT_GREATER_EQUALS(VAL1, VAL2) \
    if((VAL1)<(VAL2)) {\
        TEST_FAILED_MSG("Assertion failed: "#VAL1" is not greater equal than "#VAL2 "\n"); \
        SET_ERROR_FLAG; \
    }

#define ASSERT_LESS(VAL1, VAL2) \
    if((VAL1)>=(VAL2)) {\
        TEST_FAILED_MSG("Assertion failed: "#VAL1" is not less than "#VAL2 "\n"); \
        SET_ERROR_FLAG; \
    }

#define ASSERT_LESS_EQUALS(VAL1, VAL2) \
    if((VAL1)>(VAL2)) {\
        TEST_FAILED_MSG("Assertion failed: "#VAL1" is not greater less than "#VAL2 "\n"); \
        SET_ERROR_FLAG; \
    }

#define ASSERT_FAIL \
    TEST_FAILED_MSG("Assertion failed on demand\n"); \
    SET_ERROR_FLAG;

#define ASSERT_EQUAL ASSERT_EQUALS
#define ASSERT_NOT_EQUAL ASSERT_EQUALS
#define ASSERT_GREATER_EQUAL ASSERT_GREATER_EQUALS
#define ASSERT_LESS_EQUAL ASSERT_LESS_EQUALS

#endif //C_UNIT_TEST_H

#pragma clang diagnostic pop