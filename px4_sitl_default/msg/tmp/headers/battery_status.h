/****************************************************************************
 *
 *   Copyright (C) 2013-2016 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/* Auto-generated by genmsg_cpp from file battery_status.msg */


#pragma once


#include <uORB/uORB.h>


#ifndef __cplusplus
#define BATTERY_STATUS_BATTERY_WARNING_NONE 0
#define BATTERY_STATUS_BATTERY_WARNING_LOW 1
#define BATTERY_STATUS_BATTERY_WARNING_CRITICAL 2
#define BATTERY_STATUS_BATTERY_WARNING_EMERGENCY 3
#define BATTERY_STATUS_BATTERY_WARNING_FAILED 4

#endif


#ifdef __cplusplus
struct __EXPORT battery_status_s {
#else
struct battery_status_s {
#endif
	uint64_t timestamp;
	float voltage_v;
	float voltage_filtered_v;
	float current_a;
	float current_filtered_a;
	float average_current_a;
	float discharged_mah;
	float remaining;
	float scale;
	float temperature;
	int32_t cell_count;
	float voltage_cell_v[4];
	float max_cell_voltage_delta;
	uint16_t capacity;
	uint16_t cycle_count;
	uint16_t run_time_to_empty;
	uint16_t average_time_to_empty;
	uint16_t serial_number;
	bool connected;
	bool system_source;
	uint8_t priority;
	uint8_t id;
	bool is_powering_off;
	uint8_t warning;
	uint8_t _padding0[4]; // required for logger


#ifdef __cplusplus
	static constexpr uint8_t BATTERY_WARNING_NONE = 0;
	static constexpr uint8_t BATTERY_WARNING_LOW = 1;
	static constexpr uint8_t BATTERY_WARNING_CRITICAL = 2;
	static constexpr uint8_t BATTERY_WARNING_EMERGENCY = 3;
	static constexpr uint8_t BATTERY_WARNING_FAILED = 4;

#endif
};

/* register this as object request broker structure */
ORB_DECLARE(battery_status);


#ifdef __cplusplus
void print_message(const battery_status_s& message);
#endif
