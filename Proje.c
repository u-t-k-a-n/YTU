#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
	char ad[50];
	char kod[7];
	int kredi;
	int kontenjan;
	int ogrt_id;
	int durum=1; // 1 ise ders veriliyor, 0 ise silinmiþ 	
}DERS;

typedef struct{
	char ad[20];
	char soyad[20];
	char unvan[20];
	int id; 
	int durum=1; //1 ise çalýþýyor,0 ise eski çalýþan
}OGR_UYE;

typedef struct{
	char ad[20];
	char soyad[20];
	char no[11];
	int kredi=0;
	int ders_no=0;
	int durum=1; // 1 ise kayýtlý, 0 ise deðil
}OGRENCI;

void ders_ekle();
void ders_sil();
void ders_guncelle();
void uye_ekle();
void uye_sil();
void uye_guncelle();
void ogrenci_ekle();
void ogrenci_sil();
void ogrenci_guncelle();

int main(){
	
	
	
	
	
	
	
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
	printf("Ders kontenjani:");
	scanf("%d",&input.kontenjan);
	printf("Dersi veren ogretim uyesinin ID'si:");
	scanf("%d",&input.ogrt_id)
	
	
	if(fp=fopen("Dersler.txt","a+")==NULL){
		printf("Dosya acilamadi.\n");
		return;
	}
	
	while (!feof(fp)){
		fscanf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
		if ((strcmp(input.ad,ders.ad)==0 || strcmp(input.kod,ders.kod)==0) && ders.durum==1){
			printf("Ayni isimli veya kodlu ders bulunuyor.\n");
			fclose(fp);
			return;
		}
	}
	
	fprintf(fp,"%s %s %d %d %d %d",input.ad,input.kod,input.kredi,input.kontenjan,input.ogrt_id,input.durum);
	printf("Ders kaydedildi.\n");
	fclose(fp);
}

void ders_sil(){
	FILE *fp;
	DERS ders;
	char kod[7];
	int ders_kontrol=0; // 0 ise ders kayýtlarda bulunmuyor, 1 ise bulunuyor.
	fp=fopen("Dersler.txt","a+");
	
	if(fp==NULL){
		printf("Dosya acilamadi.\n");
		return;
	}
	
	printf("---------DERS SIL----------\n");
	printf("Silmek istediginiz dersin kodunu giriniz:");
	scanf("%s",kod);
	
	while ((!feof(fp)) && ders_kontrol!=1){
		fscanf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
		
		if (strcmp(kod,ders.kod)==0 && ders.durum==0){
			printf("Bu ders zaten silinmis.\n");
			fclose(fp);
			return;
		}
		else if (strcmp(kod,ders.kod)==0 && ders.durum==1){
			ders_kontrol=1;
			fclose(fp);
		}
	}
	
	if (ders_kontrol==1){
		FILE *fp_t=fopen("tmp.txt","w");
		fp=fopen("Dersler.txt","r");
		
		while (!feof(fp)){
			fscanf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
			if (strcmp(kod,ders.kod)==0){
				ders.durum=0;
			}
			
			fprintf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);
		}
		fclose(fp);
		fclose(fp_t);
		
		fp=fopen("Dersler.txt","w");
		fp_t=fopen("tmp.txt","r");
		
		while(!feof(fp_t)){
			fprintf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);
		}
		fclose(fp);
		fclose(fp_t);
		printf("Ders basariyla silindi.\n");
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
		fscanf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
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
		printf("0:Ad\n1:Kod\n2:Kredi3:Kontenjan4:Ogretim Uye ID\n5:Durum");
		printf("\nSecim:");
		scanf("%s",secim);
		
		if (strcmp(secim,"0")==0){
			char isim[50];
			printf("Dersin yeni ismi:");
			scanf("%[^\n]s",isim);
			
			fp=fopen("Dersler.txt","r")
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
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
				fscanf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
				if (strcmp(ders.kod,kod)==0){
					strcpy(ders.ad,isim);
				}
				fprintf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);
			}
			fclose(fp);
			flose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
				fprintf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);
				
			}
			fclose(fp);
			fclose(fp_t)
			printf("Dersin ismi degistirildi.\n");
					
		}
		
		else if (strcmp(secim,"1")==0){
			char yeni_kod[7];
			printf("Dersin yeni kodu:");
			scanf("%s",yeni_kod);
			
			fp=fopen("Dersler.txt","r")
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
				if (strcmp(yeni_kod,ders.kod)==0){
					printf("Ayni kodlu ders bulunmaktadir.");
					fclose(fp);
					return;
				}
			}
			fclose(fp);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Dersler.txt","r");
			
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
				if (strcmp(ders.kod,kod)==0){
					strcpy(ders.kod,yeni_kod);
				}
				fprintf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);
			}
			fclose(fp);
			flose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
				fprintf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);
				
			}
			fclose(fp);
			fclose(fp_t)
			printf("Dersin kodu degistirildi.\n");
			
			
		}
		else if (strcmp(secim,"2")==0){
			int kredi;
			printf("Dersin yeni kredisi:");
			scanf("%d",&kredi);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Dersler.txt","r");
			
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
				if (strcmp(ders.kod,kod)==0){
					ders.kredi=kredi;
				}
				fprintf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);	
			}
			fclose(fp);
			flose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
				fprintf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);
				
			}
			fclose(fp);
			fclose(fp_t)
			printf("Dersin kredisi degistirildi.\n");
			
			
		}
		else if (strcmp(secim,"3")==0){
			int kontenjan;
			printf("Dersin yeni kontenjani:");
			scanf("%d",&kontenjan);
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Dersler.txt","r");
			
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
				if (strcmp(ders.kod,kod)==0){
					ders.kontenjan=kontenjan;
				}
				fprintf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);	
			}
			fclose(fp);
			flose(fp_t);
			
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
				fprintf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);
				
			}
			fclose(fp);
			fclose(fp_t)
			printf("Dersin kontenjani degistirildi.\n");
				
		}
		
		else if (strcmp(secim,"4")==0){
			int id;
			int count=0;
			printf("Dersi verecek olan ogretim uyesinin ID'si:");
			scanf("%d",&id);
			FILE *fp_o=fopen("Ogretim Uyeleri.txt","r");
			
			if (fp_o==NULL){
				printf("Ogretim Uyeleri dosyasý acilamadi.\n");
				return;
			}
			
			OGR_UYE uye;
			while(!feof(fp_o)){
				fscanf(fp_o,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
				if(uye.id==id && uye.durum==1){
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
					fscanf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
					if (strcmp(ders.kod,kod)==0){
						ders.ogrt_id=id;
					}
					fprintf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);	
				}
				fclose(fp);
				fclose(fp_t);
				
				fp=fopen("Dersler.txt","w");
				fp_t=fopen("tmp.txt","r");
				
				while(!feof(fp_t)){
					fscanf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
					fprintf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);
				}
				fclose(fp);
				fclose(fp_t);
				printf("ID degistirildi.\n");
				
			}
		else if (strcmp(secim,"5")==0){
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Dersler.txt","r");
			while(!feof(fp)){
				fscanf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
				if (strcmp(ders.kod,kod)==0){
					if (ders.durum==0){
						ders.durum=1
					}
					else{
						printf("Kayýtlý dersi silmek icin menuden ders silmeyi secin.\n");
						fclose(fp);
						fclose(fp_t);
						return;
					}
					
				}
				
				fprintf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);	
			}
			fclose(fp);
			fclose(fp_t);
				
			fp=fopen("Dersler.txt","w");
			fp_t=fopen("tmp.txt","r");
				
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %d %d %d %d",ders.ad,ders.kod,&ders.kredi,&ders.kontenjan,&ders.ogrt_id,&ders.durum);
				fprintf(fp,"%s %s %d %d %d %d",ders.ad,ders.kod,ders.kredi,ders.kontenjan,ders.ogrt_id,ders.durum);
			}
			fclose(fp);
			fclose(fp_t);
			printf("Ders durumu degistirildi.\n");	
		}	
		else printf("Beklenmedik karakter.\n");	
		}
	}	
	
}
void uye_ekle(){
	OGR_UYE uye,input;
	FILE *fp;
	
	printf("----------------OGRETIM UYESI EKLE---------------\n");
	printf("Ogretim uyesi adý:");
	scanf("%[^\n]s",input.ad);
	printf("Ogretim uyesi soyadý:");
	scanf("%[^\n]s",input.soyad);
	printf("Ogretim uyesi unvani:");
	scanf("%[^\n]s",input.unvan);
	printf("Ogretim uyesi ID'si:");
	scanf("%d",input.id);
	
	fp=fopen("Ogretim Uyeleri.txt","a+");
	while(!feof(fp)){
		fscanf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
		if(input.id==uye.id && uye.durum==1){
			printf("Ayni ID'li baska bir ogretim gorevlisi bulunmaktadýr.");
			fclose(fp);
			return;
		}
	}
	fprintf(fp,"%s %s %s %d %d",input.ad,input.soyad,input.unvan,input.id,input.durum);
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
		fscanf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
		if (id==uye.id && uye.durum==0){
			printf("Bu ogretim uyesi zaten silinmis.\n");
			fclose(fp);
			return;
		}
		else if (id==uye.id && uye.durum==1){
			uye_kontrol=1;
			fclose(fp);
		}	
	}
	if (uye_kontrol==1){
		FILE *fp_t=fopen("tmp.txt","w");
		fp=fopen("Ogretim Uyeleri.txt","r");
		while (!feof(fp)){
			fscanf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
			if (id==uye.id){
				uye.durum=0;
			}
			
			fprintf(fp_t,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,uye.id,uye.durum);
		}
		fclose(fp);
		fclose(fp_t);
		
		fp=fopen("Dersler.txt","w");
		fp_t=fopen("tmp.txt","r");
		
		while(!feof(fp_t)){
			fprintf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,uye.id,uye.durum);
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
		fscanf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
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
		printf("0:Unvan\n1:ID\n2:Durum");
		printf("\nSecim:");
		scanf("%s",secim);
		
		if (strcmp(secim,"0")){
			char unvan[20];
			printf("Ogretim uyesinin yeni unvani:");
			scanf("%[^\n]s",unvan);
			
			fp=fopen("Ogretim Uyeleri.txt","r")
			while(!feof(fp)){
				fscanf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
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
				fscanf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
				if (id==uye.id){
					strcpy(uye.unvan,unvan);
				}
				fprintf(fp_t,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,uye.id,uye.durum);
			}
			fclose(fp);
			flose(fp_t);
			
			fp=fopen("Ogretim Uyeleri.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
				fprintf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,uye.id,uye.durum);
				
			}
			fclose(fp);
			fclose(fp_t)
			printf("Unvan degistirildi.\n");	
		}
		else if (strcmp(secim,"1")){
			int yeni_id;
			printf("Ogretim uyesinin yeni ID'si:");
			scanf("%d",&yeni_id);
			
			fp=fopen("Ogretim Uyeleri.txt","r")
			while(!feof(fp)){
				fscanf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
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
				fscanf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
				if (id==uye.id){
					uye.id=yeni_id;
				}
				fprintf(fp_t,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,uye.id,uye.durum);
			}
			fclose(fp);
			flose(fp_t);
			
			fp=fopen("Ogretim Uyeleri.txt","w");
			fp_t=fopen("tmp.txt","r");
			
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
				fprintf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,uye.id,uye.durum);
				
			}
			fclose(fp);
			fclose(fp_t)
			printf("ID degistirildi.\n");	
		}
		else if (strcmp(scim,"2")==0){
			FILE *fp_t=fopen("tmp.txt","w");
			fp=fopen("Ogretim Uyeleri.txt","r");
			while(!feof(fp)){
				fscanf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
				if (uye.id==id){
					if (uye.durum==0){
						uye.durum=1
					}
					else{
						printf("Kayýtlý ogretim uyesini silmek icin menuden ogretim uyesi silmeyi secin.\n");
						fclose(fp);
						fclose(fp_t);
						return;
					}
					
				}
				
				fprintf(fp_t,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,uye.id,uye.durum);	
			}
			fclose(fp);
			fclose(fp_t);
				
			fp=fopen("Ogretim Uyeleri.txt","w");
			fp_t=fopen("tmp.txt","r");
				
			while(!feof(fp_t)){
				fscanf(fp_t,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,&uye.id,&uye.durum);
				fprintf(fp,"%s %s %s %d %d",uye.ad,uye.soyad,uye.unvan,uye.id,uye.durum);
			}
			fclose(fp);
			fclose(fp_t);
			printf("Ogretim uyesi durumu degistirildi.\n");
		}
		else{
			printf("Beklenmedik karakter.\n")
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
	
	if(fp=fopen("Ogrenciler.txt","a+")==NULL){
		printf("Dosya acilamadi.\n");
		return;
	}
	
	while (!feof(fp)){
		fscanf(fp,"%s %s %s %d %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no,&ogr.durum);
		if (strcmp(input.no,ogr.no)==0 && ogr.durum==1){
			printf("Ayni numarali ogrenci bulunuyor.\n");
			fclose(fp);
			return;
		}
	}
	
	fprintf(fp,"%s %s %s %d %d %d",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no,ogr.durum);
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
		fscanf(fp,"%s %s %s %d %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no,&ogr.durum);
		
		if (strcmp(no,ogr.no)==0 && ogr.durum==0){
			printf("Bu ders zaten silinmis.\n");
			fclose(fp);
			return;
		}
		else if (strcmp(no,ogr.no)==0 && ogr.durum==1){
			ogr_kontrol=1;
			fclose(fp);
		}
	}
	
	if (ders_kontrol==1){
		FILE *fp_t=fopen("tmp.txt","w");
		fp=fopen("Ogrenciler.txt","r");
		
		while (!feof(fp)){
			fscanf(fp,"%s %s %s %d %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no,&ogr.durum);
			if (strcmp(no,ogr.no)==0){
				ogr.durum=0;
			}
			
			fprintf(fp_t,"%s %s %s %d %d %d",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no,ogr.durum);
		}
		fclose(fp);
		fclose(fp_t);
		
		fp=fopen("Ogrenciler.txt","w");
		fp_t=fopen("tmp.txt","r");
		
		while(!feof(fp_t)){
			fprintf(fp,"%s %s %s %d %d %d",ogr.ad,ogr.soyad,ogr.no,ogr.kredi,ogr.ders_no,ogr.durum);
		}
		fclose(fp);
		fclose(fp_t);
		printf("Ogrenci basariyla silindi.\n");
	}
	else{
		fclose(fp);
		printf("Bu numarada bir ogrenci bulunmamaktadir.\n");
	}	
}
void ogrenci_guncelle(){
	FILE *fp;
	char no[11];
	OGRENCI ogr;
	int ogr_kontrol=0;
	
	printf("--------OGRENCI GUNCELLE-----------\n");
	printf("Guncellemek istediginiz ogrencinin numarasini giriniz:");
	scanf("%s",no);
	
	fp=fopen("Ogrenciler.txt","a+");
	
	while ((!feof(fp)) && ogr_kontrol!=1){
		fscanf(fp,"%s %s %s %d %d %d",ogr.ad,ogr.soyad,ogr.no,&ogr.kredi,&ogr.ders_no,&ogr.durum);
		if (strcmp(no,ogr.no)==0) ogr_kontrol=1;
		
	}
	fclose(fp);
	
	if (ders_kontrol==0){
		printf("Bu numarada bir ogrenci bulunmuyor.\n");
		return;
	}
	
	else{
		char secim[1];
		printf("Ogrencinin hangi ozelligini guncellemek istersiniz?\n");
		printf("0:No\n1:Durum");
		printf("\nSecim:");
		scanf("%s",secim);
		
		
		
		
		
	}
	
	
}
















