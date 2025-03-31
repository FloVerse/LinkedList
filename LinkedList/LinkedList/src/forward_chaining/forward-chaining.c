/**
 * @file forward_chaining.c
 *
 * @author     Groupe K
 * @date       2021
 *
 * @copyright  BSD 3-Clause License
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./forward-chaining.h"
#include "./forward-chaining.inc"

#define NUMBER_OF_DIGITS 10
// defines the maximum number of digits that a
// number can contain use for to_string

void *(*forward_chaining_malloc)(size_t size) = malloc;
void *(*forward_chaining_realloc)(void *ptr, size_t size) = realloc;
void (*forward_chaining_free)(void *ptr) = free;

static int counter = 0;

bool forward_chaining_init(void) {
  if (!counter++) {
    assert(printf("forward_chaining: initialized\n"));
  }
  return true;
}

bool forward_chaining_finish(void) {
  if (counter) {
    if (!--counter) {
      assert(printf("forward_chaining: finished\n"));
    }
    return true;
  } else {
    return false;
  }
}

void rule_destroy(Rule rule) {
  forward_chaining_free(rule.premise);
  forward_chaining_free(rule.conclusion);
}

void facts_destroy(Facts *fact) {
  forward_chaining_free(fact->fact);
  forward_chaining_free(fact);
}

void rules_destroy(Rules *rules) {
  for (int i = get_number_of_rules(rules) - 1; i >= 0; i--) {
    rule_destroy(rules->rule[i]);
    rules->size--;
  }
  forward_chaining_free(rules->rule);
  if (get_number_of_rules(rules) == 0) {
    forward_chaining_free(rules);
  }
}

unsigned int get_number_of_rules(Rules *rules) { return rules->size; }
Rule *rule_create_full(const unsigned int *premise,
                       const unsigned int premise_number,
                       const unsigned int *conclusion,
                       const unsigned int conclusion_number) {
  Rule *rule = (Rule *)forward_chaining_malloc(  // NOLINT(readability/casting)
      sizeof(Rule));
  if (rule) {
    rule->premise = (unsigned int *)premise;
    if (rule->premise) {
      rule->size_premise = premise_number;
      rule->conclusion = (unsigned int *)conclusion;
      if (rule->conclusion) {
        rule->size_conclusion = conclusion_number;
        return rule;
      }
      forward_chaining_free(rule->conclusion);
    }
    forward_chaining_free(rule->premise);
  }
  forward_chaining_free(rule);
  return NULL;
}

Rules *rules_create(void) { return calloc(1, sizeof(Rules)); }
Facts *facts_create(void) {
  Facts *facts = calloc(1, sizeof(Facts));
  facts->size = 0;
  return facts;
}
int compare_int(const void *pa, const void *pb) {
  return *(int *)pa - *(int *)pb;  // NOLINT(readability/casting)
}

Rules *read_rules(char const *location_rules) {
  FILE *file_rule = NULL;
  file_rule = fopen(location_rules, "r");
  if (file_rule != NULL) {
    unsigned int *rule_info = count_info(file_rule);
    Rules *rules = rules_create();
    rules->size = 0;
    rules->rule = forward_chaining_malloc(rule_info[0] * sizeof(Rule));
    unsigned int error = 0;
    for (unsigned int i = 0; i < rule_info[0]; i++) {
      if (rule_info[(i * 3) + 1] != 0 && rule_info[(i * 3) + 2] != 0) {
        // Check that the conclusion and the
        // premise of the rule contain numbers
        rules->rule[i - error].premise =
            calloc(rule_info[(i * 3) + 1], sizeof(unsigned int));
        rules->rule[i - error].size_premise = rule_info[(i * 3) + 1];
        rules->rule[i - error].conclusion =
            calloc(rule_info[(i * 3) + 2], sizeof(unsigned int));
        rules->rule[i - error].size_conclusion = rule_info[(i * 3) + 2];
        for (unsigned int j = 0; j < rule_info[(i * 3) + 1]; j++) {
          fscanf(file_rule, "%d", rules->rule[i - error].premise + j);
        }
        qsort(rules->rule[i - error].premise,
              rules->rule[i - error].size_premise,
              sizeof(rules->rule[i - error].premise[0]), compare_int);
        for (unsigned int j = 0; j < rule_info[(i * 3) + 2]; j++) {
          fscanf(file_rule, "%d", rules->rule[i - error].conclusion + j);
        }
        qsort(rules->rule[i - error].conclusion,
              rules->rule[i - error].size_conclusion,
              sizeof(rules->rule[i - error].conclusion[0]), compare_int);
        rules->size++;
      } else {
        error++;
        printf(
            "\e[31m Warning : the rule number %d which normaly starts at line "
            "%d does not respect the formatting please check it\033[0m\n",
            i + 1, i * 3 + 1);
      }
    }
    if (error != 0) {
      printf(
          "\e[31m Warning : %d rules are not well formatted the program "
          "continues but does not take them into account \033[0m\n",
          error);
    }

    fclose(file_rule);
    forward_chaining_free(rule_info);
    return rules;
  }
  return NULL;
}

bool delete_rule(Rules *rules, int position) {
  if (position < 0) {
    position = position + rules->size + 1;
  }

  if (position < get_number_of_rules(rules)) {
    unsigned int last_postition = get_number_of_rules(rules) - 1;

    if (position != last_postition) {
      rules->rule[position].conclusion = forward_chaining_realloc(
          rules->rule[position].conclusion,
          sizeof(unsigned int) * rules->rule[last_postition].size_conclusion);
      memmove(
          rules->rule[position].conclusion,
          rules->rule[last_postition].conclusion,
          sizeof(unsigned int) * rules->rule[last_postition].size_conclusion);
      rules->rule[position].size_conclusion =
          rules->rule[last_postition].size_conclusion;

      rules->rule[position].premise = forward_chaining_realloc(
          rules->rule[position].premise,
          sizeof(unsigned int) * rules->rule[last_postition].size_premise);
      memmove(rules->rule[position].premise,
              rules->rule[last_postition].premise,
              sizeof(unsigned int) * rules->rule[last_postition].size_premise);
      rules->rule[position].size_premise =
          rules->rule[last_postition].size_premise;
    }
    rule_destroy(rules->rule[last_postition]);
    rules->size--;
    rules->rule =
        (Rule *)forward_chaining_realloc(  // NOLINT(readability/casting)
            rules->rule, (sizeof(Rule) * (get_number_of_rules(rules) + 1)));
    return true;
  } else {
    return false;
  }
}

unsigned int *count_info(FILE *file) {
  unsigned int *file_informations =
      (unsigned int *)calloc(2, sizeof(unsigned int));
  rewind(file);
  char character = fgetc(file);
  rewind(file);
  while (character != EOF) {
    character = fgetc(file);
    if (character >= '0' && character <= '9') {
      while (character >= '0' && character <= '9') {
        character = fgetc(file);
      }
      file_informations[file_informations[0] + 1]++;
    }
    if (character == '\n' || character == '\r' || character == ' ') {
      if (character == '\r') {
        character = fgetc(file);
      }
      if (character == '\n') {
        file_informations[0]++;
        file_informations = forward_chaining_realloc(
            file_informations,
            sizeof(unsigned int) * (file_informations[0] + 2));
        file_informations[file_informations[0] + 1] = 0;
      }
    }
    if (character != ' ' && character != '\n' && character != '\r' &&
        !(character >= '0' && character <= '9') && character != -1) {
      // Checks if the character is an authorized character in the
      // file otherwise it returns an error and stops the program
      fwrite(
          "\e[31mYour file does not match the required formatting please refer "
          "to the documentation for more information\033[0m",
          sizeof(""), 113, stderr);
      exit(1);
    }
  }
  rewind(file);

  file_informations[0] /= 3;
  file_informations[0] += 1;
  return file_informations;
}

Facts *read_facts(char const *location_facts) {
  FILE *file_fact = NULL;
  file_fact = fopen(location_facts, "r");
  if (file_fact != NULL) {
    unsigned int *fact_info = count_info(file_fact);
    Facts *facts = facts_create();
    unsigned int number;
    facts->fact = calloc(fact_info[1], sizeof(unsigned int));
    for (unsigned int i = 0; i < fact_info[1]; i++) {
      fscanf(file_fact, " %d", &(number));
      facts->size++;
      facts->fact[facts->size - 1] = number;
    }

    qsort(facts->fact, facts->size, sizeof(facts->fact[0]), compare_int);
    for (int i = 1; i < facts->size; i++) {
      if (facts->fact[i - 1] == facts->fact[i]) {
        // check if the fact is already present in the facts
        // checks if the fact is already present in the facts
        // if so it removes it
        i--;
        facts->size--;
        memmove(facts->fact + i, facts->fact + i + 1,
                sizeof(unsigned int) * ((facts->size) - i));
      }
    }
    if (facts->size != fact_info[1]) {
      // if a fact has been removed a new allocation is made
      facts->fact = forward_chaining_realloc(
          facts->fact, facts->size * sizeof(unsigned int));
    }
    fclose(file_fact);
    forward_chaining_free(fact_info);

    return facts;
  }
  return NULL;
}

bool *write_output(char const *location_output, Facts *facts) {
  FILE *file = NULL;
  file = fopen(location_output, "w");
  if (file != NULL) {
    char *fact = to_string_facts(facts);
    fputs(fact, file);
    forward_chaining_free(fact);
    fclose(file);
  } else {
    return false;
  }
}

char *to_string_rule(Rule rule) {
  char *string =
      (char *)forward_chaining_malloc(  // NOLINT(readability/casting)
          sizeof("Premise =\nConclusion =\n") +
          (rule.size_premise + rule.size_conclusion) * sizeof(char) *
              (NUMBER_OF_DIGITS + 1));
  unsigned int cursor = 0;
  cursor += snprintf(string + cursor, sizeof("Premise ="), "Premise =");
  char number[NUMBER_OF_DIGITS];

  for (unsigned int i = 0; i < rule.size_premise; i++) {
    cursor +=
        snprintf(string + cursor, NUMBER_OF_DIGITS, " %d", rule.premise[i]);
  }
  cursor +=
      snprintf(string + cursor, sizeof("\nConclusion ="), "\nConclusion =");
  for (unsigned int i = 0; i < rule.size_conclusion; i++) {
    cursor +=
        snprintf(string + cursor, NUMBER_OF_DIGITS, " %d", rule.conclusion[i]);
  }
  snprintf(string + cursor, sizeof(string), "\n");
  return string;
}

char *to_string_rules(Rules *rules) {
  char *string =
      (char *)forward_chaining_malloc(  // NOLINT(readability/casting)
          sizeof("Premise =\nConclusion =\n") +
          (rules->rule[0].size_premise + rules->rule[0].size_conclusion) *
              sizeof(char) * (NUMBER_OF_DIGITS + 1));
  unsigned int size = 0;
  for (unsigned int i = 0; i < rules->size; i++) {
    size += sizeof("Premise =\nConclusion =\n") +
            (rules->rule[i].size_premise + rules->rule[i].size_conclusion) *
                sizeof(char) * (NUMBER_OF_DIGITS + 1);
  }
  string = forward_chaining_realloc(string, size);
  unsigned int cursor = 0;
  for (unsigned int i = 0; i < rules->size; i++) {
    char *rule = to_string_rule(rules->rule[i]);
    cursor += snprintf(string + cursor, strlen(rule), "%s", rule);
    forward_chaining_free(rule);
  }
  return string;
}

char *to_string_facts(Facts *facts) {
  char *string =
        (char *)forward_chaining_malloc(  // NOLINT(readability/casting)
        facts->size *sizeof(char)
        * (NUMBER_OF_DIGITS + 1));
  char number[NUMBER_OF_DIGITS];
  unsigned int cursor = 0;
  for (unsigned int i = 0; i < facts->size; i++) {
    cursor += snprintf(string + cursor, NUMBER_OF_DIGITS * facts->size, " %d",
                       facts->fact[i]);
  }
  snprintf(string + cursor, sizeof(string), "\n");
  return string;
}

Facts *forward_chaining(Rules *rules, Facts *facts) {
  int i = 0;
  unsigned int j;
  unsigned int k;
  bool start_again = false;

  while (i < get_number_of_rules(rules)) {
    j = 0;
    while (j < rules->rule[i].size_premise &&
           bsearch(&(rules->rule[i].premise[j]), facts->fact, facts->size,
                   sizeof(unsigned int), compare_int)) {
      // check if the i th value is present in the rule
      j++;
      if (j == rules->rule[i].size_premise) {
        for (k = 0; k < rules->rule[i].size_conclusion; k++) {
          if (!bsearch(&(rules->rule[i].conclusion[k]), facts->fact,
                       facts->size, sizeof(unsigned int), compare_int)) {
            // check if the fact does not already exist
            // otherwise it is added to the facts
            facts->fact = forward_chaining_realloc(
                facts->fact, (facts->size + 1) * sizeof(unsigned int));
            facts->fact[facts->size] = rules->rule[i].conclusion[k];
            facts->size++;
            qsort(facts->fact, facts->size, sizeof(facts->fact[0]),
                  compare_int);
          }
        }
        delete_rule(rules, i);
        start_again = true;
      }
    }
    if (start_again) {
      start_again = false;
      i = 0;
    } else {
      i++;
    }
  }
  return facts;
}
