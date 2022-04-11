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
using namespace std;

int main()
{
    srand(time(nullptr)); //randomized random

    int bill[6] = { 100,200,500,1000,2000,5000 }; //bill varius 
    vector <int> money;
    

    for (int i = 0; i < 1000; ++i)
    {
        money.push_back(bill[rand() % 6]);   
    }

    //write input cash.bin
    fstream cash("cash.bin", fstream::in | fstream::out | ios::binary);
    //fstream cash("cash.txt");
    if (cash.is_open())
    {
        for (int i = 0; i < 1000; ++i)
        {
            cash.write((char*)&money[i], sizeof(money[i]));
        }        
        
    //}
    //else
    //{
    //    // show message:
    //    cout << "Error opening basket.txt";
    //}

    //cash.close();

        vector <int> in_cash;  //cash inside cash.bin
    
    //read input cash.bin
    //ifstream cash("cash.bin");
    //if (cash.is_open())
    //{
        //cash.seekg(0);
        while (!cash.eof())
        { 
            int in_read;
            cash >> in_read;
            //cash.read((char*)&in_cash[i], sizeof(int));
            in_cash.push_back(in_read);
        }
    }
    else
    {
        // show error message
        cout << "error opening river.txt";
    }
    cash.close();
  
}
