#ifndef TESTS_H
#define TESTS_H

#include <cstddef>

const unsigned int repetitions = 15000; // How many rounds per test?

void launchTests();

// Insertion sort
void insertionTest(size_t size);
void bstTest(size_t size);

#endif // TESTS_H
