
#ifndef TLISP_LOGGING_H
#define TLISP_LOGGING_H

#include <stdio.h>

enum LogType {
    LOG_NONE    = 0,
    LOG_FATAL   = 1,
    LOG_ERROR   = 2,
    LOG_WARN    = 3,
    LOG_MESSAGE = 4
};

extern enum LogType log_level;

/**
 * Initialize the logging file pointers. Since the stdout and stderr FILE *
 * are not constants, it isn't possible to seed the fileout array with their
 * values.
 */
int tlisp_logging_init();

/**
 * Changes the file used to write the given log to.
 * Any opened FILE * passed to this function are the responsibility of the
 * caller to close.
 * If the FILE * is closed, calling the corresponding logging function will
 * (obviously) fail.
 */
void tlisp_log_redirect(enum LogType type, FILE *fp);

/**
 * Writes a formatted log message with automatic prefix.
 */
int tlisp_log(enum LogType type, const char *fmt, ...);
/**
 * Writes a formatted message with the LOG_MESSAGE level and the message
 * prefix.
 */
int tlisp_msg(const char *fmt, ...);
/**
 * Writes a formatted warning with the LOG_WARN level and the warning prefix.
 */
int tlisp_warn(const char *fmt, ...);
/**
 * Writes a formatted error message with the LOG_ERROR level and the error
 * prefix.
 */
int tlisp_error(const char *fmt, ...);
/**
 * Writes a formatted fatal error message with the LOG_FATAL level and the
 * fatal prefix.
 */
int tlisp_fatal(const char *fmt, ...);

#endif
