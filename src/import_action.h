#ifndef _IMPORT_ACTION_H_INCLUDED_
#define _IMPORT_ACTION_H_INCLUDED_

#include "action_thread.h"
#include "import_dlg.h"

class ImportAction:public ActionThread
{
private:
  ImportDlg::sData Data;
  wxFrame *m_pFrame;

public:
  ImportAction (wxFrame * frame, apr_pool_t * __pool, Tracer * tr);

  void Perform ();
  void *Entry ();
};

#endif