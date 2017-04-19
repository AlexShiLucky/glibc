/* Change access and modification times of open file.  Linux version.
   Copyright (C) 2007-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sysdep.h>
#include <kernel_timespec.h>


/* Change the access time of the file associated with FD to TSP[0] and
   the modification time of FILE to TSP[1].

   Starting with 2.6.22 the Linux kernel has the utimensat syscall which
   can be used to implement futimens.  */
int
futimens (int fd, const struct timespec tsp[2])
{
  if (fd < 0)
    return INLINE_SYSCALL_ERROR_RETURN_VALUE (EBADF);
  /* Avoid implicit array coercion in syscall macros.  */
  return INLINE_SYSCALL (utimensat, 4, fd, NULL, &tsp[0], 0);
}

int
__futimens64 (int fd, const struct __timespec64 tsp[2])
{
  struct kernel_timespec64 kt[2];
  if (fd < 0)
    return INLINE_SYSCALL_ERROR_RETURN_VALUE (EBADF);
  kt[0].tv_sec = tsp[0].tv_sec;
  kt[0].tv_nsec = tsp[0].tv_nsec;
  kt[1].tv_sec = tsp[1].tv_sec;
  kt[1].tv_nsec = tsp[1].tv_nsec;
  /* Avoid implicit array coercion in syscall macros.  */
  return INLINE_SYSCALL (utimensat64, 4, fd, NULL, &kt[0], 0);
}
