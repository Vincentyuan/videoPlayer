#pragma once

#define WM_MYMESSAGE2 (WM_USER+3)
#define WM_MYMESSAGE1 (WM_USER+2)
// m_close 对话框

class m_close : public CDialog
{
	DECLARE_DYNAMIC(m_close)

public:
	m_close(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~m_close();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	DECLARE_MESSAGE_MAP()
};
