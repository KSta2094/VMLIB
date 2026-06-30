
#ifndef VMUTILS
#define VMUTILS

#include <libproc.h>
#include <mach/mach.h>
#include <mach/mach_vm.h>

#include <stdio.h>

typedef enum {
    SUCCESS,
    FAIL,
} RESULT;

RESULT get_pid_by_name(char *pid_name, pid_t *pid);

RESULT get_task_from_pid(pid_t pid, task_t *task);

#endif
