// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>  
#include <Windows.h>
#include <tchar.h>
#include <conio.h>
#include <locale>

const int N = 10;
void Input(unsigned short* mas);
void Output(unsigned short* mas);
void Zad(unsigned short* mas);

int main()
{
	setlocale(LC_ALL, "rus");
	unsigned short* mas;
	mas = new unsigned short[N];
	Input(mas);
	Zad(mas);
	std::cout << std::endl;
	return 0;
}

void Input(unsigned short* mas)
{
	const char* message = "Введите массив из 10 чисел:";
	const char* paragraph = "%s\n";
	const char* format = "%d";

	_asm
	{
		push message // Загружаем в стек значение переменной
		push paragraph // Загружаем в стек формат
		call printf // Вызов функции печати на консоль
		pop ebx // Чистим стек
		pop ebx
	}

	_asm
	{
		mov esi, mas // Записываем в регистр esi адрес массива mas
		mov ecx, N // Счетчик

		c :
		    push ecx // Загружаем в стек значение N
			push esi // Загружаем в стек адрес текущего элемента
			push format // Загружаем в стек формат
			call scanf // Вызов команды ввода элемента
			add esp, 8
			pop ecx
			add esi, 4 // Переход к следующему элементу
			loop c
	}
}

void Output(unsigned short* mas)
{
	const char* format = "%4d ";
	_asm
	{
		mov esi, mas // Записываем в регистр esi адрес массива mas
		mov ecx, 9 // Счетчик

		c :
		    mov eax, [esi]  // В регистр eax записываем первый элемент массива
			add esp, 8
			push eax
			push format
			call printf
			add esp, 8
			pop ecx
			add esi, 4
			loop c
	}
	std::cout << std::endl;
}

void Zad(unsigned short* mas)
{
	int max_i = 0, max_n = 0, size_mas = 10;
	char Format[] = "%d ";
	char Line[] = "\n";

	_asm
	{
		mov ebx, 0
		mov esi, mas // Записываем в регистр esi адрес массива mas
		mov eax, [esi] // В регистр eax записываем первый элемент массива 

		a :
			mov eax, [esi] 
			cmp eax, max_n // Сравниваем значения операндов
			jg update_max // Переход, если op1 > op2
			inc ebx // Добавление единицы
			add esi, 4 // Переход к следующей ячейке
			cmp ebx, size_mas // Сравниваем значения операндов
			je before_replace // Переход, если op1 = op2
			jmp a

			update_max :
		        mov max_n, eax // Записываем в max_n новый больший элемент
			    mov max_i, ebx // Записываем в max_i новый индекс этого элемента
			    inc ebx // Добавление единицы
			    add esi, 4 // Переход к следующей ячейке
			    cmp ebx, size_mas // Сравниваем значения операндов
			    je before_replace // Переход, если op1 = op2
			    jmp a

		before_replace :
		    mov ebx, 0
			lea esi, mas // Загружает в регистр адрес
			lea eax, Line // Присваиваем адрес формата
			push eax // Помещаем значение регистра в стек
			call printf // Вызов функции печати на консоль
			pop ecx // Чистим стек
			jmp replace

		put_zero :
		    mov[esi], 0
			mov[esi + 4], 0
			inc ebx // Добавление единицы
		    add esi, 4 // Переход к следующей ячейке
		    push 0
			lea eax, Format // Присваиваем адрес формата
			push eax // Помещаем значение регистра в стек
			call printf // Вызов функции печати на консоль
			pop ecx // Чистим стек
			pop ecx
			cmp ebx, size_mas // Сравниваем значения операндов
			je finish // Переход, если op1 = op2
			jmp replace

		put_max :
		    mov eax, max_n // Записываем значение max_n (максимального элемента) в регистр eax
			mov[esi], eax
			inc ebx // Добавление единицы
			add esi, 4 // Переход к следующей ячейке
			push eax // Помещаем значение регистра в стек
			lea eax, Format // Присваиваем адрес формата
			push eax
			call printf // Вызов функции печати на консоль
			pop ecx // Чистим стек
			pop ecx
			cmp ebx, size_mas // Сравниваем значения операндов
			je finish // Переход, если op1 = op2
			jmp replace

		replace :
		    cmp ebx, max_i // Сравниваем значения операндов
			jge put_max // Переход, если op1 >= op2
			jl put_zero // Переход, если op1 < op2

	    finish : // Конец

	}
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
