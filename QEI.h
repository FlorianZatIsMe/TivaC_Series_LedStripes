
#define REV_EDGES 0x000003C0	// Number of encoder ticks to perform one full revolution of the motor - 1 (959)
#define POS_ZERO	0x10000000	// When the counter's value is POS_ZERO its actual value is 0, in other words POS_ZERO is the value of the counter once a revolution is complete
#define QEIMAXPOS	0xFFFFFFFF
#define QEILOAD_R	1000000			// Timer to calculate speed to 12.5ms at 80MHz

//------------QEI0------------
// Initialize the PORT D for QEI0 (Quadrature Encoder Interface)
// ...
// Input: none
// Output: none
void QEI0_Init(void);

//------------QEI1------------
// Initialize the PORT C for QEI1 (Quadrature Encoder Interface)
// ...
// Input: none
// Output: none
void QEI1_Init(void);

//------------QEI0------------
// Update the revolution counter of the motor 1
// ...
// Input: none
// Output: none
void update_motor1_revCount(void);

//------------QEI1------------
// Update the revolution counter of the motor 2
// ...
// Input: none
// Output: none
void update_motor1_revCount(void);


