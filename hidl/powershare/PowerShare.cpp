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
#include <android-base/strings.h>
#include <fstream>
#include <powershare/sony/PowerShare.h>

namespace vendor {
namespace lineage {
namespace powershare {
namespace V1_0 {
namespace implementation {

template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    file << value;
}

template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);
    T result;

    file >> result;
    return file.fail() ? def : result;
}

Return<bool> PowerShare::isEnabled() {
    const auto value = get<std::string>(WIRELESS_TX_ENABLE_PATH, "0");
    return !(value == "disable" || value == "0");
}

Return<bool> PowerShare::setEnabled(bool enable) {
    set(WIRELESS_TX_ENABLE_PATH, enable ? 1 : 0);

    return isEnabled();
}

Return<uint32_t> PowerShare::getMinBattery() {
    return 0;
}

Return<uint32_t> PowerShare::setMinBattery(uint32_t /*minBattery*/) {
    return getMinBattery();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace powershare
}  // namespace lineage
}  // namespace vendor
