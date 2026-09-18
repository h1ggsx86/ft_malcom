# ifndef FT_MALCOM_H
#define FT_MALCOM_H

#define _GNU_SOURCE
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <linux/if_packet.h>
#include <net/if_arp.h>
#include <net/ethernet.h>
#include <linux/if_link.h>
#include <errno.h>

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <signal.h>

#include "../libft/libft.h"

#define WANTED_BITS (IFF_UP | IFF_RUNNING)
#define UNWANTED_BITS (IFF_LOOPBACK | IFF_NOARP)
#define BUFF_SIZE 60
#define ETH2_HEADER_LEN 14
#define HW_TYPE 1
#define MAC_LENGTH 6
#define IPV4_LENGTH 4
#define ARP_REQUEST 0x01
#define ARP_REPLY 0x02

extern volatile sig_atomic_t s_flag;

struct __attribute__((packed)) eth_header {
	unsigned char eth_dha[6];
	unsigned char eth_sha[6];
	uint16_t eth_type;
};

struct __attribute__((packed)) arp_header {
	uint16_t		ar_hrd;
	uint16_t		ar_pro;
	unsigned char	ar_hln;
	unsigned char	ar_pln;
	uint16_t 		ar_op;
	unsigned char	ar_sha[6];
	unsigned char	ar_spa[4];
	unsigned char	ar_tha[6];
	unsigned char	ar_tpa[4];
};

struct addr_data {
	struct in_addr ip;
	unsigned char mac[6];
};

int arg_check(char *argv[], struct in_addr *s_ip, struct in_addr *t_ip);
int err(const char *str, const char *err_str);
int parse_mac(char *str, unsigned char mac[6]);
void free_dtab(char **dtab);
void cleanup(struct ifaddrs *interfaces, int fd);


#endif
