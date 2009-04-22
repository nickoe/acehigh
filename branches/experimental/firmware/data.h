/*
 * Data feeder implementing SD card reading/writing
 *
 * Copyright (C) 2009  Kristian Kjærgaard
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * $Id$
 */


#ifndef __DATA_H__
#define __DATA_H__


#include <stdint.h>


#define PARAM_SIZE 12


/* Initialiserer dataføderen, skal kaldes inden den kan bruges */
uint8_t Data_Init(void);

/* Returnerer næste byte i strømmen hvis det er muligt */
uint8_t Data_Read(void);

/* Returnerer sand hvis der ikke er mere data i strømmen */
uint8_t Data_EOS(void);

/* Returnerer næste instruktion; springer over data inden
   instruktionen */
uint16_t Data_ReadIns(void);

/* Returnerer førstkommende parameter som double. Parameteren starter
   ved datamarkøren og data springes ikke over. */
double Data_ReadParamF(void);

/* Returnerer SAND hvis der findes flere parametre før næste
   instruktion */
uint8_t Data_ParamExists(void);



#endif /* __DATA_H__ */
