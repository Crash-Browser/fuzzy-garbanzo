/**********************************************************************

  Audacity: A Digital Audio Editor

  HelpSystem.h

  Jimmy Johnson
  James Crook

  was merged with LinkingHtmlWindow.h

  Vaughan Johnson
  Dominic Mazzoni

  utility fn and
  descendant of HtmlWindow that opens links in the user's
  default browser

**********************************************************************/

#ifndef __AUDACITY_HELPSYSTEM__
#define __AUDACITY_HELPSYSTEM__


#include <wx/defs.h>
#include "wxPanelWrapper.h" // to inherit
#include "../HelpText.h"

class TenacityProject;

/** @brief Class which contains static methods and data needed for implementing
 * help buttons
 *
 * This class should be the only place in the codebase where the location of
 * the online copy of the Audacity manual is stored, so that it can be 
 * changed if required
 */
class TENACITY_DLL_API HelpSystem
{
public:
   /// Displays cuttable information in a text ctrl, with an OK button.
   static void ShowInfoDialog( wxWindow *parent,
                     const TranslatableString &dlogTitle,
                     const TranslatableString &shortMsg,
                     const wxString &message, 
                     const int xSize, const int ySize);

   /// Displays a NEW window with wxHTML help.
   /// @param HtmlText The literal HTML code to go into the window.
   /// @param bModal Whether the resulting window should be modal or not.
   /// Default is modeless dialogue
   static void ShowHtmlText( wxWindow * pParent, 
                   const TranslatableString &Title,
                   const wxString &HtmlText,
                   bool bModal = false);

   /// Displays a file in your browser, if it's available locally,
   /// OR else links to the internet. Generally using this outside this class
   /// is depreciated in favour of the "smarter" overload below, unless there
   /// is a good reason for using this form.
   /// @param parent Parent window for the dialog
   /// @param localFileName Name and path of the file on the local machine
   /// file system to be opened. file.name#anchor syntax is allowed, and therefore
   /// file names containing a '#' are not (on any platform).
   /// @param remoteURL use instead of file if nonempty, and user preferences specify remote,
   /// or localFileName is invalid
   /// @param bModal Whether the resulting dialogue should be modal or not.
   /// Default is modeless dialogue
   static void ShowHelp(wxWindow *parent,
                     const FilePath &localFileName,
                     const URLString &remoteURL,
                     bool bModal = false);

   /// Displays a page from the Audacity manual  in your browser, if
   /// it's available locally, OR else links to the internet.
   /// @param parent Parent window for the dialog
   /// @param PageName The name of the manual page to display as it is in
   /// _development version_ of the manual (i.e. in MediaWiki), _not_ the
   /// converted file name used for offline and released manuals.
   /// @param bModal Whether the resulting dialogue should be modal or not.
   /// Default is modeless dialogue
   static void ShowHelp(wxWindow *parent,
                     const ManualPageID &PageName,
                     bool bModal = false);

   /// Hostname (domain name including subdomain) of the server on which the
   /// online help is available
   static const wxString HelpHostname;

   /// URL path on the help server to the root directory of the manual.
   /// index and quick_help are here in the on-line release manual.
   /// Must both start and end with '/' characters.
   static const wxString HelpServerHomeDir;

   /// Path to sub-directory where the manual pages are located.
   /// index and quick_help are here only in the alpha manual.
   /// Must both start and end with '/' characters.
   static const wxString HelpServerManDir;

   /// Sub-directory for local help pages (but not index.html
   /// or quick_help.html)
   /// Must both start and end with '/' characters.
   static const wxString LocalHelpManDir;

};

class ShuttleGui;

#include "HtmlWindow.h" // to inherit

TENACITY_DLL_API void OpenInDefaultBrowser(const URLString& link);


/// \brief An HtmlWindow that handles linked clicked - usually the
/// link will go to our own local copy of the manual, but it could
/// launch a new browser window.
class TENACITY_DLL_API LinkingHtmlWindow final : public HtmlWindow
{
 public:
   LinkingHtmlWindow(wxWindow *parent, wxWindowID id = -1,
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize,
                     long style = wxHW_SCROLLBAR_AUTO);
   void OnLinkClicked(const wxHtmlLinkInfo& link) override;
   //void OnSetTitle(const wxString& title) override;

};


/// Adds some event handling to an HtmlWindow
class HtmlTextDialog final : public wxDialogWrapper
{
public:
   enum { ID = 0 };
   HtmlTextDialog(wxWindow *pParent, const TranslatableString &title);
   ~HtmlTextDialog() override;

   void SetHtml(const wxString& text);

private:
   void OnClose(wxCommandEvent & event);
   void OnKeyDown(wxKeyEvent & event);

   LinkingHtmlWindow* mpHtml;
   bool mDismissed{};
   DECLARE_EVENT_TABLE()
};

#endif // __AUDACITY_HELPSYSTEM__
