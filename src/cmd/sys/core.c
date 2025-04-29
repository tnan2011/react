#include "include/core.h"
#include "include/status.h"
#include "include/fat32.h"
#include <errno.h>

static RESULT_STATUS get_mount_point(const char *device, char *out_mount, size_t size) {
     FILE *file_t = setmntent("/proc/mounts", "r");

     if(!file_t) {
          if(errno == EPERM || errno == EACCES)
               return NO_PERMIT_OPERATION;

          return GET_MOUNT_FAILED;
     }

     struct mntent *mntent_t;
     while((mntent_t = getmntent(file_t)) != NULL) {
          if(strncmp(mntent_t->mnt_fsname, device, strlen(device)) == 0) {
               strncpy(out_mount, mntent_t->mnt_dir, size - 1);
               out_mount[size - 1] = '\0';
               endmntent(file_t);
     
               return GET_MOUNT_SUCCESS;
          }
     }

     endmntent(file_t);
     return GET_MOUNT_FAILED;
}

RESULT_STATUS unmount_device(const char *device) {
     char mount_point[256];

     RESULT_STATUS get_mount_point_status = get_mount_point(
          device, mount_point, sizeof(mount_point)
     );

     if(get_mount_point_status != GET_MOUNT_SUCCESS) 
          return UNMOUNT_DEVICE_FAILED;

     if(umount2(mount_point, MNT_FORCE) == 0) 
          return UNMOUNT_DEVICE_SUCCESS;

     if(errno == EPERM)
          return NO_PERMIT_OPERATION;

     return UNMOUNT_DEVICE_FAILED;
}

RESULT_STATUS format_device(const char *device) {
   int fd_status = open(device, O_RDWR | O_EXCL);

   if(fd_status < 0) 
     return OPEN_DEVICE_FAILED;

   char zero_buffer[512] = {0};
   if(write(fd_status, zero_buffer, sizeof(zero_buffer)) != sizeof(zero_buffer)) {
        close(fd_status);
        return WRITE_DEVICE_FAILED;
   }

   if(fsync(fd_status) < 0) {
     close(fd_status);
     return SYNC_DEVICE_FAILED;
   }

   close(fd_status);
   return SUCCESS;
}

RESULT_STATUS create_mbr_partition(const char *device) {
     PedDevice *device_t = ped_device_get(device);
     if(!device_t) {
          printf("Could not open %s\n", device);
          return DEVICE_NOT_FOUND;
     }

     PedDiskType *disk_type_t = ped_disk_type_get("msdos");
     PedDisk *disk_t = ped_disk_new_fresh(device_t, disk_type_t);

     if(!disk_t) 
          return ADD_PARTITION_FAILED;
     
     PedSector sector_start_t = 1;
     PedSector sector_end_t = device_t->length - 1;
     PedPartition *ped_partition_t = ped_partition_new(disk_t, PED_PARTITION_NORMAL, NULL, sector_start_t, sector_end_t);

     if(!ped_partition_t) {
          ped_disk_destroy(disk_t);
          return ADD_PARTITION_FAILED;
     }

     if(!ped_disk_add_partition(disk_t, ped_partition_t, ped_constraint_any(device_t))) {
          ped_disk_destroy(disk_t);
          return ADD_PARTITION_FAILED;
     }

     if(!ped_disk_commit_to_dev(disk_t) || !ped_disk_commit(disk_t)) {
          ped_disk_destroy(disk_t);
          ped_device_destroy(device_t);
          return COMMIT_PARTITION_FAILED;
     }

     ped_disk_destroy(disk_t);
     ped_device_destroy(device_t);

     return SUCCESS;
}

RESULT_STATUS create_fat32_file_system(const char *device) {
     PedDevice *device_t;
     PedDisk *disk_t;
     PedPartition *partition_t;
     PedFileSystem *file_system_t;
     PedGeometry *geometry_t;
     
     device_t = ped_device_get(device);
     if(!device_t)
          return DEVICE_NOT_FOUND;

     disk_t = ped_disk_new(device_t);
     if(!disk_t) {
          ped_device_destroy(device_t);
          return LOAD_DISK_INFO_FAILED;
     }

     partition_t = ped_disk_get_partition(disk_t, 1);
     if(!partition_t) {
          ped_device_destroy(device_t);
          ped_disk_destroy(disk_t);
          return PARTITION_NOT_FOUND;
     }

     geometry_t = ped_geometry_new(device_t, 
          partition_t->geom.start, partition_t->geom.length);
     
     if(!geometry_t) {
          ped_device_destroy(device_t);
          ped_disk_destroy(disk_t);
          return GET_GEOMETRY_PARTITION_FAILED;
     }

     char partition_path[256];
     snprintf(partition_path, sizeof(partition_path), "%s1", device_t->path);
     struct fat32_params params = {
          .device = partition_path,
          .sectors = geometry_t->length * (device_t->sector_size / 512),
          .sectors_per_cluster = 0
     };

     RESULT_STATUS result = create_fat32(&params);
     if(result != SUCCESS) {
          ped_device_destroy(device_t);
          ped_disk_destroy(disk_t);
          ped_geometry_destroy(geometry_t);
          return FORMAT_FAT32_FAILED;
     }

     ped_device_destroy(device_t);
     ped_disk_destroy(disk_t);
     ped_geometry_destroy(geometry_t);

     return SUCCESS;
}
