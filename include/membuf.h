// The MIT License (MIT)
// Simplistic Binary Streams 0.9
// Copyright (C) 2014, by Wong Shao Voon (shaovoon@yahoo.com)
//
// http://opensource.org/licenses/MIT
//

#pragma once

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/array.hpp>

using namespace boost::iostreams;

typedef stream<basic_array_source<unsigned char> > mem_istream;