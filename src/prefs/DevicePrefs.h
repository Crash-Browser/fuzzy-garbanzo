/**********************************************************************

  Audacity: A Digital Audio Editor

  DevicePrefs.h

  Joshua Haberman
  James Crook

**********************************************************************/

#ifndef __AUDACITY_DEVICE_PREFS__
#define __AUDACITY_DEVICE_PREFS__

#include <wx/defs.h>

#include "PrefsPanel.h"

class wxChoice;
class ShuttleGui;

#define DEVICE_PREFS_PLUGIN_SYMBOL ComponentInterfaceSymbol{ XO("Device") }

class DevicePrefs final : public PrefsPanel
{
 public:
   DevicePrefs(wxWindow * parent, wxWindowID winid, TenacityProject* project);
   virtual ~DevicePrefs();
   ComponentInterfaceSymbol GetSymbol() override;
   TranslatableString GetDescription() override;

   bool Commit() override;
   ManualPageID HelpPageName() override;
   void PopulateOrExchange(ShuttleGui & S) override;

 private:
   void Populate();
   void GetNamesAndLabels();

   void OnHost(wxCommandEvent & e);
   void OnDevice(wxCommandEvent & e);

   TranslatableStrings mHostNames;
   wxArrayStringEx mHostLabels;

   std::string mPlayDevice;
   std::string mRecordDevice;
   long mRecordChannels;

   wxChoice *mHost;
   wxChoice *mPlay;
   wxChoice *mRecord;
   wxChoice *mChannels;
   TenacityProject* mProject;

   DECLARE_EVENT_TABLE()
};

#endif
