#ifndef FORMAT_H
#define FORMAT_H
#include "../sys/include/status.h"

RESULT_STATUS format_cmd(int argc, char *args[]);
RESULT_STATUS create_mbr_cmd(int argc, char *args[]);
RESULT_STATUS create_fat32_sys_cmd(int argc, char *args[]);

#endif // FORMAT_H

