/*
 * WPCE775x.h
 *	
 *	Author : huangwei <huangw@lemote.com>
 *	Date   : 2010-03-11
 */

#include <linux/io.h>
#include "include/shm.h"

#ifdef	LOONGSON2F_3GNB
/* delay function */
extern void delay(int microseconds);
/* version array */
extern unsigned char *get_ecver(void);

/* read and write operation */
/* PM (Power Management) Channels Register access.
 * channel 1: legacy 62h, 66h; channel 2: legacy 68h, 6Ch; channel 3: legacy 6Ah, 6Eh
 * other, 8042 KBD standard interface: port 60h, 64h;
 */
#undef	read_port
#undef	write_port
#define	read_port(x)	 (*(volatile unsigned char *)(MIPS_IO_BASE | x))
#define	write_port(x, y) (*(volatile unsigned char *)(MIPS_IO_BASE | x) = y)	

/**************************************************************/

/* base address for io access */
#undef	MIPS_IO_BASE
#define	MIPS_IO_BASE	(0xbfd00000)
#define SIO_INDEX_PORT	0x2E
#define SIO_DATA_PORT	0x2F

/* EC access port for sci communication */
#define	EC_CMD_PORT			0x66
#define	EC_STS_PORT			0x66
#define	EC_DAT_PORT			0x62

/**************************************************************/

/* ACPI OEM commands */

/* reset the machine auto-clear : rd/wr */
#define CMD_RESET           0x4E
#define BIT_RESET_ON        1
/* read version number: rd */
#define CMD_RD_VER			0x4F
#define VER_START_INDEX		0
#define	OEMVER_MAX_SIZE		36 
 
/* ACPI legacy commands */
#define CMD_READ_EC 	  	0x80	/* Read Embedded Controller command. */
#define CMD_WRITE_EC  		0x81	/* Write Embedded Controller command. */
#define	CMD_QUERY			0x84	/* Query Embedded Controller command, for get SCI event number. */

/* Read temperature & fan index information */
#define INDEX_TEMPERATURE_VALUE         0x1B    /* current CPU temperature value */
#define BIT_TEMPERATURE_PN		    (1 << 7)    /* current CPU temperature value positive or negative */
#define TEMPERATURE_VALUE_MASK			0x7F
#define INDEX_FAN_SPEED_HIGH            0x09    /* fan speed high byte */
#define INDEX_FAN_SPEED_LOW             0x08    /* fan speed low byte */
 
/* Read battery index information */
#define INDEX_BATTERY_VOL_LOW           0x90    /* Battery Voltage Low byte. */
#define INDEX_BATTERY_VOL_HIGH          0x91    /* Battery Voltage High byte. */
#define INDEX_BATTERY_CAPACITY          0x92    /* Battery Capacity byte. */
#define INDEX_BATTERY_TEMP_LOW          0x93    /* Battery Temperature Low byte. */
#define INDEX_BATTERY_TEMP_HIGH         0x94    /* Battery Temperature High byte. */
#define INDEX_BATTERY_FLAG              0x95    /* Battery Flags byte. */
#define BIT_BATTERY_CURRENT_PN          7       /* Battery current sign is positive or negative */
#define INDEX_BATTERY_AI_LOW            0x96    /* Battery Current Low byte. */
#define INDEX_BATTERY_AI_HIGH           0x97    /* Battery Current High byte. */

/* Read Current Power Status */
#define INDEX_POWER_STATUS              0xA2
#define BIT_POWER_BATPRES			(1 << 6)	/* Battery present */

/* EC_SC input */
#define   EC_SMI_EVT    (1 << 6)    // 1: SMI event pending
#define   EC_SCI_EVT    (1 << 5)    // 1: SCI event pending
#define   EC_BURST      (1 << 4)    // controller is in burst mode
#define   EC_CMD        (1 << 3)    // 1: byte in data register is command
                                    // 0: byte in data register is data
#define   EC_IBF        (1 << 1)    // 1: input buffer full (data ready for ec)
#define   EC_OBF        (1 << 0)    // 1: output buffer full (data ready for host)
									
#define	RD_REG_DELAY		30000
#define EC_CMD_TIMEOUT      0x1000  // command checkout timeout including cmd to port or state flag check
#define EC_SEND_TIMEOUT 	0x7ff

/**************************************************************/

/* 07h - 2Fh: SuperI/O Control and Configuration Registers */
/* Standard Control Registers */
#define REG_SLDN			0x7		/* Logical Device Number */
#define SIO_SID             0x20        // Super IO identification
#define REG_SID				0x20	/* SuperI/O ID */
#define REG_SIOCF1			0x21	/* SuperI/O Configuration 1 */
#define CF1_GLOBEN		(1 << 0)	/* Global Device Enable. */
#define REG_SIOCF5			0x25    /* SuperI/O Configuration 5 */
#define CF5_SMIIRQ2_EN	(1 << 4) /* SMI to IRQ2 Enable. */
#define REG_SIOCF6			0x26    /* SuperI/O Configuration 6 */
#define REG_SRID			0x27	/* SuperI/O Revision ID */
#define REG_SIOGPS			0x28	/* SuperI/O General-Purpose Scratch */
#define REG_SIOCF9   		0x29    /* SuperI/O Configuration 9 */
#define REG_SIOCFD   		0x2D    /* SuperI/O Configuration D */

/* 30h - FFh: Logical Device Control and Configuration Registers -
 * one per Logical Device(some are optional) */
/* Logical Device Activate Register */
#define REG_ACTIVATE		0x30 	/* Logical Device Control (Activate) */
/* I/O Space Configuration Registers */
#define REG_BADDR0_H		0x60	/* I/O Base Address Descriptor 0 Bits 15-8 */
#define REG_BADDR0_L		0x61	/* I/O Base Address Descriptor 0 Bits 7-0 */
#define REG_BADDR1_H		0x62	/* I/O Base Address Descriptor 1 Bits 15-8 */
#define REG_BADDR1_L		0x63	/* I/O Base Address Descriptor 1 Bits 7-0 */
/* Interrupt Configuration Registers */
#define REG_INT_CONFIG  	0x70	/* Interrupt Number and Wake-Up on IRQ Enable */
#define REG_IRQSEL			0x71	/* IRQ Type Select */
/* DMA Configuration Registers */
#define REG_DMA_CHNSEL0		0x74	/* DMA Channel Select 0 */
#define REG_DMA_CHNSEL1		0x75	/* DMA Channel Select 1 */
/* F0h - FFh: Specific Logical Device Configuration */
/* Shared Memory Configuration Registers */
#define SHM_CFG				0xF0	/* Shared Memory Configuration register. */
#define WIN_CFG				0xF1	/* Shared Access Windows Configuration register. */
#define SHAW1BA_0			0xF4	/* Shared Access Window 1, Base Address 0 register. */
#define SHAW1BA_1			0xF5	/* Shared Access Window 1, Base Address 1 register. */
#define SHAW1BA_2			0xF6	/* Shared Access Window 1, Base Address 2 register. */
#define SHAW1BA_3			0xF7	/* Shared Access Window 1, Base Address 3 register. */
#define SHAW2BA_0			0xF8	/* Shared Access Window 2, Base Address 0 register. */
#define SHAW2BA_1			0xF9	/* Shared Access Window 2, Base Address 1 register. */
#define SHAW2BA_2			0xFA	/* Shared Access Window 2, Base Address 2 register. */
#define SHAW2BA_3			0xFB	/* Shared Access Window 2, Base Address 3 register. */

// Shared Memory Registers' bits
#define SHW_FWH_ID_POS      4
#define FLASH_ACC_EN        0x4
#define SHWIN_ACC_FWH       0x40
#define BIOS_LPC_EN         0x1
#define BIOS_FWH_EN         0x8

#define FWIN1_SIZE_MASK     0xF
#define FWIN1_SIZE_512_KB   0x9         // In prototype, for FWH this is actually only 64 Kbyte
#define FWIN1_SIZE_1_MB     0xA         // In prototype, for FWH this is actually only 64 Kbyte
#define FWIN1_SIZE_2_MB     0xB         // In prototype, for FWH this is actually only 128 Kbyte
#define FWIN1_SIZE_4_MB     0xC         // In prototype, for FWH this is actually only 256 Kbyte

/* Logical Device Number (LDN) Assignments */
#define LDN_MSWC            0x4		/* Mobile System Wake-Up Control (MSWC) */
#define LDN_MOUSE			0x5 	/* Keyboard and Mouse Controller (KBC) - Mouse Interface */
#define LDN_KBD    			0x6 	/* Keyboard and Mouse Controller (KBC) - Keyboard Interface */
#define LDN_HGPIO           0x7 	/*  */
#define LDN_SHM             0xF 	/* Shared Memory (SHM) */
#define LDN_PM1             0x11	/* Power Management I/F Channel 1 (PM1) */
#define LDN_PM2             0x12	/* Power Management I/F Channel 2 (PM2) */
#define LDN_PM3             0x17	/* Power Management I/F Channel 3 (PM3) */
#define DOCKING_LPC_LDN     0x19

/* SuperI/O Values */
#define SID_WPCE775L		0xFC	/* Identity Number of the device family */
#define CHIPID_WPCE775L	(0xA << 5)	/* Chip ID. Identifies a specific device of a family. */
 
/* Logical Device values */
#define ACTIVATE_EN         0x1

// Memory Map definitions
// Device memory
#define MAX_FLASH_CAPACITY  (1 * 1024 * 1024)
#define	EC_ROM_MAX_SIZE		0xFFFF

// PC memory
#define WCB_BASE_ADDR 		0xBBF00000
#define FLASH_WIN_BASE_ADDR	0xBBE00000
#define RDBK_STAT_VAL_ADDR 	0xBBF00008

// Firmware Update Protocol definitions
/* Semaphore bits */
#define SHAW2_SEM_EXE           0x1
#define SHAW2_SEM_ERR           0x40
#define SHAW2_SEM_RDY           0x80

/* Command buffer size is 16 bytes - maximum data size is 8 bytes */
#define WCB_MAX_DATA             8
#define WCB_SIZE_ERASE_CMD       5 // 1 command byte, 4 address bytes
#define WCB_SIZE_READ_IDS_CMD    1
#define WCB_SIZE_READ_STS_CMD    1
#define WCB_SIZE_ENTER_CMD       5 // 1 command byte, 4 code bytes
#define WCB_SIZE_EXIT_CMD        1
#define WCB_SIZE_ADDRESS_SET_CMD 5
#define WCB_SIZE_BYTE_CMD        2
#define WCB_SIZE_WORD_CMD        (WCB_SIZE_BYTE_CMD + 1)  
#define WCB_SIZE_DWORD_CMD       (WCB_SIZE_WORD_CMD + 2)
#define WCB_SIZE_LONGLONG_CMD    (WCB_SIZE_DWORD_CMD + 4)
#define WCB_SIZE_GENERIC_CMD     8   
#define WCB_SIZE_SET_WINDOW      9 // 1 command byte, 8 code bytes

/* Command buffer offsets */
#define OFFSET_SEMAPHORE        0
#define OFFSET_COMMAND          3
#define OFFSET_ADDRESS          4
#define OFFSET_DATA             4    // Commands have either address or data
#define OFFSET_DATA_GENERIC     8    // Generic commands have both address and data

/* WCB Commands */
#define FLASH_COMMANDS_INIT_OP  0x5A
#define WCB_ENTER_CODE          0xBECDAA55
#define ENTER_OP                0x10
#define EXIT_OP                 0x20
#define RESET_EC_OP             0x21
#define GOTO_BOOT_BLOCK_OP      0x22
#define READ_STSREG_OP          0x30
#define WRITE_STSREG_OP         0x31
#define PROGRAM_BYTE_OP         0x32
#define ERASE_OP                0x80
#define SECTOR_ERASE_OP         0x82
#define ADDRESS_SET_OP          0xA0
#define PROGRAM_OP              0xB0
#define READ_IDS_OP             0xC0
#define GENERIC_OP              0xD0
#define SET_WINDOW_OP           0xC5
#define READ_DATA_OP            0xE0

#define DEV_SIZE_UNIT           0x20000 // 128 Kb
#define PROGRAM_FLASH_BADDR		0x20000	// to program flash base address

#define EC_ROM_PRODUCT_ID_SPANSION	0x01
#define EC_ROM_PRODUCT_ID_MXIC		0xC2
#define EC_ROM_PRODUCT_ID_AMIC		0x37
#define EC_ROM_PRODUCT_ID_EONIC		0x1C
#define EC_ROM_PRODUCT_ID_WINBOND	0xEF	// Winbond W25x80

// Write Command Buffer (WCB) commands structure
#pragma pack(1)
typedef struct
{
    unsigned char	Command;			// Byte  3
    union
    {
        FLASH_device_commands_t InitCommands;
        unsigned long   EnterCode;  	// Bytes 4-7 For Flash Update "Unlock" code
        unsigned long	Address;    	// Bytes 4-7 For Erase and Set Address
        unsigned char	Byte;			// Byte  4
        unsigned short	Word;			// Bytes 4-5
        unsigned long	DWord;			// Bytes 4-7
        struct
        {
            unsigned long DWord1;   	// Bytes 4-7
            unsigned long DWord2;   	// Bytes 8-11
        } EightBytes;
        struct
        {
            unsigned long DWAddress;	// Bytes 4-7
            unsigned long DWData;   	// Bytes 8-11
			unsigned char BFlashCmd;	// Bytes 12
			unsigned char BHasAddr;		// Bytes 13
			unsigned char BNumOfData;	// Bytes 14
			unsigned char BWriteTrans;	// Bytes 15
        } GenericOPBytes;
    } Param;
} WCB_struct;
#pragma pack()

// Possible protocol termination options
typedef enum
{
    WCB_EXIT_NORMAL = 0,
    WCB_EXIT_RESET_EC,
    WCB_EXIT_GOTO_BOOT_BLOCK,
    WCB_EXIT_LAST
} WCB_exit_t;

/* Used standard Control Registers to access WPCE775x resource by superio index/data port. */
static inline void wrsio(unsigned char reg, unsigned char data)
{
	delay(10);
	*( (volatile unsigned char *)(MIPS_IO_BASE | SIO_INDEX_PORT) ) = reg;
	*( (volatile unsigned char *)(MIPS_IO_BASE | SIO_DATA_PORT) ) = data;
}

static inline unsigned char rdsio(unsigned char reg)
{
	delay(10);
	*( (volatile unsigned char *)(MIPS_IO_BASE | SIO_INDEX_PORT) ) = reg;
	return (*( (volatile unsigned char *)(MIPS_IO_BASE | SIO_DATA_PORT) ));
}

static inline void PcIoWriteB(unsigned char port, unsigned char reg)
{
	delay(10);
	*( (volatile unsigned char *)(MIPS_IO_BASE | port) ) = reg;
}

static inline unsigned char PcIoReadB(unsigned char port)
{
	delay(10);
	return (*( (volatile unsigned char *)(MIPS_IO_BASE | port) ));
}

/****************************************************************************** 
 * Function: PcMemReadB 
 * Purpose:  Read one byte from PC linear memory 
 * Params:   Address - the physical address in the PC to read from 
 * Returns:  the value read
 ******************************************************************************/
static inline unsigned char PcMemReadB(unsigned long Address) 
{                
    return *(unsigned char *)Address;
}         

static inline void wrwcb(u32 addr, unsigned char data)
{
	delay(10);
	*( (volatile unsigned char *) addr ) = data;
}

static inline unsigned char rdwcb(u32 addr)
{
	delay(10);
	return (*((volatile unsigned char *) addr));
}

/* Access WPCE775x LDN register by superio index/data port. */
static inline void wrldn(unsigned char ldn_bank, unsigned char index, unsigned char data)
{
	delay(10);
	*( (volatile unsigned char *)(MIPS_IO_BASE | SIO_INDEX_PORT) ) = REG_SLDN;
	*( (volatile unsigned char *)(MIPS_IO_BASE | SIO_DATA_PORT) ) = ldn_bank;
	*( (volatile unsigned char *)(MIPS_IO_BASE | SIO_INDEX_PORT) ) = index;
	*( (volatile unsigned char *)(MIPS_IO_BASE | SIO_DATA_PORT) ) = data;
}

static inline unsigned char rdldn(unsigned char ldn_bank, unsigned char index)
{
	delay(10);
	*( (volatile unsigned char *)(MIPS_IO_BASE | SIO_INDEX_PORT) ) = REG_SLDN;
	*( (volatile unsigned char *)(MIPS_IO_BASE | SIO_DATA_PORT) ) = ldn_bank;
	*( (volatile unsigned char *)(MIPS_IO_BASE | SIO_INDEX_PORT) ) = index;
	return (*( (volatile unsigned char *)(MIPS_IO_BASE | SIO_DATA_PORT) ));
}

/*******************************************************************/

static inline int send_ec_command(unsigned char command)
{
	int timeout;

	timeout = EC_SEND_TIMEOUT;
	while ((read_port(EC_STS_PORT) & EC_IBF) && --timeout) {
		delay(10);
	}
	if (!timeout) {
		printf("Timeout while sending command 0x%02x to EC!\n",	command);
	}

	write_port(EC_CMD_PORT, command);
	return 0;
}

static inline int send_ec_data(unsigned char data)
{
	int timeout;

	timeout = EC_SEND_TIMEOUT;
	while ((read_port(EC_STS_PORT) & EC_IBF) && --timeout) {    // wait for IBF = 0
		delay(10);
	}
	if (!timeout) {
		printf("Timeout while sending data 0x%02x to EC!\n", data);
	}

	write_port(EC_DAT_PORT, data);

	return 0;
}

static inline int send_ec_data_nowait(unsigned char data)
{
	write_port(EC_DAT_PORT, data);

	return 0;
}

static inline unsigned char recv_ec_data(void)
{
	int timeout;
	unsigned char data;

	timeout = EC_SEND_TIMEOUT;
	while (--timeout) {     // Wait for OBF = 1
		if (read_port(EC_STS_PORT) & EC_OBF) {
			break;
		}
		delay(10);
	}
	if (!timeout) {
		printf("\nTimeout while receiving data from EC!\n");
	}

	delay(RD_REG_DELAY);
	data = read_port(EC_DAT_PORT);

	return data;
}

static inline unsigned char ec_read(unsigned char command, unsigned char index)
{
    send_ec_command(command);
    send_ec_data(index);

    return recv_ec_data();
}

static inline unsigned char ec_rd_noindex(unsigned char command)
{
    send_ec_command(command);

    return recv_ec_data();
}

static inline int ec_write(unsigned char command, unsigned char index, unsigned char data)
{
    send_ec_command(command);
    send_ec_data(index);

    return send_ec_data(data);
}

static inline int ec_wr_noindex(unsigned char command, unsigned char data)
{
    send_ec_command(command);

    return send_ec_data(data);
}

/*
 * ec_query_seq
 * this function is used for ec command writing and the corresponding status query 
 */
static inline int ec_query_seq(unsigned char cmd)
{
	int timeout;
	unsigned char status;
	int ret = 0;

	/* Send Query Command. */
	send_ec_command(cmd);

	/* check if the command is received by ec */
	timeout = EC_CMD_TIMEOUT;
	status = read_port(EC_STS_PORT);
	while(timeout--){
		if(status & EC_IBF){
			status = read_port(EC_STS_PORT);
			delay(RD_REG_DELAY);
			continue;
		}
		break;
	}
	
	if(timeout <= 0){
		printf("EC QUERY SEQ : deadable error : timeout...\n");
		ret = -1;
	}

	return ret;
}

#endif	// end ifdef LOONGSON2F_3GNB