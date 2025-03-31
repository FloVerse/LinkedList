/**
 * @file test-rules-create-full.c
 *
 * @author     Groupe K
 * @date       2021
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
  forward_chaining_init();
  {
    Rules *rules = rules_create();
    assert(get_number_of_rules(rules) == 0);
    unsigned int *premise = calloc(2, sizeof(unsigned int));
    unsigned int *conclusion = calloc(2, sizeof(unsigned int));
    premise[0] = 4;
    premise[1] = 7;
    conclusion[0] = 4;
    conclusion[1] = 2;
    rules->rule = malloc(sizeof(Rule));
    rules->size = 0;
    Rule *rule = rule_create_full(premise, 2, conclusion, 2);
    rules->rule[0] = *rule;
    rules->size++;
    assert(get_number_of_rules(rules) == 1);
    assert((rules->rule[0].premise)[0] == 4);
    assert((rules->rule[0].premise)[1] == 7);
    assert((rules->rule[0].conclusion)[0] == 4);
    assert((rules->rule[0].conclusion)[1] == 2);
    free(rule);
    rules_destroy(rules);
  }
  forward_chaining_finish();

  return 0;
}
