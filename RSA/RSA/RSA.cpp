// RSA.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>
using namespace std;

int const I = 2;

int Module(int a,int b)
{
	return a * b;
}
//функция Эйлера
int EulerFunction(int p, int q)
{
	return (p - 1) * (q - 1);
}
//Число e, отвечающее следующим критериям :
//1 оно должно быть простое, 
//2 оно должно быть меньше F
//3 оно должно быть взаимно простое с F;
//Это, так называемая, открытая экспонента.
int f(int F)
{
	srand(time(NULL));
	vector<int> numbers;
	for (int i = 2; i < F; i++)
	{
		int value = 0;
		for (int j = 1; j <= i; j++)
		{
			
			if (i % j == 0)
				value++;
		}
		if (value == 2)
			numbers.push_back(i);
	}
	for (int i = 0; i < numbers.size(); i++)
	{
		if (F % numbers[i] != 0)
			return numbers[i];
	}

}
// Поиск D
int SearchD(int E, int F)
{
	int D = 1;
	while(true)
	{
		if (((D * E) % F == 1))// and (D != E))
			return D;
		D++;
	}
}
//Шифрование
long long int Encryption(int Message, int PublicKey[])
{
	long long int Value;
	Value = pow(Message, PublicKey[0]);
	long long int Meaning;
	Meaning = Value % PublicKey[1];
	return Meaning;
}
//Расшифровка
long long int Decoding(int EncryptedMessage, int PrivateKey[])
{
	long long int Value;
	Value = pow(EncryptedMessage, PrivateKey[0]);
	long long int Meaning;
	Meaning = Value % PrivateKey[1];
	return Meaning;
}

int main()
{
	int PublicKey[2];
	int PrivateKey[2];
	int P = 3;
	int Q = 7;// P,Q-простые числа
	int N = Module(P, Q);
	int F = EulerFunction(P, Q);
	int E = f(F);
	int D;

	int Message = 19;

	PublicKey[0] = E;
	PublicKey[1] = N;

	D = SearchD(E, F);

	PrivateKey[0] = D;
	PrivateKey[1] = N;

	cout << "N = " << N << endl << "F = " << F << endl << "E = " << E << endl << "D = " << D << endl;
	cout << "PublicKey : " << E << "," << N << endl;
	cout << "PrivateKey : " << D << "," << N << endl;
	cout << "Message : " << Message << endl;
	long long int EncryptedMessage = Encryption(Message, PublicKey);
	long long int DecryptedMessage = Decoding(EncryptedMessage, PrivateKey);

	cout << "EncryptedMessage : " << EncryptedMessage << endl;
	cout << "DecryptedMessage : " << DecryptedMessage << endl;

}

