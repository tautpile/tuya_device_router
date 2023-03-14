#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <argp.h>
#include <signal.h>

#include <cJSON.h>
#include <tuya_log.h>
#include <tuya_error_code.h>
#include <system_interface.h>
#include <mqtt_client_interface.h>
#include <tuyalink_core.h>

#include "argparse.h"
#include "iotcloud.h"
#include <stddef.h>
#include <syslog.h>

