#include <Novice.h>
#include "MathFunction.h"

const char kWindowTitle[] = "LE2A_19_マキ_ユキノリ";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);
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

		Quaternion rotation0 = MakeRotateAxisAngleQuaternion(Normalize(Vector3{ 0.71f, 0.71f, 0.0f }), 0.3f);
		Quaternion rotation1 = MakeRotateAxisAngleQuaternion(Normalize(Vector3{ 0.71f, 0.0f, 0.71f }), 3.141592f);

		Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
		Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
		Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
		Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
		Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);

		QuaternionScreenPrintf(0, 0, interpolate0, "interpolate0, Slerp(q0, q1, 0.0f)");
		QuaternionScreenPrintf(0, 15, interpolate1, "interpolate1, Slerp(q0, q1, 0.3f)");
		QuaternionScreenPrintf(0, 30, interpolate2, "interpolate2, Slerp(q0, q1, 0.5f)");
		QuaternionScreenPrintf(0, 45, interpolate3, "interpolate3, Slerp(q0, q1, 0.7f)");
		QuaternionScreenPrintf(0, 60, interpolate4, "interpolate4, Slerp(q0, q1, 1.0f)");
		
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

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
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
