
//string.c
//
//		CLCL用アドインツールの文字列処理用テンプレート
//
//	************************************** で囲まれた部分を変更するだけでいいです。
//

#define _DEBUG
#define _INC_OLE
#include <windows.h>
#undef  _INC_OLE
#include <imm.h>
#include <string.h>




//-----------------------------------------------------------------
//CLCLTool用の宣言

#define RET_LOOPEND		-1	//ツール情報の取得終了
#define RET_MENUONLY	0	//メニューからの呼び出しのみ
#define RET_HISTORY		1	//履歴に追加時に呼び出す
#define RET_CLIP		2	//クリップボードに送るときに呼び出す
#define RET_NOITEM		4	//無条件呼び出し、（データは渡されない）
#define RET_TOOLMENU	8	//ホットキーからの呼び出し、設定の場合はホットキーからの呼び出しを無効にする
#define RET_START		16	//起動時の呼び出し
#define RET_END			32	//終了時の呼び出し

#define BUF_SIZE		256	//バッファサイズ


#define IDC_STATIC		3000
#define IDC_EDIT                        1000
#define IDC_LABEL 2000

struct TPCLIPINFO{
  unsigned int Type;		//データのタイプ（登録されているもののみ）
  char name[BUF_SIZE];	//データのタイプ名
  HANDLE Mem;				//データ
  long Size;				//サイズ
  long lParam;			//登録時に設定された値
  int Flag;				//ツール側で利用できるフラグ、ビットフラグの使用が推奨。
};
//-----------------------------------------------------------------


#ifndef __CLCL_GUI_H__


LRESULT CALLBACK InputDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Dlg(char* cResult,HWND hWnd,char* cPrompt,char* cTitle,char* cDefault);
HINSTANCE hInstance;

#define __CLCL_GUI_H__
#endif


