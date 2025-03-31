/**
 * @file test-write-output.c
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
    char *facts1 = to_string_facts(facts);
    assert(strcmp(facts1, " 1 2 3 4 5 6 7 14 17 45 61 71 2000000\n") == 0);
    write_output("example.output.txt", facts);
    facts_destroy(facts);
    facts = read_facts("example.output.txt");
    char *facts2 = to_string_facts(facts);
    assert(strcmp(facts2, " 1 2 3 4 5 6 7 14 17 45 61 71 2000000\n") == 0);
    free(facts1);
    free(facts2);
    facts_destroy(facts);
  }
  forward_chaining_finish();
  return EXIT_SUCCESS;
}
