/*
		1
    2  * Copyright (c) 2018, Texas Instruments Incorporated
    3  * All rights reserved.
    4  *
    5  * Redistribution and use in source and binary forms, with or without
    6  * modification, are permitted provided that the following conditions
    7  * are met:
    8  *
    9  * *  Redistributions of source code must retain the above copyright
   10  *    notice, this list of conditions and the following disclaimer.
   11  *
   12  * *  Redistributions in binary form must reproduce the above copyright
   13  *    notice, this list of conditions and the following disclaimer in the
   14  *    documentation and/or other materials provided with the distribution.
   15  *
   16  * *  Neither the name of Texas Instruments Incorporated nor the names of
   17  *    its contributors may be used to endorse or promote products derived
   18  *    from this software without specific prior written permission.
   19  *
   20  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   21  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
   22  * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   23  * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   24  * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   25  * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   26  * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
   27  * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   28  * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
   29  * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
   30  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
   31  */
      /*!*****************************************************************************
   33  *  @file       CAN.h
   34  *  @brief      <b>PRELIMINARY</b> CAN driver interface
   35  *
   36  *  <b>WARNING</b> These APIs are <b>PRELIMINARY</b>, and subject to
   37  *  change in the next few months.
   38  *
   39  *  To use the CAN driver, ensure that the correct driver library for your
   40  *  device is linked in and include this header file as follows:
   41  *  @code
   42  *  #include <ti/drivers/CAN.h>
   43  *  @endcode
   44  *
   45  *  This module serves as the main interface for applications.  Its purpose
   46  *  is to redirect the CAN APIs to specific driver implementations
   47  *  which are specified using a pointer to a #CAN_FxnTable.
   48  *
   49  *  # Overview #
   50  *  The Controller Area Network (CAN) driver is a generic driver that allows
   51  *  for communication on a CAN bus. It is a two-wire, half-duplex, LAN system
   52  *  that is collision free. The main method of transfer is by broadcasting.
   53  *  The CAN protocol defines the format of data transfer, and this CAN driver
   54  *  allows full functionality as a transmitting and receiving node on a bus.
   55  *  However, there can be higher-level software layers and stacks that use this
   56  *  driver to enable more advanced features.
   57  *  Functional modes available in this driver include blocking and non-blocking.
   58  *
   59  *  The APIs in this driver serve as an interface to a typical RTOS
   60  *  application. The specific peripheral implementations are responsible for
   61  *  creating all the RTOS specific primitives to allow for thread-safe
   62  *  operation.
   63  *
   64  *  # Usage #
   65  *
   66  *  The CAN driver interface provides device independent APIs, data types,
   67  *  and macros.  The following code example opens a CAN instance, creates
   68  *  an incrementing CAN frame, and continually writes them to the CAN bus.
   69  *  NOTE: a CAN receiver on this bus is needed, or else this transmitter will
   70  *  continually throw an error if it does not detect an ACK.
   71  *
   72  *  @code
   73  *    uint8_t i;
   74  *    // Initialize the CAN driver
   75  *    CAN_init();
   76  *
   77  *    CAN_Handle canHandle;
   78  *    CAN_Params canParams;
   79  *    CAN_Params_init(&canParams);
   80  *    canHandle = CAN_open(Board_CAN0, &canParams);
   81  *
   82  *    if (canHandle == NULL) {
   83  *        // CAN_open() failed
   84  *        while (1);
   85  *    }
   86  *
   87  *    for (i = 0; ; ++i) {
   88  *        CAN_Frame canFrame[1];
   89  *        canFrame[0].can_id = i;
   90  *        canFrame[0].err = 0;
   91  *        canFrame[0].rtr = 0;
   92  *        canFrame[0].eff = 1;
   93  *        canFrame[0].dlc = i % 9;
   94  *        canFrame[0].data[0] = i;
   95  *        canFrame[0].data[1] = i + 1;
   96  *        canFrame[0].data[2] = i + 2;
   97  *        canFrame[0].data[3] = i + 3;
   98  *        canFrame[0].data[4] = i + 4;
   99  *        canFrame[0].data[5] = i + 5;
  100  *        canFrame[0].data[6] = i + 6;
  101  *        canFrame[0].data[7] = i + 7;
  102  *
  103  *        CAN_write(canHandle, canFrame, sizeof(canFrame));
  104  *    }
  105  *  @endcode
  106  *
  107  *  Details for the example code above are described in the following
  108  *  subsections.
  109  *
  110  *
  111  *  ### CAN Driver Configuration #
  112  *
  113  *  In order to use the CAN APIs, the application is required
  114  *  to provide device-specific CAN configuration in the Board.c file.
  115  *  The CAN driver interface defines a configuration data structure:
  116  *
  117  *  @code
  118  *  typedef struct CAN_Config_ {
  119  *      CAN_FxnTable  const    *fxnTablePtr;
  120  *      void                   *object;
  121  *      void          const    *hwAttrs;
  122  *      CAN_Frame              *rxBufPtr;
  123  *      CAN_frame              *txBufPtr;
  124  *      size_t                  rxBufSize;
  125  *      size_t                  txBufSize;
  126  *  } CAN_Config;
  127  *  @endcode
  128  *
  129  *  You will need to check the device-specific CAN driver implementation's
  130  *  header file for example configuration.  Please also refer to the
  131  *  Board.c file of any of your examples to see the CAN configuration.
  132  *
  133  *  ### Initializing the CAN Driver #
  134  *
  135  *  CAN_init() must be called before any other CAN APIs.  This function
  136  *  calls the device implementation's CAN initialization function, for each
  137  *  element of CAN_config[].
  138  *
  139  *  ### Opening the CAN Driver #
  140  *
  141  *  Opening a CAN requires four steps:
  142  *  1.  Create and initialize a CAN_Params structure.
  143  *  2.  Fill in the desired parameters.
  144  *  3.  Call CAN_open(), passing the index of the CAN in the CAN_config
  145  *      structure, and the address of the CAN_Params structure.  The
  146  *      CAN instance is specified by the index in the CAN_config structure.
  147  *  4.  Check that the CAN handle returned by CAN_open() is non-NULL,
  148  *      and save it.  The handle will be used to read and write to the
  149  *      CAN you just opened.
  150  *
  151  *  Only one CAN index can be used at a time; calling CAN_open() a second
  152  *  time with the same index previously passed to CAN_open() will result in
  153  *  an error.  You can, though, re-use the index if the instance is closed
  154  *  via CAN_close().
  155  *  In the example code, Board_CAN0 is passed to CAN_open().  This macro
  156  *  is defined in the example's Board.h file.
  157  *
  158  *
  159  *  ### Modes of Operation #
  160  *
  161  *  The CAN driver can operate in blocking mode or nonblocking mode, by
  162  *  setting the mode parameters passed to CAN_open().
  163  *  If these parameters are not set, as in the example code, the CAN
  164  *  driver defaults to blocking mode.  Options for the mode parameter are
  165  *  #CAN_MODE_BLOCKING and #CAN_MODE_NONBLOCKING:
  166  *
  167  *  - #CAN_MODE_BLOCKING uses a semaphore to block while data is being sent
  168  *    or read. The context of calling CAN_read() or CAN_write() must be a Task
  169  *    when using #CAN_MODE_BLOCKING. The CAN_write() or CAN_read() call
  170  *    will block until all data is sent or received, or the write timeout or
  171  *    read timeout expires, whichever happens first.
  172  *
  173  *  - #CAN_MODE_NONBLOCKING is non-blocking and CAN_read() and CAN_write()
  174  *    will return either with the number of bytes successfully read/written,
  175  *    or a negative error number.
  176  *
  177  *  ### Reading and Writing data #
  178  *
  179  *  The example code reads one CAN frame from the CAN instance, and then writes
  180  *  one CAN frame back to the same instance:
  181  *
  182  *  @code
  183  *  CAN_read(can, &canFrame, sizeof(canFrame));
  184  *  CAN_write(can, &canFrame, sizeof(canFrame));
  185  *  @endcode
  186  *
  187  *  The CAN driver allows CAN_read() and CAN_write() calls to happen for any
  188  *  node at any time from the CAN bus. Please see the CAN protocol for how it
  189  *  handles collisions. The ability to filter incoming messages are also
  190  *  available through CAN_Params.
  191  *
  192  *  # Implementation #
  193  *
  194  *  The CAN driver interface module is joined (at link time) to an
  195  *  array of CAN_Config data structures named *CAN_config*.
  196  *  CAN_config is implemented in the application with each entry being an
  197  *  instance of a CAN peripheral. Each entry in *CAN_config* contains a:
  198  *  - (CAN_FxnTable *) to a set of functions that implement a CAN peripheral
  199  *  - (void *) data object that is associated with the CAN_FxnTable
  200  *  - (void *) hardware attributes that are associated with the CAN_FxnTable
  201  *
  202  *  The CAN APIs are redirected to the device specific implementations
  203  *  using the CAN_FxnTable pointer of the CAN_config entry.
  204  *  In order to use device specific functions of the CAN driver directly,
  205  *  link in the correct driver library for your device and include the
  206  *  device specific CAN driver header file (which in turn includes CAN.h).
  207  *  For example, for the MSP432 family of devices, you would include the
  208  *  following header file:
  209  *    @code
  210  *    #include <ti/drivers/can/CANMSP432.h>
  211  *    @endcode
  212  *
  213  *  ============================================================================
  214  */
   
  #ifndef ti_drivers_CAN__include
  #define ti_drivers_CAN__include
  
  #include <stddef.h>
  #include <stdint.h>
   
   
  #define CAN_CMD_RESERVED           (32)
   
  #define CAN_STATUS_RESERVED        (-32) 
  #define CAN_STATUS_SUCCESS         (0)
   
  #define CAN_STATUS_ERROR           (-1)
   
  #define CAN_STATUS_UNDEFINEDCMD    (-2)
  
  #define  CAN_WAIT_FOREVER           (~(0U))
   
  typedef struct CAN_Config_    *CAN_Handle;
   
  typedef enum CAN_Mode_ {
  CAN_MODE_BLOCKING,
  CAN_MODE_NONBLOCKING
  } CAN_Mode; 
  
	typedef enum CAN_Direction_ {
       CAN_DIRECTION_READ        = 0x1,
       CAN_DIRECTION_WRITE       = 0x2,
       CAN_DIRECTION_READWRITE   = 0x3,
  } CAN_Direction;
   
  typedef struct CAN_Params_ {
       CAN_Mode  mode;         
       CAN_Direction  direction; 
       uint32_t  filterID;     
       uint32_t  filterMask;   
       uint32_t  readTimeout;  
       uint32_t  writeTimeout; 
  } CAN_Params;
   
  typedef struct can_frame CAN_Frame;
   
  typedef void (*CAN_CloseFxn) (CAN_Handle handle);
   
  typedef int_fast16_t (*CAN_ControlFxn) (CAN_Handle handle, uint_fast16_t cmd, void *arg);
   
  typedef void (*CAN_InitFxn) (CAN_Handle handle);
   
  typedef CAN_Handle (*CAN_OpenFxn) (CAN_Handle handle, CAN_Params *params);
   
  typedef int_fast32_t (*CAN_ReadFxn) (CAN_Handle handle, void *buffer,
       size_t size);
   
  typedef int_fast32_t (*CAN_WriteFxn) (CAN_Handle handle, const void *buffer,
       size_t size);
   
  typedef void (*CAN_TxMsgFxn) (CAN_Handle handle);
   
  typedef struct CAN_FxnTable_ {
       CAN_CloseFxn        closeFxn;
   
       CAN_ControlFxn      controlFxn;
   
       CAN_InitFxn         initFxn;
   
       CAN_OpenFxn         openFxn;
   
       CAN_ReadFxn         readFxn;
   
       CAN_WriteFxn        writeFxn;
   
       CAN_TxMsgFxn        txMsgFxn;
  } CAN_FxnTable;
   
   typedef struct CAN_Config_ {
       CAN_FxnTable   const *fxnTablePtr;
   
       void                 *object;
   
       void           const *hwAttrs;
   
       CAN_Frame            *rxBufPtr;
   
       CAN_Frame            *txBufPtr;
   
       size_t                rxBufSize;
   
       size_t                txBufSize;
  } CAN_Config;
   
  extern void CAN_close(CAN_Handle handle);
   
  extern void CAN_init(void);
   
  extern int_fast16_t CAN_control(CAN_Handle handle, uint_fast16_t cmd, void *arg);
   
  extern CAN_Handle CAN_open(uint_least8_t index, CAN_Params *params);
   
  extern void CAN_Params_init(CAN_Params *params);
   
  extern int_fast32_t CAN_write(CAN_Handle handle, const void *buffer, size_t size);
   
  extern int_fast32_t CAN_read(CAN_Handle handle, void *buffer, size_t size);
	
	struct CAN_t {
		  void 				 (*CAN_close)      (CAN_Handle);
			void 				 (*CAN_init)       (void);
			int_fast16_t (*CAN_control)    (CAN_Handle, uint_fast16_t, void *);
			CAN_Handle   (*CAN_open)       (uint_least8_t, CAN_Params *);
 			void         (*CAN_Params_init)(CAN_Params *);
			int_fast32_t (*CAN_write)      (CAN_Handle, const void *, size_t);
			int_fast32_t (*CAN_read)       (CAN_Handle, void *, size_t);
	};
   
  #endif /* ti_drivers_CAN__include */
	/*End of the File*/
