#pragma once
#define DBVIEW_DB_ITEM		0
#define DBVIEW_TABLE_ITEM	1

// CDBView 视图

class CDBView : public CTreeView
{
	DECLARE_DYNCREATE(CDBView)

protected:
	CDBView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDBView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
private:
	CImageList m_treeImageList;
public:

	HTREEITEM m_hCurrDBItem;
	HTREEITEM m_hCurrTBItem;

	CTreeCtrl *m_pTreeCtrl;

	bool m_bAddDB;  //状态是否为添加数据库
	bool m_bAddTB;  //状态是否为添加表

	CString GetSelectedDBName();//得到当前被选择的数据库名
	CString GetSelectedTBName();//得到当前被选择的表名
	void DisplayDBList();		//显示数据库列表
	
	void GetDBAndTableName(CString &dbName,CString &tbName);

	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCrtDB();
	afx_msg void OnOpenDB();
	afx_msg void OnDeleteDB();
	afx_msg void OnCrtTable();
	afx_msg void OnLookTable();
	afx_msg void OnConditionQuery();
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeleteTable();
	afx_msg void OnDesignTable();
	afx_msg void OnRenameDB();
	afx_msg void OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAddTable();
	afx_msg void OnBackupDB();
	afx_msg void OnRecoveryDB();
	afx_msg void OnClearTable();
	afx_msg void OnLookLog();
};


