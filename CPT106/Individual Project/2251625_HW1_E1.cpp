//#include<iostream>
//#include<time.h>//generate random number
//using namespace std;
//class MyArray 
//{
//private:
//	int* arr = NULL;
//	int num = 0;
//public:
//	MyArray(int arrayLen);
//	void Display();
//	MyArray* operator+(MyArray& a);
//	friend MyArray* operator-(MyArray& a, MyArray& b);
//};
//MyArray::MyArray(int arrayLen)//define a constructor to initialize
//{
//	num = arrayLen;
//	arr = new int[arrayLen];//create dynamic memory for array
//	for (int i = 0; i < num; i++)
//	{
//		arr[i]= 100 + (rand() % 900);
//     
//	}
//}
//void MyArray::Display()//show all the members of an array
//{
//	for (int j = 0; j < num; j++)
//	{
//		cout << arr[j] << '\t';
//	}
//	cout << endl;
//}
//MyArray* MyArray::operator+(MyArray& a) //operator for addition
//{
//	int maxLength = max(num, a.num);//to discuss the situation that the length of two arrays are not the same
//	MyArray* tempPlus = new MyArray(maxLength);
//	for (int i = 0; i < maxLength; i++) 
//	{
//		int valueA = (i < num) ? arr[i] : 0;//the same as if else, but more simple
//		int valueB = (i < a.num) ? a.arr[i] : 0;//initialize the redundant member zero
//		tempPlus->arr[i] = valueA + valueB;
//	}
//	return tempPlus;
//}
//MyArray* operator-(MyArray& a, MyArray& b)//operation for subtraction
//{
//	int maxLength = max(a.num, b.num);
//	MyArray* tempMinus = new MyArray(maxLength);//to discuss the situation that the length of two arrays are not the same
//	for (int k = 0; k < maxLength; k++)
//	{
//		int valueA = (k < a.num) ? a.arr[k] : 0;//the same as if else, but more simple
//		int valueB = (k < b.num) ? b.arr[k] : 0;//initialize the redundant member zero
//		tempMinus->arr[k] = valueA - valueB;
//	}
//	return tempMinus;
//}
//int main()//show all the results required by the question
//{
//	srand(time(0));
//	int arrayLenA = 0;
//	cout<< "please input the length of the arrayA"<<endl;
//	cin >> arrayLenA;//customize the length by users
//	MyArray sequenceA(arrayLenA);
//	sequenceA.Display();
//	int arrayLenB = 0;
//	cout << "please input the length of the arrayB" << endl;
//	cin >> arrayLenB;//customize the length by users
//	MyArray sequenceB(arrayLenB);
//	sequenceB.Display();
//	cout << "The summing result of two sequence is shown as below" << endl;
//	MyArray* resultPlus = sequenceA + sequenceB;
//	resultPlus->Display();
//	delete resultPlus; 
//	cout << "The subtracting result of two sequence is shown as below" << endl;
//	MyArray* resultMinus = sequenceA - sequenceB;
//	resultMinus->Display();  
//	return 0;
//}

