#include "cldl32.h"
__declspec(dllexport) int Link(HWND hWnd,struct TPCLIPINFO *ClipInfo,int Flag,int cnt){

	HGLOBAL hRetMem;
	char *buf,*ret;
	char options[256];
	char buffer[256];


	BYTE KeySt[256];
	char result[256];
	int hSize;

	//�f�[�^�������ꍇ�͏������s��Ȃ��B
	if(ClipInfo == NULL){
		return -1;
	}

	//�e�L�X�g�ȊO�͏������s��Ȃ��B
	if(ClipInfo->Type != CF_TEXT && ClipInfo->Type != CF_OEMTEXT){
		return -1;
	}

	//�������̃T�C�Y���擾����B
	if((hSize = GlobalSize((HGLOBAL)ClipInfo->Mem)) == 0){
		return -1;
	}
	if((buf = GlobalLock((HGLOBAL)ClipInfo->Mem)) == NULL){
		return -1;
	}

	//�߂�p�̃��������m�ۂ���B
	//�Ƃ肠����2�{�̗ʂ��m�ۂ��Ă��܂����A�K�v�ȕ��ō\���܂���B
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
	// �����ŕ�����̏������s���܂��B
	// buf �͏����Ώۂ̕����񂪓������o�b�t�@�ł��B
	// ret �͏�����̃o�b�t�@�ł��B
	// ret �ɏ������{��������������ĉ������B
	// **************************************



	if(NULL!=strstr(buf, "://")||NULL!=strstr(buf, "mailto:")){
		memset(result,'\0',sizeof(result));
		Dlg(result,GetForegroundWindow(),"title=?","Please input title","");

		if(strcmp(result,"\0")==0){
			strcpy(result,buf);
		}


		//�L�[�{�[�h�̉��������擾
		if(GetKeyboardState(KeySt)==FALSE)/*Error*/;
		if(KeySt[VK_SHIFT] & 0x80)//[Shift]�������ꂽ
		  wsprintf(ret,"<a href%c\"%s\" target=\"_blank\">%s</a>",'=',buf,result);
		else
		  wsprintf(ret,"<a href%c\"%s\">%s</a>",'=',buf,result);

	}else{
		memset(result,'\0',sizeof(result));
		Dlg(result,GetForegroundWindow(),"URL=?","Please input URL","");
		/*if(strcmp(result,"\0")==0){
			strcpy(result,"\0");
		}*/

		//�L�[�{�[�h�̉��������擾
		if(GetKeyboardState(KeySt)==FALSE)/*Error*/;
		if(KeySt[VK_SHIFT] & 0x80)//[Shift]�������ꂽ
		  wsprintf(ret,"<a href%c\"%s\" target=\"_blank\">%s</a>",'=',result,buf);
		else
		  wsprintf(ret,"<a href%c\"%s\">%s</a>",'=',result,buf);
	}









	//���������o�b�t�@�̃T�C�Y���擾����B
	hSize = lstrlen(ret) + 1;

	GlobalUnlock(hRetMem);
	//�Ċm�ۂ��s���B
	if((hRetMem = GlobalReAlloc(hRetMem,hSize,0)) == NULL){
		GlobalUnlock((HGLOBAL)ClipInfo->Mem);
		return -1;
	}

	//���̃������͉������B
	GlobalUnlock((HGLOBAL)ClipInfo->Mem);
	GlobalFree(ClipInfo->Mem);

	//�\���̂ɏ����������������̃n���h����ݒ肷��B
	ClipInfo->Mem = hRetMem;

	return 0;
}

//End of source

