/*
 * Copyright 2018 Rockchip Electronics Co. LTD
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
 *
 */


#define LOG_TAG "RkAudioSetting-service"
#include <log/log.h>
#include <string.h>
#include "RkAudioSetting.h"

namespace android {

static RkAudioSettingManager* sAudioSetting = NULL;
static bool sXMLReady = false;

RkAudioSetting::RkAudioSetting() {
    int tryNum = 5;
    if (sAudioSetting == NULL) {
        sAudioSetting = new RkAudioSettingManager();
        while (tryNum >= 0) {
            if (sAudioSetting->init() < 0) {
                ALOGD("try init audiosetting tryNum = %d", tryNum);
                tryNum--;
                sXMLReady = false;
            } else {
                sXMLReady = true;
                break;
            }
        }
    }

    mAudioSetting = sAudioSetting;
    mXMLReady = sXMLReady;
}

RkAudioSetting::~RkAudioSetting() {
}

void RkAudioSetting::setSelect(int device) {
    if (mXMLReady) {
        mAudioSetting->setDevice(device);
    }
}

void RkAudioSetting::setFormat(int device, int close, const char * format) {
    if (mXMLReady) {
        mAudioSetting->setFormat(device, close, format);
    }
}

void RkAudioSetting::setMode(int device, int mode) {
    if (mXMLReady) {
        mAudioSetting->setMode(device, mode);
    }
}

int RkAudioSetting::getSelect(int device) {
    int val = 0;
    if (mXMLReady) {
        val = mAudioSetting->checkDevice(device);
    }
    return val;
}

int RkAudioSetting::getMode(int device) {
    int val = 0;
    if (mXMLReady) {
        val = mAudioSetting->getMode(device);
    }
    return val;
}

int RkAudioSetting::getFormat(int device, const char *format) {
    int val = 0;
    if (mXMLReady) {
        val = mAudioSetting->getFormat(device, format);
    }
    return val;
}

void RkAudioSetting::updataFormatForEdid() {
    if (mXMLReady) {
        mAudioSetting->updataFormatByHdmiEdid();
    }
}

}
