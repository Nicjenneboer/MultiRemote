// ==========================================================================
//
// File      : Transmitter.hpp
// Part of   : IR Library
// Copyright : Nic Jenneboer
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef TRANSMITTER_HPP
#define TRANSMITTER_HPP

#include "hwlib.hpp"
#include "Protocols.hpp"
#include "IR_Data.hpp"

/// @file

/// \brief
/// Transmitter
/// \details
/// This Transmitter class is a child class from IR_Data.\n
/// Stored code with a matching protocol can be encoded to digital signals. \n
/// These signals can be send to the pin_out.
class Transmitter : public IR_Data{
protected:
  hwlib::target::pin_out pin_out;
  std::array< signal, max_length_signals > encoded_data;

public:
  Transmitter(
    hwlib::target::pin_out pin_out,
    protocol & pro_data,
    uint32_t & code,
    std::array< signal, max_length_signals > encoded_data = {}
  ):
    IR_Data( pro_data, code ),
    pin_out( pin_out ), encoded_data( encoded_data )
    {}
  
/// \brief
/// Encode the stored code with the associated protocol.
/// \details
/// This encode() function sets the first two signals from encoded_data with the protocol::start signals.\n
/// Then for all bits in code:\n
///   if bit is one put at the end off encoded_data two signals from protocol logic one\n
///   if bit is zero put at the end off encoded_data two signals from protocol logic zero.\n
  void encode();

/// \brief
/// Send stored encoded_data with 38kHz to pin_out.
/// \details
/// This send() function send for all encoded_data signals:\n
/// If encoded_data signal state is one: a high and low digital signal on pin_out for 13 microseconds(38kHz) for x encoded_data signal time.\n
/// If encoded_data signal state is zero: a low digital signal on pin_out for x encoded_data signal time.
  void send();

/// \brief
/// Print the encoded_data array.
  void print();

};

#endif // TRANSMITTER