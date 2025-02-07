#ifndef _ERROR_FUNCTION_H
#define _ERROR_FUNCTION_H
#include <stdarg.h>
#include <stdbool.h>

void errMessage(const char * format, ...);
void outputError(bool useerror ,int error, bool flushstd,const char * format, va_list ap);

#ifdef _GNUC_
#define NORETURN __attribute__((__noreturn__))
#else
#define NORETURN
#endif

void errExit(const char * format, ...) NORETURN;
void err_exit(const char * format, ...) NORETURN;
void errExitEn(int errnum, const char * format, ...)NORETURN;
void fatal(const char * format, ...) NORETURN;
void usageError(const char * format,...)NORETURN;
void cmdLineErr(const char * format, ...)NORETURN;
#endif