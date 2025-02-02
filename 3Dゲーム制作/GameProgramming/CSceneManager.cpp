#include "CSceneManager.h"
#include "CSceneGame.h"
#include "CSceneDeath.h"

//コンストラクタ
CSceneManager::CSceneManager()
: mpScene(0)
{}
//デストラクタ（削除されるときに実行されます）
CSceneManager::~CSceneManager() {
	//シーンがあれば削除
	if (mpScene)
		//シーンの削除
		delete mpScene;
	mpScene = 0;
}
//初期化処理
void CSceneManager::Init() {
	//シーンの識別を設定する
	mScene = CScene::EGAME;
	//シーンを生成し、ポインタを設定する
	mpScene = new CSceneGame();
	//生成したクラスのメソッドが呼ばれる
	mpScene->Init();
}
//更新処理
void CSceneManager::Update() {
	//ポインタのUpdateを呼ぶ
	mpScene->Update();
	//次のシーンを取得し異なるか判定
	if (mScene != mpScene->GetNextScene()) {
		mScene = mpScene->GetNextScene();
		delete mpScene;//今のシーン削除
		//該当するシーンを生成
		switch (mScene) {
		case CScene::EGAME:
			mpScene = new CSceneGame();
			mpScene->Init();
			break;
		case CScene::EDEATH:
			mpScene = new CSceneDeath();
			mpScene->Init();
			break;
		}
	}
}
