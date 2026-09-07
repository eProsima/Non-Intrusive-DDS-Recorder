/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "database/TableNamer.h"

#include <stdio.h>

using namespace eprosima;
using namespace std;

string TableNamer::reserve(
        const string& base)
{
    string sanitized;

    for (size_t i = 0; i < base.length(); ++i)
    {
        char c = base[i];

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_')
        {
            sanitized += c;
        }
        else
        {
            sanitized += '_';
        }
    }

    string candidate = sanitized;
    unsigned int suffix = 1;

    while (taken_.find(candidate) != taken_.end())
    {
        char tail[16];
        snprintf(tail, sizeof(tail), "_%u", ++suffix);
        candidate = sanitized + tail;
    }

    taken_.insert(candidate);

    return candidate;
}
