#include "drivers/mss_gpio/mss_gpio.h"
#include "drivers/mss_uart/mss_uart.h"
#include <stdio.h>
#include <time.h>
#include "lcd.h"

void joystick(int8_t inValue, uint8_t *outValue){
	if (inValue >= 0){
		if (inValue < 5);
		else if (inValue < 20)
			*outValue += 1;
		else if (inValue < 40)
			*outValue += 2;
		else if (inValue < 60)
			*outValue += 3;
		else if (inValue < 80)
			*outValue += 4;
		else if (inValue < 100)
			*outValue += 5;
		else if (inValue < 110)
			*outValue += 6;
		else
			*outValue += 7;
	}
	else{
		if (inValue > -5);
		else if (inValue > -20)
			*outValue -= 1;
		else if (inValue > -40)
			*outValue -= 2;
		else if (inValue > -60)
			*outValue -= 3;
		else if (inValue > -80)
			*outValue -= 4;
		else if (inValue > -100)
			*outValue -= 5;
		else if (inValue > -110)
			*outValue -= 6;
		else
			*outValue -= 7;
	}
}
/*
int main()
{
	LCDinit();

	volatile uint8_t i = 0;
	volatile uint8_t prev,curr;
	prev = curr = 48;
	volatile int barNum = 0;

	while( 1 )
	{
		int * n64 = (int *) 0x40050004;
		int test = *n64;
		volatile int8_t A = test & 0x01;
		volatile int8_t B = test & 0x02;
		volatile int8_t X_coord = test>>16 & 0xFF;
		volatile int8_t Y_coord = test>>24 & 0xFF;

		if (barNum < 2){
		joystick(Y_coord, &curr);
		if (curr < 49)
			curr = 49;
		else if (curr > 110)
			curr = 110;
		fillBar(prev, curr, barNum);
		prev = curr;
		}
		else{
				joystick(X_coord, &curr);
				if (curr < 7)
					curr = 7;
				else if (curr > 70)
					curr = 70;
				fillBar(prev, curr, barNum);
				prev = curr;
		}

		volatile int i = 0;
		for (i = 0; i < 1000000; i++);
		if (A == 1){
			barNum = ++barNum % 3;
			if (barNum < 2){
				prev=curr=48;
			}
			else
				prev=curr=7;
		}
/*		begin = end++;
	//	if (Y_coord < 111 && Y_coord > 50)
	//	volatile int i;
		volatile int * pwm = (int *) 0x40050000;
	//	*pwm = 500000 + 35000;// * Y_coord;
		volatile int * yawpwm = (int *) 0x40050004;
	//	*yawpwm = 240000;
		volatile int * pitchpwm = (int *) 0x40050008;
	//	*pitchpwm = 160000;
	/*
		if (b_status == 1)
			set = 1;
		if (b_status == 2)
			set = 0;
	*/
	//	*yawpwm = 160000;
	//	*pitchpwm = 60000;
//
//	}

//	return 0;

//}

volatile int * pwm_motor = (int *) 0x40050000;
volatile int * pwm_yaw = (int *) 0x40050004;
volatile int * pwm_pitch = (int *) 0x40050008;

int power=0, yaw=0, pitch=0;

typedef struct buttonstruct {
	int A;
	int B;
	int8_t X_coord;
	int8_t Y_coord;
} buttonstruct;

void get_buttons(buttonstruct * buttons) {
	int * n64 = (int *) 0x40050004;
	buttons->A = *n64 & 0x01;
	buttons->B = *n64 & 0x02;
	buttons->X_coord = *n64>>16 & 0xFF;
	buttons->Y_coord = *n64>>24 & 0xFF;
}

int get_state(int cur_state, buttonstruct * buttons) {

	int next = cur_state;

	if (buttons->A) {
		while (buttons->A) {
			get_buttons(buttons);
		}
		next = ++cur_state;
	}
	// go back to MOTOR state //
	if (buttons->B) {
		while (buttons->B) {
			get_buttons(buttons);
		}
		next = --cur_state;
	}

	return next;
}


int main() {


	int option = 0; //start menu option. 0 for choose, 1 for slider, 2 for stats
	int cur_cup = -1; //current cup scored on that shot
	int scored[10] = { 0 }; //array to keep track of the scored cups
	volatile int i = 0;

	// state enum //
	enum states { START, YAW, PITCH, MOTOR, FIRE, CHECK, UPDATE, STATS };
	enum bars { PITCHBAR, POWERBAR, YAWBAR };
	buttonstruct buttons;
	buttons.A = 0;
	buttons.B = 0;
	buttons.X_coord = 0;
	buttons.Y_coord = 0;

	LCDstruct LCD;

	int cur_state = START, next_state;

	while (1) {

		switch (cur_state) {

			// initial starting screen //
			case START: {
				//MENUinit();
				LCDinit();
				initBars(&LCD);
				while (1) {
					get_buttons(&buttons);
					// if an option is chosen //
					if (buttons.A) {
						while (buttons.A) {
							get_buttons(&buttons);
						}
						// target choose mode //
						if ( (option == 0) || (option == 1 ) ) {
							next_state = YAW;
							break;
						}
						// stats tracker //
						else if (option == 2) {
							next_state = STATS;
							break;
						}
					}
					// else if still choosing option //
					if (buttons.Y_coord > 5) {
						if (option < 2) {
							option++ ;
						}
						// FUNCTION TO DISPLAY STARTING MENU TO THE BOARD //
					}
					else if (buttons.Y_coord < -5) {
						if (option > 0) {
							option--;
						}
						// FUNCTION TO DISPLAY STARTING MENU TO THE BOARD //
					}
				}
				break;
			}

			case YAW: {
				//LCDinit();
				get_buttons(&buttons);
				next_state = get_state(cur_state, &buttons);
				joystick(buttons.X_coord, &LCD.cur_yawBar);
				if (LCD.cur_yawBar < 7)
					LCD.cur_yawBar = 7;
				if (LCD.cur_yawBar > 70)
					LCD.cur_yawBar = 70;
				fillBar(LCD.prev_yawBar, LCD.cur_yawBar, YAWBAR);
				LCD.prev_yawBar = LCD.cur_yawBar;
/*				// else adjust yaw level //
				if ( !( (buttons.X_coord > -5) && (buttons.X_coord < 5) )) {
					int yaw = (500000+yaw) + (35000*buttons.X_coord);

					// make sure it doesnt go below the lowest pwm value //
					if (yaw < 500000) {
						yaw = 500000;
					}
					// make sure it doesnt go higher than 100 percent pwm value //
					else if(yaw > 1000000) {
						yaw = 1000000;
					}
				} */
				for (i = 0; i < 500000; i++);
				break;
			}

			// CANNON PITCH //
			case PITCH: {
				get_buttons(&buttons);
				next_state = get_state(cur_state, &buttons);
				joystick(buttons.Y_coord, &LCD.cur_pitchBar);
				if (LCD.cur_pitchBar < 49)
					LCD.cur_pitchBar = 49;
				if (LCD.cur_pitchBar > 110)
					LCD.cur_pitchBar = 110;
				fillBar(LCD.prev_pitchBar, LCD.cur_pitchBar, PITCHBAR);
				LCD.prev_pitchBar = LCD.cur_pitchBar;
		/*		get_buttons(&buttons);
				next_state = get_state(cur_state, &buttons);
				joystick(buttons.Y_coord, &LCD.cur_pitchBar);
				fillBar(LCD.prev_pitchBar, LCD.cur_pitchBar, PITCHBAR);

				// else adjust power level //
*/
				for (i = 0; i < 500000; i++);
				break;
			}
						// MOTOR SPEED //
			case MOTOR: {
				get_buttons(&buttons);
				next_state = get_state(cur_state, &buttons);
				joystick(buttons.Y_coord, &LCD.cur_powerBar);
				if (LCD.cur_powerBar < 49)
					LCD.cur_powerBar = 49;
				if (LCD.cur_powerBar > 110)
					LCD.cur_powerBar = 110;
				fillBar(LCD.prev_powerBar, LCD.cur_powerBar, POWERBAR);
				LCD.prev_powerBar = LCD.cur_powerBar;
/*				// else adjust power level //
				if ( !( (buttons.Y_coord > -5) && (buttons.Y_coord < 5) )) {
					power = (500000+power) + (35000*buttons.Y_coord);
					// make sure it doesnt go below the lowest pwm value //
					if (power < 500000) {
						power = 500000;
					}
					// make sure it doesnt go higher than 100 percent pwm value //
					else if(power > 1000000) {
						power = 1000000;
					}
				} */

				for (i = 0; i < 500000; i++);
				break;
			}

						// FIRE THE CANNON //
			case FIRE: {
				*pwm_pitch = 2000000;
				*pwm_yaw = 1000000;
				//sleep(5000); //wait for 5 seconds before firing

				// TRIGGER ACTUATOR //

				//sleep(5000); //wait 5 seconds for the ball to settle

				next_state = CHECK;
				break;
			}
/*
			// user uses a slider to choose the values of cannon speed, yaw, and pitch, and fire the cannon
			case TARGET_SLIDER: {




			}

			// determine which cup the ball scored (if any) //
			case CHECK: {

				// WHATEVER NEEDS TO GO HERE //

				// make sure to set cur_cup to the cup //
			}

			// update the current score and the players' stats //
			case UPDATE: {
				/// update the player score ///
				// if no cup was scored //
				if (cur_cup == -1) {
					if (option == 0) {	//choose
						next_state = TARGET_CHOOSE;
					}
					else if (option == 1) { //slier
						next_state = TARGET_SLIDER;
					}
					else { //error state, shouldn't ever get here //
						printf("error leaving UPDATE state");
						return 1;
					}
				}
				// else if a cup was scored //
				else {
					// error, cur_cup should not fall outside these values //
					if ( (cur_cup < -1 ) || (cur_cup > 9) ) {
						printf("ERROR: cur_cup has an invalid value");
						return 1;
					}
					// if cup hasn't been scored on yet //
					if (scored[cur_cup] == 0) {
						scored[cur_cup] = 1;
						// FILL IN CUP ON THE LCD DISPLAY //
						// maybe display that user scored //
					}
				}

				///update the player stats ///


				// reset the cur_cup to -1 (hasn't been scored)
				cur_cup = -1;
			}

			case STATS: {

				// Do whataever stats stuff needs to be done here //

			}
*/

		}

		cur_state = next_state;
	}

	return 0;
}






