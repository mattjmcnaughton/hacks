scdoc_prog = find_program(scdoc.get_pkgconfig_variable('scdoc'), native: true)
sh = find_program('sh', native: true)
mandir = get_option('mandir')

man_files = [
	# Section 1
	'basename.1',
	'cat.1',
	'chgrp.1',
	'chmod.1',
	'chown.1',
	'cksum.1',
	'cmp.1',
	'comm.1',
	'dirname.1',
	'env.1',
	'false.1',
	'head.1',
	'link.1',
	'logname.1',
	'nice.1',
	'rmdir.1',
	'sleep.1',
	'true.1',
	'tty.1',
	'uname.1',
	'unlink.1',
	# Section 7
	'ctools.7',
]

foreach page : man_files
	filename = page + '.scd'
	topic = filename.split('.')[-3].split('/')[-1]
	section = filename.split('.')[-2]
	output = '@0@.@1@'.format(topic, section)

	custom_target(
		output,
		input: filename,
		output: output,
		command: [
			sh, '-c', '@0@ < @INPUT@ > @1@'.format(
				scdoc_prog.path(),
				join_paths(meson.current_build_dir(), output))
		],
		install: true,
		install_dir: '@0@/man@1@'.format(mandir, section)
	)
endforeach
