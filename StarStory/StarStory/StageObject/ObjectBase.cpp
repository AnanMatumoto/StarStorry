﻿#include "ObjectBase.h"

//==================================
// オブジェクト基底クラス
//==================================

//----------------------------------
// コンストラクタ
ObjectBase::ObjectBase() {
	pos = { 0,0 };
	rot = 0;
	is_delete = false;
}

//---------------------------------
//　フラグを削除状態にセットする
void ObjectBase::Delete() {
	is_delete = true;
}

//---------------------------------
//　複製処理
Cloneable* ObjectBase::Clone() {
	return this;
}
