/**
 * @file test-qsort.c
 *
 * @author     Groupe K
 * @date       2021
 *
 * @copyright  BSD 3-Clause License
 */

#include <stdlib.h>
#include <string.h>

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>

#include <forward-chaining.h>
#include <forward-chaining.inc>

int main(void) {
  forward_chaining_init();
  {
    unsigned int values[] = {7, 8, 3, 4, 70, 6, 15, 13, 17, 21, 81, 42, 2};
    qsort(values, 13, sizeof *values, compare_int);
    assert(values[0] == 2);
    assert(values[1] == 3);
    assert(values[2] == 4);
    assert(values[3] == 6);
    assert(values[4] == 7);
    assert(values[5] == 8);
    assert(values[6] == 13);
    assert(values[7] == 15);
    assert(values[8] == 17);
    assert(values[9] == 21);
    assert(values[10] == 42);
    assert(values[11] == 70);
    assert(values[12] == 81);
  }
  forward_chaining_finish();

  return EXIT_SUCCESS;
}
