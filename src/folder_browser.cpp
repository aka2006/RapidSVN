#include "include.h"
#include "rapidsvn_app.h"

#include "folder_browser.h"

FolderBrowser::FolderBrowser (wxWindow * wnd,
                              apr_pool_t * __pool,
                              const wxWindowID id,
                              const wxString & dir,
                              const wxPoint & pos,
                              const wxSize & size,
                              long style,
                              const wxString & filter,
                              int defaultFilter, const wxString & name):
wxGenericDirCtrl (wnd, id, dir, pos, size, style, filter, defaultFilter, name)
{
  pool = __pool;


  wxTreeCtrl *treeCtrl = GetTreeCtrl ();

  if (treeCtrl)
  {
    wxTreeItemId rootId = treeCtrl->GetRootItem ();
    CollapseDir (rootId);
    ExpandDir (rootId);
  }

}

FolderBrowser::~FolderBrowser ()
{
}

void
FolderBrowser::OnSelChanged (wxTreeEvent & event)
{
  // This should be propagated to the parent frame,
  // which will trigger the appropiate action.
  wxGetApp ().GetAppFrame ()->GetFileList ()->UpdateFileList (GetPath ());
}

void
FolderBrowser::OnKeyDown (wxTreeEvent & event)
{
  if (event.GetKeyEvent ().GetKeyCode () == WXK_F5)
  {
    // F5 was pressed, force a refresh
    wxGetApp ().GetAppFrame ()->GetFileList ()->UpdateFileList (GetPath ());
  }
  else
  {
    event.Skip ();
  }
}

void
FolderBrowser::SetupSections ()
{
  wxTreeCtrl *treeCtrl = GetTreeCtrl ();

  if (treeCtrl)
  {
    m_workbenchId = AddSection ("", wxT ("Workbench"), 3);
  }
}


void
FolderBrowser::ExpandDir (const wxTreeItemId & parentId)
{
  if (parentId == m_workbenchId)
  {
    wxTreeCtrl *treeCtrl = GetTreeCtrl ();

    if (treeCtrl)
    {
      const size_t childCount = treeCtrl->GetChildrenCount (parentId, FALSE);

      if (childCount == 0)
      {
        const size_t count = m_workbenchItems.GetCount ();
        size_t index;
        for (index = 0; index < count; index++)
        {
          const wxString & item = m_workbenchItems.Item (index);
          PatchedDirItemData *itemData =
            new PatchedDirItemData (item, item, TRUE);
          const wxTreeItemId & itemId =
            treeCtrl->AppendItem (parentId, item, 0, -1, itemData);
          treeCtrl->SetItemHasChildren (itemId);
        }
      }
    }
  }
  else
  {
    PatchedGenericDirCtrl::ExpandDir (parentId);
  }
}


void
FolderBrowser::CollapseDir (const wxTreeItemId & parentId)
{
  wxTreeCtrl *treeCtrl = GetTreeCtrl ();
  wxTreeItemId child;

  PatchedDirItemData *data =
    (PatchedDirItemData *) treeCtrl->GetItemData (parentId);

  if (data)
  {
    data->m_isExpanded = FALSE;
    long cookie;
    child = treeCtrl->GetFirstChild (parentId, cookie);
    while (child.IsOk ())
    {
      treeCtrl->Delete (child);
      child = treeCtrl->GetFirstChild (parentId, cookie);
    }
  }
  wxGenericDirCtrl::CollapseDir (parentId);
}


void
FolderBrowser::SetWorkbenchItems (const wxArrayString & workbenchItems)
{
  m_workbenchItems = workbenchItems;

  CollapseDir (m_workbenchId);
  ExpandDir (m_workbenchId);
}

const wxArrayString
FolderBrowser::GetWorkbenchItems ()
{
  return m_workbenchItems;
}


BEGIN_EVENT_TABLE (FolderBrowser, wxGenericDirCtrl)
EVT_TREE_SEL_CHANGED (-1, FolderBrowser::OnSelChanged)
EVT_TREE_KEY_DOWN (-1, FolderBrowser::OnKeyDown) END_EVENT_TABLE ()