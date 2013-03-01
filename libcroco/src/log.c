/*
 * log.c
 *
 * Copyright (C) Catalyst EPS 2013
 * All Rights Reserved
 *
 * Tom Spink <t.spink@betasafe.com>
 */
#include <stdio.h>
#include <stdarg.h>
#include <croco.h>

static int submit_log_entry(log_level_t level, const char *message)
{
	const char *level_text;

	switch(level) {
	case LOG_FATAL:
		level_text = "fatal";
		break;

	case LOG_ERROR:
		level_text = "error";
		break;

	case LOG_WARNING:
		level_text = "warning";
		break;

	case LOG_INFO:
		level_text = "info";
		break;

	case LOG_DEBUG1:
	case LOG_DEBUG2:
	case LOG_DEBUG3:
		level_text = "debug";
		break;

	default:
		return -1;
	}

	fprintf(stderr, "%s: %s", level_text, message);
	return 0;
}

int croco_log(log_level_t level, const char *message, ...)
{
	char buffer[512];
	va_list va;

	va_start(va, message);
	vsnprintf(buffer, sizeof(buffer), message, va);
	va_end(va);

	submit_log_entry(level, buffer);
	return 0;
}
