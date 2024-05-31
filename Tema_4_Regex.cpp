#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <fstream>

// verificare daca stringul dat este un numar intreg sau real sau nu este numar, afiseaza pe ecran rezultatul

void isNumberIntregOrRealOrNAN(const std::string& number)
{
	std::regex itegerlNumberPattern(R"(0|[1-9][0-9]*)");
	std::regex realNumberPatern(R"([0-9]+[.,][0-9]+)");

	if (std::regex_match(number, itegerlNumberPattern))
		std::cout << "Stringul este un numar intreg" << std::endl;
	else if (std::regex_match(number, realNumberPatern))
		std::cout << "Stringul este un numar real" << std::endl;
	else
		std::cout << "Stringul nu este un numar" << std::endl;
}

// citirea textului din fisier, returneaza stringul cu textul citit
std::string readFromFile(std::string fileName)
{
	std::string myText;
	std::string result = "";
	std::ifstream input(fileName);

	while (!input.eof()) 
	{
		getline(input, myText);
		result = result + " " + myText;
	}
	input.close();
	result = result.substr(1);

	return result;
}

//verificare daca la inceputul cuvantului numarul literei "a" este par, returneaza numarul cuvantelor din text
int numberOfWordsWithEven_a_AtBegining(const std::string &text)
{
	int result = 0;
	std::regex even_a_Pattern(R"((aa)+([^a][A-Za-z]*)*)");
	std::stringstream stream(text);
	std::string tempString;

	while (getline(stream, tempString, ' ')) {
		if (std::regex_match(tempString, even_a_Pattern))
			result++;
	}
	return result;
}

//inlocuieste toate cuvintele cu "b" la inceput si la sfarsit cu lungimea cuvantului respectiv, afiseaza pe ecran textul modificat
void changeWordsB_BWithLength(const std::string& text)
{
	std::regex words_bb_Pattern(R"(b[A-Za-z]*b)");
	std::stringstream stream(text);
	std::string tempString;

	std::cout << "Textul modificat (b__b cuvinte inlocuite cu lungime) este:  ";

	while (getline(stream, tempString, ' ')) {
		{
			if (std::regex_match(tempString, words_bb_Pattern))
			{
				std::cout << tempString.size() << " ";
			}
			else
				std::cout << tempString << " ";
		}
	}
	std::cout << std::endl;
}

//verifica daca un cuvant contine simbolurile nepermise(care nu sunt din alfabet {a,b,c,d}), si daca da concateneaza aceste cuvinte intr-un string si il afiseaza pe ecran
void concatenareaCuvintelorInvalide(const std::string& text)
{
	std::string result = "";
	std::regex wordsInvalide_Pattern(R"([abcd]+)");
	std::stringstream stream(text);
	std::string tempString;

	std::cout << "Textul cu cuvinte invalide concatenate este:  ";

	while (getline(stream, tempString, ' ')) {
		{
			if (!std::regex_match(tempString, wordsInvalide_Pattern))
				result += tempString;
		}
	}
	if (result == "")
		std::cout << "Nu sunt cuvinte invalide" << std::endl;
	else
		std::cout << result << std::endl;
}

//verifica daca un password introdus de utilizator este strong sau nu, afiseaza pe ecran un mesaj corespunzator
void isPasswordStrong()
{
	std::string password;
	bool isStrong = false;
	std::cout << "Introduceti un password: ";
	std::cin >> password;
	std::cout << std::endl;

	std::regex simboluriSpeciale(R"([a-zA-Z0-9]*[%$#]+[a-zA-Z0-9]*)");
	std::regex literaMare(R"(\S*[A-Z]+\S*)");
	std::regex numarDeCaractere(R"(\S{10,})");
	std::regex twoCosequentDigits(R"(\S*\d\d\S*)");

	if (std::regex_match(password, simboluriSpeciale) && std::regex_match(password, literaMare) && std::regex_match(password, numarDeCaractere) && std::regex_match(password, twoCosequentDigits))
		isStrong = true;
	if (isStrong)
		std::cout << "The password is strong!" << std::endl;
	else
		std::cout << "The password is weak!" << std::endl;

}


int main()
{
	isNumberIntregOrRealOrNAN("013.31");
	isNumberIntregOrRealOrNAN("5.0");
	isNumberIntregOrRealOrNAN("5.8");
	isNumberIntregOrRealOrNAN("5,8");
	isNumberIntregOrRealOrNAN("5,0");
	isNumberIntregOrRealOrNAN("0,0");
	isNumberIntregOrRealOrNAN("0");
	isNumberIntregOrRealOrNAN("10236078");
	isNumberIntregOrRealOrNAN("0236078");
	std::cout << std::endl;
	
	std::string text = readFromFile("MyText.txt");
	std::cout << "Textul citit din fisier: " << text << std::endl;
	std::cout << std::endl;
	std::cout << "Numarul cuvantelor cu numarul par de litera (a) la inceput este: " << numberOfWordsWithEven_a_AtBegining(text) << std::endl;
	std::cout << std::endl;

	changeWordsB_BWithLength(text);
	std::cout << std::endl;

	concatenareaCuvintelorInvalide(text);
	std::cout << std::endl;

	isPasswordStrong();
}
