
#include "cldl32.h"

char* cPrompt;
char* cTitle;
char* cDefault;
char* cResult;

/////////////////////////////////////////////////////////////////////////////
//  IME��ON�^OFF����
//  hWnd�F�ړI�̃E�B���h�E�n���h��
//  bOn�FTRUE�cON�^FALSE�cOFF

void  ImeOn( HWND hWnd, BOOL bOn ){
  //  �n���h�����擾����
  HIMC hIMC = ImmGetContext( hWnd );

  //  IME��ON�^OFF
  ImmSetOpenStatus( hIMC, bOn );

  //  �擾�����n���h�����J������
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
		MessageBox(NULL, "�_�C�A���O���s", "OK", MB_OK);
		return FALSE;
	}
	return TRUE;
}




//DLL��main
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






//�c�[�����̎擾
//		Cnt - �Ăяo���J�E���g
//		Title - �^�C�g�����i�[����o�b�t�@
//		Func - �֐������i�[����o�b�t�@
//		lParam - �֐��ɓn�����l
//
//		�߂�l
//			�Ăяo���t���O
//			�S�Ă̊֐���񋓂��I������ꍇ�́ARET_LOOPEND ��Ԃ��B
//
__declspec(dllexport) int GetToolInfo(int Cnt,char *Title,char *Func,long *lParam){
  int ret = RET_LOOPEND;

  switch(Cnt)
    {
    case 0:					// 0 �Ԗڂ̌Ăяo��
      // **************************************
      lstrcpy(Title,"Font");		//�^�C�g���̐ݒ�
      lstrcpy(Func,"Font");			//�֐����̐ݒ�
      //*lParam = 0;									//�֐��ɓn�����l�̐ݒ�

      ret = RET_MENUONLY;								//�߂�l�i�Ăяo���t���O�j
      // **************************************
      break;
    case 1:
      // **************************************
      lstrcpy(Title,"Comment");		//�^�C�g���̐ݒ�
      lstrcpy(Func,"Comment");			//�֐����̐ݒ�
      //*lParam = 0;									//�֐��ɓn�����l�̐ݒ�

      ret = RET_MENUONLY;								//�߂�l�i�Ăяo���t���O�j
      // **************************************
      break;
    case 2:
      // **************************************
      lstrcpy(Title,"Link");		//�^�C�g���̐ݒ�
      lstrcpy(Func,"Link");			//�֐����̐ݒ�
      //*lParam = 0;									//�֐��ɓn�����l�̐ݒ�

      ret = RET_MENUONLY;								//�߂�l�i�Ăяo���t���O�j
      // **************************************
      break;
    case 3:
      // **************************************
      lstrcpy(Title,"_obj");		//�^�C�g���̐ݒ�
      lstrcpy(Func,"_obj");			//�֐����̐ݒ�
      //*lParam = 0;									//�֐��ɓn�����l�̐ݒ�

      ret = RET_MENUONLY;								//�߂�l�i�Ăяo���t���O�j
      // **************************************
      break;
    case 4:
      // **************************************
      lstrcpy(Title,"bmp2xpm");		//�^�C�g���̐ݒ�
      lstrcpy(Func,"bmp2xpm");			//�֐����̐ݒ�
      //*lParam = 0;									//�֐��ɓn�����l�̐ݒ�

      ret = RET_MENUONLY;								//�߂�l�i�Ăяo���t���O�j
      // **************************************
      break;
    case 5:
      // **************************************
      lstrcpy(Title,"DEFINE_VARIABLE");		//�^�C�g���̐ݒ�
      lstrcpy(Func,"DEFINE_VARIABLE");			//�֐����̐ݒ�
      //*lParam = 0;									//�֐��ɓn�����l�̐ݒ�

      ret = RET_MENUONLY;								//�߂�l�i�Ăяo���t���O�j
      // **************************************
      break;
    case 6:
      // **************************************
      lstrcpy(Title,"GTK_OBJECT");		//�^�C�g���̐ݒ�
      lstrcpy(Func,"GTK_OBJECT");			//�֐����̐ݒ�
      //*lParam = 0;									//�֐��ɓn�����l�̐ݒ�

      ret = RET_MENUONLY;								//�߂�l�i�Ăяo���t���O�j
      // **************************************
      break;
    }
  return ret;
}

//�c�[��
//		hWnd - �Ăяo�����̃E�B���h�E�n���h��
//		ClipInfo - �����̏��
//		Flag - �Ăяo���̃t���O�̑g�ݍ��킹
//				0 - ���j���[����̌Ăяo��
//				1 - �����ɒǉ����ꂽ�Ƃ��̌Ăяo��
//				2 - �N���b�v�{�[�h�ɑ���Ƃ��̌Ăяo��
//				4 - �������̌Ăяo���iClipInfo �� NULL �ł��j
//				8 - �z�b�g�L�[����̌Ăяo�� �i2 �������I�ɑg�ݍ��킳��܂��j
//				16 - �N�����̌Ăяo�� �i4 �������I�ɑg�ݍ��킳��܂��j
//				32 - �I�����̌Ăяo�� �i4 �������I�ɑg�ݍ��킳��܂��j
//		cnt - �����A�C�e�����̌Ăяo����
//				�`���P�̂ł̌Ăяo���̏ꍇ�́A0 �̂�
//
//		�߂�l
//				0�ȏ�	- ����
//				-1		- ���s
//
// **************************************
// func�Ƃ����͓̂K���ɕύX���Ă��������B
// **************************************

