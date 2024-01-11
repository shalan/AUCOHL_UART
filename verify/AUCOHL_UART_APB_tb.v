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

/* THIS FILE IS GENERATED, edit it to complete the testbench */

`timescale		1ns/1ps

`default_nettype	none

`define			APB_AW			16
`define			MS_TB_SIMTIME		2_000_000

`include		"tb_macros.vh"

module AUCOHL_UART_APB_tb;

	// Change the following parameters as desired
	parameter real CLOCK_PERIOD = 100.0;
	parameter real RESET_DURATION = 999.0;

	// DON NOT Change the following parameters
	localparam [`APB_AW-1:0]
			RXDATA_REG_OFFSET 	=   `APB_AW'h0000,
			TXDATA_REG_OFFSET 	=   `APB_AW'h0004,
			PR_REG_OFFSET 		= 	`APB_AW'h000c,
			CTRL_REG_OFFSET 	=   `APB_AW'h0008,
			CFG_REG_OFFSET 		=   `APB_AW'h0010,
			FIFOCTRL_REG_OFFSET =   `APB_AW'h0014,
			FIFOS_REG_OFFSET 	=   `APB_AW'h0018,
			MATCH_REG_OFFSET 	=   `APB_AW'h001c,
			IM_REG_OFFSET 		=   `APB_AW'h0f00,
			IC_REG_OFFSET 		=   `APB_AW'h0f0c,
			RIS_REG_OFFSET 		=   `APB_AW'h0f08,
			MIS_REG_OFFSET 		= 	`APB_AW'h0f04;

	`TB_APB_SIG

	wire	[0:0]	rx;
	wire	[0:0]	tx;

	reg				vip_tx;
	wire			vip_rx;

	assign 			rx 		= vip_tx;
	assign 			vip_rx 	= tx;

	`TB_CLK(PCLK, CLOCK_PERIOD)
	`TB_ESRST(PRESETn, 1'b0, PCLK, RESET_DURATION)
	`TB_DUMP("APB_AUCOHL_UART_tb.vcd", AUCOHL_UART_APB_tb, 0)
	`TB_FINISH(`MS_TB_SIMTIME)

	AUCOHL_UART_APB DUV (
		`TB_APB_SLAVE_CONN,
		.rx(rx),
		.tx(tx)
	);

	`include "apb_tasks.vh"

	`include "serial_tasks.vh"
	

	event	e_test1_start, e_test1_done;
	event	e_test2_start, e_test2_done;
	`TB_TEST_EVENT(test3) 
	
	localparam real BIT_TIME_115200 = 8680.55,
					BIT_TIME_57600 = 17361.11;
	initial begin
		#999 -> e_assert_reset;
		@(e_reset_done);

		// Do some initializations
		// Set the baud rate to 115,200 bps
		// 0.1152 = 10/((PR+1)*8) ==> PR = 9.85 (~10)
		// Actual baud = 113.636 baud/s
		// bit time = 8.6805 us (actual: 8.8 us)
		APB_W_WRITE(PR_REG_OFFSET, 16'd10);
		// Configure the line for 8N1
		APB_W_WRITE(CFG_REG_OFFSET, 32'b111111_000_0_1000);
		// Perform Test 1
		#1000 -> e_test1_start;
		@(e_test1_done);

		#1000 -> e_test2_start;
		@(e_test2_done);

		#1000 -> e_test3_start;
		@(e_test3_done);

		// Finish the simulation
		$display("All tests have passed");
		#10_000 $finish();
	end

	// Serial Send Thread
	event e_send_serial_data;
	initial begin
		forever begin
			@(e_send_serial_data) send_serial_8N1(BIT_TIME_115200, 8'hA5);	
		end
	end

	reg [31:0] prdata;
	reg t1f;
	// Test 1 -- Receive an 8N1 frame @ 115000 baud rate
	`TB_TEST_BEGIN(test1)
		t1f = 0;
		// Test 1 code goes here
		// Enable the receiver and the UART
		APB_W_WRITE(CTRL_REG_OFFSET, 32'b0_0_1_0_1);
		//send_serial_8N1(8696, 8'hA5);
		->e_send_serial_data;
		forever begin
			if(t1f == 0) begin
				APB_W_READ(RIS_REG_OFFSET, prdata);
				if((prdata & 32'h8) != 0) begin
					#1_000;
					APB_W_READ(RXDATA_REG_OFFSET, prdata);
					#1_1000;
					if(prdata == 'hA5) begin
						->e_test1_done;
						//break;
						t1f = 1;
					end
					else begin
						$display("Received Wrong data %x vs. %x", prdata, 'hA5);
						$finish;
					end
				end
			end else
				#1000_000_000;
		end 
	`TB_TEST_END(test1)	
	
	// Test 2 -- Send a frame @ 57600
	`TB_TEST_BEGIN(test2)
		// Disable the UART fully
		APB_W_WRITE(CTRL_REG_OFFSET, 32'b0);
		// Configure the prescaler for 57600
		// Prescaler has to be 20.7 
		// will go for 21 which gives 56818.18 baud/s
		APB_W_WRITE(PR_REG_OFFSET, 16'd21);
		// Configure the line for 812
		APB_W_WRITE(CFG_REG_OFFSET, 32'b111111_101_1_1000);
		// Enable the transmission
		APB_W_WRITE(CTRL_REG_OFFSET, 32'b0_0_0_1_1);
		// Send two different frames
		APB_W_WRITE(TXDATA_REG_OFFSET, 'hC3);
		APB_W_WRITE(TXDATA_REG_OFFSET, 'h91);
		// Wait for the time of two frames = 2 x 12 x 17.6 = 416.666 usec
		#416_666;
		// This test is a manual one. Check the waveform!
	`TB_TEST_END(test2)

	// Test 3 -- Enable Loopback mode
	`TB_TEST_BEGIN(test3)
		// Disable the UART fully
		APB_W_WRITE(CTRL_REG_OFFSET, 32'b0);
		// Configure the prescaler for 57600
		// Prescaler has to be 20.7 
		// will go for 21 which gives 56818.18 baud/s
		APB_W_WRITE(PR_REG_OFFSET, 16'd21);
		// Configure the line for 812
		APB_W_WRITE(CFG_REG_OFFSET, 32'b111111_101_1_1000);
		// Enable TX, RX and LP
		APB_W_WRITE(CTRL_REG_OFFSET, 32'b0_1_1_1_1);
		// Send two different frames
		APB_W_WRITE(TXDATA_REG_OFFSET, 'hC3);
		APB_W_WRITE(TXDATA_REG_OFFSET, 'h91);
		// Wait for the time of two frames = 2 x 12 x 17.6 = 416.666 usec
		#416_666;
		// Read the two frames
		APB_W_READ(RXDATA_REG_OFFSET, prdata);
		#1000;
		if(prdata != 'hC3) begin
			$display("Test 3 Failed; received %x, expected %x", prdata, 8'hC3);
			$finish();
		end
		APB_W_READ(RXDATA_REG_OFFSET, prdata);
		#1000;
		if(prdata != 'h91) begin
			$display("Test 3 Failed; received %x, expected %x", prdata, 8'h91);
			$finish();
		end
	`TB_TEST_END(test3)
	
endmodule
