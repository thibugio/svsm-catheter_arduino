#pragma once
#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

/* number of channels being used */
#define NCHANNELS 6 

/* number of bytes in a channel command, preamble, post-amble, packet checksum */
#define CMD_LEN 3  
#define PRE_LEN 1
#define POST_LEN 1
#define PCK_CHK_LEN 1

/* the expected length of a packet with a specified number of commands */
#define PCK_LEN(NCMDS) PRE_LEN + CMD_LEN*NCMDS + POST_LEN + PCK_CHK_LEN

#define PCK_OK 1

/* error codes for arduino to send back to PC */
#define PRE_ERR 1
#define POST_ERR 2
#define PCK_CHK_ERR 4

#define POL_B 3
#define ENA_B 2
#define UPD_B 1
#define DIR_B 0

#define DAC_RES 4096

#endif // !COMMON_DEFS_H
