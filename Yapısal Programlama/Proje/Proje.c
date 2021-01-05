#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//malloc larý yap

typedef struct{
	char ad[50];
	char kod[7];
	int kredi;
	int kontenjan;
	int ogrt_id;	
}DERS;

typedef struct{
	char ad[20];
	char soyad[20];
	char unvan[20];
	int id; 
}OGR_UYE;

typedef struct{
	char ad[20];
	char soyad[20];
	char no[11];
	int kredi;
	int ders_no;
}OGRENCI;

typedef struct{
	char no[11];
	char kod[7];
	char ay[3];
	int gun,yil;
	int ID;
	int kayit; // 1 ise kayýtlý,0 ise býraktý
}OGR_DERS;

void ders_ekle();
void ders_sil();
void ders_guncelle();
void uye_ekle();
void uye_sil();
void uye_guncelle();
void ogrenci_ekle();
void ogrenci_sil();
void ogrenci_guncelle(int max_kredi,int max_ders);
void ders_sec(int max_kredi,int max_ders);
void uye_ders_yaz();
void ders_ogr_yaz();
void ogr_ders_yaz();
void derskodu_sinif();

int main(){
	int max_kredi,max_ders;
	int secim=-1;
	printf("Ogrencinin alabilecegi maksimum kredi sayisini giriniz:");
	scanf("%d",&max_kredi);
	printf("Ogrencinin alabilecegi maksimum ders sayisini giriniz:");
	scanf("%d",&max_ders);
	
	printf("-----------------MENU------------\n");
	printf("0:  Cikis\n");
	printf("1:  Ders ekle\n");
	printf("2:  Ders sil\n");
	printf("3:  Ders guncelle\n");
	printf("4:  Ogretim uyesi ekle\n");
	printf("5:  Ogretim uyesi sil\n");
	printf("6:  Ogretim uyesi bilgilerini guncelle\n");
	printf("7:  Ogrenci ekle\n");
	printf("8:  Ogrenci sil\n");
	printf("9:  Ogrenci bilgilerini guncelle\n");
	printf("10: Ogrenci icin ders sec\n");
	printf("11: Ogretim uyesinin verdigi dersleri yazdir\n");
	printf("12: Derse kayitli ogrencileri yazdir\n");
	printf("13: Ogrencinin aldigi dersleri yazdir\n");
	printf("14: DERSKODU_SINIFLISTESI.txt dosyasini yaz\n");
	
	while(secim!=0){
		printf("Secim:");
		scanf("%d",&secim);
		
		if(secim==0) printf("Bay bay.\n");
		else if(secim==1) ders_ekle();
		else if(secim==2) ders_sil();
		else if(secim==3) ders_guncelle();
		else if(secim==4) uye_ekle();
		else if(secim==5) uye_sil();
		else if(secim==6) uye_guncelle();
		else if(secim==7) ogrenci_ekle();
		else if(secim==8) ogrenci_sil();
		else if(secim==9) ogrenci_guncelle(max_kredi,max_ders);
		else if(secim==10) ders_sec(max_kredi,max_ders);
		else if(secim==11) uye_ders_yaz();
		else if(secim==12) ders_ogr_yaz();
		else if(secim==13) ogr_ders_yaz();
		else if(secim==14) derskodu_sinif();
		else printf("Beklenmedik secim, lutfen bir daha deneyin.\n");
	}
	
	return 0;
}

void ders_ekle(){
	
	FILE *fp;
	DERS ders,input;
	
	printf("---------DERS EKLE---------\n");
	printf("Ders adi:");
	scanf("%s",input.ad);
	printf("Ders kodu:");
	scanf("%s",input.kod);
	printf("Ders kredisi:");
	scanf("%d",&input.kredi);
	
	if (input.kredi<0){
		printf("Ders kredisi negatif olamaz.\n");
		return;
	}
	printf("Ders kontenjani:");
	scanf("%d",&input.kontenjan);
	if (input.kredi<0){
		printf("Dersin kontenjani negatif olamaz.\n");
		return;
	}
	printf("Dersi veren ogretim uyesinin ID'si:");
	scanf("%d",&input.ogrt_id);
	
	
	if((fp=fopen("Dersler.txt","a+"))==NULL){
		printf("Dosya acilamadi.\n");
		return;
	}
	
	while (!feof(fp)){
		fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
		if (strcmp(input.ad,ders.ad)==0 || strcmp(input.kod,ders.kod)==0){
			printf("Ayni isimli veya kodlu ders bulunuyor.\n");
			fclose(fp);
			return;
		}
	}
	
	fprintf(fp,"%s %s %d %d %d\n",input.ad,input.kod,input.kredi,input.kontenjan,input.ogrt_id);
	printf("Ders kaydedildi.\n");
	fclose(fp);
}

void ders_sil(){
	FILE *fp;
	DERS ders;
	char kod[7];
	int ders_kontrol=0; // 0 ise ders kayýtlarda bulunmuyor, 1 ise bulunuyor.
	int kredi;
	fp=fopen("Dersler.txt","a+");
	
	if(fp==NULL){
		printf("Dosya acilamadi.\n");
		return;
	}
	
	printf("---------DERS SIL----------\n");
	printf("Silmek istediginiz dersin kodunu giriniz:");
	scanf("%s",kod);
	
	while ((!feof(fp)) && ders_kontrol!=1){
		fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
		
		
		if (strcmp(kod,ders.kod)==0){
			ders_kontrol=1;
			kredi=ders.kredi;
			fclose(fp);
		}
	}
	
	if (ders_kontrol==1){
		char no[11];
		OGR_DERS o_der;
		OGRENCI ogr;
		FILE *fp2,*fp_t2;
		FILE *fp_t=fopen("tmp.txt","w");
		fp=fopen("Dersler.txt","r");
		
		while (!feof(fp)){
			fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
			if (strcmp(kod,ders.kod)!=0){
				fprintf(fp_t,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);	
			}
		}
		fclose(fp);
		fclose(fp_t);
		
		fp=fopen("Dersler.txt","w");
		fp_t=fopen("tmp.txt","r");
		
		while(!feof(fp_t)){
			fscanf(fp_t,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
			fprintf(fp,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
		}
		fclose(fp);
		fclose(fp_t);
		printf("Ders basariyla silindi.\n");
		
		fp=fopen("OgrenciDersKayit.txt","a+");
		fp_t=fopen("tmp.txt","w");
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
			if (strcmp(o_der.kod,kod)==0){
				fp2=fopen("Ogrenciler.txt","a+");
				fp_t2=fopen("tmp2.txt","w");
				strcpy(no,o_der.no);
				
				while (!feof(fp2)){
					fscanf(fp2,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
					if (strcmp(ogr.no,no)==0){
						ogr.ders_no-=1;
						ogr.kredi-=kredi;
					}
					fprintf(fp_t2,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
				}
				fclose(fp2);
				fclose(fp_t2);
				
				fp2=fopen("Ogrenciler.txt","w");
				fp_t2=fopen("tmp2.txt","r");
				while(!feof(fp_t2)){
					fscanf(fp_t2,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
					fprintf(fp2,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
				}
				fclose(fp);
				fclose(fp_t2);
				
			}
			else{
				fprintf(fp_t,"%s %s %d %d %s %d %d\n",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
			}
			
		}
		fclose(fp);
		fclose(fp_t);
		
		fp=fopen("OgrenciDersKayit.txt","w");
		fp_t=fopen("tmp.txt","r");
		while(!feof(fp_t)){
			fscanf(fp_t,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
			fprintf(fp,"%s %s %d %d %s %d %d\n",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
		}
		fclose(fp);
		fclose(fp_t);
		printf("Ogrenciler.txt ve OgrenciDersKayit.txt dosyalari guncellendi.\n");
		
	}
	else{
		fclose(fp);
		printf("Bu kodda bir ders bulunmamaktadir.\n");
	}
	
}

void ders_guncelle(){
	FILE *fp;
	char kod[7];
	DERS ders;
	int ders_kontrol=0;
	
	printf("--------DERS GUNCELLE-----------\n");
	printf("Guncellemek istediginiz dersin kodunu giriniz:");
	scanf("%s",kod);
	
	fp=fopen("Dersler.txt","a+");
	
	while ((!feof(fp)) && ders_kontrol!=1){
		fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
		if (strcmp(kod,ders.kod)==0) ders_kontrol=1;
		
	}
	fclose(fp);
	
	if (ders_kontrol==0){
		printf("Bu kodda bir ders bulunmuyor.\n");
		return;
	}
	
	else{
		char secim[1];
		printf("Dersin hangi ozelligini guncellemek istersiniz?\n");
		printf("0:Ad\n1:Kod\n2:Kredi3:Kontenjan4:Ogretim Uye ID");
		printf("\nSecim:");
		scanf("%s",secim);
		
		if (strcmp(secim,"0")==0){
			char isim[50];
			printf("Dersin yeni ismi:");
			scanf("%s",isim);
			
			fp=fopen("Dersler.txt","r");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				if (strcmp(isim,ders.ad)==0){
					printf("Ayni isimli ders bulunmaktadir.\n");
					fclose(fp);
					return;
				}
			}
			fclose(fp);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Dersler.txt","r");
			
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				if (strcmp(ders.kod,kod)==0){
					strcpy(ders.ad,isim);
				}
				fprintf(fp_t,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				fprintf(fp,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
				
			}
			fclose(fp);
			fclose(fp_t);
			printf("Dersin ismi degistirildi.\n");
					
		}
		
		else if (strcmp(secim,"1")==0){
			char yeni_kod[7];
			printf("Dersin yeni kodu:");
			scanf("%s",yeni_kod);
			
			fp=fopen("Dersler.txt","r");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				if (strcmp(yeni_kod,ders.kod)==0){
					printf("Ayni kodlu ders bulunmaktadir.");
					fclose(fp);
					return;
				}
			}
			fclose(fp);
			OGR_DERS o_der;
			
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Dersler.txt","r");
			
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				if (strcmp(ders.kod,kod)==0){
					strcpy(ders.kod,yeni_kod);
				}
				fprintf(fp_t,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				fprintf(fp,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
				
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("OgrenciDersKayit.txt","a+");
			fp_t=fopen("tmp.txt","w");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
				if (strcmp(o_der.kod,kod)==0) strcpy(o_der.kod,yeni_kod);
				fprintf(fp_t,"%s %s %d %d %s %d %d\n",o_der.no,o_der.kod,o_der.ID,o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("OgrenciDersKayit.txt","w");
			fp_t=fopen("tmp.txt","r");
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
				fprintf(fp,"%s %s %d %d %s %d %d\n",o_der.no,o_der.kod,o_der.ID,o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
			}
			fclose(fp);
			fclose(fp_t);
			
			printf("Dersin kodu degistirildi.\n");
			printf("OgrenciDersKayit.txt dosyasi guncellendi.\n");
			
		}
		else if (strcmp(secim,"2")==0){
			OGR_DERS o_der;
			OGRENCI ogr;
			FILE *fp2;
			int yeni_kredi,kredi;
			char no[11];
			printf("Dersin yeni kredisi:");
			scanf("%d",&yeni_kredi);
			if (kredi<0){
				printf("Dersin kredisi negatif olamaz.\n");
				return;
			}
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Dersler.txt","r");
			
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				if (strcmp(ders.kod,kod)==0){
					kredi=ders.kredi;
					ders.kredi=yeni_kredi;
					
				}
				fprintf(fp_t,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);	
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				fprintf(fp,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
				
			}
			fclose(fp);
			fclose(fp_t);
			printf("Dersin kredisi degistirildi.\n");
			
			yeni_kredi-=kredi;
			
			fp=fopen("OgrenciDersKayit.txt","a+");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
				if (strcmp(o_der.kod,kod)==0){
					fp2=fopen("Ogrenciler.txt","a+");
					fp_t=fopen("tmp.txt","w");
					strcpy(no,o_der.no);
					
					while (!feof(fp2)){
						fscanf(fp2,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
						if (strcmp(ogr.no,no)==0){
							ogr.kredi+=yeni_kredi;
						}
						fprintf(fp_t,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
					}
					fclose(fp2);
					fclose(fp_t);
					
					fp2=fopen("Ogrenciler.txt","w");
					fp_t=fopen("tmp.txt","r");
					while(!feof(fp_t)){
						fscanf(fp_t,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
						fprintf(fp2,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
					}
					fclose(fp2);
					fclose(fp_t);
					
				}
				
			}
			fclose(fp);
			
		
			printf("Ogrenciler.txt dosyasi guncellendi.\n");
			
		}
		else if (strcmp(secim,"3")==0){
			int kontenjan;
			printf("Dersin yeni kontenjani:");
			scanf("%d",&kontenjan);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Dersler.txt","r");
			
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				if (strcmp(ders.kod,kod)==0){
					ders.kontenjan=kontenjan;
				}
				fprintf(fp_t,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);	
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				fprintf(fp,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
				
			}
			fclose(fp);
			fclose(fp_t);
			printf("Dersin kontenjani degistirildi.\n");
				
		}
		
		else if (strcmp(secim,"4")==0){
			int id;
			int count=0;
			printf("Dersi verecek olan ogretim uyesinin ID'si:");
			scanf("%d",&id);
			FILE *fp_o=fopen("Ogretim Uyeleri.txt","r");
			
			if (fp_o==NULL){
				printf("Ogretim Uyeleri dosyasi acilamadi.\n");
				return;
			}
			
			OGR_UYE uye;
			while(!feof(fp_o)){
				fscanf(fp_o,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
				if(uye.id==id){
					count++;
				}
			}
			fclose(fp_o);
			if (count==0){
				printf("Boyle bir ogretim uyesi bulunmamaktadir.\n");
				return;
			}
			else{
				FILE *fp_t=fopen("tmp.txt","w");
				fp=fopen("Dersler.txt","r");
				
				while(!feof(fp)){
					fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
					if (strcmp(ders.kod,kod)==0){
						ders.ogrt_id=id;
					}
					fprintf(fp_t,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);	
				}
				fclose(fp);
				fclose(fp_t);
				
				fp=fopen("Dersler.txt","w");
				fp_t=fopen("tmp.txt","r");
				
				while(!feof(fp_t)){
					fscanf(fp_t,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
					fprintf(fp,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
				}
				fclose(fp);
				fclose(fp_t);
				printf("ID degistirildi.\n");
				
			}
		
		
		}
		else printf("Beklenmedik karakter.\n");	
	}	
	
}
void uye_ekle(){
	OGR_UYE uye,input;
	FILE *fp;
	
	printf("----------------OGRETIM UYESI EKLE---------------\n");
	printf("Ogretim uyesi adi:");
	scanf("%s",input.ad);
	printf("Ogretim uyesi soyadi:");
	scanf("%s",input.soyad);
	printf("Ogretim uyesi unvani:");
	scanf("%s",input.unvan);
	printf("Ogretim uyesi ID'si:");
	scanf("%d",&input.id);
	
	fp=fopen("Ogretim Uyeleri.txt","a+");
	while(!feof(fp)){
		fscanf(fp,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
		if(input.id==uye.id){
			printf("Ayni ID'li baska bir ogretim gorevlisi bulunmaktadir.");
			fclose(fp);
			return;
		}
	}
	fprintf(fp,"%s %s %s %d\n",input.ad,input.soyad,input.unvan,input.id);
	fclose(fp);
	printf("Ogretim uyesi eklendi.\n");
}
void uye_sil(){
	int id;
	int uye_kontrol=0; // 0 ise üye kayýtlý deðil,1 ise kayýtlý
	FILE *fp;
	OGR_UYE uye;
	
	printf("------------OGRETIM UYESI SILME--------------\n");
	printf("Silmek istediginiz ogretim uyesinin ID'sini giriniz:");
	scanf("%d",&id);
	
	fp=fopen("Ogretim Uyeleri.txt","a+");
	while((!feof(fp)) && uye_kontrol!=1){
		fscanf(fp,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
		
		if (id==uye.id){
			uye_kontrol=1;
			fclose(fp);
		}	
	}
	if (uye_kontrol==1){
		fp=fopen("Dersler.txt","a+");
		FILE *fp_t=fopen("tmp.txt","w");
		FILE *fp2;
		DERS ders;
		int yeni_id;
		int kontrol;
		
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
			if (id==ders.ogrt_id){
				printf("%s kodlu dersi yeni verecek olan ogretim uyesinin ID'sini giriniz:",ders.kod);
				scanf("%d",&yeni_id);
				fp2=fopen("Ogretim Uyeleri.txt","r");
				kontrol=0;
				while((!feof(fp2)) && kontrol!=1){
					fscanf(fp2,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
					if (yeni_id==uye.id){
						kontrol=1;
					}
				}
				fclose(fp2);
				if (kontrol==0){
					printf("Boyle ID'li bir ogretim elemani bulunmuyor.\n");
					fclose(fp_t);
					fclose(fp);
					return;
				}
				ders.ogrt_id=yeni_id;
				
			}
			fprintf(fp_t,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
		}
		fclose(fp_t);
		fclose(fp);
		
		fp=fopen("Dersler.txt","w");
		fp_t=fopen("tmp.txt","r");
		while(!feof(fp_t)){
			fscanf(fp_t,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
			fprintf(fp,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
		}
		fclose(fp);
		fclose(fp_t);
		printf("Dersler.txt dosyasi guncellendi.\n");
		
		
		fp_t=fopen("tmp.txt","w");
		fp=fopen("Ogretim Uyeleri.txt","r");
		
		
		while (!feof(fp)){
			fscanf(fp,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
			if (id!=uye.id){
				fprintf(fp_t,"%s %s %s %d\n",uye.ad,uye.soyad,uye.unvan,uye.id);	
			}
		}
		fclose(fp);
		fclose(fp_t);
		
		fp=fopen("Dersler.txt","w");
		fp_t=fopen("tmp.txt","r");
		
		while(!feof(fp_t)){
			fscanf(fp_t,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
			fprintf(fp,"%s %s %s %d\n",uye.ad,uye.soyad,uye.unvan,uye.id);
		}
		fclose(fp);
		fclose(fp_t);
		printf("Ogretim uyesi basariyla silindi.\n");
	}
	else{
		fclose(fp);
		printf("Bu ID'li bir ogretim elemani bulunmamaktadir.\n");
	}
}
void uye_guncelle(){
	int id;
	int uye_kontrol=0;
	FILE *fp;
	OGR_UYE uye;
	
	
	printf("-----------------OGRETIM UYESI GUNCELLE-------------------\n");
	printf("Bilgilerini guncellemek istediginiz ogretim uyesinin ID'sini yaziniz:");
	scanf("%d",&id);
	
	
	fp=fopen("Ogretim Uyeleri.txt","a+");
	while((!feof(fp)) && uye_kontrol!=1){
		fscanf(fp,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
		if (id==uye.id) uye_kontrol=1;
	}
	fclose(fp);
	
	if (uye_kontrol==0){
		printf("Bu ID'de bir ogretim uyesi bulunmamaktadir.\n");
		return;
	}
	
	else{
		char secim[1];
		
		printf("Ogretim uyesinin hangi bilgisini guncellemek istersiniz?\n");
		printf("0:Unvan\n1:ID");
		printf("\nSecim:");
		scanf("%s",secim);
		
		if (strcmp(secim,"0")){
			char unvan[20];
			printf("Ogretim uyesinin yeni unvani:");
			scanf("%s",unvan);
			
			fp=fopen("Ogretim Uyeleri.txt","r");
			while(!feof(fp)){
				fscanf(fp,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
				if (strcmp(unvan,uye.unvan)==0){
					printf("Ayni unvani girdiniz.\n");
					fclose(fp);
					return;
				}
			}
			fclose(fp);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Ogretim Uyeleri.txt","r");
			
			while(!feof(fp)){
				fscanf(fp,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
				if (id==uye.id){
					strcpy(uye.unvan,unvan);
				}
				fprintf(fp_t,"%s %s %s %d\n",uye.ad,uye.soyad,uye.unvan,uye.id);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Ogretim Uyeleri.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
				fprintf(fp,"%s %s %s %d\n",uye.ad,uye.soyad,uye.unvan,uye.id);
				
			}
			fclose(fp);
			fclose(fp_t);
			printf("Unvan degistirildi.\n");	
		}
		else if (strcmp(secim,"1")){
			int yeni_id;
			DERS ders;
			printf("Ogretim uyesinin yeni ID'si:");
			scanf("%d",&yeni_id);
			
			fp=fopen("Ogretim Uyeleri.txt","r");
			while(!feof(fp)){
				fscanf(fp,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
				if (yeni_id==uye.id){
					printf("Boyle bir ID bulunuyor.\n");
					fclose(fp);
					return;
				}
			}
			fclose(fp);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Ogretim Uyeleri.txt","r");
			
			while(!feof(fp)){
				fscanf(fp,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
				if (id==uye.id){
					uye.id=yeni_id;
				}
				fprintf(fp_t,"%s %s %s %d\n",uye.ad,uye.soyad,uye.unvan,uye.id);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Ogretim Uyeleri.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
				fprintf(fp,"%s %s %s %d\n",uye.ad,uye.soyad,uye.unvan,uye.id);
				
			}
			fclose(fp);
			fclose(fp_t);
			printf("ID degistirildi.\n");
			
			fp=fopen("Dersler.txt","a+");
			fp_t=fopen("tmp.txt","w");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				if(ders.ogrt_id==id){
					ders.ogrt_id=yeni_id;
				}
				fprintf(fp_t,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				fprintf(fp,"%s %s %d %d %d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
			}
			fclose(fp);
			fclose(fp_t);
			printf("Dersler.txt dosyasi guncellendi.\n");
				
		}
		
		else{
			printf("Beklenmedik karakter.\n");
		}
		
	}	
}
void ogrenci_ekle(){
	FILE *fp;
	OGRENCI ogr,input;
	
	printf("------------OGRENCI EKLE-----------------\n");
	printf("Ogrenci adi:");
	scanf("%s",input.ad);
	printf("Ogrenci soyadi:");
	scanf("%s",input.soyad);
	printf("Ogrenci no:");
	scanf("%s",input.no);
	
	if((fp=fopen("Ogrenciler.txt","a+"))==NULL){
		printf("Dosya acilamadi.\n");
		return;
	}
	
	while (!feof(fp)){
		fscanf(fp,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
		if (strcmp(input.no,ogr.no)==0){
			printf("Ayni numarali ogrenci bulunuyor.\n");
			fclose(fp);
			return;
		}
	}
	
	fprintf(fp,"%s %s %s %d %d\n",input.ad,input.soyad,input.no,0,0);
	printf("Ogrenci kaydedildi.\n");
	fclose(fp);
}
void ogrenci_sil(){
	FILE *fp;
	OGRENCI ogr;
	char no[11];
	int ogr_kontrol=0; // 0 ise öðrenci kayýtlarda bulunmuyor, 1 ise bulunuyor.
	fp=fopen("Ogrenciler.txt","a+");
	
	if(fp==NULL){
		printf("Dosya acilamadi.\n");
		return;
	}
	
	printf("---------OGRENCI SIL----------\n");
	printf("Silmek istediginiz ogrencinin numarasini giriniz:");
	scanf("%s",no);
	
	while ((!feof(fp)) && ogr_kontrol!=1){
		fscanf(fp,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
		
		if (strcmp(no,ogr.no)==0){
			ogr_kontrol=1;
			fclose(fp);
		}
	}
	
	if (ogr_kontrol==1){
		FILE *fp_t=fopen("tmp.txt","w");
		fp=fopen("Ogrenciler.txt","r");
		OGR_DERS o_der;
		
		while (!feof(fp)){
			fscanf(fp,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
			if (strcmp(no,ogr.no)!=0){
				fprintf(fp_t,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
			}
			

		}
		fclose(fp);
		fclose(fp_t);
		
		fp=fopen("Ogrenciler.txt","w");
		fp_t=fopen("tmp.txt","r");
		
		while(!feof(fp_t)){
			fscanf(fp_t,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
			fprintf(fp,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
		}
		fclose(fp);
		fclose(fp_t);
		printf("Ogrenci basariyla silindi.\n");
		
		fp=fopen("OgrenciDerskayit.txt","a+");
		fp_t=fopen("tmp.txt","w");
		
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
			if (strcmp(o_der.no,no)!=0){
				fprintf(fp_t,"%s %s %d %d %s %d %d\n",o_der.no,o_der.kod,o_der.ID,o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
			}
		}
		fclose(fp);
		fclose(fp_t);
		
		fp=fopen("OgrenciDersKayit.txt","w");
		fp_t=fopen("tmp.txt","r");
		while(!feof(fp_t)){
			fscanf(fp_t,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
			fprintf(fp,"%s %s %d %d %s %d %d\n",o_der.no,o_der.kod,o_der.ID,o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
		}
		fclose(fp);
		fclose(fp_t);
		printf("OgrenciDersKayit.txt dosyasi guncellendi.\n");
	}
	else{
		fclose(fp);
		printf("Bu numarada bir ogrenci bulunmamaktadir.\n");
	}	
}
void ogrenci_guncelle(int max_kredi,int max_ders){
	
	FILE *fp;
	char no[11];
	OGRENCI ogr;
	OGR_DERS o_der;
	DERS ders;
	int ogr_kontrol=0;
	
	printf("--------OGRENCI GUNCELLE-----------\n");
	printf("Guncellemek istediginiz ogrencinin numarasini giriniz:");
	scanf("%s",no);
	
	fp=fopen("Ogrenciler.txt","a+");
	
	while ((!feof(fp)) && ogr_kontrol!=1){
		fscanf(fp,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
		if (strcmp(no,ogr.no)==0) ogr_kontrol=1;
		
	}
	fclose(fp);
	
	if (ogr_kontrol==0){
		printf("Bu numarada bir ogrenci bulunmuyor.\n");
		return;
	}
	
	else{
		char secim[1];
		printf("Ogrencinin hangi ozelligini guncellemek istersiniz?\n");
		printf("0:No\n1:Ders durumu");
		printf("\nSecim:");
		scanf("%s",secim);
		
		if(strcmp(secim,"0")==0){
			char yeni_no[11];
			printf("Ogrencinin yeni numarasi:");
			scanf("%s",yeni_no);
			
			fp=fopen("Ogrenciler.txt","r");
			while(!feof(fp)){
				fscanf(fp,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
				if (strcmp(yeni_no,ogr.no)==0){
					printf("Ayni numarali ogrenci bulunmaktadir.\n");
					fclose(fp);
					return;
				}
			}
			fclose(fp);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Ogrenciler.txt","r");
			
			while(!feof(fp)){
				fscanf(fp,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
				if (strcmp(ogr.no,no)==0){
					strcpy(ogr.no,yeni_no);
				}
				fprintf(fp_t,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Ogrenciler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
				fprintf(fp,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
				
			}
			fclose(fp);
			fclose(fp_t);
			printf("Ogrencinin numarasi degistirildi.\n");
			
			fp=fopen("OgrenciDersKayit.txt","a+");
			fp_t=fopen("tmp.txt","w");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
				if (strcmp(no,o_der.no)==0){
					strcpy(o_der.no,yeni_no);
				}
				fprintf(fp_t,"%s %s %d %d %s %d %d\n",o_der.no,o_der.kod,o_der.ID,o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("OgrenciDersKayit.txt","w");
			fp_t=fopen("tmp.txt","r");
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
				fprintf(fp,"%s %s %d %d %s %d %d\n",o_der.no,o_der.kod,o_der.ID,o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
			}
			fclose(fp);
			fclose(fp_t);
			printf("OgrenciDersKayit.txt dosyasi guncellendi.\n");		
		}
		else if (strcmp(secim,"1")==0){
			char kod[7];
			int ders_kontrol=0;
			
			printf("Ogrencinin aldigi dersin kodunu giriniz:");
			scanf("%s",kod);
			fp=fopen("OgrenciDersKayit.txt","a+");
			
			while((!feof(fp)) && ders_kontrol!=1){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
				if (strcmp(kod,o_der.kod)==0 && strcmp(no,o_der.no)==0){
					ders_kontrol=1;
				}
			}
			fclose(fp);
			if (ders_kontrol==0){
				printf("Hata.Ogrenciyle ders uyusmuyor.\n");
				return;
			}
			
			else{
				FILE *fp_t;
				FILE *fp2,*fp_t2;
				int kontrol,kredi;
				fp=fopen("OgrenciDersKayit.txt","a+");
				fp_t=fopen("tmp.txt","w");
				
				
				while(!feof(fp)){
					fscanf(fp,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
					if (strcmp(kod,o_der.kod)==0 && strcmp(no,o_der.no)==0){
						
						kontrol=0;
						
						fp2=fopen("Dersler.txt","r");
						while(!feof(fp2) && kontrol!=1){
							fscanf(fp2,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
							if (strcmp(ders.kod,kod)==0){
								kredi=ders.kredi;
								kontrol=1;
							}
						}
						fclose(fp2);
						kontrol=0;
						
						if (o_der.kayit==0){
							fp2=fopen("Ogrenciler.txt","r");
							fp_t2=fopen("tmp2.txt","w");
							while(!feof(fp2)){
								fscanf(fp2,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
								if (strcmp(no,ogr.no)==0){
									if ((ogr.kredi+kredi)>max_kredi || (ogr.ders_no+1)>max_ders){
										printf("Maksimum kredi veya ders sayisini asamazsiniz.\n");
										fclose(fp_t2);
										fclose(fp2);
										return;
									}
									ogr.kredi+=kredi;
									ogr.ders_no+=1;
								}
								fprintf(fp_t2,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
								
							}
							fclose(fp2);
							fclose(fp_t2);
							
							fp2=fopen("Ogrenciler.txt","w");
							fp_t2=fopen("tmp2.txt","r");
							while(!feof(fp_t2)){
								fscanf(fp_t2,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
								fprintf(fp2,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
							}	
							fclose(fp2);
							fclose(fp_t2);
							printf("Ogrenciler.txt dosyasi guncellendi.\n");
							
							o_der.kayit=1;
							kontrol=1;	
							
						}
						else if (o_der.kayit==1 && kontrol==0){
							fp2=fopen("Ogrenciler.txt","r");
							fp_t2=fopen("tmp2.txt","w");
							
							while(!feof(fp2)){
								fscanf(fp2,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
								if (strcmp(no,ogr.no)==0){
									ogr.kredi-=kredi;
									ogr.ders_no-=1;
								}
								fprintf(fp_t2,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
							}
							fclose(fp2);
							fclose(fp_t2);
							
							fp2=fopen("Ogrenciler.txt","w");
							fp_t2=fopen("tmp2.txt","r");
							while(!feof(fp_t2)){
								fscanf(fp_t2,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
								fprintf(fp2,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
							}	
							fclose(fp2);
							fclose(fp_t2);
							printf("Ogrenciler.txt dosyasi guncellendi.\n");
							
							o_der.kayit=0;
							
						}
					}
					fprintf(fp_t,"%s %s %d %d %s %d %d\n",o_der.no,o_der.kod,o_der.ID,o_der.kayit,o_der.ay,o_der.gun,o_der.yil);	
				}
				fclose(fp);
				fclose(fp_t);
				
				fp=fopen("OgrenciDersKayit.txt","w");
				fp_t=fopen("tmp.txt","r");
				while(!feof(fp_t)){
					fscanf(fp_t,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
					fprintf(fp,"%s %s %d %d %s %d %d\n",o_der.no,o_der.kod,o_der.ID,o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
				}
				
				printf("Ogrencinin ders durumu degistirildi.\n");
			}
				
		}
		else{
			printf("Beklenmedik karakter.\n");
		}
	}	
}
void ders_sec(int max_kredi,int max_ders){
	char no[11];
	FILE *fp;
	OGRENCI ogr;
	int ogr_kontrol=0;
	
	printf("---------------DERS SECME--------------\n");
	printf("Ogrencinin numarasini giriniz:");
	scanf("%s",no);
	
	fp=fopen("Ogrenciler.txt","a+");
	while ((!feof(fp)) && ogr_kontrol!=1){
		fscanf(fp,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
		if (strcmp(no,ogr.no)==0) ogr_kontrol=1;
		
	}
	fclose(fp);
	
	if (ogr_kontrol==0){
		printf("Bu numarada bir ogrenci bulunmuyor.\n");
		return;
	}
	else{
		char kod[7];
		DERS ders;
		int ders_kontrol=0;
		printf("Secmek istediginiz dersin kodunu giriniz:\n");
		scanf("%s",kod);
		
		fp=fopen("Dersler.txt","a+");
		
		while((!feof(fp)) && ders_kontrol!=1){
			fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
			if (strcmp(kod,ders.kod)==0) ders_kontrol=1;
		}
		fclose(fp);
		if (ders_kontrol==0){
			printf("Bu kodda bir ders bulunmuyor.\n");
			return;
		}
		else{
			int ders_kredi,ders_kont,ogr_kredi,ogr_ders,current_id,kon_counter=0;
			OGR_DERS o_der;
			
			fp=fopen("Dersler.txt","a+");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
				if (strcmp(ders.kod,kod)==0){
					ders_kredi=ders.kredi;
					ders_kont=ders.kontenjan;
				} 
			}
			fclose(fp);
			
			fp=fopen("Ogrenciler.txt","a+");
			while(!feof(fp)){
				fscanf(fp,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
				if (strcmp(ogr.no,no)==0){
					ogr_kredi=ogr.kredi;
					ogr_ders=ogr.ders_no;
				}
			}
			fclose(fp);
			
			fp=fopen("OgrenciDersKayit.txt","a+");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
				if (strcmp(kod,o_der.kod)==0 && o_der.kayit==1) kon_counter++;
				}
			fclose(fp);
			
			
			if ((ogr_kredi+ders_kredi)<=max_kredi && (ogr_ders<max_ders && kon_counter<ders_kont) ){
				FILE *fp_t;
				
				fp=fopen("OgrenciDersKayit.txt","a+");
				while(!feof(fp)){
					fscanf(fp,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
					current_id=o_der.ID;
				}
				fprintf(fp,"%s %s %d %d %s %d %d\n",no,kod,current_id+1,1,__DATE__);
				fclose(fp);
				
				fp=fopen("Ogrenciler.txt","a+");
				fp_t=fopen("tmp.txt","w");
				while(!feof(fp)){
					fscanf(fp,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
					if (strcmp(no,ogr.no)==0){
						ogr.kredi+=ders_kredi;
						ogr.ders_no+=1;
					}
					fprintf(fp_t,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
				}
				fclose(fp);
				fclose(fp_t);
				
				fp=fopen("Ogrenciler.txt","w");
				fp_t=fopen("tmp.txt","r");
				
				while(!feof(fp_t)){
					fscanf(fp_t,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
					fprintf(fp,"%s %s %s %d %d\n",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
				}
				fclose(fp);
				fclose(fp_t);
				printf("Ders secildi.\n");
				printf("Ogrenciler.txt dosyasi guncellendi.\n");
				
			}
			else{
				printf("Dersi secilemedi.\n");
			}
			
		}
	}	
}
void uye_ders_yaz(){
	FILE *fp;
	DERS ders;
	OGR_UYE uye;
	int id;
	int kontrol=0;
	
	printf("Ogretim uyesinin ID'sini giriniz:");
	scanf("%d",&id);
	
	fp=fopen("Ogretim Uyeleri.txt","a+");
	while((!feof(fp)) && kontrol!=1){
		fscanf(fp,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
		if (id==uye.id) {
		kontrol=1;}
	}
	fclose(fp);
	if (kontrol==0){
		printf("Boyle bir ogretim uyesi bulunmamaktadir.\n");
		return;
	}
	else{
		DERS ders;
		printf("-------------OGRETIM UYESININ VERDIGI DERSLER------------\n");
		fp=fopen("Dersler.txt","a+");
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
			if(id==ders.ogrt_id){
				printf("Ders Adi:%s  Ders Kodu:%s   Ders Kredisi:%d     Ders Kontenjani:%d\n",ders.ad,ders.kod,ders.kredi,ders.kontenjan);
			}
		}
		fclose(fp);
		
	}
}
void ders_ogr_yaz(){
	FILE *fp;
	DERS ders;
	char kod[7];
	int kontrol=0;
	
	printf("Ders kodunu giriniz:");
	scanf("%s",kod);
	
	fp=fopen("Dersler.txt","a+");
	while((!feof(fp)) && kontrol!=1){
		fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
		if (strcmp(kod,ders.kod)==0) kontrol=1;
	}
	fclose(fp);
	if (kontrol==0){
		printf("Boyle bir ders bulunmuyor.\n");
		return;
	}
	else{
		FILE *fp2;
		OGR_DERS o_der;
		OGRENCI ogr;
		fp=fopen("OgrenciDersKayit.txt","a+");
		printf("---------------DERSI ALAN OGRENCÝLER---------------\n");
		
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
			if (strcmp(kod,o_der.kod)==0){
				fp2=fopen("Ogrenciler.txt","a+");
				while(!feof(fp2)){
					fscanf(fp2,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
					if(strcmp(o_der.no,ogr.no)==0 && o_der.kayit==1){
						printf("Ogrenci Adi:%s   Ogrenci Soyadi:%s    Ogrenci No:%s      Ogrencinin Aldigi Kredi Sayisi:%d    Ogrencinin Aldigi Ders Sayisi:%d\n",
								ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no);
					}
				}
				fclose(fp2);
			}
		}
		fclose(fp);
	}
	
}

void ogr_ders_yaz(){
	char no[11];
	OGRENCI ogr;
	FILE *fp;
	int kontrol=0;
	
	fp=fopen("Ogrenciler.txt","a+");
	while((!feof(fp)) && kontrol!=1){
		fscanf(fp,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
		if (strcmp(ogr.no,no)==0) kontrol=1;
	}
	fclose(fp);
	
	if (kontrol==0){
		printf("Boyle bir ogrenci bulunmuyor.\n");
		return;
	}
	else{
		OGR_DERS o_der;
		DERS ders;
		FILE *fp2;
		fp=fopen("OgrenciDersKayit.txt","a+");
		printf("---------OGRENCININ ALDIGI DERSLER--------------\n");
		while (!feof(fp)){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
			if (strcmp(o_der.no,no)==0 && o_der.kayit==1){
				fp2=fopen("Dersler.txt","a+");
				while(!feof(fp2)){
					fscanf(fp2,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
					if (strcmp(ders.kod,o_der.kod)==0){
						printf("Ders Adi:%s    Ders Kodu:%s        Ders Kredisi:%d          Ders Kontenjani:%d        Dersi Veren Ogretim Uyesinin ID'si:%d\n",
								ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id);
					}
				}
				fclose(fp2);
			}
		}
		fclose(fp);
	}
	
	
}

void derskodu_sinif(){
	int id;
	FILE *fp;
	OGR_UYE uye;
	int kontrol=0;
	
	printf("Ogretim uyesinin ID'sini giriniz:");
	scanf("%d",&id);
	fp=fopen("Ogretim Uyeleri.txt","a+");
	while((!feof(fp)) && kontrol!=1){
		fscanf(fp,"%s %s %s %d",uye.ad,uye.soyad,uye.unvan,&uye.id);
		if (id==uye.id) kontrol=1;
	}
	
	fclose(fp);
	if (kontrol==0){
		printf("Boyle bir ogretim uyesi bulunmamaktadir.\n");
		return;
	}
	
	else{
		DERS ders;
		FILE *fp2,*fp3,*fp4;
		OGR_DERS o_der;
		OGRENCI ogr;
		char dosya[24];
		fp=fopen("Dersler.txt","a+");
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id);
			if(id==ders.ogrt_id){
				strcpy(dosya,ders.kod);
				strcat(dosya,"_SINIFLISTESI.txt");
				fp4=fopen(dosya,"w");
				fp2=fopen("OgrenciDersKayit.txt","a+");
				while(!feof(fp2)){
					fscanf(fp2,"%s %s %d %d %s %d %d",o_der.no,o_der.kod,&o_der.ID,&o_der.kayit,o_der.ay,o_der.gun,o_der.yil);
					if(strcmp(ders.kod,o_der.kod)==0 && o_der.kayit==1){
						fp3=fopen("Ogrenciler.txt","a+");
						while(!feof(fp3)){
							fscanf(fp3,"%s %s %s %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no);
							if (strcmp(o_der.no,ogr.no)==0){
								fprintf(fp4,"%s %s %s\n",ogr.ad,ogr.soyad,ogr.no);
							}
						}
						fclose(fp3);
					}
					
				}
				fclose(fp2);
				fclose(fp4);
			}
	
		}
		fclose(fp);
		printf("Dosyalar olusturuldu.\n");
	}
	
}












