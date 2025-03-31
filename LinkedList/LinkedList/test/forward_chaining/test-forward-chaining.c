/**
 * @file test-forward_chaining.c
 *
 * @author     Groupe K
 * @date 2021
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
    Rules *rules = read_rules("example.rule.txt");
    Facts *facts = read_facts("example.fact.txt");

    char *facts1 = to_string_facts(facts);
    assert(strcmp(facts1, " 1 2 3 4 5 6 7 14 17 45 61 71 2000000\n") == 0);
    facts = forward_chaining(rules, facts);
    char *facts2 = to_string_facts(facts);
    printf("%s", facts2);
    assert(
        strcmp(facts2,
               " 1 2 3 4 5 6 7 8 10 12 14 15 17 24 40 45 61 71 75 2000000\n") ==
        0);
    facts_destroy(facts);
    rules_destroy(rules);
    free(facts1);
    free(facts2);
  }
  forward_chaining_finish();

  return EXIT_SUCCESS;
}
