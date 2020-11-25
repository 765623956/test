// UserDlg.cpp : ʵ���ļ�
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


// CUserDlg ���

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


// CUserDlg ��Ϣ�������


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_user = TEXT("����Ա");

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name,pwd);
	m_name = name;

	//����Ϣͬ�����ؼ���ȥ
	UpdateData(FALSE);
	// TODO: �ڴ����ר�ô����/����û���
}


void CUserDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�޸����빦��
	UpdateData(TRUE);//�õ��ؼ������µ�ֵ
	if (m_newPwd.IsEmpty()||m_surePwd.IsEmpty()) {
		MessageBox(TEXT("���벻��Ϊ�գ�"));
	}
	if (m_newPwd != m_surePwd) {
		MessageBox(TEXT("������������벻ͬ��"));
	}
	//��ȡԭ����
	CInfoFile file;
	CString name,pwd;
	file.ReadLogin(name, pwd);
	if (pwd == m_newPwd) {
		MessageBox(TEXT("�����벻����ԭ������ͬ��"));
	}

	//cstringת��char*
	CStringA tmp;
	CStringA tmp2;
	tmp = name;
	tmp2 = m_newPwd;
	file.WritePwd(tmp.GetBuffer(),tmp2.GetBuffer());
	MessageBox(TEXT("�����޸ĳɹ���"));

	//�������
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}
