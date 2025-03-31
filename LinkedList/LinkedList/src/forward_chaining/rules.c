/**
 * @file rules.c
 *
 * @author     Groupe K
 * @date       2021
 * @copyright  BSD 3-Clause License
 */

#include <stdlib.h>
#include <string.h>

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>

#include "./forward-chaining.h"

int main(int argc, char const *argv[]) {
  forward_chaining_init();
  {
    if (argc != 7) {
      fprintf(
          stderr,
          "\n\e[31mUsage: %s --rules <rule.txt> --facts <facts.txt> --output "
          "<output.txt>\033[0m\n",
          argv[0]);
      return EXIT_FAILURE;
    }
    int rule_location = 0;
    int facts_location = 0;
    int output_location = 0;
    for (unsigned int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "--rules") == 0) {
        i++;
        rule_location = i;
      }
      if (strcmp(argv[i], "--facts") == 0) {
        i++;
        facts_location = i;
      }
      if (strcmp(argv[i], "--output") == 0) {
        i++;
        output_location = i;
      }
    }

    if (rule_location && facts_location && output_location) {
      Rules *rules = read_rules(argv[rule_location]);
      if (rules != NULL) {
        Facts *facts = read_facts(argv[facts_location]);

        if (facts) {
          if (write_output(argv[output_location],
                           forward_chaining(rules, facts)) == 0) {
            rules_destroy(rules);
            facts_destroy(facts);
            printf("\n\e[32mForward chaining success\033[0m\n");
          } else {
            printf(
                "\n\e[31mForward chaining error:an error occurred while "
                "writing "
                "to the output file\033[0m\n");
            return EXIT_FAILURE;
          }
        } else {
          printf(
              "\n\e[31mForward chaining error : an error occured while reading "
              "the facts\033[0m\n");
          return EXIT_FAILURE;
        }
      } else {
        printf(
            "\n\e[31mForward chaining error : an error occured while reading "
            "the "
            "rules\033[0m\n");
        return EXIT_FAILURE;
      }
    }
  }
  forward_chaining_finish();
  return EXIT_SUCCESS;
}
