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

#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <sys/cdefs.h>
#include <sys/types.h>

#include <asm/sigcontext.h>
#include <bits/pthread_types.h>
#include <bits/timespec.h>
#include <limits.h>

#if defined(__LP64__) || defined(__mips__)
/* For 64-bit (and mips), the kernel's struct sigaction doesn't match the POSIX one,
 * so we need to expose our own and translate behind the scenes. */
#  define sigaction __kernel_sigaction
#  include <linux/signal.h>
#  undef sigaction
#else
/* For 32-bit, we're stuck with the definitions we already shipped,
 * even though they contain a sigset_t that's too small. */
#  include <linux/signal.h>
#endif

#include <sys/ucontext.h>
#define __BIONIC_HAVE_UCONTEXT_T

__BEGIN_DECLS

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"
#endif

typedef int sig_atomic_t;

/* The arm and x86 kernel header files don't define _NSIG. */
#ifndef _KERNEL__NSIG
#define _KERNEL__NSIG 64
#endif

/* Userspace's NSIG is the kernel's _NSIG + 1. */
#define _NSIG (_KERNEL__NSIG + 1)
#define NSIG _NSIG

/* The kernel headers define SIG_DFL (0) and SIG_IGN (1) but not SIG_HOLD, since
 * SIG_HOLD is only used by the deprecated SysV signal API.
 */
#define SIG_HOLD __BIONIC_CAST(reinterpret_cast, sighandler_t, 2)

/* We take a few real-time signals for ourselves. May as well use the same names as glibc. */
#define SIGRTMIN (__libc_current_sigrtmin())
#define SIGRTMAX (__libc_current_sigrtmax())

#if __ANDROID_API__ >= 21
int __libc_current_sigrtmin(void) __INTRODUCED_IN(21);
int __libc_current_sigrtmax(void) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */


extern const char* const sys_siglist[_NSIG];
extern const char* const sys_signame[_NSIG]; /* BSD compatibility. */

typedef __sighandler_t sig_t; /* BSD compatibility. */
typedef __sighandler_t sighandler_t; /* glibc compatibility. */

#define si_timerid si_tid /* glibc compatibility. */

#if defined(__LP64__)

struct sigaction {
  unsigned int sa_flags;
  union {
    sighandler_t sa_handler;
    void (*sa_sigaction)(int, struct siginfo*, void*);
  };
  sigset_t sa_mask;
  void (*sa_restorer)(void);
};

#elif defined(__mips__)

struct sigaction {
  unsigned int sa_flags;
  union {
    sighandler_t sa_handler;
    void (*sa_sigaction) (int, struct siginfo*, void*);
  };
  sigset_t sa_mask;
};

#endif

int sigaction(int, const struct sigaction*, struct sigaction*);

int siginterrupt(int, int);

#if __ANDROID_API__ >= __ANDROID_API_L__
sighandler_t signal(int, sighandler_t) __INTRODUCED_IN(21);
int sigaddset(sigset_t*, int) __INTRODUCED_IN(21);
int sigdelset(sigset_t*, int) __INTRODUCED_IN(21);
int sigemptyset(sigset_t*) __INTRODUCED_IN(21);
int sigfillset(sigset_t*) __INTRODUCED_IN(21);
int sigismember(const sigset_t*, int) __INTRODUCED_IN(21);
#else
// Implemented as static inlines before 21.
#endif

int sigpending(sigset_t* _Nonnull);
int sigprocmask(int, const sigset_t*, sigset_t*);
int sigsuspend(const sigset_t* _Nonnull);
int sigwait(const sigset_t* _Nonnull, int* _Nonnull);


#if __ANDROID_API__ >= __ANDROID_API_FUTURE__
int sighold(int)
  __attribute__((deprecated("use sigprocmask() or pthread_sigmask() instead")))
  __INTRODUCED_IN_FUTURE;
int sigignore(int)
  __attribute__((deprecated("use sigaction() instead"))) __INTRODUCED_IN_FUTURE;
int sigpause(int)
  __attribute__((deprecated("use sigsuspend() instead"))) __INTRODUCED_IN_FUTURE;
int sigrelse(int)
  __attribute__((deprecated("use sigprocmask() or pthread_sigmask() instead")))
  __INTRODUCED_IN_FUTURE;
sighandler_t sigset(int, sighandler_t)
  __attribute__((deprecated("use sigaction() instead"))) __INTRODUCED_IN_FUTURE;
#endif /* __ANDROID_API__ >= __ANDROID_API_FUTURE__ */


int raise(int);
int kill(pid_t, int);
int killpg(int, int);

int sigaltstack(const stack_t*, stack_t*);


#if __ANDROID_API__ >= 17
void psiginfo(const siginfo_t*, const char*) __INTRODUCED_IN(17);
void psignal(int, const char*) __INTRODUCED_IN(17);
#endif /* __ANDROID_API__ >= 17 */


int pthread_kill(pthread_t, int);
int pthread_sigmask(int, const sigset_t*, sigset_t*);


#if __ANDROID_API__ >= 23
int sigqueue(pid_t, int, const union sigval) __INTRODUCED_IN(23);
int sigtimedwait(const sigset_t* _Nonnull, siginfo_t*, const struct timespec*) __INTRODUCED_IN(23);
int sigwaitinfo(const sigset_t* _Nonnull, siginfo_t*) __INTRODUCED_IN(23);
#endif /* __ANDROID_API__ >= 23 */


#if defined(__clang__)
#pragma clang diagnostic pop
#endif

__END_DECLS

#include <android/legacy_signal_inlines.h>

#endif /* _SIGNAL_H_ */
