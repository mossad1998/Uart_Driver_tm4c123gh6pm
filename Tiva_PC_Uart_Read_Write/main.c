#include "tm4c123gh6pm.h"
#include "GPIO_Driver.h"
#include "UART_Driver.h"
#include <stdint.h>
#include "stdio.h"

//Example of using Uart_Driver

/* This driver uses the GPIO_Driver and Uart_Driver libraries which provide definitions for
   different functions that help to intialize Tiva c  peripherals.
   To use this driver you will also need to use tm4c123gh6pm to map 
   registers correctly.
   This example used to read and write to and from a terminal such as putty and tera term.
   Using uart protocol with speed 9600 and word legnth 8
   Used pins
   ===========
   Pin A0 as Rx
   Pin A1 as Tx
   Pin F1 as Red Led
   Pin F2 as Blue Led
   Pin F3 as Green Led
   History
   =======
   2021/August/08  - First release (Mosad)
   mo.eldibani@gmail.com
*/

void New_Line_Message(void);
void Message_1(void);
void Message_2(void);
void Message_3(void);
void LED(char type[],int mode);

int main()
{

      CLK_Enable('A');                                                          //Enable Clock for Port A
      CLK_Enable_UART_Module(0);                                                //Enable Clock for UART0
      CLK_Enable('F');                                                          //Enable Clock for Port F
      GPIO_PORT_UNLOCK('F');                                                    //Unlock for port F

      Enable_UART_Module(0,"Disable");                                          //Disable UART0  
      Baud_Rate_UART_Module(0,9600);                                            //Specify 9600 Baud rate
      Word_Length_UART_Module(0,8);                                             //Specify 8Bits word length
      Enable_UART_Module(0,"Enable");                                           //Enable UART0

      PIN_ANALOG_DIGITAL('A',0,"Digital");                                      //Enable Digital For Pin A0
      PIN_ANALOG_DIGITAL('A',1,"Digital");                                      //Enable Digital For Pin A1
      PIN_FUNCTION_SELECT('A',0,"Alternative");                                 //Select Alternative Function for pin A0
      PIN_FUNCTION_SELECT('A',1,"Alternative");                                 //Select Alternative Function for pin A1
      PIN_CONFIGURE('A',0,"UART");                                              //Configure A0 as UART
      PIN_CONFIGURE('A',1,"UART");                                              //Configure A1 as UART
      
      PIN_INPUT_OUTPUT('F',1,"Output");                                         //To specifiy pin F1 as Output
      PIN_INPUT_OUTPUT('F',2,"Output");                                         //To specifiy pin F2 as Output
      PIN_INPUT_OUTPUT('F',3,"Output");                                         //To specifiy pin F3 as Output
      PIN_ANALOG_DIGITAL('F',1,"Digital");                                      //Enable Digital For Pin F1
      PIN_ANALOG_DIGITAL('F',2,"Digital");                                      //Enable Digital For Pin F2
      PIN_ANALOG_DIGITAL('F',3,"Digital");                                      //Enable Digital For Pin F3
      
      Message_1();                                                              //Print message for interface
      New_Line_Message();                                                       //Print New Line
      Message_2();                                                              //Print message for interface
      New_Line_Message();                                                       //Print New Line
      Message_3();                                                              //Print message for interface
      New_Line_Message();                                                       //Print New Line

  while(1)
  {
    char input;
      input = Receive_UART_Module(0);                                           //Read Input For Uart
      if(input == '1')
      {
        LED("RED",1);                                                           //RED led ON
        LED("BLUE",0);                                                          //BLUE led OFF
        LED("GREEN",0);                                                         //GREEN led OFF
      }
      if(input == 'G')
      {
        LED("RED",0);                                                           //RED led OFF
        LED("BLUE",0);                                                          //BLUE led OFF
        LED("GREEN",1);                                                         //GREEN led ON
      }
      if(input == 'B')
      {
        LED("RED",0);                                                           //RED led OFF
        LED("BLUE",1);                                                          //BLUE led ON
        LED("GREEN",0);                                                         //GREEN led OFF
      }
  } 

}
void Message_1(void)                                                            //To Send all letters of a whole Sentence
{
          char message1[]={"To Turn Red on Press R"};
          int length = strlen(message1);
          for(int i=0;i<length;i++)
          Transmit_UART_Module(0,message1[i]);
}

void Message_2(void)                                                            //To Send all letters of a whole Sentence
{         char message2[]={"To Turn Blue on Press B"};                          
          int length = strlen(message2);
          for(int i=0;i<length;i++)
          Transmit_UART_Module(0,message2[i]);
}

void Message_3(void)                                                            //To Send all letters of a whole Sentence 
{         char message3[]={"To Turn Green on Press G"};
          int length = strlen(message3);
          for(int i=0;i<length;i++)
          Transmit_UART_Module(0,message3[i]);
}

void New_Line_Message(void)                                                     //Message for newline
{
          Transmit_UART_Module(0,10);   
          Transmit_UART_Module(0,13); 
}

void LED(char type[],int mode)                                                  //To control led
{
 if(strcmp(type , "GREEN")==0)
      {
          if(mode==1)
             PIN_WRITE_DIGITAL('F',3,"HIGH");                                   //Turn ON Green LED
          else if (mode==0)
             PIN_WRITE_DIGITAL('F',3,"LOW");                                    //Turn OFF Green LED                                           
      }
          else if (strcmp(type , "RED")==0)
      {
          if(mode==1)
             PIN_WRITE_DIGITAL('F',1,"HIGH");                                   //Turn ON Red LED
          else if (mode==0)
             PIN_WRITE_DIGITAL('F',1,"LOW");                                    //Turn OFF Red LED
      }
          else if (strcmp(type , "BLUE")==0)
      {
          if(mode==1)
             PIN_WRITE_DIGITAL('F',2,"HIGH");                                   //Turn ON Blue LED
          else if (mode==0)
             PIN_WRITE_DIGITAL('F',2,"LOW");                                    //Turn OFF BLue LED                                                     
      }
}