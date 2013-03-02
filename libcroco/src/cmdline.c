#include <croco.h>
#include <string.h>

static struct croco_cmdline_option *find_short_option(char opt)
{
	struct croco_cmdline_option **opts = (struct croco_cmdline_option **)&__cmdline_opt_ptr_start;
	char opt_nt[2];

	/* Hackery to get strstr to work, as it needs a null-terminated string, and we're only
	 * passing in a char. */
	opt_nt[0] = opt;
	opt_nt[1] = 0;

	/* Loop through each command-line descriptor. */
	while (opts < (struct croco_cmdline_option **)&__cmdline_opt_ptr_end) {
		/* If the supplied option matches any part of the short argument list, then we've got
		 * a matching descriptor. */
		if (strstr((*opts)->opt_short, opt_nt))
			return *opts;
		opts++;
	}

	return NULL;
}

static struct croco_cmdline_option *find_long_option(char *opt)
{
	struct croco_cmdline_option **opts = (struct croco_cmdline_option **)&__cmdline_opt_ptr_start;

	/* Loop through each command-line descriptor. */
	while (opts < (struct croco_cmdline_option **)&__cmdline_opt_ptr_end) {
		/* If the long argument matches the supplied argument, then we've found a matching
		 * descriptor, so return it. */
		if (strcmp((*opts)->opt_long, opt) == 0)
			return *opts;
		opts++;
	}

	return NULL;
}

static void load_cmdline_defaults()
{
	struct croco_cmdline_option **opts = (struct croco_cmdline_option **)&__cmdline_opt_ptr_start;

	/* Loop through each command-line descriptor. */
	while (opts < (struct croco_cmdline_option **)&__cmdline_opt_ptr_end) {
		*(*opts)->opt_storage = (char *)(*opts)->opt_def; /* Store the default value in the storage location. */
		opts++;
	}
}

/**
 * Reads the command-line arguments, and loads the values into the
 * defined buffers.
 */
int croco_parse_cmdline(int argc, char **argv)
{
	int i;

	/* Load the command-line default values. */
	load_cmdline_defaults();

	/* Loop through each arguments (except the first) */
	for (i = 1; i < argc; i++) {
		struct croco_cmdline_option *opt = NULL;

		/* Check to see if the argument is a switch. */
		if (argv[i][0] == '-') {
			/* Check to see if the argument is a long or short switch. */
			if (argv[i][1] == '-') {
				opt = find_long_option(&argv[i][2]);
			} else {
				/* TODO: Make this work for multiple short arguments in one command. */
				opt = find_short_option(argv[i][1]);
			}
		}

		/* If no option descriptor was found, then it's an unrecognised command-line option. */
		if (!opt) {
			croco_log(LOG_ERROR, "unrecognised command-line option: %s", argv[i]);
			return -1;
		}

		/* Determine what the type of the option is.  If it's a switch, a boolean
		 * result will be stored - if it's a value, the next argument will be 
		 * consumed and stored as the value. */
		if (opt->opt_type == TYPE_SWITCH) {
			*opt->opt_storage = "1"; /* If the switch is present, then set the value to '1' to indicate true. */
		} else if (opt->opt_type == TYPE_VALUE) {
			/* Increment the argument index. */
			i++;

			/* Check to see if we've gone past the end of the supplied arguments. */
			if (i >= argc) {
				croco_log(LOG_ERROR, "ran out of command-line arguments whilst parsing option %s", argv[i-1]);
				return -1;
			}

			/* Store the value of the argument. */
			*opt->opt_storage = argv[i];
		}
	}

	return 0;
}
