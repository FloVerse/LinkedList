/**
 * @file test-read-rule.c
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
    Rules *rules = read_rules("example.rule.txt");
    assert(get_number_of_rules(rules) == 14);
    assert(rules->rule[0].premise[0] == 5);
    assert(rules->rule[0].size_premise == 3);
    assert(rules->rule[0].conclusion[0] == 1);
    assert(rules->rule[0].size_conclusion == 2);
    assert(rules->rule[13].premise[2] == 8);
    assert(rules->rule[13].size_premise == 3);
    assert(rules->rule[13].conclusion[0] == 24);
    assert(rules->rule[13].size_conclusion == 1);
    rules_destroy(rules);
  }
  forward_chaining_finish();

  return 0;
}
