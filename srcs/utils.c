#include "ft_malcom.h"

void free_dtab(char **dtab)
{
	for (int i=0; dtab[i] != NULL; i++)
		free(dtab[i]);
	free(dtab);
}

void cleanup(struct ifaddrs *interfaces, int fd)
{
	close(fd);
	freeifaddrs(interfaces);
}

int err(const char *str, const char *err_str)
{
	printf("ft_malcom: %s: %s.\n", str, err_str);
	return EXIT_FAILURE;
}

static unsigned char hex_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (c - 'A' + 10); // A-F
}

int parse_mac(char *str, unsigned char mac[6])
{
	char **parts;
	int i;

	parts = ft_split(str, ':');
	if (!parts)
		return (0);
	for (i = 0; parts[i] != NULL; i++) {
		if (i >= 6) { free_dtab(parts); return (0); }
		mac[i] = (hex_val(parts[i][0]) << 4) | hex_val(parts[i][1]);
	}
	free_dtab(parts);
	return (i == 5);
}