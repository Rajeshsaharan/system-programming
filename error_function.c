#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "error_function.h"
#include <stdarg.h>
#include <string.h>
#include "ename.h"
#include <errno.h>

void terminate(bool useexit)
{
    char *s;
    s = getenv("EF_DUMPCORE");
    if (s != NULL && *s != '\0')
    {
        abort();
    }
    else if (useexit)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        exit(EXIT_SUCCESS);
    }
}

void outputError(bool useerror, int error, bool flushstd, const char *format, va_list ap)
{
#define BUF_SIZE 500
    char buf[BUF_SIZE], userText[BUF_SIZE], errText[BUF_SIZE];
    vsnprintf(userText, BUF_SIZE, format, ap); // set userMessage
    if (useerror)
    {
        snprintf(errText, BUF_SIZE, "[%s,%s] ", (error > 0 && error < MAX_ENAME) ? ename[error] : "unknown error", strerror(error));
    }
    else
    {
        snprintf(errText, BUF_SIZE, ":");
    }
    snprintf(buf, BUF_SIZE, "ERROR %s,%s\n", errText, userText);
    if (flushstd)
    {
        fflush(stderr);
    }
    fputs(buf, stderr);
    fflush(stderr);
}

void errMessage(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    outputError(true, errno, true, format, args);
    va_end(args);
}

void errExit(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    outputError(true, errno, true, format, args);
    va_end(args);
    terminate(true);
}

void err_exit(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    outputError(true, errno, false, format, args);
    va_end(args);
    terminate(false);
}

void errExitEn(int errnum, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    outputError(true, errnum, true, format, args);
    va_end(args);
    terminate(true);
}

void fatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    outputError(false, 0, true, format, args);
    va_end(args);
    terminate(true);
}

void usageError(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    fprintf(stdout, "usage:");
    vfprintf(stderr, format, args);
    va_end(args);
    fflush(stderr);
    exit(EXIT_FAILURE);
}

void cmdLineErr(const char *format, ...)
{
    va_list argList;
    fflush(stdout); /* Flush any pending stdout */
    fprintf(stderr, "Command-line usage error: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);
    fflush(stderr); /* In case stderr is not line-buffered */
    exit(EXIT_FAILURE);
}