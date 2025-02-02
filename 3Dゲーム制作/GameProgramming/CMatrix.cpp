#include "CMatrix.h"
//標準入出力関数のインクルード
#include <stdio.h>
//円周率M_PIを有効にする
#define _USE_MATH_DEFINES
//数学関数のインクルード
#include <math.h>


//デフォルトコンストラクタ
CMatrix::CMatrix(){
	Identity();
}
                                                                                                                                                                                                                                                                                                                                                     
//単位行列の作成
CMatrix CMatrix::Identity(){
	mM[0][0] = 1.000000;
	mM[0][1] = 0.000000;
	mM[0][2] = 0.000000;
	mM[0][3] = 0.000000;
	mM[1][0] = 0.000000;
	mM[1][1] = 1.000000;
	mM[1][2] = 0.000000;
	mM[1][3] = 0.000000;
	mM[2][0] = 0.000000;
	mM[2][1] = 0.000000;
	mM[2][2] = 1.000000;
	mM[2][3] = 0.000000;
	mM[3][0] = 0.000000;
	mM[3][1] = 0.000000;
	mM[3][2] = 0.000000;
	mM[3][3] = 1.000000; 
	//この行列を返す
	return *this;
}
void CMatrix::Print(){
	printf("%10f%10f%10f%10f\n", mM[0][0], mM[0][1], mM[0][2], mM[0][3]);
	printf("%10f%10f%10f%10f\n", mM[1][0], mM[1][1], mM[1][2], mM[1][3]);
	printf("%10f%10f%10f%10f\n", mM[2][0], mM[2][1], mM[2][2], mM[2][3]);
	printf("%10f%10f%10f%10f\n", mM[3][0], mM[3][1], mM[3][2], mM[3][3]);
}

//拡大縮小行列の作成
//Scale(倍率X, 倍率Y, 倍率Z)
CMatrix CMatrix::Scale(float sx, float sy, float sz){
	Identity();
	mM[0][0] = sx;
	mM[1][1] = sy;
	mM[2][2] = sz;
	//この行列を返す
	return *this;
}
//回転行列(Y軸の作成)
//RotaterY(角度)
CMatrix CMatrix::RotateY(float degree){
	//角度からラジアンを求める
	float rad = degree / 180.0f * M_PI;
	//単位行列にする
	Identity();
	//Y軸で回転する行列の設定
	mM[0][0] = mM[2][2] = cosf(rad);
	mM[0][2] = -sinf(rad);
	mM[2][0] = -mM[0][2];
	//行列を返す
	return *this;
}
	//回転行列(Z軸の作成)
	//RotaterZ(角度)
CMatrix CMatrix::RotateZ(float degree){
	//角度からラジアンを求める
	float rad = degree / 180.0f * M_PI;
	//単位行列にする
	Identity();
	//Y軸で回転する行列の設定
	mM[0][0] = mM[1][1] = cosf(rad);
	mM[0][1] = -sinf(rad);
	mM[1][0] = -mM[0][1];
	//行列を返す
	return *this;
}
        //回転行列(X軸の作成)
		//RotaterX(角度)
		CMatrix CMatrix::RotateX(float degree){
			//角度からラジアンを求める
			float rad = degree / 180.0f * M_PI;
			//単位行列にする
			Identity();
			//Y軸で回転する行列の設定
			mM[1][1] = mM[2][2] = cosf(rad);
			mM[2][1] = -sinf(rad);
			mM[1][2] = -mM[2][1];
			//行列を返す
			return *this;
}

		//移動行列の作成
		//Translate(移動量X, 移動量Y, 移動量Z)
		CMatrix CMatrix::Translate(float mx, float my, float mz)
		{
			Identity();
			mM[3][0] = mx;
			mM[3][1] = my;
			mM[3][2] = mz;
			//この行列を返す
			return *this;
		}
		//*演算子のオーバーロード
		//CMatrix * CMatrix の演算結果を返す
		CMatrix CMatrix::operator*(const CMatrix &m){
			CMatrix t;
			t.mM[0][0] = mM[0][0] * m.mM[0][0] + mM[0][1] * m.mM[1][0] + mM[0][2] * m.mM[2][0] + mM[0][3] * m.mM[3][0];
			t.mM[0][1] = mM[0][0] * m.mM[0][1] + mM[0][1] * m.mM[1][1] + mM[0][2] * m.mM[2][1] + mM[0][3] * m.mM[3][1];
			t.mM[0][2] = mM[0][0] * m.mM[0][2] + mM[0][1] * m.mM[1][2] + mM[0][2] * m.mM[2][2] + mM[0][3] * m.mM[3][2];
			t.mM[0][3] = mM[0][0] * m.mM[0][3] + mM[0][1] * m.mM[1][3] + mM[0][2] * m.mM[2][3] + mM[0][3] * m.mM[3][3];

			t.mM[1][0] = mM[1][0] * m.mM[0][0] + mM[1][1] * m.mM[1][0] + mM[1][2] * m.mM[2][0] + mM[1][3] * m.mM[3][0];
			t.mM[1][1] = mM[1][0] * m.mM[0][1] + mM[1][1] * m.mM[1][1] + mM[1][2] * m.mM[2][1] + mM[1][3] * m.mM[3][1];
			t.mM[1][2] = mM[1][0] * m.mM[0][2] + mM[1][1] * m.mM[1][2] + mM[1][2] * m.mM[2][2] + mM[1][3] * m.mM[3][2];
			t.mM[1][3] = mM[1][0] * m.mM[0][3] + mM[1][1] * m.mM[1][3] + mM[1][2] * m.mM[2][3] + mM[1][3] * m.mM[3][3];

			t.mM[2][0] = mM[2][0] * m.mM[0][0] + mM[2][1] * m.mM[1][0] + mM[2][2] * m.mM[2][0] + mM[2][3] * m.mM[3][0];
			t.mM[2][1] = mM[2][0] * m.mM[0][1] + mM[2][1] * m.mM[1][1] + mM[2][2] * m.mM[2][1] + mM[2][3] * m.mM[3][1];
			t.mM[2][2] = mM[2][0] * m.mM[0][2] + mM[2][1] * m.mM[1][2] + mM[2][2] * m.mM[2][2] + mM[2][3] * m.mM[3][2];
			t.mM[2][3] = mM[2][0] * m.mM[0][3] + mM[2][1] * m.mM[1][3] + mM[2][2] * m.mM[2][3] + mM[2][3] * m.mM[3][3];

			t.mM[3][0] = mM[3][0] * m.mM[0][0] + mM[3][1] * m.mM[1][0] + mM[3][2] * m.mM[2][0] + mM[3][3] * m.mM[3][0];
			t.mM[3][1] = mM[3][0] * m.mM[0][1] + mM[3][1] * m.mM[1][1] + mM[3][2] * m.mM[2][1] + mM[3][3] * m.mM[3][1];
			t.mM[3][2] = mM[3][0] * m.mM[0][2] + mM[3][1] * m.mM[1][2] + mM[3][2] * m.mM[2][2] + mM[3][3] * m.mM[3][2];
			t.mM[3][3] = mM[3][0] * m.mM[0][3] + mM[3][1] * m.mM[1][3] + mM[3][2] * m.mM[2][3] + mM[3][3] * m.mM[3][3];
			return t;
		}