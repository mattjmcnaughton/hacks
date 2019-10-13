logname(1) "ctools"

# NAME

logname - print the name of the login user

# SYNOPSIS

*logname*

# DESCRIPTION

*logname* prints the name of the login user to _stdout_. However, this is
reliant upon the behavior of the *getlogin*(3), which is notoriously
unreliable. You may wish to use *id*(1) instead.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
