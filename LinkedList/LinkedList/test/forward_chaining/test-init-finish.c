/**
 * @file test-forward_chaining.c
 *
 * @author     Groupe K
 * @date 2021
 *
 * @copyright  BSD 3-Clause License
 */

#include <stdlib.h>

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>

#include <forward-chaining.h>
#include <forward-chaining.inc>

int main(void) {
  assert(forward_chaining_init());
  assert(forward_chaining_init());
  assert(forward_chaining_init());
  assert(forward_chaining_finish());
  assert(forward_chaining_finish());
  assert(forward_chaining_finish());
  assert(!forward_chaining_finish());

  return EXIT_SUCCESS;
}
