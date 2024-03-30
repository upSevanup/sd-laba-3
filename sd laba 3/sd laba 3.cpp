#include <iostream>
#include <clocale>
#include <fstream>

using namespace std;

struct BTree {
	int Data;
	BTree* Left;
	BTree* Right;
};

void add_to_tree(BTree** node, int key);
void range_search(BTree* node, int a, int b, ofstream &file);
void print_tree(BTree* node, ofstream &file);
void delete_tree(BTree** node);

int main() {
	setlocale(LC_ALL, "ru");

	ofstream inputfile("input.dat");
	ofstream outputfile("output.dat");

	//создание дерева
	BTree* tree = new BTree;
	tree = NULL;
	cout << "Введите количество элементов в дереве >> ";
	int n, i, s = 0; 
	cin >> n;
	inputfile << "Колличество элементов дерева: " << n << endl;
	inputfile << "\n" << "Элементы дерева: " << endl;
	while (s < n) {
		cout << "Введите элемент дерева >> "; cin >> i;
		add_to_tree(&tree, i);
		s++;
		inputfile << i << " ";
	}

	//получаем диапазон от пользователя
	cout << "Введите диапазон >> ";
	int a, b;
	while (true) {
		cin >> a >> b;
		if (a > b) {
			cout << "первое заначение должно быть меньше второго!" << endl;
			cout << "введите другой диапазон >> ";
		}
		else break;
	}
	inputfile << "\n\n" << "Диапазон: [" << a << ", " << b << "]" << endl;
	
	//выводим дерево
	cout << endl << "Дерево:" << endl;
	outputfile << "Дерево:" << endl;
	print_tree(tree, outputfile);
	
	//получаем числа вне диапазона
	cout << endl << "числа вне заданного диапазона: ";
	outputfile << endl << "числа вне заданного диапазона: ";
	range_search(tree, a, b, outputfile);
	
	//отчисткa памяти
	delete_tree(&tree);
}

void add_to_tree(BTree** node, int key) {
	BTree* ptr;
	int flag = 1;
	if (*node == NULL) {
		ptr = new BTree;
		ptr->Data = key;
		ptr->Left = ptr->Right = NULL;	
		*node = ptr; 
	}
	else {
		ptr = *node;
		while (flag == 1) {
			if (ptr->Data > key) {
				if (ptr->Left == NULL) {
					ptr->Left = new BTree;
					ptr = ptr->Left;
					ptr->Data = key;
					ptr->Left = ptr->Right = NULL;
					flag = 0;
				}
				else {
					ptr = ptr->Left;
				}
			}
			else if (ptr->Data < key) {
				if (ptr->Right == NULL) {
					ptr->Right = new BTree;
					ptr = ptr->Right;
					ptr->Data = key;
					ptr->Left = ptr->Right = NULL;
					flag = 0;
				}
				else {
					ptr = ptr->Right;
				}
			}
			else {
				flag = 2;
			}
		}
	}
}

void range_search(BTree* node, int a, int b, ofstream &file) {
	BTree* ptr = node;
	int flag = 0, uv = -1;
	BTree* st[100]; 
	while (flag == 0) {
		if (ptr == NULL) {
			if (uv == -1) {
				flag = 1;
			}
			else {
				ptr = st[uv--];
				ptr = ptr->Right;
			}
		}
		else {
			st[++uv] = ptr;
			if (ptr->Data < a or ptr->Data > b) {
				cout << ptr->Data << " ";
				file << ptr->Data << " ";
			}
			ptr = ptr->Left;
		}
	}
}

void print_tree(BTree* node, ofstream &file) {
	BTree* ptr = node;
	int flag = 1, uv = -1;
	BTree* st[100]; 

	while (flag == 1) {
		if (ptr == NULL) {
			if (uv == -1) {
				flag = 0;
			}
			else {
				ptr = st[uv--];
				ptr = ptr->Right;
			}
		}
		else {
			printf("%4ld", ptr->Data);
			file << ptr->Data << "\t";

			if (ptr->Left != NULL) {
				printf("%4ld", ptr->Left->Data);
				file << ptr->Left->Data << "\t";
			}
			else {
				printf("----");
				file << "----" << "\t";
			}

			if (ptr->Right != NULL) {
				printf("%4ld", ptr->Right-> Data);
				file << ptr->Right->Data << "\t";
			}
			else {
				printf("-----");
				file << "----" << "\t";
			}

			cout << endl;
			file << endl;
			st[++uv] = ptr;
			ptr = ptr->Left;
		}
	}
}

void delete_tree(BTree** node) {
	BTree* ptr = *node;
	int flag = 0, uv = -1;
	BTree* st[100];
	while (flag == 0) {
		if (ptr == NULL) {
			if (uv == -1) {
				flag = 1;
			}
			else {
				ptr = st[uv--];
				if (ptr->Right != NULL) {
					ptr = ptr->Right;
				}
				else {
					delete ptr;
					ptr = NULL;
				}
			}
		}
		else {
			st[++uv] = ptr;
			ptr = ptr->Left;
		}
	}
}

	
