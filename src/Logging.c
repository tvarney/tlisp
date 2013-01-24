
#include "Logging.h"

#include <stdarg.h>

/**
 * The initial elements of these arrays should be NULL, as the logging level of
 * 0 indicates that no logging should be done at all.
 */
static const char *prefix[] = {
    NULL,
    "[FATAL] :",
    "[ERROR] :",
    "[WARN] :",
    "[MESSAGE] :",
};
static FILE *outfile[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

enum LogType log_level = LOG_MESSAGE;

int
tlisp_logging_init()
{
    outfile[LOG_FATAL] = stderr;
    outfile[LOG_ERROR] = stderr;
    outfile[LOG_WARN] = stderr;
    outfile[LOG_MESSAGE] = stdout;
    
    return 1;
}

void
tlisp_log_redirect(enum LogType type, FILE *fp)
{
    if(type > LOG_MESSAGE) {
        return;
    }
    
    outfile[type] = fp;
}

/* The method that does the actual work. Since this exposes things that we
 * don't want to expose (the prefix and the va_list), it is ONLY defined in
 * this file.
 * NOTE: this method doesn't check the logging level.
 */
int
vlogf(FILE *fp, const char *prefix, const char *fmt, va_list vargs)
{
    /* Both fputs and vfprintf return the number of characters written,
     * so to do the same we just need to add the results of calling both
     */
    return fputs(prefix, fp) + vfprintf(fp, fmt, vargs);
}

int
tlisp_log(enum LogType type, const char *fmt, ...)
{
    va_list vargs;
    int rval;
    
    rval = -1;
    /* Bounds checking and level check done here. */
    if((type <= LOG_MESSAGE) && (type <= log_level)) {
        va_start(vargs, fmt);
        rval = vlogf(outfile[type], prefix[type], fmt, vargs);
        va_end(vargs);
    }
    return rval;
}

int
tlisp_msg(const char *fmt, ...)
{
    va_list vargs;
    int rval;
    
    rval = -1;
    if(log_level >= LOG_MESSAGE) {
        va_start(vargs, fmt);
        rval = vlogf(outfile[LOG_MESSAGE], prefix[LOG_MESSAGE], fmt, vargs);
        va_end(vargs);
    }
    return rval;
}

int
tlisp_warn(const char *fmt, ...)
{
    va_list vargs;
    int rval;
    
    rval = -1;
    if(log_level >= LOG_WARN) {
        va_start(vargs, fmt);
        rval = vlogf(outfile[LOG_WARN], prefix[LOG_WARN], fmt, vargs);
        va_end(vargs);
    }
    return rval;
}

int
tlisp_error(const char *fmt, ...)
{
    va_list vargs;
    int rval;
    
    rval = -1;
    if(log_level >= LOG_ERROR) {
        va_start(vargs, fmt);
        rval = vlogf(outfile[LOG_ERROR], prefix[LOG_ERROR], fmt, vargs);
        va_end(vargs);
    }
    return rval;
}

int
tlisp_fatal(const char *fmt, ...)
{
    va_list vargs;
    int rval;
    
    rval = -1;
    if(log_level >= LOG_FATAL) {
        va_start(vargs, fmt);
        rval = vlogf(outfile[LOG_FATAL], prefix[LOG_FATAL], fmt, vargs);
        va_end(vargs);
    }
    return rval;
}
