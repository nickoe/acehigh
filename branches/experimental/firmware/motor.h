#ifndef __MOTORCTRL_H__
#define __MOTORCTRL_H__

/* Højest mulige hastighed, skal kalibreres */
#define MAXSPEED 2.5

/* Initialiserer motorerne, skal kaldes inden de kan bruges */
void Motor_Init(void);

/* Flytter motoren x til højre og y ned med farten v */
void Motor_Move(int32_t x, int32_t y, double v);

#endif /* __MOTORCTRL_H__ */
