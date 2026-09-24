#include "ft_malcom.h"

void print_mac(unsigned char mac[6])
{
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
		   mac[0],
		   mac[1],
		   mac[2],
		   mac[3],
		   mac[4],
		   mac[5]);
}

void print_packet(struct eth_header *eth, struct arp_header *arp, int type)
{
	char str[INET_ADDRSTRLEN];
	struct in_addr ip;

	if (type == ARP_REQUEST) {
		printf("ARP request:\n");
	}
	else printf("ARP reply:\n");

	printf("    Ethernet header:\n");
	printf("\tdestination mac address: "); print_mac(eth->eth_dha);
	printf("\tsource mac address: "); print_mac(eth->eth_sha);
	printf("\teth type: %hx\n\n", ntohs(eth->eth_type));

	printf("    ARP header:\n");
	printf("\thardware type: %hx\n", ntohs(arp->ar_hrd));
	printf("\tprotocol type: %hx\n", ntohs(arp->ar_pro));
	printf("\thardware address length: %u\n", arp->ar_hln);
	printf("\tprotocol address length: %u\n", arp->ar_pln);
	printf("\topcode: %hx\n", arp->ar_op);
	printf("\tsource mac address: "); print_mac(arp->ar_sha);
	ft_memcpy(&ip.s_addr, arp->ar_spa, sizeof(uint32_t));
	if (inet_ntop(AF_INET, &ip, str, INET_ADDRSTRLEN) == NULL)
	{
		err("inet_ntop", strerror(errno));
	}
	else
		printf("\tsource ip address:  %s\n", str);
	printf("\tdestination mac address: "); print_mac(arp->ar_tha);
	ft_memcpy(&ip.s_addr, arp->ar_tpa, sizeof(uint32_t));
	if (inet_ntop(AF_INET, &ip, str, INET_ADDRSTRLEN) == NULL)
	{
		err("inet_ntop", strerror(errno));
	}
	else
		printf("\tdestination ip address:  %s\n", str);
}