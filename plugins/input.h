/*******************************************************************************
#                                                                              #
#      MJPG-streamer allows to stream JPG frames from an input-plugin          #
#      to several output plugins                                               #
#                                                                              #
#      Copyright (C) 2007 Tom Stöveken                                         #
#                                                                              #
# This program is free software; you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation; version 2 of the License.                      #
#                                                                              #
# This program is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of               #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
# GNU General Public License for more details.                                 #
#                                                                              #
# You should have received a copy of the GNU General Public License            #
# along with this program; if not, write to the Free Software                  #
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA    #
#                                                                              #
*******************************************************************************/

#include <syslog.h>
#include "../mjpg_streamer.h"
#include "../fifo_list.h"
#define INPUT_PLUGIN_PREFIX " i: "
#define IPRINT(...) { char _bf[1024] = {0}; snprintf(_bf, sizeof(_bf)-1, __VA_ARGS__); fprintf(stderr, "%s", INPUT_PLUGIN_PREFIX); fprintf(stderr, "%s", _bf); syslog(LOG_INFO, "%s", _bf); }

/* parameters for input plugin */
typedef struct _input_parameter input_parameter;
struct _input_parameter {
    int id;
    char *parameters;
    int argc;
    char *argv[MAX_PLUGIN_ARGUMENTS];
    struct _globals *global;
};

typedef struct _sample_data input_data;

struct _sample_data {
	int id; /* card id */
	time_t t; /* sample time */
	int len; /* data length */
	unsigned char data[1]; /* data */
};

/* structure to store variables/functions for input plugin */
typedef struct _input input;
struct _input {
    char *plugin;
    void *handle;

    input_parameter param; // this holds the command line arguments

    // input plugin parameters
    struct _control *in_parameters;
    int parametercount;

    /* signal fresh frames */
    pthread_mutex_t db;
    pthread_cond_t  db_update;

    /* global data frame, this is more or less the "database" */
    struct fifo_node *db_frame;

    int formatCount;
    int currentFormat; // holds the current format number

    int (*init)(input_parameter *, int id);
    int (*stop)(int);
    int (*run)(int);
    int (*cmd)(int plugin, unsigned int control_id, unsigned int group, int value);
};
