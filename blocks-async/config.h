#ifndef CONFIG_H
#define CONFIG_H

// To kill a specific block: 
// kill -<signalnum + 34> $(pidof dwmblocks)

// To refresh all the blocks:
// kill -10 $(pidof dwmblocks)

// To re-compile and restart dwmblocks-async:
// cd ~/suckless/blocks-async; sudo make install && { killall -q dwmblocks;setsid dwmblocks & }

// String used to delimit block outputs in the status.
#define DELIMITER "|"

// Maximum number of Unicode characters that a block can output.
#define MAX_BLOCK_OUTPUT_LENGTH 45

// Control whether blocks are clickable.
#define CLICKABLE_BLOCKS 1

// Control whether a leading delimiter should be prepended to the status.
#define LEADING_DELIMITER 0

// Control whether a trailing delimiter should be appended to the status.
#define TRAILING_DELIMITER 0

// Define blocks for the status feed as X(icon, cmd, interval, signal).
#define BLOCKS(X)             \
     X("", "cat /tmp/recordingicon 2>/dev/null",	0,     9) \
	   X("", "sb-weather",	                        3600,	 5) \
	   X("", "sb-volume",	                          0,    10) \
	   X("", "sb-internet",	                        20,    4) \
	   X("", "sb-date",	                            59,    2) \
	   X("", "sb-time",	                            59,    1) \

#endif  // CONFIG_H

