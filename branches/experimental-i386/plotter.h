/*
 * General macros and definitions for HPGL plotter
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
 * $Id: plotter.h 195 2009-03-20 14:15:51Z kkjaergaard $
 */


#ifndef __PLOTTER_H__
#define __PLOTTER_H__


/*
 * Makro til at lave HPGL-instruktioner om til tal
 */
#define HPGL_INS(ins) (((uint8_t)ins[0])<<8 | (uint8_t)ins[1])


#endif /* __PLOTTER_H__ */
