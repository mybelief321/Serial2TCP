#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__


#define BUFFER_SIEZE 1024
#define HOST_PORT 0

/*
* Function	: Set_Port
* Parameter	:
* Return	:error:-1  
* About		: To set the serialport's parameter
*/
int Set_Port(int fd,int baud_rate,int data_bits,char parity,int stop_bits);

/*
* Function	: Open_Port
* Parameter	:int com_port:0-5
* Return	:error:-1   success:0
* About		: To open the SERIALPORT
*/	
int Open_Port(int com_port);

/*
* Function	: Serial_SendStr
* Parameter	:_fd: The ComportNo. _buf: Message to Send   
* Return	:void
* About		: SendMessage
*/	
void Serial_SendStr(int _fd,char *_buf);


#endif
