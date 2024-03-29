/* vim: set sw=8 ts=8 si et: */
/*********************************************
* An implemenation of the STK500 specification (appl. note AVR068) for atmega8
* * Author: Guido Socher, Copyright: GPL
*
* Terminal capabilities for updating SW/HW version:
* Idea from Florin-Viorel Petrov, www.fonitzu.com/electronics, Date: 28Feb2006
* Florin-Viorel's version was a bit more fancy than the version implemented
* here. This implemenation is just small and simple.
*
* Copyright: GPL
**********************************************/
#include <inttypes.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include "uart.h"
#include "led.h"
#include "spi.h"
#include "avr_compat.h"
#include "command.h"
#include "timeout.h"

// remember to change the "AvrUsb500-X.X terminal mode" version string towards the end
// of the program at version change.

#define CONFIG_PARAM_BUILD_NUMBER_LOW   0
#define CONFIG_PARAM_BUILD_NUMBER_HIGH  1
// be careful with changing HW versions. avrstudio does not like all numbers:
#define CONFIG_PARAM_HW_VER             2
// update here our own default sw version:
#define D_CONFIG_PARAM_SW_MAJOR           2
#define D_CONFIG_PARAM_SW_MINOR           4
#define CONFIG_PARAM_VTARGET 50
#define CONFIG_PARAM_VADJUST 25
#define CONFIG_PARAM_OSC_PSCALE 2
#define CONFIG_PARAM_OSC_CMATCH 1

// you can change the CONFIG_PARAM_SW in terminal mode
#define EEPROM_MAJOR            ((uint8_t*)2)
#define EEPROM_MINOR            ((uint8_t*)1)
#define EEPROM_MAGIC            ((uint8_t*)0)
uint8_t CONFIG_PARAM_SW_MAJOR;
uint8_t CONFIG_PARAM_SW_MINOR;
const char terminal_init[] PROGMEM = {"\x1B[0m\x1B[2J\x1B[0;0f"};

#define MSG_IDLE 0
#define MSG_WAIT_SEQNUM 1
#define MSG_WAIT_SIZE1 2
#define MSG_WAIT_SIZE2 3
#define MSG_WAIT_TOKEN 4
#define MSG_WAIT_MSG 5
#define MSG_WAIT_CKSUM 6

static unsigned char msg_buf[295];
static unsigned char param_reset_polarity=1; // 1=avr (reset active=low), 0=at89 (not supported by this avrusb500)
static unsigned char param_controller_init=0;
unsigned long address=0;
unsigned long saddress=0;

/* transmit an answer back to the programmer software, message is
 * in msg_buf, seqnum is the seqnum of the last message from the programmer software,
 * len=1..275 according to avr068 */
void transmit_answer(unsigned char seqnum,unsigned int len)
{
        unsigned char cksum;
        unsigned char ch;
        int i;
        if (len>285 || len <1){
                // software error
                len = 2;
                // msg_buf[0]: not changed
                msg_buf[1] = STATUS_CMD_FAILED;
        }
        uart_sendchar(MESSAGE_START); // 0x1B
        cksum = MESSAGE_START^0;
        uart_sendchar(seqnum);
        cksum^=seqnum;
        ch=(len>>8)&0xFF;
        uart_sendchar(ch);
        cksum^=ch;
        ch=len&0xFF;
        uart_sendchar(ch);
        cksum^=ch;
        uart_sendchar(TOKEN); // 0x0E
        cksum^=TOKEN;
        wd_kick();
        for(i=0;i<len;i++){
                uart_sendchar(msg_buf[i]);
                cksum^=msg_buf[i];
        }
        uart_sendchar(cksum);
}

void programcmd(unsigned char seqnum)
{
        unsigned char tmp,tmp2,addressing_is_word,ci,cj,cstatus;
        unsigned int answerlen;
        unsigned long poll_address=0;
        unsigned int i,nbytes;
        // distingush addressing CMD_READ_EEPROM_ISP (8bit) and CMD_READ_FLASH_ISP (16bit)
        addressing_is_word=1; // 16 bit is default

        switch(msg_buf[0]){
                case CMD_SIGN_ON:
                // prepare answer:
                msg_buf[0] = CMD_SIGN_ON; // 0x01
                msg_buf[1] = STATUS_CMD_OK; // 0x00
                msg_buf[2] = 8; //len
                strcpy((char *)&(msg_buf[3]),"AVRISP_2"); // note: this copied also the null termination
                answerlen=11;
                break;

                case CMD_SET_PARAMETER:
                // not implemented:
                // PARAM_VTARGET
                // PARAM_VADJUST
                // PARAM_OSC_PSCALE
                // PARAM_OSC_CMATCH
                if (msg_buf[1]==PARAM_SCK_DURATION){
                        spi_set_sck_duration(msg_buf[2]);
                }else if(msg_buf[1]==PARAM_RESET_POLARITY){
                        param_reset_polarity=msg_buf[2];
                }else if(msg_buf[1]==PARAM_CONTROLLER_INIT){
                        param_controller_init=msg_buf[2];
                }
                answerlen = 2;
                //msg_buf[0] = CMD_SET_PARAMETER;
                msg_buf[1] = STATUS_CMD_OK;
                break;

                case CMD_GET_PARAMETER:
                tmp=0xff;
                switch(msg_buf[1])
                {
                        case PARAM_BUILD_NUMBER_LOW:
                                tmp = CONFIG_PARAM_BUILD_NUMBER_LOW;
                                break;
                        case PARAM_BUILD_NUMBER_HIGH:
                                tmp = CONFIG_PARAM_BUILD_NUMBER_HIGH;
                                break;
                        case PARAM_HW_VER:
                                tmp = CONFIG_PARAM_HW_VER;
                                break;
                        case PARAM_SW_MAJOR:
                                tmp = CONFIG_PARAM_SW_MAJOR;
                                break;
                        case PARAM_SW_MINOR:
                                tmp = CONFIG_PARAM_SW_MINOR;
                                break;
                        case PARAM_VTARGET:
                                tmp = CONFIG_PARAM_VTARGET;
                                break;
                        case PARAM_VADJUST:
                                tmp = CONFIG_PARAM_VADJUST;
                                break;
                        case PARAM_SCK_DURATION:
                                tmp = spi_get_sck_duration();
                                break;
                        case PARAM_RESET_POLARITY:   // is actually write only, list anyhow
                                tmp = param_reset_polarity;
                                break;
                        case PARAM_CONTROLLER_INIT:
                                tmp = param_controller_init;
                                break;
                        case PARAM_OSC_PSCALE:
                                tmp = CONFIG_PARAM_OSC_PSCALE;
                                break;
                        case PARAM_OSC_CMATCH:
                                tmp = CONFIG_PARAM_OSC_CMATCH;
                                break;
                        case PARAM_TOPCARD_DETECT: // stk500 only
                                tmp = 0; // no card ??
                                break;
                        case PARAM_DATA: // stk500 only
                                tmp = 0; 
                                break;
                        default: 
                                break;
                }
                if (tmp ==0xff){
                        // command not understood
                        answerlen = 2;
                        //msg_buf[0] = CMD_GET_PARAMETER;
                        msg_buf[1] = STATUS_CMD_UNKNOWN;
                }else{
                        answerlen = 3;
                        //msg_buf[0] = CMD_GET_PARAMETER;
                        msg_buf[1] = STATUS_CMD_OK;
                        msg_buf[2] = tmp;
                }
                break;

                case CMD_LOAD_ADDRESS:
                address =  ((unsigned long)msg_buf[1])<<24;
                address |= ((unsigned long)msg_buf[2])<<16;
                address |= ((unsigned long)msg_buf[3])<<8;
                address |= ((unsigned long)msg_buf[4]);
                answerlen = 2;
                //msg_buf[0] = CMD_LOAD_ADDRESS;
                msg_buf[1] = STATUS_CMD_OK;
                break;

                case CMD_FIRMWARE_UPGRADE:
                // firmare upgrade is not supported this way
                answerlen = 2;
                //msg_buf[0] = CMD_FIRMWARE_UPGRADE;
                msg_buf[1] = STATUS_CMD_FAILED;
                break;

                case CMD_ENTER_PROGMODE_ISP:
                // The syntax of this command is as follows:
                // 0: Command ID 1 byte, CMD_ENTER_ PROGMODE_ISP
                // 1: timeout 1 byte, Command time-out (in ms)
                // 2: stabDelay 1 byte, Delay (in ms) used for pin stabilization
                // 3: cmdexeDelay 1 byte, Delay (in ms) in connection with the EnterProgMode command execution
                // 4: synchLoops 1 byte, Number of synchronization loops
                // 5: byteDelay 1 byte, Delay (in ms) between each byte in the EnterProgMode command.
                // 6: pollValue 1 byte, Poll value: 0x53 for AVR, 0x69 for AT89xx
                // 7: pollIndex 1 byte, Start address, received byte: 0 = no polling, 3 = AVR, 4 = AT89xx
                // cmd1 1 byte
                // cmd2 1 byte
                // cmd3 1 byte
                // cmd4 1 byte
                LED_ON;
                spi_init();
                delay_ms(msg_buf[2]); // stabDelay

                answerlen=2;
                //msg_buf[0] = CMD_ENTER_PROGMODE_ISP;
                // set default to failed:
                msg_buf[1] = STATUS_CMD_FAILED;
                //connect to the target
                i=0;
                // limit the loops:
                if (msg_buf[4]> 32){
                        msg_buf[4]=32;
                }
                if (msg_buf[5] < 3){
                        // minimum delay
                        msg_buf[5]=3;
                }
                while(i<msg_buf[4]){//synchLoops
                        wd_kick();
                        LED_ON; // blink during init
                        i++;
                        spi_mastertransmit(msg_buf[8]);//cmd1
                        delay_ms(msg_buf[5]); //byteDelay
                        spi_mastertransmit(msg_buf[9]); //cmd2
                        delay_ms(msg_buf[5]); //byteDelay
                        LED_OFF;  // blink during init
                        tmp=spi_mastertransmit(msg_buf[10]);//cmd3
                        delay_ms(msg_buf[5]); //byteDelay
                        tmp2=spi_mastertransmit(msg_buf[11]);//cmd4
                        delay_ms(msg_buf[5]); //byteDelay
                        //7=pollIndex, 6=pollValue
                        if(msg_buf[7]==3 && tmp==msg_buf[6]) {
                                msg_buf[1] = STATUS_CMD_OK;
                        }
                        //7=pollIndex, 6=pollValue
                        if(msg_buf[7]!=3 && tmp2==msg_buf[6]) {
                                msg_buf[1] = STATUS_CMD_OK;
                        }
                        if(msg_buf[7]==0) { //pollIndex
                                msg_buf[1] = STATUS_CMD_OK;
                        }
                        // causes problems with MULTI spi_clock_pulse();
                        if(msg_buf[1] == STATUS_CMD_OK)
                        {
                                LED_ON;
                                i=msg_buf[4];// end loop
                        }
                }
                break;
                
                case CMD_LEAVE_PROGMODE_ISP:
                spi_disable();
                LED_OFF;
                answerlen = 2;
                //msg_buf[0] = CMD_LEAVE_PROGMODE_ISP;
                msg_buf[1] = STATUS_CMD_OK;
                break;

                case CMD_CHIP_ERASE_ISP:
                spi_mastertransmit(msg_buf[3]);
                spi_mastertransmit(msg_buf[4]);
                spi_mastertransmit(msg_buf[5]);
                spi_mastertransmit(msg_buf[6]);
                if(msg_buf[2]==0) {
                        // pollMethod use delay
                        delay_ms(msg_buf[1]); // eraseDelay
                } else {
                        // pollMethod RDY/BSY cmd
                        ci=150; // timeout
                        while((spi_mastertransmit_32(0xF0000000)&1)&&ci){
                                ci--;
                        }
                }
                answerlen = 2;
                //msg_buf[0] = CMD_CHIP_ERASE_ISP;
                msg_buf[1] = STATUS_CMD_OK;
                break;

                case CMD_PROGRAM_EEPROM_ISP:
                addressing_is_word=0;  // address each byte
                case CMD_PROGRAM_FLASH_ISP:
                // msg_buf[0] CMD_PROGRAM_FLASH_ISP = 0x13
                // msg_buf[1] NumBytes H
                // msg_buf[2] NumBytes L
                // msg_buf[3] mode
                // msg_buf[4] delay
                // msg_buf[5] cmd1 (Load Page, Write Program Memory)
                // msg_buf[6] cmd2 (Write Program Memory Page)
                // msg_buf[7] cmd3 (Read Program Memory)
                // msg_buf[8] poll1 (value to poll)
                // msg_buf[9] poll2
                // msg_buf[n+10] Data
                poll_address=0;
		ci=150;
                // set a minimum delay
                if (msg_buf[4] < 3){
                        msg_buf[4]=3;
                }
                // set a max delay
                if (msg_buf[4] > 24){
                        msg_buf[4]=24;
                }
		saddress=address; // previous address, start address 
		nbytes = ((unsigned int)msg_buf[1])<<8;
		nbytes |= msg_buf[2];
                if (nbytes> 280){
                        // corrupted message
                        answerlen = 2;
                        msg_buf[1] = STATUS_CMD_FAILED;
                        break;
                }
                wd_kick();
                // store the original mode:
                tmp2=msg_buf[3];
                // result code
                cstatus=STATUS_CMD_OK;
                // msg_buf[3] test Word/Page Mode bit:
                if ((msg_buf[3]&1)==0){
                        // word mode
                        for(i=0;i<nbytes;i++)
                        {        
                                // The Low/High byte selection bit is
                                // bit number 3. Set high byte for uneven bytes
                                if(addressing_is_word && i&1) {
                                        // high byte
                                        spi_mastertransmit(msg_buf[5]|(1<<3));
                                } else {
                                        // low byte 
                                        spi_mastertransmit(msg_buf[5]);
                                }
                                spi_mastertransmit_16(address&0xFFFF);
                                spi_mastertransmit(msg_buf[i+10]);
                                // if the data byte is not same as poll value
                                // in that case we can do polling:
                                if(msg_buf[8]!=msg_buf[i+10]) {
                                        poll_address = address&0xFFFF;
                                        // restore the possibly modifed mode:
                                        msg_buf[3]=tmp2;
                                } else {
                                        //switch the mode to timed delay (waiting), for this word
                                        msg_buf[3]= 0x02;
                                }
                                //
                                wd_kick();
                                if (!addressing_is_word){
                                        // eeprom writing, eeprom needs more time
                                        delay_ms(1);
                                }
                                //check the different polling mode methods
                                if(msg_buf[3]& 0x04) {
                                        //data value polling
                                        tmp=msg_buf[8];
                                        ci=150; // timeout
                                        while(tmp==msg_buf[8] && ci ){
                                                // The Low/High byte selection bit is
                                                // bit number 3. Set high byte for uneven bytes
                                                // Read data:
                                                if(addressing_is_word && i&1) {
                                                        spi_mastertransmit(msg_buf[7]|(1<<3));
                                                } else {
                                                        spi_mastertransmit(msg_buf[7]);
                                                }
                                                spi_mastertransmit_16(poll_address);
                                                tmp=spi_mastertransmit(0x00);
                                                ci--;
                                        }
                                } else if(msg_buf[3]&0x08){
                                        //RDY/BSY polling
                                        ci=150; // timeout
                                        while((spi_mastertransmit_32(0xF0000000)&1)&&ci){
                                                ci--;
                                        }
                                }else{
                                        //timed delay (waiting)
                                        delay_ms(msg_buf[4]);
                                }
                                if (addressing_is_word){
                                        //increment word address only when we have an uneven byte
                                        if(i&1) address++;
                                }else{
                                        //increment address
                                        address++;
                                }
				if (ci==0){
					cstatus=STATUS_CMD_TOUT;
				}
                        }                        
                }else{
                        //page mode, all modern chips
                        for(i=0;i<nbytes;i++)
                        {
                                wd_kick();
                                // The Low/High byte selection bit is
                                // bit number 3. Set high byte for uneven bytes
                                if(addressing_is_word && i&1) {
                                        spi_mastertransmit(msg_buf[5]|(1<<3));
                                } else {
                                        spi_mastertransmit(msg_buf[5]);
                                }
                                spi_mastertransmit_16(address&0xFFFF);
                                spi_mastertransmit(msg_buf[i+10]);
                                
                                // that the data byte is not same as poll value
                                // in that case we can do polling:
                                if(msg_buf[8]!=msg_buf[i+10]) {
                                        poll_address = address&0xFFFF;
                                } else {
                                        //switch the mode to timed delay (waiting)
                                        //we must preserve bit 0x80
                                        msg_buf[3]= (msg_buf[3]&0x80)|0x10;
                                
                                }
                                if (addressing_is_word){
                                        //increment word address only when we have an uneven byte
                                        if(i&1) address++;
                                }else{
                                        address++;
                                }
                        }
                        
                        wd_kick();
                        //page mode check result:
                        //
                        // stk sets the Write page bit (7) if the page is complete
                        // and we should write it.
                        if(msg_buf[3]&0x80) {
                                spi_mastertransmit(msg_buf[6]);
                                spi_mastertransmit_16(saddress&0xFFFF);
                                spi_mastertransmit(0);
                                //
                                if (!addressing_is_word){
                                        // eeprom writing, eeprom needs more time
                                        delay_ms(1);
                                }
                                //check the different polling mode methods
                                ci=150; // timeout
                                if(msg_buf[3]&0x20 && poll_address) {
                                        //Data value polling
                                        tmp=msg_buf[8];
                                        while(tmp==msg_buf[8] && ci){
                                                // The Low/High byte selection bit is
                                                // bit number 3. Set high byte for uneven bytes
                                                // Read data:
                                                if(poll_address&1) {
                                                        spi_mastertransmit(msg_buf[7]|(1<<3));
                                                } else {
                                                        spi_mastertransmit(msg_buf[7]);
                                                }
                                                spi_mastertransmit_16(poll_address);
                                                tmp=spi_mastertransmit(0x00);
                                                ci--;
                                        }
                                        if (ci==0){
                                                cstatus=STATUS_CMD_TOUT;
                                        }
                                } else if(msg_buf[3]& 0x40){
                                        //RDY/BSY polling
                                        while((spi_mastertransmit_32(0xF0000000)&1)&&ci){
                                                ci--;
                                        }
                                        if (ci==0){
                                                cstatus=STATUS_RDY_BSY_TOUT;
                                        }
                                }else{
                                        // simple waiting
                                        delay_ms(msg_buf[4]);
                                }
                        }
                }
                answerlen = 2;
                //msg_buf[0] = CMD_PROGRAM_FLASH_ISP; or CMD_PROGRAM_EEPROM_ISP
                msg_buf[1] = cstatus;
                break;

                case CMD_READ_EEPROM_ISP:
                addressing_is_word=0;  // address each byte
                case CMD_READ_FLASH_ISP:
		// msg_buf[1] and msg_buf[2] NumBytes
		// msg_buf[3] cmd
		nbytes = ((unsigned int)msg_buf[1])<<8;
		nbytes |= msg_buf[2];
		tmp = msg_buf[3];
                // limit answer len, prevent overflow:
                if (nbytes> 280){
                        nbytes=280;
                }
                //
		for(i=0;i<nbytes;i++)
		{
                        wd_kick();
			//Select Low or High-Byte
			if(addressing_is_word && i&1) {
				spi_mastertransmit(tmp|(1<<3));
			} else {
				spi_mastertransmit(tmp);
			}
			
			spi_mastertransmit_16(address&0xFFFF);
			msg_buf[i+2] = spi_mastertransmit(0);
			
                        if (addressing_is_word){
                                //increment word address only when we have an uneven byte 
                                if(i&1) address++;
                        }else{
                                address++;
                        }
		}
		answerlen = nbytes+3;
		//msg_buf[0] = CMD_READ_FLASH_ISP; or CMD_READ_EEPROM_ISP
		msg_buf[1] = STATUS_CMD_OK;
		msg_buf[nbytes+2] = STATUS_CMD_OK;
                break;

                case CMD_PROGRAM_LOCK_ISP:
                case CMD_PROGRAM_FUSE_ISP:
                spi_mastertransmit(msg_buf[1]);
                spi_mastertransmit(msg_buf[2]);
                spi_mastertransmit(msg_buf[3]);
                spi_mastertransmit(msg_buf[4]);
                answerlen =3;
                // msg_buf[0] = CMD_PROGRAM_FUSE_ISP; or CMD_PROGRAM_LOCK_ISP
                msg_buf[1] = STATUS_CMD_OK;
                msg_buf[2] = STATUS_CMD_OK;
                break;

                case CMD_READ_OSCCAL_ISP:
                case CMD_READ_SIGNATURE_ISP:
                case CMD_READ_LOCK_ISP:
                case CMD_READ_FUSE_ISP:
		for(ci=0;ci<4;ci++){
                        tmp = spi_mastertransmit(msg_buf[ci+2]);
                        if (msg_buf[1] == (ci + 1)){
                                msg_buf[2] = tmp;
                        }
			delay_ms(5);
                }
                answerlen = 4;
                // msg_buf[0] = CMD_READ_FUSE_ISP; or CMD_READ_LOCK_ISP or ...
                msg_buf[1] = STATUS_CMD_OK;
                // msg_buf[2] is the data (fuse byte)
                msg_buf[3] = STATUS_CMD_OK;
                break;

                case CMD_SPI_MULTI:
                // 0: CMD_SPI_MULTI
                // 1: NumTx
                // 2: NumRx 
                // 3: RxStartAddr counting from zero
                // 4+: TxData (len in NumTx)
                // example: 0x1d 0x04 0x04 0x00   0x30 0x00 0x00 0x00
                tmp=msg_buf[2];
                tmp2=msg_buf[3];
                cj=0; 
                ci=0;
                for (cj=0; cj<msg_buf[1]; cj++) {
                        if (cj >= tmp2 && ci <tmp){
                                // store answer starting from msg_buf[2]
                                msg_buf[ci+2]=spi_mastertransmit(msg_buf[cj+4]);
                                ci++;
                        }else{
                                spi_mastertransmit(msg_buf[cj+4]);
                        }
			delay_ms(5);
                }
                // padd with zero:
                while(ci<tmp){
                        msg_buf[ci+2]=0;
                        ci++;
                }
                answerlen = ci+3;
                // msg_buf[0] = CMD_SPI_MULTI
                msg_buf[1] = STATUS_CMD_OK;
                // msg_buf[2...ci+1] is the data 
                msg_buf[ci+2] = STATUS_CMD_OK;
                break;

                default:
                // we should not come here
                answerlen = 2;
                msg_buf[1] = STATUS_CMD_UNKNOWN;
                break;
        }
        transmit_answer(seqnum,answerlen);
        
}

// Read a max of 2 digits from the serial line
// return value of -1 means no change (user just hit return)
signed char terminalmode_readnum(unsigned char chr_nl){
        unsigned char ch;
        unsigned char lineendcnt=1;
        unsigned char digits=2; // you can enter max 2 digits
        signed char rval=-1;
	if (chr_nl){
		// we expect \r\n as line end
		lineendcnt=2;
	}
	ch=uart_getchar(1);
	while(ch != '\r' && ch !='\n' && digits){
		if ((ch >= '0') && (ch <= '9')){
			if (rval==-1){
				rval=0;
			}
			uart_sendchar(ch); // echo number back to terminal
			rval=rval*10 + (ch  - (unsigned char)'0');
			digits--;
		}
		ch=uart_getchar(1);
	}
	// user just pressed return or enter just 1 digit
	if (ch == '\r' || ch == '\n'){
		lineendcnt--;
	}
	// get \n or \r\n after a number was entered:
	while(lineendcnt){
		ch=uart_getchar(1);
		lineendcnt--;
	}
	return(rval);
}

void terminalmode_next_line(void)
{
        uart_sendchar('\x1B');
        uart_sendchar('E');
}

void terminalmode(unsigned char chr_nl)
{
	signed char i;
	// Init terminal
	uart_sendstr_p(terminal_init);
	//
	uart_sendstr_P("AvrUsb500-1.4 terminal mode\r\n");
	uart_sendstr_P("Enter SW Version Major [");
	utoa(CONFIG_PARAM_SW_MAJOR,(char *)msg_buf, 10);
	uart_sendstr((char *)msg_buf);
	uart_sendstr_P("]: ");
	i=terminalmode_readnum(chr_nl);
	if (i >=0){
		CONFIG_PARAM_SW_MAJOR=(unsigned char)i;
	}
	terminalmode_next_line();
	uart_sendstr_P("Enter SW Version Minor [");
	utoa(CONFIG_PARAM_SW_MINOR,(char *)msg_buf, 10);
	uart_sendstr((char *)msg_buf);
	uart_sendstr_P("]: ");
	i=terminalmode_readnum(chr_nl);
	if (i >=0){
		CONFIG_PARAM_SW_MINOR=(unsigned char)i;
	}
	terminalmode_next_line();
	eeprom_write_byte(EEPROM_MINOR, CONFIG_PARAM_SW_MINOR);
	eeprom_write_byte(EEPROM_MAJOR, CONFIG_PARAM_SW_MAJOR);
	eeprom_write_byte(EEPROM_MAGIC, 20);// magic number=data is valid
	uart_sendstr_P("\r\nOK, my SW version is now: ");
	utoa(CONFIG_PARAM_SW_MAJOR,(char *)msg_buf, 10);
	uart_sendstr((char *)msg_buf);
	uart_sendchar('.');
	if (CONFIG_PARAM_SW_MINOR < 10){
		uart_sendchar('0');
	}
	utoa(CONFIG_PARAM_SW_MINOR,(char *)msg_buf, 10);
	uart_sendstr((char *)msg_buf);
	uart_sendstr_P("\r\n");
	uart_sendstr_P("Ready. Just close the terminal. No reset needed.\r\n");
}

int main(void)
{
        unsigned char ch;
        unsigned char prev_ch=0;
        unsigned char chr_nl=0;
        unsigned char msgparsestate;
        unsigned char cksum=0;
        unsigned char seqnum=0;
        int msglen=0;
        int i=0;
        uart_init();
        wd_init();
        LED_INIT;
        LED_OFF;
        sei();
        msgparsestate=MSG_IDLE;
	// default values:
	CONFIG_PARAM_SW_MINOR=D_CONFIG_PARAM_SW_MINOR;
	CONFIG_PARAM_SW_MAJOR=D_CONFIG_PARAM_SW_MAJOR;
        if (eeprom_read_byte((uint8_t *)EEPROM_MAGIC) == 20){
                // ok magic number matches accept values
                CONFIG_PARAM_SW_MINOR=eeprom_read_byte(EEPROM_MINOR);
                CONFIG_PARAM_SW_MAJOR=eeprom_read_byte(EEPROM_MAJOR);
        }
        while(1){
                if (msgparsestate==MSG_IDLE){
                        ch=uart_getchar(1);
                }else{
                        ch=uart_getchar(0);
                }
                // parse message according to appl. note AVR068 table 3-1:
                if (msgparsestate==MSG_IDLE && ch == MESSAGE_START){
                        msgparsestate=MSG_WAIT_SEQNUM;
                        cksum = ch^0;
                        continue;
                }
		// The special avrusb500 terminal mode.
		// Just connect a serial terminal and press enter twice.
		// Both Windows and Linux send normally \r (=0xd) as the
		// only line end character. It is however possible to configure
		// \r\n as line end in some serial terminals. Therefore we
		// must handle it.
                if (msgparsestate==MSG_IDLE && (ch == '\r'||ch == '\n')){
			i++;
			if(chr_nl ==0 && ch=='\n' && prev_ch== '\r'){
				// terminal sends \r\n for new line
				chr_nl=1;
			}
			prev_ch=ch;
			if (chr_nl){
				// wait for \r\n \r\n
				if (i==4){
					terminalmode(1);
					i=0;
				}
			}else{
				// Linux wait for \n\n
				if (i==2){
					terminalmode(0);
					i=0;
				}
			}
			continue;
		}
                if (msgparsestate==MSG_WAIT_SEQNUM){
                        seqnum=ch;
                        cksum^=ch;
                        msgparsestate=MSG_WAIT_SIZE1;
                        continue;
                }
                if (msgparsestate==MSG_WAIT_SIZE1){
                        cksum^=ch;
                        msglen=ch<<8;
                        msgparsestate=MSG_WAIT_SIZE2;
                        continue;
                }
                if (msgparsestate==MSG_WAIT_SIZE2){
                        cksum^=ch;
                        msglen|=ch;
                        msgparsestate=MSG_WAIT_TOKEN;
                        continue;
                }
                if (msgparsestate==MSG_WAIT_TOKEN){
                        cksum^=ch;
                        if (ch==TOKEN){
                                msgparsestate=MSG_WAIT_MSG;
                                i=0;
                        }else{
                                msgparsestate=MSG_IDLE;
                        }
                        continue;
                }
                if (msgparsestate==MSG_WAIT_MSG && i<msglen && i<280){
                        cksum^=ch;
                        msg_buf[i]=ch;
                        i++;
			wdt_reset(); //wd_kick();
                        if (i==msglen){
                                msgparsestate=MSG_WAIT_CKSUM;
                        }
                        continue;
                }
                if (msgparsestate==MSG_WAIT_CKSUM){
                        if (ch==cksum && msglen > 0){
                                // message correct, process it
                                wdt_reset(); //wd_kick();
                                programcmd(seqnum);
                        }else{
                                msg_buf[0] = ANSWER_CKSUM_ERROR;
                                msg_buf[1] = STATUS_CKSUM_ERROR;
                                transmit_answer(seqnum,2);
                        }
                        // no continue here, set state=MSG_IDLE
                }
                msgparsestate=MSG_IDLE;
                msglen=0;
                seqnum=0;
		prev_ch=0;
                i=0;
        }
	return(0);
}

