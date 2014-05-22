#pragma once
#include <memory>
#include <vector>

#include "afxwin.h"
#include "Server.h"
#include "log.h"

class CWSAAsyncSelectDlg : public CDialog
{
public:
	explicit CWSAAsyncSelectDlg(CWnd* pParent = nullptr);	// standard constructor

	enum { IDD = IDD_WSAASYNCSELECT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnSocketMsg(WPARAM wParam, LPARAM lParam);
public:
	CListBox m_ctOutput;
private:
	std::unique_ptr<echoservice::Server> m_server;
	std::vector<char> m_send_buffer;
	echoservice::output m_out;

public:
	afx_msg void OnBnClickedStartServer();
};
