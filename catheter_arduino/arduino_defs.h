#pragma once
#ifndef ARDUINO_DEFS_H
#define ARDUINO_DEFS_H

#define DUE

#define CS_EN LOW
#define H_EN LOW
#define DIR_ON LOW

#define INBUF_SIZE PCK_LEN(NCHANNELS)   // a reasonable upper bound on the maximum packet size.

#endif // !ARDUINO_DEFS_H
