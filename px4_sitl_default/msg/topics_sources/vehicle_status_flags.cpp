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

/* Auto-generated by genmsg_cpp from file vehicle_status_flags.msg */


#include <inttypes.h>
#include <px4_platform_common/log.h>
#include <px4_platform_common/defines.h>
#include <uORB/topics/vehicle_status_flags.h>
#include <drivers/drv_hrt.h>
#include <lib/drivers/device/Device.hpp>

constexpr char __orb_vehicle_status_flags_fields[] = "uint64_t timestamp;bool condition_calibration_enabled;bool condition_system_sensors_initialized;bool condition_system_hotplug_timeout;bool condition_system_returned_to_home;bool condition_auto_mission_available;bool condition_global_position_valid;bool condition_home_position_valid;bool condition_local_position_valid;bool condition_local_velocity_valid;bool condition_local_altitude_valid;bool condition_power_input_valid;bool condition_battery_healthy;bool condition_escs_error;bool circuit_breaker_engaged_power_check;bool circuit_breaker_engaged_airspd_check;bool circuit_breaker_engaged_enginefailure_check;bool circuit_breaker_flight_termination_disabled;bool circuit_breaker_engaged_usb_check;bool circuit_breaker_engaged_posfailure_check;bool circuit_breaker_vtol_fw_arming_check;bool offboard_control_signal_found_once;bool offboard_control_signal_lost;bool offboard_control_set_by_command;bool offboard_control_loss_timeout;bool rc_signal_found_once;bool rc_input_blocked;bool rc_calibration_valid;bool vtol_transition_failure;bool usb_connected;bool avoidance_system_required;bool avoidance_system_valid;uint8_t[1] _padding0;";

ORB_DEFINE(vehicle_status_flags, struct vehicle_status_flags_s, 39, __orb_vehicle_status_flags_fields);


void print_message(const vehicle_status_flags_s& message)
{

	PX4_INFO_RAW(" vehicle_status_flags_s\n");
	if (message.timestamp != 0) {
		PX4_INFO_RAW("\ttimestamp: %" PRIu64 "  (%.6f seconds ago)\n", message.timestamp, hrt_elapsed_time(&message.timestamp) / 1e6);
	} else {
		PX4_INFO_RAW("\n");
	}
	PX4_INFO_RAW("\tcondition_calibration_enabled: %s\n", (message.condition_calibration_enabled ? "True" : "False"));
	PX4_INFO_RAW("\tcondition_system_sensors_initialized: %s\n", (message.condition_system_sensors_initialized ? "True" : "False"));
	PX4_INFO_RAW("\tcondition_system_hotplug_timeout: %s\n", (message.condition_system_hotplug_timeout ? "True" : "False"));
	PX4_INFO_RAW("\tcondition_system_returned_to_home: %s\n", (message.condition_system_returned_to_home ? "True" : "False"));
	PX4_INFO_RAW("\tcondition_auto_mission_available: %s\n", (message.condition_auto_mission_available ? "True" : "False"));
	PX4_INFO_RAW("\tcondition_global_position_valid: %s\n", (message.condition_global_position_valid ? "True" : "False"));
	PX4_INFO_RAW("\tcondition_home_position_valid: %s\n", (message.condition_home_position_valid ? "True" : "False"));
	PX4_INFO_RAW("\tcondition_local_position_valid: %s\n", (message.condition_local_position_valid ? "True" : "False"));
	PX4_INFO_RAW("\tcondition_local_velocity_valid: %s\n", (message.condition_local_velocity_valid ? "True" : "False"));
	PX4_INFO_RAW("\tcondition_local_altitude_valid: %s\n", (message.condition_local_altitude_valid ? "True" : "False"));
	PX4_INFO_RAW("\tcondition_power_input_valid: %s\n", (message.condition_power_input_valid ? "True" : "False"));
	PX4_INFO_RAW("\tcondition_battery_healthy: %s\n", (message.condition_battery_healthy ? "True" : "False"));
	PX4_INFO_RAW("\tcondition_escs_error: %s\n", (message.condition_escs_error ? "True" : "False"));
	PX4_INFO_RAW("\tcircuit_breaker_engaged_power_check: %s\n", (message.circuit_breaker_engaged_power_check ? "True" : "False"));
	PX4_INFO_RAW("\tcircuit_breaker_engaged_airspd_check: %s\n", (message.circuit_breaker_engaged_airspd_check ? "True" : "False"));
	PX4_INFO_RAW("\tcircuit_breaker_engaged_enginefailure_check: %s\n", (message.circuit_breaker_engaged_enginefailure_check ? "True" : "False"));
	PX4_INFO_RAW("\tcircuit_breaker_flight_termination_disabled: %s\n", (message.circuit_breaker_flight_termination_disabled ? "True" : "False"));
	PX4_INFO_RAW("\tcircuit_breaker_engaged_usb_check: %s\n", (message.circuit_breaker_engaged_usb_check ? "True" : "False"));
	PX4_INFO_RAW("\tcircuit_breaker_engaged_posfailure_check: %s\n", (message.circuit_breaker_engaged_posfailure_check ? "True" : "False"));
	PX4_INFO_RAW("\tcircuit_breaker_vtol_fw_arming_check: %s\n", (message.circuit_breaker_vtol_fw_arming_check ? "True" : "False"));
	PX4_INFO_RAW("\toffboard_control_signal_found_once: %s\n", (message.offboard_control_signal_found_once ? "True" : "False"));
	PX4_INFO_RAW("\toffboard_control_signal_lost: %s\n", (message.offboard_control_signal_lost ? "True" : "False"));
	PX4_INFO_RAW("\toffboard_control_set_by_command: %s\n", (message.offboard_control_set_by_command ? "True" : "False"));
	PX4_INFO_RAW("\toffboard_control_loss_timeout: %s\n", (message.offboard_control_loss_timeout ? "True" : "False"));
	PX4_INFO_RAW("\trc_signal_found_once: %s\n", (message.rc_signal_found_once ? "True" : "False"));
	PX4_INFO_RAW("\trc_input_blocked: %s\n", (message.rc_input_blocked ? "True" : "False"));
	PX4_INFO_RAW("\trc_calibration_valid: %s\n", (message.rc_calibration_valid ? "True" : "False"));
	PX4_INFO_RAW("\tvtol_transition_failure: %s\n", (message.vtol_transition_failure ? "True" : "False"));
	PX4_INFO_RAW("\tusb_connected: %s\n", (message.usb_connected ? "True" : "False"));
	PX4_INFO_RAW("\tavoidance_system_required: %s\n", (message.avoidance_system_required ? "True" : "False"));
	PX4_INFO_RAW("\tavoidance_system_valid: %s\n", (message.avoidance_system_valid ? "True" : "False"));
	
}
