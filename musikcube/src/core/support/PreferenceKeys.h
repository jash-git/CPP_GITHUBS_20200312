//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004-2019 musikcube team
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the author nor the names of other contributors may
//      be used to endorse or promote products derived from this software
//      without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>

namespace musik { namespace core { namespace prefs {

    namespace components {
        extern const std::string Settings;
        extern const std::string Libraries;
        extern const std::string Playback;
        extern const std::string Plugins;
        extern const std::string Session;
    }

    namespace keys {
        extern const std::string AutoSyncIntervalMillis;
        extern const std::string MaxTagReadThreads;
        extern const std::string RemoveMissingFiles;
        extern const std::string SyncOnStartup;
        extern const std::string Volume;
        extern const std::string RepeatMode;
        extern const std::string TimeChangeMode;
        extern const std::string OutputPlugin;
        extern const std::string Transport;
        extern const std::string Locale;
        extern const std::string IndexerLogEnabled;
        extern const std::string ReplayGainMode;
        extern const std::string PreampDecibels;
        extern const std::string SaveSessionOnExit;
        extern const std::string LastPlayQueueIndex;
        extern const std::string LastPlayQueueTime;
        extern const std::string LastFmToken;
        extern const std::string LastFmSessionId;
        extern const std::string LastFmUsername;
        extern const std::string DisableAlbumArtistFallback;
        extern const std::string AuddioApiToken;
    }

} } }

