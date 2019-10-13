project(
	'ctools',
	'c',
	version: '0.1.0',
	license: 'GPL-3.0-only',
	meson_version: '>=0.48.0',
	default_options: [
		'c_std=c99',
		'warning_level=2',
	],
)

oneshots = [
	'basename',
	'cat',
	'chgrp',
	'chmod',
	'chown',
	'cksum',
	'cmp',
	'comm',
	'dirname',
	'env',
	'false',
	'head',
	'logname',
	'nice', # Included in base but only effective under XSI
	'rmdir',
	'true',
	'tty',
	'sleep',
	'uname',
]

xsi_oneshots = [
	'link',
	'unlink',
]

cc = meson.get_compiler('c')

if get_option('xsi')
	add_project_arguments(['-D_XOPEN_SOURCE=700'], language: 'c')
	oneshots += xsi_oneshots
else
	add_project_arguments(['-D_POSIX_C_SOURCE=200809L'], language: 'c')
endif

add_project_arguments(cc.get_supported_arguments([
	'-Wundef',
	'-Wlogical-op',
	'-Wmissing-include-dirs',
	'-Wold-style-definition',
	'-Wpointer-arith',
	'-Winit-self',
	'-Wstrict-prototypes',
	'-Wimplicit-fallthrough=2',
	'-Wendif-labels',
	'-Wstrict-aliasing=2',
	'-Woverflow',

	'-Wno-missing-braces',
	'-Wno-missing-field-initializers',
	'-Wno-unused-parameter',
]), language: 'c')

foreach prog : oneshots
	executable(prog, ['src/' + prog + '.c'])
endforeach

scdoc = dependency('scdoc', native: true, required: get_option('man-pages'),
	version: '>=1.10.0')
if scdoc.found()
	subdir('doc')
endif

subdir('test')
