/*
	Copyright 2022 AUCOHL

	Author: Mohamed Shalan (mshalan@aucegypt.edu)

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef AUCOHL_UART_H
#define AUCOHL_UART_H

#ifndef IO_TYPES
#define IO_TYPES
#define   __R     volatile const unsigned int
#define   __W     volatile       unsigned int
#define   __RW    volatile       unsigned int
#endif

#define AUCOHL_UART_CONTROL_REG_ENABLE_BIT	0
#define AUCOHL_UART_CONTROL_REG_ENABLE_MASK	0x1
#define AUCOHL_UART_CONTROL_REG_TX_EN_BIT	1
#define AUCOHL_UART_CONTROL_REG_TX_EN_MASK	0x2
#define AUCOHL_UART_CONTROL_REG_RX_EN_BIT	2
#define AUCOHL_UART_CONTROL_REG_RX_EN_MASK	0x4
#define AUCOHL_UART_CONTROL_REG_LOOPBACK_EN_BIT	3
#define AUCOHL_UART_CONTROL_REG_LOOPBACK_EN_MASK	0x8
#define AUCOHL_UART_CONTROL_REG_GLITCH_FILTER_EN_BIT	4
#define AUCOHL_UART_CONTROL_REG_GLITCH_FILTER_EN_MASK	0x10
#define AUCOHL_UART_CONFIG_REG_DATA_SIZE_BIT	0
#define AUCOHL_UART_CONFIG_REG_DATA_SIZE_MASK	0xf
#define AUCOHL_UART_CONFIG_REG_STOP_BITS_COUNT_BIT	4
#define AUCOHL_UART_CONFIG_REG_STOP_BITS_COUNT_MASK	0x10
#define AUCOHL_UART_CONFIG_REG_PARITY_TYPE_BIT	5
#define AUCOHL_UART_CONFIG_REG_PARITY_TYPE_MASK	0xe0
#define AUCOHL_UART_CONFIG_REG_TIMEOUT_BITS_BIT	8
#define AUCOHL_UART_CONFIG_REG_TIMEOUT_BITS_MASK	0x3f00
#define AUCOHL_UART_FIFO_CONTROL_REG_TXFIFOTR_BIT	0
#define AUCOHL_UART_FIFO_CONTROL_REG_TXFIFOTR_MASK	0x1ff
#define AUCOHL_UART_FIFO_CONTROL_REG_RXFIFOTR_BIT	8
#define AUCOHL_UART_FIFO_CONTROL_REG_RXFIFOTR_MASK	0x1ff00
#define AUCOHL_UART_FIFO_STATUS_REG_RX_LEVEL_BIT	0
#define AUCOHL_UART_FIFO_STATUS_REG_RX_LEVEL_MASK	0x1ff
#define AUCOHL_UART_FIFO_STATUS_REG_TX_LEVEL_BIT	8
#define AUCOHL_UART_FIFO_STATUS_REG_TX_LEVEL_MASK	0x1ff00

#define AUCOHL_UART_TX_EMPTY_FLAG	0x1
#define AUCOHL_UART_RX_FULL_FLAG	0x2
#define AUCOHL_UART_TX_LEVEL_BELOW_FLAG	0x4
#define AUCOHL_UART_RX_LEVEL_ABOVE_FLAG	0x8
#define AUCOHL_UART_BREAK_FLAG	0x10
#define AUCOHL_UART_MATCH_FLAG	0x20
#define AUCOHL_UART_FRAME_ERROR_FLAG	0x40
#define AUCOHL_UART_PARITY_ERROR_FLAG	0x80
#define AUCOHL_UART_OVERRUN_FLAG	0x100
#define AUCOHL_UART_TIMEOUT_FLAG	0x200

typedef struct _AUCOHL_UART_TYPE_ {
	__R 	rxdata;
	__W 	txdata;
	__W 	prescaler;
	__W 	control;
	__W 	config;
	__W 	fifo_control;
	__R 	fifo_status;
	__W 	match;
	__R 	reserved[952];
	__W 	icr;
	__R 	ris;
	__RW	im;
	__R 	mis;
} AUCOHL_UART_TYPE;

#endif

