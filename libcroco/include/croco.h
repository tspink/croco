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

extern int croco_log(log_level_t level, const char *message, ...);

#endif
