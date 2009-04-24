/*
 * $Id$
 */

#ifndef __MOTOR_H__
#define __MOTOR_H__


#include <stdint.h>


/* definitioner til motorstyringskredsen */
#define MCC_DDR        DDRA
#define MCC_PORT       PORTA
#define MCC_HALFFULL   0
#define MCC_DECAY      1
#define MCC_X_CCW      2
#define MCC_ENABLE     3
#define MCC_X_CLK      4
#define MCC_Y_CLK      5
#define MCC_RESET      6
#define MCC_Y_CCW      7


/* Højest mulige hastighed i gu/clk */
/* højeste teoretiske hastighed er 0.83 */
#define MAXSPEED 0.45

/* Initialiserer motorerne, skal kaldes inden de kan bruges */
void Motor_Init(void);

/* Flytter motoren x til højre og y ned med farten v */
void Motor_Move(int32_t x, int32_t y, double v);

void Motor_MoveTo(uint32_t x, uint32_t y, double v);

/* Løfter tegnehovedet */
void Motor_Lift(void);

/* Sænker tegnehovedet */
void Motor_Lower(void);

#endif /* __MOTOR_H__ */
