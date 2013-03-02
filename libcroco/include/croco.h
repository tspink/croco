#ifndef __CROCO_H__
#define __CROCO_H__

typedef enum _log_level {
	LOG_FATAL,
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG1,
	LOG_DEBUG2,
	LOG_DEBUG3
} log_level_t;

extern int croco_log(log_level_t level, char *message, ...);

/*
 * Command-line Parsing
 */
typedef enum _opt_type {
	TYPE_SWITCH,
	TYPE_VALUE,
} opt_type_t;

struct croco_cmdline_option {
	const char *opt_short;
	const char *opt_long;
	const char *opt_def;
	const char *opt_desc;
	opt_type_t opt_type;
	char **opt_storage;
};

#define CMDLINE_OPTION(t,var,s,l,def,desc) static char * var; \
	const static struct croco_cmdline_option __cmdline_opt__##var __attribute__((section (".cmdline_opt"))) = { \
		.opt_type = t, \
		.opt_short = s, \
		.opt_long = l, \
		.opt_def = def, \
		.opt_desc = desc, \
		.opt_storage = &var \
	}; \
	const static struct croco_cmdline_option * __cmdline_opt_ptr_##var __attribute__((used)) __attribute__((section (".cmdline_opt_ptr"))) = &__cmdline_opt__##var

extern void *__cmdline_opt_start;
extern void *__cmdline_opt_size;
extern void *__cmdline_opt_end;
extern void *__cmdline_opt_ptr_start;
extern void *__cmdline_opt_ptr_size;
extern void *__cmdline_opt_ptr_end;

extern int croco_parse_cmdline(int argc, char **argv);

#endif
