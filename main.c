#include "vmutils.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    pid_t pid;
    if (get_pid_by_name(argv[1], &pid) == FAIL) {
        printf("process not found");
        return -1;
    }

    printf("PID of %s is %i\n", argv[1], pid);

    task_t task;
    if (get_task_from_pid(pid, &task) == FAIL) {
        return -1;
    }
    {

        mach_vm_address_t adress = 0;
        while (1) {
            mach_vm_size_t size = 0;
            vm_region_basic_info_data_64_t info;
            mach_msg_type_number_t count = VM_REGION_BASIC_INFO_COUNT_64;
            memory_object_name_t object;
            kern_return_t kr =
                mach_vm_region(task, &adress, &size, VM_REGION_BASIC_INFO_64,
                               (vm_region_info_t)&info, &count, &object);
            if (kr != KERN_PROTECTION_FAILURE) {
                printf("BASE ADRESS:%llu \n", adress);
                break;
            }

            adress += size;
        }
    }

    return 0;
}
