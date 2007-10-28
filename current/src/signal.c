/* IPwatchD - IP conflict detection tool for Linux
 * Copyright (C) 2007 Jaroslav Imrich <jariq(at)jariq(dot)sk>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */


#include "ipwatchd.h"


extern int   debug_flag;		/* Flag indicating debug mode */
extern char  msgbuf[IPWD_MSG_BUFSIZ];	/* Buffer for output messages */
extern pcap_t *h_pcap;			/* Handle for libpcap */


/* ipwd_set_signal_handler - sets signal handler for SIGTERM
 */

int ipwd_set_signal_handler(void) {

	struct sigaction sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigact.sa_handler = ipwd_signal_handler;
	
	if (sigaction(SIGTERM, &sigact, 0) != 0) {
        	snprintf(msgbuf, IPWD_MSG_BUFSIZ, "Unable to set SIGTERM handler");
	        ipwd_message(msgbuf, IPWD_MSG_ERROR);
		return(IPWD_RV_ERROR);
	}

	return(IPWD_RV_SUCCESS);

}


/* ipwd_signal_handler - called when signal received
 *
 * Parameters:
 *   - signal - signal identifier
 */

void ipwd_signal_handler(int signal) {
	
	snprintf(msgbuf, IPWD_MSG_BUFSIZ, "Received signal %d", signal);
	ipwd_message(msgbuf, IPWD_MSG_DEBUG);
	
	if (signal == SIGTERM) {
		pcap_close(h_pcap);
	}
	
}
