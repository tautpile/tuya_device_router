#include <argp.h>

struct arguments {
        char args[3];    /* arg1 & arg2  & arg3 */
        char di[30];    // Device id
        char ds[30];    // Device secret
        char pi[30];    // Product id
        int d;
};

error_t parse_opt (int key, char *arg, struct argp_state *state);
