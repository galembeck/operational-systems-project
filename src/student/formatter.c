#include "student_api.h"

#include "syscall_names.h"
#include "trace_helpers.h"

#include <stdio.h>

void student_debug_raw_event(const struct syscall_event *ev,
                             char *buf,
                             size_t bufsz)
{
    snprintf(buf, bufsz, "pid=%d %s %s",
             ev->pid,
             syscall_name(ev->syscall_no),
             ev->entering ? "entrada" : "saida");
}

void student_format_event(const struct syscall_event *ev,
                          char *buf,
                          size_t bufsz)
{
    long nr = ev->syscall_no;

    if (nr == syscall_number_by_name("read")) {
        snprintf(buf, bufsz, "read(%d, %#lx, %lu) = %ld",
                 (int)ev->args[0],
                 ev->args[1],
                 ev->args[2],
                 ev->ret);

    } else if (nr == syscall_number_by_name("write")) {
        snprintf(buf, bufsz, "write(%d, %#lx, %lu) = %ld",
                 (int)ev->args[0],
                 ev->args[1],
                 ev->args[2],
                 ev->ret);

    } else if (nr == syscall_number_by_name("openat")) {
        char path[256];
        if (read_child_string(ev->pid, ev->args[1], path, sizeof(path)) < 0)
            snprintf(path, sizeof(path), "<ilegivel>");

        if ((int)ev->args[0] == -100) { /* AT_FDCWD */
            snprintf(buf, bufsz,
                     "openat(AT_FDCWD, \"%s\", %#x, %#o) = %ld",
                     path,
                     (unsigned int)ev->args[2],
                     (unsigned int)ev->args[3],
                     ev->ret);
        } else {
            snprintf(buf, bufsz,
                     "openat(%d, \"%s\", %#x, %#o) = %ld",
                     (int)ev->args[0],
                     path,
                     (unsigned int)ev->args[2],
                     (unsigned int)ev->args[3],
                     ev->ret);
        }

    } else if (nr == syscall_number_by_name("execve")) {
        char path[256];
        if (read_child_string(ev->pid, ev->args[0], path, sizeof(path)) < 0)
            snprintf(path, sizeof(path), "<ilegivel>");
        snprintf(buf, bufsz, "execve(\"%s\", ...) = %ld", path, ev->ret);

    } else if (nr == syscall_number_by_name("exit_group")) {
        snprintf(buf, bufsz, "exit_group(%d) = %ld",
                 (int)ev->args[0],
                 ev->ret);

    } else {
        snprintf(buf, bufsz,
                 "%s(%#lx, %#lx, %#lx, %#lx, %#lx, %#lx) = %ld",
                 syscall_name(ev->syscall_no),
                 ev->args[0],
                 ev->args[1],
                 ev->args[2],
                 ev->args[3],
                 ev->args[4],
                 ev->args[5],
                 ev->ret);
    }
}
