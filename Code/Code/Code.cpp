#include <iostream>

using namespace std;

int IteratuionsCounter = 0;

int board[500][500];

void setQueen(int row, int column, int boardSize)
{
    for (int x = 0; x < boardSize; ++x)
    {
        board[x][column]++;
        board[row][x]++;

        int diagonal = column - row + x;

        if (diagonal >= 0 && diagonal < boardSize)
            board[x][diagonal]++;

        diagonal = column + row - x;

        if (diagonal >= 0 && diagonal < boardSize)
            board[x][diagonal]++;
    }

    board[row][column] = -1;
}

void removeQueen(int row, int column, int boardSize)
{
    for (int x = 0; x < boardSize; ++x)
    {
        board[x][column]--;
        board[row][x]--;

        int diagonal = column - row + x;

        if (diagonal >= 0 && diagonal < boardSize)
            board[x][diagonal]--;

        diagonal = column + row - x;

        if (diagonal >= 0 && diagonal < boardSize)
            board[x][diagonal]--;
    }

    board[row][column] = 0;
}

bool safeCheck(int *Arr, int size) 
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
        int place;

        do
        {
            place = availablePlaces[rand() % n];
        } 
        while (place == -1);
        


        cout << "Случайным образом выбрана позиция для постановки новой королевы: " << row + 1 << ":" << place + 1 << endl;

        setQueen(row, place, n);

        if (row == (n - 1))
        {
            cout << endl <<"Все " << n << " королев были успешно раставленны!" << endl << endl;
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

    cout << "Введите число королев и размер доски одни числом" << endl;

    cin >> n;

    if (n < 4)
    {
        cout << "Размер доски и кол-во королев должно быть больше ли равно 4" << endl;
        return 0;
    }

    cout << endl << "---------------------------" << endl;

    for (int row = 0; row < n; ++row)
        for (int square = 0; square < n; square++)
            board[row][square] = 0;

    PutQueens(0, n, 0);

    for (int row = 0; row < n; ++row)
    {
        for (int square = 0; square < n; square++)
        {
            if (board[row][square] == -1)
                cout << "[]";
            else
                cout << ". ";
        }

        cout << endl;
    }

    cout << endl << "Всего потребовалось итераций: " << IteratuionsCounter << endl;
}
