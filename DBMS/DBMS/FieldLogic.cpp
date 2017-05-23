#include "stdafx.h"
#include "FieldLogic.h"
#include "RecordDAO.h"
#include "FieldDAO.h"
#include "SystemLogic.h"

CFieldLogic::CFieldLogic(CString dbName,CString tableName)
{
	this->tdfPath = DEFAULT_ROOT+CString("/")+dbName+CString("/")+tableName+CString(".tdf");
	this->trdPath = DEFAULT_ROOT+CString("/")+dbName+CString("/")+tableName+CString(".trd");
	this->dbName = dbName;
	this->tbName = tableName;
}


CFieldLogic::~CFieldLogic(void)
{
}

//获得数据库文件夹路径
CString CFieldLogic::GetDBFolder(const CString strDBName)
{
	CString strFolder = _T("");
	try
	{
		// Get the path of the database folder
		strFolder.Format(_T("data\\%s"), strDBName);
		strFolder = GetAbsolutePath(strFolder);
	}
	catch (CConditionQuery* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CConditionQuery(_T("获得数据库文件夹路径失败!"));
	}

	return strFolder;
}

//获得tb文件路径
CString CFieldLogic::GetTableFile(const CString strDBName)
{
	CString strPath = _T("");
	try
	{
		// Get the absolute path of the table description file(*.tb)
		strPath.Format(_T("data\\%s\\%s.tb"), strDBName, strDBName);
		strPath = GetAbsolutePath(strPath);
	}
	catch (CConditionQuery* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CConditionQuery(_T("获得tb文件路径失败!"));
	}
	return strPath;
}


//创建字段
int CFieldLogic::CreateField(CFieldEntity &field)
{
	vector<CFieldEntity> flist=CFieldDAO::ReadFieldList(tdfPath);
	bool fExist=false;
	for (vector<CFieldEntity>::iterator ite=flist.begin();ite!=flist.end();++ite)
	{
		if(ite->GetName()==field.GetName())
		{
			fExist=true;
			break;
		}
	}

	if(!fExist)
	{
		int counter = CFieldDAO::GetFieldCounter(tdfPath);
		field.SetId(++counter);
		if(!CFieldDAO::WriteAnField(field,tdfPath))
			return ADD_ERROR;
		
		if(!CFieldDAO::SaveFieldCounter(tdfPath,counter))
			return SAVE_COUNTER_ERROR;

		CSystemLogic sysLogic;
		sysLogic.WriteLog(CString("created field: ")+field.GetName()+CString(". database: ")+dbName+CString(" table: ")+tbName);

		return YES;
	}
	else
	{
		return FIELD_EXIST;
	}
}

//删除字段
int CFieldLogic::DeleteField(CString &fieldName)
{
	vector<CFieldEntity> list = CFieldDAO::ReadFieldList(tdfPath);
	int index = 0;

	for (int i = 0; i < list.size(); i++)
	{
		if(list[i].GetName()==fieldName)
		{
			index = i;
			break;
		}
	}

	if(!CRecordDAO::DeleteFieldRecord(trdPath,index+1))
		return DELETE_ERROR;
	if (!CFieldDAO::DeleteField(fieldName, tdfPath))
		return DELETE_ERROR;
	CSystemLogic sysLogic;
	sysLogic.WriteLog(CString("deleted field: ")+fieldName+CString(". database: ")+dbName+CString(" table: ")+tbName);
	return YES;
}

//修改字段
int CFieldLogic::ModifyField(CFieldEntity &field)
{
	if(CFieldDAO::ModifyField(field,tdfPath))
	{
		CSystemLogic sysLogic;
		sysLogic.WriteLog(CString("modified field, field id:")+CUtil::IntegerToString(field.GetId())
						+CString(" database: ")+dbName+CString(" table: ")+tbName);
	
		return YES;
	}
	else
		return MODIFY_ERROR;
}


vector<CFieldEntity> CFieldLogic::GetFieldList()
{
	return CFieldDAO::ReadFieldList(this->tdfPath);
}
