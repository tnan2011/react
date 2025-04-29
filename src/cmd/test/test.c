/* Uncomment for use test. */
// #include "../sys/include/core.h"

/*
* Main function for testing USB operations
* 
* Test cases are defined below. Uncomment the function
* calls to execute specific tests.
*/
int main() {
    const char *device = "/dev/sdb";
    
   /*
    * Case 1: Format USB device:
    * Expected Result: The device should be formatted successfully.
    */
   // format_device(device);

  /*
   * Case 2: Create MBR partition on the USB Device:
   * Expected Result: The partition table should be created successfully.
   */
  // create_mbr_partition(device);
  
  /* 
   * Case 3: Unmount the USB device
   * Expected Status Code Result: 
   * [+] 11 => Unmount failed. Try again with root operation
   * [+] 10 => Unmount successfully.
   */
  // unmount_device(device);
  
 /*
  * Case 4: Create FAT32 Filesystem
  * Expected Status Code Result:
  * [+] 0 => Success
  * Else is error. Checkout in core.c
  */
  // create_fat32_file_system("/dev/sdb");
}