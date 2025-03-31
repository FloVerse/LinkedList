/**
 * @file test-delete-rule.c
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
    Rules *rules;
    rules = read_rules("example.rule.txt");

    assert(rules->rule[0].size_conclusion == 2);
    assert(rules->rule[0].conclusion[1] == 3);

    assert(rules->rule[0].size_premise == 3);
    assert(rules->rule[0].premise[1] == 7);
    delete_rule(rules, 0);

    assert(rules->rule[0].size_conclusion == 1);
    assert(rules->rule[0].conclusion[0] == 24);

    assert(rules->rule[0].size_premise == 3);
    assert(rules->rule[0].premise[0] == 6);

    assert(rules->rule[12].size_conclusion == 2);
    assert(rules->rule[12].conclusion[1] == 2);

    assert(rules->rule[12].size_premise == 3);
    assert(rules->rule[12].premise[2] == 7);
    delete_rule(rules, 11);

    assert(rules->rule[11].size_conclusion == 2);
    assert(rules->rule[11].conclusion[0] == 1);

    assert(rules->rule[11].size_premise == 3);
    assert(rules->rule[11].premise[2] == 7);
    rules_destroy(rules);
  }
  forward_chaining_finish();

  return 0;
}
