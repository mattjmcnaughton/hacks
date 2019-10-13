tty(1) "ctools"

# NAME

tty - print the name of the controlling tty

# SYNOPSIS

*tty*

# DESCRIPTION

*tty* prints the name of the tty associated with this process. If no tty is
associated with this process, "not a tty" is printed instead and the exit
status will be set to 1.

# EXIT STATUS

|] 0
:[ Command completed successfully
|  1
:  _stdout_ is not a tty
|  >1
:  An error occured

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
