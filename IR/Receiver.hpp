// ==========================================================================
//
// File      : Receiver.hpp
// Part of   : IR Library
// Copyright : Nic Jenneboer  Mail : Nicjenneboer@gmail.com
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include "hwlib.hpp"
#include "Protocols.hpp"
#include "IR_Data.hpp"


/// @file

/// \brief
/// Receiver
/// \details
/// This Receiver class is a child class from IR_Data.\n
/// The Receiver get signals from the pin_in.\n
/// These signals can be decode() with the associated protocol.
class Receiver : public IR_Data{
protected:
  hwlib::target::pin_in pin_in;
  std::array< signal, max_length_signals > raw_data;
  int switches = 0;

public:
  Receiver(
    hwlib::target::pin_in pin_in,
    protocol & pro_data,
    uint32_t & code,
    std::array< signal, max_length_signals > raw_data = {0}
  ):
    IR_Data( pro_data, code ),
    pin_in( pin_in ), raw_data( raw_data )
  {}

/// \brief
/// Detect an IR signal.  
/// \details
/// This detect() function waits until the pin_in makes a digital signal switch.\n
/// The time between two signal switches and the signal state would be stored in an array as raw_data. 
  void detect(unsigned int time = 0);

/// \biref
/// Find the associated protocol from stored raw_data.
/// \details
/// This match() function compares raw_data:\n
/// 1) The amount bits from the protocol.\n
/// 2) If the logic start signal is inRange() with the protocol logic start signal.\n
/// 3) If all the digital signal state time is inRange() with the protcol.\n
/// With all protocols.
  void match();

/// \biref
/// Decode the raw_data with the associated protocol.
/// \details
/// This decode() function compares sequently after the start signals if two digitial signals are inRange() with the logic one signal in the protocol.\n
/// If it's true, a one will be set in the decode code, else an zero.
  void decode();


/// \biref
/// Print the raw_data array.
  void print ();

};

#endif // RECEIVER_HPP