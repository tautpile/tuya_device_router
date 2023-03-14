#include "main.h"
#include "tuya_cacert.h"
#include <libubox/blobmsg_json.h>
#include <libubus.h>

extern int run;

static const struct blobmsg_policy memory_policy[__MEMORY_MAX] = {
	[TOTAL_MEMORY]	  = { .name = "total", .type = BLOBMSG_TYPE_INT64 },
	[FREE_MEMORY]	  = { .name = "free", .type = BLOBMSG_TYPE_INT64 },
	[SHARED_MEMORY]	  = { .name = "shared", .type = BLOBMSG_TYPE_INT64 },
};   

static const struct blobmsg_policy info_policy[__INFO_MAX] = {
	[MEMORY_DATA] = { .name = "memory", .type = BLOBMSG_TYPE_TABLE },
};

static void board_cb(struct ubus_request *req, int type, struct blob_attr *msg)
{
        struct MemData *memoryData = (struct MemData *)req->priv;
        struct blob_attr *tb[__INFO_MAX];
        struct blob_attr *memory[__MEMORY_MAX];

        blobmsg_parse(info_policy, __INFO_MAX, tb, blob_data(msg), blob_len(msg));

        if (!tb[MEMORY_DATA]) {
                syslog(LOG_ERR, "No memory data received");
                return;
        }

        blobmsg_parse(memory_policy, __MEMORY_MAX, memory, blobmsg_data(tb[MEMORY_DATA]), blobmsg_data_len(tb[MEMORY_DATA]));

        memoryData->free    = blobmsg_get_u64(memory[FREE_MEMORY]);
	memoryData->shared  = blobmsg_get_u64(memory[SHARED_MEMORY]);
}

void on_messages(tuya_mqtt_context_t* context, void* user_data, const tuyalink_message_t* msg)
{
        if (new_file_append() != 0) 
                syslog(LOG_ERR, "File append error");
}

int new_file_append()
{
        FILE *fp; 
        if ((fp = fopen("/tmp/textas.txt", "a")) == NULL)
                return 1;
        fclose(fp);
        return 0;
}

int tuya_cloud_start(struct tuya_mqtt_context *client, struct arguments *arguments)
{
        int ret = OPRT_OK;
        ret = tuya_mqtt_init(client, &(const tuya_mqtt_config_t) {
                .host = "m1.tuyacn.com",
                .port = 8883,
                .cacert = tuya_cacert_pem,
                .cacert_len = sizeof(tuya_cacert_pem),
                .device_id = arguments->di,
                .device_secret = arguments->ds,
                .keepalive = 100,
                .timeout_ms = 2000,
                .on_messages = on_messages,
        });

        if( ret != OPRT_OK) {
                syslog(LOG_ERR, "Unable to initialize tuya mqtt");
        }
        ret = tuya_mqtt_connect(client);
        if(ret != 0) {
                syslog(LOG_ERR, "mqtt_connect failed");
                run = 0;
        }      
        return 0;
}

int tuya_mqtt_main_loop(struct tuya_mqtt_context *client)
{
        char mms[70];
        int k = 0;
        int ret = 0;

        struct MemData memory = {0};

        while(run) {
                tuya_mqtt_loop(client);
                sprintf(mms, "{\"cycle\":{\"free\":%d,\"shared\":%d}}", memory.free, memory.shared);
                tuyalink_thing_property_report(client, NULL, mms);
                if(k >= 4) 
                        k = 1;
                k++;
                ret = ubus_get_rout_data(&memory);
                if (ret != 0) 
                        syslog(LOG_ERR, "Ubus data get error");
                sleep(1);
        }
        return 0;
}

int tuya_mqtt_end(struct tuya_mqtt_context *client)
{
        tuya_mqtt_disconnect(client);
        tuya_mqtt_deinit(client);
        return 0;
}

int call_daem(void)
{
        int nochdir = 0;
        int noclose = 0;
        if(daemon(nochdir, noclose) != 0)
                syslog(LOG_ERR, "Daemon failled");
        return 0;
}

int ubus_get_rout_data(struct MemData *memory) {
        struct ubus_context *ctx;
        uint32_t id;
        int rc = 0;

        ctx = ubus_connect(NULL);
        if(!ctx) {
                syslog(LOG_ERR, "Failed to connect to ubus");
                return 1;
        }

        if (ubus_lookup_id(ctx, "system", &id) || ubus_invoke(ctx, id, "info", NULL, board_cb, memory, 3000)) {
                syslog(LOG_ERR, "cannot request memory info from procs");
                rc = 1;
	} 

        ubus_free(ctx);
        return rc;
}