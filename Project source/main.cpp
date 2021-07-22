#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

using namespace std;
//prototypes
void  normalizationForWSM(float **, int , int , float **);
void normalizationForWPM(float **,int ,int , float **);
void WASPAS_method(float **, int , int ,float *, float ,float *);
void inputForTable(float **, int , int );
void inputForRates(float *,int );
void outputForTable(float **, int , int );
void outputForRates(float *,int );

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void  normalizationForWSM(float **matrix, int rowSize, int columnSize, float **returnMatrix){
//Fayda kriterleri icin bu normalizasyon	
	int row=0;
	int column=0;
	
	//float  normalizedMatrix [rowSize][columnSize];
	float  maxValues [rowSize];
	
	
	// Max values per Rows
	for(row=0;row<rowSize;row++){
		
		float maxValue=matrix[row][0];
		
		for(column=0;column<columnSize;column++){
			
			if(maxValue<matrix[row][column]){
			
				maxValue=matrix[row][column];
				
			}
			
		}
		maxValues[row]=maxValue;
	}
	
	
	// Normalizing value
	for(row=0;row<rowSize;row++){
		
		float maxValueInRow=maxValues[row];
		
		for(column=0;column<columnSize;column++){
			
			float value=matrix[row][column];
			value=value / maxValueInRow;
			
			//updating the matrix
			//normalizedMatrix[row][column]=value;
			returnMatrix[row][column]=value;
		}
	}
	
	/*
	cout<<"Normalazing Out of last***********************************";
	outputForTable(returnMatrix,rowSize,columnSize);
	*/
}

void normalizationForWPM(float **matrix,int rowSize,int columnSize, float **returnMatrix){
//Maaliyet kriterleri icin bu normalizasyon	
	int row=0;
	int column=0;
	
	//float normalizedMatrix[rowSize][columnSize] ;
	float minValues[rowSize];
	
	
	// Min values per Rows
	for(row=0;row<rowSize;row++){
		
		float minValue=matrix[row][0];
		
		for(column=0;column<columnSize;column++){
			
			if(minValue>matrix[row][column]){
			
				minValue=matrix[row][column];
				
			}
			
		}
		minValues[row]=minValue;
	}
	
	
	// Normalizing value
	for(row=0;row<rowSize;row++){
		
		float minValueInRow=minValues[row];
		
		for(column=0;column<columnSize;column++){
			
			float value=matrix[row][column];
			
			
			value=minValueInRow / value;
			
			//updating the matrix
			returnMatrix[row][column]=value;
			
		}
	}
	/*
	//*returnMatrix = &normalizedMatrix[0][0];
	cout<<"Normalazing-2 last Row***********************************";
	outputForTable(returnMatrix,rowSize,columnSize);
	*/
	
	//return normalizedMatrix;
}

void WASPAS_method(float **valueMatrix, int valueMatrixRow, int valueMatrixColumn,float *rateMatrix, float rateMatrixSize,float *returnMatrix){
	
	//1-DECLARETING 
	
	//float WASPAS_value_matrix [valueMatrixColumn];
	//step 1  take a value point of a product
	int row=0,column=0;
	float alfa = 0.5; // alfa deðeri 0.5  kabul edilirse
	

	//float outOfLastRow[valueMatrixRow-1][valueMatrixColumn];
	//float firstLastRow[1][valueMatrixColumn];
	
	// dynamically create an array of pointers of size `M`
    float** outOfLastRow = new float*[valueMatrixRow-1];
    for (int i = 0; i < valueMatrixRow-1; i++) {
        outOfLastRow[i] = new float[valueMatrixColumn];
    }
	float** firstLastRow=new float*[1];
	for (int i = 0; i <1; i++) {
        firstLastRow[i] = new float[valueMatrixColumn];
    }
	
	
	//2-DIVIDING	
	
	//divide 2 part
		// out of last Row
	for(row=0;row<valueMatrixRow-1;row++){
		for(column=0;column<valueMatrixColumn;column++){
			outOfLastRow[row][column]=valueMatrix[row][column];
		}
	}
		//last row
	for(column=0;column<valueMatrixColumn;column++){
		firstLastRow[0][column]=valueMatrix[valueMatrixRow-1][column];
	}
	
	//3-NORMALIZATIONS
	
	//Fayda kriterleri icin bu normalizasyon
	//float exceptLastRow[valueMatrixRow-1][valueMatrixColumn];
	float** exceptLastRow = new float*[valueMatrixRow-1];
    for (int i = 0; i < valueMatrixRow-1; i++) {
        exceptLastRow[i] = new float[valueMatrixColumn];
    }
	normalizationForWSM(outOfLastRow,valueMatrixRow-1,valueMatrixColumn,exceptLastRow); 
	/*
	cout<<"Normalazing-1 out of last Row***********************************";
	outputForTable(exceptLastRow,valueMatrixRow-1,valueMatrixColumn);
	*/
	
	//normalizationForWSM(outOfLastRow,valueMatrixRow-1,valueMatrixColumn,&exceptLastRow[0]); 
	
	//Maaliyet kriterleri icin bu normalizasyon	
	//float lastRow[1][valueMatrixColumn];	
	float** lastRow = new float*[1];
    for (int i = 0; i < 1; i++) {
        lastRow[i] = new float[valueMatrixColumn];
    }
	normalizationForWPM(firstLastRow,1,valueMatrixColumn,lastRow); 
	/*
	cout<<"Normalazing-2 last Row***********************************";
	outputForTable(lastRow,1,valueMatrixColumn);
	*/
	
	//4-COMBINATÝNG
	
	// we assume that the last feature is the price. (Combinating 2 array)
	float finalNormalizedMatrix[valueMatrixRow][valueMatrixColumn];
	float** tmp = new float*[valueMatrixRow];
    for (int i = 0; i < valueMatrixRow; i++) {
        tmp[i] = new float[valueMatrixColumn];
    }
    
	// Adding elements (the out of last row)
	for(row=0;row<valueMatrixRow-1;row++){
		for(column=0;column<valueMatrixColumn;column++){
			tmp[row][column]=exceptLastRow[row][column];
		}	
	}
	/*
	cout<<"Normalazing Final last Row PART***********************************";
	outputForTable(tmp,valueMatrixRow-1,valueMatrixColumn);
	*/
	
	// Adding last element
	for(column=0;column<valueMatrixColumn;column++){
			tmp[valueMatrixRow-1][column]=lastRow[0][column];
	}	
	/*
	cout<<"Normalazing Final last Row PART***********************************";
	outputForTable(tmp,1,valueMatrixColumn);
	*/
	

	
	//*tmp=&finalNormalizedMatrix[0][0];
	
	/*
	cout<<endl<<"FINAL NORMALIZED MATRIX ---------------------------------------------------------"<<endl<<endl;
	outputForTable(tmp,valueMatrixRow,valueMatrixColumn);
	*/
	
	/*
	cout<<endl<<"Current Rates ---------------------------------------------------------"<<endl<<endl;
	outputForRates(rateMatrix,rateMatrixSize);
	*/
	
	//5-CALCULATING
	float WSM_For_CurrentValueRow=0;
	float WPM_For_CurrentValueRow=0;
	float WASPAS_For_CurrentValueRow=0;
	
	//cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<|||||||||||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
	
	//WASPAS Calculation for each product. (product --> column)
	for(column=0;column<valueMatrixColumn;column++){
		
	///cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"	<<endl;
	 	WSM_For_CurrentValueRow=0;
		WPM_For_CurrentValueRow=0;
		WASPAS_For_CurrentValueRow=0;
		
		
		for(row=0;row<valueMatrixRow;row++){
		
			int productPoint=tmp[row][column];
			
				//cout<<"Current Point: "<<productPoint<<endl;
			//step 2 normalization
				//WSM  step-3
				WSM_For_CurrentValueRow += productPoint * rateMatrix[row];
				//cout<<"WSM current value: "<<WSM_For_CurrentValueRow<<endl;
				
				
				//WPM	step-4
				WPM_For_CurrentValueRow *= pow(productPoint, rateMatrix[row]);
				//cout<<"WPM current value: "<<WPM_For_CurrentValueRow<<endl;
				
			
		}
			//cout<<"----------------------------------ROW CALCULATION---------------------------------------";
			//WASPAS  step-5  Balance of calculating methods
			WASPAS_For_CurrentValueRow=alfa*WSM_For_CurrentValueRow + (1-alfa) * WPM_For_CurrentValueRow;
			//cout<<" Calculation for "<<column+1<<". is: "<<WASPAS_For_CurrentValueRow<<endl;
			
			//WAPAS values
			returnMatrix[column]=WASPAS_For_CurrentValueRow;
		
	}
	
	//cout<<endl<<"RETURN MATRIX---------------------------------------------------------"<<endl<<endl;
	//outputForRates(returnMatrix,valueMatrixColumn);
	
	//returnMatrix=&WASPAS_value_matrix[0];
}

void inputForTable(float **valueMatrix, int valueMatrixRow, int valueMatrixColumn){
	float point;
	
	cout <<endl<<"Tabloyu Doldurmak icin Talimatlari Takip Ediniz"<<endl;
	for(int column=0;column<valueMatrixColumn;column++){
		cout <<"----------------------------------------URUN-"<<column+1<<"--------------------------------------------"<<endl;
		for(int row=0;row<valueMatrixRow;row++){
			
			cout << column+1 <<" Numarali Urunun "<<row+1<<" Numarali ozelligi icin bir puan girin:";
			cin>>point;
			valueMatrix[row][column]=point;
		}
		
	}
	cout <<"------------------------------------------------------------------------------------------"<<endl<<endl;
	
}
void inputForRates(float *rateMatrix,int rateMatrixSize){
	cout <<"----------------------------------------AGIRLIKLAR----------------------------------------"<<endl;
	float w;
	cout <<"Tablodaki Ozelliklerin Agirliklaini Girmek Icin Talimatlari Takip Edniniz [0.0-1.0 arasi]"<<endl;
	for(int i=0;i<rateMatrixSize;i++){
		cout <<i+1<<" Numarali Ozelligin agirlik oranini giriniz: ";
		cin>>w;
		rateMatrix[i]=w;
	}
	cout <<"------------------------------------------------------------------------------------------"<<endl<<endl;
}
void outputForTable(float **valueMatrix, int valueMatrixRow, int valueMatrixColumn){

	cout <<endl<<endl<<"---------------------------DOLAN TABLO------------------------"<<endl<<endl;
	for(int column=0;column<valueMatrixColumn;column++){
		cout <<"----------------------------------------URUN-"<<column+1<<"--------------------------------------------"<<endl;
		for(int row=0;row<valueMatrixRow;row++){
			
			cout << column+1 <<" Numarali Urunun "<<row+1<<" Numarali ozelliginin degeri: "<<valueMatrix[row][column]<<endl;
		}
		
	}
	cout <<endl<<endl<<"------------------------------------------------------------------------------------------"<<endl<<endl;
}
void outputForRates(float *rateMatrix,int rateMatrixSize){
	cout <<"----------------------------------------GIRILEN AGIRLIKLAR----------------------------------------"<<endl;
	float w;
	cout <<"Girilen Tum agirlik degerleri asagidadir."<<endl;
	for(int i=0;i<rateMatrixSize;i++){
		cout <<i+1<<" Numarali Ozelligin agirlik oranini: "<<rateMatrix[i]<<endl;
	}
	cout <<"------------------------------------------------------------------------------------------"<<endl<<endl;	
}

int main(int argc, char** argv) {
	
	//Declarete
	
	int featureSize;
	int productSize;
	
	cout <<"-------------------------DINAMIK TABLO BOYUNUN BELIRLENMESI-------------------------------"<<endl;
	
	cout << "Tabloya Girilecek Ozellik Turu Sayisi: ";
  	cin >> featureSize;
  	
	cout << "Tabloya Girilecek Urun Sayisi: ";
  	cin >> productSize;  
	
	cout <<"------------------------------------------------------------------------------------------"<<endl<<endl;
	
	cout <<"----------------------------------------------UYARI-----------------------------------------"<<endl;
	cout<<"SON GIRILICEK OZELLIK PUANI FIYAT OLMALIDIR.(MAALIYET KRITERI KABUL EDILEREK NORMALIZASYON UYGULANACAKTIR.)"<<endl;
	cout<<"SON OZELLIKTEN ONCE GIRILEN TUM OZELLIK PUANLARI .(FAYDA KRITERI KABUL EDILEREK NORMALIZASYON UYGULANACAKTIR.)"<<endl;
	cout <<"------------------------------------------------------------------------------------------"<<endl<<endl;
	
	float** valueMatrix = new float*[featureSize];
    for (int i = 0; i < featureSize; i++) {
        valueMatrix[i] = new float[productSize];
    }
    inputForTable(valueMatrix,featureSize,productSize);
    
	//outputForTable(valueMatrix,featureSize,productSize);
    
    float rateM[featureSize]={0};
    float returnM[productSize]={0};
    
    
	//float* rateMatrix = new float[featureSize];
	float *rateMatrix=&rateM[0];
	inputForRates(rateMatrix,featureSize);
	//outputForRates(rateMatrix,featureSize);

	//float* returnMatrix = new float[productSize];	
	float *returnMatrix = &returnM[0];
	
	
	WASPAS_method(valueMatrix,featureSize,productSize,rateM,featureSize,returnM);
	//float calculatedMatr11x[productSize]= 
	
	float sortedReturnM[productSize]={0};
	for(int column=0;column<productSize;column++){
			sortedReturnM[column]=returnM[column];
	}
	
	sort(sortedReturnM, sortedReturnM + productSize);
	
	float sortedIndexReturnM[productSize]={0};
	for(int column=0;column<productSize;column++){
		for(int j=0;j<productSize;j++){
			if(returnM[column]==sortedReturnM[j]){
				sortedIndexReturnM[column]=productSize-j;
			}
		}
	}
	
	
	
	
	
	cout <<"-------------------------SONUC------------------------------------------------------------"<<endl;
	cout << "WASPAS YONTEMINE GORE YAPILAN PUANLAMA ASAGIDADIR"<<endl<<endl;
	
	for(int i=0;i<productSize;i++){
		float point=returnM[i];
		int sortNumber=sortedIndexReturnM[i];
		cout<<i+1<<" Numarali Urunun Oncelik Siralamasi: "<<sortNumber<<" WASPAS degeri: "<<point<<endl;
	}
	
	cout <<endl<<"------------------------------------------------------------------------------------------"<<endl<<endl;
	return 0;
}
