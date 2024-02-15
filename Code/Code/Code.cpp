#include <iostream>

using namespace std;

int IteratuionsCounter = 0;

int board[500][500];

void setQueen(int row, int column, int n)
{
    for (int x = 0; x < n; ++x)
    {
        ++board[x][column];
        ++board[row][x];

        int diagonal = column - row + x;

        if (diagonal >= 0 && diagonal < n)
            ++board[x][diagonal];

        diagonal = column + row - x;

        if (diagonal >= 0 && diagonal < n)
            ++board[x][diagonal];
    }

    board[row][column] = -1;
}

void removeQueen(int row, int column, int n)
{
    for (int x = 0; x < n; ++x)
    {
        --board[x][column];
        --board[row][x];

        int diagonal = column - row + x;

        if (diagonal >= 0 && diagonal < n)
            --board[x][diagonal];

        diagonal = column + row - x;

        if (diagonal >= 0 && diagonal < n)
            --board[x][diagonal];
    }

    board[row][column] = 0;
}

bool safeCheck(int *Arr, int size, bool shouldChangeArray = false) 
{
    bool flag = false;
    int counter = 0;

    while (!flag && counter < size)
    {
        flag = Arr[counter] != -1;
        counter++;
    }

    return flag;
}

bool PutQueens(int row, int n, int rootId) 
{
    int id = ++IteratuionsCounter;

    cout << "Создание новой итерации с id = " << id << ", ряд: " << row + 1 << ", id родительской итерации: " << rootId << endl << endl;

	bool result = false;
    bool flag = false;

    int availablePlaces[500];

    for (int i = 0; i < n; i++)
        availablePlaces[i] = board[row][i] == 0 ? i : -1;

    while (!result && safeCheck(&availablePlaces[0], n))
    {
        int place = availablePlaces[rand() % n];

        while (place == -1)
            place = availablePlaces[rand() % n];

        cout << "Случайным образом выбрана позиция для постановки новой королевы: " << row + 1 << ":" << place + 1 << endl;

        setQueen(row, place, n);

        if (row == (n - 1))
        {
            cout << "Все " << n << " королев были успешно раставленны!" << endl << endl;
            result = true;
        }
        else
        {
            cout << "Переход на следующий ряд, создание новой итерации!" << endl << "---------------------------" << endl;
            result = PutQueens(row + 1, n, id);
        }

        if (!result)
        {
            flag = true;
            cout << "Не удалось успешно поставить королев в последующие ряды при условии, что в ряде " << row + 1 << " королева стоит на " << place + 1 << " месте" << ". Пытаемся выбрать новое место" << endl << "---------------------------" << endl;
            removeQueen(row, place, n);
            availablePlaces[place] = -1;
        }
    }

    if (!result && !flag)
        cout << "Не удалось успешно поставить королев в ряд " << row + 1 << ". Возвращаемся на предыдущий ряд " << "(" << row << ")" << " (id, в который вернемся:  " << rootId << ")" << endl << "---------------------------" << endl;

    return result;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(0));

    int n;

    cin >> n;

    if (n < 4)
        return 0;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            board[i][j] = 0;

    PutQueens(0, n, 0);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (board[i][j] == -1)
                cout << "[]";
            else
                cout << ". ";
        }
        cout << endl;
    }
}
