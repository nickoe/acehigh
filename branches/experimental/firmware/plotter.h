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
 * $Id$
 */


#ifndef __PLOTTER_H__
#define __PLOTTER_H__


#define HPGL_INS(ins) (((uint8_t)ins[0])<<8 | (uint8_t)ins[1])

#define HPGL_CI 0x4349
#define HPGL_PA 0x5041
#define HPGL_PD 0x5044
#define HPGL_PR 0x5052
#define HPGL_PU 0x5055

#endif /* __PLOTTER_H__ */
