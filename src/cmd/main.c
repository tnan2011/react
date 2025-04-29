#include <stdio.h>
#include <string.h>
#include "include/cmd.h"
#include "include/macro.h"
#include "sys/include/status.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc == 1 || argv[1] == NULL) {
        printf(INVALID_USAGE_MSG);
        return INVALID_USAGE;
    } else if(strcmp(argv[1], "format") == 0) {
        format_cmd(argc, argv);
        return VALID_USAGE;
    } else if(strcmp(argv[1], "part-mbr") == 0) {
        create_mbr_cmd(argc, argv);
        return VALID_USAGE;
    } else if(strcmp(argv[1], "fat32") == 0) {
        create_fat32_sys_cmd(argc, argv);
        return VALID_USAGE;
    } else if(strcmp(argv[1], "gui-format-mbr-fat32") == 0) {
        format_cmd(argc, argv);
        create_mbr_cmd(argc, argv);
        create_fat32_sys_cmd(argc, argv);
        return VALID_USAGE;
    }
    printf( BAD_USAGE_MSG, argv[1]);
    
    return INVALID_USAGE;
}