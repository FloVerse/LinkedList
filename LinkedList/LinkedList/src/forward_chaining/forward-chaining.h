/**
 * @file forward_chaining.h
 *
 * @author     Groupe K
 * @date       2021
 *
 * @copyright  BSD 3-Clause License
 */

#ifndef FORWARD_CHAINING_H_
#define FORWARD_CHAINING_H_

#include <stdbool.h>
#include <stdio.h>

typedef struct _Rules Rules;
typedef struct _Rule Rule;
typedef struct _Facts Facts;

/**
 * forward_chaining_init initializes the number of forward chaining
 *
 *
 *
 * @param void
 *
 * @return a boolean
 *
 *
 */
bool forward_chaining_init(void);

/**
 * forward_chaining_finish initializes the number of forward chaining
 *
 *
 *
 * @param void
 *
 * @return a boolean
 *
 *
 */
bool forward_chaining_finish(void);

/**
 * forward_chaining compares the facts with the rules, and modify the facts
 * array.
 *
 * @param rules a Rules array
 * @param facts a Facts array
 *
 * @return a pointer to a sorted facts array
 *
 * @note removes duplicates facts, and both parameters are modified by this
 * function
 */
extern Facts *forward_chaining(Rules *rules, Facts *facts);

/**
 * rule_create_full creates a rule and fills its attributes.
 *
 * @param premise array of unsigned integers
 * @param premise_number size of the premise array
 * @param conclusion array of unsigned integers
 * @param conclusion_number size of the conclusion array
 *
 * @return a pointer to a Rule structure
 */
extern Rule *rule_create_full(const unsigned int *premise,
                              const unsigned int premise_number,
                              const unsigned int *conclusion,
                              const unsigned int conclusion_number);

/**
 * facts_create creates a Facts structure and allocates memory for it.
 *
 * @return a pointer to a Facts structure
 *
 * @note remove duplicates
 */
extern Facts *facts_create(void);

/**
 * rules_create creates a Rules structure and allocates memory for it.
 *
 * @return a pointer to a Rule structure
 */
extern Rules *rules_create(void);

/**
 * rule_destroy frees the memory that was taken by a Rule structure.
 *
 * @param rule the rule that should be freed
 *
 * @return void
 */
extern void rule_destroy(Rule rule);

/**
 * rules_destroy frees the memory that was taken by a Rules structure and by the
 * Rule array.
 *
 * @param rules the rules structure that should be freed
 *
 * @return void
 */
extern void rules_destroy(Rules *rules);

/**
 * facts_destroy frees the memory that was taken by a Facts structure and by the
 * fact array.
 *
 * @param fact a Fact structure
 *
 * @return void
 */
extern void facts_destroy(Facts *fact);

/**
 * read_rules reads a file with rules written in it and put them in a Rules
 * structure.
 *
 * @param location_rules a file
 *
 * @return a pointer to a Rules structure
 *
 * @note file needs to be formatted like this : premise1 premise2 ..
 * premisen\nconclusion1 conlusion2 .. conclusionn\n\n and so on.
 */
extern Rules *read_rules(char const *location_rules);

/**
 * read_facts reads a file with facts written in it and put them in a Facts
 * structure.
 *
 * @param location_facts a file
 *
 * @return a pointer to a Facts structure
 *
 * @note file needs to be formatted like this : premise1 premise2 .. premisen
 */
extern Facts *read_facts(char const *location_facts);

/**
 * write_output writes the facts from the Facts structure on the output file.
 *
 * @param location_output the output file
 * @param facts the Facts structure
 *
 * @return a boolean
 *
 * @note the location_ouput file is created if needed, and overriden if it
 * already exists.
 */
extern bool *write_output(char const *location_output, Facts *facts);

/**
 * count_info counts the number of int of each lines and write them in an array
 * of unsigned int.
 *
 * @param file a file containing numbers
 *
 * @return a pointer to an unsigned int array
 *
 * @note first element of the array is the number of rules in the file, and the
 * second element is the number of int for each line
 */
extern unsigned int *count_info(FILE *file);

/**
 * getNumberOfRules returns the number of rules.
 *
 * @param rules a pointer to a Rules structure
 *
 * @return an unsigned integer
 */
extern unsigned int get_number_of_rules(Rules *rules);

/**
 * deleteRule deletes a rule at a defined position.
 *
 * @param rules a pointer to a Rules structure
 * @param position an int indicating the position of the rule you want to
 * delete
 *
 * @return a boolean
 *
 * @note the boolean indicates whether of not the suppression of the rule has
 * worked
 */
extern bool delete_rule(Rules *rules, int position);

/**
 * toString_Rule convert the content of a rule in a string
 *
 * @param rule a Rule structure
 *
 * @return a pointer to a string
 */
extern char *to_string_rule(Rule rule);
/**
 * toString_Rules convert all list of rules into  string
 *
 * @param rule a Rule structure
 *
 * @return a pointer to a string
 */
extern char *to_string_rules(Rules *rules);
/**
 * toString_Fact, convert the content of a fact in a string
 *
 * @param facts a Facts structure
 *
 * @return pointer to a string
 */
extern char *to_string_facts(Facts *facts);

/**
 * compare_int returns an int greater than 0 if the first parameter is greater
 * than the second, otherwise it returns an int lower than 0 if it's the
 * opposite, or 0 if they are equals
 *
 * @param pa a pointer on a (an int)
 * @param pb a pointer on b (an int)
 *
 * @return an int
 */
extern int compare_int(const void *pa, const void *pb);

#endif  // FORWARD_CHAINING_H_
