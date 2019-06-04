﻿#include "../Common/Common.h"
#include "AnimationParameter.h"
#include <d3d9.h>
#include<d3dx9.h>
#include <dsound.h>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include <mmsystem.h>

#pragma once
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")


#define NOMINMAX


struct Vertex
{
	D3DXVECTOR4 pos;
	DWORD		col;
	D3DXVECTOR2 uv;

};

namespace Lib {

	extern HWND hWnd;
	extern LPDIRECT3D9 d3d;
	extern LPDIRECT3DDEVICE9 dev;

	//================================================
	//　デバイス設定関連
	//================================================

	/*
	使用方法：
	　例）
		Init(WINDOW_W,WINDOW_H,"サンプル");  // 初期化

		while(ProcessMessage()){			 // メッセージループ処理
			DrawBegin(0);					 // 描画処理開始
			DrawEnd();						 // 描画処理終了
		}
		AppEnd();							 // アプリ終了処理
	*/
	LRESULT CALLBACK WinProc(
		HWND hwnd, UINT msg,
		WPARAM wp, LPARAM lp
	);

	void Init(
		int w, int h,
		const char* title
	);
	
	void SetWinDevice(
		HINSTANCE h_instance,
		const char* class_name,
		WNDCLASSEX *wc
	);

	void MakeWindow(
		HINSTANCE h_instance,
		const char* class_name,
		const char* title,
		int w, int h
	);

	void InitD3D9();
	void AppEnd();
	bool ProcessMessage();
	void DrawBegin(DWORD back_color = 0xe0e0ff
	);
	void DrawEnd();

	//================================================
	// テクスチャ読み込み関連
	//================================================
	class Texture {

	public:

		/*
		使用方法：
		　<コンストラクタ>
		  例）
			・Texture tex("画像名");
			・Texture("画像名");
			・Texture tex = "画像名";

		　< LPDIRECTTEXTURE9をテクスチャクラスに代用する場合 >
		  例）
			LPDIRECTTEXTURE9 texture;
			Texutre tex("画像名");
			texture = tex;

		  < サイズ、名前を取得する場合 >
		  例）※リブ内での操作にしか有効ではないので注意
			 float size = tex.GetSize();
			 const char* name = tex.GetName();
		*/

		// コンストラクタ
		Texture() :tex(nullptr), size(0.f, 0.f) {}
		Texture(const char* file_name);
		Texture(const Texture& t);

		Texture& operator=(const Texture& _tex);
		operator LPDIRECT3DTEXTURE9()const {
			return tex;
		};
		const D3DXVECTOR2& GetSize() const {
			return size;
		};
		const std::string& GetName() const {
			return name;
		};
		~Texture();
	private:

		LPDIRECT3DTEXTURE9 tex;
		D3DXVECTOR2 size;
		std::string name;

	};


	class Animation {

	public:

		/*
		< キーの生成 >
		num_key: キーの数
		
		生成後、キーに対応する値（float型）の配列が生成される。
		*/
		void CreateKey(int num_key);
		
		/*
		< キーの値をセットする >
		　index: CrateKeyで生成した配列のインデックス
		  key  : キー
		  value: キーに対応する値
		*/
		void SetKeyValue(
			int index,
			float key,
			float value,
			bool is_loop);

		/*
		<アニメーションの継続時間をセットする>
		　duration: アニメーションの継続時間
		　（timeGetTime関数でセットする）
		*/
		void SetDuration(DWORD duration);
		
		/*
		<スタート時間をセットする>
		start_time:アニメーションの開始時刻
		（timeGetTime関数で取得）
		*/
		void SetStartTime(DWORD start_time);
		
		/*
		<キーの値を取得する>
		time    :現在の時刻
		p_value :値（アドレス）
		p_is_end:終了判定フラグ
		*/
		bool GetValue(DWORD time, float* p_value, bool *p_is_end);


	private:

		float GetFraction(DWORD time);
		int GetBeginIndex(float fraction);
		int    m_num_key;
		float* m_keys;
		float* m_values;
		BOOL  m_is_loop;
		DWORD m_duration;
		DWORD m_start_time;



	};

	//=========================================
	//　キー・マウス処理関連
	//=========================================

	/*
	使用方法：
		例）

		while(true){

		  KeyUpdate();	     // 毎フレームキーの入力情報を確認する

		　 KeyOn('A'); 	     //  「A」キー押下
		   KeyPress('S')      // 「S」キーを押した瞬間
		   KeyOff('VK_SPACE');// スペースキーを離した瞬間
		}
	*/
	void KeyUpdate();
	bool KeyOn(int nVirtKey);
	bool KeyPress(int nVirtKey);
	bool KeyOff(int nVirtKey);
	

	/*
		クリック時のマウス座標を取得し、
		引数にセットする

		第1：X座標
		第2：Y座標
	*/
	Vec2 GetMousePoint();

	/*
		マウスの移動中の座標を取得する
		戻り値　POINT&型

	使用例：
		float x =0. y =0;
		x = Lib::GetPointOnDrag(),xl
		y = Lib::GetPointOnDrag().y;
	*/
	Vec2 GetPointOnDrag();

	/*
		マウスの左ボタンのクリックの判定を返す
	
	使用例：
		bool was_click = Lib::HasOneClickOnMouse();
	*/
	const bool  HasOneClickOnMouse();

	//============================================
	// 2D描画処理
	//============================================

	/*
		ピクセルサイズ描画関数（基本は左上原点）

		第1　：指定するテクスチャ
		第2,3：描画したい座標
		第4,5：幅高を【ピクセルサイズ】で指定する
		第6　：色相
		第7,8：オフセット値(0.5で中心座標)

	仕様方法：
	　Lib::DrawPx(
		"Hoge.png"
		0, 0,
		128, 256,
		0x00ffffff,
		0.5, 0,5
	  );

	*/
	void DrawPx2D(
		const Texture& tex,
		float pos_x,
		float pos_y,
		float width = 1.f,
		float height = 1.f,
		float depth = 0.f,
		DWORD color = 0x00ffffff,
		float ox = 0.f,
		float oy = 0.f
	);

	/*
	
		ピクセルサイズ描画関数
		(※色相指定D3DXCOLOR型)

		第1　：指定するテクスチャ
		第2,3：描画したい座標
		第4,5：幅高を【ピクセルサイズ】で指定する
		第6　：色相
		第7,8：オフセット値(0.5で中心座標)
	*/
	void DrawPx2D(
		const Texture& tex,
		float pos_x, float pos_y,
		D3DXCOLOR color,
		float width = 1.f,
		float height = 1.f,
		float depth = 0.f,
		float ox = 0.f,
		float oy = 0.f
	);

	/*
		画像サイズ描画関数（基本は左上原点）
	

		第1　：指定するテクスチャ
		第2,3：描画したい座標
		第4,5：【倍率】を直接渡す
		第6　：色相
		第7,8：オフセット値(0.5で中心座標)
	*/
	void DrawBox2D(
		const Texture& tex,
		float pos_x,
		float pos_y,
		float width = 1.f,
		float height = 1.f,
		float depth = 0.f,
		DWORD color = 0x00ffffff,
		float ox = 0.f,
		float oy = 0.f
		
	);
	
	/*
		画像サイズ描画関数（基本は左上原点）
		(※色相設定D3DXCOLOR型)

		第1　：指定するテクスチャ
		第2,3：描画したい座標
		第4,5：【倍率】を直接渡す
		第6　：色相
		第7,8：オフセット値(0.5で中心座標)
	*/
	void DrawBox2D(
		const Texture& tex,
		float pos_x, float pos_y,
		D3DXCOLOR color,
		float width = 1.f,
		float height = 1.f,
		float depth = 0.f,
		float ox = 0.f,
		float oy = 0.f
	);

	/*
		頂点座標四角形描画関数

		第1：指定するテクスチャ
		第2：描画する頂点情報
	*/
	void DrawBox2D(
		const Texture& tex,
		Vertex[4]
	);

	/*
		透過効果付板ポリゴン
	
		第1  ：指定するテクスチャ
		第2,3：XY座標
		第4　：色相
		第6,7：幅高
		第8,9：オフセット値
	
	*/
	void DrawBoxAlpha(
		const Texture& tex,
		float pos_x,
		float pos_y,
		D3DXCOLOR color,
		float width = 1.f,
		float height = 1.f,
		float ox = 0.f, float oy = 0.f
	);


	/*
		三角形描画関数（ピクセルサイズ）

		第1：画像名
		第2：頂点情報
		第3：X座標
		第4：Y座標
		第5：幅（デフォルトは128ピクセル）
		第6：高（デフォルトは128ピクセル）
		第7：色相

		◆注意
		第2：引数に頂点を渡すことで描画可能
		（内部で頂点配列は作られない）
		
	*/
	void DrawTriangle2D(
		const Texture& tex,
		Vertex v[],
		float pos_x, float pos_y,
		float width=128, float height=128,
		DWORD color = 0x00ffffff
	);

	/*
		三角形回転描画関数（ピクセルサイズ）

		第1　：指定するテクスチャ
		第2　：回転角度（内部でラジアン変換有り）
		第3.4：自身の座標
		第5.6：幅高（ピクセルサイズで指定）
		第7.8：基準値からの距離（0.5以下で左寄り）
		第9	 ：色相

	◆使用方法：
		Lib::RotTriangle2D(
			"Player.jpg",
			c,
			x, y,
			128,128
			);
	*/
	void RotTriangle2D(
		const Texture& tex,
		float angle,
		float &px, float &py,
		float w, float h,
		float ox=0.5f, float oy=0.5f,
		DWORD color	= 0x00ffffff
	);

	/*
		回転付菱形描画関数

		第1　：指定するテクスチャ
		第2,3：XY座標
		第4,5：中心から頂点角までの長さ（対角線の半分）
		第6  ：回転角度
		第7　：色相
		第8,9：オフセット値（デフォルト中心座標）

		（※オフセット値0.5で中心を軸に回転）
	*/
	void DrawDaiamond2D(
		const Texture& tex,
		float pos_x, float pos_y,
		float h, float w,
		float angle,
		DWORD color = 0x00ffffff,
		float ox = 0.5f, float oy = 0.5f
	);

	void DrawDiamond2D(
		const Texture& tex,
		Vertex vtx_[4]
	);

	/*
		回転付菱形描画関数（複数指定可能）

		第1  ：指定するテクスチャ
		第2,3：XY座標（中心座標）
		第4  ：オブジェクトの最大数
		第5,6：中心から頂点角までの長さ（対角線の半分）
		第7  ：回転角度
		第8　：オフセット値
		第9　：色相
	*/
	void DrawDaiamonds2D(
		const Texture& tex,
		float pos_x[], float pos_y[],
		float obj_num,
		float height, float width,
		float angle,
		DWORD color,
		float ox, float oy
	);

	//αブレンドの設定（※外部での使用はできない）
	void SetAlphaBlend();
	void SetColorBlend();

	/*
	   UVアニメーション関数
	   第1 ：テクスチャ名
	　 第2 ：統合画像の長さ
	   第3 ：現在の描画番号
	   第4 ：深度
	   第5 :ｘ座標
	   第6 : ｙ座標
	   第7 : 高さ
	   第8 ：幅
	   第9 ：ｘオフセット値（デフォルト（0.f）
	   第10：yオフセット値（デフォルト（0.f）
	   第11：色相
	*/
	void AnimationUV(
		const Texture& tex,
		int   length,
		int   cur_num,
		float depth,
		float pos_x, float pos_y,
		float height, float width,
		float ox=0.f, float oy=0.f,
		DWORD color = 0x00ffffff
	);

	/*
	　　UVアニメーション（オーバーロード）
	  　
	   第1 :アニメーションパラメーター構造体
	   第2 :深度
	*/
	void AnimationUV(
		AnimationParameter& param,
		float depth,
		float width, float height);

	//====================================
	// サウンド関連
	//====================================

	/*
	AudioClip
		waveファイルを管理する
	*/
	class AudioClip{

	public:

		static AudioClip& GetInterface(HWND hwnd = nullptr);
		/*
		コンストラクタ
		　
		 wavファイルの書き出しを行い、リストに登録する。

		使用方法：
			AudioClip("hoge.wave");
		*/
		IDirectSoundBuffer8* LoadWaveFile(std::string file_name);

		/*
		GetResource:
			リソースを取得する
		
		使用方法：
			GetResource("hoge.wave");
		*/
		IDirectSoundBuffer8* GetResourcre(std::string name);

	private:

		AudioClip(HWND hwnd);
		AudioClip(const AudioClip&) = delete;

		//デストラクタ
		~AudioClip();
		
	private:
		
		IDirectSound8* m_ds8;
		IDirectSoundBuffer* m_prim_buf;
		std::unordered_map<std::string, IDirectSoundBuffer8*> m_list;

	};

	class AudioPlayer {

	public:
		AudioPlayer(){}

		// 再生（再生終了後、頭出し設定をして終了する）
		void Play(std::string sound_naem);
		
		// ループ再生
		void LoopOnPlay(std::string sound_name);
		
		// 停止
		void Stop();

		// ボリューム設定
		void SetVolume(int volume);

		~AudioPlayer();
	


	private:
		IDirectSoundBuffer8* m_sec_buf; //セカンダリバッファ
		WAVEFORMATEX m_format;
		DWORD m_size;


	};


	//=============================
	//　色の設定
	//=============================

	/*
		色相の変化を作るための色作成関数
	
		（※各引数0.f～1.fまでの数値を指定すること）
	*/
	D3DXCOLOR CreateColor(
		float red,
		float green,
		float blue,
		float alpha);
};

