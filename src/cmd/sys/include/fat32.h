#ifndef FAT32_H
#define FAT32_H
#define SECTOR_SIZE  512
#define MAX_CLUSTERS  0x0FFFFFF0ULL
#define MAX_FAT_32_CLUSTERS 0xFFFFFFF6
#include "status.h"
#include <fcntl.h>
#include <unistd.h>

struct fat32_params {
    const char *device;
    unsigned long long sectors;
    int sectors_per_cluster;
};

RESULT_STATUS create_fat32(struct fat32_params *params);

#endif // FAT32_H