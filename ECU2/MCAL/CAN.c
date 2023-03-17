#include "CAN.h"

  void CAN_close(CAN_Handle handle)
	{
		//TODO
	}
   
  void CAN_init(void)
	{
		//TODO
	}
   
  int_fast16_t CAN_control(CAN_Handle handle, uint_fast16_t cmd, void *arg)
	{
		//TODO
		return 1;
	}
   
  CAN_Handle CAN_open(uint_least8_t index, CAN_Params *params)
	{
		//TODO
		CAN_Handle handle;
		return handle;
	}
   
  void CAN_Params_init(CAN_Params *params)
	{
		//TODO
	}
   
  int_fast32_t CAN_write(CAN_Handle handle, const void *buffer, size_t size)
	{
		//TODO
		return 1;
	}
   
  int_fast32_t CAN_read(CAN_Handle handle, void *buffer, size_t size)
	{
		//TODO
		return 1;
	}

/*End of the File*/
	
