// Speak.h: interface for the CSpeak class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPEAK_H__9BFA87CF_FA95_47D9_9739_FBD43581E5F1__INCLUDED_)
#define AFX_SPEAK_H__9BFA87CF_FA95_47D9_9739_FBD43581E5F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <sapi.h>
#include <afxmt.h>
#include <process.h>


class CSpeak  

{
	static	void  _Thread(void *lpParam);
	
public:
	void Skip(int num);

	HWND	postto;

	CSpeak();
	virtual ~CSpeak();

	int		Speak(const char *str);
	void	Stop();

	int	CSpeak::Prop();

protected:

	ISpVoice * pVoice;
	void CleanUp();
	unsigned short  outp[10240];

	// Thread related
	HANDLE  thhevent; int thhend, thhandle;
};

#endif // !defined(AFX_SPEAK_H__9BFA87CF_FA95_47D9_9739_FBD43581E5F1__INCLUDED_)
