#ifndef __XBEE_INTERNAL_H
#define __XBEE_INTERNAL_H

/*
	libxbee - a C/C++ library to aid the use of Digi's XBee wireless modules
	          running in API mode.

	Copyright (C) 2009 onwards  Attie Grande (attie@attie.co.uk)

	libxbee is free software: you can redistribute it and/or modify it
	under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	libxbee is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with libxbee. If not, see <http://www.gnu.org/licenses/>.
*/

/* ######################################################################### */
/* just to keep the compiler happy before structs are declared */
struct xbee;
struct xbee_con;
struct xbee_serialInfo;
struct xbee_frameBlock;
struct xbee_frameInfo;
struct xbee_log;
struct xbee_mode;
struct xbee_txInfo;
struct xbee_rxInfo;
struct xbee_interface;

#include "xsys.h"
#include "xbee.h"
#include "mutex.h"

struct xbee_buf {
	size_t len;
	unsigned char data[1];
};

struct xbee_sbuf {
	xsys_sem sem;
	size_t len;
	unsigned char data[1];
};

struct xbee_tbuf {
	struct timespec ts;
	size_t len;
	unsigned char data[1];
};

struct xbee_serialInfo {
	char *device;
	int baudrate;
	xsys_serialDev dev;
	
	size_t txBufSize;
	struct xbee_sbuf *txBuf;
};

#define LH fprintf(stderr, "LOG_HERE: %s:%d\n", __FILE__, __LINE__);

/* ######################################################################### */

#include <lga.h>

#define XBEE_DECLARE_MODE(mode_name) \
	extern const struct xbee_mode mode_##mode_name; \
	const struct xbee_mode * const _xbee_##mode_name _lga_el(xbee_mode_list) = &mode_##mode_name; \
	const struct xbee_mode mode_##mode_name

#define XBEE_DECLARE_CONTYPE_ARRAY(mode_name) \
	_lga_get_array_static(const struct xbee_modeConType *, xbee_##mode_name##_list, conTypes); \
	static struct xbee_modeConType *listEnd _lga_terminator(xbee_##mode_name##_list) = NULL;

#define XBEE_DECLARE_CONTYPE(mode_name, type_name) \
	extern const struct xbee_modeConType xbee_##mode_name##_##type_name; \
	const struct xbee_modeConType * const _xbee_##mode_name##_##type_name _lga_el(xbee_##mode_name##_list) = &xbee_##mode_name##_##type_name; \
	const struct xbee_modeConType xbee_##mode_name##_##type_name

#endif /* __XBEE_INTERNAL_H */
