/*
 * ====================================================================
 * Copyright (c) 2002 The RapidSvn Group.  All rights reserved.
 *
 * This software is licensed as described in the file LICENSE.txt,
 * which you should have received as part of this distribution.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */
#ifndef _IDS_H_INCLUDED_
#define _IDS_H_INCLUDED_

/*
 * Menu commands IDs
 */
enum
{
  ID_Quit = 1,
  ID_About,
  ID_Refresh,
  ID_Import,
  ID_Checkout,
  ID_Copy,
  ID_Rename,
  ID_Combo,
  ID_Update,
  ID_Commit,
  ID_Add,
  ID_Del,
  ID_Revert,
  ID_Log,
  ID_Info,
  ID_Resolve,
  ID_Merge,
  ID_Contents,
  ID_Mkdir,
  ID_Switch,
  ID_Preferences,
  ID_Property,
  ID_AddProject,
  ID_RemoveProject,
  ID_MoveTo,
  ID_CopyTo,
  ID_RenameHere,
  ID_CopyHere,

  ACTION_EVENT,                 // this one gets sent from the action threads

  LIST_CTRL = 1000
};

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */