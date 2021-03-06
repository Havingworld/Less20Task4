/*
Требуется реализовать упрощённую симуляцию работы банкомата. В банкомате могут храниться только бумажные купюры номиналом от 100 до 5000 рублей.
Максимально в банкомате может храниться только 1000 купюр. Все они записываются в отдельный файл.
У банкомата, как у устройства, две основных операции — снятие денег пользователем и наполнение деньгами инкассаторами банка.

Наполнение банкомата происходит, если при старте программы в консоль вводится символ плюс “+”.  Количество купюр рассчитывается так,
чтобы банкомат был заполнен полностью. Все купюры при этом выбираются случайным образом.

Если на старте программы в консоль вводится минус (“-”), то симулируется снятие пользователем денег. Пользователь указывает сумму с
точностью до 100 рублей. Мы будем считать, что каждый клиент обладает неограниченным балансом в системе и теоретически может снять любую сумму.
На практике, если данная сумма не может быть снята из-за отсутствия подходящих денег в машине, показывается сообщение, что эта операция невозможна.

После выполнения любой из операций программа завершает выполнение. Состояние банкомата должно храниться в отдельном бинарном файле, автономно.

Советы и рекомендации
Вы можете хранить массив купюр целиком, помечая отсутствующие позиции нулями.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

void readcash(vector <int>& money)
{
    fstream cash("cash.bin", fstream::in | ios::binary);
    //fstream cash("cash.txt");
    if (cash.is_open())
    {
        cash.read((char*)money.data(), money.size() * sizeof(int));
        
        cash.close();
    }
    else
    {
        // show error message
        cout << "error opening cash.bin";
    }
}

void writecash(vector <int> money)
{
    fstream cash("cash.bin", fstream::out | ios::binary);
    //fstream cash("cash.txt");
    if (cash.is_open())
    {
        cash.write((char*)money.data(), money.size() * sizeof(int));

        cash.close();
    }
    else
    {
        // show error message
        cout << "error opening cash.bin";
    }
}

int main()
{
    srand(time(nullptr)); //randomized random
    int bill[6] = { 5000,2000,1000,500,200,100 }; //bill varius
    //write input cash.bin      
    int nInput = 0;
    vector <int> money;

    for (int i = 0; i < 1000; ++i)
    {
        money.push_back(bill[rand() % 6]);
    }

    writecash(money);

    cout << endl << "input ""-1"" for exit" << endl;

    readcash(money);

    while (nInput != -1)
    {
        cout << endl << "input sum multiple of 100: ";
        cin >> nInput;
        if (nInput % 100) continue;

        int bill_temp = 0;

        if (nInput < 0)
        {

            nInput = abs(nInput);

            //Разложить запрос на купюры
            // 8800 % 5000 = 3800
            // 3800 % 2000 = 1800
            // 1800 % 1000 = 800
            // 800 % 500 = 300
            // 300 % 200 = 100
            // 100 % 100 = 0

            int cashwithdrawal[] = { 0, 0, 0, 0, 0, 0 };

            for (int i = 0; i < 6; ++i)
            {
                //if (nInput % bill[i])   //может не работает на 100
                //{
                    cashwithdrawal[i] = nInput / bill[i];
                    nInput = nInput % bill[i];
                //}
            }

            //извлечь купюры
            //используя два массива пройти по файлу
            for (int i = 0; i < 6; ++i)
            {
                //if (cashwithdrawal[i] > 0) {
                    for (int n = 0; n < money.size(); ++n)
                    {
                        if (cashwithdrawal[i] == 0) break;
                        if (money[n] == bill[i])
                        {
                            bill_temp += bill[i];
                            money[n] = 0;
                            cashwithdrawal[i] -= 1;
                        }                       
                    }
               // }
            }

            cout << endl << "take cash: " << bill_temp;
            //если нет крупных купюр, выдать более мелкими
            // 
            //вывести купюры на экран
        }
        else if (nInput > 0)
        {

            for (int i = 0; i < money.size(); ++i)
            {
                if (money[i] == 0)
                {
                    money[i] = bill[rand() % 6];
                    bill_temp += money[i];
                }
            }

            cout << endl << "added cash: " << bill_temp;

        }

        writecash(money);
    }

}
