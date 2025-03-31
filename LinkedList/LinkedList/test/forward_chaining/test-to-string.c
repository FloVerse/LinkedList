/**
 * @file test-to-string.c
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
    char *rule0 = to_string_rule(rules->rule[0]);  // rule of index 0
    printf("%s", rule0);
    char *rule13 = to_string_rule(rules->rule[13]);
    printf("%s", rule13);
    assert(strcmp(rule0, "Premise = 5 7 45\nConclusion = 1 3\n") == 0);
    assert(strcmp(rule13, "Premise = 6 7 8\nConclusion = 24\n") == 0);
    free(rule0);
    free(rule13);
    rules_destroy(rules);
  }
  forward_chaining_finish();

  return EXIT_SUCCESS;
}
