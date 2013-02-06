/*
 this sticks around for documentation issues only and will be removed in the next
 release - it documents the direct syscalls for affinity, without going thru glibc
 */

#if 0

/* 
 I don't know where this was exactly taken from, but I think I found it
 in glibc.
 */
#include <linux/unistd.h>
#define __NR_sched_setaffinity	241
#define __NR_sched_getaffinity	242

/*
 a nice macro to define the following:
 it's a syscall with 3 args,
 it returns int,
 it's named sched_....,
 the next arg is of type pid_t,
 has the local name pid,
 next is unsigned int,
 with name len,
 then an unsigned long *,
 named user_mask_ptr
 */
_syscall3 (int, sched_setaffinity, pid_t, pid, unsigned int, len, unsigned long *, user_mask_ptr)
_syscall3 (int, sched_getaffinity, pid_t, pid, unsigned int, len, unsigned long *, user_mask_ptr)

#endif

#include <linux/kernel.h>
#include <linux/unistd.h>
#include <linux/types.h>
#include <time.h>

/* XXX use the proper syscall numbers */
#ifdef __x86_64__
#define __NR_sched_setparam2		314
#define __NR_sched_getparam2		315
#define __NR_sched_setscheduler2	316
#endif

#ifdef __i386__
#define __NR_sched_setparam2		351
#define __NR_sched_getparam2		352
#define __NR_sched_setscheduler2	353
#endif

#ifdef __arm__
#define __NR_sched_setscheduler2	380
#define __NR_sched_setparam2		381
#define __NR_sched_getparam2		382
#endif

#define SF_SIG_RORUN	2
#define SF_SIG_DMISS	4

struct sched_param2 {
	int sched_priority;
	unsigned int sched_flags;
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;

	__u64 __unused[12];
};

#define sched_setscheduler2(pid, policy, param) \
	syscall(__NR_sched_setscheduler2, pid, policy, param)

#define sched_getparam2(pid, param) \
	syscall(__NR_sched_getparam2, pid, param)

#define sched_setparam2(pid, param) \
	syscall(__NR_sched_setparam2, pid, param)
