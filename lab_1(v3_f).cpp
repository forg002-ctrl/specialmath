#include <iostream>
#include <conio.h>
using namespace std;

void print_ma_smej(int** ma_smej, int tops);
void print_spk(int* spk, int tops);
void print_ma_inti(int** ma_inti, int tops, int arcs);
void ma_smej_v_spk(int** ma_smej, int tops, int*& spk);
void spk_v_ma_smej(int* spk, int**& ma_smej, int tops);
void ma_inti_v_spk(int** ma_inti, int tops, int arcs, int*& spk);
void spk_v_ma_inti(int* spk, int**& ma_inti, int tops);
void ma_inti_v_spk(int** ma_inti, int tops, int arcs, int*& spk);
void ma_smej_v_ma_inti(int** ma_smej, int tops, int**& ma_inti);
void ma_inti_v_ma_smej(int** ma_inti, int tops, int arcs, int**& ma_smej);
int** memory_allocation_1(int tops, int arcs, int choice);
int* memory_allocation_2(int tops, int counter);
void memory_delete(int tops, int arcs, int**& mx, int type);
int menu(int& choice_3, bool inserted);

int main()
{
    int tops, arcs, choice_2, choice_3, digit, counter, counter_tmp, choice, **ma_smej{},
        **ma_inti{}, *spk{};
    bool finish, inserted = false;
    menu(choice_3, inserted);
    while (finish != true)
    {
        if (choice_3 == 1)
        {
            if (inserted == true)
            {
                memory_delete(tops, 0, ma_smej, 1);
                memory_delete(0, arcs, ma_inti, 2);
                if (spk != nullptr)
                {
                    delete[] spk;
                    spk = nullptr;
                }
                inserted = false;
            }
            cout << "      Способы ввода графа    \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n|   1.Матрица "
                    "смежности       |\n|   2.Список смежности        |\n|   3.Матрица "
                    "инцидентности   |\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                 << endl;
            cout << "Cпособ номер - ";
            cin >> choice;
            cout << "----------------" << endl;
            while (choice != 1 && choice != 2 && choice != 3)
            {
                cout << "Вы ввели неправильное число, введите еще раз - ";
                cin >> choice;
            }
            cout << "Введите кол-во вершин графа - ";
            cin >> tops;
            while (tops < 3)
            {
                cout
                    << "Вы вели слишком маленькое количество вершин графа, введите другое число - ";
                cin >> tops;
            }
            if (choice == 1)
            {
                ma_smej = memory_allocation_1(tops, 0, 1);
                cout << "Заполните матрицу смежности построчно через пробел: " << endl;
                counter = 0;
                for (int i = 0; i < tops; ++i)
                {
                    counter_tmp = 0;
                    cout << "Элементы " << i + 1 << " строки - ";
                    for (int j = 0; j < tops; ++j)
                    {
                        cin >> digit;
                        if (digit == 1 || digit == 2)
                        {
                            counter_tmp++;
                        }
                        if (digit != 0 && digit != 1 && digit != 2)
                        {
                            cin.clear();
                            cin.ignore(100, '\n');
                            cout << "Вы ввели неверное число, возвожные варианты ввода 1, 0, 2. "
                                    "Прошлые данные неправильные, начните ввод данных для "
                                 << i + 1 << " строки сначала." << endl;
                            cout << "Элементы " << i + 1 << " строки - ";
                            counter_tmp = 0;
                            j = -1;
                        }
                        else
                        {
                            ma_smej[i][j] = digit;
                        }
                    }
                    counter = counter + counter_tmp;
                }
            }
            if (choice == 2)
            {
                int* tmp = memory_allocation_2(tops, tops * tops);
                cout << "Заполните список смежности построчно через пробел (ставьте 0 в конце "
                        "каждой строки): "
                     << endl;
                bool flag;
                counter = 0;
                for (int i = 0; i < tops; ++i)
                {
                    counter_tmp = 0;
                    cout << i + 1 << " - ";
                    flag = false;
                    while (flag != true)
                    {
                        cin >> digit;
                        if (digit < 0 || digit > tops)
                        {
                            cin.clear();
                            cin.ignore(100, '\n');
                            for (int i = 0; i < counter_tmp; ++i)
                            {
                                tmp[counter + i] = 0;
                            }
                            cout << "Вы вели неправильный номер вершины. Прошлые данные "
                                    "неправильные, начните ввод данных для "
                                 << i + 1 << " строки сначала - " << endl;
                            i--;
                            counter_tmp = 0;
                            break;
                        }
                        tmp[counter + counter_tmp] = digit;
                        counter_tmp++;
                        if (digit == 0)
                        {
                            cin.clear();
                            cin.ignore(100, '\n');
                            flag = true;
                        }
                    }
                    counter = counter + counter_tmp;
                }
                spk = memory_allocation_2(0, counter);
                for (int i = 0; i < counter; ++i)
                {
                    spk[i] = tmp[i];
                }
                delete[] tmp;
                counter = counter - tops;
            }
            if (choice == 3)
            {
                cout << "Введите кол-во дуг графа - ";
                cin >> arcs;
                ma_inti = memory_allocation_1(tops, arcs, 2);
                cout << "Заполните матрицу инцидентности построчно через пробел: " << endl;
                counter = 0;
                for (int i = 0; i < arcs; ++i)
                {
                    counter_tmp = 0;
                    cout << "Элементы " << i + 1 << " строки - ";
                    for (int j = 0; j < tops; ++j)
                    {
                        cin >> digit;
                        if (digit == 1 || digit == 2)
                        {
                            counter_tmp++;
                        }
                        if (digit != 0 && digit != 1 && digit != 2 && digit != -1)
                        {
                            cin.clear();
                            cin.ignore(100, '\n');
                            cout << "Вы ввели неверное число, возвожные варианты ввода 1, 0, 2, "
                                    "-1. Прошлые данные неправильные, начните ввод данных для "
                                 << i + 1 << " строки сначала." << endl;
                            counter_tmp = 0;
                            j = -1;
                            cout << "Элементы " << i + 1 << " строки - ";
                        }
                        else
                        {
                            ma_inti[i][j] = digit;
                        }
                    }
                    counter = counter + counter_tmp;
                }
            }
            inserted = true;
            menu(choice_3, inserted);
        }
        if (choice_3 == 2)
        {
            cout << "     Способы вывода графа    \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n|   1.Матрица "
                    "смежности       |\n|   2.Список смежности        |\n|   3.Матрица "
                    "инцидентности   |\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                 << endl;
            cout << "Cпособ номер - ";
            cin >> choice_2;
            cout << "----------------" << endl;
            while (choice_2 != 1 && choice_2 != 2 && choice_2 != 3)
            {
                cout << "Вы ввели неправильное число, введите еще раз - ";
                cin >> choice_2;
            }
            if (choice_2 == 1)
            {
                if (choice == 1)
                {
                    print_ma_smej(ma_smej, tops);
                }
                if (choice == 2)
                {
                    ma_smej = memory_allocation_1(tops, 0, 1);
                    spk_v_ma_smej(spk, ma_smej, tops);
                    print_ma_smej(ma_smej, tops);
                    memory_delete(tops, 0, ma_smej, 1);
                }
                if (choice == 3)
                {
                    ma_smej = memory_allocation_1(tops, 0, 1);
                    ma_inti_v_ma_smej(ma_inti, tops, arcs, ma_smej);
                    print_ma_smej(ma_smej, tops);
                    memory_delete(tops, 0, ma_smej, 1);
                }
            }
            if (choice_2 == 2)
            {
                if (choice == 1)
                {
                    spk = memory_allocation_2(tops, counter);
                    ma_smej_v_spk(ma_smej, tops, spk);
                    print_spk(spk, tops);
                    delete[] spk;
                    spk = nullptr;
                }
                if (choice == 2)
                {
                    print_spk(spk, tops);
                }
                if (choice == 3)
                {
                    spk = memory_allocation_2(tops, arcs);
                    ma_inti_v_spk(ma_inti, tops, arcs, spk);
                    print_spk(spk, tops);
                    delete[] spk;
                    spk = nullptr;
                }
            }
            if (choice_2 == 3)
            {
                if (choice == 1)
                {
                    arcs = counter;
                    ma_inti = memory_allocation_1(tops, arcs, 2);
                    ma_smej_v_ma_inti(ma_smej, tops, ma_inti);
                    print_ma_inti(ma_inti, tops, arcs);
                    memory_delete(0, arcs, ma_inti, 2);
                }
                if (choice == 2)
                {
                    arcs = counter;
                    ma_inti = memory_allocation_1(tops, arcs, 2);
                    spk_v_ma_inti(spk, ma_inti, tops);
                    print_ma_inti(ma_inti, tops, arcs);
                    memory_delete(0, arcs, ma_inti, 2);
                }
                if (choice == 3)
                {
                    print_ma_inti(ma_inti, tops, arcs);
                }
            }
            getch();
            menu(choice_3, inserted);
            if (choice_3 != 2)
            {
                if (choice == 1)
                {
                    memory_delete(tops, 0, ma_smej, 1);
                }
                if (choice == 2)
                {
                    delete[] spk;
                    spk = nullptr;
                }
                if (choice == 3)
                {
                    memory_delete(0, arcs, ma_inti, 2);
                }
            }
        }
        if (choice_3 == 3)
        {
            if (inserted == true)
            {
                memory_delete(tops, 0, ma_smej, 1);
                memory_delete(0, arcs, ma_inti, 2);
                if (spk != nullptr)
                {
                    delete[] spk;
                }
            }
            finish = true;
        }
    }
}

void print_ma_smej(int** ma_smej, int tops)
{
    for (int i = -1; i < tops; ++i)
    {
        if (i >= 0)
        {
            cout << "x" << i + 1 << "\t";
        }
        else
        {
            cout << "\t";
        }
        for (int j = 0; j < tops; ++j)
        {
            if (i < 0)
            {
                cout << "x" << j + 1 << "\t";
            }
            else
            {
                cout << ma_smej[i][j] << "\t";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void print_spk(int* spk, int tops)
{
    int tmp = 0;
    for (int i = 0; i < tops; ++i)
    {
        cout << i + 1 << " - ";
        while (spk[tmp] != 0)
        {
            cout << spk[tmp];
            tmp++;
            if (spk[tmp] != 0)
            {
                cout << " , ";
            }
            else
            {
                cout << endl;
            }
        }
        tmp++;
    }
    cout << endl;
}

void print_ma_inti(int** ma_inti, int tops, int arcs)
{
    for (int i = -1; i < arcs; ++i)
    {
        if (i >= 0)
        {
            cout << " e" << i + 1 << "\t";
        }
        else
        {
            cout << "\t";
        }

        for (int j = 0; j < tops; ++j)
        {
            if (i < 0)
            {

                cout << " x" << j + 1 << "\t";
            }
            else
            {
                if (ma_inti[i][j] < 0)
                {
                    cout << ma_inti[i][j] << "\t";
                }
                else
                {
                    cout << " " << ma_inti[i][j] << "\t";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

void ma_smej_v_spk(int** ma_smej, int tops, int*& spk)
{
    int k = 0;
    for (int i = 0; i < tops; ++i)
    {
        for (int j = 0; j < tops; ++j)
        {
            if (ma_smej[i][j] == 1 || ma_smej[i][j] == 2)
            {
                spk[k] = j + 1;
                k++;
            }
        }
        spk[k] = 0;
        k++;
    }
}

void spk_v_ma_smej(int* spk, int**& ma_smej, int tops)
{
    int counter = 0;
    int k = 0;
    while (counter != tops)
    {
        if (spk[k] == 0)
        {
            counter++;
            k++;
        }
        else
        {
            if (spk[k] == counter + 1)
            {
                ma_smej[counter][spk[k] - 1] = 2;
            }
            else
            {
                ma_smej[counter][spk[k] - 1] = 1;
            }
            k++;
        }
    }
}

void spk_v_ma_inti(int* spk, int**& ma_inti, int tops)
{
    int counter = 0;
    int k = 0;
    int tmp = 0;
    while (counter != tops)
    {
        if (spk[k] == 0)
        {
            counter++;
            k++;
        }
        else
        {
            if (spk[k] == counter + 1)
            {
                ma_inti[tmp][spk[k] - 1] = 2;
                tmp++;
            }
            else
            {
                ma_inti[tmp][spk[k] - 1] = 1;
                ma_inti[tmp][counter] = -1;
                tmp++;
            }
            k++;
        }
    }
}

void ma_inti_v_spk(int** ma_inti, int tops, int arcs, int*& spk)
{
    int tmp[tops];
    int k = 0;
    int counter;
    for (int j = 0; j < tops; j++)
    {
        tmp[tops] = 0;
        counter = 0;
        for (int i = 0; i < arcs; i++)
        {
            if (ma_inti[i][j] == 2)
            {
                tmp[counter] = j + 1;
                counter++;
            }
            if (ma_inti[i][j] == -1)
            {
                for (int j_tmp = 0; j_tmp < tops; ++j_tmp)
                {
                    if (ma_inti[i][j_tmp] == 1)
                    {
                        tmp[counter] = j_tmp + 1;
                        counter++;
                    }
                }
            }
        }
        if (counter > 1)
        {
            for (int i = 0; i < counter; ++i)
            {
                if (tmp[i] > tmp[i + 1])
                {
                    int b = tmp[i];
                    tmp[i] = tmp[i + 1];
                    tmp[i + 1] = b;
                }
            }
        }
        for (int i = 0; i < counter; ++i)
        {
            spk[k] = tmp[i];
            k++;
        }
        spk[k] = 0;
        k++;
    }
}

void ma_smej_v_ma_inti(int** ma_smej, int tops, int**& ma_inti)
{
    int arcs = 0;
    for (int i = 0; i < tops; i++)
    {
        for (int j = 0; j < tops; j++)
        {
            if (ma_smej[i][j] == 1 || ma_smej[i][j] == 2)
            {
                if (ma_smej[i][j] == 1)
                {
                    ma_inti[arcs][j] = 1;
                    ma_inti[arcs][i] = -1;
                    arcs++;
                }
                else
                {
                    ma_inti[arcs][i] = 2;
                    arcs++;
                }
            }
        }
    }
}

void ma_inti_v_ma_smej(int** ma_inti, int tops, int arcs, int**& ma_smej)
{
    bool uzel;
    int i_tmp, j_tmp;
    for (int i = 0; i < arcs; ++i)
    {
        uzel = false;
        for (int j = 0; j < tops; ++j)
        {
            if (ma_inti[i][j] == 2)
            {
                uzel = true;
                i_tmp = j;
            }
            else
            {
                if (ma_inti[i][j] == -1)
                {
                    i_tmp = j;
                }
                if (ma_inti[i][j] == 1)
                {
                    j_tmp = j;
                }
            }
        }
        if (uzel == true)
        {
            ma_smej[i_tmp][i_tmp] = 2;
        }
        else
        {
            ma_smej[i_tmp][j_tmp] = 1;
        }
    }
}

int** memory_allocation_1(int tops, int arcs, int type)
{
    if (type == 1)
    {
        int** mtx = new int*[tops];
        for (int i = 0; i < tops; ++i)
        {
            mtx[i] = new int[tops]{};
        }
        return mtx;
    }

    {
        int** mtx = new int*[arcs];
        for (int i = 0; i < arcs; ++i)
        {
            mtx[i] = new int[tops]{};
        }
        return mtx;
    }
}

int* memory_allocation_2(int tops, int counter)
{
    int* spk = new int[counter + tops]{};
    return spk;
}

void memory_delete(int tops, int arcs, int**& mx, int type)
{
    if (mx != nullptr)
    {
        if (type == 1)
        {
            for (int i = 0; i < tops; ++i)
            {
                delete[] mx[i];
            }
            delete[] mx;
        }
        if (type == 2)
        {
            for (int i = 0; i < arcs; ++i)
            {
                delete[] mx[i];
            }
            delete[] mx;
        }
        mx = nullptr;
    }
}

int menu(int& choice_3, bool inserted)
{

    cout << "            Меню    \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n|   1.Ввести граф           |\n| "
            "  2.Вывести граф          |\n|   3.Выйти из програмы     "
            "|\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         << endl;
    cout << "Пункт номер - ";
    cin >> choice_3;
    if (choice_3 == 3)
    {
        cout << "Программа завершена" << endl;
        return 0;
    }
    while (choice_3 != 1 && inserted != true)
    {
        cout << "Для начала нужно ввести граф, введите число 1 для ввода графа - ";
        cin >> choice_3;
    }
    cout << endl;
    return choice_3;
}
