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

#define LOG_TAG "android.hardware.sensors@1.0-service.wt88047"

#include <android/hardware/sensors/1.0/ISensors.h>
#include <hidl/HidlSupport.h>
#include <binder/IPCThreadState.h>
#include <hidl/HidlTransportSupport.h>
#include <log/log.h>

using android::hardware::sensors::V1_0::ISensors;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;

int main() {
    configureRpcThreadpool(2, true);
    sp<ISensors> service = ISensors::getService("default", true /* getStub */);

    if (service == nullptr) {
        ALOGE("Could not get passthrough implementation for %s/%s.",
            ISensors::descriptor, "default");
        return 1;
    }

    android::status_t status = service->registerAsService("default");

    if (status == android::OK) {
        ALOGI("Registration complete for %s/%s.",
            ISensors::descriptor, "default");
    } else {
        ALOGE("Could not register service %s/%s (%d).",
            ISensors::descriptor, "default", status);
    }
    if (status != android::OK) {
        return 1;
    }
    android::IPCThreadState::self()->joinThreadPool();
    return 0;
}
