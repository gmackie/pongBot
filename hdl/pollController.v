///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <Name>
//
// File: n64.v
// File history:
//      <Revision number>: <Date>: <Comments>
//      <Revision number>: <Date>: <Comments>
//      <Revision number>: <Date>: <Comments>
//
// Description: 
//
// <Description here>
//
// Targeted device: <Family::SmartFusion> <Die::A2F200M3F> <Package::484 FBGA>
// Author: <Name>
//
/////////////////////////////////////////////////////////////////////////////////////////////////// 

module pollController(
input PCLK,
input PRESERN, // system reset 
input PSEL, // peripheral select 
input PENABLE, // distinguishes access phase 
output wire PREADY, // peripheral ready signal 
output wire PSLVERR, // error signal 
input PWRITE, // distinguishes read and write cycles 
input [31:0] PADDR, // I/O address 
input wire [31:0] PWDATA, // data from processor to I/O device (32 bits) 
output reg [31:0] PRDATA, // data to processor from I/O device (32-bits) 
output reg pollCommand,
inout io_port
);

reg [15:0] count;
reg [15:0] sync_count;
reg [31:0] master;
reg read1, read2;
reg start;
reg [31:0] bitnum;
/*
reg [31:0] motorduty_cycle;
reg [31:0] yawduty_cycle;
reg [31:0] pitchduty_cycle;
assign PSLVERR = 0;

wire power_write_enable = (PENABLE && PWRITE && PSEL && PADDR[3:0] == 'h0);
wire yaw_write_enable = (PENABLE && PWRITE && PSEL && PADDR[3:0] == 'h4);
wire pitch_write_enable = (PENABLE && PWRITE && PSEL && PADDR[3:0] == 'h8);

reg [31:0] motorpwm_count; 
reg [31:0] yawpwm_count;
reg [31:0] pitchpwm_count;*/

assign io_port = (master >= 3400) ? pollCommand : 'hz;
assign PREADY = (bitnum == 32 ? 1 : 0);
assign PSLVERR = 0;

/* Block to send polling command */
always @(posedge PCLK)
begin
	if (master < 2800)
	begin 
		if (count < 300)
			pollCommand <= 0;
		else 
			pollCommand <= 'hz;
	end
	
	else 
	begin
		if (count < 100 && master < 3400)
			pollCommand <= 0;
		else 
			pollCommand <= 'hz;
	end

	if (master >= 3400)
	begin
		read1 <= io_port;
		read2 <= read1;

		if (read2 == 1 && read1 == 0 && start != 1)
		begin
			start <= 1;
			sync_count <= 0;
		end

		if (start)
		begin
			if (sync_count == 200)
			begin
				if (bitnum < 16)
				begin
					PRDATA[bitnum] <= io_port;
					bitnum <= bitnum + 1;
				end
				else if (bitnum < 24)
				begin
					PRDATA[39 - bitnum] <= io_port;
					bitnum <= bitnum + 1;
				end
				else if (bitnum < 32)
				begin
					PRDATA[55 - bitnum] <= io_port;
					bitnum <= bitnum + 1;
				end
			end
			if (sync_count == 380)
				start <= 0;
			else
				sync_count <= sync_count + 1;
		end

	end

	if (count >= 400)
		count <= 0;
	else
		count <= count + 1;
	
	if (master >= 100000)
	begin
		bitnum <= 0;
		master <= 0;
		count <= 0;
	end 
	else
		master <= master + 1;
end

endmodule

