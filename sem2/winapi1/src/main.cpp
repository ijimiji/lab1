#define A 3
#define B 7
#define DELTA 0.01
#define INTERVAL 1
#define FG_COLOR 0x000000
#define BG_COLOR 0xFFFFFF

#include <windows.h>
#include <map>
#include <string>
#include <cmath>
template <typename T>
struct Point
{
    T x;
    T y;
    Point(T X, T Y)
    {
        x = X;
        y = Y;
    }
};

std::map<int, int> TimerMap;
int Timer1Id = 1;

double t = 0.0;

Point<int> GetPoint(double t, int width, int height)
{
    double r = std::sin(A * t / B);
    double x_math = r * std::cos(t);
    double y_math = r * std::sin(t);
    double scale = min(width, height) / 4;
    int x = width / 2 + x_math * scale;
    int y = height / 2 - y_math * scale;
    return Point<int>(x, y);
}
COLORREF FromHex(int hex)
{
    auto r = (hex & 0xFF0000) >> 16;
    auto g = (hex & 0x00FF00) >> 8;
    auto b = (hex & 0x0000FF) >> 0;
    return RGB(r, g, b);
}

void SelectObjectAndDeletePrevious(HDC hDeviceContext, HGDIOBJ gdiObject)
{
    auto previousGdiObject = SelectObject(hDeviceContext, gdiObject);
    DeleteObject(previousGdiObject);
}

void DrawCircle(HDC hdc, long width, long height, Point<int> point, COLORREF color){
    auto Brush = CreateSolidBrush(color);
    auto Pen = CreatePen(PS_SOLID, 1, color);
    int radius = min(width, height) / 40;
    SelectObject(hdc, Brush);
    SelectObject(hdc, Pen);
    Ellipse(hdc, point.x - radius, point.y - radius, point.x + radius, point.y + radius);
    DeleteObject(Brush);
    DeleteObject(Pen);
}
void DrawPoint(HDC hdc, long width, long height, Point<int> point)
{
    auto defaultPen = SelectObject(hdc, CreatePen(PS_DASHDOTDOT, 2, FromHex(0x317897)));
    LineTo(hdc, point.x, point.y);
    SelectObjectAndDeletePrevious(hdc, defaultPen);
}

HFONT CreateFont(std::string name, int size, int weight)
{
    auto lf = LOGFONT{};
    strcpy_s(lf.lfFaceName, name.data());
    lf.lfHeight = size;
    lf.lfWeight = weight;
    lf.lfCharSet = DEFAULT_CHARSET;
    return CreateFontIndirect(&lf);
}

RECT GetClientRect(HWND hWnd)
{
    RECT rect;
    ::GetClientRect(hWnd, &rect);
    return rect;
}

void DrawLines(HDC hdc, long width, long height)
{
    auto defaultPen = SelectObject(hdc, CreatePen(PS_DASHDOTDOT, 1, FromHex(FG_COLOR)));

    MoveToEx(hdc, 0, height / 2, nullptr);
    LineTo(hdc, width, height / 2);

    MoveToEx(hdc, width / 2, 0, nullptr);
    LineTo(hdc, width / 2, height);

    SelectObjectAndDeletePrevious(hdc, defaultPen);
}

void DrawCoords(HDC hdc, long width, long height, long scale, Point<int> CurrentPoint)
{
    auto textRectangle = RECT{0, 0, scale / 2 , height/8};
    auto defaultBrush = CreateSolidBrush(FromHex(BG_COLOR));
    FillRect(hdc, &textRectangle, defaultBrush);
    SelectObjectAndDeletePrevious(hdc, defaultBrush);

    auto defaultFont = SelectObject(hdc, CreateFont("Consolas", scale / 8, FW_BOLD));
    SetTextColor(hdc, FG_COLOR);
    SetBkMode(hdc, TRANSPARENT);

    auto text = std::to_string(CurrentPoint.x) + ", " + std::to_string(CurrentPoint.y);
    DrawText(hdc, text.c_str(), -1, &textRectangle, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    SelectObjectAndDeletePrevious(hdc, defaultFont);
}

LPARAM OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    auto clientRect = GetClientRect(hWnd);
    auto width = clientRect.right - clientRect.left;
    auto height = clientRect.bottom - clientRect.top;
    auto scale = min(width, height);
    if (t > 6.28)
    {
        t = 0.0;
        TimerMap[Timer1Id] = 0;
        auto Brush = CreateSolidBrush(FromHex(BG_COLOR));
        FillRect(hdc, &clientRect, Brush);
        DeleteObject(Brush);
    }

    Point<int> CurrentPoint = GetPoint(t, width, height);
    DrawCircle(hdc, width, height, CurrentPoint, FromHex(BG_COLOR));
    if (t / DELTA >= 30){
        t -= DELTA * 30;
        for (int i = 0; i < 30; i++)
        {
            CurrentPoint = GetPoint(t, width, height);
            MoveToEx(hdc, CurrentPoint.x, CurrentPoint.y, nullptr);
            t += DELTA;
            CurrentPoint = GetPoint(t, width, height);
            DrawPoint(hdc, width, height, CurrentPoint);
        }
    }

    MoveToEx(hdc, CurrentPoint.x, CurrentPoint.y, nullptr);
    t += DELTA;
    CurrentPoint = GetPoint(t, width, height);
    DrawCircle(hdc, width, height, CurrentPoint, FromHex(FG_COLOR));
    DrawCoords(hdc, width, height, scale, CurrentPoint);
    DrawPoint(hdc, width, height, CurrentPoint);
    DrawLines(hdc, width, height);
    return true;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        SetTimer(hWnd, Timer1Id, INTERVAL, nullptr);
        TimerMap[Timer1Id] = 0;
        break;
    }
    case WM_TIMER:
    {
        TimerMap[Timer1Id]++;
        InvalidateRect(hWnd, nullptr, true);
        break;
    }
    case WM_PAINT:
    {
        OnPaint(hWnd, uMsg, wParam, lParam);
        break;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
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
    //wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Polar axis";
    wc.style = CS_VREDRAW | CS_HREDRAW;
    RegisterClass(&wc);
    hWnd = CreateWindow(wc.lpszClassName, "Hello", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}
