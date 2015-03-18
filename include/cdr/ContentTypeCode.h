/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _CDR_CONTENTTYPECODE_H_
#define _CDR_CONTENTTYPECODE_H_

#include "cdr/TypeCode.h"

namespace eprosima
{
    class ContentTypeCode : public TypeCode
    {
    public:

        /*!
         * @brief This function returns the typecode of the content.
         */
        const TypeCode* getContentTypeCode() const;

        void setContentTypeCode(TypeCode*);

    protected:

        //! @brief Default constructor.
        ContentTypeCode(uint32_t kind);

        //! @brief Default destructor.
        virtual ~ContentTypeCode();

        bool deserializeContent(Cdr &cdr);

    private:

        TypeCode * m_contentTypeCode;
    };
};

#endif // _CDR_CONTENTTYPECODE_H_
