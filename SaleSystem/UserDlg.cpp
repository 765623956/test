// UserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "UserDlg.h"
#include "InfoFile.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_USER)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_surePwd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDOK, &CUserDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUserDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_user = TEXT("销售员");

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name,pwd);
	m_name = name;

	//将信息同步到控件中去
	UpdateData(FALSE);
	// TODO: 在此添加专用代码和/或调用基类
}


void CUserDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//修改密码功能
	UpdateData(TRUE);//拿到控件中最新的值
	if (m_newPwd.IsEmpty()||m_surePwd.IsEmpty()) {
		MessageBox(TEXT("输入不能为空！"));
	}
	if (m_newPwd != m_surePwd) {
		MessageBox(TEXT("两次输入的密码不同！"));
	}
	//获取原密码
	CInfoFile file;
	CString name,pwd;
	file.ReadLogin(name, pwd);
	if (pwd == m_newPwd) {
		MessageBox(TEXT("新密码不能与原密码相同！"));
	}

	//cstring转换char*
	CStringA tmp;
	CStringA tmp2;
	tmp = name;
	tmp2 = m_newPwd;
	file.WritePwd(tmp.GetBuffer(),tmp2.GetBuffer());
	MessageBox(TEXT("密码修改成功！"));

	//清空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}
