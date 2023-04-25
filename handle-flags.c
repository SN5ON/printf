#include "main.h"

/**
 *handle_flags - Matches flags with corresponding values.
 * @flag: A pointer to a potential string of flags.
 * @index: An index counter for the original format string.
 *
 * Return: 0 or a corresponding value.
 *
 */
unsigned char handle_flags(const char *flag, char *index)
{
	int n, i;
	unsigned char ret = 0;
	flag_t flags[] = {
		{'+', Plus},
		{' ', Space},
		{'#', Hush},
		{'0', Zero},
		{'-', Negative},
		{0, 0}
	};

	for (n = 0; flag[n]; n++)
	{
	for (i = 0; flags[i].flag != 0; i++)
		{
	if (flag[n] == flags[i].flag)
	{
	(*index)++;
	if (ret == 0)
	ret = flags[i].value;
	else
	ret |= flags[i].value;
		break;
		}
	}
	if (flags[i].value == 0)
	break;
	}
	return (ret);
}

