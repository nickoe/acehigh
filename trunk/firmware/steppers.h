/*
 * $Id$
 */


#ifndef __STEPPERS_H__
#define __STEPPERS_H__

/* 
 * initialize steppers
 */
void steppers_init();

/* 
 * move the cursor, units are mm and mm/s
 *
 * returns when the movement has started
 */
void steppers_move(int x, int y, double v);

/* 
 * step with the cursor, units are steps and steps/s 
 *
 * this function does not do any scaling of steps to fit the metric
 * scala, so it is useful for calibration
 *
 * returns when the movement has started
 */
//void steppers_step(int x, int y, double v);


#endif /* __STEPPERS_H__ */
