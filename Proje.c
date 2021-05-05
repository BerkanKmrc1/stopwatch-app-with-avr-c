

#include <avr/io.h>//Kütüphane tanýmlandý tccr1b tcnt gibi kavramlar için

void BirKombinasyondayaz(int,int,int);//Üçünü birden yazdýrmak için fonksiyon prototipi
void YirmibesMiliSaniyeBekle(int);//25 ms beklemek için fonksiyon prototipi
void BirSaniyeBekle(int);//Bir saniye beklemek için fonksiyon prototipi
void SaliseyiYazdir(int);//Saliseyi yazdýrýrken kullandýðýmýz fonksiyon prototipi
void SaniyeyiYazdir(int);//Saniyeyi yazdýrýrken kullandýðýmýz fonksiyon prototipi
void DakikayiYazdir(int);//Dakikayý yazdýrýrken kullandýðýmýz fonksiyon prototipi
    
 

int main()//main fonksiyonunu tanýmladým
{
          DDRB=0xFF;//B portunu yani 8 den 13e kadar olan pinlerin hepsini çýkýþ olarak ayarladýk
          DDRD=0xF0;//D portunun buton pinlerini yani 2 ile 3 ü giriþ 4 den 8 e kadar olan display pinlerinide çýkýþ olarak ayarladýk
          TCCR1B|=((1<<CS12)|(1<<CS10));//Týmer 1 için prescaler deðerini 1024 olarak belirledik Buraya kadar setup kýsmýydý þimdi loop kýsmýný yazýcaz

while(1)//loopa girdik
{
	
  for (int dakika=9;dakika>=0;dakika--)//dakikayý dolaþmasý için en dýþta for tanýmladýk 9 dan baþlayýp 0 a kadar sayýcak
	{
	  for (int saniye=5;saniye>=0;saniye--)//saniyeyi dolaþmasý için for tanýmladýk 5 den 0 a kadar sayýcak
		 {
			for (int salise=9;salise>=0;salise--)//saliseyi dolaþmasý için for tanýmladýk 9 dan 0 a kadar sayýcak
			  {
				if ((PIND & (1 << 2))  == 0  )//1 i 2 bit sola kaydýrarak 2. pini kontrol ediyoruz basýlý deðiilse
				  {
					if ((PIND & (1 << 3))  ==0  )//1 i 3 bit sola kaydýrarak 3. pini kontrol ediyoruz basýlý deðilse 
						{
						 BirKombinasyondayaz(dakika,saniye,salise);//Bu fonksiyonu çaðýr fonksiyonun ne iþ yaptýðýný altta açýkladým
						}
					else //iç teki ifin else inde butona basýlý durumunu kontrol eder basýlý ise
					{
						salise=0;//saliseyi 0 lar
						saniye=0;//saniyeyi 0 lar 
						dakika=0;//dakikayý 0 lar
					}
							
					}
					else//dýþtaki ifin else durumunda ise basýlý olma durumunu kontrol eder ve basýlý ise 
					{
					  while(1)//sonsuz döngü içinde tekrar butona basýlý olmama durumunu kontrol edicek 
					  {
						if ((PIND & (1 << 2))  ==0 )//Durdurma butonundan elimizi çekmiþsek  yaný basýlý deðilse 
						{
							break;//döngüden çýkýcak 
					    }
					    else//eðer basýlý ise 
						{
						 DakikayiYazdir(dakika);//O anki kombinsayon da hangi dakikada kalmýþsa o dakikayý yakýcak 
						 YirmibesMiliSaniyeBekle(1);//25 ms beklicek bunu hýzlý bi þekilde yapýcak gözle görülmemesi için
						 SaniyeyiYazdir(saniye);//O anki kombinasyons da hangi saniyede kalmýþsa o aniyeyi yakýcak
						 YirmibesMiliSaniyeBekle(1);//25 ms beklicek bunu hýzlý bi þekilde yapýcak yine gözle görülmemesi için
						 SaliseyiYazdir(salise);// O anki kombinasyon da hangi salisede kalmýþsa o saliseyi yakýcak 
						 YirmibesMiliSaniyeBekle(1);//25 ms beklicek bunu hýzlý bi þekilde yapýcak ki gözle görülmesin 25 ms nin altýný insan gözü kesintisiz olarak görür
						 BirSaniyeBekle(1);//ve bir saniye beklicek bu ledler bu þekilde o kombinasyonu durdurduðumuzda yanýp sönecek
						}
					  }
									
		
			}
					
		}
				
	}
}
		
	
}
            return 0;//mainin içini sonlandýrdýk
}

    void BirKombinasyondayaz(int dakika ,int saniye ,int salise)//Bir kombinasyonda yazan fonksiyonumuzun içini tanýmlýcaz
    {
	
	   for(int sayac=0;sayac<200;sayac++)//200 e kadar gitmesinin sebebi salise saniye ve dakikanýn orantýlý bi þekilde azalmasýdýr
	     {
		   DakikayiYazdir(dakika);//bu fonksiyonun içinde dakikayi yazdýr fonksiyonunu çaðýrýyoruz bu fonksiyonun ne iþ yaptýðýný altta açýkladým
		   YirmibesMiliSaniyeBekle(1);//25 MS çaðýrýyoruz bunun da ne iþ yaptýðýný açýkladým
		   SaniyeyiYazdir(saniye);//ayný þekilde saniye yi de çaðýrýyoruz ne iþ yaptýðý altta açýklandý
		   YirmibesMiliSaniyeBekle(1);//25 ms bekliyoruz altta açýkladým
		   SaliseyiYazdir(salise);//ve son olarak saliseyi de çaðýrýyoruz altta açýklamasý bulunuyor
		   YirmibesMiliSaniyeBekle(1);//ve yine 25 ms bekliyoruz
	     }
     }

    void YirmibesMiliSaniyeBekle(int x)//25 ms bekleme yarattýðýmýz fonksiyonu tanýmlýcaz
    {
	   for(int sayac=1;sayac<=x;sayac++)//bu döngüyü þunun için tanýmladýk mesela bu fonksiyonu çaðýrdýðýmýzda bir foru 1 kere döndürürsek 25 ms bekler 40 kere döndürürsek 1 saniye bekler
	     {
		  TCNT1=65500;//65500 den 65536 ya kadar sayýnca 25 ms üretir
		  while((TIFR1&(1<<TOV1))==0);//tov 1 bayraðýný sürekli kontrol eder(polling iþlemi) 0 olunca sürekli sayar 25 ms ürettiðinde 1 olur ve döngüden çýkar
		  TIFR1|=(1<<TOV1);//TOV1 bayraðýný tekrar 0 layarak yeniden saymasýný saðlýyoruz
	     }

     }
    void BirSaniyeBekle(int x)//1saniye gecikme üretmek için kullanacaðýmýz fonksiyon
    {
	   for(int sayac=1;sayac<=x;sayac++)//Bu da ayný þekilde 1 parametresiyle  çaðýrdýmýzda 1sn üretir farklý parametrelerde 1 in katlarý kadar saniye üretir
	     {
		  TCNT1=49911;//49911 den 65536 ya kadar saydýðýnda 1 saniye geçmiþ olucak
		  while((TIFR1&(1<<TOV1))==0);//TOV1 bayraðýnýn 1 olmasýný bekliyoruz
		  TIFR1|=(1<<TOV1);//1 olduðunda tekrar 0 lýyoruz ki tekrar sayabilsin
	     }
    }

   void SaliseyiYazdir(int segment)//saliseyi yazdýrmak için 
   {
	
	        switch(segment){//switch kontrolünü tanýmlýyoruz
		    case 0:	//0 yakmak için yani 0 ise 
		    PORTD=      0x10 | // 4.pin
		                0x20 | // 5.pin
			            0x40 | // 6.pin
			            0x80 ; // 7.pin
		    PORTB=      0x01 | // 8.pin
		                0x02 | // 9.pin
			            0x20;  //salise pini bu pinler yandýðýnda göstergede  0 yanýcak 
			            break;
		    case 1:	
			PORTD=      0x20 | // 5.pin
		                0x40;  // 6.pin
			PORTB=      0x20;  //salise pini bu pinler yandýðýnda göstergede  1 yanýcak		
				        break;
		    case 2:	
			PORTD=      0x10 | //4.pin
			            0x20 | //5.pin
						0x80;  //7.pin
			PORTB=      0x04 | //10.pin
			            0x01 | //8.pin
						0x20;  //salise pini bu pinler yandýðýnda göstergede  2 yanýcak
				        break;
		    case 3: 
		    PORTD=     0x10  | //4.pin
			           0x20  | //5.pin
					   0x40  | //6.pin
					   0x80;   //7.pin
			PORTB=     0x04  | //10.pin
			           0x20;   //salise pini bu pinler yandýðýnda göstergede 3 yanýcak		
				       break;
				
		    case 4: 
			PORTD=     0x20  | //5.pin
		               0x40;   //6.pin
			PORTB=     0x04  | //10.pin
			           0x02  | //9.pin
					   0x20;   //salise pini bu pinler yandýðýnda göstergede 4 yanýcak
				       break;
		    case 5: 
		    PORTD=
			           0x10  | //4.pin
					   0x40  | //6.pin
					   0x80;   //7.pin
			PORTB=     0x02  | //9.pin
			           0x04  | //10.pin
					   0x20;   //salise pini bu pinler yandýðýnda göstergede 5 yanýcak 	
				       break;
		
		    case 6: 
			PORTD=     0x10  | //4.pin
			           0x40  | //6.pin
					   0x80;   //7.pin
			PORTB=
			           0x02  | //9.pin
					   0x04  | //10.pin
					   0x01  | //8.pin
					   0x20;   //salise pini bu pinler yandýðýnda göstergede 6 yanýcak
				       break;
		    case 7: 
		    PORTD=     0x10  | //4.pin
			           0x20  | //5.pin
					   0x40;   //6.pin
			PORTB=     0x20;   //salise pini bu pinler yandýðýnda göstergede 7 yanýcak		
				       break;
		    case 8: 
		    PORTD=     0x10  | //4.pin
			           0x20  | //5.pin
					   0x40  | //6.pin
					   0x80;   //7.pin
			PORTB=     0x01  | //8.pin
			           0x02  | //9.pin
					   0x04  | //10.pin
					   0x20;   //salise pini bu pinler yandýðýnda göstergede 8 yanýcak
				       break;
		     case 9: 
			 PORTD=    0x10  | //4.pin
			           0x20  | //5.pin
					   0x40  | //6.pin
					   0x80;   //7.pin
			 PORTB=    0x02  | //9.pin
			           0x04  | //10.pin
					   0x20;   //salise pini bu pinler yandýðýnda göstergede 9 yanýcak
				       break;
		
		
			}
    }

    void SaniyeyiYazdir(int segment)// bu fonksiyonda salise fonksiyonu gibi çalýþýr 0 1 2 3 4 5 6 7 8 9 yakmak için port b ye ve port d ye gönderilen pinler aynýdýr yalnýzca saniye biti 0x10 olarak ayarlanmýþtýr
    {
	        switch(segment){
		        case 0:
				
		     PORTD=    0x10 |
		               0x20 |
		               0x40 |
		               0x80 ;
		     PORTB=    0x01 |
		               0x02 |
		               0x10;
		               break;
				
		         case 1:
			 PORTD=    0x20 |
		               0x40;
		     PORTB=    0x10;
		               break;
				
		         case 2:
			 PORTD=    0x10 |
		               0x20 |
		               0x80;
		     PORTB=    0x04 |
		               0x01 |
		               0x10;
		               break;
				
		         case 3:
		     PORTD=    0x10  |
		               0x20  |
		               0x40  |
		               0x80;
		     PORTB=    0x04  |
		               0x10;
		               break;
		        
		          case 4:
		     PORTD=    0x20  |
		               0x40;
		     PORTB=    0x04  |
		               0x02  |
		               0x10;
		               break;
				
		          case 5:
		     PORTD=
		               0x10  |
		               0x40  |
		               0x80;
		     PORTB=    0x02  |
		               0x04  |
		               0x10;
		               break;
		        
		           case 6:
		     PORTD=    0x10  |
		               0x40  |
		               0x80;
		     PORTB=    0x02  |
		               0x04  |
		               0x01  |
		               0x10;
		               break;
				
		            case 7:
		     PORTD=    0x10  |
		               0x20  |
		               0x40;
		     PORTB=    0x10;
		               break;
				
		            case 8:
		     PORTD=    0x10  |
		               0x20  |
		               0x40  |
		               0x80;
		     PORTB=    0x01  |
		               0x02  |
		               0x04  |
		               0x10;
		               break;
				
		             case 9:
		     PORTD=    0x10  |
		               0x20  |
		               0x40  |
		               0x80;
		     PORTB=    0x02  |
		               0x04  |
		               0x10;
		               break;
		        
			}
	        
    }

    void DakikayiYazdir(int segment)// bu fonksiyonda salise fonksiyonu gibi çalýþýr 0 1 2 3 4 5 6 7 8 9 yakmak için port b ye ve port d ye gönderilen pinler aynýdýr yalnýzca saniye biti 0x08 olarak ayarlanmýþtýr
    {
		    switch(segment){
			        case 0: 
			 PORTD=    0x10  |
			           0x20  |
			           0x40  |
			           0x80 ;
			 PORTB=    0x01  |
			           0x02  |
			           0x08;
			           break;
			        
			         case 1:
			 PORTD=    0x20  |
			           0x40;
			 PORTB=    0x08;
			           break;
			        
			         case 2:
			 PORTD=    0x10  |
			           0x20  |
			           0x80;
			 PORTB=    0x04  |
			           0x01  |
			           0x08;
			           break;
			        
			         case 3:
			 PORTD=    0x10  |
			           0x20  |
			           0x40  |
			           0x80;
			 PORTB=    0x04  |
			           0x08;
			           break;
			        
			         case 4:
			 PORTD=    0x20  |
			           0x40;
			 PORTB=    0x04  |
			           0x02  |
			           0x08;
			           break;
			        
			         case 5:
			  PORTD=   0x10  |
			           0x40  |
			           0x80;
			  PORTB=   0x02  |
			           0x04  |
			           0x08;
			           break;
			        
			         case 6:
			  PORTD=   0x10  |
			           0x40  |
			           0x80;
			  PORTB=   0x02  |
			           0x04  |
			           0x01  |
			           0x08;
			           break;
			        
			         case 7:
			  PORTD=   0x10  |
			           0x20  |
			           0x40;
			  PORTB=   0x08;
			           break;
			        
			          case 8:
			  PORTD=   0x10  |
			           0x20  |
			           0x40  |
			           0x80;
			  PORTB=   0x01  |
			           0x02  |
			           0x04  |
			           0x08;
			           break;
			        
			          case 9:
			  PORTD=    0x10  |
			            0x20  |
			            0x40  |
			            0x80;
			  PORTB=    0x02  |
			            0x04  |
			            0x08;
			            break;
			        
			        
			}
    }


