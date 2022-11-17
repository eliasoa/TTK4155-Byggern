//volatile uint32_t i,j;
//PMC -> PMC_PCER0 = (1 << ID_PIOA);				// Enables all PORT A as write-only
//PIOA -> PIO_PER = (1 << 19) | (1 << 20);       // Enable PIOA for GPIO (General-purpose IO)
//PIOA -> PIO_OER = (1 << 19) | (1 << 20);      // Enable port pin for output
//
//PIOA -> PIO_SODR = (1 << 19) | (1 << 20);       // Write High Logic on PIOA.19 and PIOA.20 pin (Set Output Data Register)
//
//for ( i = 0; i < 1000; i++)                     // Delay
//{
//for ( j = 0; j <10; j++){}
//}
//
//PIOA -> PIO_CODR = (1 << 19) | (1 << 20);      // Write Low Logic on PIOA.19 and PIOA.20 pin (Clear Output Data Register)
//
//for ( i = 0; i < 1000; i++)                     // Delay
//{
//for ( j = 0; j <10; j++){}
//}