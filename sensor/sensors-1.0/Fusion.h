/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _FUSION_SENSOR_H_
#define _FUSION_SENSOR_H_

#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>


#include "SensorContext.h"
#include "SensorBase.h"
#include "SensorEventReader.h"
#include <linux/hwmsensor.h>
#include "hwmsen_custom.h"

#ifdef FUSION_ALGORITHM_IN_SENSORHUB
class FusionSensor : public SensorBase {
private:
    enum fusion_handle {
        orientation,
        grv,
        gmrv,
        rv,
        la,
        grav,
        ungyro,
        unmag,
        pdr,
        gyro_temperature,
        max_fusion_support,
    };
    int mEnabled[max_fusion_support];
    sensors_event_t mPendingEvent;
    SensorEventCircularReader mSensorReader;
    int64_t mEnabledTime[max_fusion_support];
    uint32_t mFlushCnt[max_fusion_support];
    char input_sysfs_path[PATH_MAX];
    int input_sysfs_path_len;
    int mDataDiv[max_fusion_support];

    void processEvent(struct sensor_event const *event);
    int HandleToIndex(int handle);

public:
            FusionSensor();
    virtual ~FusionSensor();
    virtual int readEvents(sensors_event_t* data, int count);
    virtual int setDelay(int32_t handle, int64_t ns);
    virtual int enable(int32_t handle, int enabled);
    virtual int batch(int handle, int flags, int64_t samplingPeriodNs, int64_t maxBatchReportLatencyNs);
    virtual int flush(int handle);
    virtual int getFd() {
        return mSensorReader.getReadFd();
    };
};
#else
#include "VendorInterface.h"
#include "MtkInterface.h"
#include "SensorManager.h"
#include "SensorCalibration.h"

struct sensorInfo {
    int mEnabled;
    int64_t samplingPeriodNs;
    int64_t batchReportLatencyNs;
    uint32_t mFlushCnt;
    bool useAccData;
    bool useGyroData;
    bool useMagData;
};

class FusionSensor : public SensorBase {
private:
    enum fusion_handle {
        orientation,
        grv,
        gmrv,
        rv,
        la,
        grav,
        ungyro,
        unmag,
        pdr,
        max_fusion_support,
    };
    sensors_event_t mPendingEvent;
    struct sensorInfo mSensorInfo[max_fusion_support];
    int64_t bestSamplingPeriodNs;
    int64_t bestBatchReportLatencyNs;
    int mWritePipeFd;
    BaseInterface *mBaseInterface;
    SensorManager *mSensorManager;
    SensorConnection *mSensorConnection;
    int gyroEnabledCount;
    int accEnabledCount;
    int magEnabledCount;
    SensorEventCircularReader mSensorReader;
    SensorCalibration *mSensorCalibration;

protected:
    void processEvent(struct sensor_event const *event);
    int HandleToIndex(int handle);
    int reportFlush(int handle);
    int reportData(int handle, struct sensorData *data);
    int selectBestSampleLatency();
    int getFusionAndReport();
    int getUncaliGyroAndReport(sensors_event_t *data);
    int getUncaliMagAndReport(sensors_event_t *data);
public:
            FusionSensor();
    virtual ~FusionSensor();
    virtual int readEvents(sensors_event_t* data, int count);
    virtual int setDelay(int32_t handle, int64_t ns);
    virtual int enable(int32_t handle, int enabled);
    virtual int batch(int handle, int flags, int64_t samplingPeriodNs, int64_t maxBatchReportLatencyNs);
    virtual int flush(int handle);
    virtual int setEvent(sensors_event_t *data);
    virtual int getFd() {
        return mSensorReader.getReadFd();
    };
};
#endif
#endif  // ANDROID_FUSION_SENSOR_H
