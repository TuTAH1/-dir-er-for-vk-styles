#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;
#define minint -2147483647
#define ushort unsigned short
#define byte unsigned char

enum { черн, тсин, тзел, тгол, крас, лил, жел, ссер, сер, син, зел, гол, роз, фиол, тел, бел };
char default_background = 	черн,
	default_text_color = 	бел,
	input_color = 			жел,
	negative_color = 		крас,
	positive_color = 		зел,
	progress_color =		гол;
		

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Для setconsole (изм цвета фона и текста)
void clr(char background, char color) { SetConsoleTextAttribute(hConsole, (WORD)((background << 4) | color)); }
void clr(char color) { SetConsoleTextAttribute(hConsole, (WORD)((default_background << 4) | color)); }
void clr() { SetConsoleTextAttribute(hConsole, (WORD)((default_background << 4) | default_text_color)); }

bool qu() { //Функция вопроса
	char* q = new char[31]; bool answer;
	clr(input_color);
	do { fgets(q, 31, stdin); } while (q[0] == '\n');
	clr();
	if (((q[0] == 'д') || (q[0] == 'y') || (q[0] == '1') || (strstr(q, "конечно") != 0) || (strstr(q, "positive") != 0) || (strstr(q, "Sbrakets") != 0) || (strstr(q, "ок") != 0) || (strstr(q, "ладно") != 0) || (strstr(q, "угу") != 0) || (strstr(q, "ага") != 0) || (strstr(q, "хорошо") != 0) || (strstr(q, "хочу") != 0)) && (q[3] != 'н')) answer = true; else answer = false;
	delete[] q;
	return answer;
}

bool Isdigit(char c) {
	return (c >= '0' && c <= '9');

}

unsigned int getuint() {
	unsigned int val = 0;
	clr(input_color);
	for (unsigned char i = 0;;)
	{
		i = _getch();
		if (i == '\r') { break; } //если Enter
		if (Isdigit(i)) { val = val * 10 + (i - 48); printf("%c", i); }
		if ((i == '\b')) { //Если нажат backspace
			if (val != 0) { val = floor(val / 10); printf("\b \b"); } //Если есть число
		}
	}
	clr();
	return val;
}

int getint() {
	int val = 0;
	clr(input_color);
	for (unsigned char i = 0;;)
	{
		bool minus = false;
		i = _getch();
		if (i == '\r') { if (minus) val *= -1; break; }
		if (i == '-' && !minus) { printf("%c", i); minus = true; }
		if (Isdigit(i)) { val = val * 10 + (i - 48); printf("%c", i); }
		if ((i == '\b')) { //Если нажат backspace
			if (val != 0) { val = floor(val / 10); printf("\b \b"); } //Если есть число
			else if (minus) { minus = false; printf("\b \b"); }
		} //Если есть минус
	}
	clr();
	return val;
}

void perr(string massage) {
	clr(negative_color); cout << "\n" << massage<< (char)(7); clr();
}

string getstring() { //Нормальная функция ввода строки, исключающая возможность ввести пустую строку + цвет
	string input = "";
	clr(input_color);
	char symbol;
	while (true) {
		symbol = _getch();

		if (symbol == '\r') if (input == "") continue; else break; //Завершить ввод при нажатии Enter только ЕСЛИ строка не пуста
		if (symbol == '\b') if (input != "") { printf("\b \b"); input.pop_back(); continue; }
		else continue;

		input += symbol; printf("%c", symbol);
		if (symbol == 27) return ("" + (char)(27));
	}
	clr();
	return input;
}

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool Repeat = true;
	while (Repeat) {
		clr();
		printf("Выбрать путь по умолчанию?");
		string FilePath;
		if (qu()) FilePath = "C:\\css.txt";
		else
		{
			printf("Введите путь: ");
			clr(input_color); string FilePath = getstring();
		}
		printf("Выбрать текст по умолчанию?");
		string AddText;
		if (qu()) AddText = "[dir] ";
		else {
			printf("Введите текст: ");
			AddText = getstring();
		}

		ifstream rd;
		rd.open(FilePath);
		while (!rd) {
			perr("Не удалось открыть файл"); printf(", повторить?");
			if (qu()) { rd.close(); rd.open(FilePath); }
			else break;
		}
		if (rd) {
			ofstream wr;
			string NewFilePath = FilePath.substr(0, FilePath.rfind('.')) + "_fixed.txt";
			wr.open(NewFilePath);
			char symbol; bool firstBlock = true;
			do {
				symbol = rd.get();
				if (symbol == 13 || symbol == ','||symbol == '\n') { // \n
					wr << symbol;
					while (true) {
						symbol = rd.get();
						if (symbol == ' ') wr << symbol;
						else break;
					}
					if (symbol == '.'|| symbol == '#') {
						wr << AddText;
					}
				}
				
					if (symbol == '/') { //Комментарии
						wr << symbol;
						symbol = rd.get();
						wr << symbol;
						if (symbol == '/') {// "//"
							do {
								symbol = rd.get();
								wr << symbol;
							} while (symbol != '\n'); //Переписывать, пока строка не закончится
						}
						else if (symbol == '*') {// "/*"
							while (true) {
								symbol = rd.get(); wr << symbol;
								int cur = rd.tellg();
								if (symbol == '\n') {
									printf("");
								}
								if (symbol == '*') {
									symbol = rd.get(); wr << symbol;
									if (symbol == '/') break; // читать, пока комментарий не закончится ("*/")
								}
							}
						}
					}
					else
						if (symbol == '{') { //блоки
							wr << symbol;
							do {
								symbol = rd.get();
								wr << symbol;
							} while (symbol != '}');  //читать, пока блок не закончится
						}
						else
							if (symbol == '@')
							{
								wr << symbol;
								string input = "";
								for (int i = 0; i < strlen("-moz-document"); i++)
								{
									input += rd.get();
									if (input[i] == '/' || input[i] == '*' || input[i] == '{' || input[i] == ',' || input[i] == 13) {
										rd.seekg(-i, ios::cur);
										break;
									}
								}
								if (input == "-moz-document") {
									wr << input;
									do {
										symbol = rd.get();
										wr << symbol;
									} while (symbol != '{'); //После -moz-document игнорируется открытие блока
								}
								else {
									perr("Внимание: @ обнаружен, ожидалось "); clr(progress_color); printf("-moz-document");
									clr(negative_color); printf("а обнаружено "); clr(progress_color); printf("%s", input); clr();
									printf(". Игнорирование "); clr(progress_color); printf("{}"); clr(); printf(" отменено");
									int NotAnUnsignedInt = input.length();
									rd.seekg(-NotAnUnsignedInt,ios::cur);
								}

							}
							else if (!rd.eof()) wr << symbol;
				int cur = rd.tellg();
				if (cur > 17915+2718-145) {
					printf("");
				}
			} while (!rd.eof());
			wr.close();
			clr(positive_color); printf("[dir]ирование кода завершено!");
			clr(); printf(" Повторить?");
			Repeat = qu();
		}
	}
}