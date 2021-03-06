// Matr_thread.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
using namespace std;

void Solve(int start, int stop, int cols, int** matr_A, int** matr_B, int** matr_C);
void Rand(int rows, int cols, int** matr);
void Print_matr(int rows, int cols, int**matr, char name);

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "The main thread was started, id-" << this_thread::get_id() << endl;
	int rows;
	int cols;	
	cout << "Matrix[rows,cols]" << endl;
	cout << "Enter rows: ";
	cin >> rows;
	cout << "Enter cols: ";
	cin >> cols;	

	int **matr_A = new int* [rows];
	int **matr_B = new int* [rows];
	int **matr_C = new int* [rows];
	// create for each pointer an array of columns
	for (int i = 0; i < rows; i++)
		matr_A[i] = new int [cols];
	for (int i = 0; i < rows; i++)
		matr_B[i] = new int[cols];
	for (int i = 0; i < rows; i++)
		matr_C[i] = new int[cols];
	// score by random values
	//Rand(rows, cols, matr_A);
	//Rand(rows, cols, matr_B);
	int count = 0;
	if (rows % 2 == 0)
	{		
		cout << "\nWe hammer by random values..." << endl;
		thread th1(Rand, rows, cols, matr_A);
		thread th2(Rand, rows, cols, matr_B);		
		th1.join();
		th2.join();
		cout << "Operation completed." << endl;

		cout << "\nThe calculations are..." << endl;
		count = rows / 2;		
		thread th3(Solve, count * 0, count * 1, cols, matr_A, matr_B, matr_C);
		thread th4(Solve, count * 1, count * 2, cols, matr_A, matr_B, matr_C);		
		th3.join();
		th4.join();		
		cout << "Calculations completed." << endl;
	}	
	
	//Print_matr(rows, cols, matr_A, 'A');
	//Print_matr(rows, cols, matr_B, 'B');
	//Print_matr(rows, cols, matr_C, 'C'); 		
	/*//we multiply the matrices
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
	cout << "The calculations are complete." << endl;
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

// calculating
void Solve(int start, int stop, int cols, int** matr_A, int** matr_B, int** matr_C)
{
	cout << "The new thread was launched, id-" << this_thread::get_id() << endl;
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
// clogging with random values
void Rand(int rows, int cols, int** matr)
{
	cout << "The new thread was launched, id-" << this_thread::get_id() << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matr[i][j] = rand() % 9;
		}
		//cout << i << " Line Crammed" << endl;
	}
}
// output on display
void Print_matr(int rows, int cols, int**matr, char name)
{
	cout << "Matrix " << name << ":" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << matr[i][j] << " ";
		}
		cout << endl;
	}
}