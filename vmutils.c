#include "vmutils.h"

RESULT get_pid_by_name(char *pid_name, pid_t *pid) {

    pid_t pids[4096];

    int bytes = proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));

    int count = bytes / sizeof(pid_t);

    for (int i = 0; i < count; i++) {

        if (pids[i] == 0)
            continue;

        char name[PROC_PIDPATHINFO_MAXSIZE];

        proc_name(pids[i], name, sizeof(name));
        if (strcmp(name, pid_name) == 0) {

            *pid = pids[i];
            return SUCCESS;
        }
    }
    *pid = 0;
    return FAIL;
}

// Error printed automaticlly
RESULT get_task_from_pid(pid_t pid, task_t *task) {
    kern_return_t kr = task_for_pid(mach_task_self(), pid, task);

    if (kr != KERN_SUCCESS) {
        puts(mach_error_string(kr));
        return FAIL;
    }
    return SUCCESS;
};
