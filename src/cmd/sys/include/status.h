#ifndef STATUS_H
#define STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SUCCESS, /* With no error. Expands to 0 */
    FAILED, /* With some error. Expands to 1 */
    NO_PERMIT_OPERATION, /* No permit access, write. Expands to 2 */

    GET_MOUNT_FAILED, /* Get mount point failed. Expands to 3 */
    GET_MOUNT_SUCCESS, /* Get mount point success. Expands to 4 */
    UNMOUNT_DEVICE_FAILED, /* Unmount device failed. Expands to 5 */
    UNMOUNT_DEVICE_SUCCESS, /* Unmount device success. Expands to 6 */

    OPEN_DEVICE_FAILED, /* Open device failed. Expands to 7 */
    WRITE_DEVICE_FAILED, /* Write to device failed. Expands to 8 */
    SYNC_DEVICE_FAILED, /* Sync device failed. Expands to  9 */

    DEVICE_NOT_FOUND, /* Device not found. Expands to 10 */

    ADD_PARTITION_FAILED, /* Add partition to device failed. Expands to 11 */
    COMMIT_PARTITION_FAILED, /* Commit to partition device failed. Expands to 12 */
    LOAD_DISK_INFO_FAILED, /* Load disk info is failed. Expands to 13 */
    PARTITION_NOT_FOUND,  /* Partition not found. Expands to 14 */
    GET_GEOMETRY_PARTITION_FAILED, /* Get geometry partition of device failed. Expands to  15*/
    
    FORMAT_FAT32_FAILED, /* Format device with FAT32 file  system failed. Expands to  16 */

    PARTITION_TOO_BIG, /* Partition too big. Expands to 17 */
    PARTITION_TOO_SMALL, /* Partition too small. Expands to 18 */
    MAX_CLUSTER_ERROR, /* Max cluster error. Expands to 19 */

    WRITE_BOOT_SECTOR_FAILED, /* Write boot sector failed. Expands to 20 */
    WRITE_FS_INFO_FAILED, /* Write FS info failed. Expands to 21 */
    WRITE_SECTOR_FAILED, /* Write sector in device failed. Expands to 22 */

    MISSING_ARGS, /* Missing argument in CLI. Expands to 23 */
    INVALID_USAGE, /* Invalid usage in CLI. Expands to 24 */
    VALID_USAGE, /* Valid usage in CLI. Expands to 25 */

    CLI_PATH_NOT_FOUND /* CLI path directory not found. Expands to 26 */
} RESULT_STATUS;

#ifdef __cplusplus
}
#endif
#endif // STATUS_H
