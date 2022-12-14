/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _STDLIB_H
#define _STDLIB_H

#include <sys/cdefs.h>
#include <xlocale.h>

#include <alloca.h>
#include <malloc.h>
#include <stddef.h>

__BEGIN_DECLS

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

__noreturn void abort(void);
__noreturn void exit(int);

#if __ANDROID_API__ >= 21
__noreturn void _Exit(int) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */

int atexit(void (*)(void));


#if __ANDROID_API__ >= 21
int at_quick_exit(void (*)(void)) __INTRODUCED_IN(21);
void quick_exit(int) __noreturn __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */


char* getenv(const char*);
int putenv(char*);
int setenv(const char*, const char*, int);
int unsetenv(const char*);
int clearenv(void);

char* mkdtemp(char*);
char* mktemp(char*) __attribute__((deprecated("mktemp is unsafe, use mkstemp or tmpfile instead")));


#if __ANDROID_API__ >= 23
int mkostemp64(char*, int) __INTRODUCED_IN(23);
int mkostemp(char*, int) __INTRODUCED_IN(23);
int mkostemps64(char*, int, int) __INTRODUCED_IN(23);
int mkostemps(char*, int, int) __INTRODUCED_IN(23);
#endif /* __ANDROID_API__ >= 23 */


#if __ANDROID_API__ >= 21
int mkstemp64(char*) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */

int mkstemp(char*);

#if __ANDROID_API__ >= 23
int mkstemps64(char*, int) __INTRODUCED_IN(23);
#endif /* __ANDROID_API__ >= 23 */

int mkstemps(char*, int);

long strtol(const char *, char **, int);
long long strtoll(const char *, char **, int);
unsigned long strtoul(const char *, char **, int);
unsigned long long strtoull(const char *, char **, int);


#if __ANDROID_API__ >= 16
int posix_memalign(void** memptr, size_t alignment, size_t size) __INTRODUCED_IN(16);
#endif /* __ANDROID_API__ >= 16 */


double strtod(const char*, char**);

#if __ANDROID_API__ >= 21
long double strtold(const char*, char**) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */



#if __ANDROID_API__ >= __ANDROID_API_FUTURE__
unsigned long strtoul_l(const char*, char**, int, locale_t) __INTRODUCED_IN_FUTURE;
#endif /* __ANDROID_API__ >= __ANDROID_API_FUTURE__ */


int atoi(const char*) __attribute_pure__;
long atol(const char*) __attribute_pure__;
long long atoll(const char*) __attribute_pure__;

char* realpath(const char* path, char* resolved);
int system(const char* string);

void* bsearch(const void* key, const void* base0, size_t nmemb, size_t size,
              int (*compar)(const void*, const void*));

void qsort(void*, size_t, size_t, int (*)(const void*, const void*));

uint32_t arc4random(void);
uint32_t arc4random_uniform(uint32_t);
void arc4random_buf(void*, size_t);

#define RAND_MAX 0x7fffffff


#if __ANDROID_API__ >= 21
int rand_r(unsigned int*) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */


double drand48(void);
double erand48(unsigned short[3]);
long jrand48(unsigned short[3]);

#if __ANDROID_API__ >= 23
void lcong48(unsigned short[7]) __INTRODUCED_IN(23);
#endif /* __ANDROID_API__ >= 23 */

long lrand48(void);
long mrand48(void);
long nrand48(unsigned short[3]);
unsigned short* seed48(unsigned short[3]);
void srand48(long);


#if __ANDROID_API__ >= 21
char* initstate(unsigned int, char*, size_t) __INTRODUCED_IN(21);
char* setstate(char*) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */


int getpt(void);

#if __ANDROID_API__ >= 21
int posix_openpt(int) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */

char* ptsname(int);
int ptsname_r(int, char*, size_t);
int unlockpt(int);


#if __ANDROID_API__ >= __ANDROID_API_FUTURE__
int getsubopt(char**, char* const*, char**) __INTRODUCED_IN_FUTURE;
#endif /* __ANDROID_API__ >= __ANDROID_API_FUTURE__ */


typedef struct {
    int  quot;
    int  rem;
} div_t;

div_t div(int, int) __attribute_const__;

typedef struct {
    long int  quot;
    long int  rem;
} ldiv_t;

ldiv_t ldiv(long, long) __attribute_const__;

typedef struct {
    long long int  quot;
    long long int  rem;
} lldiv_t;

lldiv_t lldiv(long long, long long) __attribute_const__;

/* BSD compatibility. */

#if __ANDROID_API__ >= 21
const char* getprogname(void) __INTRODUCED_IN(21);
void setprogname(const char*) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */


int mblen(const char*, size_t) __INTRODUCED_IN_FUTURE __VERSIONER_NO_GUARD;
size_t mbstowcs(wchar_t*, const char*, size_t);
int mbtowc(wchar_t*, const char*, size_t) __INTRODUCED_IN(21) __VERSIONER_NO_GUARD;
int wctomb(char*, wchar_t) __INTRODUCED_IN(21) __VERSIONER_NO_GUARD;

size_t wcstombs(char*, const wchar_t*, size_t);

#if __ANDROID_API__ >= __ANDROID_API_L__
size_t __ctype_get_mb_cur_max(void) __INTRODUCED_IN(21);
#define MB_CUR_MAX __ctype_get_mb_cur_max()
#else
/*
 * 4 is only true for UTF-8 locales, but that's what we default to. We'll need
 * the NDK compatibility library to fix this properly.
 */
#define MB_CUR_MAX 4
#endif

#if defined(__BIONIC_FORTIFY)

char* __realpath_real(const char*, char*) __RENAME(realpath);
__errordecl(__realpath_size_error, "realpath output parameter must be NULL or a >= PATH_MAX bytes buffer");

#if !defined(__clang__)
__BIONIC_FORTIFY_INLINE
char* realpath(const char* path, char* resolved) {
    size_t bos = __bos(resolved);

    /* PATH_MAX is unavailable without polluting the namespace, but it's always 4096 on Linux */
    if (bos != __BIONIC_FORTIFY_UNKNOWN_SIZE && bos < 4096) {
        __realpath_size_error();
    }

    return __realpath_real(path, resolved);
}
#endif

#endif /* defined(__BIONIC_FORTIFY) */

#if __ANDROID_API__ >= __ANDROID_API_L__
float strtof(const char*, char**) __INTRODUCED_IN(21);
double atof(const char*) __attribute_pure__ __INTRODUCED_IN(21);
int abs(int) __attribute_const__ __INTRODUCED_IN(21);
long labs(long) __attribute_const__ __INTRODUCED_IN(21);
long long llabs(long long) __attribute_const__ __INTRODUCED_IN(21);
int rand(void) __INTRODUCED_IN(21);
void srand(unsigned int) __INTRODUCED_IN(21);
long random(void) __INTRODUCED_IN(21);
void srandom(unsigned int) __INTRODUCED_IN(21);
int grantpt(int) __INTRODUCED_IN(21);

long long strtoll_l(const char*, char**, int, locale_t) __INTRODUCED_IN(21);
unsigned long long strtoull_l(const char*, char**, int, locale_t) __INTRODUCED_IN(21);
long double strtold_l(const char*, char**, locale_t) __INTRODUCED_IN(21);
#else
// Implemented as static inlines before 21.
#endif

#if __ANDROID_API__ >= __ANDROID_API_FUTURE__
double strtod_l(const char*, char**, locale_t) __INTRODUCED_IN_FUTURE;
float strtof_l(const char*, char**, locale_t) __INTRODUCED_IN_FUTURE;
long strtol_l(const char*, char**, int, locale_t) __INTRODUCED_IN_FUTURE;
#else
// Implemented as static inlines.
#endif

__END_DECLS

#include <android/legacy_stdlib_inlines.h>

#endif /* _STDLIB_H */
