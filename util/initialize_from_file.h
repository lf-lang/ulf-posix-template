/**
 * @file
 * @author Edward A. Lee
 *
 * @brief Utility functions for initializing parameters and state variables from a file.
 *
 * Adapted for micro-LF / reactor-uc (POSIX). Originally from reactor-c util.
 */
#ifndef INITIALIZE_FROM_FILE_H
#define INITIALIZE_FROM_FILE_H

#include <stddef.h> // Defines size_t

/**
 * @brief Read one delimited row from a file and parse as doubles.
 *
 * Given a file path (either absolute or relative to the current working directory),
 * this function reads the specified row, which it assumes is a list of doubles separated by a delimiter,
 * and parses the values into a list of specified variables given as a list of double* pointers
 * terminated with NULL.
 * Example:
 * ```
 *   double a, b;
 *   int count = lf_initialize_double("x.csv", ',', 2, &a, &b, NULL);
 * ```
 * This will read the third row of the file "x.csv" (row numbers start from 0)
 * and parse the values into the variables `a` and `b`.
 *
 * The return value is the number of values parsed (2 in this case), or -1 if an error occurred.
 *
 * To use this in a micro-LF program, include `util/initialize_from_file.cmake` from your
 * project's CMakeLists.txt after `lf_build_generated_code()`. For example:
 * ```cmake
 *   include(${CMAKE_CURRENT_SOURCE_DIR}/util/initialize_from_file.cmake)
 * ```
 * In the `.ulf` file containing a reactor that uses this utility, include the following:
 * ```ulf
 * preamble {=
 *   #include "initialize_from_file.h"
 * =}
 * ```
 *
 * @param filename The name of the file to read.
 * @param delimiter The delimiter character to use.
 * @param row_number The row number in the file to read.
 * @param ... The double* pointers to the variables to store the values in, terminated with NULL.
 * @return The number of values parsed, or -1 if an error occurred.
 */
int lf_initialize_double(const char* filename, char delimiter, size_t row_number, ...);

/**
 * @brief Read one delimited row from a file and parse as integers.
 *
 * Given a file path (either absolute or relative to the current working directory),
 * this function reads the specified row, which it assumes is a list of integers separated by a delimiter,
 * and parses the values into a list of specified variables given as a list of int* pointers
 * terminated with NULL.
 * Example:
 * ```
 *   int a, b;
 *   int count = lf_initialize_int("x.csv", ',', 2, &a, &b, NULL);
 * ```
 * This will read the third row of the file "x.csv" (row numbers start from 0)
 * and parse the values into the variables `a` and `b`.
 *
 * The return value is the number of values parsed (2 in this case), or -1 if an error occurred.
 *
 * To use this in a micro-LF program, include `util/initialize_from_file.cmake` from your
 * project's CMakeLists.txt after `lf_build_generated_code()`. For example:
 * ```cmake
 *   include(${CMAKE_CURRENT_SOURCE_DIR}/util/initialize_from_file.cmake)
 * ```
 * In the `.ulf` file containing a reactor that uses this utility, include the following:
 * ```ulf
 * preamble {=
 *   #include "initialize_from_file.h"
 * =}
 * ```
 * @param filename The name of the file to read.
 * @param delimiter The delimiter character to use.
 * @param row_number The row number in the file to read.
 * @param ... The int* pointers to the variables to store the values in, terminated with NULL.
 * @return The number of values parsed, or -1 if an error occurred.
 */
int lf_initialize_int(const char* filename, char delimiter, size_t row_number, ...);

/**
 * @brief Read one delimited row from a file and parse as strings.
 * 
 * Given a file path (either absolute or relative to the current working directory),
 * this function reads the specified row, which it assumes is a list of strings separated by a delimiter,
 * and parses the values into a list of specified variables given as a list of char** pointers
 * terminated with NULL.
 * Example:
 * ```
 *   char* a;
 *   char* b;
 *   int count = lf_initialize_string("x.csv", ',', 2, &a, &b, NULL);
 * This will read the third row of the file "x.csv" (row numbers start from 0)
 * and parse the values into the variables `a` and `b`.
 * 
 * Memory for each string is allocated with `calloc`. It is the responsibility
 * of the caller to free the strings after use. If the strings set the values of state
 * variables, then the reactor should free the strings in a reaction to `shutdown`.
 * If the strings are sent to other reactors, then those other reactors are
 * responsible for freeing the strings in a reaction to `shutdown`.
 *
 * The return value is the number of values parsed (2 in this case), or -1 if an error occurred.
 *
 * To use this in a micro-LF program, include `util/initialize_from_file.cmake` from your
 * project's CMakeLists.txt after `lf_build_generated_code()`. For example:
 * ```cmake
 *   include(${CMAKE_CURRENT_SOURCE_DIR}/util/initialize_from_file.cmake)
 * ```
 * In the `.ulf` file containing a reactor that uses this utility, include the following:
 * ```ulf
 * preamble {=
 *   #include "initialize_from_file.h"
 * =}
 * ```
 *
 * @param filename The name of the file to read.
 * @param delimiter The delimiter character to use.
 * @param row_number The row number in the file to read.
 * @param ... The char** pointers to the variables to store the values in, terminated with NULL.
 * @return The number of values parsed, or -1 if an error occurred.
 */
int lf_initialize_string(const char* filename, char delimiter, size_t row_number, ...);

#endif // INITIALIZE_FROM_FILE_H
