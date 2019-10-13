harness=join_paths(meson.current_source_dir(), 'harness.sh')

test_files = [
	'basename',
	'cat',
	'chgrp',
	'chown',
	'chmod',
	'cksum',
	'cmp',
	'comm',
	'dirname',
	'env',
	'false',
	'head',
	'logname',
	'nice',
	'rmdir',
	'sleep',
	'true',
	'tty',
	'uname',
]

xsi_tests = [
	'link',
	'unlink',
]

if get_option('xsi')
	test_files += xsi_tests
endif

foreach test_file : test_files
	test(
		test_file,
		find_program(test_file),
		env: [
			'HARNESS=@0@'.format(harness),
			'BUILDDIR=@0@'.format(meson.current_build_dir()),
		],
	)
endforeach
