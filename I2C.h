#define I2C_START 							0x02
#define I2C_DATA 								0x01
#define I2C_STOP	 							0x04

//I2C0 DEFINES - REGISTERS, Base address: 0x4002.0000
//---------------------------------------------------
//I2C Master
#define I2C0_I2CMSA_R      			(*((volatile unsigned long *)0x40020000))
#define I2C0_I2CMCS_R      			(*((volatile unsigned long *)0x40020004))
#define I2C0_I2CMDR_R      			(*((volatile unsigned long *)0x40020008))
#define I2C0_I2CMTPR_R      		(*((volatile unsigned long *)0x4002000C))
#define I2C0_I2CMIMR_R      		(*((volatile unsigned long *)0x40020010))
#define I2C0_I2CMRIS_R      		(*((volatile unsigned long *)0x40020014))
#define I2C0_I2CMMIS_R      		(*((volatile unsigned long *)0x40020018))
#define I2C0_I2CMICR_R      		(*((volatile unsigned long *)0x4002001C))
#define I2C0_I2CMCR_R      			(*((volatile unsigned long *)0x40020020))
#define I2C0_I2CMCLKOCNT_R      (*((volatile unsigned long *)0x40020024))
#define I2C0_I2CMBMON_R      		(*((volatile unsigned long *)0x4002002C))
#define I2C0_I2CMCR2_R      		(*((volatile unsigned long *)0x40020038))

//I2C Slave
#define I2C0_I2CSOAR_R      		(*((volatile unsigned long *)0x40020800))
#define I2C0_I2CSCSR_R      		(*((volatile unsigned long *)0x40020804))
#define I2C0_I2CSDR_R      			(*((volatile unsigned long *)0x40020808))
#define I2C0_I2CSIMR_R      		(*((volatile unsigned long *)0x4002080C))
#define I2C0_I2CSRIS_R      		(*((volatile unsigned long *)0x40020810))
#define I2C0_I2CSMIS_R      		(*((volatile unsigned long *)0x40020814))
#define I2C0_I2CSICR_R      		(*((volatile unsigned long *)0x40020818))
#define I2C0_I2CSOAR2_R      		(*((volatile unsigned long *)0x4002081C))
#define I2C0_I2CSACKCTL_R      	(*((volatile unsigned long *)0x40020820))

//I2C Status and Control
#define I2C0_I2CPP_R      			(*((volatile unsigned long *)0x40020FC0))
#define I2C0_I2CPC_R      			(*((volatile unsigned long *)0x40020FC4))

//I2C1 DEFINES - REGISTERS, Base address: 0x4002.1000
//---------------------------------------------------
//I2C Master
#define I2C1_I2CMSA_R      			(*((volatile unsigned long *)0x40021000))
#define I2C1_I2CMCS_R      			(*((volatile unsigned long *)0x40021004))
#define I2C1_I2CMDR_R      			(*((volatile unsigned long *)0x40021008))
#define I2C1_I2CMTPR_R      		(*((volatile unsigned long *)0x4002100C))
#define I2C1_I2CMIMR_R      		(*((volatile unsigned long *)0x40021010))
#define I2C1_I2CMRIS_R      		(*((volatile unsigned long *)0x40021014))
#define I2C1_I2CMMIS_R      		(*((volatile unsigned long *)0x40021018))
#define I2C1_I2CMICR_R      		(*((volatile unsigned long *)0x4002101C))
#define I2C1_I2CMCR_R      			(*((volatile unsigned long *)0x40021020))
#define I2C1_I2CMCLKOCNT_R      (*((volatile unsigned long *)0x40021024))
#define I2C1_I2CMBMON_R      		(*((volatile unsigned long *)0x4002102C))
#define I2C1_I2CMCR2_R      		(*((volatile unsigned long *)0x40021038))

//I2C Slave
#define I2C1_I2CSOAR_R      		(*((volatile unsigned long *)0x40021800))
#define I2C1_I2CSCSR_R      		(*((volatile unsigned long *)0x40021804))
#define I2C1_I2CSDR_R      			(*((volatile unsigned long *)0x40021808))
#define I2C1_I2CSIMR_R      		(*((volatile unsigned long *)0x4002180C))
#define I2C1_I2CSRIS_R      		(*((volatile unsigned long *)0x40021810))
#define I2C1_I2CSMIS_R      		(*((volatile unsigned long *)0x40021814))
#define I2C1_I2CSICR_R      		(*((volatile unsigned long *)0x40021818))
#define I2C1_I2CSOAR2_R     	 	(*((volatile unsigned long *)0x4002181C))
#define I2C1_I2CSACKCTL_R      	(*((volatile unsigned long *)0x40021820))

//I2C Status and Control
#define I2C1_I2CPP_R      			(*((volatile unsigned long *)0x40021FC0))
#define I2C1_I2CPC_R      			(*((volatile unsigned long *)0x40021FC4))

//I2C2 DEFINES - REGISTERS, Base address: 0x4002.2000
//---------------------------------------------------
//I2C Master
#define I2C2_I2CMSA_R      			(*((volatile unsigned long *)0x40022000))
#define I2C2_I2CMCS_R      			(*((volatile unsigned long *)0x40022004))
#define I2C2_I2CMDR_R      			(*((volatile unsigned long *)0x40022008))
#define I2C2_I2CMTPR_R      		(*((volatile unsigned long *)0x4002200C))
#define I2C2_I2CMIMR_R      		(*((volatile unsigned long *)0x40022010))
#define I2C2_I2CMRIS_R      		(*((volatile unsigned long *)0x40022014))
#define I2C2_I2CMMIS_R      		(*((volatile unsigned long *)0x40022018))
#define I2C2_I2CMICR_R      		(*((volatile unsigned long *)0x4002201C))
#define I2C2_I2CMCR_R      			(*((volatile unsigned long *)0x40022020))
#define I2C2_I2CMCLKOCNT_R      (*((volatile unsigned long *)0x40022024))
#define I2C2_I2CMBMON_R      		(*((volatile unsigned long *)0x4002202C))
#define I2C2_I2CMCR2_R      		(*((volatile unsigned long *)0x40022038))

//I2C Slave
#define I2C2_I2CSOAR_R      		(*((volatile unsigned long *)0x40022800))
#define I2C2_I2CSCSR_R      		(*((volatile unsigned long *)0x40022804))
#define I2C2_I2CSDR_R      			(*((volatile unsigned long *)0x40022808))
#define I2C2_I2CSIMR_R      		(*((volatile unsigned long *)0x4002280C))
#define I2C2_I2CSRIS_R      		(*((volatile unsigned long *)0x40022810))
#define I2C2_I2CSMIS_R      		(*((volatile unsigned long *)0x40022814))
#define I2C2_I2CSICR_R      		(*((volatile unsigned long *)0x40022818))
#define I2C2_I2CSOAR2_R      		(*((volatile unsigned long *)0x4002281C))
#define I2C2_I2CSACKCTL_R      	(*((volatile unsigned long *)0x40022820))

//I2C Status and Control
#define I2C2_I2CPP_R      			(*((volatile unsigned long *)0x40022FC0))
#define I2C2_I2CPC_R      			(*((volatile unsigned long *)0x40022FC4))

//I2C3 DEFINES - REGISTERS, Base address: 0x4002.3000
//---------------------------------------------------
//I2C Master
#define I2C3_I2CMSA_R      			(*((volatile unsigned long *)0x40023000))
#define I2C3_I2CMCS_R      			(*((volatile unsigned long *)0x40023004))
#define I2C3_I2CMDR_R      			(*((volatile unsigned long *)0x40023008))
#define I2C3_I2CMTPR_R      		(*((volatile unsigned long *)0x4002300C))
#define I2C3_I2CMIMR_R      		(*((volatile unsigned long *)0x40023010))
#define I2C3_I2CMRIS_R      		(*((volatile unsigned long *)0x40023014))
#define I2C3_I2CMMIS_R      		(*((volatile unsigned long *)0x40023018))
#define I2C3_I2CMICR_R      		(*((volatile unsigned long *)0x4002301C))
#define I2C3_I2CMCR_R      			(*((volatile unsigned long *)0x40023020))
#define I2C3_I2CMCLKOCNT_R      (*((volatile unsigned long *)0x40023024))
#define I2C3_I2CMBMON_R      		(*((volatile unsigned long *)0x4002302C))
#define I2C3_I2CMCR2_R      		(*((volatile unsigned long *)0x40023038))

//I2C Slave
#define I2C3_I2CSOAR_R      		(*((volatile unsigned long *)0x40023800))
#define I2C3_I2CSCSR_R      		(*((volatile unsigned long *)0x40023804))
#define I2C3_I2CSDR_R      			(*((volatile unsigned long *)0x40023808))
#define I2C3_I2CSIMR_R      		(*((volatile unsigned long *)0x4002380C))
#define I2C3_I2CSRIS_R      		(*((volatile unsigned long *)0x40023810))
#define I2C3_I2CSMIS_R      		(*((volatile unsigned long *)0x40023814))
#define I2C3_I2CSICR_R      		(*((volatile unsigned long *)0x40023818))
#define I2C3_I2CSOAR2_R      		(*((volatile unsigned long *)0x4002381C))
#define I2C3_I2CSACKCTL_R      	(*((volatile unsigned long *)0x40023820))

//I2C Status and Control
#define I2C3_I2CPP_R      			(*((volatile unsigned long *)0x40023FC0))
#define I2C3_I2CPC_R      			(*((volatile unsigned long *)0x40023FC4))

//------------I2C0------------
// 
// 
// Input: none
// Output: none
void I2C0_Init(void);
void I2C0_enableSlave(void);
void I2C0_disableSlave(void);

