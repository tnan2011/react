#include "include/cmd.h"
#include "include/macro.h"
#include "sys/include/core.h"
#include "sys/include/status.h"
#include <stdio.h>

RESULT_STATUS format_cmd(int argc, char *args[]) {
    if(argc < 3 ) {
        printf(MISSING_ARGS_MSG);
        return MISSING_ARGS;
    }

    const char *device_path = args[2];
    RESULT_STATUS task_status = format_device(device_path);

    if(task_status == OPEN_DEVICE_FAILED) {
        printf(OPEN_DEVICE_FAILED_MSG);
        return OPEN_DEVICE_FAILED;
    } else if(task_status == WRITE_DEVICE_FAILED) {
        printf(OPEN_DEVICE_FAILED_MSG);
        return WRITE_DEVICE_FAILED;
    } else if(task_status == SYNC_DEVICE_FAILED) {
        printf(SYNC_DEVICE_FAILED_MSG);
        return SYNC_DEVICE_FAILED;
    } 
    printf(FORMAT_SUCCESS_MSG);
    return SUCCESS;
}

RESULT_STATUS create_mbr_cmd(int argc, char *args[]) {
    if(argc < 3) {
        printf(MISSING_ARGS_MSG);
        return MISSING_ARGS;
    }

    const char *device_path = args[2];
    // RESULT_STATUS umount_status = unmount_device(device_path);
    // if(umount_status == UNMOUNT_DEVICE_FAILED) {
    //     printf(UMOUNT_DEVICE_FAILED_MSG);
    //     return UNMOUNT_DEVICE_FAILED;
    // } else if(umount_status == NO_PERMIT_OPERATION) {
    //     printf(NO_PERMIT_MSG);
    //     return NO_PERMIT_OPERATION;
    // }

    RESULT_STATUS task_status = create_mbr_partition(device_path);

    if(task_status == DEVICE_NOT_FOUND) {
        printf(DEVICE_NOT_FOUND_MSG);
        return DEVICE_NOT_FOUND;
    } else if(task_status == ADD_PARTITION_FAILED) {
        printf(ADD_PARTITION_FAILED_MSG);
        return ADD_PARTITION_FAILED;
    } else if(task_status == COMMIT_PARTITION_FAILED) {
        printf(COMMIT_PARTITION_FAILED_MSG);
        return COMMIT_PARTITION_FAILED;
    }

    return SUCCESS;
}

RESULT_STATUS create_fat32_sys_cmd(int argc, char *args[]) {
    const char *device = args[2];

    RESULT_STATUS task_status = create_fat32_file_system(device);
    if(task_status == PARTITION_TOO_BIG) {
        printf(PARTITION_TOO_BIG_MSG);
        return PARTITION_TOO_BIG;
    } else if(task_status == PARTITION_TOO_SMALL) {
        printf(PARTITION_TOO_SMALL_MSG);
        return PARTITION_TOO_SMALL;
    } else if(task_status == MAX_CLUSTER_ERROR) {
        printf(MAX_CLUSTER_ERR_MSG);
        return MAX_CLUSTER_ERROR;
    } else if(task_status == WRITE_BOOT_SECTOR_FAILED) {
        printf(WRITE_BOOT_SECTOR_FAILED_MSG);
        return WRITE_BOOT_SECTOR_FAILED;
    } else if(task_status == WRITE_FS_INFO_FAILED) {
        printf(WRITE_FS_FAILED_MSG);
        return WRITE_FS_INFO_FAILED;
    } else if(task_status == WRITE_SECTOR_FAILED) {
        printf(WRITE_BOOT_SECTOR_FAILED_MSG);
        return WRITE_SECTOR_FAILED;
    }

    return SUCCESS;
}
