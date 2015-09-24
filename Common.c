//#include <18F46K20.h>
//#include "Common.h"

///////////////////////////////////////////////////////////////////////
// Function   : ConvertFromBCDasasasas
// Purpose    : Converts a received bcd encoded string into.bbbb
//              an integer
// Parameters : bp: Address of bcd array 
//              size of array
// Returns    : None
///////////////////////////////////////////////////////////////////////
int32 ConvertFromBCD(unsigned char * bp, unsigned char size)
{
   int32 k, value = 0;
   unsigned char index;

   k = 1;
   for ( index = size; index > 0; --index, k *= 100 )
      value += (((bp[index - 1] >> 4) * 10) + (bp[index - 1] & 0x0f)) * k;
  return value;
}

///////////////////////////////////////////////////////////////////////
// Function   : CalculateCRC
// Purpose    : Calculates the crc from an array of characters. Used to
//              check validity of received packets and to set CRC bytes
//              on outgoing LPs
// Parameters : sp     - address of first byte in sequence 
//              len    - number of chars to process
//              crcval - starting 'seed' value (usally 0 for general use)
// Returns    : two byte crc value
////////////////////////////////////////////////////////////////
unsigned int16 CalculateCRC(unsigned char* sp, unsigned char len, unsigned long crcval)
{
   unsigned int32 ch;
   unsigned int32 q;

   for (; len; len--)
   {
      ch = *sp++;
      q = (crcval ^ ch) & 017;
      crcval = (crcval >> 4) ^ (q * 010201);
      q = (crcval ^ (ch >> 4)) & 017;
      crcval = (crcval >> 4) ^ (q * 010201);
   }
   return (unsigned int16)crcval;
}

void memclr_ms(void *s, unsigned short n)
{
     unsigned char *us;
     us = s;
     while (n-- )
         *us++ = 0;
}

void memcpy_ms(unsigned char* dst, unsigned char* src, unsigned char n)
{
     while (n-- != 0)
         *dst++ = *src++;
}

int8 memnonzero_ms(unsigned char* src, int8 count)
{
   while ( count-- )
   {
      if ( *src  )
         return 1;
      ++src;
   }
   return 0;
}


