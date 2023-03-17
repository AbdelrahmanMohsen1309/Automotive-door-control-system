/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Common_Macros.h
 *       Module:  -
 *
 *  Description:  Contains types that dependent on platform - CortexM4     
 *  
 *********************************************************************************************************************/
#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
typedef unsigned char         boolean;       /*        TRUE .. FALSE           */

typedef signed char           sint8;         /*        -128 .. +127            */
typedef unsigned char         uint8;         /*           0 .. 255             */
typedef signed short          sint16;        /*      -32768 .. +32767          */
typedef unsigned short        uint16;        /*           0 .. 65535           */
typedef signed long           sint32;        /* -2147483648 .. +2147483647     */
typedef unsigned long         uint32;        /*           0 .. 4294967295      */

typedef float                 float32;
typedef double                float64;

#define WORD_LENGTH_BITS      32u
#define WORD_LENGTH_BYTES     4u
#define MSB_FIRST             0u    /* big endian bit ordering */
#define LSB_FIRST        1u    /* little endian bit ordering */

#define HIGH_BYTE_FIRST  0u    /* big endian byte ordering */
#define LOW_BYTE_FIRST   1u    /* little endian byte ordering */

#ifndef TRUE
   #define TRUE   1u
#endif

#ifndef FALSE
   #define FALSE  0u
#endif

#define ENABLE    1u
#define DISABLE   0u

#define CPU_BIT_ORDER    LSB_FIRST        /*little endian bit ordering*/
#define CPU_BYTE_ORDER   LOW_BYTE_FIRST   /*little endian byte ordering*/

#define NULL_PTR       ((void *)0)



/**********************************************************************************************************************
 *  Serial Communications
 *********************************************************************************************************************/
#define CAN_PROTOCOL  1
#define LIN_PROTOCOL  2
#define SPI_PROTOCOL  3
#define I2C_PROTOCOL  4
#define UART_PROTOCOL 5

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#ifndef COMMON_MACROS
#define COMMON_MACROS

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) ( REG |= ( 1 << BIT ) )

/* Clear a certain bit in any register */
#define CLR_BIT(REG,BIT) ( REG &= ( ~ (  1 << BIT  ) ) )

/* Toggle a certain bit in any register */
#define TOG_BIT(REG,BIT) (REG^=(((uint32)1)<<BIT))

/* Returns value of bit (bitN) in a register (reg)*/
#define GET_BIT(reg,bitN)    (1 & ((reg)>>bitN))      

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#endif




 
#endif  /* COMMON_MACROS_H */

/**********************************************************************************************************************
 *  END OF FILE: Common_Macros.h
 *********************************************************************************************************************/

