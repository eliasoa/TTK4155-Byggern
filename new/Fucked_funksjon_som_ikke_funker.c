xmem_init ();
	UART_Init(MYUBRR);
	
	while(1){
		volatile char* ext_mem = (char *) 0x1000;
		ext_mem[0] = 0x12;
		//write_oled();
		//volatile char* ext_mem = (char *) 0x0000;
		//ext_mem[0] = 0x12;
		//_delay_ms(5000);
		//nils ( 1, 0); // Write to OLED ADDRESS
		//_delay_ms(5000);
	//xmem_write ( 1, 0x400); // Write to ADC ADDRESS

	//xmem_write ( 1, 0X800); // Write to SRAM ADDRESS
	}
}
// OLED 00
// ADC 01
// SRAM 1x
// GUL = A10 = PC2
// GRØNN = A11 = PC3

void write_oled (){
		volatile char* ext_mem = (char *) 0x1000;
		ext_mem[0] = 0x12;
}

void nils ( uint8_t data , uint16_t addr ){
		volatile char* ext_mem = (char *) 0x0000;
		//printf("%i \r\n", BASE_ADDRESS);
		printf("%i \r\n", 0x0000);
		ext_mem[addr] = data;
	
	
	//volatile char* ext_mem = ( char *) BASE_ADDRESS ;
	//printf("%i \r\n", BASE_ADDRESS);
	//printf("%i \r\n", addr);
	//ext_mem [ addr ]= data ;

}