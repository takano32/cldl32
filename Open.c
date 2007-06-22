#include "cldl32.h"
__declspec(dllexport) int Open(HWND hWnd,struct TPCLIPINFO *ClipInfo,int Flag,int cnt)
{
	
	HGLOBAL hRetMem;
	char *buf,*ret;
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
	if((hRetMem = GlobalAlloc(GHND,hSize*2 +16)) == NULL){
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
	
	// sprintf(ret,"%s<%%=fn '%s�F'%%>",buf,buf);
	ShellExecute(NULL, "open", buf, NULL, NULL, SW_SHOWNORMAL);
	
	
	
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
