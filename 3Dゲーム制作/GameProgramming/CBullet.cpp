#include "CBullet.h"

//幅と奥行きの設定
//Set(幅、奥行き)
CBullet::CBullet()
	:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 1.0f)
	, mLife(50)
{}

void CBullet::Set(float w, float d){
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定→3
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0, 0.0));
	//三角形の法線設定
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

//更新
void CBullet::Update(){
	//線損時間の判定
	if (mLife-- > 0){
		CTransform::Update();
		//位置更新
		mPosition = CVector(0.0f, -10.0f, 0.0f) * mMatrix;
	}
	else{
		//無効にする
		mEnabled = false;
	}
}

//描画
void CBullet::Render(){
	//DIFFUSE黄色設定
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//三角形描画→12
	mT.Render(mMatrix);

}

