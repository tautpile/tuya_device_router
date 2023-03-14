#include "main.h"

error_t parse_opt (int key, char *arg, struct argp_state *state)
{
        struct arguments *arguments = state->input;

        switch (key)
        {
        case 'd':
                arguments->d = 1;
                break;
        case 'i':
                strcpy(arguments->di, state->argv[state->next]);
                break;
        case 's':
                strcpy(arguments->ds, state->argv[state->next]);
                break;
        case 'p':
                strcpy(arguments->pi, state->argv[state->next]);
                break;

        case ARGP_KEY_ARG:
                if (state->arg_num >= 5)
                argp_usage (state);
                break;

        arguments->args[state->arg_num] = (int)arg;

        break;

        case ARGP_KEY_END:
                if (state->arg_num < 1)
                argp_usage (state);
                break;
        default:
                return ARGP_ERR_UNKNOWN;
        }
        return 0;
}