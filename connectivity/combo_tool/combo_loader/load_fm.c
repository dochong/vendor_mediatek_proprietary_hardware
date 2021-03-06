/*
*FM radio driver kernel module insmod file for wmt dynamic loader
*/
#include "loader.h"

#define FMR_MODULES_PATH "/system/lib/modules/mtk_fm_drv.ko"

//insmod
static int insmod(const char *filename, const char *args)
{
    void *module;
    unsigned int size;
    int ret = -1;
    int retry = 10;

    ALOGI("filename(%s)\n", filename);

    module = load_file(filename, &size);
    if (!module) {
        ALOGE("load file fail\n");
        return -1;
    }

    while (retry-- > 0) {
        ret = init_module(module, size, args);
        if (ret < 0) {
            ALOGE("insmod module fail(%d)\n", ret);
            usleep(10000);
        } else
            break;
    }

    free(module);

    return ret;
}

int load_fm_module(__attribute__((unused))int chip_id)
{
    int ret = -1;

    ret = insmod(FMR_MODULES_PATH, "");
    ALOGI("insert mtk_fm_drv.ko %s (%d)\n", ret ? "fail" : "ok", ret);

    return ret;
}

