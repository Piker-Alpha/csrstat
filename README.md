You can run the csrstat tool by entering:
```
./csrstat
```
Here's an example of the output (in the latest version):
```
System Integrity Protection status: enabled (0x00000080) (Custom Configuration).

Configuration:
	Apple Internal...........: enabled
	Kext Signing Restrictions: disabled
	Task for PID Restrictions: disabled
	Filesystem Protections...: disabled
	Debugging Restrictions...: disabled
	DTrace Restrictions......: disabled
	NVRAM Protections........: disabled
	Device Configuration.....: enabled
	BaseSystem Verification..: enabled
	High Sierra..............: disabled

This is an unsupported configuration, likely to break in the future and leave your machine in an unknown state.
```
Please note that csrstat ignores the NVRAM variable (csr-active-config), as it should, because that will only be valid after a reboot.
