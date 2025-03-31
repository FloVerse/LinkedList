/**
 * @file test-read-fact.c
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
    Facts *facts = read_facts("example.fact.txt");
    assert(facts->size == 13);
    assert(facts->fact[0] == 1);
    assert(facts->fact[1] == 2);
    assert(facts->fact[2] == 3);
    assert(facts->fact[3] == 4);
    assert(facts->fact[4] == 5);
    assert(facts->fact[5] == 6);
    assert(facts->fact[6] == 7);
    assert(facts->fact[7] == 14);
    assert(facts->fact[8] == 17);
    assert(facts->fact[9] == 45);
    assert(facts->fact[10] == 61);
    assert(facts->fact[11] == 71);
    facts_destroy(facts);
  }
  forward_chaining_finish();

  return 0;
}
