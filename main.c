
#include "cldl32.h"

char* cPrompt;
char* cTitle;
char* cDefault;
char* cResult;

/////////////////////////////////////////////////////////////////////////////
//  IMEをON／OFFする
//  hWnd：目的のウィンドウハンドル
//  bOn：TRUE…ON／FALSE…OFF

void  ImeOn( HWND hWnd, BOOL bOn ){
  //  ハンドルを取得する
  HIMC hIMC = ImmGetContext( hWnd );

  //  IMEのON／OFF
  ImmSetOpenStatus( hIMC, bOn );

  //  取得したハンドルを開放する
  ImmReleaseContext( hWnd, hIMC );
}


LRESULT CALLBACK InputDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp){
  char buffer[1024];
  switch (msg) {
  case WM_INITDIALOG:
    SetWindowText(hDlg,cTitle);
    SetWindowText(GetDlgItem(hDlg, IDC_LABEL),cPrompt);

    ImeOn(hDlg,FALSE);
    SetWindowPos(hDlg,0,0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
    SetFocus(hDlg);
    SetWindowText(GetDlgItem(hDlg, IDC_EDIT),cDefault);
    SetFocus(GetDlgItem(hDlg, IDC_EDIT));

    
    return FALSE;
  case WM_COMMAND:
    switch (LOWORD(wp)) {
    case IDOK:
      //strcpy(cResult,);
      GetDlgItemText( hDlg, IDC_EDIT, buffer,sizeof(buffer) );
      strcpy(cResult,buffer);
      EndDialog(hDlg, IDOK);
      break;
    case IDCANCEL:
      EndDialog(hDlg, IDCANCEL);
      break;
    default:
      return FALSE;
    }
  default:
    return FALSE;
  }
  return TRUE;
}

BOOL CALLBACK Dlg(char* _Result,HWND hWnd,char* _Prompt,char* _Title,char* _Default){
	cResult=_Result;cPrompt=_Prompt;cTitle=_Title;cDefault=_Default;
	if(_Prompt==NULL)
	  cPrompt="Please input";
	if(_Title==NULL)
	  cTitle="Input Dialog";
	if(_Default==NULL)
	  cDefault="";

	if(DialogBoxParam(hInstance, "INPUTDLG", hWnd,
				 (DLGPROC)InputDlgProc,0) == FALSE) {
		MessageBox(NULL, "ダイアログ失敗", "OK", MB_OK);
		return FALSE;
	}
	return TRUE;
}




//DLLのmain
int WINAPI DllMain(HINSTANCE hInst, DWORD fdwReason, PVOID pvReserved){

  switch (fdwReason) {
  case DLL_PROCESS_ATTACH:
    hInstance = (HINSTANCE)hInst;
    break;
  case DLL_PROCESS_DETACH:
    break;
  default:
    break;
  }

  return TRUE;
}






//ツール情報の取得
//		Cnt - 呼び出しカウント
//		Title - タイトルを格納するバッファ
//		Func - 関数名を格納するバッファ
//		lParam - 関数に渡す数値
//
//		戻り値
//			呼び出しフラグ
//			全ての関数を列挙し終わった場合は、RET_LOOPEND を返す。
//
__declspec(dllexport) int GetToolInfo(int Cnt,char *Title,char *Func,long *lParam){
  int ret = RET_LOOPEND;

  switch(Cnt)
    {
    case 0:					// 0 番目の呼び出し
      // **************************************
      lstrcpy(Title,"Font");		//タイトルの設定
      lstrcpy(Func,"Font");			//関数名の設定
      //*lParam = 0;									//関数に渡す数値の設定

      ret = RET_MENUONLY;								//戻り値（呼び出しフラグ）
      // **************************************
      break;
    case 1:
      // **************************************
      lstrcpy(Title,"Comment");		//タイトルの設定
      lstrcpy(Func,"Comment");			//関数名の設定
      //*lParam = 0;									//関数に渡す数値の設定

      ret = RET_MENUONLY;								//戻り値（呼び出しフラグ）
      // **************************************
      break;
    case 2:
      // **************************************
      lstrcpy(Title,"Link");		//タイトルの設定
      lstrcpy(Func,"Link");			//関数名の設定
      //*lParam = 0;									//関数に渡す数値の設定

      ret = RET_MENUONLY;								//戻り値（呼び出しフラグ）
      // **************************************
      break;
    case 3:
      // **************************************
      lstrcpy(Title,"_obj");		//タイトルの設定
      lstrcpy(Func,"_obj");			//関数名の設定
      //*lParam = 0;									//関数に渡す数値の設定

      ret = RET_MENUONLY;								//戻り値（呼び出しフラグ）
      // **************************************
      break;
    case 4:
      // **************************************
      lstrcpy(Title,"bmp2xpm");		//タイトルの設定
      lstrcpy(Func,"bmp2xpm");			//関数名の設定
      //*lParam = 0;									//関数に渡す数値の設定

      ret = RET_MENUONLY;								//戻り値（呼び出しフラグ）
      // **************************************
      break;
    case 5:
      // **************************************
      lstrcpy(Title,"DEFINE_VARIABLE");		//タイトルの設定
      lstrcpy(Func,"DEFINE_VARIABLE");			//関数名の設定
      //*lParam = 0;									//関数に渡す数値の設定

      ret = RET_MENUONLY;								//戻り値（呼び出しフラグ）
      // **************************************
      break;
    case 6:
      // **************************************
      lstrcpy(Title,"GTK_OBJECT");		//タイトルの設定
      lstrcpy(Func,"GTK_OBJECT");			//関数名の設定
      //*lParam = 0;									//関数に渡す数値の設定

      ret = RET_MENUONLY;								//戻り値（呼び出しフラグ）
      // **************************************
      break;
    }
  return ret;
}

//ツール
//		hWnd - 呼び出し元のウィンドウハンドル
//		ClipInfo - 履歴の情報
//		Flag - 呼び出しのフラグの組み合わせ
//				0 - メニューからの呼び出し
//				1 - 履歴に追加されたときの呼び出し
//				2 - クリップボードに送るときの呼び出し
//				4 - 無条件の呼び出し（ClipInfo は NULL です）
//				8 - ホットキーからの呼び出し （2 が自動的に組み合わされます）
//				16 - 起動時の呼び出し （4 が自動的に組み合わされます）
//				32 - 終了時の呼び出し （4 が自動的に組み合わされます）
//		cnt - 履歴アイテム時の呼び出し回数
//				形式単体での呼び出しの場合は、0 のみ
//
//		戻り値
//				0以上	- 成功
//				-1		- 失敗
//
// **************************************
// funcというのは適当に変更してください。
// **************************************

