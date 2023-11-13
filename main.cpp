#include <Novice.h>
#include "MathFunction.h"

const char kWindowTitle[] = "LE2A_19_マキ_ユキノリ";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* name);
void QuaternionScreenPrintf(int x, int y, const Quaternion& q, const char* name);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Quaternion q1 = { 2.0f, 3.0f, 4.0f, 1.0f };
		Quaternion q2 = { 1.0f, 3.0f, 5.0f, 2.0f };
		Quaternion identity = IndentityQuaternion();
		Quaternion conj = Conjugate(q1);
		Quaternion inv = Inverse(q1);
		Quaternion normal = Normalize(q1);
		Quaternion mul1 = Multiply(q1, q2);
		Quaternion mul2 = Multiply(q2, q1);
		float norm = Norm(q1);

		QuaternionScreenPrintf(0, 0, identity, "Identity");
		QuaternionScreenPrintf(0, 15, conj, "Conjugate");
		QuaternionScreenPrintf(0, 30, inv, "Inverse");
		QuaternionScreenPrintf(0, 45, normal, "Normalize");
		QuaternionScreenPrintf(0, 60, mul1, "Multiply(q1, q2)");
		QuaternionScreenPrintf(0, 75, mul2, "Multiply(q2, q1)");
		Novice::ScreenPrintf(0,90, "%6.02f  : Norm", norm);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* name) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x, y, "%s", name);
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + 20, "%6.03f", matrix.m[row][column]);
		}
	}
}

void QuaternionScreenPrintf(int x, int y, const Quaternion& q, const char* name)
{
	Novice::ScreenPrintf(x, y, "%6.02f %6.02f %6.02f %6.02f  : %s" , q.x, q.y, q.z, q.w, name);

}
