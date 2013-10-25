#ifndef MJPG_STREAMER_H
#define MJPG_STREAMER_H
#define SOURCE_VERSION "0.1"

/* FIXME take a look to the output_http clients thread marked with fixme if you want to set more then 10 plugins */
#define MAX_INPUT_PLUGINS 10
#define MAX_OUTPUT_PLUGINS 10
#define MAX_PLUGIN_ARGUMENTS 32
#include <linux/types.h>          /* for videodev2.h */
#define DEBUG
#ifdef DEBUG
#define DBG(...) fprintf(stderr, " DBG(%s, %s(), %d): ", __FILE__, __FUNCTION__, __LINE__); fprintf(stderr, __VA_ARGS__)
#else
#define DBG(...)
#endif

#define LOG(...) { char _bf[1024] = {0}; snprintf(_bf, sizeof(_bf)-1, __VA_ARGS__); fprintf(stderr, "%s", _bf); syslog(LOG_INFO, "%s", _bf); }

#include "plugins/input.h"
#include "plugins/output.h"

/* global variables that are accessed by all plugins */
typedef struct _globals globals;

/* an enum to identify the commands destination*/
typedef enum {
    Dest_Input = 0,
    Dest_Output = 1,
    Dest_Program = 2,
} command_dest;

/* commands which can be send to the input plugin */
typedef enum _cmd_group cmd_group;
enum _cmd_group {
    IN_CMD_GENERIC = 0, // if you use non V4L2 input plugin you not need to deal the groups.
    IN_CMD_V4L2 = 1,
    IN_CMD_RESOLUTION = 2,
    IN_CMD_JPEG_QUALITY = 3,
};

typedef struct _control control;
struct _control {

    int value;
    int group;
};

struct _globals {
    int stop;

    /* input plugin */
    input in[MAX_INPUT_PLUGINS];
    int incnt;

    /* output plugin */
    output out[MAX_OUTPUT_PLUGINS];
    int outcnt;

    /* pointer to control functions */
    //int (*control)(int command, char *details);
};

#endif
