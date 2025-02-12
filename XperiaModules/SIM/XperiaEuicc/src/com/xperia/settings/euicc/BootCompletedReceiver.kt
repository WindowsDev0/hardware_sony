/*
 * Copyright (C) 2024 XperiaLabs Project
 * Copyright (C) 2021 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

package com.xperia.settings.euicc

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.util.Log

class BootCompletedReceiver : BroadcastReceiver() {
    override fun onReceive(context: Context, intent: Intent) {
        Log.d(TAG, "Received boot completed intent")
        EuiccDisabler.enableOrDisableEuicc(context)
    }

    companion object {
        private const val TAG = "XperiaEuicc"
    }
}
