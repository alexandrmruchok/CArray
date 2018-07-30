#include "stdafx.h"

#include "cArray.h"
#include <regex>

using namespace std;

void stage(
  char* _caption,
  bool  _paragraf = false
)
{
  if (_paragraf)
    cout << "============================================================\n";
  cout << _caption << endl;
  if (_paragraf)
    cout << endl;
}




int main()
{
  setlocale(LC_ALL, "Rus");
  srand(time(0));

  // ====================================================================
  stage("1. Работа с числами (int).", true);

  CArray<int> intArr;


  stage("1.1. добавление в цикле 20 случайных чисел в диапазоне от 0 до 100.");

  for (int i = 0; i < 20; i++)
    intArr.push_back(rand() % 101);

  intArr.out();


  stage("1.2. упорядочивание получившегося набора чисел по возрастанию.");

  intArr.sort();

  intArr.out();


  stage("1.3. удаление каждого 2 элемента.");

  for (unsigned int i = 1; i < intArr.size(); i++)
    intArr.erase(i);

  intArr.out();


  stage("1.4.вставка 10 случайных чисел в диапазоне от 0 до 100 на случайные позиции.");

  for (int i = 1; i <= 10; i++)
  {
    unsigned int position = rand() % intArr.size();
    unsigned int value = rand() % 101;
    intArr.insert(position, value);
  }

  intArr.out();


  stage("1.5.очистка контейнера.");

  intArr.clear();

  intArr.out();


  // ====================================================================
  stage("2. Работа с объектами (std:string).", true);

  CArray<string> strArr;

  const unsigned int WORDS_COUNT = 30;
  string words[WORDS_COUNT] = { "lorm", "ipsum", "olor", "sit", "amet", "consectetur", "adipiscing", "elit", "vivamus", "maximus", "facilisis", "velit", "non", "faucibus", "ex", "mollis", "ugut", "null", "facilisi", "fus", "vulput", "tristiqu", "imprit", "suspendisse", "untum", "nisi", "euismod", "ligula", "vehicula", "ac" };


  stage("2.1. добавление в цикле 15 случайно выбранных слов, состоящих из латинских букв в нижнем регистре.");

  for (int i = 1; i <= 15; i++)
  {
    string value = words[rand() % (WORDS_COUNT)];
    strArr.push_back(value);
  }

  strArr.out();


  stage("2.2. упорядочивание получившегося набора слов по возрастанию.");

  strArr.sort();

  strArr.out();


  stage("2.3.удаление каждого слова, включающего в себя любую из букв a, b, c, d, e.");

  regex reg("[abcde]");

  for (unsigned int i = 0; i < strArr.size(); i)
  {
    if (regex_search(strArr[i], reg))
      strArr.erase(i);
    else
      i++;
  }
  strArr.out();


  stage("2.4. вставка 3 новых случайно выбранных слов на случайные позиции.");

  for (int i = 1; i <= 3; i++)
  {
    unsigned int position = strArr.size() ? (rand() % strArr.size()) : 0;
    string value = words[rand() % (WORDS_COUNT)];
    strArr.insert(position, value);
  }

  strArr.out();


  system("pause");
  return 0;
}
