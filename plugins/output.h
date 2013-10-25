#include "../mjpg_streamer.h"
#define OUTPUT_PLUGIN_PREFIX " o: "
#define OPRINT(...) { char _bf[1024] = {0}; snprintf(_bf, sizeof(_bf)-1, __VA_ARGS__); fprintf(stderr, "%s", OUTPUT_PLUGIN_PREFIX); fprintf(stderr, "%s", _bf); syslog(LOG_INFO, "%s", _bf); }

/* parameters for output plugin */
typedef struct _output_parameter output_parameter;
struct _output_parameter {
    int id;
    char *parameters;
    int argc;
    char *argv[MAX_PLUGIN_ARGUMENTS];
    struct _globals *global;
};



/* structure to store variables/functions for output plugin */
typedef struct _output output;
struct _output {
    char *plugin;
    void *handle;
    output_parameter param;

    // input plugin parameters
    struct _control *out_parameters;
    int parametercount;

    int (*init)(output_parameter *param, int id);
    int (*stop)(int);
    int (*run)(int);
    int (*cmd)(int plugin, unsigned int control_id, unsigned int group, int value);
};

