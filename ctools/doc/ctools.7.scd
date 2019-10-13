ctools(1) "ctools"

# NAME

ctools - core tools

# DESCRIPTION

*ctools* provides the *core tools* of a POSIX-1.2017-compatible operating
system, with optional XSI support. These tools provide the core utilities
necessary for a useful scripting environment and a comfortable interactive
shell environment. These tools are used for tasks such as:

- Manipulating and examining the filesystem
- Operations on text files, strings, and paths
- Managing processes on the system

# TOOLS

*ctools* provides the following tools:

|[ *basename*(1)
:< Print the filename part of a pathname
|  *cat*(1)
:  Concatenate files
|  *chgrp*(1)
:  Change group ownership of files
|  *chmod*(1)
:  Change the mode of files
|  *chown*(1)
:  Change ownership of files
|  *cksum*(1)
:  Calculate the cyclic redundancy check (CRC) for files
|  *cmp*(1)
:  Compare two files
|  *comm*(1)
:  Compare two sorted files
|  *dirname*(1)
:  Print the directory part of a pathname
|  *env*(1)
:  Run command with a specified environment
|  *false*(1)
:  Exit with status code 1
|  *head*(1)
:  Print the beginning of files
|  *link*(1)
:  Create a hard link
|  *logname*(1)
:  Print the name of the login user
|  *nice*(1)
:  Run a process with an altered niceness value
|  *rmdir*(1)
:  Remove directories
|  *sleep*(1)
|  Suspend execution for an interval
|  *true*(1)
:  Exit with status code 0
|  *tty*(1)
:  Print the name of the controlling tty
|  *uname*(1)
:  Print the name(s) of the system
|  *unlink*(1)
:  Unlink a file

Detailed information about each tool is available in its respective manual.

# COMMON BEHAVIORS

Most commands adhere to a few common conventions, which are explained here and
only mentioned in each utility's manual if its behavior differs from these
conventions.

## UTILITY SYNTAX

Most tools conform to the XBD Utility Syntax Guidelines. Their usage takes the
form of:

	*command* [-options...] [--] [_argument_...]

In the manual, [ ] is used to indicate optional parameters, and ... is used to
indicate parameters which may be repeated. Command names are shown in *bold*
and _underscored_ text is to be replaced with a value of the user's choosing.
Text with no styling is to be used literally.

The command may accept optional (or mandatory) options, which are preceeded
with a dash ("-") and are one character in length. If an option accepts a
value, the value may be specified immediately following it (e.g. -ovalue) or as
the next parameter (e.g. -o value). Options which do not accept a value may be
specified together (e.g. -abc). An option which accepts a value may also be
specified as the last of several options (e.g. -abcovalue, specifying -abc and
\-ovalue together).

The first non-option parameter indicates the start of the arguments, and each
following parameters is considered such as well. A "--" parameter may also be
used to signal the end of options, allowing the following parameter to begin
with "-" and be interpreted an argument.

## EXIT STATUS

Unless otherwise specified, all commands will exit with status code *0* on
success or a value *>0* on error.

## OUTPUT

Unless otherwise specified, all programs use _stdin_ for input, _stdout_ for
output, and _stderr_ to communicate diagnostic messages.

# COMPATIBILITY

*ctools* provides POSIX-1.2017-compatible "base utilities" with optional
support for the XSI option. This man page is not intended to be a complete
reference, and where it disagrees with the specification, the specification
takes precedence.  The *at*(1), *batch*(1), and *crontab*(1) commands are also
optional, and may not be present on your system.

A shell (*sh*(1)) is not provided by *ctools*.
