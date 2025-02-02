#include "CCollider.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"
//コンストラクタ
//CCollider(親,位置,回転,拡縮,半径)
CCollider::CCollider(CCharacter * parent, CMatrix *matrix,
	CVector position, float radius)
	: CCollider()
{
	//親設定
	mpParent = parent;
	//親行列
	mpMatrix = matrix;
	//CTrasform設定
	mPosition = position; //位置
	//半径設定
	mRadius = radius;
	
	//コリジョンリストに追加
	//削除CCollisionManager::Get()->Add(this);
}

//描画
void CCollider::Render(){
	glPushMatrix();
	//コライダの中心座標を計算
	//自分の座標*親の変換行列を掛ける
	CVector pos = mPosition * *mpMatrix;
	//中心座標へ移動
	glMultMatrixf(CMatrix().Translate(pos.mX, pos.mY, pos.mZ).mM[0]);
	//DIFFUSE赤色設定
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//球描画
	//glutWireSphere(mRadius, 16, 16);
	glPopMatrix();

}
CCollider::~CCollider(){
	//コリジョンリストから削除
	CCollisionManager::Get()->Remove(this);
}

//衝突判定
//Collison(コライダ１,コライダ２)
//retrun:true(衝突している)false(衝突していない)
bool CCollider::Collision(CCollider *m, CCollider *o){
	//各コライダの中心座標を求める
	//原点＊コライダの変換行列＊親の変換行列
	CVector mpos = m->mPosition * *m->mpMatrix;
	CVector opos = o->mPosition *  *o->mpMatrix;
	//中心から中心へのベクトルを求める
	mpos = mpos - opos;
	//中心の距離が半径の合計より小さいと衝突
	if (m->mRadius + o->mRadius > mpos.Length()){
		//衝突している
		return true;
	}
	//衝突していない
	return false;
}
CCollider::CCollider()
: mpParent(0)
, mpMatrix(&mMatrix)
, mType(ESPHERE)
, mTag(EBODY)
{
	//コリジョンマネージャに追加
	CCollisionManager::Get()->Add(this);
}

bool CCollider::CollisionTriangleLine(CCollider *t, CCollider*l, CVector *a){
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	sv = l->mV[0] * *l->mpMatrix;
	ev = l->mV[1] * *l->mpMatrix;
	//面の法線を、外積を正規化して求める
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//三角の頂点から線分始点へのベクトルを求める
	CVector v0sv = sv - v[0];
	//三角の頂点から線分終点へのベクトルを求める
	CVector v0ev = ev - v[0];
	//線分が面と交差しているか内積で確認する
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//プラスは交差していない
	if (dots * dote >= 0.0f){
		//衝突してない（調整不要）
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//線分は面と交差している

	//面と線分の交点を求める
	//交点の計算
	CVector cross = sv + (ev - sv) * (abs(dots) / (abs(dots) + abs(dote)));

	//交点が三角形内なら衝突している
	//頂点1頂点２ベクトルと頂点１交点ベクトルとの外積を求め、
	//法線との内積がマイナスの羅、三角形の外
	if ((v[1] - v[0]).Cross(cross - v[0]).Dot(normal) < 0.0f){
		//衝突してない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//頂点２頂点３ベクトルと頂点２交点ベクトルとの外積を求め、
	//法線との内積がマイナスなら、三角形の外
	if ((v[2] - v[1]).Cross(cross - v[1]).Dot(normal) < 0.0f){
		//衝突してない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//課題３２ 
	//頂点３頂点１ベクトルと頂点３交点ベクトルとの外積を求め、
	//法線との内積がマイナス、三角形の外
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f){
		//衝突してない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//調整池計算（衝突しない位置まで戻す）
	if (dots < 0.0f){
		//始点が裏面
		*a = normal * -dots;
	}
	else{
		//終点が裏面
		*a = normal * -dote;
	}
	return true;
}

bool CCollider::CollisionTrianglesSphere(CCollider *t, CCollider *s, CVector *a)
{
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	//面の法線を、外積を正規化して求める
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//線コライダをワールド座標で作成
	sv = s->mPosition * *s->mpMatrix + normal * s->mRadius;
	ev = s->mPosition * *s->mpMatrix - normal * s->mRadius;
	CColliderLine line(NULL, NULL, sv, ev);
	//三角コライダと線コライダの衝突処理
	return CollisionTriangleLine(t, &line, a);
}