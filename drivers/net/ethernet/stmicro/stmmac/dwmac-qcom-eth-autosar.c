/* SPDX-License-Identifier: GPL-2.0-only */
/* Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved. */

#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/if_ether.h>
#include <linux/ptp_clock_kernel.h>
#include <linux/ptp_clock.h>
#include "dwmac-qcom-ethqos.h"

// Define the structure
struct cnf_callback_structure {
	void (*txcnfcallback)(struct sk_buff *skb, u8 result);
	void (*rxcnfcallback) (struct sk_buff *skb);
};

// Create an instance of the structure
struct cnf_callback_structure cnf_callback_structure_t = {
	.txcnfcallback = NULL,
	.rxcnfcallback = NULL
};


/**
 *  EthWrapper_RegisterTxCnfCallback - Resgiter the callback
 *  @callback: function pointer.
 *  Description:
 *  Function to register the callback for Tx complete in the ETH wrapper API
 */
void ethWrapper_registertxcnfcallback(void (*callback)(struct sk_buff *skb, u8 result)) {
}

/**
 *  EthWrapper_HandleTxCompletion - Handle TX completion
 *  @skb: Pointer to the sk_buff structure
 *  @result: Result of the transmission
 *
 *  Description:
 *  This function handles the completion of a transmit operation. It invokes the registered
 *  callback function, if available, to notify the caller about the transmission result.
 */
void ethwrapper_handletxcompletion(struct sk_buff *skb, u8 result) {
}


/**
 *  EthWrapper_RegisterRxCnfCallback - Resgiter the callback
 *  @callback: function pointer.
 *  Description:
 *  Function to register the callback for Rx indication in the ETH wrapper API
 */
void ethWrapper_registerrxcnfcallback(void (*callback)(struct sk_buff *skb))
{
}

/**
 *  EthWrapper_HandleRICompletion - Handle RX indication completion
 *  @skb: Pointer to the sk_buff structure
 *
 *  Description:
 *  This function handles the completion of a receive indication. It invokes the registered
 *  callback function, if available, to notify the caller about the received packet.
 */
void ethwrapper_handlericompletion(struct sk_buff *skb)
{
}

/**
 *  EthDrv_allocateTxBuffer - Allocate transmit buffer
 *  @size: Size of the buffer to allocate
 *  Description-API to allocate Tx buffer.
 */
struct sk_buff *ethdrv_allocatetxbuffer(size_t size)
{
}

/**
 *  EthDrv_Transmit - Transmit the packet
 *  @skb: Pointer to the sk_buff structure
 *
 *  Description-
 *  API to transmit the packet. For the ethernet driver to transmit,
 *  the LG HAL layer needs to copy the Tx packet into SKB
 */
int ethdrv_transmit(struct sk_buff *skb)
{
}


/**
 *  EthDrv_GetCurSysTime - Get the current system time.
 *  @ts: Pointer to a struct timespec64 to store the current system time.
 *
 *  Description-
 *  API to get the current hardware time from Ethernet controller(ptp system time)
 */
void ethdrv_getcursystime(struct timespec64 *ts)
{
}


/**
 *  EthDrv_EnableTS - Enable hardware timestamping.
 *  @config: Pointer to a struct hwtstamp_config containing the configuration for
 *  hardware timestamping.
 *
 *  Description:
 *  This function enables hardware timestamping by calling the EthDrv_EnableTS_Wrapper function
 *  with the provided configuration.
 */
void ethdrv_enablets(struct hwtstamp_config *config)
{
}
