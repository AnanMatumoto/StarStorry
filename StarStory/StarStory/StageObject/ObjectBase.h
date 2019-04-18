﻿#pragma once

#include "../Lib/Lib.h"

//================================
// ステージオブジェクトID
//================================

/*
 Todo:　松本
  IDをStageObjectIDから
  ObjectIDに変更する
*/
enum StageObjectID {


	OBJ_TEST1,
	OBJ_CLONE1,
	//---星オブジェクト---
	STAR_OBJ,
	STAR_CHILD1,
	STAR_CHILD2,
	STAR_CHILD3,
	STAR_CHILD4,
	STAR_CHILD5,
	//------UI---------
	//タイトルボタン
	BT_TT_START,		//タイトル画面スタート
	BT_TT_END,		//  　〃　　　終了
	
	//カスタム
	BT_CT_DEC,
	BT_CT_MAP,
	BT_CT_TOSELECT,

	//ゲームボタン
	BT_GM_WIND,
	BT_GM_TOCUSTOM,
	BT_GM_STOP,
	BT_GM_ONOFF,
	
	//リザルト
	BT_RS_SELECT,		//ステージセレクトへ
	BT_RS_CUSUTOM,		//カスタムへ
	
};


//===================================
//　ステージオブジェクト基底クラス
//===================================

class ObjectBase {
	
public:

	ObjectBase(float x, float y, float rotate = 0.f) : m_pos(x, y),m_rot(rotate) {

		m_width = 0;
		m_height = 0;
		is_delete = false;

		memset(m_vtx, 0, sizeof(m_vtx));

	}
	virtual ~ObjectBase() {}

	//　更新処理
	virtual void Update()   = 0;
	//　描画処理
	virtual void Draw  ()   = 0;
	//　頂点情報をセットする
	virtual void SetVertex(DWORD color = 0x00ffffff) {}
	//　削除フラグをセットする
	void Delete();
	//　削除状態かどうかを返す
    const bool IsDelete()const;

public:
	//　X座標ゲッター
	const float GetX()const;
	//　Y座標ゲッター
	const float GetY()const;
	//  回転角度ゲッター
	const float GetRot()const;
	//  幅ゲッター
	const float GetWidth()const;
	//　高さゲッター
	const float GetHeight()const;


protected:

	//　頂点情報ゲッター
	const Vertex* GetVertex()const;
	
	// 　頂点情報ゲッターオーバーロード（指定した頂点情報を取得）
	const Vertex GetVertex(int prim_num)const;

	//　矩形用ローカル座標変換
	void BoxLocalTransform(
		Vertex vtx[4],
		float width,
		float height
	);

	//　菱形用ローカル座標変換
	void DiamondLocalTransform(
		Vertex vtx[4],
		float width,
		float height
	);

	//　オブジェクトの上面を返す
	bool IsHitToSurface(Vec2 point, ObjectBase* obj);

protected:
	Vec2 m_pos;         // 座標
	Vertex m_vtx[4];    // 頂点情報
	float m_width;      // 幅
	float m_height;     // 高さ
	float m_rot;        // 回転角度
	bool  is_delete;    // 削除状態を示すフラグ
};

