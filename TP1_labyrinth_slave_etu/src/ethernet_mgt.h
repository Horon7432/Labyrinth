/*
 * ethernet_mgt.h
 *
 * Created on: 8.2.2016
 * Author: Pilloux V.
 */

#ifndef ETHERNET_MGT_H_
#define ETHERNET_MGT_H_

/* Description: callback prototype for ethernet_init()
 *
 * Parameter: data: pointer on data to be received
 *            length: data length [bytes]
 */
typedef void (*rx_callback_t)(void *data, int len);

/* Description: initialise Ethernet connection.
 *
 * Parameter: rx_callback: pointer on a callback function which is called
 *            each time data is received by Ethernet. If rx_callback==NULL,
 *            no callback is used.
 */
void ethernet_init(rx_callback_t rx_callback);

/* Description: send raw data to Ethernet (no address management)
 *
 * Parameter: data: pointer on data to be sent
 *            length: data length [bytes]
 */
void send_eth(void *data, int length);

/* Description: receive raw data from Ethernet (no address management).
 *              This function blocks until data is received.
 *
 * Parameter: data: pointer on data to be received
 *            length: data length [bytes]
 */
void rec_eth(void *data, int length);

#endif /* ETHERNET_MGT_H_ */
