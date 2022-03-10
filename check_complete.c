#include <linux/kernel.h>
#include "Funcbalanced.h"
//#include "tinyexpr.h"

asmlinkage long sys_check_complete(char *exp, int *result)
{
    // Declare an empty character stack
    struct sNode* stack = NULL;

    // Traverse the given expression to check matching
    // brackets
    while (*exp != '\0')
    {
        // If the exp[i] is a starting bracket then push
        // it
        if (*exp == '{' || *exp == '(' || *exp == '[')
            push(&stack, *exp);

        // If exp[i] is an ending bracket then pop from
        // stack and check if the popped bracket is a
        // matching pair*/
        if (*exp == '}' || *exp == ')'
            || *exp == ']') {

            // If we see an ending bracket without a pair
            // then return false
            if (stack == NULL)
                return 0;

            // Pop the top element from stack, if it is not
            // a pair bracket of character then there is a
            // mismatch.
            // his happens for expressions like {(})
            else if (!isMatchingPair(pop(&stack), *exp))
                return 0;
        }
        exp++;
    }

    // If there is something left in expression then there
    // is a starting bracket without a closing
    // bracket
    if (stack == NULL)
    {
        //*result = te_interp(x, 0);
        return 1; // balanced
    }
    else
        return 0; // not balanced
}

