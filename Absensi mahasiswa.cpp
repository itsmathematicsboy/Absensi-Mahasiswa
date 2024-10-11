#include<iostream>
#include<conio.h>
#include<fstream>
#include<cstring>

using namespace std;

class mahasiswa //class yang memuat data mahasiswa
{
public:
	char nama[50];
	char kehadiran[20][2];
	int hadir=0;
	int nrp;
	float persen;
}; 
mahasiswa mhs[30]; //objek dari class mahasiswa dibuat ARRAY

void dataMasuk(int i) //Fungsi ketika mengisi data2 awal mahasiswa (hanya dilakukan sekali)
{
	ofstream datamhs("data.dat"); //membuat file(database) yang memuat data2 pada class mahasiswa
	cout << "Input Data Mahasiswa Ke-" << i + 1 << endl;
	cout << "NRP\t: ";	cin >> mhs[i].nrp;
	cout << "Nama\t: "; cin >> mhs[i].nama;

	datamhs.write((char*)&mhs, sizeof(mhs)); //menyimpan data
	datamhs.close(); //menutup data

}

void dataPresensi(int j, int minggu) //fungsi ketika mahasiswa melakukan presensi
{
	ifstream bukadata("data.dat"); //membuka data yang sudah dibuat
	bukadata.read((char*)&mhs, sizeof(mhs)); 
	
	cout << mhs[j].nrp <<"\t"<< mhs[j].nama<<"\t";
	cout << "\t Kehadiran[H/A/I/S]: ";
	fflush(stdin); //menghapus buffer
	cin >> mhs[j].kehadiran[minggu]; //mengisi data kehadiran per pertemuan

	ofstream simpandata("data.dat"); //menyimpan data yang telah diupdate
	simpandata.write((char*)&mhs, sizeof(mhs));

	bukadata.close(); 
	simpandata.close();
}

void rekapData(int banyakMhs) //fungsi ketika semua data kehadiran direkap
{
	int i, j;
	int banding;
	ifstream fileRekap("data.dat");
	fileRekap.read((char*)&mhs, sizeof(mhs));

	cout << "NRP\t\tNama\t\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t%" << endl << endl;
	for (i = 0; i < banyakMhs; i++)
	{
		cout << mhs[i].nrp <<"\t"<< mhs[i].nama<<"\t\t";
		for (j = 0; j < 10; j++)
		{
			cout << mhs[i].kehadiran[j]<<"\t";
			
			banding = _strcmpi(mhs[i].kehadiran[j], "H"); //proses mengambil nilai jika absensi H
			if (banding == 0)
			{
				mhs[i].hadir += 1;
			}
		}
		mhs[i].persen = mhs[i].hadir*100/10;
		cout << mhs[i].persen;
		cout << endl;
	}

	fileRekap.close();
}

int main()
{
	int i, n = 3;
	int x; int Minggu=0
		;
	int pilihan;
	char lagi;
	cout << "Pilih Opsi" << endl;
	cout << "1. Masukkan data Mahasiswa\n2. Presensi Mahasiswa\n3. Rekap Data" << endl;
	cout << "Pilihan: ";
	cin >> pilihan;
	system("cls");
	switch (pilihan)
	{
	case 1:
	{
		for (i = 0; i < n; i++)
		{
			dataMasuk(i);
			system("cls");
		}
		
	} break;

	case 2:
	{
		do{
			cout << "Absensi Minggu ke-" << Minggu + 1 << endl;

			for (x = 0; x < n; x++) //n merupakan banyaknya mahasiswa
			{
				dataPresensi(x, Minggu);
			}
			cout << "Absensi Minggu Berikutnya[Y/N]= ";
			cin >> lagi;
			Minggu++;
		} while (lagi == 'y' || lagi == 'Y');
		
	}break;

	case 3:
	{
		rekapData(n);
	}break;

	default: cout << "pilihan salah";
	}

	_getch();

}
