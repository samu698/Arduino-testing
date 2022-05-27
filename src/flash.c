#include "util.h"
#include <avr/pgmspace.h>
#include <avr/boot.h>

typedef void (*do_spm_t)(uint16_t address, uint8_t command, uint16_t data);
const do_spm_t do_spm = (do_spm_t)((FLASHEND - 511 + 2) >> 1);

void writePage(const uint8_t* pageBuffer, uint16_t pageN) {
	const uint16_t pageAddress = pageN * SPM_PAGESIZE;
	const uint16_t* wordBuffer = (const uint16_t*)pageBuffer;

	uint8_t sregBak = SREG;
	asm volatile ("cli");

	do_spm(pageAddress, __BOOT_PAGE_ERASE, 0);
	for (uint16_t i = 0; i < SPM_PAGESIZE / 2; i++) 
		do_spm(pageAddress + i * 2, __BOOT_PAGE_FILL, wordBuffer[i]);
	do_spm(pageAddress, __BOOT_PAGE_WRITE, 0);

	SREG = sregBak;
}

void readPage(uint8_t* pageBuffer, uint16_t pageN) {
	for (uint16_t i = 0; i < SPM_PAGESIZE; i++)
		pageBuffer[i] = pgm_read_byte((void*)(SPM_PAGESIZE * pageN + i));
}
