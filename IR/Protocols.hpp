// ==========================================================================
//
// File      : Protocols.hpp
// Part of   : IR Library
// Copyright : Nic Jenneboer
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef PROTOCOLS_HPP
#define PROTOCOLS_HPP

#include "hwlib.hpp"
/// @file

/// \brief
/// The max length for signal data in a array.
const int max_length_signals = 100;

struct signal{
  long unsigned int us;
  bool stat;

   /// \brief
   /// output operator for a signal.
   /// \details
   /// This operator<< prints a signal in the format: stat[us]
  friend hwlib::ostream & operator<<( hwlib::ostream & lhs, const signal & rhs );

};

inline hwlib::ostream & operator<<( hwlib::ostream & lhs, const signal & rhs ){
   lhs << rhs.stat << "[" << rhs.us << "] ";
   return lhs;
}

/// \brief
/// Struct for define a protocol
/// \details
/// Protocol template:\n\n
/// const protocol [NAME] = {\n
/// &nbsp;&nbsp;&nbsp;&nbsp;"[NAME]",\n
/// &nbsp;&nbsp;&nbsp;&nbsp;{{[START_US], [START_STATE]},{[START_US], [START_STATE]}},\n
/// &nbsp;&nbsp;&nbsp;&nbsp;{{[ONE_US], [ONE_STATE]},{[ONE_US], [ONE_STATE]}},\n
/// &nbsp;&nbsp;&nbsp;&nbsp;{{[ZERO_US], [ZERO_STATE]},{[ZERO_US], [ZERO_STATE]}},\n
/// &nbsp;&nbsp;&nbsp;&nbsp;[BITS],\n
/// &nbsp;&nbsp;&nbsp;&nbsp;[RANGE]\n
/// };

struct protocol{
	char name[25];
	signal start[2];
	signal l_one[2];
	signal l_zero[2];
	int bits = 0;
	int range;
};


const protocol sony = {
	"SONY",
	{{2400, 1},{600, 0}},
	{{1200, 1},{600, 0}},
	{{600, 1},{600, 0}},
	11,
	150
};

const protocol nec = {
	"NEC",
	{{9000, 1},{4500, 0}},
	{{560, 1},{1690, 0}},
	{{560, 1},{560, 0}},
	32,
	150
};

const protocol jvc = {
	"JVC",
	{{8400, 1},{4200, 0}},
	{{525, 1},{1575, 0}},
	{{525, 1},{525, 0}},
	16,
	150
};

const protocol samsung = {
	"SAMSUNG",
	{{4500, 1},{4500, 0}},
	{{550, 1},{1700, 0}},
	{{550, 1},{550, 0}},
	32,
	150
};

const protocol saba = {
	"SABA",
	{{10300, 1},{5200, 0}},
	{{650, 1},{650, 0}},
	{{2000, 1},{650, 0}},
	23,
	150
};

/// \brief
/// Array of all protocols.\n
/// Used in Receiver::match() function.
const std::array<protocol, 5> protocols = 
{
	sony,
	nec,
	jvc,
	saba,
	samsung
};


#endif // PROTOCOLS_HPP