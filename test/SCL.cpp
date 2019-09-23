#include "DxLib.h"
#include "Header.h"
#define PI 3.141592654
#define WIDTH 120
#define HIGHT 90
#define STARTx 100
#define STARTy 350
#define STARTw 200
#define STARTh 86
POINT MousePoint;

//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

int Mouse;


//GetMousePoint(&mouseX, &mouseY);//マウスカーソルの位置を取得

typedef enum {
	eScene_Menu,    //メニュー画面
	eScene_Game,    //ゲーム画面
	eScene_Config,  //設定画面
	eScene_GameClear, //ゲームクリア画面
} eScene;

static int Scene = eScene_Menu;    //現在の画面(シーン)

//シーンを更新する
void UpdateScene() {
	Mouse = GetMouseInput();
	DrawString(0, 20, "左クリックでゲーム画面、右クリックで終了、", GetColor(255, 255, 255));
	if (Mouse & MOUSE_INPUT_LEFT) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		if (mouseX >= STARTx && mouseX < (STARTx + STARTw) && mouseY >= STARTy && mouseY < (STARTy + STARTh)) {
			int mouseX, mouseY;
			Scene = eScene_Game;
		}
	}
	if (Mouse & MOUSE_INPUT_RIGHT) {
		DxLib_End(); // DXライブラリ終了処理
	}
}

//メニュー画面
void Menu() {
	DrawString(0, 0, "１５パズル（仮）", GetColor(255, 255, 255));
	int Start = LoadGraph("画像/noboru.jpg");
	DrawGraph(STARTx, STARTy, Start, TRUE); // 背景を描画
	Mouse = GetMouseInput();
	DrawString(0, 20, "左クリックでゲーム画面、右クリックで終了、", GetColor(255, 255, 255));
	if (Mouse & MOUSE_INPUT_LEFT) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		if (mouseX >= STARTx && mouseX < (STARTx + STARTw) && mouseY >= STARTy && mouseY < (STARTy + STARTh)) {
			int mouseX, mouseY;
			Scene = eScene_Game;
		}
	}
	if (Mouse & MOUSE_INPUT_RIGHT) {
		DxLib_End(); // DXライブラリ終了処理
	}
}

//ゲーム画面
void Game() {
	int CheckHitKey(int KeyCode);
	DrawString(0, 0, "ゲーム画面です。", GetColor(255, 255, 255));


		LoadDivGraph("画像/neko2.png", 16, 4, 4, WIDTH, HIGHT, image); // 画像の分割読み込み
		int haikei = LoadGraph("画像/haikei.png");
		int waku = LoadGraph("画像/waku2.png");

		DrawGraph(0, 0, haikei, TRUE); // 背景を描画
		DrawGraph(nx - 10, ny - 10, waku, FALSE); // 背景を描画

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				DrawGraph(nx + (j * WIDTH), ny + (i * HIGHT), image[(i*4)+j], TRUE);
			}
		}
		while (1) {
			ProcessMessage();
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				Scene = eScene_Config;
				break;
			}
		}
}

//設定画面
void Config() {
	DrawString(0, 0, "設定画面です。", GetColor(255, 255, 255));
}
void GameClear() {
	DrawString(0, 0, "ゲームクリアです。", GetColor(255, 255, 255));
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	SetWindowSize(800, 800);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		switch (Scene) {//現在のシーンにあった処理をする
		case eScene_Menu://現在のシーンがメニューなら
			Menu();//メニュー画面
			break;
		case eScene_Game://現在のシーンがゲームなら
			Game();//ゲーム画面
			break;
		case eScene_Config://現在のシーンが設定なら
			Config();//設定画面
			break;
		case eScene_GameClear:
			GameClear();
			break;

		}

		UpdateScene();//シーンを更新する

	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}
