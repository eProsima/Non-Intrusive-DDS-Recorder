/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _TABLENAMER_H_
#define _TABLENAMER_H_

#ifdef __cplusplus

#include <set>
#include <string>

namespace eprosima {

/**
 * \brief Hands out the SQL name of every table the '-queryable' schema creates.
 *
 * A DDS topic name is not a legal SQL identifier, and the tables of a topic are named after it, so
 * the name has to be sanitized. Sanitizing loses information: two different topic names can end up
 * with the same identifier, and so can a topic's own table and the child table of another topic's
 * collection member. A topic called 'A b' sanitizes to 'Data_A_b', which is also what a topic 'A'
 * with a sequence member 'b' calls its child table.
 *
 * Every table name, of a topic or of one of its collection members, is therefore reserved here.
 * Whichever is asked for second gets a numeric suffix instead of silently replacing the first,
 * which matters because the tables are dropped before being created. DataTables records what each
 * name ended up being, so a reader never has to reproduce any of this.
 */
class TableNamer
{
public:

    /**
     * \brief Reserves an SQL identifier built from \c base.
     *
     * \param base The desired name, which may contain characters that are not legal in an
     * identifier.
     * \return \c base sanitized, with a numeric suffix appended when that name is already taken.
     */
    std::string reserve(
            const std::string& base);

private:

    std::set<std::string> taken_;
};
} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _TABLENAMER_H_
