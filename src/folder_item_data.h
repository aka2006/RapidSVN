#ifndef _FOLDER_ITEM_DATA_H_
#define _FOLDER_ITEN_DATA_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "folder_item_data.h"
#endif

#include "wx/wx.h"
#include "wx/treectrl.h"

enum
{
    FOLDER_TYPE_INVALID,
    FOLDER_TYPE_WORKBENCH,
    FOLDER_TYPE_PROJECT,
    FOLDER_TYPE_NORMAL
};

class FolderItemData:public wxTreeItemData
{
 public: 
    FolderItemData(const int folderType,  
		   const wxString & path = wxEmptyString, 
		   const wxString & name = wxEmptyString,
		   const bool hasChildren = FALSE);

    FolderItemData();

    FolderItemData(const FolderItemData& src);	

    void Create(const int folderType,  
		const wxString & path = wxEmptyString, 
		const wxString & name = wxEmptyString,
		const bool hasChildren = FALSE);
    
    const int getFolderType()
	{
	    return m_folderType;
	}

    const wxString& getPath()
	{
	    return m_path;
	}

    const wxString& getName()
	{
	    return m_name;
	}

    const bool hasChildren()
	{
	    return m_hasChildren;
	}

 private:
    int m_folderType;
    wxString m_path;
    wxString m_name;
    bool m_hasChildren;
};


#endif