#include "ft_malcom.h"

int check_ip(char *arg, struct in_addr *ip)
{
	if (inet_pton(AF_INET, arg, ip) != 1)
		return (printf("ft_malcom: unknown host or invalid IP address: (%s).\n", arg), 1);

	if (!gethostbyname(arg))
		return (printf("ft_malcom: unknown host or invalid IP address: (%s).\n", arg), 1);

	return 0;
}

static int is_hex(char c)
{
	return ((c >= '0' && c <= '9')
	|| (c >= 'a' && c <= 'f')
	|| (c >= 'A' && c <= 'F'));
}

int check_mac(char *arg)
{
	char **parts;
	char *err_mess = "ft_malcom: invalid MAC address ";
	int i;
	int j;

	parts = ft_split(arg, ':');
	if (!parts)
		return (printf("ft_malcom: malloc() error.\n"), 1);

	for (i=0; parts[i] != NULL; i++) {
		if (ft_strlen(parts[i]) != 2)
			return (printf("%s (%s).\n", err_mess, arg), free_dtab(parts), 1);
		j = 0;
		while (parts[i][j]) {
			if (!is_hex(parts[i][j]))
				return (printf("%s (%s).\n", err_mess, arg), free_dtab(parts), 1);
			j++;
		}
	}
	if (i != 6)
		return (printf("%s (%s).\n", err_mess, arg), free_dtab(parts), 1);
	free_dtab(parts);
	return 0;
}

int arg_check(char *argv[], struct in_addr *s_ip, struct in_addr *t_ip)
{
	// Check ip and mac format first
	if (check_ip(argv[0], s_ip)) return 1;
	if (check_mac(argv[1])) return 1;
	if (check_ip(argv[2], t_ip)) return 1;
	if (check_mac(argv[3])) return 1;
	return 0;
}

int check_verbose(char *argv)
{
	if (!ft_strcmp("-v", argv)) {
		g_program.verbose = 1;
		return EXIT_SUCCESS;
	}
	else if (argv[0] == '-') {
		printf("ft_malcom: invalid flag (%s) only flag is `-v'\n", argv);
		return EXIT_FAILURE;
	}

	printf("ft_malcom: wrong number of arguments.\nUsage: sudo ./ft_malcom [OPTION] <source ip> <source mac> <target ip> <target mac>\n");
	return EXIT_FAILURE;
}