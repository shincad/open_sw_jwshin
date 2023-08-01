static unsigned char Dbi=30;
Debug(Ch,Wait,Mode)
unsigned char Ch;
unsigned int Wait;
unsigned char Mode;
{
unsigned char HexHi,HexLow;
     HexHi  = (unsigned char)(((Ch >> 4)&0x0f) + 0x30);
     HexLow = (unsigned char)((Ch & 0x0f) + 0x30);
     if(Dbi == 30)  { CurHome1(); Dbi=0; }
     if(Dbi == 15) { CurHome2(); }

     if(!Mode){
         CharOut(HexHi);   Dbi++;
         CharOut(HexLow);  Dbi++;
         CharOut(' ');     Dbi++;
      }
     else{ CharOut('[');   Dbi++;
           CharOut(Ch);    Dbi++;
           CharOut(']');   Dbi++;
     }

     Delay2(Wait);
}
