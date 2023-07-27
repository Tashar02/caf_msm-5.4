/* SPDX-License-Identifier: GPL-2.0-only */
/*Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.*/
#ifndef	_DWMAC_QCOM_ETH_AUTOSAR_H
#define	_DWMAC_QCOM_ETH_AUTOSAR_H

struct sk_buff *EthDrv_allocateTxBuffer(size_t);
int EthDrv_Transmit(struct sk_buff *);
void EthWrapper_RegisterTxCnfCallback(void (*callback)(struct sk_buff *skb, u8 result));
void EthWrapper_HandleTxCompletion(struct sk_buff *skb, u8 result);
void EthWrapper_HandleRICompletion(struct sk_buff *skb);
void EthWrapper_RegisterRxCnfCallback(void (*callback)(struct sk_buff *skb));
void EthDrv_GetCurSysTime(struct timespec64 *ts);
void EthDrv_EnableTS(struct hwtstamp_config *config);
#endif /* _DWMAC_QCOM_ETH_AUTOSAR_H */

