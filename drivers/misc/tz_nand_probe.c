// SPDX-License-Identifier: GPL-2.0-only
/*
 * QTI Secure Execution Environment Communicator (QSEECOM) driver
 * NAND controller TZ access support by using SCM call.
 * SCM call to reinit QPIC NAND controller from TZ.
 *
 * Copyright (c) 2021-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <soc/qcom/secure_buffer.h>
#include <linux/types.h>
#include <linux/dma-mapping.h>
#include <soc/qcom/qseecom_scm.h>
#include <soc/qcom/qseecomi.h>
#include <linux/delay.h>

#define QSEECOM_SCM_EBUSY_WAIT_MS 30
#define QSEECOM_SCM_EBUSY_MAX_RETRY 67

static dma_addr_t dma_pa;
static void *dma_va;

static void tz_release(struct device *dev)
{
	printk(KERN_ALERT "releasing tz device\n");
}

static struct device dev = {
	.release = tz_release
};

static void call_tz_nand_probe(uint32_t smc_id, struct scm_desc *desc)
{
	int ret = 0;
	int retry_count = 0;

	do {
		ret = qcom_scm_qseecom_call_noretry(smc_id, desc);
		if (ret != 0)
			msleep(QSEECOM_SCM_EBUSY_WAIT_MS);
		if (retry_count == 33)
			printk(KERN_ALERT "secure world has been busy for 1 second!\n");
	} while (ret != 0 && (retry_count++ < QSEECOM_SCM_EBUSY_MAX_RETRY));
	printk(KERN_ALERT "ret = %d!\n", ret);
}

int _tz_nand_probe(void)
{
	int ret = 0;
	struct scm_desc desc = {0};
	/* FLASH driver needs ~5K+ memory */
        uint32_t dma_pool_size=0x2000;

	ret = dev_set_name(&dev, "tz");
        if (ret)
             dev_err(&dev, "Error dev_set_name = %d.\n", ret);

	ret = device_register(&dev);
	if (ret) {
		put_device(&dev);
                dev_err(&dev, "Error device_register = %d.\n", ret);
	}

	ret = dma_set_coherent_mask(&dev, DMA_BIT_MASK(32));
        if (ret)
             dev_err(&dev, "Error dma_set_coherent_mask() = %d.\n", ret);

        dma_va = dma_alloc_coherent(&dev, dma_pool_size, &dma_pa, GFP_KERNEL);
	if (!dma_va){
		printk(KERN_ALERT "DN: failed a_alloc_coherent %s %d\n",__func__,__LINE__);
		return -ENOMEM;
	}
        desc.arginfo = TZ_OS_NAND_PROBE_STATUS_ID_PARAM_ID;
        desc.args[0] = (uint32_t)dma_pa;
        desc.args[1] = (uint32_t)dma_pool_size;
        pr_info("%s %d dma_pa:0x%x dma_va:0x%x dma_pool_size:0x%x\n",
			__func__,__LINE__, (uint32_t)dma_pa, (uint32_t)dma_va, dma_pool_size);
        memset((void*)dma_va, 0x0, dma_pool_size);
        call_tz_nand_probe(TZ_OS_NAND_PROBE_STATUS_ID, &desc);
	if (desc.ret[0] != 0)
		ret = -EIO;
        pr_info("desc ret[0]=%x ret[1]=%x\n",
		(uint32_t)desc.ret[0], (uint32_t)desc.ret[1]);
        dma_free_coherent(&dev, dma_pool_size, dma_va, dma_pa);

	return ret;
}

void _tz_nand_probe_exit(void)
{
	printk(KERN_ALERT "Exit NAND PROBE\n");
}
module_init(_tz_nand_probe);
module_exit(_tz_nand_probe_exit);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Qualcomm Technologies, Inc. TZ NAND PROBE driver");
