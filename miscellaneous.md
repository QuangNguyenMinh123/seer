# Todo list

# To fix attach to target issue
2 solutions:
- ```sudo seergdb```
- Edit /etc/sysctl.d/10-ptrace.conf (or /etc/sysctl.d/99-sysctl.conf)<br>
```kernel.yama.ptrace_scope = 0```
