/* Test program taken from the geresh configure.in test of fribidi, this is the
 * program that exposed the problem.
 */

#include <stdio.h>

#include "fribidi.h"

typedef FriBidiChar     unichar;
typedef FriBidiCharType ctype_t;
typedef FriBidiLevel    level_t;
typedef FriBidiStrIndex idx_t;

int main()
{
    unichar unistr[] = { 0x5D0, 0x5D1, 0x5D2, 'A', 0 }; /* alef, bet, gimel, 'A' */
#define UNISTRLEN 4
    level_t levels[UNISTRLEN];
    unichar deststr[UNISTRLEN + 1];
    ctype_t ctype;
    ctype_t base_dir = FRIBIDI_TYPE_RTL;
    unichar lparen = '(';
    unichar lparen_mirror;

    /* make sure all these constants are defined. */
    ctype = FRIBIDI_TYPE_LTR | FRIBIDI_TYPE_RTL | FRIBIDI_TYPE_ON | FRIBIDI_TYPE_NSM;

    if (sizeof(unichar) != 4) {
        printf("\nERROR: FriBiDi doesn't use UCS-4\n");
        /* I'm planning support for 16 bit chars someday. */
        return 1;
    }

    ctype = fribidi_get_type(unistr[0]);
    if (!FRIBIDI_IS_LETTER(ctype) ||
        !FRIBIDI_IS_RTL(ctype) ||
        FRIBIDI_IS_SPACE(ctype) ||
        FRIBIDI_IS_NUMBER(ctype))
    {
        printf("\nERROR: Wrong properties for the Hebrew letter Alef\n");
        return 1;
    }

    fribidi_log2vis_get_embedding_levels(unistr, UNISTRLEN, &base_dir, levels);
    if (levels[0] != 1 ||
        levels[1] != 1 ||
        levels[2] != 1 ||
        levels[3] != 2)
    {
        printf("\nERROR: fribidi_log2vis_get_embedding_levels() "
                            "gives wrong results\n");
        return 1;
    }

    fribidi_log2vis(unistr, UNISTRLEN, &base_dir, deststr, NULL, NULL, NULL);
    if (deststr[0] != 'A' ||
        deststr[1] != 0x5D2 ||
        deststr[2] != 0x5D1 ||
        deststr[3] != 0x5D0)
    {
        printf("\nERROR: fribidi_log2vis() gives wrong results\n");
        return 1;
    }
    
    if (!fribidi_get_mirror_char(lparen, &lparen_mirror) ||
        lparen_mirror != ')')
    {
        printf("\nERROR: fribidi_get_mirror_char() gives wrong results\n");
        return 1;
    }

    return 0;
}
