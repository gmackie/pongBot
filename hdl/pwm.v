///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <Name>
//
// File: pwm.v
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

module PWM(
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
output reg power,
output reg pitch,
output reg yaw
);

reg [31:0] motorduty_cycle;
reg [31:0] motorpwm_count; 
reg [31:0] yawduty_cycle;
reg [31:0] yawpwm_count;
reg [31:0] pitchduty_cycle;
reg [31:0] pitchpwm_count;

wire power_write_enable = (PENABLE && PWRITE && PADDR[3:0] == 'h0);
wire yaw_write_enable = (PENABLE && PWRITE && PADDR[3:0] == 'h4);
wire pitch_write_enable = (PENABLE && PWRITE && PADDR[3:0] == 'h8);


assign PSLVERR = 0;
assign PREADY = 1;

always @(posedge PCLK)
begin
	if (motorpwm_count >= 1000000)
		motorpwm_count <= 0;
	else 
		motorpwm_count <= motorpwm_count + 1;

	if (power_write_enable)
		motorduty_cycle <= PWDATA;

	if (motorpwm_count >= motorduty_cycle)
		power <= 0;
	else
		power <= 1;
end

always @(posedge PCLK)
begin
	if (yawpwm_count >= 2000000)
		yawpwm_count <= 0;
	else
		yawpwm_count <= yawpwm_count + 1;

	if (yaw_write_enable)
		yawduty_cycle <= PWDATA;

	if (yawpwm_count >= yawduty_cycle)
		yaw <= 0;
	else
		yaw <= 1;
end

always @(posedge PCLK)
begin
	if (pitchpwm_count >= 2000000)
		pitchpwm_count <= 0;
	else
		pitchpwm_count <= pitchpwm_count + 1;

	if (pitch_write_enable)
		pitchduty_cycle <= PWDATA;

	if (pitchpwm_count >= pitchduty_cycle)
		pitch <= 0;
	else
		pitch <= 1;
end

endmodule
