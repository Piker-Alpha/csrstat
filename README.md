You can run the csrstat tool by entering:
```
./csrstat
```
Here's an example of the output (latest version):
```
csrstat v1.5 Copyright (c) 2015-2017) by Pike R. Alpha
System Integrity Protection status: enabled (0x00000080) (Custom Configuration).

Configuration:
	Apple Internal............: 0 (disabled)
	Kext Signing Restrictions.: 0 (enabled)
	Task for PID Restrictions.: 0 (enabled)
	Filesystem Protections....: 0 (enabled)
	Debugging Restrictions....: 0 (enabled)
	DTrace Restrictions.......: 0 (enabled)
	NVRAM Protections.........: 0 (enabled)
	Device Configuration......: 0 (disabled)
	BaseSystem Verification...: 0 (enabled)
	User Approved Kext Loading: 0 (enabled)

This is an unsupported configuration, likely to break in the future and leave your machine in an unknown state.
```
Please note that csrstat ignores the NVRAM variable (csr-active-config), as it should, because that is only valid after a reboot.
