comm(1) "ctools"

# NAME

comm - compare two sorted files

# SYNOPSIS

*comm* [-123] _file1_ _file2_

# DESCRIPTION

*comm* will compare two sorted text files line-by-line, and print each line
with respect to its uniqueness between the two files. Lines unique to _file1_
will be printed with no indentation, lines unique to _file2_ will be printed
with a leading tab character, and lines common to both files will be printed
with two leading tab characters.

All lines in both files must be pre-sorted character-wise.

# OPTIONS

*-1*
	Suppress the output of lines unique to _file1_ and remove one leading
	tab character from the output of other lines.

*-2*
	Suppress the output of lines unique to _file2_ and remove one leading
	tab character from the output of common lines.

*-3*
	Suppress the output of lines common to both files.

# UNSPECIFIED BEHAVIOR

The POSIX standard does not unambiguously specify the behavior of this command
under certain conditions. Under such conditions, the ctools implementation of
*comm* behaves as follows:

- If either file is not sorted, *comm* exits with an error.
- If both _file1_ and _file2_ refer to standard input or to the same FIFO
  special, block special, or character special file, *comm* exits with an error.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
