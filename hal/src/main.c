/*
 * main.c
 *
 * Copyright (C) Catalyst EPS 2013
 * All Rights Reserved
 *
 * Tom Spink <t.spink@betasafe.com>
 */
#include <croco.h>
#include <hal.h>

CMDLINE_OPTION(TYPE_VALUE, config_file, "c", "config", "hal.conf", "Sets the configuration filename.");
CMDLINE_OPTION(TYPE_SWITCH, show_help, "?h", "help", "0", "Displays the help message.");

/**
 * Application entry-point.
 */
int main(int argc, char **argv)
{
	int rc;

	/* Parse the command-line arguments. */
	rc = croco_parse_cmdline(argc, argv);
	if (rc) {
		croco_log(LOG_ERROR, "error parsing command-line");
		return rc;
	}

	/* Print out the welcome banner. */
	printf("CROCO - HAL Service\nCopyright (C) Catalyst EPS 2013 - All Rights Reserved\n\n");

	/* Check to see if the 'show help' command-line option was given. */
	if (show_help[0] == '1') {
		printf("usage: %s [command-line options]\n", argv[0]);
		return 0;
	}

	return 0;
}
