/*
 * Copyright (C) 2024 XperiaLabs Project
 * Copyright (C) 2022 The LineageOS Project
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

#define LOG_TAG "vendor.lineage.powershare@1.0-service.sony"

#include <android-base/logging.h>
#include <binder/ProcessState.h>
#include <hidl/HidlTransportSupport.h>
#include <powershare/sony/PowerShare.h>

using ::android::OK;
using ::android::sp;
using ::android::status_t;
using ::android::hardware::configureRpcThreadpool;
using ::android::hardware::joinRpcThreadpool;

using ::vendor::lineage::powershare::V1_0::IPowerShare;
using ::vendor::lineage::powershare::V1_0::implementation::PowerShare;

int main() {
    status_t status = OK;

    android::ProcessState::initWithDriver("/dev/vndbinder");

    LOG(INFO) << "PowerShare HAL service is starting.";

    sp<IPowerShare> ps = new PowerShare();

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    status = ps->registerAsService();
    if (status != OK) {
        LOG(ERROR) << "Could not register service for PowerShare HAL service ("
                   << status << ")";
        goto shutdown;
    }

    LOG(INFO) << "PowerShare HAL service is ready.";
    joinRpcThreadpool();
    // Should not pass this line

shutdown:
    // In normal operation, we don't expect the thread pool to shutdown
    LOG(ERROR) << "PowerShare HAL service is shutting down.";
    return 1;
}
