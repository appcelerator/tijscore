/**
 * Appcelerator Titanium License
 * This source code and all modifications done by Appcelerator
 * are licensed under the Apache Public License (version 2) and
 * are Copyright (c) 2009-2014 by Appcelerator, Inc.
 */

/*
 * Copyright (C) 2008 Apple Inc. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef CallIdentifier_h
#define CallIdentifier_h

#include <wtf/text/CString.h>
#include <wtf/text/StringHash.h>
#include <wtf/text/WTFString.h>

namespace TI {

    struct CallIdentifier {
        WTF_MAKE_FAST_ALLOCATED;
    public:
        String m_name;
        String m_url;
        unsigned m_lineNumber;

        CallIdentifier()
            : m_lineNumber(0)
        {
        }

        CallIdentifier(const String& name, const String& url, int lineNumber)
            : m_name(String(name.characters(),name.length()))
            , m_url(!url.isNull() ? String(url.characters(),url.length()) : "")
            , m_lineNumber(lineNumber)
        {
        }

        inline bool operator==(const CallIdentifier& ci) const { return ci.m_lineNumber == m_lineNumber && ci.m_name == m_name && ci.m_url == m_url; }
        inline bool operator!=(const CallIdentifier& ci) const { return !(*this == ci); }

        struct Hash {
            static unsigned hash(const CallIdentifier& key)
            {
                unsigned hashCodes[3] = {
                    key.m_name.impl()->hash(),
                    key.m_url.impl()->hash(),
                    key.m_lineNumber
                };
                return StringHasher::hashMemory<sizeof(hashCodes)>(hashCodes);
            }

            static bool equal(const CallIdentifier& a, const CallIdentifier& b) { return a == b; }
            static const bool safeToCompareToEmptyOrDeleted = true;
        };

        unsigned hash() const { return Hash::hash(*this); }

#ifndef NDEBUG
        operator const char*() const { return c_str(); }
        const char* c_str() const { return m_name.utf8().data(); }
#endif
    };

} // namespace TI

namespace WTI {

    template<> struct DefaultHash<TI::CallIdentifier> { typedef TI::CallIdentifier::Hash Hash; };

    template<> struct HashTraits<TI::CallIdentifier> : GenericHashTraits<TI::CallIdentifier> {
        static void constructDeletedValue(TI::CallIdentifier& slot)
        {
            new (NotNull, &slot) TI::CallIdentifier(String(), String(), std::numeric_limits<unsigned>::max());
        }
        static bool isDeletedValue(const TI::CallIdentifier& value)
        {
            return value.m_name.isNull() && value.m_url.isNull() && value.m_lineNumber == std::numeric_limits<unsigned>::max();
        }
    };

} // namespace WTI

#endif  // CallIdentifier_h

