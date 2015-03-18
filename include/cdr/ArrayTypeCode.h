/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _CDR_ARRAYTYPECODE_H_
#define _CDR_ARRAYTYPECODE_H_

#include "cdr/ContentTypeCode.h"

#include <vector>


namespace eprosima
{
	namespace fastcdr{

	class Cdr;
	}
	using namespace fastcdr;

    class ArrayTypeCode : public ContentTypeCode
    {
    public:
        //! @brief Default constructor.
        ArrayTypeCode();
        //! @brief Dimension-constructor
        ArrayTypeCode(std::vector<int32_t>&);

        //! @brief Default destructor.
        virtual ~ArrayTypeCode(){}

        /*!
         * @brief This function returns the member count of the membered type.
         */
        uint32_t getDimensionCount() const;

        /*!
         * @brief This function return the selected dimension.
         */
        uint32_t getDimension(uint32_t dim) const;
        
        /*!
         * @brief This function deserializes an array that is contained in a CDR stream.
         *
         * @param Reference to the CDR stream.
         * @return if the operation works successfully then a true value is returned. In other case false value is returned.
         */
        bool deserialize(Cdr &cdr);

        bool print(IDLPrinter &printer, bool write) const;



    private:

        uint32_t m_dimensionCount;

        std::vector<uint32_t> m_dimensions;
    };
};

#endif // _CDR_ARRAYTYPECODE_H_
