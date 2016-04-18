// MPT5Dlg.h : ͷ�ļ�
//

#pragma once
#include "ocx.h"
#include "afxwin.h"
#include "CWMPControls.h"
#include "CWMPMedia.h"
#include "afxcmn.h"
#include "CWMPSettings.h"
#define WM_SHOWTASK (WM_USER +1)

#define WM_MYMESSAGE2 (WM_USER+3)
#define WM_MYMESSAGE1 (WM_USER+2)

// CMPT5Dlg �Ի���
class CMPT5Dlg : public CDialog
{
// ����
public:
	CMPT5Dlg(CWnd* pParent = NULL);	// ��׼���캯��

	void ToTray();
	void DeleteTray();
	VOID OpenWindow();
	void AboutUs();

// �Ի�������
	enum { IDD = IDD_MPT5_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Handler(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Handler1(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Handler2(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	COcx m_player;
	CWMPSettings m_settings;
	CToolTipCtrl m_tooltip;
	CWMPMedia m_media;
	CWMPControls m_ctr;
	CBitmap m_background;
	afx_msg void OnPlay();
	
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);


	afx_msg void OnBnClickedSetAB();
	afx_msg void OnBnClickedDelaB();
	afx_msg void OnBnClickedList();
	afx_msg void OnBnClickedAddlist();
	afx_msg void OnBnClickedRenamelist();
	afx_msg void OnBnClickedAddfile();
	afx_msg void OnBnClickedDellist();
	afx_msg void OnBnClickedResetlist();
	afx_msg void OnBnClickedAddfolder();
	afx_msg void OnBnClickedRemovefile();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedFastforward();

	afx_msg void OnBnClickedPrevious();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedStop();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedDown();
	CListBox m_list;
	CListBox m_list2;
	CComboBox m_combobox;
	CComboBox m_combobox2;
	
	CStringArray strcontainer;//�����и��
	int counts;//��ʼ�����
	double dtime[100];//��double�͵�ʱ��
	bool ReadLyricsFile(CString);//��ȡ����ļ�

	int flagAB;//����AB��
	int flagPause;//��ͣ���
	int flagForward;//������
	double startP;
	double endP;
	double duration;//��ʱ��
	int sliderPos;//������λ��
	double lengthRate;//������������ʱ�䳤�Ȱٷֱ�
	afx_msg void OnLbnDblclkPlistbox();
	void Save();
	void SetList();
	void MessageTips();
	void InitialSlider();
	CString StandardTime(int,int);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void getFolder(CString,int&,int&,CString&,int );//����ļ��е���
	afx_msg void OnCbnSelchangeListcombo();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CEdit m_time;
	CSliderCtrl m_slider;
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton1();
	CBitmapButton m_play;
	CBitmapButton m_previous;
	CBitmapButton m_next;
	CBitmapButton m_stop;
	CBitmapButton m_up;
	CBitmapButton m_down;
	CBitmapButton m_flexlist;
	CBitmapButton m_setab;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CBitmapButton m_delab;
	CBitmapButton m_fastforward;
	CButton m_addlist;
	CButton m_renamelist;
	CButton m_dellist;
	CButton m_addfolder;
	
	CBitmapButton m_mute;
	CBitmapButton m_trash;
	CBitmapButton m_addfile;
	CBitmapButton m_removefile;
	CBitmapButton m_esc;
	CBitmapButton m_marka;
	CBitmapButton m_markb;
protected:
//	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg void OnBnClickedCheck1();
	CEdit m_lyric;
	CButton m_geci;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CSliderCtrl m_valumSlider;
};
