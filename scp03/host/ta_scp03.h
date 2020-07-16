/* SPDX-License-Identifier: BSD-3-Clause */
/* Copyright (c) 2020, Foundries.IO */

#ifndef __TA_SCP03_H
#define __TA_SCP03_H

#define PTA_SCP03_UUID { 0xbe0e5821, 0xe718 ,0x4f77, \
			{ 0xab, 0x3e, 0x8e ,0x6c ,0x73 ,0xa9 ,0xc7, 0x35 } }

/*
 * Enable SCP03 support on the SE. Rotate scp03 keys if requested
 *
 * in	params[0].a = operation

 */
#define PTA_CMD_ENABLE_SCP03		0

#endif /*__TA_SCP03_H*/
