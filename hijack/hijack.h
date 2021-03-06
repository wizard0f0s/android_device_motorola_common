#ifndef __HIJACK_H__
#define __HIJACK_H__

// declare all of our includes
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <limits.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <sys/reboot.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/limits.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <cutils/properties.h>
// Add bootmenu includes
#include "extendedcommands.h"
#include "common.h"
#include "overclock.h"
#include "minui/minui.h"
#include "bootmenu_ui.h"

/*
#ifndef LOG_ENABLE
#define LOG_ENABLE 1
#endif
 */

// sleepwait time (we default to MAX_INT fur die lulz)
#ifndef HIJACK_SLEEPWAIT_SEC
#define HIJACK_SLEEPWAIT_SEC UINT_MAX
#endif

// file that throws us into recovery mode
#ifndef RECOVERY_MODE_FILE
#define RECOVERY_MODE_FILE "/data/.recovery_mode"
#endif

// file that tells if bootmenu has already run or not
#ifndef BOOTMENU_RUN_FILE
#define BOOTMENU_RUN_FILE "/.bootmenu"
#endif

// init.mapphone_cdma.rc file that needs to be modified to remove default governor settings
#ifndef INIT_MAPPHONE_CDMA_FILE
#define INIT_MAPPHONE_CDMA_FILE "init.mapphone_cdma.rc"
#endif

// init.mapphone_umts.rc file that needs to be modified to remove default governor settings
#ifndef INIT_MAPPHONE_UMTS_FILE
#define INIT_MAPPHONE_UMTS_FILE "init.mapphone_umts.rc"
#endif

// if we enable logging...
#ifdef LOG_ENABLE
// log device
#ifndef LOG_DEVICE
#define LOG_DEVICE "/dev/block/mmcblk0p1" // default to SD card
#endif
// log mount point
#ifndef LOG_MOUNT
#define LOG_MOUNT "/sdlog" // default to SD logging
#endif
// log file name (will be placed under SDLOG_MOUNT)
#ifndef LOG_FILE
#define LOG_FILE "hijack.log" // this works
#endif
// script that dumps dmesg/logcat/etc
#ifndef LOG_DUMP_BINARY
#define LOG_DUMP_BINARY "/system/bin/hijack.log_dump"
#endif
// frequency of indefinite log
#define LOG_INDEF_FREQ "10s"
// convenience define
#define LOG_PATH LOG_MOUNT"/"LOG_FILE
#endif

// update-binary executable
#ifndef UPDATE_BINARY
#define UPDATE_BINARY "/preinstall/recovery/update-binary"
#endif

// boot update.zip
#ifndef BOOT_UPDATE_ZIP
#define BOOT_UPDATE_ZIP "/system/etc/hijack-boot.zip"
#endif

// recovery update.zip
#ifndef RECOVERY_UPDATE_ZIP
#define RECOVERY_UPDATE_ZIP "/preinstall/recovery/recovery.zip"
#endif

// function prototypes! :D
int exec_and_wait(char ** argp);
int remount_root(const char * hijack_exec, int rw);
int hijack_mount(const char * hijack_exec, const char * dev, const char * mount_point);
int hijack_umount(const char * hijack_exec, const char * mount_point);
void hijack_log(char * format, ...);
int parse_init_mapphone_cdma();
int mark_file(const char * filename);
int run_bootmenu(void);
int exec_script(char * hijack_exec, const char * script);
int get_menu_selection(char** headers, char** items, int menu_only, int initial_selection);
void free_menu_headers(char **headers);
static void prompt_and_wait();
static int wait_key(int key);
static void ui_finish(void);
char** prepend_title(const char** headers);

#endif
