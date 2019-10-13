nice(1) "ctools"

# NAME

nice - run a process with an altered niceness value

# SYNOPSIS

*nice* [-n _incr_] _command_ [_args_...]

# DESCRIPTION

*nice* runs _command_ (with optional _args_) with the niceness adjusted
relative to the current niceness.

Note that on systems where ctools has been compiled without XSI support, *nice*
will run _command_ without setting the niceness.

# OPTIONS

*-n* _incr_
	Specify _incr_ as an integer representing the amount to adjust the
	niceness by, positive or negative. The default adjustement is 10.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
