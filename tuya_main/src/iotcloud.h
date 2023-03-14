struct MemData {
        int free;
        int shared;
};

enum {
        TOTAL_MEMORY,
        FREE_MEMORY,
        SHARED_MEMORY,
        __MEMORY_MAX,
};

enum {
        MEMORY_DATA,
        __INFO_MAX,
};

int tuya_cloud_start(struct tuya_mqtt_context *client, struct arguments *arguments);
int tuya_mqtt_main_loop(struct tuya_mqtt_context *client); 
int tuya_mqtt_end(struct tuya_mqtt_context *client);
int new_file_append(void);

int call_daem(void);

int ubus_get_rout_data(struct MemData *memory);