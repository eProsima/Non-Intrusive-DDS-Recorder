#ifndef _CDR_CONTENTTYPECODE_H_
#define _CDR_CONTENTTYPECODE_H_

#include "cdr/TypeCode.h"

namespace eProsima
{
    class ContentTypeCode : public TypeCode
    {
    public:

        /*!
         * @brief This function returns the typecode of the content.
         */
        const TypeCode* getContentTypeCode() const;

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
