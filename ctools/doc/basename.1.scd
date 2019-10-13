basename(1) "ctools"

# NAME

basename - print the filename part of a pathname

# SYNOPSIS

*basename* _string_ [suffix]

# DESCRIPTION

*basename* will interpret _string_ as a pathname and print only the filename
portion of the path. If a suffix is specified on the command line and is found
to be the suffix of the filename, it will be trimmed.

# UNSPECIFIED BEHAVIOR

The POSIX standard does not unambiguously specify the behavior of this command
under certain conditions. Under such conditions, the ctools implementation of
*basename* behaves as follows:

- If _string_ is an empty string, *basename* will randomly choose between
  printing "." or an empty string.
- If _string_ is equal to "//", *basename* may randomly choose to output it
  as-is with no further processing.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
