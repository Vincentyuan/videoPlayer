#pragma once

#define WM_MYMESSAGE2 (WM_USER+3)
#define WM_MYMESSAGE1 (WM_USER+2)
// m_close �Ի���

class m_close : public CDialog
{
	DECLARE_DYNAMIC(m_close)

public:
	m_close(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~m_close();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


	DECLARE_MESSAGE_MAP()
};
