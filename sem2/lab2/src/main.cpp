#include <windows.h>
#include <map>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <thread>
using std::pair;
using std::vector;

std::map<int, int> TimerMap;
std::pair<int, int> Current;
int Timer1Id = 1;
bool Timer = true;
int speed = 1000;

class State
{
    bool _isAlive;

public:
    State(bool isAlive)
    {
        _isAlive = isAlive;
    }

    bool IsAlive()
    {
        return _isAlive;
    }

    void SetIsAlive(bool isAlive)
    {
        _isAlive = isAlive;
    }
};

class Cell
{
    int _lives = 0;
    State _state = State(false);

public:
    void SetLives(int lives)
    {
        _lives = lives;
    }
    int GetLives()
    {
        return _lives;
    }
    Cell(State state)
    {
        _state = state;
    }

    Cell()
    {
    }

    bool IsAlive()
    {
        return _lives > 0;
    }

    void SetIsAlive(bool isAlive)
    {
        _state = isAlive;
        if (isAlive){
            _lives = 2;
        } else {
            _lives = 0;
        }
    }
};

class Grid
{
    std::vector<std::vector<Cell>> _cells;
    int _width;
    int _height;

public:
    Grid(int width, int height) : _width(width), _height(height)
    {
        _cells.resize(height);

        for (auto rowIndex = 0; rowIndex < height; ++rowIndex)
        {
            _cells[rowIndex].resize(width);
        }
    }
    void Resize(int width, int height)
    {
        _cells.resize(height);
        for (int i = 0; i < height; i++)
        {
            _cells[i].resize(width);
        }
        _width = width;
        _height = height;
    }
    int GetWidth()
    {
        return _width;
    }

    int GetHeight()
    {
        return _height;
    }

    Cell &GetCell(int rowIndex, int columnIndex)
    {
        if (rowIndex < 0 || rowIndex >= _height)
            throw std::exception("Wrong rowIndex");
        if (columnIndex < 0)
        {
            return _cells[rowIndex][_width + columnIndex];
        }
        if (columnIndex >= _width)
        {
            return _cells[rowIndex][_width - columnIndex];
        }

        return _cells[rowIndex][columnIndex];
    }
};

class LifeEngine
{
public:
    Grid CalculateNext(Grid currentGrid)
    {
        auto newGrid = Grid(currentGrid.GetWidth(), currentGrid.GetHeight());

        auto distance = 1;
        for (auto rowIndex = 0; rowIndex < currentGrid.GetHeight(); ++rowIndex)
        {
            for (auto columnIndex = 0; columnIndex < currentGrid.GetWidth(); ++columnIndex)
            {
                auto aliveCellCount = CalculateAliveNeighbour(rowIndex, columnIndex, currentGrid, distance);

                if (aliveCellCount == 3 && !currentGrid.GetCell(rowIndex, columnIndex).IsAlive())
                {
                    newGrid.GetCell(rowIndex, columnIndex).SetLives(2);
                }
                else if ((aliveCellCount == 2 || aliveCellCount == 3) && currentGrid.GetCell(rowIndex, columnIndex).IsAlive())
                {
                    newGrid.GetCell(rowIndex, columnIndex).SetLives(currentGrid.GetCell(rowIndex, columnIndex).GetLives());
                }
                else  
                {
                    if (currentGrid.GetCell(rowIndex, columnIndex).GetLives() > 0){
                        newGrid.GetCell(rowIndex, columnIndex).SetLives(currentGrid.GetCell(rowIndex, columnIndex).GetLives() - 1);
                    }
                }
            }
        }
        return newGrid;
    }

private:
    int GetLeftStartIndex(int columnIndex, int distance)
    {
        return max(columnIndex - distance, 0);
    }

    int GetTopStartIndex(int rowIndex, int distance)
    {
        return max(rowIndex - distance, 0);
    }

    int GetRightStartIndex(int columnIndex, int gridWidth, int distance)
    {
        return min(columnIndex + distance, gridWidth - 1);
    }

    int GetBottomStartIndex(int rowIndex, int gridHeight, int distance)
    {
        return min(rowIndex + distance, gridHeight - 1);
    }

    int CalculateAliveNeighbour(int rowIndex, int columnIndex, Grid currentGrid, int distance)
    {
        auto aliveCellCount = 0;

        auto leftStartIndex = GetLeftStartIndex(columnIndex, distance);
        auto rightStartIndex = GetRightStartIndex(columnIndex, currentGrid.GetWidth(), distance);
        auto topStartIndex = GetTopStartIndex(rowIndex, distance);
        auto bottomStartIndex = GetBottomStartIndex(rowIndex, currentGrid.GetHeight(), distance);

        for (auto neighbourColumnIndex = leftStartIndex; neighbourColumnIndex <= rightStartIndex; ++neighbourColumnIndex)
        {
            for (auto neighbourRowIndex = topStartIndex; neighbourRowIndex <= bottomStartIndex; ++neighbourRowIndex)
            {
                if (rowIndex == neighbourRowIndex && columnIndex == neighbourColumnIndex)
                    continue;

                if (currentGrid.GetCell(neighbourRowIndex, neighbourColumnIndex).IsAlive())
                {
                    ++aliveCellCount;
                }
            }
        }

        return aliveCellCount;
    }
};

Grid grid = Grid(10, 10);
LifeEngine lifeEngine;

void DrawGrid(HWND hWnd, HDC hdc)
{
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    auto cellWidth = clientRect.right / grid.GetWidth();

    for (auto j = 0; j < grid.GetWidth() + 1; ++j)
    {
        MoveToEx(hdc, cellWidth * j, 0, nullptr);
        LineTo(hdc, cellWidth * j, clientRect.bottom);
    }

    auto cellHeight = clientRect.bottom / grid.GetHeight();

    for (auto i = 0; i < grid.GetHeight() + 1; ++i)
    {
        MoveToEx(hdc, 0, cellHeight * i, nullptr);
        LineTo(hdc, clientRect.right, cellHeight * i);
    }
}

std::pair<int, int> Pos2Index(int width, int height, int x, int y)
{
    int xStep = width / grid.GetWidth();
    int yStep = height / grid.GetHeight();
    return std::make_pair(y / yStep, x / xStep);
}

void DrawLine(HDC hdc, long x, long y, long x_, long y_, COLORREF color, int style)
{
    auto defaultPen = SelectObject(hdc, CreatePen(style, 1, color));
    MoveToEx(hdc, x, y, nullptr);
    LineTo(hdc, x_, y_);
    DeleteObject(defaultPen);
}

void DrawHover(HWND hWnd, HDC hdc)
{
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    auto cellWidth = clientRect.right / grid.GetWidth();
    auto cellHeight = clientRect.bottom / grid.GetHeight();
    auto brush = CreateSolidBrush(RGB(255, 255, 0));
    RECT rect;

    rect.left = cellWidth * Current.second;
    rect.top = cellHeight * Current.first;
    rect.right = cellWidth * (Current.second + 1);
    rect.bottom = cellHeight * (Current.first + 1);
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
}

void HandleHover(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    int xPos = ((int)(short)LOWORD(lParam));
    int yPos = ((int)(short)HIWORD(lParam));

    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    Current = Pos2Index(clientRect.right, clientRect.bottom, xPos, yPos);
}

void DrawCells(HWND hWnd, HDC hdc)
{
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    auto cellWidth = clientRect.right / grid.GetWidth();
    auto cellHeight = clientRect.bottom / grid.GetHeight();

    auto blackBrush = CreateSolidBrush(RGB(0, 0, 0));
    auto redBrush = CreateSolidBrush(RGB(255, 0, 0));

    for (auto i = 0; i < grid.GetHeight(); ++i)
    {
        for (auto j = 0; j < grid.GetWidth(); ++j)
        {
            if (grid.GetCell(i, j).GetLives() > 0)
            {
                if (grid.GetCell(i, j).GetLives() == 2)
                {
                    SelectObject(hdc, blackBrush);
                }
                else
                {
                    SelectObject(hdc, redBrush);
                }
                Ellipse(hdc, j * cellWidth, i * cellHeight, (j + 1) * cellWidth, (i + 1) * cellHeight);
            }
        }
    }

    DeleteObject(redBrush);
    DeleteObject(blackBrush);
}

void OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    DrawGrid(hWnd, hdc);
    DrawHover(hWnd, hdc);
    DrawCells(hWnd, hdc);

    EndPaint(hWnd, &ps);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        grid.GetCell(0, 1).SetIsAlive(true);
        grid.GetCell(1, 2).SetIsAlive(true);
        grid.GetCell(2, 0).SetIsAlive(true);
        grid.GetCell(2, 1).SetIsAlive(true);
        grid.GetCell(2, 2).SetIsAlive(true);
        SetTimer(hWnd, Timer1Id, speed, nullptr);
        TimerMap[Timer1Id] = 0;
        break;
    }
    case WM_TIMER:
    {
        if (Timer)
        {
            grid = lifeEngine.CalculateNext(grid);
            TimerMap[Timer1Id]++;
        }
        InvalidateRect(hWnd, nullptr, true);
        break;
    }
    case WM_MOUSEMOVE:
    {
        HandleHover(hWnd, wParam, lParam);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        grid.GetCell(Current.first, Current.second).SetIsAlive(true);
        // grid.GetCell(Current.first, Current.second).SetLives(1);
    }
    break;
    case WM_RBUTTONDOWN:
    {
        grid.GetCell(Current.first, Current.second).SetIsAlive(false);
    }
    break;
    case WM_MOUSEWHEEL:
    {
        if ((GetKeyState(VK_SHIFT) & 0x8000) != 0)
        {
            if ((short)HIWORD(wParam) > 0)
            {
                if (grid.GetWidth() < 25)
                {
                    grid.Resize(grid.GetWidth() + 1, grid.GetHeight());
                }
            }
            else
            {
                if (grid.GetWidth() > 3)
                {
                    grid.Resize(grid.GetWidth() - 1, grid.GetHeight());
                }
            }
        }
        else
        {
            if ((short)HIWORD(wParam) > 0)
            {
                if (grid.GetHeight() < 25)
                {
                    grid.Resize(grid.GetWidth(), grid.GetHeight() + 1);
                }
            }
            else
            {
                if (grid.GetHeight() > 3)
                {
                    grid.Resize(grid.GetWidth(), grid.GetHeight() - 1);
                }
            }
        }
    }
    break;
    case WM_PAINT:
    {
        OnPaint(hWnd);
    }
    break;
    case WM_SYSKEYUP:
    {
        if (!Timer)
        {
            if (((GetKeyState(VK_CONTROL) & 0x8000) != 0) && wParam == VK_F10)
            {
                grid = lifeEngine.CalculateNext(grid);
                grid = lifeEngine.CalculateNext(grid);
                grid = lifeEngine.CalculateNext(grid);
                grid = lifeEngine.CalculateNext(grid);
                grid = lifeEngine.CalculateNext(grid);
                TimerMap[Timer1Id] += 5;
            }
            if (((GetKeyState(VK_CONTROL) & 0x8000) == 0) && wParam == VK_F10)
            {
                grid = lifeEngine.CalculateNext(grid);
                TimerMap[Timer1Id]++;
            }
        }
    }

    break;
    case WM_KEYDOWN:
    {

        if (wParam == VK_SPACE)
        {
            Timer = !Timer;
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
};

int CALLBACK wWinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    PWSTR args,
    int nCmdShow)
{
    MSG msg{};
    HWND hWnd{};
    WNDCLASS wc{};
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "GameOfLife";
    wc.style = CS_VREDRAW | CS_HREDRAW;

    RegisterClass(&wc);
    hWnd = CreateWindow(wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPEDWINDOW, 100, 100, 501, 500, nullptr, nullptr, wc.hInstance, nullptr);
    HMENU Menu = CreateMenu();

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}
