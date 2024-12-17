#ifndef _COMM_CAN_H_
#define _COMM_CAN_H_

#include "../../include.h"

#include "../../datalayer/datalayer.h"
#include "../../devboard/utils/events.h"
#include "../../devboard/utils/value_mapping.h"
#include "../../lib/me-no-dev-ESPAsyncWebServer/src/ESPAsyncWebServer.h"
#include "../../lib/miwagner-ESP32-Arduino-CAN/ESP32CAN.h"
#ifdef CAN_ADDON
#include "../../lib/pierremolinaro-acan2515/ACAN2515.h"
#endif  //CAN_ADDON
#ifdef CANFD_ADDON
#include "../../lib/pierremolinaro-ACAN2517FD/ACAN2517FD.h"
#endif  //CANFD_ADDON

enum frameDirection { MSG_RX, MSG_TX };  //RX = 0, TX = 1

/**
 * @brief Initialization function for CAN.
 *
 * @param[in] void
 *
 * @return void
 */
void init_CAN();

/**
 * @brief Transmit one CAN frame
 *
 * @param[in] CAN_frame* tx_frame
 * @param[in] int interface
 *
 * @return void
 */
void transmit_can();

/**
 * @brief Send CAN messages to all components 
 *
 * @param[in] void
 *
 * @return void
 */
void send_can();

/**
 * @brief Receive CAN messages from all interfaces 
 *
 * @param[in] void
 *
 * @return void
 */
void receive_can();

/**
 * @brief Receive CAN messages from CAN tranceiver natively installed on Lilygo hardware
 *
 * @param[in] void
 *
 * @return void
 */
void receive_can_native();

/**
 * @brief Receive CAN messages from CAN addon chip
 *
 * @param[in] void
 *
 * @return void
 */
void receive_can_addon();

/**
 * @brief Receive CAN messages from CANFD addon chip
 *
 * @param[in] void
 *
 * @return void
 */
void receive_canfd_addon();

/**
 * @brief print CAN frames via USB
 *
 * @param[in] void
 *
 * @return void
 */
void print_can_frame(CAN_frame frame, frameDirection msgDir);

#endif
