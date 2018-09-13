// Matr_thread.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
using namespace std;

// вычисления
void Solve(int start, int stop, int cols, int** matr_A, int** matr_B,  int** matr_C)
{
	cout << "Новый поток был запущен, id-" << this_thread::get_id() << endl;
	int res = 0;
	for (int i = start; i < stop; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < cols; k++)
			{
				res = res + matr_A[i][k] * matr_B[k][j];
			}
			matr_C[i][j] = res;
			res = 0;
		}
	}	
}
// забивание рандомными знач.
void Rand(int rows,int cols, int** matr)
{
	cout << "Новый поток был запущен, id-" << this_thread::get_id() << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matr[i][j] = rand() % 9;			
		}
		//cout << i << "-ая Строка забита" << endl;
	}
}
// вывод на экран
void Print_matr(int rows, int cols, int**matr, char name)
{	
	cout << "Матрица " << name << ":" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << matr[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Основной поток был запущен, id-" << this_thread::get_id() << endl;
	int rows;
	int cols;	
	cout << "Матрица[rows,cols]" << endl;
	cout << "Введите rows: ";
	cin >> rows;
	cout << "Введите cols: ";
	cin >> cols;
	

	int **matr_A = new int* [rows];
	int **matr_B = new int* [rows];
	int **matr_C = new int* [rows];
	// создаем для каждого указателя массив столбцов
	for (int i = 0; i < rows; i++)
		matr_A[i] = new int [cols];
	for (int i = 0; i < rows; i++)
		matr_B[i] = new int[cols];
	for (int i = 0; i < rows; i++)
		matr_C[i] = new int[cols];
	// забиваем рандомными значениями
	//Rand(rows, cols, matr_A);
	//Rand(rows, cols, matr_B);
	int count = 0;
	if (rows % 2 == 0)
	{		
		cout << "Забиваем рандомными значениями..." << endl;
		thread th1(Rand, rows, cols, matr_A);
		thread th2(Rand, rows, cols, matr_B);		
		th1.join();
		th2.join();
		cout << "Операция выполнена." << endl;

		cout << "Идут вычисления..." << endl;
		count = rows / 2;		
		thread th3(Solve, count * 0, count * 1, cols, matr_A, matr_B, matr_C);
		thread th4(Solve, count * 1, count * 2, cols, matr_A, matr_B, matr_C);		
		th3.join();
		th4.join();		
		cout << "Вычисления завершены." << endl;
	}	
	
	//Print_matr(rows, cols, matr_A, 'A');
	//Print_matr(rows, cols, matr_B, 'B');
	//Print_matr(rows, cols, matr_C, 'C'); 	
	
	/*//перемножаем матрицы
	int res = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < cols; k++)
			{
				res = res + matr_A[i][k] * matr_B[k][j];				
			}			
			matr_C[i][j] = res;
			res = 0;
		}		
	}	
	cout << "Вычисления завершены." << endl;
	*/
	for (int i = 0; i < rows; i++)
	{
		delete[] matr_A[i];
		delete[] matr_B[i];
		delete[] matr_C[i];
	}

	delete[] matr_A;
	delete[] matr_B;
	delete[] matr_C;
	
    return 0;
}

