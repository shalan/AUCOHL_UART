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

#define AUCOHL_UART_CTRL_REG_EN_BIT	0
#define AUCOHL_UART_CTRL_REG_EN_MASK	0x1
#define AUCOHL_UART_CTRL_REG_TXEN_BIT	1
#define AUCOHL_UART_CTRL_REG_TXEN_MASK	0x2
#define AUCOHL_UART_CTRL_REG_RXEN_BIT	2
#define AUCOHL_UART_CTRL_REG_RXEN_MASK	0x4
#define AUCOHL_UART_CTRL_REG_LPEN_BIT	3
#define AUCOHL_UART_CTRL_REG_LPEN_MASK	0x8
#define AUCOHL_UART_CTRL_REG_GFEN_BIT	4
#define AUCOHL_UART_CTRL_REG_GFEN_MASK	0x10
#define AUCOHL_UART_CFG_REG_WLEN_BIT	0
#define AUCOHL_UART_CFG_REG_WLEN_MASK	0xf
#define AUCOHL_UART_CFG_REG_STP2_BIT	4
#define AUCOHL_UART_CFG_REG_STP2_MASK	0x10
#define AUCOHL_UART_CFG_REG_PARITY_BIT	5
#define AUCOHL_UART_CFG_REG_PARITY_MASK	0xe0
#define AUCOHL_UART_CFG_REG_TIMEOUT_BIT	8
#define AUCOHL_UART_CFG_REG_TIMEOUT_MASK	0x3f00
#define AUCOHL_UART_FIFOCTRL_REG_TXLT_BIT	0
#define AUCOHL_UART_FIFOCTRL_REG_TXLT_MASK	0xf
#define AUCOHL_UART_FIFOCTRL_REG_RXLT_BIT	8
#define AUCOHL_UART_FIFOCTRL_REG_RXLT_MASK	0xf00
#define AUCOHL_UART_FIFOS_REG_RXL_BIT	0
#define AUCOHL_UART_FIFOS_REG_RXL_MASK	0xf
#define AUCOHL_UART_FIFOS_REG_TXL_BIT	8
#define AUCOHL_UART_FIFOS_REG_TXL_MASK	0xf00

#define AUCOHL_UART_TXE_FLAG	0x1
#define AUCOHL_UART_RXF_FLAG	0x2
#define AUCOHL_UART_TXB_FLAG	0x4
#define AUCOHL_UART_RXA_FLAG	0x8
#define AUCOHL_UART_BRK_FLAG	0x10
#define AUCOHL_UART_MATCH_FLAG	0x20
#define AUCOHL_UART_FE_FLAG	0x40
#define AUCOHL_UART_PRE_FLAG	0x80
#define AUCOHL_UART_OR_FLAG	0x100
#define AUCOHL_UART_RTO_FLAG	0x200

typedef struct _AUCOHL_UART_TYPE_ {
	__R 	RXDATA;
	__W 	TXDATA;
	__W 	PR;
	__W 	CTRL;
	__W 	CFG;
	__W 	FIFOCTRL;
	__R 	FIFOS;
	__W 	MATCH;
	__R 	reserved[952];
	__W 	icr;
	__R 	ris;
	__RW	im;
	__R 	mis;
} AUCOHL_UART_TYPE;

#endif

