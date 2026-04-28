/* SPDX-License-Identifier: GPL-2.0+ WITH Linux-syscall-note */
#ifndef _UAPI_LINUX_STACKTRACE_H
#define _UAPI_LINUX_STACKTRACE_H

enum stacktrace_setup_types {
	STACKTRACE_REGISTER_SFRAME	= 1,
	STACKTRACE_UNREGISTER_SFRAME	= 2,
};

#endif /* _UAPI_LINUX_STACKTRACE_H */
