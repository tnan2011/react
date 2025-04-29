#include "include/fat32.h"
#include "include/status.h"
#include <string.h>

RESULT_STATUS create_fat32(struct fat32_params* params) {
    int device = open(params->device, O_RDWR);
    if (device < 0)
        return DEVICE_NOT_FOUND;
          
    unsigned long long total_sectors = params->sectors;

    int sectors_per_cluster = params->sectors_per_cluster;
    if (!sectors_per_cluster) {
        if (total_sectors < 1048576) { /* < 512MB */
            sectors_per_cluster = 4;
        } else if (total_sectors < 16777216) { /* < 8GB */
            sectors_per_cluster = 8;
        } else { // >= 8GB
            sectors_per_cluster = 16;
        }
    }

    if(sectors_per_cluster > 32)
        sectors_per_cluster = 32;

    unsigned long long adjusted_sectors = total_sectors - (total_sectors % sectors_per_cluster);
    unsigned long long total_clusters = adjusted_sectors / sectors_per_cluster;

    int reserved_sectors = 32;
    int fat_count = 2;
    unsigned long long sectors_per_fat = (total_clusters * 4 + SECTOR_SIZE - 1) / SECTOR_SIZE;

    if (total_sectors > (1ULL << 32))
        return PARTITION_TOO_BIG;
    if (total_sectors < 65525) {
        close(device);
        return PARTITION_TOO_SMALL;
    }
    if (total_clusters > MAX_FAT_32_CLUSTERS) {
        close(device);
        return MAX_CLUSTER_ERROR;
    }

    /* Write boot sector */
    unsigned char boot_sector[SECTOR_SIZE] = {0};
    boot_sector[0] = 0xEB; boot_sector[1] = 0x58; boot_sector[2] = 0x90;
    memcpy(boot_sector + 3, "MSWIN4.1", 8);
    boot_sector[11] = 0x00; boot_sector[12] = 0x02;

    boot_sector[13] = sectors_per_cluster;

    boot_sector[14] = reserved_sectors & 0xFF;
    boot_sector[15] = (reserved_sectors >> 8) & 0xFF;

    boot_sector[16] = fat_count;
    boot_sector[21] = 0xF8;
    *(unsigned int*)&boot_sector[0x20] = (unsigned int)adjusted_sectors;
    *(unsigned int*)&boot_sector[0x24] = (unsigned int)sectors_per_fat;

    boot_sector[36] = 0x80;
    boot_sector[38] = 0x29;
    boot_sector[40] = sectors_per_fat & 0xFF;
    boot_sector[41] = (sectors_per_fat >> 8) & 0xFF;

    boot_sector[42] = (sectors_per_fat >> 16) & 0xFF;
    boot_sector[43] = (sectors_per_fat >> 24) & 0xFF;

    boot_sector[48] = 1; /* FSInfo sector */
    boot_sector[50] = 6; /* Backup boot sector */
    boot_sector[510] = 0x55; boot_sector[511] = 0xAA;

    memcpy(boot_sector + 0x36, "FAT32   ", 8);

    lseek(device, 0, SEEK_SET);
    if (write(device, boot_sector, SECTOR_SIZE) != SECTOR_SIZE) {
        close(device);
        return WRITE_BOOT_SECTOR_FAILED;
    }

    /* Write FSInfo */
    unsigned char fsinfo[SECTOR_SIZE] = {0};
    fsinfo[0] = 'R'; fsinfo[1] = 'R'; fsinfo[2] = 'a'; fsinfo[3] = 'A';
    fsinfo[484] = 'r'; fsinfo[485] = 'r'; fsinfo[486] = 'A'; fsinfo[487] = 'a';

    unsigned long long free_clusters = total_clusters - 3;
    fsinfo[488] = free_clusters & 0xFF;
    fsinfo[489] = (free_clusters >> 8) & 0xFF;
    fsinfo[490] = (free_clusters >> 16) & 0xFF;

    fsinfo[491] = (free_clusters >> 24) & 0xFF;
    fsinfo[492] = 3; /* First available cluster */
    fsinfo[510] = 0x55; fsinfo[511] = 0xAA;

    lseek(device, SECTOR_SIZE, SEEK_SET);
    if (write(device, fsinfo, SECTOR_SIZE) != SECTOR_SIZE) {
        close(device);
        return WRITE_FS_INFO_FAILED;
    }

    /* Write backup boot sector */
    lseek(device, 6 * SECTOR_SIZE, SEEK_SET);
    if (write(device, boot_sector, SECTOR_SIZE) != SECTOR_SIZE) {
        close(device);
        return WRITE_BOOT_SECTOR_FAILED;
    }

    /* Write FAT tables */
    unsigned char fat_buffer[SECTOR_SIZE * 32] = {0};
    /* Cluster 0 */
    fat_buffer[0] = 0xF8; 
    fat_buffer[1] = 0xFF; 
    fat_buffer[2] = 0xFF; 
    fat_buffer[3] = 0xFF;

    /* Cluster 1 */
    fat_buffer[4] = 0xFF; 
    fat_buffer[5] = 0xFF; 
    fat_buffer[6] = 0xFF; 
    fat_buffer[7] = 0xFF;

    /* Cluster 2 */
    fat_buffer[8] = 0xFF; 
    fat_buffer[9] = 0xFF; 
    fat_buffer[10] = 0xFF; 
    fat_buffer[11] = 0x0F; 

    /* Write FAT1 */
    lseek(device, reserved_sectors * SECTOR_SIZE, SEEK_SET);
    unsigned long remaining_sectors = sectors_per_fat;
    
    while (remaining_sectors > 0) {
        int write_size = (remaining_sectors > 32) ? 32 : remaining_sectors;
        if (write(device, fat_buffer, write_size * SECTOR_SIZE) != write_size * SECTOR_SIZE) {
            close(device);
            return WRITE_SECTOR_FAILED;
        }
        remaining_sectors -= write_size;
        memset(fat_buffer, 0, SECTOR_SIZE * 32);
    }

    /* Write FAT2 */
    lseek(device, (reserved_sectors + sectors_per_fat) * SECTOR_SIZE, SEEK_SET);
    fat_buffer[0] = 0xF8; 
    fat_buffer[1] = 0xFF; 
    fat_buffer[2] = 0xFF;

    fat_buffer[3] = 0xFF;
    fat_buffer[4] = 0xFF;

    fat_buffer[5] = 0xFF; 
    fat_buffer[6] = 0xFF; 
    fat_buffer[7] = 0xFF;

    fat_buffer[8] = 0xFF; 
    fat_buffer[9] = 0xFF; 
    fat_buffer[10] = 0xFF; 
    fat_buffer[11] = 0xFF;
    remaining_sectors = sectors_per_fat;

    while (remaining_sectors > 0) {
        int write_size = (remaining_sectors > 32) ? 32 : remaining_sectors;

        if (write(device, fat_buffer, write_size * SECTOR_SIZE) != write_size * SECTOR_SIZE) {
            close(device);
            return WRITE_SECTOR_FAILED;
        }
        remaining_sectors -= write_size;
        memset(fat_buffer, 0, SECTOR_SIZE * 32);
    }

    fsync(device);
    close(device);
    return SUCCESS;
}
