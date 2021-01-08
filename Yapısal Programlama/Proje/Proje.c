#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
	DERS *ders=(DERS*)malloc(sizeof(DERS));
	DERS *input=(DERS*)malloc(sizeof(DERS));
	int i;
	int satir=-1;
	
	printf("---------DERS EKLE---------\n");
	printf("Ders adi:");
	scanf("%s",input[0].ad);
	printf("Ders kodu:");
	scanf("%s",input[0].kod);
	printf("Ders kredisi:");
	scanf("%d",&input[0].kredi);
	
	if (input[0].kredi<0){
		printf("Ders kredisi negatif olamaz.\n");
		free(ders);
		free(input);
		return;
	}
	printf("Ders kontenjani:");
	scanf("%d",&input[0].kontenjan);
	if (input[0].kredi<0){
		printf("Dersin kontenjani negatif olamaz.\n");
		free(ders);
		free(input);
		return;
	}
	printf("Dersi veren ogretim uyesinin ID'si:");
	scanf("%d",&input[0].ogrt_id);
	
	
	if((fp=fopen("Dersler.txt","a+"))==NULL){
		printf("Dosya acilamadi.\n");
		free(ders);
		free(input);
		return;
	}
	
	while (!feof(fp)){
		fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
		satir++;
		
	}
	fclose(fp);
	fp=fopen("Dersler.txt","a+");
	for(i=0;i<satir;i++){
		fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
		if (strcmp(input[0].ad,ders[0].ad)==0 || strcmp(input[0].kod,ders[0].kod)==0){
			printf("Ayni isimli veya kodlu ders bulunuyor.\n");
			free(ders);
			free(input);
			fclose(fp);
			return;
		}
	}
	fclose(fp);
	fp=fopen("Dersler.txt","a+");
	
	fprintf(fp,"%s %s %d %d %d\n",input[0].ad,input[0].kod,input[0].kredi,input[0].kontenjan,input[0].ogrt_id);
	printf("Ders kaydedildi.\n");
	fclose(fp);
	free(ders);
	free(input);
}

void ders_sil(){
	FILE *fp;
	DERS *ders=(DERS*)malloc(sizeof(DERS));
	char *kod=(char*)malloc(7*sizeof(char));
	int ders_kontrol=0; // 0 ise ders kayýtlarda bulunmuyor, 1 ise bulunuyor.
	int kredi;
	fp=fopen("Dersler.txt","a+");
	int i,satir=-1;
	
	if(fp==NULL){
		printf("Dosya acilamadi.\n");
		free(ders);
		free(kod);
		return;
	}
	
	printf("---------DERS SIL----------\n");
	printf("Silmek istediginiz dersin kodunu giriniz:");
	scanf("%s",kod);
	
	while(!feof(fp)){
		fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
		satir++;
	}
	fclose(fp);
	fp=fopen("Dersler.txt","a+");
	
	for (i=0;i<satir && ders_kontrol!=1;i++){
		fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
		
		
		if (strcmp(kod,ders[0].kod)==0){
			ders_kontrol=1;
			kredi=ders[0].kredi;
			fclose(fp);
		}
	}
	
	if (ders_kontrol==1){
		char *no=(char*)malloc(11*sizeof(char));
		OGR_DERS *o_der=(OGR_DERS*)malloc(sizeof(OGR_DERS));
		OGRENCI *ogr=(OGRENCI*)malloc(sizeof(OGRENCI));
		FILE *fp2,*fp_t2;
		FILE *fp_t=fopen("tmp.txt","w");
		fp=fopen("Dersler.txt","r");
		
		for (i=0;i<satir;i++){
			fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			if (strcmp(kod,ders[0].kod)!=0){
				fprintf(fp_t,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);	
			}
		}
		fclose(fp);
		fclose(fp_t);
		
		fp=fopen("Dersler.txt","w");
		fp_t=fopen("tmp.txt","r");
		satir=-1;
		while(!feof(fp_t)){
			fscanf(fp_t,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			satir++;
		}
		fclose(fp_t);
		fp_t=fopen("tmp.txt","r");
		
		for(i=0;i<satir;i++){
			fscanf(fp_t,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			fprintf(fp,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
		}
		fclose(fp);
		fclose(fp_t);
		printf("Ders basariyla silindi.\n");
		
		satir=-1;
		int satir2=-1;
		int j;
		
		fp=fopen("OgrenciDersKayit.txt","a+");
		fp_t=fopen("tmp.txt","w");
		
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			satir++;
		}
		fclose(fp);
		fp2=fopen("Ogrenciler.txt","a+");
		while(!feof(fp)){
			fscanf(fp2,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
			satir2++;
		}
		fclose(fp2);
		
		fp=fopen("OgrenciDersKayit.txt","a+");
		for(i=0;i<satir;i++){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			if (strcmp(o_der[0].kod,kod)==0){
				fp2=fopen("Ogrenciler.txt","a+");
				fp_t2=fopen("tmp2.txt","w");
				strcpy(no,o_der[0].no);
				
				for (j=0;j<satir2;j++){
					fscanf(fp2,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
					if (strcmp(ogr[0].no,no)==0){
						ogr[0].ders_no-=1;
						ogr[0].kredi-=kredi;
					}
					fprintf(fp_t2,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
				}
				fclose(fp2);
				fclose(fp_t2);
				
				fp2=fopen("Ogrenciler.txt","w");
				fp_t2=fopen("tmp2.txt","r");
				for(j=0;j<satir2;j++){
					fscanf(fp_t2,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
					fprintf(fp2,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
				}
				fclose(fp);
				fclose(fp_t2);
				
			}
			else{
				fprintf(fp_t,"%s %s %d %d %s %d %d\n",o_der[0].no,o_der[0].kod,o_der[0].ID,o_der[0].kayit,o_der[0].ay,o_der[0].gun,o_der[0].yil);
			}
			
		}
		fclose(fp);
		fclose(fp_t);
		
		fp=fopen("OgrenciDersKayit.txt","w");
		fp_t=fopen("tmp.txt","r");
		for(i=0;i<satir;i++){
			fscanf(fp_t,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			fprintf(fp,"%s %s %d %d %s %d %d\n",o_der[0].no,o_der[0].kod,o_der[0].ID,o_der[0].kayit,o_der[0].ay,o_der[0].gun,o_der[0].yil);
		}
		fclose(fp);
		fclose(fp_t);
		printf("Ogrenciler.txt ve OgrenciDersKayit.txt dosyalari guncellendi.\n");
		
		free(no);
		free(o_der);
		free(ogr);
		
	}
	else{
		fclose(fp);
		printf("Bu kodda bir ders bulunmamaktadir.\n");
	}
	free(ders);
	free(kod);
}

void ders_guncelle(){
	FILE *fp;
	char *kod=(char*)malloc(7*sizeof(char));
	DERS *ders=(DERS*)malloc(sizeof(DERS));
	int ders_kontrol=0;
	int i;
	int satir=-1;
	
	printf("--------DERS GUNCELLE-----------\n");
	printf("Guncellemek istediginiz dersin kodunu giriniz:");
	scanf("%s",kod);
	
	fp=fopen("Dersler.txt","a+");
	while(!feof(fp)){
		fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
		satir++;
	}
	fclose(fp);
	fp=fopen("Dersler.txt","a+");
	
	for(i=0;i<satir && ders_kontrol!=1;i++){
		fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
		if (strcmp(kod,ders[0].kod)==0) ders_kontrol=1;
		
	}
	fclose(fp);
	
	if (ders_kontrol==0){
		printf("Bu kodda bir ders bulunmuyor.\n");
		free(kod);
		free(ders);
		return;
	}
	
	else{
		char *secim=(char*)malloc(sizeof(char));
		printf("Dersin hangi ozelligini guncellemek istersiniz?\n");
		printf("0:Ad\n1:Kod\n2:Kredi3:Kontenjan4:Ogretim Uye ID");
		printf("\nSecim:");
		scanf("%s",secim);
		
		if (strcmp(secim,"0")==0){
			char *isim=(char*)malloc(50*sizeof(char));
			printf("Dersin yeni ismi:");
			scanf("%s",isim);
			
			fp=fopen("Dersler.txt","r");
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				if (strcmp(isim,ders[0].ad)==0){
					printf("Ayni isimli ders bulunmaktadir.\n");
					free(kod);
					free(ders);
					free(secim);
					free(isim);
					fclose(fp);
					return;
				}
			}
			fclose(fp);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Dersler.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				if (strcmp(ders[0].kod,kod)==0){
					strcpy(ders[0].ad,isim);
				}
				fprintf(fp_t,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp_t,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				fprintf(fp,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
				
			}
			fclose(fp);
			fclose(fp_t);
			printf("Dersin ismi degistirildi.\n");
			free(isim);
					
		}
		
		else if (strcmp(secim,"1")==0){
			char *yeni_kod=(char*)malloc(7*sizeof(char));
			printf("Dersin yeni kodu:");
			scanf("%s",yeni_kod);
			
			fp=fopen("Dersler.txt","r");
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				if (strcmp(yeni_kod,ders[0].kod)==0){
					printf("Ayni kodlu ders bulunmaktadir.");
					fclose(fp);
					free(yeni_kod);
					free(kod);
					free(ders);
					return;
				}
			}
			fclose(fp);
			OGR_DERS *o_der=(OGR_DERS*)malloc(sizeof(OGR_DERS));
			
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Dersler.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				if (strcmp(ders[0].kod,kod)==0){
					strcpy(ders[0].kod,yeni_kod);
				}
				fprintf(fp_t,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp_t,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				fprintf(fp,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
				
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("OgrenciDersKayit.txt","a+");
			fp_t=fopen("tmp.txt","w");
			satir=-1;
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
				satir++;
			}
			fclose(fp);
			fp=fopen("OgrenciDersKayit.txt","a+");
			
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
				if (strcmp(o_der[0].kod,kod)==0) strcpy(o_der[0].kod,yeni_kod);
				fprintf(fp_t,"%s %s %d %d %s %d %d\n",o_der[0].no,o_der[0].kod,o_der[0].ID,o_der[0].kayit,o_der[0].ay,o_der[0].gun,o_der[0].yil);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("OgrenciDersKayit.txt","w");
			fp_t=fopen("tmp.txt","r");
			for(i=0;i<satir;i++){
				fscanf(fp_t,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
				fprintf(fp,"%s %s %d %d %s %d %d\n",o_der[0].no,o_der[0].kod,o_der[0].ID,o_der[0].kayit,o_der[0].ay,o_der[0].gun,o_der[0].yil);
			}
			fclose(fp);
			fclose(fp_t);
			
			printf("Dersin kodu degistirildi.\n");
			printf("OgrenciDersKayit.txt dosyasi guncellendi.\n");
			free(o_der);
			free(yeni_kod);
			
		}
		else if (strcmp(secim,"2")==0){
			OGR_DERS *o_der=(OGR_DERS*)malloc(sizeof(OGR_DERS));
			OGRENCI *ogr=(OGRENCI*)malloc(sizeof(OGRENCI));
			FILE *fp2;
			int yeni_kredi,kredi;
			char *no=(char*)malloc(11*sizeof(char));
			printf("Dersin yeni kredisi:");
			scanf("%d",&yeni_kredi);
			if (kredi<0){
				printf("Dersin kredisi negatif olamaz.\n");
				free(o_der);
				free(ogr);
				free(no);
				free(secim);
				free(kod);
				free(ders);
				return;
			}
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Dersler.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				if (strcmp(ders[0].kod,kod)==0){
					kredi=ders[0].kredi;
					ders[0].kredi=yeni_kredi;
					
				}
				fprintf(fp_t,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);	
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp_t,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				fprintf(fp,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
				
			}
			fclose(fp);
			fclose(fp_t);
			printf("Dersin kredisi degistirildi.\n");
			
			yeni_kredi-=kredi;
			
			int j;
			int satir2=-1;
			satir=-1;
			fp=fopen("OgrenciDersKayit.txt","a+");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
				satir++;
			}
			fclose(fp);
			fp2=fopen("Ogrenciler.txt","a+");
			while(!feof(fp2)){
				fscanf(fp2,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
				satir2++;
			}
			fclose(fp2);
			
			fp=fopen("OgrenciDersKayit.txt","a+");
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
				if (strcmp(o_der[0].kod,kod)==0){
					fp2=fopen("Ogrenciler.txt","a+");
					fp_t=fopen("tmp.txt","w");
					strcpy(no,o_der[0].no);
					
					for (j=0;j<satir;j++){
						fscanf(fp2,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
						if (strcmp(ogr[0].no,no)==0){
							ogr[0].kredi+=yeni_kredi;
						}
						fprintf(fp_t,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
					}
					fclose(fp2);
					fclose(fp_t);
					
					fp2=fopen("Ogrenciler.txt","w");
					fp_t=fopen("tmp.txt","r");
					for(j=0;j<satir2;j++){
						fscanf(fp_t,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
						fprintf(fp2,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
					}
					fclose(fp2);
					fclose(fp_t);
					
				}
				
			}
			fclose(fp);
			free(o_der);
			free(ogr);
			free(no);
		
			printf("Ogrenciler.txt dosyasi guncellendi.\n");
			
		}
		else if (strcmp(secim,"3")==0){
			int kontenjan;
			printf("Dersin yeni kontenjani:");
			scanf("%d",&kontenjan);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Dersler.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				if (strcmp(ders[0].kod,kod)==0){
					ders[0].kontenjan=kontenjan;
				}
				fprintf(fp_t,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);	
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp_t,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				fprintf(fp,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
				
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
			int satir2=-1;
			
			if (fp_o==NULL){
				printf("Ogretim Uyeleri dosyasi acilamadi.\n");
				free(secim);
				free(kod);
				free(ders);
				return;
			}
			
			OGR_UYE *uye=(OGR_UYE*)malloc(sizeof(OGR_UYE));
			
			while(!feof(fp_o)){
				fscanf(fp_o,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
				satir2++;
			}
			fclose(fp_o);
			fp_o=fopen("Ogretim Uyeleri.txt","a+");
			for(i=0;i<satir2;i++){
				fscanf(fp_o,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
				if(uye[0].id==id){
					count++;
				}
			}
			fclose(fp_o);
			if (count==0){
				printf("Boyle bir ogretim uyesi bulunmamaktadir.\n");
				free(secim);
				free(kod);
				free(ders);
				free(uye);
				return;
			}
			else{
				FILE *fp_t=fopen("tmp.txt","w");
				fp=fopen("Dersler.txt","r");
				
				for(i=0;i<satir;i++){
					fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
					if (strcmp(ders[0].kod,kod)==0){
						ders[0].ogrt_id=id;
					}
					fprintf(fp_t,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);	
				}
				fclose(fp);
				fclose(fp_t);
				
				fp=fopen("Dersler.txt","w");
				fp_t=fopen("tmp.txt","r");
				
				for(i=0;i<satir;i++){
					fscanf(fp_t,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
					fprintf(fp,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
				}
				fclose(fp);
				fclose(fp_t);
				printf("ID degistirildi.\n");
				
			}
		
		
		}
		else printf("Beklenmedik karakter.\n");	
		free(secim);
	}	
	free(kod);
	free(ders);
}
void uye_ekle(){
	OGR_UYE *uye=(OGR_UYE*)malloc(sizeof(OGR_UYE));
	OGR_UYE *input=(OGR_UYE*)malloc(sizeof(OGR_UYE));
	FILE *fp;
	int i;
	int satir=-1;
	
	
	printf("----------------OGRETIM UYESI EKLE---------------\n");
	printf("Ogretim uyesi adi:");
	scanf("%s",input[0].ad);
	printf("Ogretim uyesi soyadi:");
	scanf("%s",input[0].soyad);
	printf("Ogretim uyesi unvani:");
	scanf("%s",input[0].unvan);
	printf("Ogretim uyesi ID'si:");
	scanf("%d",&input[0].id);
	
	fp=fopen("Ogretim Uyeleri.txt","a+");
	
	while(!feof(fp)){
		fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
		satir++;
	}
	fclose(fp);
	fp=fopen("Ogretim Uyeleri.txt","a+");
	
	for(i=0;i<satir;i++){
		fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
		if(input[0].id==uye[0].id){
			printf("Ayni ID'li baska bir ogretim gorevlisi bulunmaktadir.");
			free(input);
			free(uye);
			fclose(fp);
			return;
		}
	}
	fclose(fp);
	fp=fopen("Ogretim Uyeleri.txt","a+");
	fprintf(fp,"%s %s %s %d\n",input[0].ad,input[0].soyad,input[0].unvan,input[0].id);
	free(uye);
	free(input);
	fclose(fp);
	printf("Ogretim uyesi eklendi.\n");
}
void uye_sil(){
	int id;
	int uye_kontrol=0; // 0 ise üye kayýtlý deðil,1 ise kayýtlý
	FILE *fp;
	OGR_UYE *uye=(OGR_UYE*)malloc(sizeof(OGR_UYE));
	int i;
	int satir=-1;
	
	printf("------------OGRETIM UYESI SILME--------------\n");
	printf("Silmek istediginiz ogretim uyesinin ID'sini giriniz:");
	scanf("%d",&id);
	
	fp=fopen("Ogretim Uyeleri.txt","a+");
	while(!feof(fp)){
		fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
		satir++;
	}
	fclose(fp);
	
	
	fp=fopen("Ogretim Uyeleri.txt","a+");
	for (i=0;i<satir && uye_kontrol!=1;i++){
		fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
		
		if (id==uye[0].id){
			uye_kontrol=1;
			fclose(fp);
		}	
	}
	
	if (uye_kontrol==1){
		fp=fopen("Dersler.txt","a+");
		FILE *fp_t=fopen("tmp.txt","w");
		FILE *fp2;
		DERS *ders=(DERS*)malloc(sizeof(DERS));
		int yeni_id;
		int kontrol;
		int j;
		int satir2;
		
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			satir2++;
		}
		fclose(fp);
		fp=fopen("Dersler.txt","a+");
		
		for(i=0;i<satir2;i++){
			fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			if (id==ders[0].ogrt_id){
				printf("%s kodlu dersi yeni verecek olan ogretim uyesinin ID'sini giriniz:",ders[0].kod);
				scanf("%d",&yeni_id);
				fp2=fopen("Ogretim Uyeleri.txt","r");
				kontrol=0;
				for(j=0;j<satir && kontrol!=1;j++){
					fscanf(fp2,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
					if (yeni_id==uye[0].id){
						kontrol=1;
					}
				}
				fclose(fp2);
				if (kontrol==0){
					printf("Boyle ID'li bir ogretim elemani bulunmuyor.\n");
					free(ders);
					free(uye);
					fclose(fp_t);
					fclose(fp);
					return;
				}
				ders[0].ogrt_id=yeni_id;
				
			}
			fprintf(fp_t,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
		}
		fclose(fp_t);
		fclose(fp);
		
		fp=fopen("Dersler.txt","w");
		fp_t=fopen("tmp.txt","r");
		for(i=0;i<satir2;i++){
			fscanf(fp_t,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			fprintf(fp,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
		}
		fclose(fp);
		fclose(fp_t);
		printf("Dersler.txt dosyasi guncellendi.\n");
		
		
		fp_t=fopen("tmp.txt","w");
		fp=fopen("Ogretim Uyeleri.txt","r");
		
		
		for(i=0;i<satir;i++){
			fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
			if (id!=uye[0].id){
				fprintf(fp_t,"%s %s %s %d\n",uye[0].ad,uye[0].soyad,uye[0].unvan,uye[0].id);	
			}
		}
		fclose(fp);
		fclose(fp_t);
		
		fp=fopen("Dersler.txt","w");
		fp_t=fopen("tmp.txt","r");
		
		satir=-1;
		while(!feof(fp_t)){
			fscanf(fp_t,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
			satir++;
		}
		fclose(fp_t);
		fp_t=fopen("tmp.txt","r");
		
		for(i=0;i<satir;i++){
			fscanf(fp_t,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
			fprintf(fp,"%s %s %s %d\n",uye[0].ad,uye[0].soyad,uye[0].unvan,uye[0].id);
		}
		fclose(fp);
		fclose(fp_t);
		printf("Ogretim uyesi basariyla silindi.\n");
		free(ders);
	}
	else{
		fclose(fp);
		printf("Bu ID'li bir ogretim elemani bulunmamaktadir.\n");
	}
	free(uye);
}
void uye_guncelle(){
	int id;
	int uye_kontrol=0;
	FILE *fp;
	OGR_UYE *uye=(OGR_UYE*)malloc(sizeof(OGR_UYE));
	int i;
	int satir=-1;
	
	
	printf("-----------------OGRETIM UYESI GUNCELLE-------------------\n");
	printf("Bilgilerini guncellemek istediginiz ogretim uyesinin ID'sini yaziniz:");
	scanf("%d",&id);
	
	fp=fopen("Ogretim Uyeleri.txt","a+");
	while(!feof(fp)){
		fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
		satir++;	
	}
	fclose(fp);
	
	fp=fopen("Ogretim Uyeleri.txt","a+");
	for(i=0;i<satir && uye_kontrol!=1;i++){
		fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
		if (id==uye[0].id) uye_kontrol=1;
	}
	fclose(fp);
	
	if (uye_kontrol==0){
		printf("Bu ID'de bir ogretim uyesi bulunmamaktadir.\n");
		free(uye);
		return;
	}
	
	else{
		char *secim=(char*)malloc(sizeof(char));
		
		printf("Ogretim uyesinin hangi bilgisini guncellemek istersiniz?\n");
		printf("0:Unvan\n1:ID");
		printf("\nSecim:");
		scanf("%s",secim);
		
		if (strcmp(secim,"0")){
			char *unvan=(char*)malloc(20*sizeof(unvan));
			printf("Ogretim uyesinin yeni unvani:");
			scanf("%s",unvan);
			
			fp=fopen("Ogretim Uyeleri.txt","r");
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
				if (strcmp(unvan,uye[0].unvan)==0){
					printf("Ayni unvani girdiniz.\n");
					free(uye);
					free(secim);
					free(unvan);
					fclose(fp);
					return;
				}
			}
			fclose(fp);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Ogretim Uyeleri.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
				if (id==uye[0].id){
					strcpy(uye[0].unvan,unvan);
				}
				fprintf(fp_t,"%s %s %s %d\n",uye[0].ad,uye[0].soyad,uye[0].unvan,uye[0].id);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Ogretim Uyeleri.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp_t,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
				fprintf(fp,"%s %s %s %d\n",uye[0].ad,uye[0].soyad,uye[0].unvan,uye[0].id);
				
			}
			free(unvan);
			fclose(fp);
			fclose(fp_t);
			printf("Unvan degistirildi.\n");	
		}
		else if (strcmp(secim,"1")){
			int yeni_id;
			DERS *ders=(DERS*)malloc(sizeof(DERS));
			printf("Ogretim uyesinin yeni ID'si:");
			scanf("%d",&yeni_id);
			
			fp=fopen("Ogretim Uyeleri.txt","r");
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
				if (yeni_id==uye[0].id){
					printf("Boyle bir ID bulunuyor.\n");
					free(ders);
					free(uye);
					free(secim);
					fclose(fp);
					return;
				}
			}
			fclose(fp);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Ogretim Uyeleri.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
				if (id==uye[0].id){
					uye[0].id=yeni_id;
				}
				fprintf(fp_t,"%s %s %s %d\n",uye[0].ad,uye[0].soyad,uye[0].unvan,uye[0].id);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Ogretim Uyeleri.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp_t,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
				fprintf(fp,"%s %s %s %d\n",uye[0].ad,uye[0].soyad,uye[0].unvan,uye[0].id);
				
			}
			fclose(fp);
			fclose(fp_t);
			printf("ID degistirildi.\n");
			
			satir=-1;
			fp=fopen("Dersler.txt","a+");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				satir++;
			}
			fclose(fp);
			
			fp=fopen("Dersler.txt","a+");
			fp_t=fopen("tmp.txt","w");
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				if(ders[0].ogrt_id==id){
					ders[0].ogrt_id=yeni_id;
				}
				fprintf(fp_t,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			for(i=0;i<satir;i++){
				fscanf(fp_t,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				fprintf(fp,"%s %s %d %d %d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
			}
			free(ders);
			fclose(fp);
			fclose(fp_t);
			printf("Dersler.txt dosyasi guncellendi.\n");
				
		}
		
		else{
			printf("Beklenmedik karakter.\n");
		}
		free(secim);	
	}
	free(uye);	
}
void ogrenci_ekle(){
	FILE *fp;
	OGRENCI *ogr=(OGRENCI*)malloc(sizeof(OGRENCI));
	OGRENCI *input=(OGRENCI*)malloc(sizeof(OGRENCI));
	int i;
	int satir=-1;
	
	printf("------------OGRENCI EKLE-----------------\n");
	printf("Ogrenci adi:");
	scanf("%s",input[0].ad);
	printf("Ogrenci soyadi:");
	scanf("%s",input[0].soyad);
	printf("Ogrenci no:");
	scanf("%s",input[0].no);
	
	if((fp=fopen("Ogrenciler.txt","a+"))==NULL){
		printf("Dosya acilamadi.\n");
		free(ogr);
		free(input);
		return;
	}
	
	while(!feof(fp)){
		fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
		satir++;
	}
	fclose(fp);
	fp=fopen("Ogrenciler.txt","a+");
	
	for (i=0;i<satir;i++){
		fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
		if (strcmp(input[0].no,ogr[0].no)==0){
			printf("Ayni numarali ogrenci bulunuyor.\n");
			free(ogr);
			free(input);
			fclose(fp);
			return;
		}
	}
	fclose(fp);
	fp=fopen("Ogrenciler.txt","a+");
	fprintf(fp,"%s %s %s %d %d\n",input[0].ad,input[0].soyad,input[0].no,0,0);
	free(ogr);
	free(input);
	printf("Ogrenci kaydedildi.\n");
	fclose(fp);
}
void ogrenci_sil(){
	FILE *fp;
	OGRENCI *ogr=(OGRENCI*)malloc(sizeof(OGRENCI));
	char *no=(char*)malloc(11*sizeof(char));
	int ogr_kontrol=0; // 0 ise öðrenci kayýtlarda bulunmuyor, 1 ise bulunuyor.
	fp=fopen("Ogrenciler.txt","a+");
	int i;
	int satir=-1;
	
	if(fp==NULL){
		printf("Dosya acilamadi.\n");
		free(ogr);
		free(no);
		return;
	}
	
	while(!feof(fp)){
		fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
		satir++;
	}
	fclose(fp);
	fp=fopen("Ogrenciler.txt","a+");
	
	printf("---------OGRENCI SIL----------\n");
	printf("Silmek istediginiz ogrencinin numarasini giriniz:");
	scanf("%s",no);
	
	for (i=0;i<satir && ogr_kontrol!=1;i++){
		fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
		
		if (strcmp(no,ogr[0].no)==0){
			ogr_kontrol=1;
			fclose(fp);
		}
	}
	
	if (ogr_kontrol==1){
		FILE *fp_t=fopen("tmp.txt","w");
		fp=fopen("Ogrenciler.txt","r");
		OGR_DERS *o_der=(OGR_DERS*)malloc(sizeof(OGR_DERS));
		
		for(i=0;i<satir;i++){
			fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
			if (strcmp(no,ogr[0].no)!=0){
				fprintf(fp_t,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
			}
		}
		fclose(fp);
		fclose(fp_t);
		satir=-1;
		
		fp=fopen("Ogrenciler.txt","w");
		fp_t=fopen("tmp.txt","r");
		
		while(!feof(fp_t)){
			fscanf(fp_t,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
			satir++;
		}
		fclose(fp_t);
		fp_t=fopen("tmp.txt","r");
		
		for(i=0;i<satir;i++){
			fscanf(fp_t,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
			fprintf(fp,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
		}
		fclose(fp);
		fclose(fp_t);
		printf("Ogrenci basariyla silindi.\n");
		
		fp=fopen("OgrenciDerskayit.txt","a+");
		fp_t=fopen("tmp.txt","w");
		
		satir=-1;
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			satir++;
		}
		fclose(fp);
		fp=fopen("OgrenciDersKayit.txt","a+");
		
		
		for(i=0;i<satir;i++){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			if (strcmp(o_der[0].no,no)!=0){
				fprintf(fp_t,"%s %s %d %d %s %d %d\n",o_der[0].no,o_der[0].kod,o_der[0].ID,o_der[0].kayit,o_der[0].ay,o_der[0].gun,o_der[0].yil);
			}
		}
		fclose(fp);
		fclose(fp_t);
		
		satir=-1;
		fp_t=fopen("tmp.txt","r");
		while(!feof(fp_t)){
			fscanf(fp_t,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			satir++;
		}
		fclose(fp_t);
		
		fp=fopen("OgrenciDersKayit.txt","w");
		fp_t=fopen("tmp.txt","r");
		for(i=0;i<satir;i++){
			fscanf(fp_t,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			fprintf(fp,"%s %s %d %d %s %d %d\n",o_der[0].no,o_der[0].kod,o_der[0].ID,o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
		}
		free(o_der);
		fclose(fp);
		fclose(fp_t);
		printf("OgrenciDersKayit.txt dosyasi guncellendi.\n");
		
	}
	else{
		fclose(fp);
		printf("Bu numarada bir ogrenci bulunmamaktadir.\n");
	}
	free(no);
	free(ogr);	
}
void ogrenci_guncelle(int max_kredi,int max_ders){
	
	FILE *fp;
	char *no=(char*)malloc(11*sizeof(char));
	OGRENCI *ogr=(OGRENCI*)malloc(sizeof(OGRENCI));
	OGR_DERS *o_der=(OGR_DERS*)malloc(sizeof(OGR_DERS));
	DERS *ders=(DERS*)malloc(sizeof(DERS));
	int ogr_kontrol=0;
	int i;
	int satir=-1;
	
	printf("--------OGRENCI GUNCELLE-----------\n");
	printf("Guncellemek istediginiz ogrencinin numarasini giriniz:");
	scanf("%s",no);
	
	fp=fopen("Ogrenciler.txt","a+");
	while(!feof(fp)){
		fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
		satir++;
	}
	fclose(fp);
	
	
	fp=fopen("Ogrenciler.txt","a+");
	
	for (i=0;i<satir && ogr_kontrol!=1;i++){
		fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
		if (strcmp(no,ogr[0].no)==0) ogr_kontrol=1;
		
	}
	fclose(fp);
	
	if (ogr_kontrol==0){
		printf("Bu numarada bir ogrenci bulunmuyor.\n");
		free(no);
		free(ogr);
		free(o_der);
		free(ders);
		return;
	}
	
	else{
		char *secim=(char*)malloc(sizeof(char));
		printf("Ogrencinin hangi ozelligini guncellemek istersiniz?\n");
		printf("0:No\n1:Ders durumu");
		printf("\nSecim:");
		scanf("%s",secim);
		
		if(strcmp(secim,"0")==0){
			char *yeni_no=(char*)malloc(11*sizeof(char));
			printf("Ogrencinin yeni numarasi:");
			scanf("%s",yeni_no);
			
			fp=fopen("Ogrenciler.txt","r");
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
				if (strcmp(yeni_no,ogr[0].no)==0){
					printf("Ayni numarali ogrenci bulunmaktadir.\n");
					free(yeni_no);
					free(secim);
					free(no);
					free(ogr);
					free(o_der);
					free(ders);
					fclose(fp);
					return;
				}
			}
			fclose(fp);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Ogrenciler.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
				if (strcmp(ogr[0].no,no)==0){
					strcpy(ogr[0].no,yeni_no);
				}
				fprintf(fp_t,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("Ogrenciler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			for(i=0;i<satir;i++){
				fscanf(fp_t,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
				fprintf(fp,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
				
			}
			fclose(fp);
			fclose(fp_t);
			printf("Ogrencinin numarasi degistirildi.\n");
			
			satir=-1;
			fp=fopen("OgrenciDersKayit.txt","a+");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
				satir++;
			}
			fclose(fp);
			
			fp=fopen("OgrenciDersKayit.txt","a+");
			fp_t=fopen("tmp.txt","w");
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
				if (strcmp(no,o_der[0].no)==0){
					strcpy(o_der[0].no,yeni_no);
				}
				fprintf(fp_t,"%s %s %d %d %s %d %d\n",o_der[0].no,o_der[0].kod,o_der[0].ID,o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			}
			fclose(fp);
			fclose(fp_t);
			
			fp=fopen("OgrenciDersKayit.txt","w");
			fp_t=fopen("tmp.txt","r");
			for(i=0;i<satir;i++){
				fscanf(fp_t,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
				fprintf(fp,"%s %s %d %d %s %d %d\n",o_der[0].no,o_der[0].kod,o_der[0].ID,o_der[0].kayit,o_der[0].ay,o_der[0].gun,o_der[0].yil);
			}
			
			free(yeni_no);
			fclose(fp);
			fclose(fp_t);
			printf("OgrenciDersKayit.txt dosyasi guncellendi.\n");		
		}
		else if (strcmp(secim,"1")==0){
			char *kod=(char*)malloc(7*sizeof(char));
			int ders_kontrol=0;
			int j;
			int satir2=-1,satir3=-1;
			
			printf("Ogrencinin aldigi dersin kodunu giriniz:");
			scanf("%s",kod);
			fp=fopen("OgrenciDersKayit.txt","a+");
			
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
				satir2++;
			}
			fclose(fp);
			fp=fopen("OgrenciDersKayit.txt","a+");
			
			
			for(i=0;i<satir2 && ders_kontrol!=1;i++){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
				if (strcmp(kod,o_der[0].kod)==0 && strcmp(no,o_der[0].no)==0){
					ders_kontrol=1;
				}
			}
			fclose(fp);
			if (ders_kontrol==0){
				printf("Hata.Ogrenciyle ders uyusmuyor.\n");
				free(kod);
				free(secim);
				free(no);
				free(ogr);
				free(o_der);
				free(ders);
				return;
			}
			
			else{
				FILE *fp_t;
				FILE *fp2,*fp_t2;
				int kontrol,kredi;
				fp=fopen("Dersler.txt","a+");
				fp_t=fopen("tmp.txt","w");
				
				while(!feof(fp)){
					fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
					satir3++;
				}
				fclose(fp);
				fp=fopen("OgrenciDersKayit.txt","a+");
				
				for(i=0;i<satir2;i++){
					fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
					if (strcmp(kod,o_der[0].kod)==0 && strcmp(no,o_der[0].no)==0){
						
						kontrol=0;
						
						fp2=fopen("Dersler.txt","r");
						for(j=0;j<satir3 && kontrol!=1;j++){
							fscanf(fp2,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
							if (strcmp(ders[0].kod,kod)==0){
								kredi=ders[0].kredi;
								kontrol=1;
							}
						}
						fclose(fp2);
						kontrol=0;
						
						if (o_der[0].kayit==0){
							fp2=fopen("Ogrenciler.txt","r");
							fp_t2=fopen("tmp2.txt","w");
							for(j=0;j<satir;j++){
								fscanf(fp2,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
								if (strcmp(no,ogr[0].no)==0){
									if ((ogr[0].kredi+kredi)>max_kredi || (ogr[0].ders_no+1)>max_ders){
										printf("Maksimum kredi veya ders sayisini asamazsiniz.\n");
										free(kod);
										free(secim);
										free(no);
										free(ogr);
										free(o_der);
										free(ders);
										fclose(fp_t2);
										fclose(fp2);
										return;
									}
									ogr[0].kredi+=kredi;
									ogr[0].ders_no+=1;
								}
								fprintf(fp_t2,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
								
							}
							fclose(fp2);
							fclose(fp_t2);
							
							fp2=fopen("Ogrenciler.txt","w");
							fp_t2=fopen("tmp2.txt","r");
							for(j=0;j<satir;j++){
								fscanf(fp_t2,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
								fprintf(fp2,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
							}	
							fclose(fp2);
							fclose(fp_t2);
							printf("Ogrenciler.txt dosyasi guncellendi.\n");
							
							o_der[0].kayit=1;
							kontrol=1;	
							
						}
						else if (o_der[0].kayit==1 && kontrol==0){
							fp2=fopen("Ogrenciler.txt","r");
							fp_t2=fopen("tmp2.txt","w");
							
							for(j=0;j<satir;j++){
								fscanf(fp2,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
								if (strcmp(no,ogr[0].no)==0){
									ogr[0].kredi-=kredi;
									ogr[0].ders_no-=1;
								}
								fprintf(fp_t2,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
							}
							fclose(fp2);
							fclose(fp_t2);
							
							fp2=fopen("Ogrenciler.txt","w");
							fp_t2=fopen("tmp2.txt","r");
							for(j=0;j<satir;j++){
								fscanf(fp_t2,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
								fprintf(fp2,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
							}	
							fclose(fp2);
							fclose(fp_t2);
							printf("Ogrenciler.txt dosyasi guncellendi.\n");
							
							o_der[0].kayit=0;
							
						}
					}
					fprintf(fp_t,"%s %s %d %d %s %d %d\n",o_der[0].no,o_der[0].kod,o_der[0].ID,o_der[0].kayit,o_der[0].ay,o_der[0].gun,o_der[0].yil);	
				}
				fclose(fp);
				fclose(fp_t);
				
				fp=fopen("OgrenciDersKayit.txt","w");
				fp_t=fopen("tmp.txt","r");
				for(i=0;i<satir2;i++){
					fscanf(fp_t,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
					fprintf(fp,"%s %s %d %d %s %d %d\n",o_der[0].no,o_der[0].kod,o_der[0].ID,o_der[0].kayit,o_der[0].ay,o_der[0].gun,o_der[0].yil);
				}
				printf("Ogrencinin ders durumu degistirildi.\n");
			}
			free(kod);	
		}
		else{
			printf("Beklenmedik karakter.\n");
		}
		free(secim);
	}
	free(no);
	free(ogr);
	free(o_der);
	free(ders);
		
}
void ders_sec(int max_kredi,int max_ders){
	char *no=(char*)malloc(11*sizeof(char));
	FILE *fp;
	OGRENCI *ogr=(OGRENCI*)malloc(sizeof(OGRENCI));
	int ogr_kontrol=0;
	int i;
	int satir=-1;
	
	printf("---------------DERS SECME--------------\n");
	printf("Ogrencinin numarasini giriniz:");
	scanf("%s",no);
	
	fp=fopen("Ogrenciler.txt","a+");
	while(!feof(fp)){
		fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
		satir++;
	}
	fclose(fp);
	fp=fopen("Ogrenciler.txt","a+");
	
	for(i=0;i<satir && ogr_kontrol!=1;i++){
		fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
		if (strcmp(no,ogr[0].no)==0) ogr_kontrol=1;
		
	}
	fclose(fp);
	
	if (ogr_kontrol==0){
		printf("Bu numarada bir ogrenci bulunmuyor.\n");
		free(no);
		free(ogr);
		return;
	}
	else{
		char *kod=(char*)malloc(7*sizeof(char));
		DERS *ders=(DERS*)malloc(sizeof(DERS));
		int ders_kontrol=0;
		int satir2=-1,satir3=-1;
		printf("Secmek istediginiz dersin kodunu giriniz:\n");
		scanf("%s",kod);
		
		fp=fopen("Dersler.txt","a+");
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			satir2++;
		}
		fclose(fp);
		fp=fopen("Dersler.txt","a+");
		
		for(i=0;i<satir2 && ders_kontrol!=1;i++){
			fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			if (strcmp(kod,ders[0].kod)==0) ders_kontrol=1;
		}
		fclose(fp);
		if (ders_kontrol==0){
			printf("Bu kodda bir ders bulunmuyor.\n");
			free(kod);
			free(ders);
			free(no);
			free(ogr);
			return;
		}
		else{
			int ders_kredi,ders_kont,ogr_kredi,ogr_ders,kon_counter=0;
			OGR_DERS *o_der=(OGR_DERS*)malloc(sizeof(OGR_DERS));
			
			fp=fopen("Dersler.txt","a+");
			for(i=0;i<satir2;i++){
				fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
				if (strcmp(ders[0].kod,kod)==0){
					ders_kredi=ders[0].kredi;
					ders_kont=ders[0].kontenjan;
				} 
			}
			fclose(fp);
			
			fp=fopen("Ogrenciler.txt","a+");
			for(i=0;i<satir;i++){
				fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
				if (strcmp(ogr[0].no,no)==0){
					ogr_kredi=ogr[0].kredi;
					ogr_ders=ogr[0].ders_no;
				}
			}
			fclose(fp);
			
			fp=fopen("OgrenciDersKayit.txt","a+");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
				satir3++;
				
			}
			fclose(fp);
			fp=fopen("OgrenciDersKayit.txt","a+");
			for(i=0;i<satir3;i++){
				fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
				if (strcmp(kod,o_der[0].kod)==0 && o_der[0].kayit==1) kon_counter++;
				}
			fclose(fp);
			
			
			if ((ogr_kredi+ders_kredi)<=max_kredi && (ogr_ders<max_ders && kon_counter<ders_kont) ){
				FILE *fp_t;
				
				fp=fopen("OgrenciDersKayit.txt","a+");
				
				fprintf(fp,"%s %s %d %d %s\n",no,kod,satir3+1,1,__DATE__);
				fclose(fp);
				
				fp=fopen("Ogrenciler.txt","a+");
				fp_t=fopen("tmp.txt","w");
				for(i=0;i<satir;i++){
					fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
					if (strcmp(no,ogr[0].no)==0){
						ogr[0].kredi+=ders_kredi;
						ogr[0].ders_no+=1;
					}
					fprintf(fp_t,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
				}
				fclose(fp);
				fclose(fp_t);
				
				fp=fopen("Ogrenciler.txt","w");
				fp_t=fopen("tmp.txt","r");
				
				for(i=0;i<satir;i++){
					fscanf(fp_t,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
					fprintf(fp,"%s %s %s %d %d\n",ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
				}
				fclose(fp);
				fclose(fp_t);
				printf("Ders secildi.\n");
				printf("Ogrenciler.txt dosyasi guncellendi.\n");
				
			}
			else{
				printf("Dersi secilemedi.\n");
			}
			free(o_der);
		}
		free(kod);
		free(ders);
	}
	free(no);
	free(ogr);	
}
void uye_ders_yaz(){
	FILE *fp;
	DERS *ders=(DERS*)malloc(sizeof(DERS));
	OGR_UYE *uye=(OGR_UYE*)malloc(sizeof(OGR_UYE));
	int id;
	int kontrol=0;
	int i;
	int satir=-1;
	
	printf("Ogretim uyesinin ID'sini giriniz:");
	scanf("%d",&id);
	
	fp=fopen("Ogretim Uyeleri.txt","a+");
	while(!feof(fp)){
		fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);	
		satir++;
	}
	fclose(fp);
	fp=fopen("Ogretim Uyeleri.txt","a+");
	
	
	for(i=0;i<satir && kontrol!=1;i++){
		fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
		if (id==uye[0].id) {
			kontrol=1;
		}
	}
	fclose(fp);
	if (kontrol==0){
		printf("Boyle bir ogretim uyesi bulunmamaktadir.\n");
		free(ders);
		free(uye);
		return;
	}
	else{
		printf("-------------OGRETIM UYESININ VERDIGI DERSLER------------\n");
		fp=fopen("Dersler.txt","a+");
		
		satir=-1;
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			satir++;
		}
		fclose(fp);
		fp=fopen("Dersler.txt","a+");
		
		for(i=0;i<satir;i++){
			fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			if(id==ders[0].ogrt_id){
				printf("Ders Adi:%s  Ders Kodu:%s   Ders Kredisi:%d     Ders Kontenjani:%d\n",ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan);
			}
		}
		fclose(fp);
		
	}
	free(ders);
	free(uye);
}
void ders_ogr_yaz(){
	FILE *fp;
	DERS *ders=(DERS*)malloc(sizeof(DERS));
	char *kod=(char*)malloc(7*sizeof(char));
	int kontrol=0;
	int i,j;
	int satir=-1;
	
	printf("Ders kodunu giriniz:");
	scanf("%s",kod);
	
	fp=fopen("Dersler.txt","a+");
	while(!feof(fp)){
		fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
		satir++;
	}
	fclose(fp);
	fp=fopen("Dersler.txt","a+");
	
	
	for(i=0;i<satir && kontrol!=1;i++){
		fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
		if (strcmp(kod,ders[0].kod)==0) kontrol=1;
	}
	fclose(fp);
	if (kontrol==0){
		printf("Boyle bir ders bulunmuyor.\n");
		free(ders);
		free(kod);
		return;
	}
	else{
		FILE *fp2;
		OGR_DERS *o_der=(OGR_DERS*)malloc(sizeof(OGR_DERS));
		OGRENCI *ogr=(OGRENCI*)malloc(sizeof(OGRENCI));
		int satir2=-1;
		fp=fopen("OgrenciDersKayit.txt","a+");
		printf("---------------DERSI ALAN OGRENCÝLER---------------\n");
		
		satir=-1;
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			satir++;
		}
		fclose(fp);
		
		fp2=fopen("Ogrenciler.txt","a+");
		while(!feof(fp2)){
			fscanf(fp2,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
			satir2++;
		}
		
		for(i=0;i<satir;i++){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			if (strcmp(kod,o_der[0].kod)==0){
				fp2=fopen("Ogrenciler.txt","a+");
				for(j=0;j<satir2;j++){
					fscanf(fp2,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
					if(strcmp(o_der[0].no,ogr[0].no)==0 && o_der[0].kayit==1){
						printf("Ogrenci Adi:%s   Ogrenci Soyadi:%s    Ogrenci No:%s      Ogrencinin Aldigi Kredi Sayisi:%d    Ogrencinin Aldigi Ders Sayisi:%d\n",
								ogr[0].ad,ogr[0].soyad,ogr[0].no,ogr[0].kredi,ogr[0].ders_no);
					}
				}
				fclose(fp2);
			}
		}
		free(o_der);
		free(ogr);
		fclose(fp);
	}
	free(ders);
	free(kod);
	
}

void ogr_ders_yaz(){
	char *no=(char*)malloc(11*sizeof(char));
	OGRENCI *ogr=(OGRENCI*)malloc(sizeof(OGRENCI));
	FILE *fp;
	int kontrol=0;
	int i,j;
	int satir=-1,satir2=-1;
	
	printf("Ogrencinin numarasini giriniz:");
	scanf("%s",no);
	
	fp=fopen("Ogrenciler.txt","a+");
	while(!feof(fp)){
		fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
		satir++;
	}
	fclose(fp);
	fp=fopen("Ogrenciler.txt","a+");
	
	for(i=0;i<satir && kontrol!=1;i++){
		fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
		if (strcmp(ogr[0].no,no)==0) kontrol=1;
	}
	fclose(fp);
	
	if (kontrol==0){
		printf("Boyle bir ogrenci bulunmuyor.\n");
		free(no);
		free(ogr);
		return;
	}
	
	
	else{
		OGR_DERS *o_der=(OGR_DERS*)malloc(sizeof(OGR_DERS));
		DERS *ders=(DERS*)malloc(sizeof(DERS));
		FILE *fp2;
		
		satir=-1;
		fp=fopen("OgrenciDersKayit.txt","a+");
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			satir++;
		}
		fclose(fp);
	
		fp=fopen("Dersler.txt","a+");
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			satir2++;
		}
		fclose(fp);
	
		fp=fopen("OgrenciDersKayit.txt","a+");
		printf("---------OGRENCININ ALDIGI DERSLER--------------\n");
		for (i=0;i<satir;i++){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			if (strcmp(o_der[0].no,no)==0 && o_der[0].kayit==1){
				fp2=fopen("Dersler.txt","a+");
				for(j=0;j<satir2;j++){
					fscanf(fp2,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
					if (strcmp(ders[0].kod,o_der[0].kod)==0){
						printf("Ders Adi:%s    Ders Kodu:%s        Ders Kredisi:%d          Ders Kontenjani:%d        Dersi Veren Ogretim Uyesinin ID'si:%d\n",
								ders[0].ad,ders[0].kod,ders[0].kredi,ders[0].kontenjan,ders[0].ogrt_id);
					}
				}
				fclose(fp2);
			}
		}
		free(o_der);
		free(ders);
		fclose(fp);
	}
	free(no);
	free(ogr);
	
}

void derskodu_sinif(){
	int id;
	FILE *fp;
	OGR_UYE *uye=(OGR_UYE*)malloc(sizeof(OGR_UYE));
	int kontrol=0;
	int i,j,k;
	int satir=-1,satir2=-1,satir3=-1;
	
	printf("Ogretim uyesinin ID'sini giriniz:");
	scanf("%d",&id);
	fp=fopen("Ogretim Uyeleri.txt","a+");
	
	while(!feof(fp)){
		fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
		satir++;
	}
	fclose(fp);
	fp=fopen("Ogretim Uyeleri.txt","a+");
	
	for(i=0;i<satir && kontrol!=1;i++){
		fscanf(fp,"%s %s %s %d",uye[0].ad,uye[0].soyad,uye[0].unvan,&uye[0].id);
		if (id==uye[0].id) kontrol=1;
	}
	
	fclose(fp);
	if (kontrol==0){
		printf("Boyle bir ogretim uyesi bulunmamaktadir.\n");
		free(uye);
		return;
	}

	else{
		DERS *ders=(DERS*)malloc(sizeof(DERS));
		FILE *fp2,*fp3,*fp4;
		OGR_DERS *o_der=(OGR_DERS*)malloc(sizeof(OGR_DERS));
		OGRENCI *ogr=(OGRENCI*)malloc(sizeof(OGRENCI));
		char *dosya=(char*)malloc(24*sizeof(char));
		
		satir=-1;
		fp=fopen("Dersler.txt","a+");
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			satir++;
		}
		fclose(fp);
	
		fp=fopen("OgrenciDersKayit.txt","a+");
		while(!feof(fp)){
			fscanf(fp,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
			satir2++;
		}
		fclose(fp);
	
		fp=fopen("Ogrenciler.txt","a+");
		while(!feof(fp)){
			fscanf(fp,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
			satir3++;
		}
		fclose(fp);
		
		fp=fopen("Dersler.txt","a+");
		for(i=0;i<satir;i++){
			fscanf(fp,"%s %s %d %d %d",ders[0].ad,ders[0].kod,&ders[0].kredi,&ders[0].kontenjan,&ders[0].ogrt_id);
			if(id==ders[0].ogrt_id){
				strcpy(dosya,ders[0].kod);
				strcat(dosya,"_SINIFLISTESI.txt");
				fp4=fopen(dosya,"w");
				fp2=fopen("OgrenciDersKayit.txt","a+");
				for(j=0;j<satir2;j++){
					fscanf(fp2,"%s %s %d %d %s %d %d",o_der[0].no,o_der[0].kod,&o_der[0].ID,&o_der[0].kayit,o_der[0].ay,&o_der[0].gun,&o_der[0].yil);
					if(strcmp(ders[0].kod,o_der[0].kod)==0 && o_der[0].kayit==1){
						fp3=fopen("Ogrenciler.txt","a+");
						for(k=0;k<satir3;k++){
							fscanf(fp3,"%s %s %s %d %d",ogr[0].ad,ogr[0].soyad,ogr[0].no,&ogr[0].kredi,&ogr[0].ders_no);
							if (strcmp(o_der[0].no,ogr[0].no)==0){
								fprintf(fp4,"%s %s %s\n",ogr[0].ad,ogr[0].soyad,ogr[0].no);
							}
						}
						fclose(fp3);
					}
					
				}
				fclose(fp2);
				fclose(fp4);
			}
	
		}
		free(ders);
		free(o_der);
		free(ogr);
		free(dosya);
		fclose(fp);
		printf("Dosyalar olusturuldu.\n");
	}
	free(uye);
	
}












