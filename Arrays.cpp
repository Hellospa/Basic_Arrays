#include <iostream>

template <typename type>
struct vector{
	#define FREE free(array)
	#define Push_back(arr,val) arr.Push(1,val,arr.size)
	type* array = (type*)malloc(1);
	int size = 0;
	
	vector(){}
	vector(vector<type>& copy)
		:size(copy.size){
		FREE;array = (type*)calloc(sizeof(type),size);
		memcpy(array,copy.array,sizeof(type) * size);
	}
	~vector() {FREE;}
	
	int ReallocPlace(int add){
		size += add;if (size < 0) return -1;
		type temp[size];
		memcpy(temp,array,sizeof(type) * size);
		FREE;array = (type*)calloc(sizeof(type),size);
		memcpy(array,temp,sizeof(type) * size);
		return 1;
	}
	void Push(bool IsAdd,type input,int pos){
		if (!IsAdd) goto EXIT1;
		ReallocPlace(1);
		for (int i = pos;i < size;i++)
			*(array + pos) = *(array + pos + 1);
		EXIT1:
			*(array + pos) = input;
	}
	int Earser(bool isSub,int pos){
		if (pos < 0) return -1;
		memset(array + pos,0,sizeof(type));
		if (isSub){
			for (int i = pos;i < size;i++)
				*(array + i) = *(array + i + 1);
			ReallocPlace(-1);
		}
		return 1;
	}
	type& operator[](int pos){
		return *(array + pos);
	}
	void ForEach(void (*f)(type)){
		for (int i = 0;i < size;i++)
			f(*(array + i));
	}
};

struct ConstStrArray{
	vector<char> arrays;
	vector<int> strpos;
	
	ConstStrArray(){
		Push_back(strpos,0);
	};
	ConstStrArray(ConstStrArray& copy)
		:arrays(copy.arrays),strpos(copy.strpos){
			Push_back(strpos,0);}
	
	void Push(char* input){
		Push_back(strpos,arrays.size);
		arrays.ReallocPlace(strlen(input) + 1);
		strcpy(arrays.array + strpos[strpos.size - 1],input);
	}
	void Del(int pos){
		int removeStrSize = strlen(arrays.array + strpos[pos + 1]) + 1;
		int moveSize = arrays.size - strpos[pos + 1] - removeStrSize;
		memcpy(arrays.array + strpos[pos + 1],arrays.array + strpos[pos + 1] + removeStrSize,moveSize);
		
		for (int i = pos + 1;i < strpos.size;i++)
			strpos[i] -= removeStrSize;
		strpos.Earser(1,pos + 1);
		arrays.ReallocPlace(-removeStrSize);
	}
	char* operator[](int pos){
		return arrays.array + strpos[pos + 1];
	}
};
