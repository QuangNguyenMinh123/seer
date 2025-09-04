# Todo list
1. Capture OpenOCD launch mode
2. Start OpenOCD process
3. Start GDB-multiarch process
4. Connect GDB-multiarch to OpenOCD port
# To fix attach to target issue
2 solutions:
- ```sudo seergdb```
- Edit /etc/sysctl.d/10-ptrace.conf (or /etc/sysctl.d/99-sysctl.conf)<br>
```kernel.yama.ptrace_scope = 0```
