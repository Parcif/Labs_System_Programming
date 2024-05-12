#include<iostream>
using namespace std;

// ����� ����� ����� ���� ������������� ��������� �������
int main()
{
	int siz, result_c = 0, result_asm = 0, of = 0;
	cout << "Enter array size: ";
	cin >> siz;
	int* mas;
	if(siz > 0)
	{
		mas = new int[siz];
		cout << "Enter elements: \n";
		for (int i = 0; i < siz; i++)
		{
			cin >> mas[i];
			if (mas[i] > 0)
			{
				result_c += pow(mas[i], 3);
			}
		}
	}
	else
	{
		cout << "\nError!" << endl;
		return -1;
	}
	
	__asm
	{
		xor esi, esi; ���������� ������� ������� � �������
		mov ebx, mas; ebx ��������� �� ������ �������
		mov ecx, siz; ������� ����� �� ���� ��������� �������
		jecxz end_programm; ��������� ���� ����� ������� 0

		begin_loop:
			mov eax, [ebx + esi * 4]; ���������� ������� �������
			cmp eax, 0; ��������� a[i] � 0
			jl end_loop; ���� ������, �� ��������� ����

			mov edx, eax; �������� ������� ������� ��� ���������� � ���

			imul eax, eax; ������� �������� � �������
			jo overflow; ������ ������������

			imul eax, edx; ����� �������� � ���
			jo overflow; ������ ������������

			add result_asm, eax; ���������� � ����� �����
			jo overflow; ������ ������������

		end_loop:
			add esi, 1; ��������� � ���������� ��������
			jo overflow; ������ ������������
			loop begin_loop; ��������� ���� ��� ���� ��������� �������
			jmp end_programm

		overflow:
			mov of, 1
			jmp end_programm

		end_programm:

	}

	if (of == 1)
	{
		cout << "\nError, overflow!" << endl;
		return -1;
	}
	else
	{
		cout << "\nArray: [ ";
		for (int i = 0; i < siz - 1; i++)
		{
			cout << mas[i] << ", ";
		}
		cout << mas[siz - 1] << " ]\n";
		cout << "Result C++: " << result_c << endl;
		cout << "Result asm: " << result_asm << endl;
		return 0;
	}

}