#ifdef XMEM_
#define XMEM_

void xmem_init ();

void xmem_write ( uint16_t base_address, int addr, uint8_t data);

uint8_t xmem_read ( uint16_t base_address, uint16_t addr );

#endif