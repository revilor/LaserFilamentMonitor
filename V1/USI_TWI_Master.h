/*****************************************************************************
*
*
* File              USI_TWI_Master.h compiled with gcc
* Date              Friday, 10/31/08		Boo!
* Updated by        jkl
*
*
* Supported devices : All device with USI module can be used.
*                     The example is written for the ATtiny2313
*
* AppNote           : AVR310 - Using the USI module as a TWI Master
*
* This is modified to just do I2C communication on ATtiny2313 running at 
*	1MHz. Fast mode is probably possible, but would need a faster clock
*	and has not been tested.
*
*	12/15/08	Added declaration of USI_TWI_Start_Memory_Read	-jkl
****************************************************************************/

#ifndef USI_TWI_MASTER_H_INCLUDED
#define USI_TWI_MASTER_H_INCLUDED

//********** Defines **********//

// Defines controlling timing limits - SCL <= 100KHz.

// For use with _delay_us()
#define T2_TWI    5 		// >4,7us
#define T4_TWI    4 		// >4,0us

// Defines error code generating
//#define PARAM_VERIFICATION
//#define NOISE_TESTING
#define SIGNAL_VERIFY		// This should probably be on always.

/****************************************************************************
  Bit and byte definitions
****************************************************************************/
#define TWI_READ_BIT  0u       // Bit position for R/W bit in "address byte".
#define TWI_ADR_BITS  1u       // Bit position for LSB of the slave address bits in the init byte.
#define TWI_NACK_BIT  0u       // Bit position for (N)ACK bit.

// Note these have been renumbered from the Atmel Apps Note. Most likely errors are now
//		lowest numbers so they're easily recognized as LED flashes.
#define USI_TWI_NO_DATA             0x08  // Transmission buffer is empty
#define USI_TWI_DATA_OUT_OF_BOUND   0x09  // Transmission buffer is outside SRAM space
#define USI_TWI_UE_START_CON        0x07  // Unexpected Start Condition
#define USI_TWI_UE_STOP_CON         0x06  // Unexpected Stop Condition
#define USI_TWI_UE_DATA_COL         0x05  // Unexpected Data Collision (arbitration)
#define USI_TWI_NO_ACK_ON_DATA      0x02  // The slave did not acknowledge  all data
#define USI_TWI_NO_ACK_ON_ADDRESS   0x01  // The slave did not acknowledge  the address
#define USI_TWI_MISSING_START_CON   0x03  // Generated Start Condition not detected on bus
#define USI_TWI_MISSING_STOP_CON    0x04  // Generated Stop Condition not detected on bus
#define USI_TWI_BAD_MEM_READ	    0x0A  // Error during external memory read

// Device dependent defines ADDED BACK IN FROM ORIGINAL ATMEL .H

#if defined(__AVR_AT90Mega169__) | defined(__AVR_ATmega169__) | \
    defined(__AVR_AT90Mega165__) | defined(__AVR_ATmega165__) | \
    defined(__AVR_ATmega325__) | defined(__AVR_ATmega3250__) | \
    defined(__AVR_ATmega645__) | defined(__AVR_ATmega6450__) | \
    defined(__AVR_ATmega329__) | defined(__AVR_ATmega3290__) | \
    defined(__AVR_ATmega649__) | defined(__AVR_ATmega6490__)
    #define DDR_USI             DDRE
    #define PORT_USI            PORTE
    #define PIN_USI             PINE
    #define PORT_USI_SDA        PORTE5
    #define PORT_USI_SCL        PORTE4
    #define PIN_USI_SDA         PINE5
    #define PIN_USI_SCL         PINE4
#endif

#if defined(__AVR_ATtiny25__) | defined(__AVR_ATtiny45__) | defined(__AVR_ATtiny85__) | \
    defined(__AVR_AT90Tiny26__) | defined(__AVR_ATtiny26__)
    #define DDR_USI             DDRB
    #define PORT_USI            PORTB
    #define PIN_USI             PINB
    #define PORT_USI_SDA        PORTB0
    #define PORT_USI_SCL        PORTB2
    #define PIN_USI_SDA         PINB0
    #define PIN_USI_SCL         PINB2
#endif

#if defined(__AVR_ATtiny84__) | defined(__AVR_ATtiny44__) | defined(__AVR_ATtiny44A__)
    #define DDR_USI				DDRA
    #define PORT_USI			PORTA
    #define PIN_USI				PINA
    #define PORT_USI_SDA		PORTA6
    #define PORT_USI_SCL	    PORTA4
    #define PIN_USI_SDA		    PINA6
    #define PIN_USI_SCL			PINA4
#endif

#if defined(__AVR_AT90Tiny2313__) | defined(__AVR_ATtiny2313__)
    #define DDR_USI             DDRB
    #define PORT_USI            PORTB
    #define PIN_USI             PINB
    #define PORT_USI_SDA        PORTB5
    #define PORT_USI_SCL        PORTB7
    #define PIN_USI_SDA         PINB5
    #define PIN_USI_SCL         PINB7
#endif

//********** Prototypes **********//

#ifdef __ECV__

#pragma ECV verifyincludefiles
extern void _delay_loop_2(uint16_t __count);

#else

#include <util/delay_basic.h>

#endif

// Delay a smallish number of microseconds (max. 32767)
inline void _delay_us(uint16_t us)
{
	_delay_loop_2(us * 2);			// each iteration takes 4 clocks, so at 8MHz clock we need 2 iterations per microsecond
}

void USI_TWI_Master_Initialise();
bool USI_TWI_Start_Random_Read(uint8_t * array, uint8_t);
bool USI_TWI_Start_Read_Write(uint8_t * array, uint8_t);
bool USI_TWI_Master_Stop();
uint8_t USI_TWI_Get_State_Info();

#endif // USI_TWI_MASTER_H_INCLUDED
