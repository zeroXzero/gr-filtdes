# Copyright 2011-2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
#include_directories(${CMAKE_CURRENT_BINARY_DIR})
#add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/icons.qrc COMMAND echo hello > icons.qrc)
install(FILES
    add_pole.svg
	add_zero.svg
	group_delay.svg
	impulse_response.svg
	mag_response.svg
	overlay.svg
	phase_delay.svg
	phase_response.svg
	step_response.svg
	conjugate.svg
	filtr_taps.svg
	remove_red.svg
    DESTINATION bin/icons 
)

