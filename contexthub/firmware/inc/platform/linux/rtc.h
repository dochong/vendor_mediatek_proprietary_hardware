/*
 * Copyright (C) 2016 The Android Open Source Project
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

#ifndef _LNX_RTC_H_
#define _LNX_RTC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <seos.h>

#define RTC_ERR_TOO_BIG         -1
#define RTC_ERR_TOO_SMALL       -2
#define RTC_ERR_INTERNAL        -3
#define RTC_ERR_ACCURACY_UNMET  -4

void rtcInit(void);
int rtcSetWakeupTimer(uint64_t delay, int ppm);

#ifdef __cplusplus
}
#endif

#endif
