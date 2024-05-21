#include <iostream>
#include <string>
using namespace std;

struct Stack
{
    string number;
    Stack* tail = NULL;
};

void printStack(Stack* result)
{
	while (result != 0)
	{
		cout << result->number << ' ';
		result = result->tail;
	}
}

bool isOper(char a)
{
	if (a == '+' || a == '-' || a == '*' || a == '/' || a == '(' || a == ')')
	{
		return true;
	}
	return false;
}

int priorOper(char choise)
{
	switch (choise)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '(':
	case ')':
		return 0;
	default:
		return -1;
	}
}

int mathOperation(int value1, int value2, char choise)
{
	switch (choise)
	{
	case '+':
		return value1 + value2;
		break;
	case '-':
		return value1 - value2;
		break;
	case '*':
		return value1 * value2;
		break;
	case '/':
		return value1 / value2;
		break;
	default:
		break;
	}
}

void transport(Stack*& op, Stack*& res)
{
	while (op->tail != 0)
	{
		Stack* currStack;
		currStack = new Stack;
		currStack->number = op->number;
		currStack->tail = res;
		res = currStack;
		op = op->tail;
	}
	Stack* now;
	now = new Stack;
	now->number = op->number;
	now->tail = res;
	res = now;
	op = op->tail;
}

void operSign(Stack*& op, char a, Stack*& res)
{
	Stack* operatorSign;
	operatorSign = new Stack;
	operatorSign->number = a;
	if (op == 0)
	{
		operatorSign->tail = 0;
	}
	else
	{
		if (priorOper(a) < priorOper(op->number[0]))
		{
			transport(op, res);
			operatorSign->tail = 0;
		}
		else
		{
			operatorSign->tail = op;
		}
	}
	op = operatorSign;
	cout << "Стек операторов: \n";
	printStack(op);
	cout << '\n';
}

void strItog(Stack*& start, string a)
{
	Stack* work;
	work = new Stack;

	work->number = a;
	if (start == 0)
	{
		work->tail = 0;
	}
	else
	{
		work->tail = start;
	}

	start = work;
	cout << "Результирующий стек: \n";
	printStack(start);

	cout << '\n';
}

Stack* prPolNat(int len, string example)
{
	string b;
	Stack* result = 0, * operation = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		if (isOper(example[i]))
		{
			strItog(result, b);
			b = "";
			operSign(operation, example[i], result);
		}
		else
		{
			b += example[i];
		}
	}
	strItog(result, b);

	transport(operation, result);

	operation = result;
	cout << "\nПольская нотация: \n";
	printStack(result);
	
	return operation;
}

void obrTransport(Stack*& res)
{
	Stack* head = 0;
	while (res->tail != 0)
	{
		Stack* now;
		now = new Stack;
		now->number = res->number;
		if (head == 0)
		{
			now->tail = 0;
		}
		else
		{
			now->tail = head;
		}
		head = now;
		res = res->tail;
	}
	Stack* now;
	now = new Stack;

	now->number = res->number;
	now->tail = head;

	head = now;
	res = head;
}

Stack* obrPolNat(int len, string example)
{
	string b;
	Stack* result = 0, * oper = 0;
	for (int i = 0; i < len; i++)
	{
		if (isOper(example[i]))
		{
			strItog(result, b);
			b = "";
			operSign(oper, example[i], result);
		}
		else
		{
			b += example[i];
		}
	}
	strItog(result, b);
	transport(oper, result);
	obrTransport(result);
	oper = result;
	cout << "\nОбратная польская нотация: \n";
	printStack(result);
	return oper;
}

void pr_ch(Stack*& now)
{
	obrTransport(now);
	Stack* ch = 0, * head = 0;
	while (now != 0)
	{
		if (!isOper(now->number[0]))
		{
			if (now->number != "")
			{
				ch = new Stack;
				ch->tail = head;
				ch->number = now->number;
				head = ch;
			}
		}
		else
		{
			if (head->tail == 0)
			{
				cout << "Ошибка!";
				return;
			}
			else
			{
				head->tail->number = to_string(mathOperation(stoi(head->number), stoi(head->tail->number), now->number[0]));
				head = head->tail;
				cout << "Операция: ";
				cout << now->number << '\n';
			}
		}
		now = now->tail;
		cout << "Результирующий стек: \n";
		printStack(head);
		cout << '\n';
	}
	cout << "Результат: \n";
	cout << head->number;
}

void obr_ch(Stack*& now)
{
	Stack* ch = 0, * head = 0;
	while (now != 0)
	{
		if (!isOper(now->number[0]))
		{
			if (now->number != "")
			{
				ch = new Stack;
				ch->tail = head;
				ch->number = now->number;
				head = ch;
			}
		}
		else
		{
			if (head->tail == 0)
			{
				cout << "Ошибка!";
				return;
			}
			else
			{
				head->tail->number = to_string(mathOperation(stoi(head->tail->number), stoi(head->number), now->number[0]));
				head = head->tail;
				cout << "Операция: ";
				cout << now->number << '\n';
			}
		}
		cout << "Результирующий стек: \n";
		printStack(head);
		now = now->tail;
		cout << '\n';
	}
	cout << "Результат: \n";
	cout << head->number;
}

int main() {
	setlocale(LC_ALL, "RU");
	while (true) {
		system("cls");
		string example;
		Stack* pr_nat, * obr_nat;
		cout << "Введите выражение: ";
		cin >> example;
		cout << endl;
		int len;
		len = size(example);
		pr_nat = prPolNat(len, example);
		cout << '\n';
		cout << '\n';
		obr_nat = obrPolNat(len, example);
		cout << '\n';
		cout << '\n';
		system("pause");
		string b, c;
		Stack* prov = 0, * prova = 0;
		prov = obr_nat;
		prova = pr_nat;
		while (prov != 0)
		{
			if (!isOper(prov->number[0]) and !isdigit(prov->number[0]) and prov->number != "")
			{
				cout << "Введите значение переменной " << prov->number << ' ';
				c = prov->number;
				cin >> prov->number;
				b = prov->number;
				while (prova->number != c)
				{
					prova = prova->tail;
				}
				prova->number = b;
			}
			prov = prov->tail;
		}
		cout << "\nПольская нотация: ";
		printStack(pr_nat);
		cout << '\n';
		cout << '\n';
		pr_ch(pr_nat);
		cout << '\n';
		cout << "\nОбратная польская нотация: ";
		printStack(obr_nat);
		cout << '\n';
		cout << '\n';
		obr_ch(obr_nat);
		cout << "\n\n[1]Ввести пример еще раз\n[0]Выход\n";
		int a;
		cin >> a;
		if (a == 0)
		{
			break;
		}
	}
}

