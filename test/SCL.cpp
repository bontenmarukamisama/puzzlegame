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
	//ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

int Mouse;


//GetMousePoint(&mouseX, &mouseY);//�}�E�X�J�[�\���̈ʒu���擾

typedef enum {
	eScene_Menu,    //���j���[���
	eScene_Game,    //�Q�[�����
	eScene_Config,  //�ݒ���
	eScene_GameClear, //�Q�[���N���A���
} eScene;

static int Scene = eScene_Menu;    //���݂̉��(�V�[��)

//�V�[�����X�V����
void UpdateScene() {
	Mouse = GetMouseInput();
	DrawString(0, 20, "���N���b�N�ŃQ�[����ʁA�E�N���b�N�ŏI���A", GetColor(255, 255, 255));
	if (Mouse & MOUSE_INPUT_LEFT) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		if (mouseX >= STARTx && mouseX < (STARTx + STARTw) && mouseY >= STARTy && mouseY < (STARTy + STARTh)) {
			int mouseX, mouseY;
			Scene = eScene_Game;
		}
	}
	if (Mouse & MOUSE_INPUT_RIGHT) {
		DxLib_End(); // DX���C�u�����I������
	}
}

//���j���[���
void Menu() {
	DrawString(0, 0, "�P�T�p�Y���i���j", GetColor(255, 255, 255));
	int Start = LoadGraph("�摜/noboru.jpg");
	DrawGraph(STARTx, STARTy, Start, TRUE); // �w�i��`��
	Mouse = GetMouseInput();
	DrawString(0, 20, "���N���b�N�ŃQ�[����ʁA�E�N���b�N�ŏI���A", GetColor(255, 255, 255));
	if (Mouse & MOUSE_INPUT_LEFT) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		if (mouseX >= STARTx && mouseX < (STARTx + STARTw) && mouseY >= STARTy && mouseY < (STARTy + STARTh)) {
			int mouseX, mouseY;
			Scene = eScene_Game;
		}
	}
	if (Mouse & MOUSE_INPUT_RIGHT) {
		DxLib_End(); // DX���C�u�����I������
	}
}

//�Q�[�����
void Game() {
	int CheckHitKey(int KeyCode);
	DrawString(0, 0, "�Q�[����ʂł��B", GetColor(255, 255, 255));


		LoadDivGraph("�摜/neko2.png", 16, 4, 4, WIDTH, HIGHT, image); // �摜�̕����ǂݍ���
		int haikei = LoadGraph("�摜/haikei.png");
		int waku = LoadGraph("�摜/waku2.png");

		DrawGraph(0, 0, haikei, TRUE); // �w�i��`��
		DrawGraph(nx - 10, ny - 10, waku, FALSE); // �w�i��`��

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

//�ݒ���
void Config() {
	DrawString(0, 0, "�ݒ��ʂł��B", GetColor(255, 255, 255));
}
void GameClear() {
	DrawString(0, 0, "�Q�[���N���A�ł��B", GetColor(255, 255, 255));
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	SetWindowSize(800, 800);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		switch (Scene) {//���݂̃V�[���ɂ���������������
		case eScene_Menu://���݂̃V�[�������j���[�Ȃ�
			Menu();//���j���[���
			break;
		case eScene_Game://���݂̃V�[�����Q�[���Ȃ�
			Game();//�Q�[�����
			break;
		case eScene_Config://���݂̃V�[�����ݒ�Ȃ�
			Config();//�ݒ���
			break;
		case eScene_GameClear:
			GameClear();
			break;

		}

		UpdateScene();//�V�[�����X�V����

	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}
