
//string.c
//
//		CLCL�p�A�h�C���c�[���̕����񏈗��p�e���v���[�g
//
//	************************************** �ň͂܂ꂽ������ύX���邾���ł����ł��B
//

#define _DEBUG
#define _INC_OLE
#include <windows.h>
#undef  _INC_OLE
#include <imm.h>
#include <string.h>




//-----------------------------------------------------------------
//CLCLTool�p�̐錾

#define RET_LOOPEND		-1	//�c�[�����̎擾�I��
#define RET_MENUONLY	0	//���j���[����̌Ăяo���̂�
#define RET_HISTORY		1	//�����ɒǉ����ɌĂяo��
#define RET_CLIP		2	//�N���b�v�{�[�h�ɑ���Ƃ��ɌĂяo��
#define RET_NOITEM		4	//�������Ăяo���A�i�f�[�^�͓n����Ȃ��j
#define RET_TOOLMENU	8	//�z�b�g�L�[����̌Ăяo���A�ݒ�̏ꍇ�̓z�b�g�L�[����̌Ăяo���𖳌��ɂ���
#define RET_START		16	//�N�����̌Ăяo��
#define RET_END			32	//�I�����̌Ăяo��

#define BUF_SIZE		256	//�o�b�t�@�T�C�Y


#define IDC_STATIC		3000
#define IDC_EDIT                        1000
#define IDC_LABEL 2000

struct TPCLIPINFO{
  unsigned int Type;		//�f�[�^�̃^�C�v�i�o�^����Ă�����̂̂݁j
  char name[BUF_SIZE];	//�f�[�^�̃^�C�v��
  HANDLE Mem;				//�f�[�^
  long Size;				//�T�C�Y
  long lParam;			//�o�^���ɐݒ肳�ꂽ�l
  int Flag;				//�c�[�����ŗ��p�ł���t���O�A�r�b�g�t���O�̎g�p�������B
};
//-----------------------------------------------------------------


#ifndef __CLCL_GUI_H__


LRESULT CALLBACK InputDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Dlg(char* cResult,HWND hWnd,char* cPrompt,char* cTitle,char* cDefault);
HINSTANCE hInstance;

#define __CLCL_GUI_H__
#endif


