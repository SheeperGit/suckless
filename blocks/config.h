// Modify this file to change what commands output to your statusbar, and recompile using the make command.
//
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	/* {"⌨", "sb-kbselect",         0,                 30},    */
	/* {"",	 "sb-tasks",	         10,                 26},    */
	/* {"",	 "sb-music",	          0,	               11},    */
	/* {"",	 "sb-pacpackages",	    0,	                8},    */
	/* {"",	 "sb-torrent",	       20,	                7},    */
	/* {"",	 "sb-memory",	         10,	               14},    */
     {"", "cat /tmp/recordingicon 2>/dev/null",	0,	  9},
	/* {"",	 "sb-cpu",		         10,	               18},    */
	   {"",	 "sb-weather",	     3600,	                5},
	/* {"",	 "sb-nettraf",	        1,	               16},    */
	   {"",	 "sb-volume",	          0,	               10},
	   {"",	 "sb-internet",	       20,	                4},
	// {"",	 "sb-battery",	        5,	                3},    */
	   {"",	 "sb-date",	           59,	                2},
	   {"",	 "sb-time",	           59,	                1},
	/* {"",	 "sb-iplocate",         0,	                27},   */
	/* {"",	 "sb-help-icon",	      0,	                15},   */
};

/* To kill a specific block: kill -[signalnum + 34] $(pidof dwmblocks) */

// Sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char *delim = "|";

// Have dwmblocks automatically recompile and run when you edit this file in
// vim with the following line in your vimrc/init.vim:

// autocmd BufWritePost ~/.local/src/dwmblocks/config.h !cd ~/.local/src/dwmblocks/; sudo make install && { killall -q dwmblocks;setsid dwmblocks & }
