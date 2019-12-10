#include<stdio.h> 
#include<string.h>
#include<Windows.h>

#define f fflush(stdin) // melakukan define f = fflush(stdin) agar saat melakukan fflush(stdin) lebih singkat

int index = 0; // menyiapkan index = 0
int itemDelete, totalDelete; // itemDelete untuk nomor/pilihan mana yang nantinya akan dihapus dengan jumlah totalDelete(jumlah barang yang akan dihapus)
char generate[10]; // menampung input user untuk melakukan generate ulang
bool cek = false; // boolean cek untuk mengecek program dalam kondisi tertentu

struct itemStock{
	char itemName[1000] ; // memesan 1000 kolom array 
	int itemAmount; 
	int itemPrice;
}itS[1000]; // memesan 1000 kolong array
//akses struct dengan itS. lalu identifier dari struct

// function prototype:
void loadData();
void saveData();
int getInt(int input, int lower, int upper, char* sentence);
int getInput();
void generateAgain();
void namaBarang();
void jumlahBarang();
void hargaBarang();
void caseOne();
void pilihHapus();
void pilihanHapus();
void jumlahHapus();
void caseTwo();
void caseThree();
void caseFour();
void welcome();
void closeProgram();

int main(){

	loadData();
	int input;
	welcome();
	while(true){
		input = getInput();
		system("cls");
		if(input == 5){
			closeProgram();
			break;
		}
		switch(input){
		case 1:
			caseOne();
			break;
		case 2:
			caseTwo();
			break;
		case 3:
			caseThree();
			break;
		case 4:
			caseFour();
			break;
		}
	}
	saveData();

	getchar();
	return 0;
}

void loadData(){ 
	FILE *open = fopen("stokbarang.txt", "r"); // membuka file yang telah dibuat sesuai fopen dan mode 'r' untuk membaca file
	if(open == NULL){ // apabila file tidak ditemukan, maka dilanjutkan statement dibawah
		return; // return void(tidak mengembalikan apa-apa)
	}
	else{
		while(!feof(open)){ // apabila belum mencapai end of file(akhir dari data dalam file), maka dilakukan statement dibawah dan dilakukan looping sampai kondisi while(!fopen(open)) benar
			fscanf(open, "%[^|]|%d|%d\n", &itS[index].itemName, &itS[index].itemAmount, &itS[index].itemPrice); // membaca dan mengoper semua data ke array yang telah disiapkan dari file stokbarang.txt
			index++;
			cek = true;
		}
	}
	fclose(open); // file ditutup kembali setelah digunakan
}

void saveData(){
	FILE *close = fopen("stokbarang.txt", "w"); // membuka file yang telah dibuat sesuai fopen dan mode 'w' untuk menambahkan data ke dalam file/membuat file baru
	for(int i = 0; i < index; i++){
		fprintf(close, "%s|%d|%d\n", itS[i].itemName, itS[i].itemAmount, itS[i].itemPrice); // menambahkan semua data yang ada dan di tulis ke dalam file stokbarang.txt
	}
	fclose(close);// file ditutup kembali setelah digunakan
}

int getInt(int input, int lower, int upper, char* sentence){ // menyiapkan argumen dalam function 'getInt' yang nantinya akan dioperkan value/nilai tertentu
	do{
		printf("%s", sentence); // melakukan print string yang dioper dari function lain
		scanf("%d", &input); f; // melakukan scan data type integer yang dioper dari function lain
	}while(input < lower || input > upper); // validasi input kecil dari lower(value lower akan dioper dari function lain) atau input besar dari upper(value uppe akan dioper dari function lain) maka akan dilakukan looping
	return input; // mengembalikan nilai input | wajib melakukan return function data typenya adalah 'int'
}

int getInput(){
	int input = 0;
	printf("1. Masukkan stok barang \n"); // print pilihan menu 1
	printf("2. Kurangi jumlah stok barang \n"); // print pilihan menu 1
	printf("3. Tampilkan stok barang \n"); // print pilihan menu 1
	printf("4. Hapus semua stok barang \n"); // print pilihan menu 1
	printf("5. Keluar dari program\n\n"); // print pilihan menu 1
	return getInt(input, 1, 5, "Masukkan Pilihan Anda [1-5] : "); // mengembalikan function 'getInt' dengan parameter : input, 1, 5, dan "Masukkan Pilihan Anda [1-4] : "
}

// untuk function data typenya 'void' tidak perlu melakukan return
void generateAgain(){
	do{
		printf("Masukkan stok barang lagi? [Yes][No] : "); // print pilihan generate [Yes]/[No]
		scanf("%s", &generate); f; // melakukan scan terhadap array of char 'generate[10]' 
	}while(strcmpi(generate, "No") != 0 && strcmpi(generate, "Yes") != 0); // melakukan komparasi antara generate dengan "No" dan generate dengan "Yes"(tidak case sensitive), apabila tidak sama dengan "Yes"/"No", maka akan dilakukan looping
}

void namaBarang(){
	printf("Masukkan nama barang!   : "); 
	scanf("%[^\n]", &itS[index].itemName); f; 
}

void jumlahBarang(){
	do{
		printf("Masukkan jumlah barang! : ");
		scanf("%d", &itS[index].itemAmount); f;
	}while(itS[index].itemAmount < 1 || itS[index].itemAmount > 10000001); // validasi itS[index].itemAmount kecil dari 1(karena jumlah barang harus lebih dari 0) atau itS[index].itemAmount lebih dari 10000001
}

void hargaBarang(){
	do{
		printf("Masukkan harga barang!  : ");
		scanf("%d", &itS[index].itemPrice); f;
	}while(itS[index].itemPrice < 1 || itS[index].itemPrice > 10000000001); // validasi itS[index].itemPrice kurang dari 1 atau itS[index].itemPrice > 10000000001
}

void caseOne(){ // menu program untuk case input '1'
	do{
		namaBarang(); // input nama barang 
		jumlahBarang(); // input jumlah barang
		hargaBarang(); // input harga barang
		index++; // menambahkan jumlah index sebanyak 1
		generateAgain(); // menjalankan function 'generateAgain()' yang sudah ada di atas
	}while(strcmpi(generate, "Yes") == 0); // validasi komparasi generate apabila input sama dengan "Yes", maka akan dilakukan looping
	cek = true; // boolean cek berubah menjadi 'true'
	system("cls"); // melakukan pembersihan layar console
}

void pilihHapus(){
	do{
		printf("Stok barang nomor berapa yang ingin anda hapus? : ");
		scanf("%d", &itemDelete); f;
	}while(itemDelete < 1 || itemDelete > index); // validasi itemDelete tidak boleh kurang dari 1 atau itemDelete besar dari index karena pilihan belum tersedia/terdata
}

void pilihanHapus(){
	printf("-----------------------------------------------------------------------------------------\n");
	printf("[ %-2d.| %-35s | %-20d | Rp. %-15d ]\n", itemDelete, itS[itemDelete-1].itemName, itS[itemDelete-1].itemAmount, itS[itemDelete-1].itemPrice); // menampilkan pilihan nomor 
	printf("-----------------------------------------------------------------------------------------\n");
}

void jumlahHapus(){
	do{
		printf("Berapa banyak stok barang yang ingin anda hapus? : ");
		scanf("%d", &totalDelete); f;
	}while(totalDelete < 0 || totalDelete > itS[itemDelete-1].itemAmount); // validasi totalDelete tidak boleh kurang dari 0 atau totalDelete lebih dari jumlah barang yang terdata
	itS[itemDelete-1].itemAmount = itS[itemDelete-1].itemAmount - totalDelete; // operasi pengurangan jumlah barang yang telah dipilih tadi
}

void caseTwo(){ // menu program untuk case input '2'
	if(cek == false){ // apabila user belum menggunakan menu '1'(otomatis data belum ada), maka dilakukan statement di bawah
		printf("%65s", "Stok Barang Anda Kosong!");
		getchar();
	}
	else { // apabila user sudah menggunakan menu '1', maka boolean cek berubah menjadi true dan statement dibawah dijalankan
		do{
			pilihHapus(); // pilihan yang akan dihapus
			pilihanHapus(); // menampilkan pilihan yang akan dikurangi jumlah barangnya
			jumlahHapus(); // jumlah barang yang akan dihapus
			generateAgain(); // menjalankan function 'generateAgain()'
		}while(strcmpi(generate, "Yes") == 0); // validasi komparasi generate dengan "Yes", jika sama maka dilakukan looping
	}
	system("cls");
}

void caseThree(){ // menu program untuk case input '3'
	if(cek == false){ // apabila user belum menggunakan menu '1' atau melakukan menu '4', maka boolean cek == false dan dilakukan statement di bawah
		printf("%65s", "Stok Barang Anda Kosong!");
	}
	else{ // user sudah menggunakan menu '1' dan tidak menggunakan menu '4' setelah melakukan menu '1', statement di bawah dijalankan
		printf("[ %-2s | %-35s | %-20s | %-20s]\n", "No", "Nama Barang", "Jumlah Barang", "Harga Barang");
		printf("-----------------------------------------------------------------------------------------\n");
		for(int i = 0; i < index; i++){
			printf("[ %-2d.| %-35s | %-20d | Rp. %-15d ]\n", i + 1, itS[i].itemName, itS[i].itemAmount, itS[i].itemPrice); // print seluruh data yang sudah terdata
		}
		printf("========================================================================================="); 
	}
	getchar();
	system("cls");
}

void caseFour(){
	index = 0, cek = false; // menghapus seluruh data dan boolean cek berubah menjadi false
	printf("%80s", "Semua Stok Barang Anda Telah Berhasil Dihapus!");
	getchar();
	system("cls");
}

void welcome(){ // melakukukan statement dibawah untuk program baru dijalankan
	printf("--------------------------------------------------------------------------------------- \n");
	printf("-----------------------------Selamat Datang di Program Ini----------------------------- \n");
	printf("--------------------------------------------------------------------------------------- \n");
	getchar(); // menahan layar sebelum menekan enter
	system("cls"); // melakukan pembersihan layar console
}

void closeProgram(){ // melakukan statement dibawah untuk program exit / menu '5'
	system("cls"); // melakukan pembersihan layar console 
	printf("--------------------------------------------------------------------------------------- \n");
	printf("----------------------Terima Kasih Telah Menggunakan Program Ini----------------------- \n");
	printf("--------------------------------------------------------------------------------------- \n");
}