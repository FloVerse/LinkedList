/**
 * @file test-create-full.c
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
    int *premise = calloc(2, sizeof(unsigned int));
    int *conclusion = calloc(2, sizeof(unsigned int));
    premise[0] = 4;
    premise[1] = 7;
    conclusion[0] = 4;
    conclusion[1] = 2;

    Rule *rule = rule_create_full(premise, 2, conclusion, 2);

    assert((rule->premise)[0] == 4);
    assert((rule->premise)[1] == 7);
    assert((rule->conclusion)[0] == 4);
    assert((rule->conclusion)[1] == 2);
    rule_destroy(*rule);
    free(rule);
  }
  forward_chaining_finish();
  return EXIT_SUCCESS;
}
