// ManagedDxlGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include <Windows.h >
#include <chrono>
#pragma comment(lib,"winmm.lib")

#include "framework.h"
#include "ManagedDxlGame.h"
#include "DxLib.h"
#include "program/library/tnl_input.h"
#include "program/game/Main.h"
#include "program/dxlib_ext/dxlib_ext.h"


#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


static std::chrono::system_clock::time_point clock_start, clock_end;
static std::chrono::system_clock::time_point fps_clock_start, fps_clock_end;

extern std::string g_drag_file_path;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // ウィンドウモードで起動
    ChangeWindowMode(true);

    // ウィンドウサイズ設定
    SetGraphMode(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, 32);

    // ＤＸライブラリ初期化処理
    if (DxLib_Init() == -1)
    {
        // エラーが起きたら直ちに終了
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);

    // 計測開始時間
    clock_start = std::chrono::system_clock::now();

    // キー入力制御の初期化
    HWND hWnd = GetMainWindowHandle();
    HDC hdc = GetDC(hWnd);
    tnl::Input::Initialize(hInstance, hWnd, hdc, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

    SetDragFileValidFlag(TRUE);
    SetAlwaysRunFlag(TRUE);

    // ゲームスタート処理
    gameStart();

    // メッセージループ
    while (1)
    {
        // フレーム間の経過時間
        // マイクロ秒で計測して秒に変換
        clock_end = std::chrono::system_clock::now();
        double micro_seconds = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(clock_end - clock_start).count());
        float delta_time = static_cast<float>(micro_seconds / 1000.0 / 1000.0);
        clock_start = clock_end;

        if (ProcessMessage() == -1) {
            break;
        }

        char filepath[256] = { 0 };
        if (0 == GetDragFilePath(filepath)) {
            g_drag_file_path = std::string(filepath);
        }
        DragFileInfoClear();

        fps_clock_start = std::chrono::system_clock::now();

        // 画面をクリア
        ClearDrawScreen();

        // キー状態の更新
        tnl::Input::Update();

        // ゲームメインルーチン
        gameMain(delta_time);

        // バックバッファをフリップ
        ScreenFlip();
        //SetWaitVSyncFlag(FALSE);

        // フレームレートコントロール
        fps_clock_end = std::chrono::system_clock::now();
        double fps_mic = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(fps_clock_end - fps_clock_start).count());
        float fps_mils = static_cast<float>(fps_mic / 1000.0);
        float fps_lim = 1000.0f / DXE_FIX_FPS;

        if (fps_lim > fps_mils) {
            timeBeginPeriod(1);
            Sleep(DWORD(fps_lim - fps_mils));
            timeEndPeriod(1);
        }

    }

    // ゲーム側の終了処理
    gameEnd();

    ReleaseDC(hWnd, hdc);

    // ＤＸライブラリ使用の終了処理
    DxLib_End();

    return 0;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MANAGEDDXLGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MANAGEDDXLGAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
