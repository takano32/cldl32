#include "cldl32.h"
__declspec(dllexport) int Link(HWND hWnd,struct TPCLIPINFO *ClipInfo,int Flag,int cnt){

	HGLOBAL hRetMem;
	char *buf,*ret;
	char options[256];
	char buffer[256];


	BYTE KeySt[256];
	char result[256];
	int hSize;

	//データが無い場合は処理を行わない。
	if(ClipInfo == NULL){
		return -1;
	}

	//テキスト以外は処理を行わない。
	if(ClipInfo->Type != CF_TEXT && ClipInfo->Type != CF_OEMTEXT){
		return -1;
	}

	//メモリのサイズを取得する。
	if((hSize = GlobalSize((HGLOBAL)ClipInfo->Mem)) == 0){
		return -1;
	}
	if((buf = GlobalLock((HGLOBAL)ClipInfo->Mem)) == NULL){
		return -1;
	}

	//戻り用のメモリを確保する。
	//とりあえず2倍の量を確保していますが、必要な分で構いません。
	if((hRetMem = GlobalAlloc(GHND,hSize * 2+256)) == NULL){
		GlobalUnlock((HGLOBAL)ClipInfo->Mem);
		return -1;
	}
	if((ret = GlobalLock(hRetMem)) == NULL){
		GlobalUnlock((HGLOBAL)ClipInfo->Mem);
		GlobalFree(hRetMem);
		return -1;
	}




	// **************************************
	// ここで文字列の処理を行います。
	// buf は処理対象の文字列が入ったバッファです。
	// ret は処理後のバッファです。
	// ret に処理を施した文字列を入れて下さい。
	// **************************************



	if(NULL!=strstr(buf, "://")||NULL!=strstr(buf, "mailto:")){
		memset(result,'\0',sizeof(result));
		Dlg(result,GetForegroundWindow(),"title=?","Please input title","");

		if(strcmp(result,"\0")==0){
			strcpy(result,buf);
		}


		//キーボードの押下情報を取得
		if(GetKeyboardState(KeySt)==FALSE)/*Error*/;
		if(KeySt[VK_SHIFT] & 0x80)//[Shift]が押された
		  wsprintf(ret,"<a href%c\"%s\" target=\"_blank\">%s</a>",'=',buf,result);
		else
		  wsprintf(ret,"<a href%c\"%s\">%s</a>",'=',buf,result);

	}else{
		memset(result,'\0',sizeof(result));
		Dlg(result,GetForegroundWindow(),"URL=?","Please input URL","");
		/*if(strcmp(result,"\0")==0){
			strcpy(result,"\0");
		}*/

		//キーボードの押下情報を取得
		if(GetKeyboardState(KeySt)==FALSE)/*Error*/;
		if(KeySt[VK_SHIFT] & 0x80)//[Shift]が押された
		  wsprintf(ret,"<a href%c\"%s\" target=\"_blank\">%s</a>",'=',result,buf);
		else
		  wsprintf(ret,"<a href%c\"%s\">%s</a>",'=',result,buf);
	}









	//処理したバッファのサイズを取得する。
	hSize = lstrlen(ret) + 1;

	GlobalUnlock(hRetMem);
	//再確保を行う。
	if((hRetMem = GlobalReAlloc(hRetMem,hSize,0)) == NULL){
		GlobalUnlock((HGLOBAL)ClipInfo->Mem);
		return -1;
	}

	//元のメモリは解放する。
	GlobalUnlock((HGLOBAL)ClipInfo->Mem);
	GlobalFree(ClipInfo->Mem);

	//構造体に処理をしたメモリのハンドルを設定する。
	ClipInfo->Mem = hRetMem;

	return 0;
}

//End of source

