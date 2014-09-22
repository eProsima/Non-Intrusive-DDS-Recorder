#ifndef _CDR_SEQUENCETYPECODE_H_
#define _CDR_SEQUENCETYPECODE_H_

#include "cdr/ContentTypeCode.h"

namespace eProsima
{
    class Cdr;

    class SequenceTypeCode : public ContentTypeCode
    {
    public:
        //! @brief Default constructor.
        SequenceTypeCode();
        //!@brief Max Length Constructor
        SequenceTypeCode(uint32_t maxL):ContentTypeCode(TypeCode::KIND_SEQUENCE),m_maxLength(maxL){}

        //! @brief Default destructor.
        virtual ~SequenceTypeCode(){}

        /*!
         * @brief This function returns the member count of the membered type.
         */
        uint32_t getMaxLength() const;
        
        /*!
         * @brief This function deserializes an array that is contained in a CDR stream.
         *
         * @param Reference to the CDR stream.
         * @return if the operation works successfully then a true value is returned. In other case false value is returned.
         */
        bool deserialize(Cdr &cdr);

        bool print(IDLPrinter &printer, bool write) const;

    private:

        uint32_t m_maxLength;
    };
};

#endif // _CDR_SEQUENCETYPECODE_H_
