#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <sstream>

using namespace std;

class CSVReader{
    /*
    * csv dosyasındaki verileri okuyacak class tanımı
    */
	string fileName;
	string delimeter;

public:
	CSVReader(string filename, string delm = ";") :
			fileName(filename), delimeter(delm)
	{ }

	// veriyi parçalayan vektör foknsiyonu
	vector<vector<string> > getData();
};

vector<vector<string> > CSVReader::getData(){//csv dosyasındaki verileri satır satır ayrıştırıp vektör şekline getirir
	ifstream file(fileName);
	vector<std::vector<std::string> > dataList;
	string line = "";
	while (getline(file, line))
	{
		vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
		dataList.push_back(vec);
	}
	// dosyayı kapatır
	file.close();

	return dataList;
}

int end;
int location=0;
string fileName="Cam.bin";
int totalRecordLength=72,modelLength=30,otherLength=6;

class Camera{
    public:
        string model;
	char model2[30];
        string relDate;
        string resol;
        string zoom;
        string fRange;
        string storage;
        string weight;
        string price;
};

    void addCam(int loca, Camera *cam){//dosyaya cam nesnesini yazmasını yapar
            fstream myFile (fileName, ios::out |ios::in | ios::binary);
            myFile.seekp (loca);
            myFile.write(cam->model.c_str(),modelLength);
            loca+=modelLength;
            myFile.seekp (loca);
            myFile.write(cam->relDate.c_str(),otherLength);
            loca+=otherLength;
            myFile.seekp (loca);
            myFile.write(cam->resol.c_str(),otherLength);
            loca+=otherLength;
            myFile.seekp (loca);
            myFile.write(cam->zoom.c_str(),otherLength);
            loca+=otherLength;
            myFile.seekp (loca);
            myFile.write(cam->fRange.c_str(),otherLength);
            loca+=otherLength;
            myFile.seekp (loca);
            myFile.write(cam->storage.c_str(),otherLength);
            loca+=otherLength;
            myFile.seekp (loca);
            myFile.write(cam->weight.c_str(),otherLength);
            loca+=otherLength;
            myFile.seekp (loca);
            myFile.write(cam->price.c_str(),otherLength);
            loca+=otherLength;
            myFile.close();
        }

        string charToString(char * ch){//chardan stringe çeviren fonksiyon
            stringstream ss;
            ss<<ch;
            string s;
            ss>>s;
            return s;
        }
        void getCam(int loca, Camera *cam){// dosyadan cam nesnesini okur
            fstream myFile (fileName, ios::in | ios::out | ios::binary);
            char tmp[31];
            myFile.seekg (loca);
            myFile.read(cam->model2,modelLength);
            loca+=modelLength;
            myFile.seekg (loca);
            myFile.read(tmp,otherLength);
            cam->relDate=charToString(tmp);
            loca+=otherLength;
            myFile.seekg (loca);
            myFile.read(tmp,otherLength);
            cam->resol=charToString(tmp);
            loca+=otherLength;
            myFile.seekg (loca);
            myFile.read(tmp,otherLength);
            cam->zoom=charToString(tmp);
            loca+=otherLength;
            myFile.seekg (loca);
            myFile.read(tmp,otherLength);
            cam->fRange=charToString(tmp);
            loca+=otherLength;
            myFile.seekg (loca);
            myFile.read(tmp,otherLength);
            cam->storage=charToString(tmp);
            loca+=otherLength;
            myFile.seekg (loca);
            myFile.read(tmp,otherLength);
            cam->weight=charToString(tmp);
            loca+=otherLength;
            myFile.seekg (loca);
            myFile.read(tmp,otherLength);
            cam->price=charToString(tmp);
            loca+=otherLength;
            myFile.close();
        }
         int getCamCount(){//dosyadaki veri sayısını döner
            return (int)location/totalRecordLength;
         }




        void giris(){	//arayüz
	cout << "\n******************************";
	cout << "\nGIRIS EKRANI";
	cout << "\n\n1 : KULLANICI\n2 : YONETICI\n3 : CIKIS\n\n";
	cout << ">> Tercihiniz: ";
	}

	void katalogSistemi(){	//arayüz
	cout << "\n******************************";
	cout << "\nKULLANICI KATALOG SISTEMI";
	cout << "\n\n1 : Kamera adina gore ara \n2 : Geri";
	cout << "\n\n>> Tercihiniz: ";
    }

    void katalogSistemi2(){	//arayüz
        cout << "\n******************************";
        cout << "\nYONETICI KATALOG SISTEMI";
        cout << "\n\n1 : Listele ";
        cout << "\n2 : girise don";
        cout << "\n3 : Girdi sayisini goster";
        cout << "\n\n>> Tercihiniz: ";
    }

    void camadinagoreara(){
	fstream myFile ("Cam.bin", ios::in | ios::out | ios::binary);
	cout << "*****Kamera Arama***********\n";
	bool bulundu=false; //kamerayı bulup bulamadığımı tutan bool degeri.
	char ad[40];
	string ad2;
	int yer=0; 			//bin dosyasındaki indeks
	cout << "\n>> Kamera adi giriniz : \n";
	scanf("%s",ad);
	getline(cin , ad2);
	strcat(ad,ad2.c_str());
	cout << ad << " araniyor";
                while(true){
                    if(yer>=location){	//indeksimizin sınırını gösteriyor. eğer totalRecordLength'a ulaşırsak arama bitirilecek.
                        break;
                    }
			Camera cam;
			getCam(yer,&cam);
cout << cam.model2 << endl;
                        if(strcmp(cam.model2,ad)==0){
                            cout << "bulundu";
                            bulundu=true;
                            break;
                        }

                    yer+=72;
                }
                if(!bulundu){
                    cout << "\n" << ad << ", bulunamadi.";
                }
	myFile.close();
}

    void excelToBinary(){
        CSVReader reader("Camera.csv");

        vector<vector<string> > dataList = reader.getData();// csv dosyasındaki veriyi çağırır
        int vektorr=0;
        // vektör içindeki veriyi sıra sıra kontrol edip ayrıştırıyoruz.1.sıra model 2.sıra date ....
        for(vector<string> vec : dataList){
            int valueCount=0;
            Camera *cam;
            cam=new Camera;
            if(vektorr>1){
                    for(int i=0; i<8; ++i){
                         switch(valueCount){
                            case 0: cam->model =vec[i];break;
                            case 1: cam->relDate=vec[i];break;
                            case 2: cam->resol=vec[i];break;
                            case 3: cam->zoom =vec[i];break;
                            case 4: cam->fRange=vec[i]; break;
                            case 5: cam->storage=vec[i];break;
                            case 6: cam->weight =vec[i];break;
                            case 7: cam->price=vec[i];break;
                            default : cout<<"8 nolu girdi geldi"<<endl;
                        }
                        valueCount++;
                    }
                    addCam(location,cam);
                    location+=totalRecordLength;
            }
            vektorr++;
        }

    }

	void listed(){
		fstream myFile ("Cam.bin", ios::in | ios::out | ios::binary);
		int yer =0;
		cout << "*****Kamera Listesi***********\n";
		while(yer<location){
			Camera cam;
			getCam(yer,&cam);
		    cout << cam.model2 <<" "<<cam.relDate << endl;
		    yer+=72;
		}
		myFile.close();
	}

int main(){
	excelToBinary();
	//listed();
   	int tercih=-1,tercih2=-2,tercih3=-3;
    giris();
    cin >> tercih;


	do{
	 	switch(tercih){
	 		case 1:
				katalogSistemi(); cin >> tercih2;
					switch(tercih2){
				 		case 1: camadinagoreara(); break;
				 		case 2: giris(); cin >> tercih; break;
					}
					break;
	 		case 2: katalogSistemi2(); cin >> tercih3;

                        		switch(tercih3){
                            			case 1: listed();break;
                            			case 2: giris(); cin >> tercih;break;
                            			case 3: cout << "kamera sayisi: "<< getCamCount(); int a;cin >> a;break;
                        		}
                        		break;
	 		case 3: break;
	 		default:giris(); cin >> tercih; break;
		 }
	 }while(tercih!=3);
	return 0;
}
