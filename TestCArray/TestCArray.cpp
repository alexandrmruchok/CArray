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
  stage("1. ������ � ������� (int).", true);

  CArray<int> intArr;


  stage("1.1. ���������� � ����� 20 ��������� ����� � ��������� �� 0 �� 100.");

  for (int i = 0; i < 20; i++)
    intArr.push_back(rand() % 101);

  intArr.out();


  stage("1.2. �������������� ������������� ������ ����� �� �����������.");

  intArr.sort();

  intArr.out();


  stage("1.3. �������� ������� 2 ��������.");

  for (unsigned int i = 1; i < intArr.size(); i++)
    intArr.erase(i);

  intArr.out();


  stage("1.4.������� 10 ��������� ����� � ��������� �� 0 �� 100 �� ��������� �������.");

  for (int i = 1; i <= 10; i++)
  {
    unsigned int position = rand() % intArr.size();
    unsigned int value = rand() % 101;
    intArr.insert(position, value);
  }

  intArr.out();


  stage("1.5.������� ����������.");

  intArr.clear();

  intArr.out();


  // ====================================================================
  stage("2. ������ � ��������� (std:string).", true);

  CArray<string> strArr;

  const unsigned int WORDS_COUNT = 30;
  string words[WORDS_COUNT] = { "lorm", "ipsum", "olor", "sit", "amet", "consectetur", "adipiscing", "elit", "vivamus", "maximus", "facilisis", "velit", "non", "faucibus", "ex", "mollis", "ugut", "null", "facilisi", "fus", "vulput", "tristiqu", "imprit", "suspendisse", "untum", "nisi", "euismod", "ligula", "vehicula", "ac" };


  stage("2.1. ���������� � ����� 15 �������� ��������� ����, ��������� �� ��������� ���� � ������ ��������.");

  for (int i = 1; i <= 15; i++)
  {
    string value = words[rand() % (WORDS_COUNT)];
    strArr.push_back(value);
  }

  strArr.out();


  stage("2.2. �������������� ������������� ������ ���� �� �����������.");

  strArr.sort();

  strArr.out();


  stage("2.3.�������� ������� �����, ����������� � ���� ����� �� ���� a, b, c, d, e.");

  regex reg("[abcde]");

  for (unsigned int i = 0; i < strArr.size(); i)
  {
    if (regex_search(strArr[i], reg))
      strArr.erase(i);
    else
      i++;
  }
  strArr.out();


  stage("2.4. ������� 3 ����� �������� ��������� ���� �� ��������� �������.");

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
