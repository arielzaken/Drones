#ifndef _CONFIG_H
#define _CONFIG_H
#include <Arduino.h>
#include <BluetoothSerial.h>

/****************
 * debug CONFIG *
 ***************/
#define DEBUG_PRINT_SERIAL HardwareSerial
//#define DEBUG_PRINT_SERIAL BluetoothSerial

#define DEBUG_PRINT_DELAY 200

/*************************
 * HEIGHT CHANNEL CONFIG *
 ************************/
#define HEIGHT_CHANNEL 400 // [cm] the height of the craft at transit

/******************
 * ALT PID CONFIG *
 *****************/
#define MAX_ALT 200 // [cm] the maximum altitude allowed for the craft
//#define H 5.0 // [m] the target altitude for the craft to hover over

#define ALT_PID_P 5
#define ALT_PID_I 0
#define ALT_PID_D 0


/******************
 *   GPS CONFIG   *
 *****************/
#define ERROR_RADIUS 300 // [cm] the error radius in which two locations are considered the same


/*******************
 * ALTITUDE CONFIG *
 ******************/
#define ALTITUDE_ERROR_RANGE 10 // [cm] the error radius in which the alttitude is equals


/**************
 * MSP CONFIG *
 *************/
#define MSP_STATUS               101    //out message         cycletime & errors_count & sensor present & box activation & current setting number
#define MSP_RAW_IMU              102    //out message         9 DOF
#define MSP_SERVO                103    //out message         servos
#define MSP_MOTOR                104    //out message         motors
#define MSP_RC                   105    //out message         rc channels and more
#define MSP_RAW_GPS              106    //out message         fix, numsat, lat, lon, alt, speed, ground course
#define MSP_COMP_GPS             107    //out message         distance home, direction home
#define MSP_ATTITUDE             108    //out message         2 angles 1 heading
#define MSP_ALTITUDE             109    //out message         altitude, variometer
#define MSP_ANALOG               110    //out message         vbat, powermetersum, rssi if available on RX
#define MSP_RC_TUNING            111    //out message         rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_PID                  112    //out message         P I D coeff (9 are used currently)

#define MSP_ACC_CALIBRATION      205    //in  message         callebrate the accelerometer


/***************
 * Ibus CONFIG *
 **************/
#define IBUS_BAUD_RATE 115200
#define IBUS_SEND_INTERVAL_MS 100
#define IBUS_PACKET_BYTES_COUNT 32
#define IBUS_CHANNELS_COUNT 14
#define MIN_CONTROL_VALUE 1000
#define MAX_CONTROL_VALUE 2000

/*********************
 * Controller CONFIG *
 ********************/
#define ARM_CHANNEL 4
#define ARM_VAL 1800
#define DISARM_VAL 1000
#define ARM_DEFULATE_VALUE 1000

#define ROLL_CHANNEL 0
#define ROLL_DEFAULT_VALUE 1500

#define PITCH_CHANNEL 1
#define PITCH_DEFAULT_VALUE 1500

#define YAW_CHANNEL 2
#define YAW_DEFAULT_VALUE 1500

#define THROTTLE_CHANNEL 3
#define THROTTLE_DEFAULT_VALUE 1000

#define AUX_DEFAULT_VALUE 1500

/******************
 * transit CONFIG *
 *****************/
#define STOP_YAW 1500
#define FORWARD_YAW STOP_YAW + 40
#define BACKWARDS_YAW STOP_YAW - 40


#endif // _CONFIG_H