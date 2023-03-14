#include "main.h"
 
int run = 1;

void sig_handler(int signum) 
{
        printf("CTRL + C was pressed. Stopping program\n");
        run = 0;
}

struct argp_option options[] = {
        {"di", 'i', 0, 0, "Device id"},
        {"ds", 's', 0, 0, "Device secret"},
        {"pi", 'p', 0, 0, "Product id"},
        {"de", 'd', 0, 0, "Call daemon"},
        { 0 }
};

const char args_doc[] = "Device id -i, Device secret -s, Product id -p";
const char doc[] =
        "\nThis program launches a daemon process which sends data to the tuya cloud. "
        "When specified it can accept: Device id, Device secret, Product id";

struct argp argp = { options, parse_opt, args_doc, doc };
tuya_mqtt_context_t client_instance;

int main(int argc, char** argv)
{
        struct arguments arguments;
        int rc = 0;
       
        struct sigaction sa;
        memset(&sa, 0, sizeof(struct sigaction));
        sa.sa_handler = sig_handler;
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);

        openlog("tuya_iot_sender", LOG_PID|LOG_CONS, LOG_USER);

        rc = argp_parse (&argp, argc, argv, 0, 0, &arguments);
        if(rc != 0) {
                syslog(LOG_ERR, "Parse error");
                return 0;
        }

        tuya_mqtt_context_t* client = &client_instance;

        if (arguments.d == 1)
                call_daem();

        rc = tuya_cloud_start(client, &arguments);
        if (rc != 0) 
                syslog(LOG_ERR, "Init error");
        
        rc = tuya_mqtt_main_loop(client);
        if (rc != 0) 
                syslog(LOG_ERR, "Loop error");

        rc = tuya_mqtt_end(client);
        if (rc != 0) 
                syslog(LOG_ERR, "Close error");

        closelog();
        return 0;
}
