

#include "Drv_Devices.h"
#include "UART.h"
#include "ADS131E08.h"
#include "GPIO.h"
#include "board_api.h"
#include "chip.h"
#include <stdlib.h>



/**
 * @brief Flag to indicate if the ADS1299 is acquiring data or not
 */
//bool is_running = FALSE;

/**
 * @brief Flag to indicate if channel settings commands are being received
 */
bool getChannelSettings = FALSE;

/**
 * @brief Mode of use: 8 or 16 channels
 */
//uint8_t  outputType = OUTPUT_8_CHAN; //default to 8 channels

/**
 * @brief Counter to have control of the received commands
 */
uint8_t plusCounter = 0;

/**
 * @brief Auxiliary byte
 */
uint8_t testChar = 0;

/**
 * @brief Keep track of what channel we are loading settings for
 */
uint8_t currentChannelToSet = 0;

/**
 * @brief Counter used to retrieve channel settings from serial port
 */
uint8_t channelSettingsCounter = 0;

/**
 * @brief Flag to indicate the use of filters
 */
bool useFilters = FALSE;

/**
 * @brief Counter used to retrieve lead off settings from serial port
 */
uint8_t leadOffSettingsCounter = 0;

/**
 * @brief Flag to indicate if lead off settings commands are being received
 */
bool getLeadOffSettings = FALSE;

/**
 * @brief Flag to indicate if the board is Master (HIGH state) or Slave (LOW state)
 */
bool isMaster = FALSE;

/**
 * @brief Function for receiving new commands
 
void Drv_Devices_eventSerial()
{
	uint8_t inChar = 0;

	while(UART_available())
	{
		inChar = UART_ReadByte();

		if(getChannelSettings) // if we just got an 'x' expect channel setting parameters
		{
			Drv_Devices_loadChannelSettings(inChar); //go get channel settings parameters
		}
		else if(getLeadOffSettings) // if we just got a 'z' expect lead-off setting parameters
		{
			Drv_Devices_loadLeadOffSettings(inChar); //go get lead-off settings parameters
		}
		else
		{
			Drv_Devices_getCommands(inChar); // decode the command
		}
	}

}
*/
/**
 * @brief Function for interpreting commands
 * @param token Command to be decoded and interpreted

void Drv_Devices_getCommands(uint8_t token)
{
	uint8_t echo = 0;
	switch (token)
	{
	//Turn channels on/off commands
		case '1':
				echo = '1';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(1, DEACTIVATE);
				break;
		case '2':
			    echo = '2';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(2, DEACTIVATE);
				break;
		case '3':
			    echo = '3';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(3, DEACTIVATE);
				break;
		case '4':
			    echo = '4';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(4, DEACTIVATE);
				break;
		case '5':
			    echo = '5';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(5, DEACTIVATE);
				break;
		case '6':
			    echo = '6';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(6, DEACTIVATE);
				break;
		case '7':
			    echo = '7';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(7, DEACTIVATE);
				break;
		case '8':
			    echo = '8';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(8, DEACTIVATE);
				break;
		case '!':
			    echo = '!';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(1, ACTIVATE);				
				break;
		case '@':
				echo = '@';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(2, ACTIVATE);
				break;
		case '#':
			    echo = '#';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(3, ACTIVATE);
				break;
		case '$':
			    echo = '$';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(4, ACTIVATE);
				break;
		case '%':
			    echo = '%';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(5, ACTIVATE);
				break;
		case '^':
			    echo = '^';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(6, ACTIVATE);
				break;
		case '&':
			    echo = '&';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(7, ACTIVATE);
				break;
		case '*':
			    echo = '*';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(8, ACTIVATE);
				break;
		case 'q':
			    echo = 'q';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(9, DEACTIVATE);
				break;
		case 'w':
			    echo = 'w';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(10, DEACTIVATE);
				break;
		case 'e':
			    echo = 'e';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(11, DEACTIVATE);
				break;
		case 'r':
			    echo = 'r';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(12, DEACTIVATE);
				break;
		case 't':
			    echo = 't';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(13, DEACTIVATE);
				break;
		case 'y':
				echo = 'y';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(14, DEACTIVATE);
				break;
		case 'u':
			    echo = 'u';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(15, DEACTIVATE);
				break;
		case 'i':
			    echo = 'i';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(16, DEACTIVATE);
				break;
		case 'Q':
			    echo = 'Q';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(9, ACTIVATE);
				break;
		case 'W':
			    echo = 'W';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(10, ACTIVATE);
				break;
		case 'E':
			    echo = 'E';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(11, ACTIVATE);
				break;
		case 'R':
			    echo = 'R';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(12, ACTIVATE);
				break;
		case 'T':
			    echo = 'T';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(13, ACTIVATE);
				break;
		case 'Y':
			    echo = 'Y';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(14, ACTIVATE);
				break;
		case 'U':
			    echo = 'U';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(15, ACTIVATE);
				break;
		case 'I':
			    echo = 'I';
				UART_Send(&echo,1); 
				
				Drv_Devices_changeChannelState_maintainRunningState(16, ACTIVATE);
				break;

		// Test signal control commands
		case '0':
			    echo = '0';
				UART_Send(&echo,1); 
				
				Drv_Devices_activateAllChannelsToTestCondition(ADSINPUT_SHORTED, ADSTESTSIG_NOCHANGE, ADSTESTSIG_NOCHANGE);
				break;
		case '-':
			    echo = '-';
				UART_Send(&echo,1);

				Drv_Devices_activateAllChannelsToTestCondition(ADSINPUT_TESTSIG, ADSTESTSIG_AMP_1X, ADSTESTSIG_PULSE_SLOW);		
				break;
		case '=':
			    echo = '=';
				UART_Send(&echo,1); 
				
				Drv_Devices_activateAllChannelsToTestCondition(ADSINPUT_TESTSIG, ADSTESTSIG_AMP_1X, ADSTESTSIG_PULSE_FAST);
				break;
		case 'p':
			    echo = 'p';
				UART_Send(&echo,1); 
				
				Drv_Devices_activateAllChannelsToTestCondition(ADSINPUT_TESTSIG, ADSTESTSIG_AMP_2X, ADSTESTSIG_DCSIG);
				break;
		case '[':
			    echo = '[';
				UART_Send(&echo,1); 
				
				Drv_Devices_activateAllChannelsToTestCondition(ADSINPUT_TESTSIG, ADSTESTSIG_AMP_2X, ADSTESTSIG_PULSE_SLOW);
				break;
		case ']':
			    echo = ']';
				UART_Send(&echo,1); 
				
				Drv_Devices_activateAllChannelsToTestCondition(ADSINPUT_TESTSIG, ADSTESTSIG_AMP_2X, ADSTESTSIG_PULSE_FAST);
				break;

		// Channel settings commands
		case 'x':
			    echo = 'x';
				UART_Send(&echo,1);

				if(!is_running)
				{
					UART_Send((uint8_t*)("Ready to accept new channel settings\r\n"),38);
				}
				channelSettingsCounter = 0;
			    getChannelSettings = TRUE;

				 break;


		case 'X':
			    echo = 'X';
				UART_Send(&echo,1); 
				
				if(!is_running)
				{
					UART_Send((uint8_t*)("Updating channel settings\r\n"),27);
				}
				Drv_Devices_writeChannelSettings_maintainRunningState(currentChannelToSet);
				break;
		case 'd':
			    echo = 'd';
				UART_Send(&echo,1); 
				
				if(!is_running)
				{
					UART_Send((uint8_t*)("Updating channel settings to Default\r\n"),38);
				}
				Drv_Devices_setChannelsToDefaultSettings();
				break;
		case 'D':
			    echo = 'D';
				UART_Send(&echo,1);

				Drv_Devices_printDefaultChannelSettings();
				break;


		// Change sampling frequency
		case 'A':
				echo = 'A';
				UART_Send(&echo,1);
				if(!is_running)
				{
					UART_Send((uint8_t*)("Updating channels sampling rate to 2kHz\r\n"),39);
				}
				Drv_Devices_updateFrequency(SAMPLE_RATE_2kHZ);
				break;
		case 'S':
				echo = 'S';
				UART_Send(&echo,1);
				if(!is_running)
				{
					UART_Send((uint8_t*)("Updating channels sampling rate to 1kHz\r\n"),39);
				}
				Drv_Devices_updateFrequency(SAMPLE_RATE_1kHZ);
				break;
		case 'F':
				echo = 'F';
				UART_Send(&echo,1);
				if(!is_running)
				{
					UART_Send((uint8_t*)("Updating channels sampling rate to 500Hz\r\n"),42);
				}
				Drv_Devices_updateFrequency(SAMPLE_RATE_500HZ);
				break;
		case 'G':
				echo = 'G';
				UART_Send(&echo,1);
				if(!is_running)
				{
					UART_Send((uint8_t*)("Updating channels sampling rate to 250Hz\r\n"),42);
				}
				Drv_Devices_updateFrequency(SAMPLE_RATE_250HZ);
				break;

		// Lead-off impedance detection commands
		case 'z':
			    echo = 'z';
				UART_Send(&echo,1); 

				if(!is_running)
				{
					UART_Send((uint8_t*)("Ready to accept new impedance detect settings\r\n"),47);
				}
				leadOffSettingsCounter = 0; //reset counter
				getLeadOffSettings = TRUE;
				break;
		case 'Z':
			    echo = 'Z';
				UART_Send(&echo,1); 


				if(!is_running)
				{
					UART_Send((uint8_t*)("Updating impedance detect settings\r\n"),36);
				}
				Drv_Devices_changeChannelLeadOffDetect_maintainRunningState(currentChannelToSet);
				break;

		// Slave board commands
		case 'c':	// use 8 channel mode
			    echo = 'c';
				UART_Send(&echo,1); 

				if(Drv_ADS1299_getSlavePresent())
				{
					Drv_ADS1299_removeSlave();
				}
				outputType = OUTPUT_8_CHAN;
				break;
		case 'C':	// use 16 channel mode
			    echo = 'C';
				UART_Send(&echo,1); 

				if(!(Drv_ADS1299_getSlavePresent()))
				{
					Drv_ADS1299_attachSlave();
				}

				if(Drv_ADS1299_getSlavePresent())
				{
					outputType = OUTPUT_16_CHAN;
				}
				else
				{
					outputType = OUTPUT_8_CHAN;
				}
				break;

		//Stream data and filter commands
		case 'b':
			    echo = 'b';
				UART_Send(&echo,1); 
				
				Drv_Devices_startRunning(outputType); 
				break;
		case 's':
			    echo = 's';
				UART_Send(&echo,1); 
				
				Drv_Devices_stopRunning();
				break;
		case 'f':
			    echo = 'f';
				UART_Send(&echo,1); 
				
				useFilters = TRUE;
				break;
		case 'g':
			    echo = 'g';
				UART_Send(&echo,1); 
				
				useFilters = FALSE;
				break;

		// Initialize and verify
		case 'v':
			    echo = 'v';
				UART_Send(&echo,1); 
				
				Drv_Devices_startFromScratch(); //initialize ADS and read device IDs
				break;

		// Query the ADS registers
		case '?':
			    echo = '?';
				UART_Send(&echo,1); 

				Drv_Devices_printRegisters();
				break;

		// Query the ADS registers
		case 'M':
			    echo = 'M';
				//UART_Send(&echo,1);
				Drv_Devices_printMenu();
				break;

		default:
				break;

	}
} //end Drv_Devices_getComands()
 */

/**
 * @brief Stop data acquisition
 * @return HIGH if the device is running, LOW if not
 
bool Drv_Devices_stopRunning()
{
	if(is_running)
	{
		Drv_ADS1299_stopStreaming(); //stop data acquisition
		is_running = FALSE;
	}

	return is_running;
}
*/
/**
 * @brief Start data acquisition
 * @param OUT_TYPE Define if quiet or how many channels are active:  OUTPUT_NOTHING, OUTPUT_8_CHAN, OUTPUT_16_CHAN
 * @return HIGH if the device is running, LOW if not
 
bool Drv_Devices_startRunning(int OUT_TYPE)
{
	if(!is_running)
	{
		outputType = OUT_TYPE;
		Drv_ADS1299_startStreaming(); //start data acquisition
		is_running = TRUE;
	}

	return is_running;
}
*/
/**
 * @brief Start the system from scratch, send initial message and get the board ready to get commands
 */
 /*
void Drv_Devices_startFromScratch()
{
	if(!is_running)
	{
		//Iniciar UART
		UART_Setup();
		//Función que inicializa el ADS1299
      ADS131E08_signalDown();
		//ADS131E08_initialize();
		//delayMs(0, 50);
		//Drv_Devices_boardReset();
		//Drv_Devices_sendEOT();

	}
}
*/
/**
* @description: This is a function that can be called multiple times, this is
*                 what we refer to as a `soft reset`. You will hear/see this
*                 many times.
* @author: AJ Keller (@pushtheworldllc)

void Drv_Devices_boardReset(void) {

	char vstring [2];
    //Drv_ADS1299_initialize(); // initalizes accelerometer and on-board ADS and on-daisy ADS if present
	UART_Send((uint8_t*)("Poncho de Biopotenciales V1.1 8 canales\r\n"),41);
    UART_Send((uint8_t*)("ID del ADS1299: 0x"),18);
    itoa(Drv_ADS1299_getDeviceID(BOARD_ADS),vstring,16); // convert to hexadecimal
    UART_Send(vstring,2);
    UART_Send((uint8_t*)("\r\n"),2);

    if(slavePresent){  // library will set this in initialize() if daisy present and functional
    	 UART_Send((uint8_t*)("ADS1299 en placa esclavo ID: 0x"),31);
    	 itoa(Drv_ADS1299_getDeviceID(SLAVE_ADS),vstring,16); // convert to hexadecimal
    	 UART_Send(vstring,2);
    	 UART_Send((uint8_t*)("\r\n"),2);
    }

    UART_Send((uint8_t*)("Firmware: v1.0.0"),17);
    Drv_Devices_printMenu();

    Drv_Devices_sendEOT();
}
*/

/**
 * @brief Send characters to shake hands with the controlling program
 
void Drv_Devices_sendEOT()
{
	UART_Send((uint8_t*)("$$$\r\n"),5); //send "$$$"
}
*/
/**
 * @brief Call init and start functions of the different peripherals of the uC

void Drv_Devices_startDevices()
{

	// Init board function from "board_api.h"
	//Board_Init();

	// Init GPIO pins
	GPIO_init();
	//GPIO_setPinDir(MS_PORT, MS_PIN, FALSE); //set M/S pin as input
	GPIO_setPinDir(LED_R_PORT, LED_R_PIN, TRUE); //set pin as output
	GPIO_setPinDir(LED_V_PORT, LED_V_PIN, TRUE); //set pin as output
	GPIO_setPinState(LED_V_PORT, LED_V_PIN, FALSE); //set LOW
	GPIO_setPinState(LED_R_PORT, LED_R_PIN, FALSE); //set LOW



	//TODO: COMENTAR: LED azul del RGB de la Base Board


}
 */
/**
 * @brief Retrieve parameters and execute channel settings
 * @param parameter Setting parameter received as command: CHAN_NUM, POWER_DOWN, GAIN_SET, INPUT_TYPE_SET, BIAS_SET, SRB2_SET, SRB1_SET
 
void Drv_Devices_loadChannelSettings(uint8_t parameter)
{
	if(channelSettingsCounter == 0)// if it's the first byte in this channel's array, this byte is the channel number to set
	{
		currentChannelToSet = Drv_Devices_getChannelNumber(parameter); // we just got the channel to load settings into (shift number down for array usage)
		channelSettingsCounter++;

		if(!is_running)
		{
			uint8_t number = currentChannelToSet + 1 + '0';
			UART_Send((uint8_t*)("Load settings of channel: "),26);
			UART_Send(&number,1);
			UART_Send((uint8_t*)("\r\n"),2);
		}

	}
	else
	{

		//  setting bytes are in order: POWER_DOWN, GAIN_SET, INPUT_TYPE_SET, BIAS_SET, SRB2_SET, SRB1_SET

		parameter = parameter - '0'; //convert char to number

		if(channelSettingsCounter-1 == GAIN_SET)
		{
			parameter <<= 4;
		}

		// Fill array with current channel settings defined in the Drv_ADS1299 library
		channelSettings[currentChannelToSet][channelSettingsCounter-1] = parameter;

		channelSettingsCounter++;

		if(channelSettingsCounter == 7) // 1 currentChannelToSet, plus 6 channelSetting parameters
		{
			getChannelSettings = FALSE;
		}
	}
}
*/
/**
 * @brief Convert channel number from character to number
 * @param n Character defining channel: "1-8", "Q-I"
 * @return Channel number
 
uint8_t Drv_Devices_getChannelNumber(uint8_t n)
{
	if(n > '0' && n < '9')
	{
		n = n - '1';
	}

	switch(n)
	{
		case 'Q':
			n = 0x08;
			break;
		case 'W':
			n = 0x09;
			break;
		case 'E':
			n = 0x0A;
			break;
		case 'R':
			n = 0x0B;
			break;
		case 'T':
			n = 0x0C;
			break;
		case 'Y':
			n = 0x0D;
			break;
		case 'U':
			n = 0x0E;
			break;
		case 'I':
			n = 0x0F;
			break;
		default:
			break;
	}

	return n;
}
*/
/**
 * @brief Stop acquisition, set the channels and re-start acquisition
 * @param channel Channel number
 
void Drv_Devices_writeChannelSettings_maintainRunningState(uint8_t channel)
{
	bool is_running_when_called = is_running;
	uint8_t cur_outputType = outputType;

	Drv_Devices_stopRunning(); //must stop running to change channel settings

	Drv_ADS1299_writeOneChannelSettings(channel+1); //change the channel settings on ADS

	if(is_running_when_called)
	{
		Drv_Devices_startRunning(cur_outputType); //restart, if it was running before
	}
}
*/

/**
 * @brief Update sampling frequency
 * @param freq Sampling frequency
 
void Drv_Devices_updateFrequency(uint8_t freq)
{
	bool is_running_when_called = is_running;
	uint8_t cur_outputType = outputType;

	Drv_Devices_stopRunning(); //must stop running to change channel settings

	if(!slavePresent)
	{
		Drv_ADS1299_WREG(CONFIG1, 0x90 | freq, BOARD_ADS); //Turn off clk output if no slave present, set the data rate
	}
	else
	{
		if(freq==SAMPLE_RATE_2kHZ)
		{
			Drv_ADS1299_WREG(CONFIG1, 0xB0 | SAMPLE_RATE_1kHZ, BOARD_ADS); //tell on-board ADS to output its clk, set the data rate
			Drv_ADS1299_WREG(CONFIG1, 0x90 | SAMPLE_RATE_1kHZ, SLAVE_ADS); //Turn off clk output in slave, set the data rate
		}
		else
		{
			Drv_ADS1299_WREG(CONFIG1, 0xB0 | freq, BOARD_ADS); //tell on-board ADS to output its clk, set the data rate
			Drv_ADS1299_WREG(CONFIG1, 0x90 | freq, SLAVE_ADS); //Turn off clk output in slave, set the data rate
		}
	}

	if(is_running_when_called)
	{
		Drv_Devices_startRunning(cur_outputType); //restart, if it was running before
	}
}
*/

/**
 * @brief Set all channels to the default settings
 
void Drv_Devices_setChannelsToDefaultSettings()
{
	bool is_running_when_called = is_running;
	uint8_t cur_outputType = outputType;

	Drv_Devices_stopRunning(); //must stop running to change channel settings

	Drv_ADS1299_setChannelsToDefault();

	if(is_running_when_called)
	{
		Drv_Devices_startRunning(cur_outputType); //restart, if was running before
	}
}
*/
/**
 * @brief Activate or De-activate channel maintaining running state
 * @param channel Channel number
 * @param start Channel desired state: TRUE (1) to activate channel, FALSE (0) to de-activate channel
 
void Drv_Devices_changeChannelState_maintainRunningState(uint8_t channel, uint8_t start)
{
	bool is_running_when_called = is_running;
	uint8_t cur_outputType = outputType;

	Drv_Devices_stopRunning(); //must stop running to change channel settings

	if(start == 1)
	{
		Drv_ADS1299_activateChannel(channel);
	}
	else if(start == 0)
	{
		Drv_ADS1299_deactivateChannel(channel);
	}

	if(is_running_when_called == true)
	{
		Drv_Devices_startRunning(cur_outputType); //restart, if it was running before
	}
}
*/
/**
 * @brief Set test inputs to all channels
 * @param inputCode Input types
 * @param amplitudCode Amplitude of the test signal: ADSTESTSIG_NOCHANGE, ADSTESTSIG_AMP_1X, ADSTESTSIG_AMP_2X 
 * @param freqCode Frequence of the test signal: ADSTESTSIG_NOCHANGE, ADSTESTSIG_PULSE_SLOW, ADSTESTSIG_PULSE_FAST
 
 void Drv_Devices_activateAllChannelsToTestCondition(uint8_t testInputCode, uint8_t amplitudeCode, uint8_t freqCode)
 {
	 bool is_running_when_called = is_running;
	 uint8_t cur_outputType = outputType;
	 
	 Drv_Devices_stopRunning(); //must stop running to change channel settings
	 delayMs(0, 10);
	 
	 Drv_ADS1299_configureInternalTestSignal(amplitudeCode, freqCode); //set the test signal to the desired state
	 Drv_ADS1299_changeInputType(testInputCode);
	 
	 if(is_running_when_called == TRUE)
	 {
		 Drv_Devices_startRunning(cur_outputType); //restart if it was running before
	 }
 }
 */
 /**
  * @brief Print the current state of all ADS1299 registers
  
 void Drv_Devices_printRegisters()
 {
	uint8_t regData[24];
	bool slavePresent = Drv_ADS1299_getSlavePresent(); //is the slave board present?
	uint8_t i = 0; //loop counter
	uint8_t vstring [4];
	
	if(!is_running)
	{

	//First read the registers of the Master Board
	Drv_ADS1299_RREGS(0x00, 0x0C, BOARD_ADS); // read out the first registers
	delayMs(0, 10); // stall to let all that data get read by the PC
	Drv_ADS1299_RREGS(0x0D, 0x17-0x0D, BOARD_ADS); // read out the rest

	Drv_ADS1299_getRegistersData(regData); //get the the current registers

	UART_Send((uint8_t*)("\r\nBoard ADS Registers\r\n"),23);
	
	for(i=0; i<24; i++) //send the 24 ADS1299 registers
	{

		Drv_Devices_printRegisterName(i);
		UART_Send((uint8_t*)("0x"),2);
		itoa(regData[i],vstring,16); // convert to hexadecimal
		UART_Send(vstring,2);
		UART_Send((uint8_t*)("  "),2);
		//UART_Send(&regData[i],1); //send one byte
	}

	if(slavePresent == TRUE)
	{
		//If present, read the registers of the Slave Board
		Drv_ADS1299_RREGS(0x00, 0x0C, SLAVE_ADS); // read out the first registers
		delayMs(0, 10); // stall to let all that data get read by the PC
		Drv_ADS1299_RREGS(0x0D, 0x17-0x0D, SLAVE_ADS); // read out the rest

		Drv_ADS1299_getRegistersData(regData); //get the the current registers

		UART_Send((uint8_t*)("\r\nSlave ADS Registers\r\n"),23);
		
		for(i=0; i<24; i++) //send the 24 ADS1299 registers
		{
			Drv_Devices_printRegisterName(i);
			UART_Send((uint8_t*)("0x"),2);
			itoa(regData[i],vstring,16); // convert to hexadecimal
			UART_Send(vstring,2);
			UART_Send((uint8_t*)("  "),2);
			//UART_Send(&regData[i],1); //send one byte
		}
	}
	

	Drv_Devices_sendEOT(); //end communication
	delayMs(0, 20);
	}
 }
 */
 /**
 * @brief To get and send by UART the name of a specific ADS1299 register
 * @param regNumber Number of register in decimal (0-23)
 */
 /*
 void Drv_Devices_printRegisterName(uint8_t regNumber)
 {
	 switch(regNumber)
	 {
		case 0:
			UART_Send((uint8_t*)("ADS_ID: "),8);
			break;
		case 1:
			UART_Send((uint8_t*)(",CONFIG1: "),10);
			break;
		case 2:
			UART_Send((uint8_t*)(",CONFIG2: "),10);
			break;
		case 3:
			UART_Send((uint8_t*)(",CONFIG3: "),10);
			break;
		case 4:
			UART_Send((uint8_t*)(",LOFF: "),7);
			break;
		case 5:
			UART_Send((uint8_t*)(",CH1SET: "),9);
			break;
		case 6:
			UART_Send((uint8_t*)(",CH2SET: "),9);
			break;
		case 7:
			UART_Send((uint8_t*)(",CH3SET: "),9);
			break;
		case 8:
			UART_Send((uint8_t*)(",CH4SET: "),9);
			break;
		case 9:
			UART_Send((uint8_t*)(",CH5SET: "),9);
			break;
		case 10:
			UART_Send((uint8_t*)(",CH6SET: "),9);
			break;
		case 11:
			UART_Send((uint8_t*)(",CH7SET: "),9);
			break;
		case 12:
			UART_Send((uint8_t*)(",CH8SET: "),9);
			break;
		case 13:
			UART_Send((uint8_t*)(",BIAS_SENSP: "),13);
			break;
		case 14:
			UART_Send((uint8_t*)(",BIAS_SENSN: "),13);
			break;
		case 15:
			UART_Send((uint8_t*)(",LOFF_SENSP: "),13);
			break;
		case 16:
			UART_Send((uint8_t*)(",LOFF_SENSN: "),13);
			break;
		case 17:
			UART_Send((uint8_t*)(",LOFF_FLIP: "),12);
			break;
		case 18:
			UART_Send((uint8_t*)(",LOFF_STATP: "),13);
			break;
		case 19:
			UART_Send((uint8_t*)(",LOFF_STATN: "),13);
			break;
		case 20:
			UART_Send((uint8_t*)(",GPIO: "),7);
			break;
		case 21:
			UART_Send((uint8_t*)(",MISC1: "),8);
			break;
		case 22:
			UART_Send((uint8_t*)(",MISC2: "),8);
			break;
		case 23:
			UART_Send((uint8_t*)(",CONFIG4: "),10);
			break;
		default:
			break;
	 }
 }
 */
 /**
  * @brief Print the current Default Channel Settings
  
 void Drv_Devices_printDefaultChannelSettings()
 {
	 uint8_t defaultSettings[6];
	 uint8_t i = 0; //loop counter
	 bool is_running_when_called = is_running;
	 uint8_t cur_outputType = outputType;

	 //stop running
	 Drv_Devices_stopRunning();

	 Drv_ADS1299_getDefaultChannelSettings(defaultSettings); //get the array with default channel settings

	 for(i=0; i<6; i++)
	 {
		 if(i==1)
		 {
			 defaultSettings[i] = (defaultSettings[i] >> 4) + 48; //48 is the decimal of the ASCCI '0'
		 }
		 else
		 {
			 defaultSettings[i] = defaultSettings[i] + 48; //48 is the decimal of the ASCCI '0'
		 }

		 UART_Send(&(defaultSettings[i]),1);
		 UART_Send((uint8_t*)("\r\n"),2);
	 }

	 Drv_Devices_sendEOT();
	 delayMs(0, 10);

	 //restart if it was running before
	 if(is_running_when_called == TRUE)
	 {
		 Drv_Devices_startRunning(cur_outputType);
	 }

 }
 */
 /**
  * @brief Change lead off detect settings and re-start device
  * @param channel Channel number
  
 void Drv_Devices_changeChannelLeadOffDetect_maintainRunningState(uint8_t channel)
 {
	 bool is_running_when_called = is_running;
	 uint8_t cur_outputType = outputType;

	 //must stop running to change channel settings
	 Drv_Devices_stopRunning();

	 Drv_ADS1299_changeOneChannelLeadOffDetect(channel);

	 //restar if it was running before
	 if(is_running_when_called == TRUE)
	 {
		 Drv_Devices_startRunning(cur_outputType);
	 }
 }
 */
/**
 * @brief Retrieve parameters and execute channel settings
 * @param parameter Setting parameter received as command: PCHAN, NCHAN
 
void Drv_Devices_loadLeadOffSettings(uint8_t parameter)
{
	if(leadOffSettingsCounter == 0)// if it's the first byte in this channel's array, this byte is the channel number to set
	{
		currentChannelToSet = Drv_Devices_getChannelNumber(parameter); // we just got the channel to load settings into (shift number down for array usage)
		leadOffSettingsCounter++;

		if(!is_running)
		{
			uint8_t number = currentChannelToSet + 1 + '0';
			UART_Send((uint8_t*)("Load Lead-off settings of channel: "),35);
			UART_Send(&number,1);
			UART_Send((uint8_t*)("\r\n"),2);
		}

	}
	else
	{//  setting bytes are in order: PCHAN, NCHAN
		parameter = parameter - '0'; //convert char to number
		
		leadOffSettings[currentChannelToSet][leadOffSettingsCounter-1] = parameter;
		
		leadOffSettingsCounter++;
		
		if(leadOffSettingsCounter == 3) // 1 currentChannelToSet, plus 2 leadOff setting parameters
		{
			getLeadOffSettings = FALSE;
		}
	}
} 
 */
/**
 * @brief Determines if the board is Master or Slave and set a flag
 * @return HIGH if the board is Master, LOW if the board is Slave
 */
bool Drv_Devices_isMaster()
{
	bool MSstate = GPIO_getPinState(MS_PORT, MS_PIN); //read M/S signal state

	isMaster = MSstate; //set the flag

	return MSstate;
}
 
/**
 * @brief Return the state of the isMaster flag
 * @return HIGH if the board is Master, LOW if the board is Slave
 */
 bool Drv_Devices_getIsMaster()
 {
	 return isMaster;
 }
 
 /**
  * @brief Return the state of the is_running flag
  * @return TRUE if the board is running, FALSE if the board is not acquiring data
  */
 bool Drv_Devices_getIsRunning()
 {
	 return 1; //is_running;
 }

 /**
  * @brief Send via UART the data acquired by the ADS
  
  void Drv_Devices_sendChannelData()
  {
	  //TODO: revisar el envío de datos: master y slave

	  if(is_running) // if the ADS is acquiring data
	  {
	  
		  uint8_t Header = 0xA0;
		  uint8_t Footer = 0xC0;
		  uint8_t zero = 0x00;

		  uint8_t sampleCnt = 0;
		  uint8_t channelData[48]; //array to get channel data from Master and Slave Board
		  uint8_t i = 0; //loop counter
        UART_Send("AAA",3);
		  while(!(Drv_ADS1299_isDataAvailable())) {} // wait for DRDY pin to be HIGH
        //delayMs(0, 5000);
        UART_Send("BBB",3);
		  //get channel data
		  Drv_ADS1299_getChannelData(&sampleCnt, channelData);

		  UART_Send(&Header,1); //Header
  		  UART_Send(&sampleCnt,1); //send sample counter value

		  if(slavePresent){
		//	  if(sampleCnt % 2 != 0){
		  		  //send Slave Board data
		  		for(i=0; i<24; i++)
		  				  {
		  					  UART_Send(&channelData[i],1);
		  				 //   UART_Send(&meanBoardDataRaw[i],1);
		  				  }

		// 		  }
		//	  else{
				  for(i=24; i<48; i++)
				   		   {
				  		  	  UART_Send(&channelData[i],1);
		  				    //UART_Send(&meanSlaveDataRaw[i],1);

				  		  }
		//	  }

		  }
		  else{
		  for(i=0; i<24; i++)
		     {
			  UART_Send(&channelData[i],1);
			//  UART_Send(&channelData[i],1);
		     }
		  }

		 for(i=0; i<6; i++){
              UART_Send(&zero,1);
		  }

		  UART_Send(&Footer,1); //Footer

	  }
  }
 */
  /**
   * @brief Start the system as Salve. Configure I/O pins
   
  void Drv_Devices_startAsSlave()
  {
		//configure Board ADS chip select pin as input
		GPIO_setPinDir(BOARD_ADS_PORT, BOARD_ADS_PIN, FALSE);

		//configure Slave ADS chip select pin as input
		GPIO_setPinDir(SLAVE_ADS_PORT, SLAVE_ADS_PIN, FALSE);

		//configure ADS Reset pin as input
		GPIO_setPinDir(ADS_RST_PORT, ADS_RST_PIN, FALSE);

		//configure ADS Start pin as input
		GPIO_setPinDir(ADS_START_PORT, ADS_START_PIN, FALSE);

		//configure ADS Data Ready pin as input
		GPIO_setPinDir(ADS_DRDY_PORT, ADS_DRDY_PIN, FALSE);


		//Chip_IOCON_PinMux(LPC_IOCON, 0, 15, IOCON_MODE_INACT, IOCON_FUNC0);	// SSP SCK signal (SCK0 funcionality)
		//Chip_IOCON_PinMux(LPC_IOCON, 0, 17, IOCON_MODE_INACT, IOCON_FUNC0);	// SSP MISO signal (MISO0 funcionality)
		//Chip_IOCON_PinMux(LPC_IOCON, 0, 18, IOCON_MODE_INACT, IOCON_FUNC0);	// SSP MOSI signal (MOSI0 funcionality)

		GPIO_setPinDir(0, 15, FALSE);
		GPIO_setPinDir(0, 17, FALSE);
		GPIO_setPinDir(0, 18, FALSE);


		//LED Configuration
		GPIO_setPinDir(LED_R_PORT, LED_R_PIN, TRUE); //set pin as output
		GPIO_setPinDir(LED_V_PORT, LED_V_PIN, TRUE); //set pin as output
		GPIO_setPinState(LED_V_PORT, LED_V_PIN, FALSE); //set LOW
		GPIO_setPinState(LED_R_PORT, LED_R_PIN, FALSE); //set LOW
  }
*/


/*
   void Drv_Devices_printMenu(void){
		if(!is_running)
			{
				UART_Send((uint8_t*)("\r\n"), 2);
				UART_Send((uint8_t*)("\r\n"), 2);
				UART_Send((uint8_t*)("------------------\r\n"), 20);
				UART_Send((uint8_t*)("  Command list:\r\n"), 16);
				UART_Send((uint8_t*)("------------------\r\n"), 20);
				UART_Send((uint8_t*)("\r\n"), 2);
				UART_Send((uint8_t*)("send 'b' to start data stream\r\n"), 31);
				UART_Send((uint8_t*)("send 's' to stop data stream\r\n"), 30);
				UART_Send((uint8_t*)("use 1,2,3,4,5,6,7,8 to turn OFF channels\r\n"), 42);
				UART_Send((uint8_t*)("use !,@,#,$,%,^,&,* to turn ON channels\r\n"), 41);
				UART_Send((uint8_t*)("in 16chan, use q,w,e,r,t,y,u,i to turn OFF channels\r\n"), 53);
				UART_Send((uint8_t*)("in 16chan, use Q,W,E,R,T,Y,U,I to turn ON channels\r\n"), 52);
				UART_Send((uint8_t*)("send 'd' to set channels to default\r\n"), 37);
				UART_Send((uint8_t*)("send '?' to print all registers\r\n"), 33);
				UART_Send((uint8_t*)("send 'v' to initialize board\r\n"), 30);
				UART_Send((uint8_t*)("send 0,-,=,p,[,] to enable test signals\r\n"), 41);
				UART_Send((uint8_t*)("send 'z (CHANNEL, PCHAN, NCHAN) Z' to start impedance test (see User Manual)\r\n"), 78);
				UART_Send((uint8_t*)("send 'x (CHANNEL, POWER_DOWN, GAIN_SET, INPUT_TYPE_SET, BIAS_SET, SRB2_SET, SRB1_SET) X'  for channel setting (see User Manual)\r\n"), 129);
				UART_Send((uint8_t*)("send 'A' for 2kHz sample rate (only in 8chan)\r\n"), 47);
				UART_Send((uint8_t*)("send 'S' for 1kHz  sample rate\r\n"), 32);
				UART_Send((uint8_t*)("send 'F' for 500Hz sample rate\r\n"), 32);
				UART_Send((uint8_t*)("send 'G' for 250Hz sample rate\r\n"), 32);
			}
	}
*/
/*
static volatile uint32_t tick_ct = 0;
void SysTick_Handler(void) {
   tick_ct++;
}

void delayMs(uint32_t tk) {
	SysTick_Config(SystemCoreClock / 1000);
	uint32_t end = tick_ct + tk;
	while(tick_ct < end)
		__WFI();
}
void delayUs(uint32_t tk) {
	SysTick_Config(SystemCoreClock / 1000000);
	uint32_t end = tick_ct + tk;
	while(tick_ct < end)
		__WFI();
}
*/


  /**
     * @brief Delay in milliseconds
     * @param timer_num Timer to use
     * @return delayInMs Time in milliseconds
     

 
void delayMs(uint32_t delayInMs)
{
     LPC_TIMER1->TCR = 0x02;                // reset timer
      LPC_TIMER1->PR  = 0x00;                // set prescaler to zero
      LPC_TIMER1->MR[0] = delayInMs * ((SystemCoreClock/4) / 1000-1);
      LPC_TIMER1->IR  = 0xff;                // reset all interrrupts
      LPC_TIMER1->MCR = 0x04;                // stop timer on match
      LPC_TIMER1->TCR = 0x01;                // start timer

      // wait until delay time has elapsed
      while (LPC_TIMER1->TCR & 0x01);
   return;
}


  void delayUs(uint32_t delayInUs)
    {
            LPC_TIMER1->TCR = 0x02;                // reset timer
            LPC_TIMER1->PR  = 0x00;                // set prescaler to zero 
            LPC_TIMER1->MR[0] = delayInUs * ((SystemCoreClock/4) / 1000000-1);
            LPC_TIMER1->IR  = 0xff;                // reset all interrrupts 
            LPC_TIMER1->MCR = 0x04;                // stop timer on match 
            LPC_TIMER1->TCR = 0x01;                // start timer

            // wait until delay time has elapsed 
            while (LPC_TIMER1->TCR & 0x01);
      return;
    }
 */
 
 
 
 
 
 
 
 



