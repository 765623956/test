
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "SaleSystem.h"

#include "MainFrm.h"
#include "infoFile.h"
#include "SelectView.h"
#include "DispalyView.h"
#include "UserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE��Ӧ�����Զ�����Ϣ
	//����NM_X��Ϣ���Զ�����OnMyChange����
	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//����ͼ�꣬IDI_ICON_WINΪͼ����ԴID����ΪWINAPI����
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_WIN));

	//���ñ���--�Ҳ�
	SetTitle(TEXT("2020/11/8"));
	//���ñ������ ��doc��

	//���ô��ڵ�λ�úʹ�С��CWnd::MoveWindow
	//0, 0, �������x��y
	//800, 500, ���ڿ�Ⱥ͸߶�
	MoveWindow(0, 0, 800, 500);

	//�������ƶ�����Ļ���룬CWnd::CenterWindow
	CenterWindow();

	//�����¶�ȡ�ļ�������
//	CInfoFile file;
//	CString name;
//	CString pwd;
////	file.WritePwd("��ͷ�����", "123");
//	file.ReadLogin(name,pwd);
	//MessageBox(name);
	//MessageBox(pwd);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	//���һ������
	m_spliter.CreateStatic(this,1,2);
	//�����Ҳ�������ʾ����
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500), pContext);
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDispalyView), CSize(600, 500), pContext);
	return TRUE;//�Լ����
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext   Context;
	if (wParam == NM_A) {
		//MessageBox(TEXT("������Ϣ������أ�"));
		//���ؽ��棨��δ��벻��Ҫ�Լ��ǣ��õ�ʱ����ֱ���ң�
		Context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 500), &Context);
		CUserDlg *pNewView = (CUserDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_B) {
		MessageBox(TEXT("���۹��������أ�"));
	}



	return 0;
}
