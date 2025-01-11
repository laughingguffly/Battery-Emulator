#include "USER_SETTINGS.h"
#include <string>
#include "src/devboard/hal/hal.h"

/* This file contains all the battery settings and limits */
/* They can be defined here, or later on in the WebUI */
/* Most important is to select which CAN interface each component is connected to */
/* 
CAN_NATIVE = Native CAN port on the LilyGo & Stark hardware
CANFD_NATIVE = Native CANFD port on the Stark CMR hardware
CAN_ADDON_MCP2515 = Add-on CAN MCP2515 connected to GPIO pins
CANFD_ADDON_MCP2518 = Add-on CAN-FD MCP2518 connected to GPIO pins
*/

volatile CAN_Configuration can_config = {
    .battery = CAN_NATIVE,   // Which CAN is your battery connected to?
    .inverter = CAN_NATIVE,  // Which CAN is your inverter connected to? (No need to configure incase you use RS485)
    .battery_double = CAN_ADDON_MCP2515,  // (OPTIONAL) Which CAN is your second battery connected to?
    .charger = CAN_NATIVE,                // (OPTIONAL) Which CAN is your charger connected to?
    .shunt = CAN_NATIVE                   // (OPTIONAL) Which CAN is your shunt connected to?
};

#ifdef WIFI

volatile uint8_t AccessPointEnabled = false;           //Set to either true/false to enable direct wifi access point
std::string ssid = "Thor2g";          // Maximum of 63 characters
std::string password = "iloveeddy";  // Minimum of 8 characters
const char* ssidAP = "Battery Emulator";  // Maximum of 63 characters, also used for device name on web interface
const char* passwordAP = "rkekej";  // Minimum of 8 characters; set to NULL if you want the access point to be open
const uint8_t wifi_channel = 0;        // Set to 0 for automatic channel selection

#ifdef WIFICONFIG
// Set your Static IP address
IPAddress local_IP(192, 168, 10, 150);
// Set your Gateway IP address
IPAddress gateway(192, 168, 10, 1);
// Set your Subnet IP address
IPAddress subnet(255, 255, 255, 0);
#endif
#ifdef WEBSERVER
const char* http_username = "ed";  // username to webserver authentication;
const char* http_password = "ed4901780";  // password to webserver authentication;

#endif  // WEBSERVER
// MQTT
#ifdef MQTT
const char* mqtt_user = "freezer";      // Set NULL for no username
const char* mqtt_password = "H87UHM876876812";  // Set NULL for no password
#ifdef MQTT_MANUAL_TOPIC_OBJECT_NAME
const char* mqtt_topic_name =
    "pebbles/battery";  // Custom MQTT topic name. Previously, the name was automatically set to "battery-emulator_esp32-XXXXXX"
const char* mqtt_object_id_prefix =
    "be_";  // Custom prefix for MQTT object ID. Previously, the prefix was automatically set to "esp32-XXXXXX_"
const char* mqtt_device_name =
    "Battery Emulator";  // Custom device name in Home Assistant. Previously, the name was automatically set to "BatteryEmulator_esp32-XXXXXX"
#endif  // MQTT_MANUAL_TOPIC_OBJECT_NAME
#endif  // USE_MQTT
#endif  // WIFI

#ifdef EQUIPMENT_STOP_BUTTON
// Equipment stop button behavior. Use NC button for safety reasons.
//LATCHING_SWITCH  - Normally closed (NC), latching switch. When pressed it activates e-stop
//MOMENTARY_SWITCH - Short press to activate e-stop, long 15s press to deactivate. E-stop is persistent between reboots
volatile STOP_BUTTON_BEHAVIOR equipment_stop_behavior = LATCHING_SWITCH;
#endif

/* Charger settings (Optional, when using generator charging) */
volatile float CHARGER_SET_HV = 384;      // Reasonably appropriate 4.0v per cell charging of a 96s pack
volatile float CHARGER_MAX_HV = 420;      // Max permissible output (VDC) of charger
volatile float CHARGER_MIN_HV = 200;      // Min permissible output (VDC) of charger
volatile float CHARGER_MAX_POWER = 3300;  // Max power capable of charger, as a ceiling for validating config
volatile float CHARGER_MAX_A = 11.5;      // Max current output (amps) of charger
volatile float CHARGER_END_A = 1.0;       // Current at which charging is considered complete
