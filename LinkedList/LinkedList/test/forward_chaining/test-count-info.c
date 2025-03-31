/**
 * @file test-count-info.c
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
    FILE *file_rule = NULL;
    file_rule = fopen("example.rule.txt", "r");
    if (file_rule != NULL) {
      int *count = count_info(file_rule);
      assert(count[0] == 14);
      assert(count[1] == 3);
      assert(count[2] == 2);
      assert(count[3] == 0);
      assert(count[40] == 3);
      assert(count[41] == 1);
      free(count);
    }
    fclose(file_rule);
  }
  forward_chaining_finish();
  return 0;
}
