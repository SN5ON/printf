#include "main.h"

/**
 * handle_flags - Matches flags with corresponding values.
 * @flag: A pointer to a potential string of flags.
 * @index: An index counter for the original format string.
 *
 * Return: 0 or a corresponding value.
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

/**
 * handle_length - Matches length modifiers with their corresponding value.
 * @modifier: A pointer to a potential length modifier.
 * @index: An index counter for the original format string.
 *
 * Return: 0.
 */
unsigned char handle_length(const char *modifier, char *index)
{
	if (*modifier == 'i')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * handle_width -  width modifier with a corresponding value.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential width modifier.
 * @index: An index counter for the original format string.
 *
 * Return: value or 0 otherwise
 */
int handle_width(va_list args, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_precision - a precision modifier with value
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential precision modifier.
 * @index: An index counter for the original format string.
 *
 * Return: 0 and value otherwise negative one.
 */
int handle_precision(va_list args, const char *modifier, char *index)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
	     *modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
	       (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_specifiers -  specifiers function
 * @specifier: A pointer to a potential conversion specifier.
 *
 * Return: value or 0 otherwise
 */
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char)
{
	int i;
	converter_t converters[] = {
		{'c', convert_c};
		{'s', convert_s};
		{'d', convert_di};
		{'i', convert_di};
		{'%', convert_percent};
		{'b', convert_b};
		{'u', convert_u};
		{'o', convert_o};
		{'x', convert_x};
		{'X', convert_X};
		{'S', convert_S};
		{'p', convert_p};
		{'r', convert_r};
		{'R', convert_R};
		{0, NULL}
	}

	for (i = 0; converters[i].func; i++)
	{
		if (converters[i].specifier == *specifier)
			return (converters[i].func);
	}

	return (NULL);
}
