/* SSDP responder
 *
 * Copyright (c) 2017-2019  Joachim Nilsson <troglobit@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.a
 */
#ifndef SSDP_H_
#define SSDP_H_

#include "config.h"
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <getopt.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <paths.h>
#include <poll.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/param.h>		/* MIN() */
#include <sys/socket.h>
#include <syslog.h>

/* Notify should be less than half the cache timeout */
#define NOTIFY_INTERVAL      300
#define REFRESH_INTERVAL     600
#define CACHE_TIMEOUT        1800
#define MAX_NUM_IFACES       100
#define MAX_PKT_SIZE         2000
#define MC_SSDP_GROUP        "239.255.255.250"
#define MC_SSDP_PORT         1900
#define MC_TTL_DEFAULT       2
#define LOCATION_PORT        (MC_SSDP_PORT + 1)
#define LOCATION_DESC        "/description.xml"

#define SSDP_ST_ALL          "ssdp:all"

#define logit(lvl, fmt, args...) syslog(lvl, fmt, ##args)

#define ENABLE_SOCKOPT(sd, level, opt)					\
        do {								\
                int val = 1;						\
		if (setsockopt(sd, level, opt, &val, sizeof(val)) < 0)	\
			warn("Failed enabling %s", #opt);		\
        } while (0);

/* From The Practice of Programming, by Kernighan and Pike */
#ifndef NELEMS
#define NELEMS(array) (sizeof(array) / sizeof(array[0]))
#endif

extern int debug;
extern char uuid[];

void web_init(void);
int register_socket(int sd, struct sockaddr *addr, struct sockaddr *mask, void (*cb)(int sd));

#ifndef HAVE_PIDFILE
int pidfile(const char *basename);
#endif

#ifndef HAVE_STRLCPY
size_t strlcpy(char *dst, const char *src, size_t siz);
#endif

#endif /* SSDP_H_ */
