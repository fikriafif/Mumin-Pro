#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <windows.h>


//This block of codes was made by M. Raihan Azhari//
//------------------------------------------------
struct amalan{
	
	//variabel amanalan ibadah harian
	int tahajud;
	int dhuha;
	int wajib;
	int tilawah;
	int tahfidz;
	
	struct amalan *next;
};


typedef struct User{
	
	//variabel data user pengguna aplikasi (hanya 1 user)
	char nama[30];
	int target_status;
	int target_tahajud, target_dhuha, target_wajib;
	int target_tilawah, target_tahfidz;
	int day;
	
	struct amalan *data;
}User;



typedef struct amalan Amalan;
typedef Amalan *Amalanptr;

//end of codes block
//----------------------------------------------------


void input_data(Amalanptr *sptr);
void input_menu();
void printAmalan(Amalanptr current, int day_removed[50], User *userptr);
void print_evaluasi(Amalanptr current, User *userptr , int day_removed[50]);
void removeptr (Amalanptr *startPtr, int day, int day_removed[50]);
int file_user_read (User *userptr, int day_removed[50]);
int file_user_write (User *userptr, int day_removed[50]);
int file_amalan_write (Amalanptr current, int day_removed[50]);
int file_amalan_read (Amalanptr *sptr, int day_removed[50], int i, int *posisi);
void welcome(User *userptr);
void help_mutabaah();
int file_removed_write(int day[50]);
int file_removed_read(int day[50]);






int main(){
	

	FILE *fptr;
	
	int menu, day, i, j, id_input,id, mutabaah, status, login, login_status, file_status, posisi;
	int day_removed[50] = {}; //array untuk mengetahui hari yang telah di remove
	
	//set variabel ke 0 untuk mencegah adanya garbage value
	menu = 0;
	mutabaah = 0;
	id = 0;

	//struct user dalam fungsi ini dapat dipanggil melalui pointer *userptr
	User *userptr;
	userptr = (User*) calloc(1, 2 * sizeof(User));
	/*Tadinya kami ingin membuat multi-user berdasarka idnya, namun karena kesulitan pada file handling maka
		kami membuat 1 user saja, namun tetap menggunakan pointer struct*/
	
	
	Amalanptr startptr = NULL;
	
	file_status = file_user_read(userptr, day_removed);
	file_removed_read(day_removed);
	
	posisi = 0;
	
	if((userptr + id)->day == 0){
		file_amalan_read(&startptr, day_removed, 0, &posisi);
	}
	
	else{
	
		for(i = 0; i < (userptr + id)->day - 1; i++){
			file_amalan_read(&startptr, day_removed, i, &posisi);
		}
		
		file_amalan_read(&startptr, day_removed, -1, &posisi);
	}
	
	(userptr + id)->data = startptr; 
	
	
	
	
	while (menu != -1){
		welcome(userptr);
		login_status = 1;
		printf("\nMasukan angka: ");
		scanf("%d", &menu);
		system("cls");
		
		mutabaah = 0;

		switch (menu){
			case 1: 
			//---------------------------------------------------
			//case 1 (Mutaba'ah Yaumiah) was made by M. Raihan Azhari
			
				
				while(mutabaah != -1){
					help_mutabaah();
					printf("\nMasukan pilihan metode mutabaah: ");
					scanf("%d", &mutabaah);
					system("cls");
					switch (mutabaah){
						
					case 1:
						(userptr + id)->target_status = 1;
						//coba masukin ke fungsi
						//printf("\nuser ID: %d", id);
						printf("\nMasukan Nama : ");
						scanf("%s", &(userptr + id)->nama);
						printf("\n Masukan Target Rakaat Tahajud: ");
						scanf("%d", &(userptr + id)->target_tahajud);
						printf("\n Masukan Target Rakaat Dhuha: ");
						scanf("%d", &(userptr + id)->target_dhuha);
						
						(userptr + id)->target_wajib = 5;
						printf("\n Masukan Target Halaman Tilawah: ");
						scanf("%d", &(userptr + id)->target_tilawah);
						printf("\n Masukan Target Ayat Tahfidz: ");
						scanf("%d", &(userptr + id)->target_tahfidz);
						printf("\n\n");
						system("pause");
						system("cls");
						break;
						
					case 2:
						//input mutabaah
						//nanti mainin file handling disini
						
						if((userptr + id)->target_status != 1){
							printf("\nHarap masukan target terlebih dahulu\n\n");
							system("pause");
							system("cls");
							break;
						}
						
						
						printf("\nAssalamualaikum %s", (userptr + id)->nama);
						printf("\nMasukan jumlah hari yang akan diinput: ");
						scanf("%d", &day);
						for(i = 0; i < day; i++){
							printf("\n\nAmalan hari ke-%d", (userptr->day) + i + 1);
							input_data(&startptr);
						}
						
						(userptr + id)->data = startptr; 
						system("cls");
	
						printf("\n\ninput berhasil !\n");
						printAmalan((userptr + id)->data, day_removed, userptr);
						printf("\n\n");
						system("pause");
						system("cls");
						break;
						
					case 3:
						
						if((userptr + id)->target_status != 1){
							printf("\nHarap masukan target terlebih dahulu\n\n");
							system("pause");
							system("cls");
							break;
						}
						printAmalan((userptr + id)->data, day_removed, userptr);
						printf("\n\n");
						system("pause");
						system("cls");
						print_evaluasi((userptr + id)->data, userptr, day_removed);
						printf("\n\n");
						system("pause");
						system("cls"); 
						break;
					case 4:
						if((userptr + id)->target_status != 1){
							printf("\nHarap masukan target terlebih dahulu\n\n");
							system("pause");
							system("cls");
							break;
						}
						printf("Pilih hari yang akan dihapus: ");
						scanf("%d", &day);
						day--;
						removeptr (&startptr, day, day_removed);
						day_removed[day] = 1;
						printf("\nData hari ke-%d berhasil dihapus\n\n", day+1);
						system("pause");
						system("cls");
						
				}
					
			}
			//end of codes block
			//---------------------------------------------------------
			
			case 2:
				//zakat
				break;
			case 3:
				//waris
				break;
		}
		
	}
	
	file_user_write(userptr, day_removed);
	file_amalan_write((userptr + id)->data, day_removed);
	file_removed_write(day_removed);
	return 0;
		
}


//--------------------------------------------------------
//This function was made by M. Raihan Azhari
void input_data(Amalanptr *sptr){
	
//	int sks_var, kode_var, bobot_var, status_var, condition;
//	char nilai_var;
	
	
	Amalanptr currentptr;
	Amalanptr newptr;
	Amalanptr prevptr;
	
	newptr = malloc(sizeof(Amalan));
	
	//masukin kode input variabel apa aja disini
	
	printf("\nMasukan amalan");
	printf("\nRakaat Tahajud: ");
	scanf("%d", &newptr->tahajud);
	printf("Rakaat Dhuha: ");
	scanf("%d", &newptr->dhuha);
	printf("Banyak Sholat Wajib yang Dikerjakan: ");
	scanf("%d", &newptr->wajib);
	printf("Jumlah Halaman Tilawah: ");
	scanf("%d", &newptr->tilawah);
	printf("Jumlah Ayat Tahfidz: ");
	scanf("%d", &newptr->tahfidz );

	newptr->next = NULL;
	
	prevptr = NULL;
	
	currentptr = *sptr;
	
	while(currentptr != NULL){
		prevptr = currentptr;
		currentptr = currentptr->next;
	}
	
	if (prevptr == NULL){
		newptr->next = *sptr;
		*sptr = newptr;
	}
	
	else{
		prevptr->next = newptr;
		newptr->next = currentptr;
	}
	
	
}
//end of codes block
//----------------------------------------------------


//---------------------------------------------------
//This function was made by M. Raihan Azhari
void printAmalan(Amalanptr current, int day_removed[50], User *userptr){
	
	//ini masih yang matkul blm gw ganti hehe
	int counter;
	counter = 0;
	
	while(current != NULL){
		
		if(day_removed[counter] == 1){
			printf("\n\nRekap ibadah hari ke-%d telah dihapus \n", counter + 1);
		}
		else{
			
		#pragma omp parallel
		{
			int tid;
		
			tid = omp_get_thread_num();
			
			#pragma omp single
			{
				printf("\n\nRekap ibadah hari ke-%d:", counter + 1);	
			}
			
			#pragma omp taskwait
			
			if(tid == 0){
				printf("\nTahajud : %d Rakaat",current->tahajud);
				printf("\nDhuha : %d Rakaat",current->dhuha);
				printf("\nWajib : %d Waktu",current->wajib);
			
			}
		
			if (tid == 1){				
			printf("\nTilawah : %d Halaman",current->tilawah);
			printf("\nTahfidz : %d Ayat",current->tahfidz);
			}
			
			#pragma omp taskwait
		
		}
	}
		current = current->next;
		counter++;
	}
	
	userptr->day = counter;
	
	
}

//end of codes block
//------------------------------------------------------------


//-------------------------------------------------------------
//this function was made by M. Raihan Azhari
void print_evaluasi(Amalanptr current, User *userptr , int day_removed[50]){
	
	int counter, i;
	int jumlah_tahajud, jumlah_dhuha, jumlah_wajib, jumlah_tilawah, jumlah_tahfidz, avg, tugas, step;
	
	jumlah_tahajud = 0;
	jumlah_dhuha = 0;
	jumlah_wajib = 0;
	jumlah_tilawah = 0;
	jumlah_tahfidz = 0;
	counter = 0;
	
	
	
	while (current != NULL){
		
		jumlah_tahajud += current->tahajud;
		jumlah_dhuha += current->dhuha;
		jumlah_wajib += current->wajib;
		jumlah_tilawah += current->tilawah;
		jumlah_tahfidz += current->tahfidz;
		counter ++;
		
		current = current->next;
	
	}
	
	userptr->day = counter;
	
	
	if(counter == 0){
		printf("Data masih kosong");
	}
	
	else{
		printf("\n Evaluasi ibadah harian selama %d hari: ", counter);
		tugas = 0;
		step = 0;
		
		#pragma omp parallel private(tugas, step)
		{
			#pragma omp master
			{
				for(i = step; i < 5; i++){
					tugas = i;
					step = i;
					#pragma omp task
					{
						if (tugas == 0 && userptr->target_tahajud != 0){
							float rata_tahajud = jumlah_tahajud / (float)counter;
							float result_tahajud = rata_tahajud /(float) userptr->target_tahajud;
							#pragma omp critical
							{
								printf("\n\n~~Tahajud~~ ");
								printf("\nRata-rata Rakaat setiap harinya : %.2f", rata_tahajud);
								printf("\nPersen ketercapaian target: %.2f %", result_tahajud * 100);
							}
						}
						
						if(tugas == 1 && userptr->target_dhuha != 0){
							float rata_dhuha = jumlah_dhuha / (float)counter;
							float result_dhuha = rata_dhuha /(float)userptr->target_dhuha;
							#pragma omp critical
							{
								printf("\n\n~~Dhuha~~ ");
								printf("\nRata-rata Rakaat setiap harinya : %.2f", rata_dhuha);
								printf("\nPersen ketercapaian target: %.2f %", result_dhuha * 100);
							}
						}
						
						if(tugas == 2 && userptr->target_wajib != 0){
							float rata_wajib = jumlah_wajib / (float)counter;
							float result_wajib = rata_wajib /(float)userptr->target_wajib;
							#pragma omp critical
							{
								printf("\n\n~~Sholat wajib 5 waktu~~ ");
								printf("\nRata-rata Rakaat setiap harinya : %.2f", rata_wajib);
								printf("\nPersen ketercapaian target: %.2f %", result_wajib * 100);
							}
						}
						if(tugas == 3 && userptr->target_tilawah != 0){
							float rata_tilawah = jumlah_tilawah / (float)counter;
							float result_tilawah = rata_tilawah /(float)userptr->target_tilawah;
							#pragma omp critical
							{
								printf("\n\n~~Tilawah~~ ");
								printf("\nRata-rata Halaman setiap harinya : %.2f", rata_tilawah);
								printf("\nPersen ketercapaian target: %.2f %", result_tilawah * 100);
							}
						}
						if(tugas == 4 && userptr->target_tilawah != 0){
							float rata_tahfidz = jumlah_tahfidz / (float)counter;
							float result_tahfidz = rata_tahfidz /(float)userptr->target_tahfidz;
							#pragma omp critical
							{
									printf("\n\n~~Tahfidz~~ ");
									printf("\nRata-rata Halaman setiap harinya : %.2f", rata_tahfidz);
									printf("\nPersen ketercapaian target: %.2f %", result_tahfidz * 100);
		
							}
						}
						
					}
					
					
				}
			}
			
			#pragma omp taskwait
		}
		
	}
	
}

//-----------------------------------------------------------------------------------



//-----------------------------------------------
//Muhammad Raihan Azhari
void removeptr (Amalanptr *startPtr, int day, int day_removed[50]){
	
	Amalanptr prevPtr;
	Amalanptr tempPtr;
	Amalanptr currentPtr;
	
	int i, hari;
	
	day++;
	

	
	if ( day == 0) {
 		tempPtr = *startPtr;
		*startPtr = ( *startPtr )->next; 
 		free( tempPtr ); 
 	} 
 	else {
 		prevPtr = *startPtr;
 		currentPtr = ( *startPtr )->next;
 
 		for(i = 1; i < day; i++){
 			
 			if(day_removed[i]== 1){
 				continue;
			 }
 			
 			if (i == day) {
		 		tempPtr = currentPtr;
		 		prevPtr->next = currentPtr->next;
		 		free( tempPtr );
		 	} 
 			prevPtr = currentPtr; 
 			currentPtr = currentPtr->next;
		
		 	if(currentPtr == NULL) {
			 	break;
			 }
 		} 

 	
 	} 

 }
//------------------------------------------------------

//---------------------------------------------------
//Fikri Afif Musyaffa 
int file_user_read (User *userptr, int day_removed[50]){
	
	FILE *fptr;
	
	fptr = fopen("userMuslim.txt", "r");
	
	if(fptr == NULL){
	//	printf("\nFile user belmu dibuat");
		fclose(fptr);
		fptr = fopen("userMuslim.txt", "w");
		fclose(fptr);
		return 0;
	}
	else{	
		fseek(fptr, 0, SEEK_SET);
	//	printf("\nFile sudah dibuat");
		fscanf(fptr, "\n%s", &userptr->nama);
		fscanf(fptr, "\n%d", &userptr->target_status);
		fscanf(fptr, "\n%d", &userptr->target_tahajud);
		fscanf(fptr, "\n%d", &userptr->target_dhuha);
		fscanf(fptr, "\n%d", &userptr->target_wajib);
		fscanf(fptr, "\n%d", &userptr->target_tilawah);
		fscanf(fptr, "\n%d", &userptr->target_tahfidz);
		fscanf(fptr, "\n%d", &userptr->day);
		
	}
	
	
	
	fclose(fptr);
	return 1;

}
//--------------------------------------------------


//---------------------------------------------------
//Fikri Afif Musyaffa
int file_user_write (User *userptr, int day_removed[50]){
	
	FILE *fptr;
	
	fptr = fopen("userMuslim.txt", "w");
	
	fprintf(fptr, "\n%s", userptr->nama);
	fprintf(fptr, "\n%d", userptr->target_status);
	fprintf(fptr, "\n%d", userptr->target_tahajud);
	fprintf(fptr, "\n%d", userptr->target_dhuha);
	fprintf(fptr, "\n%d", userptr->target_wajib);
	fprintf(fptr, "\n%d", userptr->target_tilawah);
	fprintf(fptr, "\n%d", userptr->target_tahfidz);
	fprintf(fptr, "\n%d", userptr->day);
	fclose(fptr);
	
	
}

//---------------------------------------------------


//---------------------------------------------------
//M. Raihan Azhari
int file_amalan_read (Amalanptr *sptr, int day_removed[50], int i, int *posisi){
	
	FILE *fptr;
	
	
	int tahajud_var, dhuha_var, wajib_var, tilawah_var, tahfidz_var;
		
	Amalanptr currentptr;
	Amalanptr newptr;
	Amalanptr prevptr;
	
	newptr = malloc(sizeof(Amalan));
	
	if(i == 0){
		fptr = fopen("amalan.txt", "r");
	}
	
	
	if(fptr == NULL){
	//	printf("\nFile amalan belmu dibuat");
		fclose(fptr);
		fptr = fopen("userMuslim.txt", "w");
		fclose(fptr);
		return 0;
	}
	
	
	else{
		if(i == 0){
			fseek(fptr, 0, SEEK_SET);
		}
		
		else{
			fseek(fptr,  0 , SEEK_CUR);
		}
	//	printf("\nFile sudah dibuat");
		
		
		fscanf(fptr,"\n%d",&newptr->tahajud);
		fscanf(fptr,"\n%d",&newptr->dhuha);
		fscanf(fptr,"\n%d",&newptr->wajib);
		fscanf(fptr,"\n%d",&newptr->tilawah);
		fscanf(fptr,"\n%d",&newptr->tahfidz);
		
	
		newptr->next = NULL;
	
		prevptr = NULL;
	
		currentptr = *sptr;
	
		while(currentptr != NULL){
			prevptr = currentptr;
			currentptr = currentptr->next;
		}
	
		if (prevptr == NULL){
			newptr->next = *sptr;
			*sptr = newptr;
		}
	
		else{
			prevptr->next = newptr;
			newptr->next = currentptr;
		}
		
		if(i == -1){
			fclose(fptr);
		}
		
		
		
		return 1;
		
	}
	
	

}
//--------------------------------------------------


//---------------------------------------------------
//M. Raihan Azhari
int file_amalan_write (Amalanptr current, int day_removed[50]){
	
	FILE *fptr;
	
	fptr = fopen("amalan.txt", "w");
	
	while (current != NULL){
		
		fprintf(fptr,"\n%d",current->tahajud);
		fprintf(fptr,"\n%d",current->dhuha);
		fprintf(fptr,"\n%d",current->wajib);
		fprintf(fptr,"\n%d",current->tilawah);
		fprintf(fptr,"\n%d",current->tahfidz);
		
		current = current->next;
	
	}
	

	fclose(fptr);
	
	
}

//---------------------------------------------------


void welcome(User *userptr){
	
	int i, tid;
	
	
	#pragma omp for
	for(i = 0; i < 60; i++){
		printf("-");
	}
	
	#pragma omp barrier
	printf("\n\t\t\t Mu'min Pro\n");
	#pragma omp for
	for(i = 0; i < 60 ;i++){
		printf("-");
	}
	
	#pragma omp barrier
	
	printf("\nAssalamu'alaikum %s", (userptr)->nama);
	printf("\n\nMode Menu Mutabaah: ");
	printf("\n1. Mutaba'ah Yaumiah (Evaluasi Ibadah Harian)");
	printf("\n2. untuk Kalkulator Perhitungan Zakat");
	printf("\n3. untuk Kalkulator Perhitungan Waris\n\n" );
	
}

void help_mutabaah(){
	
	printf("\n1. Input Target Mutabaah");
	printf("\n2. Input Ibadah Harian");
	printf("\n3. Lihat Evaluasi Ibadah Harian");
	printf("\n4. Menghapus Ibadah Harian");
	printf("\n-1 Untuk keluar program");
	
}

int file_removed_write(int day[50]){
	
	FILE *fptr;
	
	fptr = fopen("removeday.txt", "w");
	
	int i;
	
	for(i = 0; i < 50; i++){
		fprintf(fptr, "\n%d", day[i]);
	}
	
	fclose(fptr);

	
}


int file_removed_read(int day[50]){
	
	FILE *fptr;
	
	fptr = fopen("removeday.txt", "r");
	
	if (fptr == NULL){
		fclose(fptr);
		fptr = fopen("removeday.txt", "w");
		fclose (fptr);
		return 0;
	}
	
	else{
		int i;
		
		for(i = 0 ; i < 50; i++){
			fscanf(fptr, "\n%d", &day[i]);
		}
		return 1;
	}
	
}
