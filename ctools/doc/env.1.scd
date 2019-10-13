env(1) "ctools"

# NAME

env - set the environment to run a program

# SYNOPSIS

*env* [-i] [_name_=_value_]... [_utility_ [_argument_...]]

# DESCRIPTION

*env* will update the environment based on its arguments, then invoke
_utility_, passing _arguments_ to it.

If _utility_ is not provided, the resulting environment is written to standard
output with one _name_=_value_ pair per line.

# OPTIONS

*-i*
	Clear the inherited environment before setting new variables and invoking
	_utility_.

# UNSPECIFIED BEHAVIOR

The POSIX standard does not unambiguously specify the behavior of this command
under certain conditions. Under such conditions, the ctools implementation of
*env* behaves as follows:

- If the first argument is *'-'*, *env* will exit with an error.

# NOTES

The ctools implementation of *env* uses _execvp_ to execute _utility_. Should
PATH be unset, _execvp_ may search some default path set by the system and/or
C library.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
