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

#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#include <bits/timespec.h>
#include <linux/stat.h>
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

#if defined(__aarch64__) || (defined(__mips__) && defined(__LP64__))
#define __STAT64_BODY \
  dev_t st_dev; \
  ino_t st_ino; \
  mode_t st_mode; \
  nlink_t st_nlink; \
  uid_t st_uid; \
  gid_t st_gid; \
  dev_t st_rdev; \
  unsigned long __pad1; \
  off_t st_size; \
  int st_blksize; \
  int __pad2; \
  long st_blocks; \
  struct timespec st_atim; \
  struct timespec st_mtim; \
  struct timespec st_ctim; \
  unsigned int __unused4; \
  unsigned int __unused5; \

#elif defined(__mips__) && !defined(__LP64__)
#define __STAT64_BODY \
  unsigned int st_dev; \
  unsigned int __pad0[3]; \
  unsigned long long st_ino; \
  mode_t st_mode; \
  nlink_t st_nlink; \
  uid_t st_uid; \
  gid_t st_gid; \
  unsigned int st_rdev; \
  unsigned int __pad1[3]; \
  long long st_size; \
  struct timespec st_atim; \
  struct timespec st_mtim; \
  struct timespec st_ctim; \
  unsigned int st_blksize; \
  unsigned int __pad2; \
  unsigned long long st_blocks; \

#elif defined(__x86_64__)
#define __STAT64_BODY \
  dev_t st_dev; \
  ino_t st_ino; \
  unsigned long st_nlink; \
  mode_t st_mode; \
  uid_t st_uid; \
  gid_t st_gid; \
  unsigned int __pad0; \
  dev_t st_rdev; \
  off_t st_size; \
  long st_blksize; \
  long st_blocks; \
  struct timespec st_atim; \
  struct timespec st_mtim; \
  struct timespec st_ctim; \
  long __pad3[3]; \

#else /* __arm__ || __i386__ */
#define __STAT64_BODY \
  unsigned long long st_dev; \
  unsigned char __pad0[4]; \
  unsigned long __st_ino; \
  unsigned int st_mode; \
  nlink_t st_nlink; \
  uid_t st_uid; \
  gid_t st_gid; \
  unsigned long long st_rdev; \
  unsigned char __pad3[4]; \
  long long st_size; \
  unsigned long st_blksize; \
  unsigned long long st_blocks; \
  struct timespec st_atim; \
  struct timespec st_mtim; \
  struct timespec st_ctim; \
  unsigned long long st_ino; \

#endif

struct stat { __STAT64_BODY };
struct stat64 { __STAT64_BODY };

#undef __STAT64_BODY

/* Compatibility with older versions of POSIX. */
#define st_atime st_atim.tv_sec
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
/* Compatibility with glibc. */
#define st_atimensec st_atim.tv_nsec
#define st_mtimensec st_mtim.tv_nsec
#define st_ctimensec st_ctim.tv_nsec

#if defined(__USE_BSD)
/* Permission macros provided by glibc for compatibility with BSDs. */
#define ACCESSPERMS (S_IRWXU | S_IRWXG | S_IRWXO) /* 0777 */
#define ALLPERMS    (S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO) /* 07777 */
#define DEFFILEMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) /* 0666 */
#endif

#if defined(__USE_BSD) || defined(__USE_GNU)
#define S_IREAD S_IRUSR
#define S_IWRITE S_IWUSR
#define S_IEXEC S_IXUSR
#endif

/* POSIX mandates these, but Linux doesn't implement them as distinct file types. */
#define S_TYPEISMQ(__sb) 0
#define S_TYPEISSEM(__sb) 0
#define S_TYPEISSHM(__sb) 0
#define S_TYPEISTMO(__sb) 0

int chmod(const char*, mode_t);
int fchmod(int, mode_t);
int mkdir(const char*, mode_t);

int fstat(int, struct stat*);

#if __ANDROID_API__ >= 21
int fstat64(int, struct stat64*) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */

int fstatat(int, const char*, struct stat*, int);

#if __ANDROID_API__ >= 21
int fstatat64(int, const char*, struct stat64*, int) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */

int lstat(const char*, struct stat*);

#if __ANDROID_API__ >= 21
int lstat64(const char*, struct stat64*) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */

int stat(const char*, struct stat*);

#if __ANDROID_API__ >= 21
int stat64(const char*, struct stat64*) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */


int mknod(const char*, mode_t, dev_t);
mode_t umask(mode_t);


#if __ANDROID_API__ >= 18
mode_t __umask_chk(mode_t) __INTRODUCED_IN(18);
#endif /* __ANDROID_API__ >= 18 */

mode_t __umask_real(mode_t) __RENAME(umask);
__errordecl(__umask_invalid_mode, "umask called with invalid mode");

#if defined(__BIONIC_FORTIFY)

#if __ANDROID_API__ >= __ANDROID_API_J_MR2__
__BIONIC_FORTIFY_INLINE
mode_t umask(mode_t mode) {
#if !defined(__clang__)
  if (__builtin_constant_p(mode)) {
    if ((mode & 0777) != mode) {
      __umask_invalid_mode();
    }
    return __umask_real(mode);
  }
#endif
  return __umask_chk(mode);
}
#endif /* __ANDROID_API__ >= __ANDROID_API_J_MR2__ */

#endif /* defined(__BIONIC_FORTIFY) */

#if __ANDROID_API__ >= __ANDROID_API_L__
int mkfifo(const char*, mode_t) __INTRODUCED_IN(21);
#else
// Implemented as a static inline before 21.
#endif


#if __ANDROID_API__ >= 23
int mkfifoat(int, const char*, mode_t) __INTRODUCED_IN(23);
#endif /* __ANDROID_API__ >= 23 */


int fchmodat(int, const char*, mode_t, int);
int mkdirat(int, const char*, mode_t);

#if __ANDROID_API__ >= 21
int mknodat(int, const char*, mode_t, dev_t) __INTRODUCED_IN(21);
#endif /* __ANDROID_API__ >= 21 */


#define UTIME_NOW  ((1L << 30) - 1L)
#define UTIME_OMIT ((1L << 30) - 2L)

#if __ANDROID_API__ >= 12
int utimensat(int fd, const char* path, const struct timespec times[2], int flags)
  __INTRODUCED_IN(12);
#endif /* __ANDROID_API__ >= 12 */


#if __ANDROID_API__ >= 19
int futimens(int fd, const struct timespec times[2]) __INTRODUCED_IN(19);
#endif /* __ANDROID_API__ >= 19 */


__END_DECLS

#include <android/legacy_sys_stat_inlines.h>

#endif /* _SYS_STAT_H_ */
