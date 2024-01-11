# AUCOHL_UART
A more complete UART

## Registers

|Name|Offset|Reset Value|Access Mode|Description|
|---|---|---|---|---|
|RXDATA|0000|0x00000000|r|RX Data register; the interface to the Receive FIFO.|
|TXDATA|0004|0x00000000|w|TX Data register; ; the interface to the Receive FIFO.|
|PR|000c|0x00000000|w|The Prescaler register; used to determine the baud rate. $Baud\ Rate = (Clock\ freq.)/((PR+1)\times16)$.|
|CTRL|0008|0x00000000|w|UART Control Register|
|CFG|0010|0x00003F08|w|UART Configuration Register|
|FIFOCTRL|0014|0x00000000|w|FIFO Control Register|
|FIFOS|0018|0x00000000|r|FIFO Status Register|
|MATCH|001c|0x00000000|w|Match Register|
|IM|0f00|0x00000000|w|Interrupt Mask Register; write 1/0 to enable/disable interrupts; check the interrupt flags table for more details|
|RIS|0f08|0x00000000|w|Raw Interrupt Status; reflects the current interrupts status;check the interrupt flags table for more details|
|MIS|0f04|0x00000000|w|Masked Interrupt Status; On a read, this register gives the current masked status value of the corresponding interrupt. A write has no effect; check the interrupt flags table for more details|
|IC|0f0c|0x00000000|w|Interrupt Clear Register; On a write of 1, the corresponding interrupt (both raw interrupt and masked interrupt, if enabled) is cleared; check the interrupt flags table for more details|

### RX Data register; the interface to the Receive FIFO. [Offset: 0x0, mode: r]

RX Data register; the interface to the Receive FIFO.

<img src="https://svg.wavedrom.com/{reg:[{name:'RXDATA', bits:9},{bits: 23}], config: {lanes: 2, hflip: true}} "/>

### TX Data register; ; the interface to the Receive FIFO. [Offset: 0x4, mode: w]

TX Data register; ; the interface to the Receive FIFO.

<img src="https://svg.wavedrom.com/{reg:[{name:'TXDATA', bits:9},{bits: 23}], config: {lanes: 2, hflip: true}} "/>

### The Prescaler register; used to determine the baud rate. $baud_rate = clock_freq/((PR+1)*16)$. [Offset: 0xc, mode: w]

The Prescaler register; used to determine the baud rate. $baud_rate = clock_freq/((PR+1)*16)$.

<img src="https://svg.wavedrom.com/{reg:[{name:'PR', bits:16},{bits: 16}], config: {lanes: 2, hflip: true}} "/>

### UART Control Register [Offset: 0x8, mode: w]

UART Control Register

|bit|field name|width|description|
|---|---|---|---|
|0|en|1|UART enable|
|1|txen|1|UART Transmitter enable|
|2|rxen|1|UART Receiver enable|
|3|lpen|1|Loopback (connect RX and TX pins together) enable|
|4|gfen|1|UART Glitch Filer on RX enable|

<img src="https://svg.wavedrom.com/{reg:[{name:'en', bits:1},{name:'txen', bits:1},{name:'rxen', bits:1},{name:'lpen', bits:1},{name:'gfen', bits:1},{bits: 27}], config: {lanes: 2, hflip: true}} "/>

### UART Configuration Register [Offset: 0x10, mode: w]

UART Configuration Register

|bit|field name|width|description|
|---|---|---|---|
|0|wlen|4|Data word length: 5-9 bits|
|4|stp2|1|Two Stop Bits Select|
|5|parity|3|Parity Type: 000: None, 001: odd, 010: even, 100: Sticky 0, 101: Sticky 1|
|8|timeout|6|Receiver Timeout measured in number of bits|

<img src="https://svg.wavedrom.com/{reg:[{name:'wlen', bits:4},{name:'stp2', bits:1},{name:'parity', bits:3},{name:'timeout', bits:6},{bits: 18}], config: {lanes: 2, hflip: true}} "/>

### FIFO Control Register [Offset: 0x14, mode: w]

FIFO Control Register

|bit|field name|width|description|
|---|---|---|---|
|0|TXLT|4|Transmit FIFO Level Threshold|
|8|RXLT|4|Receive FIFO Level Threshold|

<img src="https://svg.wavedrom.com/{reg:[{name:'TXLT', bits:4},{bits: 4},{name:'RXLT', bits:4},{bits: 20}], config: {lanes: 2, hflip: true}} "/>

### FIFO Status Register [Offset: 0x18, mode: r]

FIFO Status Register

|bit|field name|width|description|
|---|---|---|---|
|0|RXL|4|Receive FIFO Level|
|8|TXL|4|Transmit FIFO Level|

<img src="https://svg.wavedrom.com/{reg:[{name:'RXL', bits:4},{bits: 4},{name:'TXL', bits:4},{bits: 20}], config: {lanes: 2, hflip: true}} "/>

### Match Register [Offset: 0x1c, mode: w]

Match Register

<img src="https://svg.wavedrom.com/{reg:[{name:'MATCH', bits:9},{bits: 23}], config: {lanes: 2, hflip: true}} "/>

## Interrupt Flags


The following are the bit definitions for the interrupt registers: IM, RIS, MIS, and IC.

|Bit|Flag|Width|Description|
|---|---|---|---|
|0|TXE|1|Transmit FIFO is Empty.|
|1|RXF|1|Receive FIFO is Full.|
|2|TXB|1|Transmit FIFO level is Below Threshold.|
|3|RXA|1|Receive FIFO level is Above Threshold.|
|4|BRK|1|Line Break; 13 consecutive 0's have been detected on the line.|
|5|MATCH|1|Match; the receive data matches the MATCH register.|
|6|FE|1|Framing Error; the receiver does not see a "stop" bit at the expected "stop" bit time.|
|7|PRE|1|Parity Error; the receiver calculated parity does not match the received one.|
|8|OR|1|Overrun; data has been received but the RX FIFO is full.|
|9|RTO|1|Receiver Timeout; no data has been received for the time of a specified number of bits.|