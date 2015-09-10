/*
 * Created: 23 August 2015
 * Name...: csrstat.c
 * Author.: Pike R. Alpha
 * Purpose: Command line tool for El Capitan to get the active SIP status.
 *
 * Compile with: cc csrstat.c /usr/lib/libSystem.B.dylib -o csrstat
 * 
 * Updates:
 *			- Use csr_check so that csr_allow_all/internal are taken into account (Pike R. Alpha September 2015).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint32_t csr_config_t;

/* Rootless configuration flags */
#define CSR_ALLOW_UNTRUSTED_KEXTS		(1 << 0)
#define CSR_ALLOW_UNRESTRICTED_FS		(1 << 1)
#define CSR_ALLOW_TASK_FOR_PID			(1 << 2)
#define CSR_ALLOW_KERNEL_DEBUGGER		(1 << 3)
#define CSR_ALLOW_APPLE_INTERNAL		(1 << 4)
#define CSR_ALLOW_UNRESTRICTED_DTRACE	(1 << 5)
#define CSR_ALLOW_UNRESTRICTED_NVRAM	(1 << 6)

#define CSR_VALID_FLAGS (CSR_ALLOW_UNTRUSTED_KEXTS | \
	CSR_ALLOW_UNRESTRICTED_FS | \
	CSR_ALLOW_TASK_FOR_PID | \
	CSR_ALLOW_KERNEL_DEBUGGER | \
	CSR_ALLOW_APPLE_INTERNAL | \
	CSR_ALLOW_UNRESTRICTED_DTRACE | \
	CSR_ALLOW_UNRESTRICTED_NVRAM)

/* Syscalls */
extern int csr_check(csr_config_t mask);
extern int csr_get_active_config(csr_config_t *config);

//==============================================================================

char * _csr_check(aMask, aFlipflag)
{
	bool stat = 0;

	// Syscall
	if (csr_check(aMask) != 0)
	{
		stat = (aFlipflag) ? 0 : 1;
	}
	else
	{
		stat = (aFlipflag) ? 1 : 0;
	}
	
	if (stat)
	{
		return("enabled");
	}

	return("\33[1mdisabled\33[0m");
}


//==============================================================================

int main(int argc, const char * argv[])
{
	uint32_t config = 0;
	// Syscall
	csr_get_active_config(&config);

	printf("System Integrity Protection status: %s ", (config == CSR_VALID_FLAGS) ? "\33[1mdisabled\33[0m": "enabled");

	if (config)
	{
		if (config == CSR_ALLOW_APPLE_INTERNAL)
		{
			printf("(Apple Internal).");
		}
		else
		{
			printf("(Custom Configuration: 0x%08x).", config);
		}
	}
	
	printf("\n\nConfiguration:\n");

	printf("\tApple Internal: %s\n", _csr_check(CSR_ALLOW_APPLE_INTERNAL, 1));
	printf("\tKext Signing Restrictions: %s\n", _csr_check(CSR_ALLOW_UNTRUSTED_KEXTS, 0));
	printf("\tFilesystem Protections: %s\n", _csr_check(CSR_ALLOW_UNRESTRICTED_FS, 0));
	printf("\tDebugging Restrictions: %s\n", _csr_check(CSR_ALLOW_KERNEL_DEBUGGER, 0));
	printf("\tDTrace Restrictions: %s\n", _csr_check(CSR_ALLOW_UNRESTRICTED_DTRACE, 0));
	printf("\tNVRAM Protections: %s\n", _csr_check(CSR_ALLOW_UNRESTRICTED_NVRAM, 0));
	
	if (config && (config != CSR_ALLOW_APPLE_INTERNAL))
	{
		printf("\nThis is an unsupported configuration, likely to break in the future and leave your machine in an unknown state.\n");
	}

	exit(-1);
}
